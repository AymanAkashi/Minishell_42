/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [signal]ctrl_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:12:24 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/25 18:50:10 by aaggoujj         ###   ########.fr       */
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

void	_restctrl(void)
{
	struct	termios _termios;

	tcgetattr(STDIN_FILENO, &_termios);
	_termios.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &_termios);
}

void	_hidectrl(void)
{
	struct	termios _termios;

	tcgetattr(STDIN_FILENO, &_termios);
	_termios.c_lflag &= ~ECHOCTL; // diseble ctrl+c "^C"
	tcsetattr(STDIN_FILENO, 0, &_termios);
}

void	_ctrl_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	_reset_ctrl_handler(void)
{
	signal(SIGINT, SIG_DFL);
}

void	ctrl_d_handler(t_data *data)
{
	(void)data;
	printf("\x1B[1;A\x1B[13;Cexit\n");
	rl_clear_history();
	_restctrl();
	exit(EXIT_SUCCESS);
}
