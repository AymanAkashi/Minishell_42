/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:45:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 17:37:24 by aaggoujj         ###   ########.fr       */
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

int	check_double_helper(t_token *tmp)
{
	if ((tmp->type != TOKEN_WORD && tmp->type != TOKEN_PAREN_OUT
			&& tmp->next && tmp->next->type == TOKEN_PAREN_OUT))
		return (1);
	if (tmp->type == TOKEN_WORD && tmp->next
		&& tmp->next->type == TOKEN_PAREN_IN)
		return (1);
	if (tmp->type == TOKEN_PAREN_IN
		&& (tmp->next->cmd[0] == '|' || tmp->next->cmd[0] == '&'))
		return (1);
	return (0);
}

int	check_double(t_token *token)
{
	t_token			*tmp;
	t_type_token	type;

	tmp = token;
	while (tmp)
	{
		type = tmp->type;
		if (tmp && !ft_strcmp(tmp->cmd, "&") && ft_strcmp(tmp->next->cmd, "&"))
			return (ft_exit_ps(ECHECK, tmp->cmd));
		if (!check_redirection(tmp, type))
			return (0);
		if (is_redirection(type) && tmp->next && is_type_token(tmp->next->type))
			return (ft_exit_ps(ECHECK, tmp->next->cmd));
		if ((tmp->type == TOKEN_PAREN_OUT) && tmp->next
			&& tmp->next->type == TOKEN_WORD)
			return (ft_exit_ps(ECHECK, tmp->next->cmd));
		if (check_double_helper(tmp))
			return (ft_exit_ps(ECHECK, tmp->cmd));
		tmp = tmp->next;
	}
	return (1);
}

int	checking_parenteses(char *line)
{
	int	parenteses;
	int	i;

	i = 0;
	parenteses = 0;
	while (line && line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = got_close_quote(line, line[i], i);
			if (!i)
				return (0);
		}
		if (parenteses < 0 || (line[i] == ')' && line[i + 1] == '('))
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
	if (check_quote(token) == 0)
		return (ft_exit_ps("minishell: syntax error! \n", "\0"));
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
	return (1);
}
