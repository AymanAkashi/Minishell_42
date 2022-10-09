/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:52:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/07 11:20:17 by aaggoujj         ###   ########.fr       */
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
	while (str && str[++i] != '\0')
		dest[i] = str[i];
	while (buff && buff[++j] != '\0')
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
		if (ft_strcmp(e->name, key) == 0)
			return (ft_strdup(e->value));
		lst = lst->next;
	}
	return ("");
}

int	exporting(char **result, char *line, int i, t_data *data)
{
	char	*key;
	char	*value;

	key = NULL;
	while (line[i] == '$' && (line[i +1] == '$' || !type_caracter(line[i +1])))
		append_char(result, line[i++]);
	if (line[i] == '$')
		i++;
	if (line[i] == '?')
	{
		i += add_exitstatue(result);
		return (i);
	}
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
		&& line[i] != '\"' && line[i] != '\'' && line[i] != '$'
		&& (ft_isalpha(line[i]) || line[i] == '_'))
		append_char(&key, line[i++]);
	value = search_env(key, data);
	*result = ft_strjoin2(*result, value);
	if (value != NULL && value[0] != '\0')
		free(value);
	free(key);
	return (i);
}

char	*expander(char *line, t_data *data)
{
	char	*result;
	int		i;

	i = 0;
	data->state = DEFAULT;
	result = NULL;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			data->state = check_state(line[i++]);
		if (line[i] && data->state == DOU_QUOTHE)
		{
			i = expand_dou_quote(line, i, &result, data);
			data->state = check_state(line[i]);
		}
		else if (line[i] && data->state == SIN_QUOTHE)
			i = expand_sin_quote(line, i, &data->state, &result);
		if (data->state == DEFAULT && line[i] == '$')
			i = exporting(&result, line, i, data);
		else if (line[i] && data->state == DEFAULT)
			append_char(&result, line[i++]);
	}
	return (result);
}

char	*check_expender(char *args, t_data *data)
{
	char	*res;
	size_t	i;

	i = 0;
	res = NULL;
	while (args && (args[i] == '\'' || args[i] == '"'))
		i++;
	if (i == ft_strlen(args))
		return (ft_strdup(""));
	i = 0;
	while (args && args[i] && !is_token(args[i]))
	{
		while (args[i] == '$' && args[i + 1] == '$')
			i++;
		if ((args[i] == '$' && type_caracter(args[i + 1]))
			|| args[i] == '\'' || args[i] == '\"')
		{
			res = expander(args, data);
			break ;
		}
		i++;
	}
	if (res != NULL)
		return (res);
	return (args);
}
