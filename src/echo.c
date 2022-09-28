/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:55:04 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/09/28 16:15:25 by aaggoujj         ###   ########.fr       */
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

int	check_quotes(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			j++;
		if (str[i] == '\'')
			k++;
		i++;
	}
	if (j % 2 == 0 && k % 2 == 0)
		return (1);
	return (0);
}

int	ft_echo(char **cmd, t_data *data)
{
	int	i;
	int	nextl;

	i = -1;
	nextl = 0;
	while (cmd[++i])
		cmd[i] = check_expender(cmd[i], data);
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
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (nextl == 0)
		printf("\n");
	return (0);
}
