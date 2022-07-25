/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 23:10:16 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/25 13:21:53 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_pipe(t_token *token, char *line, int i)
{
	int	k;

	k = 0;
	if (line[i] == line[i + 1])
		token->cmd = ft_any_alloc(sizeof(char), 3);
	else
		token->cmd = ft_any_alloc(sizeof(char), 2);
	if (line[i] == '|')
		token->cmd[k++] = line[i++];
	if (line[i] == '|')
		token->cmd[k++] = line[i++];
	token->cmd[k] = '\0';
	return (i);
}

int	token_and(t_token *token, char *line, int i)
{
	int	k;

	k = 0;
	if (line[i] == line[i + 1])
		token->cmd = ft_any_alloc(sizeof(char), 3);
	else
		token->cmd = ft_any_alloc(sizeof(char), 2);
	if (line[i] == '&')
		token->cmd[k++] = line[i++];
	if (line[i] == '&')
		token->cmd[k++] = line[i++];
	token->cmd[k] = '\0';
	return (i);
}

int	token_paren(t_token *token, char *line, int i, t_data *data)
{
	int	k;

	k = 0;
	token->cmd = ft_any_alloc(sizeof(char), 2);
	if (line[i] == '(')
	{
		token->cmd[k++] = line[i++];
		data->parenthes++;
	}
	else
	{
		token->cmd[k++] = line[i++];
		data->parenthes++;
	}
	token->cmd[k] = '\0';
	return (i);
}

int	token_red_in(t_token *token, char *line, int i)
{
	int	k;

	k = 0;
	if (line[i] == line[i + 1])
		token->cmd = ft_any_alloc(sizeof(char), 3);
	else
		token->cmd = ft_any_alloc(sizeof(char), 2);
	if (line[i] == '<')
		token->cmd[k++] = line[i++];
	if (line[i] == '<')
		token->cmd[k++] = line[i++];
	token->cmd[k] = '\0';
	return (i);
}

int	token_red_out(t_token *token, char *line, int i)
{
	int	k;

	k = 0;
	if (line[i] == line[i + 1])
		token->cmd = ft_any_alloc(sizeof(char), 3);
	else
		token->cmd = ft_any_alloc(sizeof(char), 2);
	if (line[i] == '>')
		token->cmd[k++] = line[i++];
	if (line[i] == '>')
		token->cmd[k++] = line[i++];
	return (i);
}
