/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 08:04:09 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/23 23:09:51 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_token(char c)
{
	if (c == '|' || c == '&' || c == '(' || c == ')' || c == '<'
			|| c == '>')
		return (1);
	return (0);
}

void	token_check(t_token *token)
{
	if (ft_strncmp(token->cmd, "|", 2))
		token->type_token = TOKEN_PIPE;
	else if (ft_strncmp(token->cmd, ">", 2))
		token->type_token = TOKEN_RED_OUT;
	else if (ft_strncmp(token->cmd, "<", 2))
		token->type_token = TOKEN_RED_OUT;
	else if (ft_strncmp(token->cmd, ">>", 3))
		token->type_token = TOKEN_RED2_OUT;
	else if (ft_strncmp(token->cmd, "<<", 3))
		token->type_token = TOKEN_HEREDOC;
	else if (ft_strncmp(token->cmd, "&&", 3))
		token->type_token = TOKEN_AND;
	else if (ft_strncmp(token->cmd, "||", 3))
		token->type_token = TOKEN_OR;
	else
		token->type_token = TOKEN_WORD;
}

void	*ft_any_alloc(size_t size, size_t len)
{
	void	*ptr;

	ptr = malloc(size * len);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size * len);
	return (ptr);
}

int	ft_str_cpyn(char *line, t_token *token, int i)
{
	int j;
	int k;

	k = 0;
	j = i;
	while(line[j] && line[j] != ' ' && line[j] != '\t' && !is_token(line[j]))
	{
		k++;
		j++;
	}
	token->cmd = ft_any_alloc(sizeof(char), k + 1);
	j = i;
	k = 0;
	while(line[j] &&  line[j] != ' ' && line[j] != '\t' && !is_token(line[j]))
	{
		token->cmd[k] = line[j];
		k++;
		j++;
	}
	token->cmd[k] = '\0';
	while(line[i] != '\0' && (line[j] == ' ' || line[j] == '\t'))
		j++;
	return (j);
}

int	token_pipe(t_token *token, char *line, int i)
{
	int k;

	k = 0;
	if(line[i] == line[i + 1])
		token->cmd = ft_any_alloc(sizeof(char), 3);
	else
		token->cmd = ft_any_alloc(sizeof(char), 2);
	if(line[i] == '|')
		token->cmd[k++] = line[i];
	if (line[i + 1] == '|')
		token->cmd[k++] = line[++i];
	token->cmd[k] = '\0';
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}



void	tokenizetion(t_token **token, char *line)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	t_token *head;
	head = *token;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if(!is_token(line[i]))
			i = ft_str_cpyn(line, *token, i);
		else if (line[i] == '|')
			i = token_pipe(*token, line, i);
		else if (line[i] == '&')
			i = token_and(*token, line, i);
		else if (line[i] == '(' || line[i] == ')')
			i = token_paren(*token, line, i);
		else if (line[i] == '<')
			i = token_red_in(*token, line, i);
		else if (line[i] == '>')
			i = token_red_out(*token, line, i);
		if(line[i])
		{
			(*token)->next = (t_token *)ft_any_alloc(sizeof(t_token), 1);
			*token = (*token)->next;
			i++;
		}
	}
	*token = head;
}