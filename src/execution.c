/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:18:13 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/31 16:14:26 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_thecmd(char **path, char *cmd)
{
	char	*tmp;
	char	*arg;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		arg = ft_strjoin(tmp, cmd);
		if (access(arg, 0) == 0)
			return (arg);
		free(arg);
		free(tmp);
		path++;
	}
	return (NULL);
}

int	check_if_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

int	check_cmd(char *str, t_data *data)
{
	char	*cmd;

	if (ft_strchr(str,'/'))
	{
		if (check_if_path(str))
			return (2);
		else
			return (0);
	}
	else
	{
		cmd = get_thecmd(data->path, str);
		if (cmd == NULL)
			return (0);
	}
	return (1);
}

char **list_to_args(t_list *lst)
{
	char	**args;
	int		i;
	t_env	*e;

	i = 0;
	args = ft_any_alloc(sizeof(char *), ft_lstsize(lst) + 1);
	while (lst)
	{
		e = lst->content;
		args[i] = ft_strjoin(e->name, "=");
		args[i] = ft_strjoin2(args[i], e->value);
		lst = lst->next;
		i++;
	}
	return (args);
}

void	child_cmd(t_ast *ast, t_data *data, int absolut, char *str)
{
	char **envp;
	char	*cmd;
	int		i;

	i = -1;
	// if (ast->in != STDIN_FILENO)
		dup2(ast->in, 0);
	// if (ast->out != STDOUT_FILENO)
		dup2(ast->out, 1);
	envp = list_to_args(data->envp);
	while(ast->args[++i])
		ast->args[i] = check_expender(ast->args[i], data);
	if (absolut == 1)
	{
		cmd = get_thecmd(data->path, str);
		execve(cmd, ast->args, envp);
		exit(1);
	}
	else
	{
		execve(str, ast->args, envp);
		exit(1);
	}
}

int	execut_redirection(t_ast *ast, t_ast *red ,t_data *data)
{
	(void)data;
	if (red->type == TOKEN_RED_IN)
		ast->in = open(red->args[1], O_RDONLY);
	if (red->type == TOKEN_RED_OUT)
		ast->out = open(red->args[1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (red->type == TOKEN_RED2_OUT)
		ast->out = open(red->args[1], O_CREAT | O_RDWR | O_APPEND, 0000644);
	if (ast->in == -1 || ast->out == -1)
	{
		if (ast->in == -1)
			perror(red->args[1]);
		if (ast->out == -1)
			perror(red->args[1]);
		return (0);
	}
	return (1);
}

void	exec_block(t_ast *ast, t_data *data);
void	execut_pipe(t_ast *ast, t_data *data);

void	execut_cmd(t_ast *ast, t_data *data)
{
	pid_t	pid;
	char	*str;
	int		status;
	int		absolut;

	status = 0;
	
	if (ast->left)
		if (is_redirection(ast->left->type))
			if (!execut_redirection(ast, ast->left, data))
				return ;
	if (ast->right)
		if (is_redirection(ast->right->type))
			if (!execut_redirection(ast, ast->right, data))
				return ;
	str = check_expender(ast->cmd, data);
	absolut = check_cmd(str, data);
	_restctrl();
	if (!absolut)
		perror(str); // TODO check exit status "127"
	pid = fork();
	if (pid == 0)
	{
		dup2(ast->in, STDIN_FILENO);
		dup2(ast->out, STDOUT_FILENO);
		if (ast->in != STDIN_FILENO)
			close(ast->in);
		if (ast->out != STDOUT_FILENO)
			close(ast->out);
		child_cmd(ast, data, absolut, str);
	}
	waitpid(pid, &status, 0);
	g_exitstatus = WEXITSTATUS(status);
	_hidectrl();
}

void	exec_or(t_ast *ast, t_data *data)
{
	exec_block(ast->left, data);
	if (g_exitstatus != 0)
		exec_block(ast->right, data);
}

void	exec_and(t_ast *ast, t_data *data)
{
	exec_block(ast->left, data);
		if (g_exitstatus == 0)
		exec_block(ast->right, data);
}

void	exec_block(t_ast *ast, t_data *data)
{
	if (is_redirection(ast->type))
		execut_redirection(ast, ast, data);
	else if (ast->type == TOKEN_WORD)
		execut_cmd(ast, data);
	else if (ast->type == TOKEN_PIPE)
		execut_pipe(ast, data);
	else
	{
		if (ast->type == TOKEN_AND)
			exec_and(ast, data);
		else
			exec_or(ast, data);
	}
}

void	execut_pipe(t_ast *ast, t_data *data)
{
	int pip[2];

	if (ast->type == TOKEN_PIPE || ast->type == TOKEN_AND || ast->type == TOKEN_OR)
		ast->left->in = ast->in;
	if (is_redirection(ast->type))
		execut_redirection(ast, ast, data);
	else if (ast->type == TOKEN_WORD)
		execut_cmd(ast, data);
	else if (ast->type == TOKEN_OR || ast->type == TOKEN_AND)
		exec_block(ast, data);
	else
	{
		(void)data;
		if(pipe(pip) == -1)
			perror("Pipe :");
		ast->right->in = pip[0];
		ast->left->out = pip[1];
		execut_pipe(ast->left, data);
		close(pip[1]);
		execut_pipe(ast->right, data);
		close(pip[0]);
	}
}

void	execution(t_data *data, t_ast *root)
{
	if (!root)
		return ;
	exec_block(root, data);
}