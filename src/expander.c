/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:52:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/21 13:57:16 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *str, char *buff)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	if (!str)
	{
		str = (char *) malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	if (!str)
		return (NULL);
	dest = (char *)malloc((ft_strlen(str) + ft_strlen(buff) + 1));
	if (!dest)
		return (NULL);
	if (str)
		while (str[++i] != '\0')
			dest[i] = str[i];
	if(buff)
	while (buff[++j] != '\0')
		dest[i + j] = buff[j];
	else
		j++;
	dest[i + j] = '\0';
	free(str);
	return (dest);
}

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

char *search_env(char *key, t_data *data)
{
	size_t	i;
	t_env *e;
	t_list *lst;

	lst = data->envp;
	i = 0;
	while (lst)
	{
		e = lst->content;
		if(ft_strcmp(e->name, key) == 0)
			return (ft_strdup(e->value));
		lst = lst->next;
	}
	return ("");
}

int	exporting(char **result, char *line, int pos, t_data *data)
{
	char	*key;
	char    *value;
	int		i;

	i = pos;
	while(line[i] == '$')
		i++;
	while(line[i] && line[i] != ' '&& line[i] != '\t' && line[i] != '\n'
		&& line[i] != '\"' && line[i] != '\'')
		{
			append_char(&key, line[i]);
			i++;
		}
		value = search_env(key, data);
		*result = ft_strjoin2(*result, value);
		return (i);
}

char	*expander(char *line, t_data *data)
{
	char    *result;
	int		i;
	t_state state;

	i = 0;
	state = DEFAULT;
	while(line[i])
	{
		if(line[i] == '\'')
		{
			state = SIN_QUOTHE;
			i++;
		}
		else if (line[i] == '\"')
		{
			state = DOU_QUOTHE;
			i++;
		}
		while (line[i] && state == DOU_QUOTHE)
		{
			if(line[i] == '\"')
			{
				state = DEFAULT;
				break;
			}
			if (line[i] == '$')
				i = exporting(&result, line, i, data);
			else
				append_char(&result, line[i]);
		}
		while(line[i] && state == SIN_QUOTHE)
		{
			append_char(&result, line[i]);
			if(line[i] == '\'')
				state = DEFAULT;
			i++;
		}
		if (state == DEFAULT && line[i] == '$')
			i = exporting(&result, line, i, data);
		i++;
	}

	return (result);
}

char	*check_expender(char *args, t_data *data)
{
	size_t	i;

	i = 0;
	while(args[i] && !is_token(args[i]))
	{
		if(args[i] == '$')
		{
			args[i] = expander(args[i], data);
			break;
		}
		i++;
	}
}