/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:52:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/20 23:42:18 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_exp(char *line)
{
	size_t	i;

	i = 0;
	if(line[i] == '\"')
		return (1);
	while(line[i] == '\'')
		i++;
	if(i % 2 == 0)
		return (0);
	else
		return (1);
}

char	exporting_line(char *line, char *key, t_data *data, int i)
{
	t_env	*env;
	t_list	*lst;
	char 	*new;

	lst = data->envp;
	while (lst)
	{
		env = lst->content;
		if(!ft_strcmp(env->name, key))
		{
			new = ft_strjoin(ft_substr(line, 0, i),env->value);
			break;
		}
		data->envp = data->envp->next;
	}
	return (new);
}

char	*expander(char *line, t_data *data,int i)
{
	char	*dest;
	size_t		j;

	j = 0;
	while(line[i] == '$')
		i++;
	while(line[i + j] && line[i + j] != '$')
		j++;
	dest = ft_any_alloc(sizeof(char), j + 1);
	j = -1;
	while(line[i + ++j] && line[i + j] != '$')
		dest[j] = line[i + j];
	dest[j] = '\0';
	exporting_line(line, dest, data, i);
}

void	check_expender(char **args, t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while(args[i][j] && !is_token(args[i]))
		{
			if(args[i][j] == '$')
				expander(&args[i], data, j);
			j++;
		}
		i++;
	}
}