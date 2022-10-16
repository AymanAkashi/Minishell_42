/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:37:01 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 17:39:29 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_2(t_token *tmp)
{
	int	i;

	i = -1;
	while (tmp->cmd && tmp->cmd[++i])
	{
		if (tmp->cmd[i] == '\"')
		{
			i = close_quote(tmp->cmd, '\"', ++i);
			if (!i)
				return (0);
		}
		else if (tmp->cmd[i] == '\'')
		{
			i = close_quote(tmp->cmd, '\'', ++i);
			if (!i)
				return (0);
		}
	}
	return (1);
}

int	check_quote(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
		{
			if (check_quote_2(tmp) == 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	got_close_quote(char *str, char c, int i)
{
	if (c == '\'')
		while (str[++i] && str[i] != '\'')
			;
	if (c == '\"')
		while (str[++i] && str[i] != '\"')
			;
	if (!str[i])
		return (0);
	return (i);
}
