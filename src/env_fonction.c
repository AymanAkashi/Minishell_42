/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:07:51 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/25 20:23:18 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shlvl(t_data *data)
{
	int		shlvl;
	t_env	*e;

	e = search_env2("SHLVL", data->envp);
	if (!e)
		return ;
	shlvl = ft_atoi(e->value);
	if (data->found_env == 0)
		e->value = ft_strdup("1");
	else
	{
		if (shlvl < 0)
			shlvl = 1;
		else
			shlvl++;
		e->value = ft_strdup(ft_itoa(shlvl));
	}
}

void	add_path(t_data *data)
{
	data->path = ft_split(search_env("PATH", data), ':');
	if (!data->path)
		perror(*data->path);
}

void	alloc_empty_envp(t_data *data)
{
	char	*pwd;

	data->path = ft_split(ft_strdup(_PATH_STDPATH), ':');
	// for (int i = 0; data->path[i]; i++)
	// 	printf("%s\n", data->path[i]);
	data->found_env = 0;
	pwd = getcwd(NULL, 0);
	data->envp = ft_lstnew(ft_env_new("PWD", pwd));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("OLDPWD", NULL)));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("SHLVL", "1")));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("_", "/usr/bin/env")));
}

void	add_oldpwd(t_env *e, t_list **lst)
{
	ft_env_new("OLDPWD", "");
	ft_lstadd_back(lst, ft_lstnew(e));
}

void	alloc_envp(t_data *data, char *envp[], t_list *head)
{
	int		i;
	int		o;
	char	*tmp;
	t_env	*e;

	i = 0;
	o = 0;
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
			if (!ft_strcmp(envp[i], "OLDPWD"))
			{
				e = ft_env_new(envp[i], "");
				o = 1;
			}
			else
				e = ft_env_new(envp[i], tmp);
			ft_lstadd_back(&head, ft_lstnew(e));
			i++;
		}
		if (!o)
			add_oldpwd(e, &head);
		ft_lstadd_back(&head, NULL);
		data->envp = head;
	}
}

void	print_export(char *name, char *value, t_env **e)
{
	(*e)->print = 1;
	printf("declare -x %s", name);
	if (value && value[0] != '\0')
		printf("=\"%s\"\n", value);
	else
		printf("\n");
}

char	*no_print(t_list *lst)
{
	t_env	*e;

	while (lst)
	{
		e = lst->content;
		if (e->print == 0)
			return (e->name);
		lst = lst->next;
	}
	return (NULL);
}

void	sort_list(t_list *lst, t_list *head)
{
	char	*key;
	char	*value;
	t_list	*tmp;
	t_env	*name;
	t_env	*min;

	while (lst)
	{
		tmp = head;
		name = tmp->content;
		key = no_print(tmp);
		while (tmp)
		{
			name = tmp->content;
			if (ft_strcmp(key, name->name) >= 0 && name->print == 0)
			{
				min = name;
				key = name->name;
				value = name->value;
			}
			tmp = tmp->next;
		}
		print_export(key, value, &min);
		lst = lst->next;
	}
}

t_list	*ft_lstcopy(t_list *lst)
{
	t_list	*new;

	new = ft_lstnew(lst->content);
	lst = lst->next;
	new->next = malloc(sizeof(t_list) * 1);
	new = new->next;
	while (lst)
	{
		new->content = lst->content;
		lst = lst->next;
		if (lst)
		{
			new->next = malloc(sizeof(t_list) * 1);
			new = new->next;
		}
	}
	return (new);
}

void	ft_export_new(t_data *data)
{
	sort_list(data->envp, data->envp);
}

t_env	*ft_env_new(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	return (new);
}
