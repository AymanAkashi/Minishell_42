/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:59:50 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/09/18 18:50:06 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_env_path(t_list *env, char *var, size_t len)
{
    t_env	*tmp;
	t_list	*linked;

	linked = env;
    tmp = linked->content;
    while (tmp)
    {
        if (ft_strncmp(tmp->name, var, len) == 0)
            return (tmp->value);
        linked = linked->next;
    }
    return (NULL);
}

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

static int update_pwd(t_list *env)
{
	char	cwd[9999999999];
    char    *newpwd;
    t_env   *tmp;
    t_list  *linked;

    linked = env;
    tmp = ft_get_env(linked->content);
    if (getcwd(cwd, 99999999999) == NULL)
        return (0);
    if (!(newpwd = ft_strjoin("PWD", cwd)))
        return (0);
    while (env)
    {
        tmp = ft_get_env(env->next->content);
        if (ft_strcmp((char *)tmp->name, "PWD") == 0)
        {
            free(tmp->value);
            tmp->value = newpwd;
            return (1);
        }
        env = env->next;
    }
    return (0);
}

t_env *ft_get_env(void *env)
{
    t_env   *tmp;

    tmp = env;
    tmp->name = ft_strchr(env, '=');
    tmp->value = ft_strrchr(env, '=');
    return (&*tmp);
}

static int go_to_home(t_data *data)
{
    char *path;

    if (ft_update_oldpwd(data->envp) == 0)
        return (0);
    if ((path = get_env_path(data->envp, "HOME=", 5)) == NULL)
    {
        g_exitstatus = 1;
        return (printf("minishell: cd: HOME not set\n"), 0);
    }
    if (chdir(path) == -1)
    {
        g_exitstatus = 1;
        return (printf("minishell: cd: no such file or directory: %s\n", path), 0);
    }
    update_pwd(data->envp);
    return (1);
}

static int go_to_path(t_data *data,char **cmd)
{
    char *path;

    path = cmd[1];
    if (ft_update_oldpwd(data->envp) == 0)
        return (0);
    if (chdir(path) == -1)
    {
        g_exitstatus = 1;
        return (printf("minishell: cd: no such file or directory: %s\n", path), 0);
    }
    update_pwd(data->envp);
    return (1);
}

int ft_cd(t_data *data, char **cmd)
{
    if (ft_strcmp(cmd[0], "cd") || ft_strcmp(cmd[0], "CD"))
        return (1);
    g_exitstatus = 0;
    if (cmd[1])
        return (go_to_path(data, cmd));
    else
        go_to_home(data);
    return (1);
}