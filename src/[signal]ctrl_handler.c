/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [signal]ctrl_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:12:24 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/06 20:40:02 by aaggoujj         ###   ########.fr       */
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
	(void)data;
	printf("\x1B[1;A\x1B[13;Cexit\n");
	// free(data->token);
	// free(data->scanner);
	// free_ast(data->root);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
