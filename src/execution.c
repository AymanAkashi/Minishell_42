/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:18:13 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/02 20:28:33 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_red(t_ast *ast, t_data *data);

char	**list_to_args(t_list *lst, int env)
{
	char	**args;
	int		i;
	t_env	*e;

	i = 0;
	if (env == 0)
		args = ft_any_alloc(sizeof(char *), ft_lstsize(lst) + 2);
	else
		args = ft_any_alloc(sizeof(char *), ft_lstsize(lst) + 1);
	while (lst)
	{
		e = lst->content;
		args[i] = ft_strjoin(e->name, "=");
		args[i] = ft_strjoin2(args[i], e->value);
		lst = lst->next;
		i++;
	}
	if (env == 0)
		args[i++] = ft_strjoin("PATH=", _PATH_STDPATH);
	args[i] = NULL;
	return (args);
}
//************************************************************************

void	ft_execve(char *str, t_ast *ast, char **envp, int absolut)
{
	if (absolut == 1)
	{
		execve(str, ast->args, envp);
		print_err("Minishell: %s : No such file or directory\n", str, 2);
		g_exitstatus = 127;
		exit(g_exitstatus);
	}
	else
	{
		execve(str, ast->args, envp);
		print_err("Minishell: %s : command not found\n", ast->cmd, 2);
		g_exitstatus = 127;
		exit(g_exitstatus);
	}
}

void	child_cmd(t_ast *ast, t_data *data, int absolut, char *str)
{
	char	**envp;
	char	*cmd;
	int		i;

	i = -1;
	envp = list_to_args(data->envp, data->found_env);
	while (ast->args[++i])
		ast->args[i] = check_expender(ast->args[i], data);
	if (absolut == 2)
		ft_execve(str, ast, envp, 1);
	else
	{
		cmd = get_thecmd(data->path, str);
		ft_execve(cmd, ast, envp, 0);
	}
}
//************************************************************************

int	exec_red(t_ast *ast, t_data *data)
{
	if (ast->left && is_redirection(ast->left->type))
	{
		if (!execut_redirection(ast, ast->left, data))
			return (0);
	}
	if (ast->right && is_redirection(ast->right->type))
	{
		if (!execut_redirection(ast, ast->right, data))
			return (0);
	}
	return (1);
}

void	execution(t_data *data, t_ast *root)
{
	if (!root)
		return ;
	exec_block(root, data);
}
