/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:08:27 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/05 17:37:10 by aaggoujj         ###   ########.fr       */
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

int	step_exec_cmd(t_ast *ast, t_data *data, char **str, int *absolut)
{
	int	i;

	i = -1;
	if (!exec_red(ast, data))
		return (0);
	*str = check_expender(ast->cmd, data);
	while (ast->args[++i])
		ast->args[i] = check_expender(ast->args[i], data);
	*absolut = check_cmd(*str, data);
	update_underscore(data, ast->args);
	ast->args = check_args(ast->args);
	return (1);
}
