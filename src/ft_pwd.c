/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 21:00:11 by aaggoujj          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/20 21:03:19 by aaggoujj         ###   ########.fr       */
=======
/*   Updated: 2022/10/04 10:54:33 by aaggoujj         ###   ########.fr       */
>>>>>>> origin/update
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
}
=======
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
	free(pwd);
}
>>>>>>> origin/update
