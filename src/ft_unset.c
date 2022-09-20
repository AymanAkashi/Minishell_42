/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:19:07 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/21 00:19:16 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(char *cmd, t_list **envp)
{
	t_env	*e;
	t_list	*lst;
	t_list	*tmp;

	lst = *envp;
	while(*envp)
	{
		e = (*envp)->content;
		if(!ft_strcmp(e->name, cmd))
		{
			tmp = *envp;
			*envp = (*envp)->next;
			ft_env_del(e);
			free(tmp);
		}
		if(*envp)
			*envp = (*envp)->next;
	}
	*envp = lst;
}

void	ft_unset(t_data *data, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		unset_var(args[i], &data->envp);
		i++;
	}
}