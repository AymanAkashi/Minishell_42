/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 04:39:31 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/09/02 17:23:44 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_char_instring(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(t_data *data, char **cmds)
{
	t_list	*tmp;

	tmp = data->envp;
	if (cmds[1])
	{
		printf("env: %s: No such file or directory\n", cmds[1]);
		//g_var.exit_status = 127;
		return (1);
	}
	//g_var.exit_status = 0;
	while (!(cmds[1]) && tmp)
	{
		if (ft_is_char_instring(tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}


// void	ft_env(t_data *data)
// {
// 	data->export = ft_any_alloc(sizeof(t_list), 1);
// 	sort_list(data->envp, &data->export);
// 	//***********************export**************************//
// 	t_env *e;
// 	t_list *lst;
// 	lst = data->export;
// 	for (int i = 0;data->export; i++)
// 	{
// 		e = data->export->content;
// 		printf("%s=%s\n", e->name, e->value);
// 		data->export = data->export->next;
// 	}
// 	data->export = lst  ;
// 	//************************ *****************************//
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