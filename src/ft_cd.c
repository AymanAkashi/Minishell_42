/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:59:50 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/10/11 18:50:48 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_get_env(void *env)
{
	t_env	*tmp;

	tmp = env;
	tmp->name = ft_strchr(env, '=');
	tmp->value = ft_strrchr(env, '=');
	return (&*tmp);
}

static int	go_to_home(t_data *data)
{
	char	*path;

	path = search_env("HOME", data);
	if (!path || path[0] == '\0')
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (0);
	}
	if (chdir(path) == -1)
	{
		g_exitstatus = 1;
		return (printf("%s %s\n", NO_SUCH_DIR, path), 0);
	}
	update_pwd(data, path);
	return (1);
}

void	no_dir(t_data *data)
{
	char	*pwd;
	t_env	*e;
	t_env	*old;

	e = search_env2("PWD", data->envp);
	if (e->value)
	{
		pwd = ft_strjoin(e->value, "/..");
		old = search_env2("OLDPWD", data->envp);
		old->value = ft_strdup(e->value);
		free(e->value);
		e->value = ft_strdup(pwd);
		free(pwd);
	}
}

static void	go_to_path(t_data *data, char **cmd)
{
	char	*path;
	char	*pwd;

	path = cmd[1];
	pwd = getcwd(NULL, 0);
	if ((!ft_strcmp(path, "..") || !ft_strcmp(path, ".")) && pwd == NULL)
	{
		g_exitstatus = 1;
		printf("%s\n", ft_strjoin(ERROR_CD, ERROR_CD2));
		if (chdir(path) == -1)
			print_err(NO_SUCH_DIR, path, 2);
		no_dir(data);
	}
	else if (access(path, F_OK) == -1)
	{
		free_pwd(pwd);
		return (print_err(NO_SUCH_DIR, path, 2));
	}
	if (chdir(path) == -1)
	{
		free_pwd(pwd);
		return (print_err(NO_SUCH_DIR, path, 2));
	}
	update_pwd(data, pwd);
}

int	ft_cd(t_data *data, char **cmd)
{
	g_exitstatus = 0;
	if (cmd[1])
		go_to_path(data, cmd);
	else
		return (go_to_home(data));
	return (0);
}
