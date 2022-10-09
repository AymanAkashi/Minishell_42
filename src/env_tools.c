/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:33:30 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 11:11:48 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shlvl(t_data *data)
{
	int		shlvl;
	t_env	*e;
	char	*s;

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
			shlvl = 0;
		else
			shlvl++;
		s = ft_itoa(shlvl);
		free(e->value);
		e->value = ft_strdup(s);
		free(s);
	}
}

void	print_export(char *name, char *value, t_env **e, int fd)
{
	(*e)->print = 1;
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(name, fd);
	if (value && value[0] != '\0')
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(value, fd);
		ft_putstr_fd("\"\n", fd);
	}
	else
		ft_putchar_fd('\n', fd);
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

void	sort_list(t_list *lst, t_list *head, int fd)
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
		print_export(key, value, &min, fd);
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
