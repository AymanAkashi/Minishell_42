/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:26:53 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 16:25:40 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builting(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

void	exec_builting(char *str, t_data *data, char **args, int fd)
{
	if (!ft_strcmp(str, "echo"))
		ft_echo(args, fd);
	else if (!ft_strcmp(str, "cd"))
		ft_cd(data, args);
	else if (!ft_strcmp(str, "export"))
		ft_export(data, args, fd);
	else if (!ft_strcmp(str, "env"))
		ft_env(data, fd);
	else if (!ft_strcmp(str, "unset"))
		ft_unset(data, args);
	else if (!ft_strcmp(str, "pwd"))
		ft_pwd(data, fd);
	else if (!ft_strcmp(str, "exit"))
	{
		if (args && args[1])
			ft_exit(args, data, ft_atoi(args[1]));
		else
			ft_exit(args, data, 0);
	}
}
