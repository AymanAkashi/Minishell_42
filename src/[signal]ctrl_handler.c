/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [signal]ctrl_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:12:24 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/20 15:31:38 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	_ctrl_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	_reset_ctrl_handler(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ctrl_d_handler(t_data *data)
{
	printf("\x1B[1;A\x1B[13;Cexit\n");
	if(data->token)
		free_token(&data->token);
	if(data->root)
		free_ast(data->root);
	if(data->scanner)
		free(data->scanner);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
