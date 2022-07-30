/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [Tokenization]copy_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:49:21 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/29 14:42:55 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dou_quote(char *line, t_token *token, int i, t_data *data)
{
	int	k;

	k = 0;
	data->dou_quothe++;
	if (token->cmd)
		k = ft_strlen(token->cmd);
	if (k == 0)
		token->cmd = ft_any_alloc(sizeof(char), 2);
	append_char(&(token)->cmd, line[i++]);
	while (line[i] && line[i] != '\"')
		append_char(&(token)->cmd, line[i++]);
	if (line[i])
	{
		data->dou_quothe++;
		append_char(&(token)->cmd, line[i++]);
	}
	if (line[i] && line[i] != ' ' && line[i] != '\t' && !is_token(line[i]))
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\"')
			append_char(&(token)->cmd, line[i++]);
	return (i);
}

int	ft_sin_quote(char *line, t_token *token, int i, t_data *data)
{
	int	k;

	k = 0;
	data->sin_quothe++;
	if (token->cmd)
		k = ft_strlen(token->cmd);
	if (k == 0)
		token->cmd = ft_any_alloc(sizeof(char), 2);
	append_char(&(token)->cmd, line[i++]);
	while (line[i] && line[i] != '\'')
		append_char(&(token)->cmd, line[i++]);
	if (line[i])
	{
		data->sin_quothe++;
		append_char(&(token)->cmd, line[i++]);
	}
	if (line[i] && line[i] != ' ' && line[i] != '\t' && !is_token(line[i]))
		while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\'')
			append_char(&(token)->cmd, line[i++]);
	return (i);
}

int	add_token(char *line, t_token **token, int i, t_data *data)
{
	if (line[i] == '|')
		i = token_pipe(*token, line, i);
	else if (line[i] == '&' && line[i + 1] == '&')
		i = token_and(*token, line, i);
	else if (line[i] == '(' || line[i] == ')')
		i = token_paren(*token, line, i, data);
	else if (line[i] == '<')
		i = token_red_in(*token, line, i);
	else if (line[i] == '>')
		i = token_red_out(*token, line, i);
	else
	{
		append_char(&(*token)->cmd, line[i]);
		i++;
	}
	return (i);
}

void	append_char(char **line, char c)
{
	char	*dest;
	int		i;

	i = 0;
	if (*line == NULL)
		*line = ft_any_alloc(sizeof(char), 2);
	dest = ft_any_alloc(sizeof(char), ft_strlen(*line) + 2);
	while ((*line)[i])
	{
		dest[i] = (*line)[i];
		i++;
	}
	dest[i] = c;
	dest[i + 1] = '\0';
	free(*line);
	*line = dest;
}

int	ft_str_cpyn(char *line, t_token **token, int i, t_data *data)
{
	int	j;

	j = i;
	if (line[i] && line[i] != ' ' && line[i] != '\t' && !is_token(line[i]))
	{
		append_char(&(*token)->cmd, line[i]);
		i++;
	}
	else if (is_token(line[i]))
	{
		if(line[i] == '&' && line[i + 1] != '&')
			return (add_token(line, token, i, data));
		else if ((*token)->cmd != NULL)
		{
			(*token)->next = ft_any_alloc(sizeof(t_token), 1);
			(*token) = (*token)->next;
		}
		i = add_token(line, token, i, data);
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		{
			(*token)->next = ft_any_alloc(sizeof(t_token), 1);
			(*token) = (*token)->next;
		}
	}
	return (i);
}
