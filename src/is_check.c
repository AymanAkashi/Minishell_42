/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:47:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/01 17:04:41 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	check_state(char c)
{
	if (c == '\'')
		return (SIN_QUOTHE);
	if (c == '\"')
		return (DOU_QUOTHE);
	else
		return (DEFAULT);
}

int	is_token(char c)
{
	if (c == '|' || c == '&' || c == '(' || c == ')' || c == '<'
		|| c == '>')
		return (1);
	return (0);
}

int	is_type_token(t_type_token type)
{
	if (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_PIPE
		|| type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	is_redirection(t_type_token type)
{
	if (type == TOKEN_RED_IN || type == TOKEN_RED_OUT
		|| type == TOKEN_RED2_OUT || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	close_quote(char *str, char c, int index)
{
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (0);
}
