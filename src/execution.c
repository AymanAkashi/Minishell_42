/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:18:13 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/10 13:29:51 by aaggoujj         ###   ########.fr       */
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
	(void)env;
	args = ft_any_alloc(sizeof(char *), ft_lstsize(lst) + 1);
	while (lst)
	{
		e = lst->content;
		args[i] = ft_strjoin(e->name, "=");
		args[i] = ft_strjoin2(args[i], e->value);
		lst = lst->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_execve(char *str, t_ast *ast, t_data *data, int absolut)
{
	char	**envp;

	envp = list_to_args(data->envp, data->found_env);
	if (absolut == 1)
	{
		execve(str, ast->args, envp);
		print_err("Minishell: %s: No such file or directory\n", ast->args[0], 2);
		free_all(data, 1);
		free_table(envp);
		g_exitstatus = 127;
		exit(g_exitstatus);
	}
	else
	{
		execve(str, ast->args, envp);
		print_err("Minishell: %s : command not found\n", ast->args[0], 2);
		free_all(data, 2);
		free_table(envp);
		g_exitstatus = 127;
		exit(g_exitstatus);
	}
}

void	child_cmd(t_ast *ast, t_data *data, int absolut, char *str)
{
	char	*cmd;
	int		i;

	i = -1;
	if (absolut == 2)
		ft_execve(str, ast, data, 1);
	else
	{
		cmd = get_thecmd(data->path, str);
		ft_execve(cmd, ast, data, 0);
	}
}

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
