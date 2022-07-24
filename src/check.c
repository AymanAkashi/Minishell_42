/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:45:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/24 23:57:19 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	check_state(char c)
{
	if (c == '\"' || c == '\'')
		return (QUOTHE);
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
