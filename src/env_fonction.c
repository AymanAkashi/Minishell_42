/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:07:51 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/29 09:27:49 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_empty_envp(t_data *data)
{
	char	*pwd;

	data->path = ft_split(_PATH_STDPATH, ':');
	data->found_env = 0;
	pwd = getcwd(NULL, 0);
	data->envp = ft_lstnew(ft_env_new("PWD", pwd));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("OLDPWD", NULL)));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("SHLVL", "1")));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("_", "/usr/bin/env")));
}

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

void	alloc_envp(t_data *data, char *envp[], t_list *head)
{
	static int	i;
	static int	o;
	char		*tmp;
	t_env		*e;

	if (!*envp)
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
				ft_lstadd_back(&head, ft_lstnew(e));
			i++;
		}
		if (o < 2)
			check_pwd(&head);
		ft_lstadd_back(&head, NULL);
		data->envp = head;
	}
}
