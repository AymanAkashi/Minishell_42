/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:55:04 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/09/01 04:38:53 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmds)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (cmds[i] && !ft_strcmp(cmds[i], "-n"))
	{
		nl = 1;
		i++;
	}
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], 1);
		if (cmds[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!nl)
		write(1, "\n", 2);
	//g_var.exit_status = 0;
}


int	ft_echo(char **cmd)
{
	int	i;
	int	nextl;

	i = 1;
	nextl = 0;
	while (cmd[i][0] && ft_strcmp(cmd[i][0], "-"))
	{
		while (cmd[i][j] && ft_strcmp(cmd[i][j],"n"))
			j++;
		if (cmd[i][j] && !ft_strcmp(cmd[i][j],"n"))
			break;
		nextl = 1;
		i++;
	}
	while (cmd[i++])
		write(1, &cmd[i], 1);
	if (nextl == 0)
		write(1, "\n", 1);
	return (0);
}
