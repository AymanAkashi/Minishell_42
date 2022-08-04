/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [Tokenization]token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 08:04:09 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/04 17:15:22 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_nl(char *str, char *dest, char c)
{
	char	*src;
	int		i;
	int		j;

	i = -1;
	if (!dest)
		return (NULL);
	if (!str)
	{
		str = ft_any_alloc(sizeof(char), 2);
		str[0] = '\0';
	}
	src = ft_any_alloc(sizeof(char), ft_strlen(str) + ft_strlen(dest) + 2);
	if (!src)
		return (NULL);
	while (str[++i])
		src[i] = str[i];
	if (str[0] != '\0')
		src[i++] = c;
	j = -1;
	while (dest[++j])
		src[i++] = dest[j];
	src[i] = '\0';
	free(str);
	return (src);
}

void	type_heredoc(t_token **token)
{
	char *line;

	(*token)->type = TOKEN_HEREDOC;
	if (!(*token)->next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			exit(1);
		}
	while(1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp((*token)->next->cmd, line, ft_strlen(line)) == 0)
		{
			free (line);
			break;
		}
		if (!line)
			continue ;
		else if (line)
		{

			(*token)->here_doc = ft_strjoin_nl((*token)->here_doc, line, '\n');
			free (line);
		}
	}
}

void	type_token(t_token **token)
{
	while (*token)
	{
		if (!ft_strncmp((*token)->cmd, "|", 2))
			(*token)->type = TOKEN_PIPE;
		else if (!ft_strncmp((*token)->cmd, ">", 2))
			(*token)->type = TOKEN_RED_OUT;
		else if (!ft_strncmp((*token)->cmd, "<", 2))
			(*token)->type = TOKEN_RED_IN;
		else if (!ft_strncmp((*token)->cmd, ">>", 3))
			(*token)->type = TOKEN_RED2_OUT;
		else if (!ft_strncmp((*token)->cmd, "<<", 3))
			type_heredoc(token);
		else if (!ft_strncmp((*token)->cmd, "&&", 3))
			(*token)->type = TOKEN_AND;
		else if (!ft_strncmp((*token)->cmd, "||", 3))
			(*token)->type = TOKEN_OR;
		else if (!ft_strncmp((*token)->cmd, "(", 2))
			(*token)->type = TOKEN_PAREN_IN;
		else if (!ft_strncmp((*token)->cmd, ")", 2))
			(*token)->type = TOKEN_PAREN_OUT;
		else
			(*token)->type = TOKEN_WORD;
		*token = (*token)->next;
	}
}

void	index_token(t_token **token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

void	tokenizetion(t_token **token, char *line, t_data *data)
{
	t_token	*head;
	int		i;

	i = 0;
	head = *token;
	data->parenthes = 0;
	data->sin_quothe = 0;
	data->dou_quothe = 0;
	data->operator = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t'))
		{
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (!line[i])
				break ;
			if ((*token)->cmd != NULL)
				alloc_token(token);
		}
		(*token)->state = check_state(line[i]);
		if ((*token)->state == DEFAULT)
			i = ft_str_cpyn(line, token, i, data);
		else if ((*token)->state == SIN_QUOTHE)
			i = ft_sin_quote(line, *token, i, data);
		else if ((*token)->state == DOU_QUOTHE)
			i = ft_dou_quote(line, *token, i, data);
	}
	*token = head;
	type_token(&head);
	index_token(token);
}

