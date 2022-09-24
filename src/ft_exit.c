/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:17:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/22 22:07:03 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_digit(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

void	ft_exit(char **args)
{
	if(args[1] == NULL)
		exit(0);
	if (check_digit(args[1]) && args[2] != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exitstatus = 1;
	}
	else if (!check_digit(args[1]))
	{
		ft_putstr_fd("exit\n", 2);
		print_err("minishell: exit: %s: numeric argument required\n",args[1], 2);
		exit(2);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(args[1]) % 256);
	}
}