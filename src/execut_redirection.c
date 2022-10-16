/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:35:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 17:47:35 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execut_heredoc(t_ast *ast, t_ast *red, t_data *data, int *pip)
{
	if (red->left && red->left->type == TOKEN_HEREDOC)
		execut_redirection(red, red->left, data);
	else
	{
		if (pipe(pip) == -1)
			perror("Pipe ");
		ft_putstr_fd(red->here_doc, pip[1]);
		ast->in = pip[0];
		close(pip[1]);
	}
	if (ast->in == STDIN_FILENO)
		ast->in = red->in;
}

void	execut_red_in(t_ast *ast, t_ast *red)
{
	ast->in = open(red->args[1], O_RDONLY);
	if (red->in != STDIN_FILENO)
		ast->in = red->in;
}

void	execut_red_out(t_ast *ast, t_ast *red)
{
	ast->out = open(red->args[1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (red->out != STDOUT_FILENO)
		ast->out = red->out;
}

void	execut_red_out2(t_ast *ast, t_ast *red)
{
	ast->out = open(red->args[1], O_CREAT | O_RDWR | O_APPEND, 0000644);
	if (red->out != STDOUT_FILENO)
		ast->out = red->out;
}

int	execut_redirection(t_ast *ast, t_ast *red, t_data *data)
{
	int	pip[2];
	int	i;

	i = -1;
	red->args = check_args(red->args);
	while (red->args[++i])
		red->args[i] = check_expender(red->args[i], data);
	if (!exec_red(red, data))
		return (0);
	if (red->type == TOKEN_RED_IN)
		execut_red_in(ast, red);
	if (red->type == TOKEN_RED_OUT)
		execut_red_out(ast, red);
	if (red->type == TOKEN_RED2_OUT)
		execut_red_out2(ast, red);
	if (red->type == TOKEN_HEREDOC)
		execut_heredoc(ast, red, data, pip);
	if (ast->in == -1 || ast->out == -1)
	{
		perror(red->args[1]);
		return (0);
	}
	return (1);
}
