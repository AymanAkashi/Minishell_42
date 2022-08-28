/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:30:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/27 15:10:43 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_env2(char *name, t_list	*lst)
{
	t_env	*e;

	if (!lst)
		return (NULL);
	while (lst)
	{
		e = lst->content;
		if (ft_strcmp(e->name, name) == 0)
			return (e);
		lst = lst->next;
	}
	return (NULL);
}

void	update_pwd(t_data *data)
{
	char	*pwd;
	t_env	*e;
	t_env	*old;

	e = search_env2("PWD", data->envp);
	pwd = getcwd(NULL, 0);
	if (ft_strcmp(pwd, e->value) != 0)
	{
		old = search_env2("OLDPWD", data->envp);
		old->value = e->value;
		e->value = pwd;
	}
}

char	*last_args(char **args)
{
	int	i;

	i = 0;
	while (args[i + 1])
		i++;
	return (args[i]);
}

void	update_underscore(t_data *data)
{
	t_env	*e;

	e = search_env2("_", data->envp);
	e->value = last_args(last_ast(data->root)->args);
}

void	update_data(t_ast *ast, t_data *data)
{
	(void)ast;
	update_pwd(data);
	update_underscore(data);
}