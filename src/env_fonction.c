/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:07:51 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 18:08:33 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_to_env(t_list **head, char *str, int *o)
{
	char	*path;
	t_env	*e;

	if (str[0] == 'O')
	{
		e = ft_env_new(str, "");
		ft_lstadd_back(head, ft_lstnew(e));
		(*o)++;
	}
	else
	{
		(*o)++;
		path = getcwd(NULL, 0);
		e = ft_env_new(str, path);
		ft_lstadd_back(head, ft_lstnew(e));
		free(path);
	}
}

void	check_pwd(t_list **lst)
{
	t_env	*e;
	char	*pwd;

	e = search_env2("PWD", *lst);
	if (e == NULL)
	{
		pwd = getcwd(NULL, 0);
		e = ft_env_new("PWD", pwd);
		ft_lstadd_back(lst, ft_lstnew(e));
	}
	e = search_env2("OLDPWD", *lst);
	if (e == NULL)
	{
		e = ft_env_new("OLDPWD", NULL);
		ft_lstadd_back(lst, ft_lstnew(e));
	}
}

t_env	*creat_env(t_list **lst, char *tmp, int *o, char *envp)
{
	t_env	*e;

	e = NULL;
	if (!ft_strcmp(envp, "OLDPWD") || !ft_strcmp(envp, "PWD"))
		return (path_to_env(lst, envp, o), NULL);
	else
		e = ft_env_new(envp, tmp);
	return (e);
}

void	add_back_envp(t_env *e, t_list **head)
{
	t_list	*lst;

	lst = ft_lstnew(e);
	ft_lstadd_back(head, lst);
}

void	alloc_envp(t_data *data, char *envp[], t_list *head)
{
	static int	i;
	static int	o;
	char		*tmp;
	t_env		*e;

	if (!envp || !(*envp) || check_envp(envp) == 0)
		alloc_empty_envp(data);
	else
	{
		data->found_env = 1;
		head = NULL;
		while (envp[i])
		{
			tmp = ft_strchr(envp[i], '=') + 1;
			*ft_strchr(envp[i], '=') = '\0';
			e = creat_env(&head, tmp, &o, envp[i]);
			if (e)
				add_back_envp(e, &head);
			i++;
		}
		if (o < 2)
			check_pwd(&head);
		ft_lstadd_back(&head, NULL);
		data->envp = head;
	}
}
