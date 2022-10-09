/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:19:07 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/07 11:28:18 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_var(t_list **lst, char *cmd)
{
	t_list	*tmp;
	t_list	*prev;
	t_env	*e;

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
			e = tmp->content;
			free_null((void **)&e->name);
			free_null((void **)&e->value);
			free_null((void **)&e);
			free_null((void **)&tmp);
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
			free(((t_env *)tmp->content)->value);
			((t_env *)tmp->content)->value = ft_strdup("");
			return ;
		}
		tmp = tmp->next;
	}
}

void	remove_path(t_data *data)
{
	free_table(data->path);
	data->path = NULL;
}

void	ft_unset(t_data *data, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "PWD") || !ft_strcmp(args[i], "OLDPWD"))
			remove_content(&data->envp, args[i]);
		else
			remove_var(&data->envp, args[i]);
		if (!ft_strcmp(args[i], "PATH"))
			remove_path(data);
		i++;
	}
}
