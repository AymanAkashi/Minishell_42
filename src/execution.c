/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:18:13 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/29 20:32:19 by aaggoujj         ###   ########.fr       */
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

void	execut_cmd(t_ast *ast, t_data *data)
{
	pid_t	pid;
	char	*str;
	int		status;
	int		absolut;

	status = 0;
	str = check_expender(ast->cmd, data);
	absolut = check_cmd(str, data);
	if (!absolut)
		perror(str); // TODO check exit status "127"
	pid = fork();
	if (pid == 0)
		child_cmd(ast, data, absolut, str);
	else
		waitpid(pid, &status, 0);
		WEXITSTATUS(status);

}

void	execution(t_data *data, t_ast *root)
{
	if (root->type == TOKEN_WORD || is_redirection(root->type))
		execut_cmd(root, data);
}