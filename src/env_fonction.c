/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashi <akashi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:07:51 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/19 20:51:43 by akashi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_empty_envp(t_data *data)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	data->envp = ft_lstnew(ft_env_new("PWD",pwd));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("OLDPWD",NULL)));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("SHLVL","1")));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("_",ft_strjoin(pwd, "/minishell"))));
}
void	alloc_envp(t_data *data, char *envp[])
{
	int i;
	t_list *head;
	char *tmp;

	i = 1;
	if (!*envp)
		alloc_empty_envp(data);
	else
	{
		tmp = ft_strchr(envp[0], '=') + 1;
		*ft_strchr(envp[0], '=') = '\0';
		data->envp = ft_lstnew(ft_env_new(ft_strdup(envp[0]), tmp));
		head = data->envp;
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "OLDPWD",6) == 0)
				i++;
			tmp = ft_strchr(envp[i], '=') + 1;
			*ft_strchr(envp[i], '=') = '\0';
			ft_lstadd_back(&head, ft_lstnew(ft_env_new(ft_strdup(envp[i]), tmp)));
			i++;
		}
		ft_lstadd_back(&head, NULL);
		data->envp = head;
	}
}

void	sort_list(t_list *lst, t_list **lst2)
{
	t_list *tmp;
	t_env	*name;
	t_env	*name2;

	(*lst2) = lst;
	tmp = lst->next;
	while(lst)
	{
		tmp = lst->next;
		while (tmp)
		{
			name = lst->content;
			name2 = tmp->content;
			if (ft_strcmp(name->name, name2->name) > 0)
			{
				tmp->content = name;
				lst->content = name2;
			}
			tmp = tmp->next;
		}
		lst = lst->next;
	}
}

t_list	*ft_lstcopy(t_list *lst)
{
	t_list *new;

	new = ft_lstnew(lst->content);
	lst = lst->next;
	new->next = malloc(sizeof(t_list) * 1);
	new = new->next;
	while(lst)
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
	data->export = ft_any_alloc(sizeof(t_list), 1);
	sort_list(data->envp, &data->export);
	//***********************export**************************//
	// t_env *e;
	// t_list *lst;
	// lst = data->export;
	// for (int i = 0;data->export; i++)
	// {
	// 	e = data->export->content;
	// 	printf("[name]%s === [value]%s\n", e->name, e->value);
	// 	data->export = data->export->next;
	// }
	// data->export = lst  ;
	//************************ *****************************//
}

t_env	*ft_env_new(char *name, char *value)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	return (new);
}

void	ft_env_del(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	free(env->value);
	free(env);
}