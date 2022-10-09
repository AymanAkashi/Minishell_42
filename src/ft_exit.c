/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:17:28 by aaggoujj          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/21 12:02:59 by aaggoujj         ###   ########.fr       */
=======
/*   Updated: 2022/10/03 12:59:55 by aaggoujj         ###   ########.fr       */
>>>>>>> origin/update
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_digit(char *str)
{
<<<<<<< HEAD
	int i;
=======
	int	i;
>>>>>>> origin/update

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

<<<<<<< HEAD
void	ft_exit(char **args)
{
	if(args[1] == NULL)
		exit(0);
=======
void	ft_exit(char **args, t_data *data)
{
	if (args[1] == NULL)
	{
		free_all(data, 2);
		exit(g_exitstatus);
	}
>>>>>>> origin/update
	if (check_digit(args[1]) && args[2] != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
<<<<<<< HEAD
		exit(ft_atoi(args[1]));
=======
		g_exitstatus = 1;
>>>>>>> origin/update
	}
	else if (!check_digit(args[1]))
	{
		ft_putstr_fd("exit\n", 2);
<<<<<<< HEAD
		print_err("minishell: exit: %s: numeric argument required\n",args[1], 2);
		exit(2);
=======
		print_err("minishell: exit:%s: numeric argument required\n", args[1], 2);
		free_all(data, 2);
		exit(255);
>>>>>>> origin/update
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
<<<<<<< HEAD
		exit(ft_atoi(args[1]));
	}
}
=======
		free_all(data, 2);
		exit(ft_atoi(args[1]));
	}
}
>>>>>>> origin/update
