/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 08:04:09 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/24 23:53:47 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_token(t_token **token)
{
	while (*token)
	{
		if (!ft_strncmp((*token)->cmd, "|", 2))
			(*token)->type_token = TOKEN_PIPE;
		else if (!ft_strncmp((*token)->cmd, ">", 2))
			(*token)->type_token = TOKEN_RED_OUT;
		else if (!ft_strncmp((*token)->cmd, "<", 2))
			(*token)->type_token = TOKEN_RED_IN;
		else if (!ft_strncmp((*token)->cmd, ">>", 3))
			(*token)->type_token = TOKEN_RED2_OUT;
		else if (!ft_strncmp((*token)->cmd, "<<", 3))
			(*token)->type_token = TOKEN_HEREDOC;
		else if (!ft_strncmp((*token)->cmd, "&&", 3))
			(*token)->type_token = TOKEN_AND;
		else if (!ft_strncmp((*token)->cmd, "||", 3))
			(*token)->type_token = TOKEN_OR;
		else if (!ft_strncmp((*token)->cmd, "(", 2))
			(*token)->type_token = TOKEN_PAREN_IN;
		else if (!ft_strncmp((*token)->cmd, ")", 2))
			(*token)->type_token = TOKEN_PAREN_OUT;
		else
			(*token)->type_token = TOKEN_WORD;
		*token = (*token)->next;
	}
}

void	tokenizetion(t_token **token, char *line)
{
	t_token	*head;
	int		i;

	i = 0;
	head = *token;
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
			i = ft_str_cpyn(line, token, i);
		else if ((*token)->state == QUOTHE)
			i = ft_quote(line, *token, i);
	}
	*token = head;
	type_token(&head);
}
