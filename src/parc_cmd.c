/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:23:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 15:54:08 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast	*ft_create_ast(void)
{
	t_ast	*new;

	new = ft_calloc(sizeof(t_ast), 1);
	new->cmd = NULL;
	new->left = NULL;
	new->right = NULL;
	new->here_doc = NULL;
	new->args_exp = NULL;
	new->args = NULL;
	new->in = 0;
	new->out = 1;
	new->exp = 1;
	return (new);
}

t_ast	*parcing_word(t_ast *ast, t_scanner *scan, t_data *data)
{
	if (ast && ast->cmd != NULL)
		ast = parc_word(scan, data, ast);
	else
		ast = parc_word(scan, data, NULL);
	return (ast);
}

t_ast	*parcing(t_data *data, t_ast *ast, t_scanner *scan)
{
	if (!scan && scan->curr_token->cmd == NULL)
		return (NULL);
	while (scan->curr_token)
	{
		if (scan->curr_token->type == TOKEN_WORD
			|| scan->curr_token->type == TOKEN_PIPE)
			ast = parcing_word(ast, scan, data);
		else if (scan->curr_token->type == TOKEN_AND
			|| scan->curr_token->type == TOKEN_OR)
			ast = parc_opera(scan, ast, data);
		else if (is_redirection(scan->curr_token->type))
			ast = parc_redirection(scan, ast, data);
		else if (scan->curr_token->type == TOKEN_PAREN_IN)
		{
			if (!ast)
				ast = parc_paren(scan, ast, data);
			else
				ast->left = parc_paren(scan, ast, data);
		}
		else if (scan->curr_token->type == TOKEN_PAREN_OUT)
			return (scanner_token(data->token, &scan), ast);
	}
	if (ast == NULL || ast->cmd == NULL)
		return (NULL);
	return (ast);
}
