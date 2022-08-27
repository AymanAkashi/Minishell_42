/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:55:04 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/27 20:38:43 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
