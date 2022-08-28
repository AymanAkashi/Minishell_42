/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:01:53 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/28 20:30:26 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(t_data *data, char **cmd)
{
	int i;

	i = 0
	if (ft_strcmp(cmd[0], "export"))
		return 1;
	if (!cmd[1] || is_valid(cmd[1], "+="))
		return (1);
	return (0);
}

int is_valid(char *str, char *array)
{
	int	i;
	int	j;
//	*********************
	i = -1;
	j = -1;
	while (str[++i])
	{
		if(!ft_isdigit(str[i]))
			return 1;
		if (!if_ischar(str[i]))
			return 1;
		while (array[++j] && )
		{
			if (array[j] != str[i]) 
			return (1);
		}
	}
	return 0;
}

void show_exp(t_data *data)
{
	data->export = ft_any_alloc(sizeof(t_list), 1);
	sort_list(data->envp, &data->export);
	//***********************export**************************//
	t_env *e;
	t_list *lst;
	lst = data->export;
	for (int i = 0;data->export; i++)
	{
		e = data->export->content;
		printf("declare -x \"%s=%s\"\n", e->name, e->value);
		data->export = data->export->next;
	}
	data->export = lst  ;
	//************************ *****************************//
}


void  ft_add_first(t_env **env, t_env itm)
{
	if (env)
	{
		if (*env)
			itm->next = *env;
		*env = itm;
	}
}


// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	if (lst)
// 	{
// 		if (*lst)
// 			new -> next = *lst;
// 		*lst = new;
// 	}
// }

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