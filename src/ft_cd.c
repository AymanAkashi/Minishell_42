/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:59:50 by yjarhbou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/21 17:00:21 by aaggoujj         ###   ########.fr       */
=======
/*   Updated: 2022/10/07 09:17:44 by aaggoujj         ###   ########.fr       */
>>>>>>> origin/update
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

<<<<<<< HEAD
// static char *get_env_path(t_list *env, char *var, size_t len)
// {
//     t_env	*tmp;
// 	t_list	*linked;

// 	linked = env;
//     tmp = linked->content;
//     while (tmp)
//     {
//         if (ft_strncmp(tmp->name, var, len) == 0)
//             return (tmp->value);
//         linked = linked->next;
//     }
//     return (NULL);
// }

int ft_update_oldpwd(t_list *env)
{
	char    cwd[99999999999];
	char    *oldpwd;
	t_env   *tmp;
	t_list   *new;
	t_list  *linked;

	linked = env;
	tmp = env->content;
	if (getcwd(cwd, 99999999999999) == NULL)
		return (0);
	if (!(oldpwd = ft_strjoin("OLDPWD", cwd)))
		return (0);
	while (linked)
	{
		tmp = linked->content;
		if (ft_strcmp((char *)tmp->name, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = oldpwd;
			return (1);
		}
		linked = linked->next;
	}
	new = ft_lstnew(oldpwd);
	ft_lstadd_back(&env, new);
	return (0);
}

// static int update_pwd(t_list *env)
// {
// 	char	cwd[9999999999];
//     char    *newpwd;
//     t_env   *tmp;
//     t_list  *linked;

//     linked = env;
//     tmp = ft_get_env(linked->content);
//     if (getcwd(cwd, 99999999999) == NULL)
//         return (0);
//     if (!(newpwd = ft_strjoin("PWD", cwd)))
//         return (0);
//     while (env)
//     {
//         tmp = ft_get_env(env->next->content);
//         if (ft_strcmp((char *)tmp->name, "PWD") == 0)
//         {
//             free(tmp->value);
//             tmp->value = newpwd;
//             return (1);
//         }
//         env = env->next;
//     }
//     return (0);
// }

t_env *ft_get_env(void *env)
{
	t_env   *tmp;
=======
t_env	*ft_get_env(void *env)
{
	t_env	*tmp;
>>>>>>> origin/update

	tmp = env;
	tmp->name = ft_strchr(env, '=');
	tmp->value = ft_strrchr(env, '=');
	return (&*tmp);
}

<<<<<<< HEAD
static int go_to_home(t_data *data)
{
	char   *path;

	// if (ft_update_oldpwd(data->envp) == 0)
	//     return (0);
	path = search_env("HOME",data);
=======
static int	go_to_home(t_data *data)
{
	char	*path;

	path = search_env("HOME", data);
>>>>>>> origin/update
	if (path[0] == '\0')
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (0);
	}
	if (chdir(path) == -1)
	{
		g_exitstatus = 1;
<<<<<<< HEAD
		return (printf("minishell: cd: no such file or directory: %s\n", path), 0);
	}
	update_pwd(data);
	return (1);
}

void    no_dir(t_data   *data)
=======
		return (printf("%s %s\n", NO_SUCH_DIR, path), 0);
	}
	update_pwd(data, path);
	return (1);
}

void	no_dir(t_data *data)
>>>>>>> origin/update
{
	char	*pwd;
	t_env	*e;
	t_env	*old;

	e = search_env2("PWD", data->envp);
<<<<<<< HEAD
	pwd = ft_strjoin(e->value, "/..");
	if (ft_strcmp(pwd, e->value) != 0)
	{
=======
	if (e->value)
	{
		pwd = ft_strjoin(e->value, "/..");
>>>>>>> origin/update
		old = search_env2("OLDPWD", data->envp);
		old->value = e->value;
		e->value = pwd;
	}
}

<<<<<<< HEAD
static int go_to_path(t_data *data,char **cmd)
{
	char *path;
	char *pwd;

	path = cmd[1];
	pwd = getcwd(NULL,0);
	if(!ft_strcmp(path, "..") && pwd == NULL)
	{
		g_exitstatus = 1;
		printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		if (chdir(path) == -1)
			return (printf("minishell: cd: no such file or directory: %s\n", path), 0);
		no_dir(data);
		return 0;
	}
	else if (access(path, F_OK) == -1)
	{
		g_exitstatus = 1;
		return (printf("minishell: cd: no such file or directory: %s\n", path), 0);
	}
	// if (ft_update_oldpwd(data->envp) == 0)
	//     return (0);
	if (chdir(path) == -1)
	{
		g_exitstatus = 1;
		return (printf("minishell: cd: no such file or directory: %s\n", path), 0);
	}
	update_pwd(data);
	return (1);
}

int ft_cd(t_data *data, char **cmd)
{
	// if (ft_strcmp(cmd[0], "cd") || ft_strcmp(cmd[0], "CD"))
	//     return (1);
	g_exitstatus = 0;
	if (cmd[1])
		return (go_to_path(data, cmd));
	else
		return (go_to_home(data));
}
=======
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
>>>>>>> origin/update
