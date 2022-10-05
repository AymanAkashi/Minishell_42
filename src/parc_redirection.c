/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:02:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/04 21:01:42 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*just_red(t_scanner *scan, t_data *data)
{
	t_ast	*new;

	new = ft_create_ast();
	new->cmd = ft_strdup(scan->curr_token->cmd);
	new->here_doc = ft_strdup(scan->curr_token->here_doc);
	new->args = ft_any_alloc(sizeof(char *), 3);
	new->args[0] = ft_strdup(scan->curr_token->cmd);
	new->type = scan->curr_token->type;
	scanner_token(data->token, &scan);
	new->args[1] = ft_strdup(scan->curr_token->cmd);
	new->args[2] = NULL;
	scanner_token(data->token, &scan);
	return (new);
}

void	parc_red_in2(t_ast *root, t_ast *ast, t_ast *new)
{
	if (!root->left)
		root->left = new;
	else if (!root->right)
		root->right = new;
	else
	{
		if (new)
			ast_add_left(&root, new);
		else
			ast_add_left(&root, ast);
	}
}

t_ast	*parc_red_in(t_scanner *scan, t_ast *root, t_ast *ast, t_data *data)
{
	t_ast	*new;

	new = NULL;
	if (scan->curr_token && scan->curr_token->type == TOKEN_WORD)
	{
		new = parc_cmd(scan, data);
		ast_add_left(&new, ast);
	}
	else if (scan->curr_token && scan->curr_token->type == TOKEN_PIPE)
	{
		new = parc_word(scan, data, root);
		ast_add_left(&new, ast);
	}
	if (root)
		parc_red_in2(root, ast, new);
	else
		root = new;
	return (root);
}

void	parcing_word_red(t_scanner *scan, t_data *data, t_ast *new)
{
	if (scan->curr_token->type == TOKEN_RED2_OUT
		|| scan->curr_token->type == TOKEN_RED_OUT)
		ast_add_right(&new, just_red(scan, data));
	else
		ast_add_left(&new, just_red(scan, data));
}

t_ast	*parc_red_out(t_scanner *scan, t_ast *root, t_ast *ast, t_data *data)
{
	t_ast	*new;

	new = NULL;
	if (scan->curr_token && scan->curr_token->type == TOKEN_WORD)
	{
		new = parc_cmd(scan, data);
		ast_add_right(&new, ast);
	}
	else if (scan->curr_token && scan->curr_token->type == TOKEN_PIPE)
	{
		new = parc_word(scan, data, root);
		ast_add_right(&new, ast);
	}
	if (root)
		parc_red_in2(root, ast, new);
	else
		root = new;
	return (root);
}
