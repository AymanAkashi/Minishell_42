/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:45:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/18 19:23:04 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_ps(char *str, char *str2)
{
	ft_putstr_fd(str, 1);
	if (str2[0] != '\0')
	{
		ft_putstr_fd(str2, 1);
		ft_putstr_fd("\'\n", 1);
	}
	return (0);
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

int check_redirection(t_token *tmp, t_type_token type)
{
		if ((is_redirection(type) && tmp->next == NULL) || (is_redirection(type) && tmp->next->type != TOKEN_WORD))
			return (ft_exit_ps("minishell: syntax error near unexpected token `",	"newline"));
		if ((tmp->type == TOKEN_PAREN_OUT) && tmp->next && is_redirection(tmp->next->type))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->cmd));
		if (is_redirection(tmp->type) && tmp->next && tmp->next->next && tmp->next->next->type == TOKEN_PAREN_IN)
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->cmd));
		if ((tmp->type == TOKEN_PAREN_OUT) && tmp->next && is_redirection(tmp->next->type))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->cmd));
		if (is_type_token(tmp->type) && tmp->next
		&& (tmp->next->type != TOKEN_WORD && tmp->next->type != TOKEN_PAREN_IN
			&& tmp->next->type != TOKEN_PAREN_OUT && !is_redirection(tmp->next->type)))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		if (tmp->type == TOKEN_PAREN_IN && tmp->next->type == TOKEN_PAREN_OUT)
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		if (is_redirection(type) && tmp->next && (tmp->next->type == TOKEN_PAREN_IN || tmp->next->type == TOKEN_PAREN_OUT))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->cmd));
		return (1);
}

int	check_double(t_token *token)
{
	t_token			*tmp;
	t_type_token	type;

	tmp = token;
	while (tmp)
	{
		type = tmp->type;
		if (!check_redirection(tmp, type))
			return (0);
		if (is_redirection(type) && tmp->next && is_type_token(tmp->next->type))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		if ((tmp->type == TOKEN_PAREN_OUT) && tmp->next && tmp->next->type == TOKEN_WORD)
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		if (type != TOKEN_WORD && tmp->next && type == tmp->next->type)
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->cmd));
		if (tmp->type == TOKEN_WORD && tmp->next && tmp->next->type == TOKEN_PAREN_IN)
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->cmd));
		if (tmp->type == TOKEN_PAREN_IN && (tmp->next->cmd[0] == '|' || tmp->next->cmd[0] == '&'))
			return (ft_exit_ps("minishell: syntax error near unexpected token `", tmp->next->cmd));
		tmp = tmp->next;
	}
	return (1);
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

int	check_quote(t_token *token)
{
	t_token *tmp;
	int		i;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == TOKEN_WORD)
		{
			i = 0;
			while (tmp->cmd[i])
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
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_line(t_token *token, t_data *data, char *line)
{
	size_t	i;

	i = 1;
	(void)token;
	if (data->dou_quothe == 1)
		return(ft_exit_ps("minishell: syntax error! unexpected close dou_quotes\n", "\0"));
	if (data->sin_quothe == 1)
		return(ft_exit_ps("minishell: syntax error! unexpected close sin_quotes\n", "\0"));
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
	if (check_quote(token) == 0)
		return (ft_exit_ps("minishell: syntax error! \n", "\0"));
	return (1);
}
 