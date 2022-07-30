/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [parsing]parc_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:23:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/30 23:27:21 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
t_ast *parc_word(t_scanner *scan, t_data *data, t_ast *root);

t_ast *ft_create_ast(void)
{
	t_ast *new;

	new = malloc(sizeof(t_ast));
	new->cmd = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast *parc_word(t_scanner *scan, t_data *data, t_ast *root);

t_ast*	parcing(t_data *data, t_ast *ast, t_scanner *scan)
{
	scanner_token(data->token, &scan);
	if(!scan && scan->curr_token->cmd == NULL)
		return NULL ;
 	while (scan->curr_token)
	{
		if (scan->curr_token->type == TOKEN_WORD
			|| scan->curr_token->type == TOKEN_PIPE)
			{
				if(ast)
					ast = parc_word(scan, data, ast);
				else
					ast = parc_word(scan, data, NULL);
			}
		else if (scan->curr_token->type == TOKEN_AND
			|| scan->curr_token->type == TOKEN_OR)
			ast = parc_opera(scan, ast, data);
		else if (scan->curr_token->type == TOKEN_PAREN_IN)
				ast = parc_paren(scan, ast, data);
		else if (scan->curr_token->type == TOKEN_PAREN_OUT)
		{
			scanner_token(data->token, &scan);
			return (ast);
		}
	}
	return (ast);
}




