/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:53:27 by aaggoujj          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/20 20:03:53 by aaggoujj         ###   ########.fr       */
=======
/*   Updated: 2022/10/07 09:50:10 by aaggoujj         ###   ########.fr       */
>>>>>>> origin/update
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
=======
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

>>>>>>> origin/update
void	ft_env(t_data *data)
{
	t_env	*e;
	t_list	*lst;

	lst = data->envp;
	while (lst)
	{
		e = lst->content;
		printf("%s=%s\n", e->name, e->value);
		lst = lst->next;
	}
<<<<<<< HEAD
}
=======
}
>>>>>>> origin/update
