/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:07:51 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/27 19:18:01 by aaggoujj         ###   ########.fr       */
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
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("_","/usr/bin/env")));
}

void	alloc_envp(t_data *data, char *envp[])
{
	int i;
	t_list *head;
	char *tmp;
	t_env *e;
	int		o;

	i = 1;
	o = 0;
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
		{
			ft_env_new("OLDPWD", "");
			ft_lstadd_back(&head, ft_lstnew(e));
		}
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

char *no_print(t_list *lst)
{
	t_env *e;
	while(lst)
	{
		e = lst->content;
		if(e->print == 0)
			return (e->name);
		lst = lst->next;
	}
	return (NULL);
}

void	sort_list(t_list *lst, t_list *head)
{
	char	*key;
	char	*value;
	t_list *tmp;
	t_env	*name;
	t_env   *min;

	while(lst)
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
	sort_list(data->envp, data->envp);
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

