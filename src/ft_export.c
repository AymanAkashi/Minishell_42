/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:49:59 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/10 14:01:14 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_export(t_data *data, char *key, char *value, int add)
{
	t_env	*e;

	if (!ft_strcmp("PATH", key) && value)
		export_path(data, value, add);
	e = search_env2(key, data->envp);
	if (e == NULL)
		ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new(key, value)));
	else if (add == 0)
	{
		if (!value)
			return ;
		free(e->value);
		e->value = ft_strdup(value);
	}
	else
	{
		if (e->value == NULL)
			e->value = ft_strdup(value);
		else
			e->value = ft_strjoin2(e->value, value);
	}
	g_exitstatus = 0;
}

void	add_export_var(t_data *data, char *cmd)
{
	int		i;
	char	*pwd;

	i = 0;
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+' && ft_isalpha(cmd[i]))
		i++;
	if (!cmd[i])
		search_export(data, cmd, NULL, 0);
	else if (!ft_isalpha(cmd[i]) && cmd[i] != '=' && cmd[i] != '+')
		print_err("minishell : export: `%s': not a valid identifier\n", cmd, 2);
	else if (cmd[i] == '=')
		creat_export_var(data, cmd);
	else if (cmd[i] == '+' && cmd[i + 1] == '=')
	{
		pwd = ft_strchr(cmd, '+') + 2;
		*ft_strchr(cmd, '+') = '\0';
		search_export(data, cmd, pwd, 1);
	}
	else if (cmd[i] == '+' && cmd[i + 1] != '=')
		print_err("minishell: export: `%s': not a valid identifier\n", cmd, 2);
}

void	creat_export_var(t_data *data, char *cmd)
{
	int		i;
	char	*pwd;

	i = 0;
	while (cmd[i] && cmd[i] != '=' && cmd[i] != '+' && ft_isalpha(cmd[i]))
		i++;
	if (!cmd[i])
		search_export(data, cmd, NULL, 0);
	else if (cmd[i] != '=' && cmd[i] != '+' && !ft_isalpha(cmd[i]))
		print_err("minishell : export: `%s': not a valid identifier\n", cmd, 2);
	else if (cmd[i] == '=')
	{
		pwd = ft_strchr(cmd, '=') + 1;
		*ft_strchr(cmd, '=') = '\0';
		search_export(data, cmd, pwd, 0);
	}
}

char	*check_expend_export(char *args, t_data *data)
{
	size_t	i;

	i = 0;
	while (args[i] && !is_token(args[i]))
	{
		while (args[i] == '$' && args[i + 1] == '$')
			i++;
		if ((args[i] == '$' || args[i] == '\'' || args[i] == '\"'))
		{
			args = expander(args, data);
			break ;
		}
		i++;
	}
	return (args);
}

void	ft_export(t_data *data, char **cmd, int fd)
{
	int		i;

	i = 1;
	if (cmd[1] == NULL)
	{
		sort_list(data->envp, data->envp, fd);
		g_exitstatus = 0;
	}
	else
	{
		while (cmd[i])
		{
			if (ft_strchr(cmd[i], '+') == NULL)
				creat_export_var(data, cmd[i]);
			else
				add_export_var(data, cmd[i]);
			i++;
		}
	}
}
