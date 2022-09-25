/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:47:17 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/24 20:14:58 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("QUIT: 3");
}

void	wait_all(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) != -1)
	{
		if (WIFSIGNALED(status))
		{
			g_exitstatus = 128 + WTERMSIG(status);
			set_signal(WTERMSIG(status));
		}
		if (WIFEXITED(status))
		{
			g_exitstatus = WEXITSTATUS(status);
		}
	}
}
