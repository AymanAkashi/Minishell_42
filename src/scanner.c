/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:26:53 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/25 08:28:59 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(t_token *token)
{
	if (token->next)
		return (token->next);
	return (NULL);
}

void	scanner_token(t_token *token, t_scanner **curr_scan)
{
	if ((*curr_scan) == NULL)
	{
		*curr_scan = (t_scanner *)malloc(sizeof(t_scanner));
		(*curr_scan)->curr_token = token;
		(*curr_scan)->next_token = get_next_token(token);
	}
	else
	{
		while (token && token != (*curr_scan)->next_token)
			token = token->next;
		if (token)
		{
			(*curr_scan)->curr_token = token;
			(*curr_scan)->next_token = get_next_token(token);
		}
	}
}
