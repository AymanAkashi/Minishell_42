/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:33:30 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/02 14:38:00 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shlvl(t_data *data)
{
	int		shlvl;
	t_env	*e;

	e = search_env2("SHLVL", data->envp);
	if (!e)
	{
		ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("SHLVL", "1")));
		return ;
	}
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
