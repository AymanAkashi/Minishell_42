/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:30:39 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/22 12:28:39 by aaggoujj         ###   ########.fr       */
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
		if(e->value == NULL)
			old->value = NULL;
		else
			old->value = e->value;
		if (pwd == NULL)
			e->value = ft_strjoin(e->value, "/..");
		else
			e->value = pwd;
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

void	update_underscore(t_data *data, char **args)
{
	t_env	*e;
	if(!ft_strcmp(last_args(args), "$_"))
		return ;
	e = search_env2("_", data->envp);
	if (e)
	{
		if(e->value)
			free(e->value);
		e->value = ft_strdup(last_args(args));
	}
}
