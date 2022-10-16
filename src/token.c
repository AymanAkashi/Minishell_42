/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 08:04:09 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/11 20:28:47 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_token(t_token **token, t_data *data)
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
			set_here_doc(token, data);
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

void	set_num(int *n)
{
	if (n == 0)
		*n = 1;
	else
		*n = 0;
}

int	creat_tokenization(t_token **token, char *line, t_data *data, int i)
{
	(*token)->state = check_state(line[i]);
	if ((*token)->state == DEFAULT)
		i = ft_str_cpyn(line, token, i, data);
	else if ((*token)->state == SIN_QUOTHE)
		i = ft_sin_quote(line, *token, i, data);
	else if ((*token)->state == DOU_QUOTHE)
		i = ft_dou_quote(line, *token, i, data);
	return (i);
}

void	tokenizetion(t_token **token, char *line, t_data *data)
{
	t_token	*head;
	int		i;

	i = 0;
	head = *token;
	data->parenthes = 0;
	data->operator = 0;
	while (line && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line && line[i])
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
		i = creat_tokenization(token, line, data, i);
	}
	*token = head;
	type_token(&head, data);
	index_token(token);
}
