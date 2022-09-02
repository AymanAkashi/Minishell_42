/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:52:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/28 21:59:29 by yjarhbou         ###   ########.fr       */
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
	while (buff[++j] != '\0')
		dest[i + j] = buff[j];
	dest[i + j] = '\0';
	free(str);
	return (dest);
}

char	*search_env(char *key, t_data *data)
{
	t_env	*e;
	t_list	*lst;

	lst = data->envp;
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
	key = NULL;
	while (line[i] == '$')
		i++;
	while (line[i] && line[i] != ' '&& line[i] != '\t' && line[i] != '\n'
		&& line[i] != '\"' && line[i] != '\'' && line[i] != '$')
			append_char(&key, line[i++]);
		value = search_env(key, data);
		*result = ft_strjoin2(*result, value);
		if(value && value[0] != '\0')
		free(value);
		free(key);
		return (i);
}

int	expand_dou_quote(char *line, int i, t_state *state,
	char ** result, t_data *data)
{
	while (line[i] && *state == DOU_QUOTHE)
	{
		if(line[i] == '\"')
		{
			*state = check_state(line[i+1]);
			i++;
			break;
		}
		if (line[i] == '$')
			i = exporting(result, line, i, data);
		else
			append_char(result, line[i++]);
	}
	return (i);
}

int	expand_sin_quote(char *line, int i, t_state *state, char **result)
{
	while (line[i] && *state == SIN_QUOTHE)
	{
		if (line[i] == '\'')
		{
			*state = check_state(line[i+1]);
			i++;
			break;
		}
		append_char(result, line[i]);
		i++;
	}
	return (i);
}

char	*expander(char *line, t_data *data)
{
	char	*result;
	int		i;
	t_state	state;

	i = 0;
	state = DEFAULT;
	result = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			state = check_state(line[i++]);
		if (line[i] && state == DOU_QUOTHE)
			i = expand_dou_quote(line, i, &state, &result, data);
		else if(line[i] && state == SIN_QUOTHE)
			i = expand_sin_quote(line, i, &state, &result);
		if (state == DEFAULT && line[i] == '$')
			i = exporting(&result, line, i, data);
		else if (line[i] && state == DEFAULT)
			append_char(&result, line[i++]);
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
			args = expander(args, data);
			break;
		}
		i++;
	}
	return (args);
}