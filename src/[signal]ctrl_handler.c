/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [signal]ctrl_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:12:24 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/03 10:13:14 by aaggoujj         ###   ########.fr       */
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
