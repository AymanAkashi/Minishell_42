/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:08:27 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/06 15:01:47 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__reset_sig(int def)
{
	if (def == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	ft_dup(int in, int out, int p)
{
	if (p > 0)
		close(p);
	__reset_sig(1);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	if (out != STDOUT_FILENO)
		close(out);
}

int	step_exec_cmd(t_ast *ast, t_data *data, int *absolut)
{
	char	*tmp;
	char	**args_exp;
	int		i;

	i = -1;
	args_exp = NULL;
	if (!exec_red(ast, data))
		return (0);
	while (ast->args[++i])
	{
		tmp = check_expender(ast->args[i], data);
		args_exp = d_alloc_tabs(args_exp, tmp);
		if (ft_strcmp(tmp, ast->args[i]))
			free(tmp);
	}
	free_table(ast->args);
	ast->args = args_exp;
	*absolut = check_cmd(ast->args[0], data);
	update_underscore(data, ast->args);
	ast->args = check_args(ast->args);
	return (1);
}
