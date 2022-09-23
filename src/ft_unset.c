/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:19:07 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/23 18:41:04 by yjarhbou         ###   ########.fr       */
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
			free(((t_env *)tmp->content)->value);
			return ;
		}
		tmp = tmp->next;
	}
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
		i++;
	}
}
