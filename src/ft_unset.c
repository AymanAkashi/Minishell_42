/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:19:07 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/22 10:17:44 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_var(t_list **lst, char *cmd)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->content)->name, cmd) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = tmp->next;
			free(((t_env *)tmp->content)->name);
			free(((t_env *)tmp->content)->value);
			free(tmp->content);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	remove_content(t_list **lst, char *cmd)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->content)->name, cmd) == 0)
		{
			// *lst = tmp->next;
			free(((t_env *)tmp->content)->value);
			return ;
		}
		tmp = tmp->next;
	}
}


void	ft_unset(t_data *data, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "PWD") || !ft_strcmp(args[i], "OLDPWD"))
			remove_content(&data->envp, args[i]);
		else
			remove_var(&data->envp, args[i]);
		i++;
	}
	// t_env 	*e;
	// t_list *lst;
	// lst = data->envp;
	// while (lst)
	// {
	// 	e = lst->content;
	// 	printf("[%s]-->[%s]\n", e->name, e->value);
	// 	lst = lst->next;
	// }
}