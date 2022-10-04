/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:40:40 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/03 11:35:03 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_dir(DIR *dir)
{
	struct dirent	*wild;
	int				i;

	i = 0;
	wild = readdir(dir);
	while (wild)
	{
		i++;
		wild = readdir(dir);
	}
	return (i);
}

char	**add_case_alloc(char **str)
{
	char	**dest;
	int		i;

	i = 0;
	if (str == NULL)
		dest = ft_calloc(2, sizeof(char *));
	else
	{
		while (str[i])
			i++;
		dest = ft_calloc(i + 2, sizeof(char *));
		i = -1;
		while (str[++i])
			dest[i] = ft_strdup(str[i]);
		free_table(str);
	}
	return (dest);
}

int	return_check(char *str, char *src, int i, int j)
{
	if ((!str[j] && !src[i]) || (!src[i]
			&& str[ft_strlen(str) - 1] == src[i - 1]) || (!src[i] && !str[j]))
		return (1);
	if (src[i] == '*')
		return (check_str(&str[j], &src[i]));
	else if (src[i] != str[j])
		return (0);
	return (0);
}

int	check_str(char *str, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (src[i] == '*')
	{
		i++;
		while (str[j] && str[j] != src[i])
			j++;
		while (str[j] && src[i] && str[j] == src[i])
		{
			i++;
			j++;
		}
		return (return_check(str, src, i, j));
	}
	while (src[i] == str[j])
	{
		i++;
		j++;
	}
	return (return_check(str, src, i, j));
}

char	**wildcard_str(char **str, char *src)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = NULL;
	while (str[i])
	{
		if (check_str(str[i], src))
		{
			dest = add_case_alloc(dest);
			dest[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	free_table(str);
	return (dest);
}

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
	char	**args;
	int		i;

	i = 0;
	str = ft_strdup(str);
	args = ft_calloc(3, sizeof(char *));
	if (ft_strchr(str, '/') == NULL)
	{
		args[0] = ft_strdup(".");
		args[1] = ft_strdup(str);
		args[2] = NULL;
	}
	else
	{
		args[1] = ft_strdup(ft_strrchr(str, '/') + 1);
		*ft_strrchr(str, '/') = '\0';
		args[0] = ft_strdup(str);
		args[2] = NULL;
	}
	free(str);
	return (args);
}

char	*ft_revsplit(char **str, char *sep)
{
	char	*new;
	int		len;
	int		i;

	i = -1;
	len = 0;
	if (!str)
		return (NULL);
	while (str[++i])
		len += ft_strlen(str[i]) + 1;
	new = ft_calloc(len + 1, sizeof(char ));
	i = 0;
	new = ft_strdup(str[i++]);
	new = ft_strjoin(new, sep);
	while (str[i])
	{
		new = ft_strjoin(new, str[i]);
		new = ft_strjoin(new, sep);
		i++;
	}
	new[len + 1] = '\0';
	return (new);
}

char	**check_args(char **args)
{
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
			new_wild[i] = ft_revsplit(wild(args[i]), " ");
		else
			new_wild[i] = ft_strdup(args[i]);
		i++;
	}
	new_wild[i] = NULL;
	return (new_wild);
}

int	check_wildcard(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
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
	return (args);
}
