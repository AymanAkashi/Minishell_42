/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:49:59 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/20 18:22:49 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_export(t_data *data, char *key, char *value, int add)
{
	t_env	*e;
	char	*tmp;

	e = search_env2(key, data->envp);
	if(add == 0)
	{
		if (e == NULL)
			ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new(key, value)));
		else
		{
			free(e->value);
			e->value = ft_strdup(value);
		}
	}
	else
	{
		if (e == NULL)
			ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new(key, value)));
		else
		{
			tmp = e->value;
			e->value = ft_strjoin(e->value, value);
			free(tmp);
		}
	}
}

void	add_export_var(t_data *data, char *cmd)
{
	int	i;
	char	*pwd;

	i = 0;
	while(cmd[i] && cmd[i] != '=' && cmd[i] != '+' && ft_isalpha(cmd[i]))
		i++;
	if (!cmd[i])
		search_export(data, cmd, NULL, 0);
	else if (!ft_isalpha(cmd[i]) && cmd[i] != '=' && cmd[i] != '+')
		print_err("minishell : export: `%s': not a valid identifier\n", cmd, 2);
	else if(cmd[i] == '=')
		creat_export_var(data, cmd);
	else if (cmd[i] == '+' && cmd[i + 1] == '=')
	{
		pwd	= ft_strchr(cmd, '+') + 2;
		*ft_strchr(cmd, '+') = '\0';
		search_export(data, cmd, pwd, 1);
	}
	else if (cmd[i] == '+' && cmd[i + 1] != '=')
		print_err("minishell: export: `%s': not a valid identifier\n", cmd, 2);
}

void	creat_export_var(t_data *data, char *cmd)
{
	int i;
	char *pwd;

	i = 0;
	while(cmd[i] && cmd[i] != '=' && cmd[i] != '+' && ft_isalpha(cmd[i]))
		i++;
	if (!cmd[i])
		search_export(data, cmd, NULL, 0);
	else if(cmd[i] != '=' && cmd[i] != '+' && !ft_isalpha(cmd[i]))
		print_err("minishell : export: `%s': not a valid identifier\n", cmd, 2);
	else if (cmd[i] == '=')
	{
		pwd	= ft_strchr(cmd, '=') + 1;
		*ft_strchr(cmd, '=') = '\0';
		search_export(data, cmd, pwd, 0);
	}
}

void	ft_export(t_data *data, char **cmd)
{
	int		i;

	i = 1;
	if(cmd[1] == NULL)
	{
		ft_export_new(data);
		return ;
	}
	else
	{
		while (cmd[i])
		{
			if(ft_strchr(cmd[i], '+') == NULL)
				creat_export_var(data, cmd[i]);
			else
				add_export_var(data, cmd[i]);
			i++;
		}
	}
}