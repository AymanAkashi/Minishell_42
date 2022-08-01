/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:45:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/31 11:33:04 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_ps(char *str, char *str2)
{
	ft_putstr_fd(str, 1);
	if(str2[0]!= '\0')
	{
		ft_putstr_fd(str2, 1);
		ft_putstr_fd("\'\n", 1);
	}
	return(0);
}

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

int is_type_token(t_type_token type)
{
	if (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_PIPE
		|| type == TOKEN_RED_IN || type == TOKEN_RED_OUT
		|| type == TOKEN_RED2_OUT || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	check_double(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (is_type_token(tmp->type) && tmp->next
		&& (tmp->next->type != TOKEN_WORD && tmp->next->type != TOKEN_PAREN_IN
			&& tmp->next->type != TOKEN_PAREN_OUT))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		if (tmp->type == TOKEN_PAREN_IN && tmp->next->type == TOKEN_PAREN_OUT)
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		if (tmp->type == TOKEN_PAREN_IN && (tmp->next->cmd[0] == '|' || tmp->next->cmd[0] == '&' || tmp->next->cmd[0] == '<' || tmp->next->cmd[0] == '>'))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		tmp = tmp->next;
	}
	return (1);
}

int	check_line(t_token *token, t_data *data, char *line)
{
	size_t i;

	i = 1;
	(void)token;
	if (data->dou_quothe % 2 != 0)
		return(ft_exit_ps("minishell: syntax error! unexpected close quotes\n", "\0"));
	if (data->sin_quothe % 2 != 0)
		return(ft_exit_ps("minishell: syntax error! unexpected close quotes\n", "\0"));
	if (data->parenthes % 2 != 0)
		return (ft_exit_ps("minishell: syntax error! unexpected close parentheses\n", "\0"));
	if (line[0] == '|' || line[0] == '&')
		return (ft_exit_ps("minishell: syntax error!\n", "\0"));
	while (i <= ft_strlen(line) && (line[ft_strlen(line) - i] == ' '
			|| line[ft_strlen(line) - i] == '\t'))
		i++;
	if (i <= ft_strlen(line) &&  (line[ft_strlen(line) - i] == '|' || line[ft_strlen(line) - i] == '&'))
		return (ft_exit_ps("minishell: syntax error! \n", "\0"));
	if (check_double(token) == 0)
		return (0);
	return (1);
}