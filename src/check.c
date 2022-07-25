/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:45:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/25 21:24:24 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_ps(char *str, int i)
{
	ft_putstr_fd(str, i);
	exit(i);
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

void	check_line(t_token *token, t_data *data, char *line)
{
	int i;

	i = 1;
	(void)token;
	if (data->quothe % 2 != 0)
		printf("minishell: syntax error! unexpected close quotes\n");
	if (data->parenthes % 2 != 0)
		printf("minishell: syntax error! unexpected close parentheses\n");
	if (line[0] == '|' || line[0] == '&')
		printf("minishell: syntax error! unexpected pipe or and\n");
	while (line[ft_strlen(line) - i] == ' '
			|| line[ft_strlen(line) - i] == '\t')
		i++;
	if (line[ft_strlen(line) - i] == '|' || line[ft_strlen(line) - i] == '&')
		printf("minishell: syntax error! unexpected pipe or and\n");
}