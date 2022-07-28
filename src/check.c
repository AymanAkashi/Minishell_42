/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:45:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/28 11:58:09 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_ps(char *str)
{
	ft_putstr_fd(str, 1);
	return(0);
}

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

int	check_double(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while(tmp)
	{
		if(tmp->type == TOKEN_PIPE && tmp->next && tmp->next->type == TOKEN_PIPE)
			return (ft_exit_ps("minishell: syntax error near unexpected token '|'\n"));
		else if(tmp->type == TOKEN_AND && tmp->next && tmp->next->type == TOKEN_AND)
			return (ft_exit_ps("minishell: syntax error near unexpected token '&'\n"));
		else if(tmp->type == TOKEN_OR && tmp->next && tmp->next->type == TOKEN_OR)
			return (ft_exit_ps("minishell: syntax error near unexpected token '||'\n"));
		tmp = tmp->next;
	}
	return (1);
}

int	check_line(t_token *token, t_data *data, char *line)
{
	int i;

	i = 1;
	(void)token;
	if (data->quothe % 2 != 0)
		return(ft_exit_ps("minishell: syntax error! unexpected close quotes\n"));
	if (data->parenthes % 2 != 0)
		return (ft_exit_ps("minishell: syntax error! unexpected close parentheses\n"));
	if (line[0] == '|' || line[0] == '&')
		return (ft_exit_ps("minishell: syntax error! unexpected pipe or and\n"));
	while (line[ft_strlen(line) - i] == ' '
			|| line[ft_strlen(line) - i] == '\t')
		i++;
	if (line[ft_strlen(line) - i] == '|' || line[ft_strlen(line) - i] == '&')
		return (ft_exit_ps("minishell: syntax error! unexpected pipe or and\n"));
	if (check_double(token) == 0)
		return (0);
	return (1);
}