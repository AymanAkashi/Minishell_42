/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:26:53 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/24 23:54:21 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(t_token *token)
{
	if (token->next)
		return (token->next);
	return (NULL);
}

t_scanner	*scanner_token(t_token *token, t_scanner *curr_scan)
{
	t_scanner	*scanner;

	scanner = (t_scanner *)malloc(sizeof(t_scanner));
	scanner->curr_token = NULL;
	scanner->next_token = NULL;
	if (curr_scan == NULL)
	{
		scanner->curr_token = token;
		scanner->next_token = get_next_token(token);
		return (scanner);
	}
	while (token && token != curr_scan->curr_token)
		token = token->next;
	if (token)
	{
		scanner->curr_token = token;
		scanner->next_token = get_next_token(token);
	}
	return (scanner);
}
