/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:02:16 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/09 20:54:01 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_hidefile(char **args)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i][0] == '.')
		i++;
	if (!args[i])
		return (NULL);
	while (args[i + j])
		j++;
	dest = ft_calloc(j + 1, sizeof(char *));
	j = i;
	i = 0;
	while (args[j])
		dest[i++] = ft_strdup(args[j++]);
	dest[i] = NULL;
	free_table(args);
	return (dest);
}

char	**get_path_wildcard(char *str)
{
	char	*dest;
	char	**args;
	int		i;

	i = 0;
	dest = ft_strdup(str);
	args = ft_calloc(3, sizeof(char *));
	if (ft_strchr(dest, '/') == NULL)
	{
		args[0] = ft_strdup(".");
		args[1] = ft_strdup(dest);
		args[2] = NULL;
	}
	else
	{
		args[1] = ft_strdup(ft_strrchr(dest, '/') + 1);
		*ft_strrchr(dest, '/') = '\0';
		args[0] = ft_strdup(dest);
		args[2] = NULL;
	}
	free(dest);
	return (args);
}

char	*ft_join_sep(char *s1, char *s2, char sep)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	str = ft_calloc(sizeof(char ), ft_strlen(s1) + ft_strlen(s2) + 2);
	while (s1 && s1[++i])
		str[i] = s1[i];
	str[i++] = sep;
	j = -1;
	while (s2 && s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if (j > 0)
		free(s2);
	return (str);
}

char	**check_args(char **args)
{
	char	**tmp;
	char	**new_wild;
	int		i;

	i = 0;
	if (!args)
		return (NULL);
	new_wild = ft_calloc(size_tab(args) + 1, sizeof(char *));
	i = -1;
	while (args[++i])
	{
		if (check_wildcard(args[i]))
		{
			tmp = wild(args[i]);
			new_wild[i] = ft_revsplit(tmp, ' ');
			if (!new_wild[i] || new_wild[i][0] == '\0')
				new_wild[i] = ft_strdup(args[i]);
			free_table(tmp);
		}
		else
			new_wild[i] = ft_strdup(args[i]);
	}
	new_wild[i] = NULL;
	free_table(args);
	return (new_wild);
}

char	**wild(char *str)
{
	t_wild	v;
	int		i;

	i = 0;
	v.src = get_path_wildcard(str);
	v.dir = opendir(v.src[0]);
	if (v.dir == NULL)
		return (NULL);
	v.args = ft_calloc(size_dir(v.dir) + 1, sizeof(char *));
	closedir(v.dir);
	v.dir = opendir(v.src[0]);
	v.wild = readdir(v.dir);
	while (v.wild)
	{
		v.args[i++] = ft_strdup(v.wild->d_name);
		v.wild = readdir(v.dir);
	}
	if (ft_strcmp(v.src[1], "*") == 0)
		v.args = remove_hidefile(v.args);
	else
		v.args = wildcard_str(v.args, v.src[1]);
	free_table(v.src);
	closedir(v.dir);
	return (v.args);
}
