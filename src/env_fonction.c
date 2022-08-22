/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:07:51 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/22 19:01:04 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void	append_char(char **line, char c)
// {
// 	char	*dest;
// 	int		i;

// 	i = 0;
// 	if (*line == NULL)
// 		*line = ft_any_alloc(sizeof(char), 2);
// 	dest = ft_any_alloc(sizeof(char), ft_strlen(*line) + 2);
// 	while ((*line)[i])
// 	{
// 		dest[i] = (*line)[i];
// 		i++;
// 	}
// 	dest[i] = c;
// 	dest[i + 1] = '\0';
// 	free(*line);
// 	*line = dest;
// }

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
	t_env *e;

	i = 1;
	if (!*envp)
		alloc_empty_envp(data);
	else
	{
		tmp = ft_strchr(envp[0], '=') + 1;
		*ft_strchr(envp[0], '=') = '\0';
		e = ft_env_new(envp[0], tmp);
		data->envp = ft_lstnew(e);
		head = data->envp;
		while (envp[i])
		{
			tmp = ft_strchr(envp[i], '=') + 1;
			*ft_strchr(envp[i], '=') = '\0';
			e = ft_env_new(envp[i], tmp);
			ft_lstadd_back(&head, ft_lstnew(e));
			i++;
		}
			// free(tmp);
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

