/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:55:04 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/10/12 16:24:50 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **cmd, int fd)
{
	int	i;
	int	nextl;

	i = -1;
	nextl = 0;
	i = 1;
	while (!ft_strncmp(&cmd[i][0], "-", 1))
	{
		if (check_n(&cmd[i][1]) == 1)
			nextl = 1;
		else
			break ;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		i++;
		if (cmd[i])
			ft_putstr_fd(" ", fd);
	}
	if (nextl == 0)
		ft_putchar_fd('\n', fd);
	g_exitstatus = 0;
	return (0);
}
