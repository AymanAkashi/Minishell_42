/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:19:07 by aaggoujj          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/21 14:38:13 by aaggoujj         ###   ########.fr       */
=======
/*   Updated: 2022/10/06 18:39:33 by aaggoujj         ###   ########.fr       */
>>>>>>> origin/update
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_var(t_list **lst, char *cmd)
{
	t_list	*tmp;
	t_list	*prev;
<<<<<<< HEAD
=======
	t_env	*e;
>>>>>>> origin/update

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
<<<<<<< HEAD
			free(((t_env *)tmp->content)->name);
			free(((t_env *)tmp->content)->value);
			free(tmp->content);
			free(tmp);
=======
			e = tmp->content;
			free_null((void **)&e->name);
			free_null((void **)&e->value);
			free_null((void **)&e);
			free_null((void **)&tmp);
>>>>>>> origin/update
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
<<<<<<< HEAD
			*lst = tmp->next;
			free(((t_env *)tmp->content)->value);
=======
			free_null((void **)&((t_env *)tmp->content)->value);
>>>>>>> origin/update
			return ;
		}
		tmp = tmp->next;
	}
}

<<<<<<< HEAD

void	ft_unset(t_data *data, char **args)
{
	int i;
=======
void	remove_path(t_data *data)
{
	free_table(data->path);
	data->path = NULL;
}

void	ft_unset(t_data *data, char **args)
{
	int	i;
>>>>>>> origin/update

	i = 1;
	while (args[i])
	{
		if (!ft_strcmp(args[i], "PWD") || !ft_strcmp(args[i], "OLDPWD"))
			remove_content(&data->envp, args[i]);
<<<<<<< HEAD
=======
		else if (!ft_strcmp(args[i], "PATH"))
			remove_path(data);
>>>>>>> origin/update
		else
			remove_var(&data->envp, args[i]);
		i++;
	}
<<<<<<< HEAD
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
=======
}
>>>>>>> origin/update
