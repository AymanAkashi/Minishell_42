/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:40:40 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/04 21:03:40 by aaggoujj         ###   ########.fr       */
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
