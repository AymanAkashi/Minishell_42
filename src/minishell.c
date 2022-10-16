/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:07:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 16:27:24 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_ast(t_ast *ast)
{
	t_ast	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ast;
	while (tmp)
	{
		i++;
		tmp = tmp->right;
	}
	tmp = ast;
	while (tmp)
	{
		j++;
		tmp = tmp->left;
	}
	if (j > i)
		return (j);
	else
		return (i);
}

int	add_here_doc(t_token **token, t_data *data)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			if (!type_heredoc(&tmp, data, data->token->next->cmd))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	beg_minishell(t_data *data)
{
	if (data->here_doc == 1)
		if (!add_here_doc(&data->token, data))
			return ;
	scanner_token(data->token, &data->scanner);
	data->root = parcing(data, data->root, data->scanner);
	execution(data, data->root);
	close_all(data->root);
	wait_all(0);
	_hidectrl();
}
