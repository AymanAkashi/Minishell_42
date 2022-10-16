/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:47:17 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/11 20:19:50 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pwd(char *pwd)
{
	g_exitstatus = 1;
	free(pwd);
}

int	check_wildcard(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

void	set_signal(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("QUIT: 3\n");
}

void	wait_all(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) != -1)
	{
		if (WIFSIGNALED(status) && status != 13)
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
