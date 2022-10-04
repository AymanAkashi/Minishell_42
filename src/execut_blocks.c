/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_blocks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:27:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/04 15:55:27 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execut_cmd(t_ast *ast, t_data *data, int p)
{
	pid_t	pid;
	char	*str;
	int		absolut;

	if (step_exec_cmd(ast, data, &str, &absolut) == 0)
		return ;
	if (is_builting(str) && p < 0)
		exec_builting(str, data, ast->args);
	else
	{
		_restctrl();
		pid = fork();
		if (pid == 0)
		{
			ft_dup(ast->in, ast->out, p);
			if (is_builting(str))
				exec_builting(str, data, ast->args);
			else
				child_cmd(ast, data, absolut, str);
			exit(g_exitstatus);
		}
		__reset_sig(0);
	}
}

void	exec_or(t_ast *ast, t_data *data)
{
	exec_block(ast->left, data);
	wait_all(0);
	if (g_exitstatus != 0)
		exec_block(ast->right, data);
}

void	exec_and(t_ast *ast, t_data *data)
{
	exec_block(ast->left, data);
	wait_all(0);
	if (g_exitstatus == 0)
	{
		printf("i am here\n");
		exec_block(ast->right, data);
	}
}

void	exec_block(t_ast *ast, t_data *data)
{
	if (is_redirection(ast->type))
		execut_redirection(ast, ast, data);
	else if (ast->type == TOKEN_WORD)
		execut_cmd(ast, data, -1);
	else if (ast->type == TOKEN_PIPE)
		execut_pipe(ast, data, -1);
	else
	{
		if (ast->type == TOKEN_AND)
			exec_and(ast, data);
		else
			exec_or(ast, data);
	}
}

void	execut_pipe(t_ast *ast, t_data *data, int p)
{
	int	pip[2];

	if (ast->type == TOKEN_PIPE
		|| ast->type == TOKEN_AND || ast->type == TOKEN_OR)
	{
		ast->left->in = ast->in;
		// ast->right->in = ast->in;
	}
	if (!exec_red(ast, data))
		return ;
	else if (ast->type == TOKEN_WORD)
		execut_cmd(ast, data, p);
	else if (ast->type == TOKEN_OR || ast->type == TOKEN_AND)
		exec_block(ast, data);
	else
	{
		if (pipe(pip) == -1)
			perror("Pipe :");
		ast->right->in = pip[0];
		ast->left->out = pip[1];
		execut_pipe(ast->left, data, pip[0]);
		close(pip[1]);
		execut_pipe(ast->right, data, pip[1]);
		close(pip[0]);
	}
}
