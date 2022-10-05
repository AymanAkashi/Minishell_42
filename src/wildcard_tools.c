/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:02:16 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/05 18:46:59 by aaggoujj         ###   ########.fr       */
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

char	*ft_revsplit(char **str, char sep)
{
	char	*new;
	int		len;
	int		i;

	i = -1;
	len = 0;
	new = NULL;
	if (!str)
		return (NULL);
	while (str[++i])
		new = ft_join_sep(str[i], new, sep);
	return (new);
}

char	**check_args(char **args)
{
	char	**tmp;
	char	**new_wild;
	int		i;

	i = 0;
	if (!args)
		return (NULL);
	while (args[i])
		i++;
	new_wild = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (args[i])
	{
		if (check_wildcard(args[i]))
		{
			tmp = wild(args[i]);
			new_wild[i] = ft_revsplit(tmp, ' ');
			free_table(tmp);
		}
		else
			new_wild[i] = ft_strdup(args[i]);
		i++;
	}
	new_wild[i] = NULL;
	free_table(args);
	return (new_wild);
}

char	**wild(char *str)
{
	char			**args;
	char			**src;
	DIR				*dir;
	struct dirent	*wild;
	int				i;

	i = 0;
	src = get_path_wildcard(str);
	dir = opendir(src[0]);
	if (dir == NULL)
		return (NULL);
	args = ft_calloc(size_dir(dir) + 1, sizeof(char *));
	closedir(dir);
	dir = opendir(src[0]);
	wild = readdir(dir);
	while (wild)
	{
		args[i++] = ft_strdup(wild->d_name);
		wild = readdir(dir);
	}
	if (ft_strcmp(src[1], "*") == 0)
		args = remove_hidefile(args);
	else
		args = wildcard_str(args, src[1]);
	free_table(src);
	closedir(dir);
	return (args);
}
