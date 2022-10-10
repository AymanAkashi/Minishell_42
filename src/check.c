/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:45:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/10 21:41:28 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(t_token *tmp, t_type_token type)
{
	if ((is_redirection(type) && tmp->next == NULL)
		|| (is_redirection(type) && tmp->next->type != TOKEN_WORD))
		return (ft_exit_ps(ECHECK, "newline"));
	if (is_redirection(tmp->type) && tmp->next
		&& tmp->next->next && tmp->next->next->type == TOKEN_PAREN_IN)
		return (ft_exit_ps(ECHECK, tmp->cmd));
	if (is_type_token(tmp->type) && tmp->next
		&& (tmp->next->type != TOKEN_WORD && tmp->next->type != TOKEN_PAREN_IN
			&& tmp->next->type != TOKEN_PAREN_OUT
			&& !is_redirection(tmp->next->type)))
		return (ft_exit_ps(ECHECK, tmp->next->cmd));
	if (tmp->type == TOKEN_PAREN_IN && tmp->next->type == TOKEN_PAREN_OUT)
		return (ft_exit_ps(ECHECK, tmp->next->cmd));
	if (is_redirection(type) && tmp->next
		&& (tmp->next->type == TOKEN_PAREN_IN
			|| tmp->next->type == TOKEN_PAREN_OUT))
		return (ft_exit_ps(ECHECK, tmp->cmd));
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
			return (ft_exit_ps(ECHECK, tmp->next->cmd));
		if ((tmp->type == TOKEN_PAREN_OUT) && tmp->next
			&& tmp->next->type == TOKEN_WORD)
			return (ft_exit_ps(ECHECK, tmp->next->cmd));
		if ((tmp->type != TOKEN_WORD && tmp->type != TOKEN_PAREN_OUT
			&& tmp->next && tmp->next->type == TOKEN_PAREN_OUT))
			return (ft_exit_ps(ECHECK, tmp->next->cmd));
		if (tmp->type == TOKEN_WORD && tmp->next
			&& tmp->next->type == TOKEN_PAREN_IN)
			return (ft_exit_ps(ECHECK, tmp->cmd));
		if (tmp->type == TOKEN_PAREN_IN
			&& (tmp->next->cmd[0] == '|' || tmp->next->cmd[0] == '&'))
			return (ft_exit_ps(ECHECK, tmp->next->cmd));
		tmp = tmp->next;
	}
	return (1);
}

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

int	checking_parenteses(char *line)
{
	int	parenteses;
	int	i;

	i = 0;
	if (!line)
		return (0);
	parenteses = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			while(line[++i] && line[i] != '\'')
				;
		if (line[i] == '\"')
			while(line[++i] && line[i] != '\"')
				;
		if (parenteses < 0)
			return (0);
		if (line[i] == '(')
			parenteses++;
		else if (line[i] == ')')
			parenteses--;
		i++;
	}
	if (parenteses != 0)
		return (0);
	return (1);
}

int	check_line(t_token *token, t_data *data, char *line)
{
	size_t	i;

	i = 1;
	(void)token;
	if (data->dou_quothe == 1)
		return (ft_exit_ps("minishell: unexpected close dou_quotes\n", "\0"));
	if (data->sin_quothe == 1)
		return (ft_exit_ps("minishell: unexpected close sin_quotes\n", "\0"));
	if (checking_parenteses(line) == 0)
		return (ft_exit_ps("minishell: unexpected close parentheses\n", "\0"));
	if (line[0] == '|' || line[0] == '&')
		return (ft_exit_ps("minishell: syntax error!\n", "\0"));
	while (i <= ft_strlen(line) && (line[ft_strlen(line) - i] == ' '
			|| line[ft_strlen(line) - i] == '\t'))
		i++;
	if (i <= ft_strlen(line) && (line[ft_strlen(line) - i] == '|'
			|| line[ft_strlen(line) - i] == '&'))
		return (ft_exit_ps("minishell: syntax error! \n", "\0"));
	if (check_double(token) == 0)
		return (0);
	if (check_quote(token) == 0)
		return (ft_exit_ps("minishell: syntax error! \n", "\0"));
	return (1);
}
