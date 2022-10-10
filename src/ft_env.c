/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:53:27 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/10 14:02:06 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_path(t_data *data, char *value, int add)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	if (add == 0)
	{
		free_table(data->path);
		data->path = ft_split(value, ':');
	}
	else
	{
		tmp = ft_split(value, ':');
		if (!tmp)
		{
			free_table(data->path);
			data->path = NULL;
		}
		i = -1;
		while (tmp[++i])
			data->path = d_alloc_tabs(data->path, tmp[i]);
		free_table(tmp);
	}
}

void	ft_env(t_data *data, int fd)
{
	t_env	*e;
	t_list	*lst;

	lst = data->envp;
	while (lst)
	{
		e = lst->content;
		if (!e->value || e->value[0] == '\0')
			lst = lst->next;
		else
		{
			ft_putstr_fd(e->name, fd);
			ft_putchar_fd('=', fd);
			ft_putstr_fd(e->value, fd);
			ft_putchar_fd('\n', fd);
			lst = lst->next;
		}
	}
	g_exitstatus = 0;
}
