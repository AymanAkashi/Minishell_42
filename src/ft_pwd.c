/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:00:11 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/10 14:02:44 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data, int fd)
{
	t_env	*e;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		e = search_env2("PWD", data->envp);
		if (e->value == NULL)
			print_err("minishell: pwd: PWD not set\n", NULL, 2);
		else
		{
			ft_putstr_fd(e->value, fd);
			ft_putchar_fd('\n', fd);
		}
	}
	else
	{
		ft_putstr_fd(pwd, fd);
		ft_putchar_fd('\n', fd);
	}
	g_exitstatus = 0;
	free(pwd);
}
