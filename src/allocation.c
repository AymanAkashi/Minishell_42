/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:39:29 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/04 20:56:35 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_empty_envp(t_data *data)
{
	char	*pwd;

	data->path = ft_split(_PATH_STDPATH, ':');
	data->found_env = 0;
	pwd = getcwd(NULL, 0);
	data->envp = ft_lstnew(ft_env_new("PWD", pwd));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("OLDPWD", NULL)));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("SHLVL", "1")));
	ft_lstadd_back(&data->envp, ft_lstnew(ft_env_new("_", "/usr/bin/env")));
}

char	**d_alloc_tabs(char **args, char *str)
{
	char	**d_table;
	int		i;

	i = 0;
	if (!args || !args[i])
	{
		d_table = ft_calloc(sizeof(char *), 2);
		d_table[0] = ft_strdup(str);
		d_table[1] = NULL;
		return (d_table);
	}
	while (args[i])
		i++;
	d_table = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (args[++i])
		d_table[i] = ft_strdup(args[i]);
	d_table[i++] = ft_strdup(str);
	d_table[i] = NULL;
	free_table(args);
	args = NULL;
	return (d_table);
}

void	*ft_any_alloc(size_t size, size_t len)
{
	void	*ptr;

	ptr = malloc(size * len);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size * len);
	return (ptr);
}

char	*ft_alloc_cmd(char *str, char *str2)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	i = -1;
	if (!str)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(str2) + 2;
	dest = ft_any_alloc(sizeof(char), len);
	while (str[++i])
		dest[i] = str[i];
	j = -1;
	dest[i++] = ' ';
	if (str2)
		while (str2[++j])
			dest[j + 1] = str2[j];
	dest[j + i] = '\0';
	return (dest);
}

void	alloc_token(t_token **token)
{
	(*token)->next = ft_any_alloc(sizeof(t_token), 1);
	(*token) = (*token)->next;
}
