/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:00:11 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/23 18:40:23 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	t_env	*e;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		e = search_env2("PWD", data->envp);
		if (e->value == NULL)
			ft_putstr_fd("minishell: pwd: PWD not set\n", 2);
		else
		{
			ft_putstr_fd(e->value, 1);
			ft_putchar_fd('\n', 1);
		}
	}
	else
		printf("%s\n", pwd);
}
