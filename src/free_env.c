/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:56:18 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/22 19:00:24 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_del(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}

void	free_env(t_data *env)
{
	t_env	*e;
	t_list	*lst;

	lst = env->envp;
	while (lst)
	{
		e = lst->content;
		ft_env_del(e);
		env->envp = env->envp->next;
		free(lst);
		lst = env->envp;
	}
	free(lst);
	free(env->envp);
}
