/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:26:53 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/16 01:39:38 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	return (0);
}

t_token	*get_next_token(t_token *token)
{
	if (token && token->next)
		return (token->next);
	return (NULL);
}

static	void	free_scanner(t_scanner **scanner)
{
	(*scanner)->curr_token = NULL;
	(*scanner)->next_token = NULL;
}

void	scanner_token(t_token *token, t_scanner **curr_scan)
{
	t_token	*tmp;

	tmp = token;
	if ((*curr_scan) == NULL)
	{
		*curr_scan = (t_scanner *)malloc(sizeof(t_scanner));
		if (!(*curr_scan))
			ft_exit2(ALLOCATION_FAILED, 1);
		(*curr_scan)->curr_token = token;
		(*curr_scan)->next_token = get_next_token(token);
	}
	else
	{
		while (tmp && tmp != (*curr_scan)->next_token)
			tmp = tmp->next;
		if (token)
		{
			(*curr_scan)->curr_token = tmp;
			(*curr_scan)->next_token = get_next_token(tmp);
		}
		else
		{
			free_scanner(curr_scan);
		}
	}
}
