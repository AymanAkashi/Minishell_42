/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [parsing]parc_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:23:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/01 20:51:35 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast	*ft_create_ast(void)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	new->cmd = NULL;
	new->left = NULL;
	new->right = NULL;
	new->here_doc = NULL;
	new->in = 0;
	new->out = 1;
	new->exp = 1;
	return (new);
}

t_ast	*ast_here_doc(t_ast *ast, t_scanner *scan, t_data *data)
{
	ast->here_doc = ft_strdup(scan->curr_token->here_doc);
	ast->type = scan->curr_token->type;
	ast->exp = scan->curr_token->exp;
	ast->cmd = ft_strdup(scan->curr_token->cmd);
	ast->args = ft_any_alloc(sizeof(char *), 3);
	ast->args[0] = ft_strdup(scan->curr_token->cmd);
	ast->type = scan->curr_token->type;
	scanner_token(data->token, &scan);
	ast->args[1] = ft_strdup(scan->curr_token->cmd);
	ast->args[2] = NULL;
	data->num_heredoc++;
	return (ast);
}

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
	else
		root = new;
	return (root);
}

t_ast	*parc_red_here(t_scanner *scan, t_ast *root, t_ast *ast, t_data *data)
{
	t_ast	*new;

	new = NULL;
	if (!scan->curr_token)
		ast_add_left(&root, ast);
	if (scan->curr_token && (scan->curr_token->type == TOKEN_WORD
			|| scan->curr_token->type == TOKEN_PIPE))
	{
		ast_add_left(&root, ast);
		root = parc_word(scan, data, root);
	}
	if (scan->curr_token && (scan->curr_token->type == TOKEN_AND
			|| scan->curr_token->type == TOKEN_OR))
	{
		ast_add_left(&root, ast);
		root = parc_opera(scan, root, data);
	}
	return (root);
}

t_ast	*parc_red_out(t_scanner *scan, t_ast *root, t_ast *ast, t_data *data)
{
	t_ast	*new;

	new = NULL;
	if (!scan->curr_token)
		ast_add_right(&root, ast);
	else if (scan->curr_token && (scan->curr_token->type == TOKEN_WORD
			|| scan->curr_token->type == TOKEN_PIPE))
	{
		ast_add_right(&root, ast);
		root = parc_word(scan, data, root);
	}
	else if (scan->curr_token && (scan->curr_token->type == TOKEN_AND
			|| scan->curr_token->type == TOKEN_OR))
	{
		ast_add_right(&root, ast);
		root = parc_opera(scan, root, data);
	}
	else
		ast_add_right(&root, ast);
	return (root);
}

void	multi_red(t_ast *new, t_data *data, t_scanner *scan)
{
	while ((new->type == TOKEN_RED_IN || new->type == TOKEN_HEREDOC)
		&& scan->curr_token && (scan->curr_token->type == TOKEN_RED_IN
			|| scan->curr_token->type == TOKEN_HEREDOC))
		ast_add_left(&new, just_red(scan, data));
	while ((new->type == TOKEN_RED2_OUT || new->type == TOKEN_RED_OUT)
		&& scan->curr_token && (scan->curr_token->type == TOKEN_RED2_OUT
			|| scan->curr_token->type == TOKEN_RED_OUT))
		ast_add_right(&new, just_red(scan, data));
}

t_ast	*ast_red(t_data *data, t_scanner *scan, t_ast *new)
{
	new->cmd = ft_strdup(scan->curr_token->cmd);
	new->args = ft_any_alloc(sizeof(char *), 3);
	new->args[0] = ft_strdup(scan->curr_token->cmd);
	new->type = scan->curr_token->type;
	scanner_token(data->token, &scan);
	new->args[1] = ft_strdup(scan->curr_token->cmd);
	new->args[2] = NULL;
	return (new);
}

t_ast	*parc_heredoc(t_scanner *scan, t_ast *root, t_data *data)
{
	t_ast	*new;

	new = ft_create_ast();
	if (scan->curr_token && scan->curr_token->type == TOKEN_HEREDOC)
		new = ast_here_doc(new, scan, data);
	else
		new = ast_red(data, scan, new);
	scanner_token(data->token, &scan);
	multi_red(new, data, scan);
	if (!scan->curr_token && !root)
		return (new);
	if (new->type == TOKEN_RED_IN)
		root = parc_red_in(scan, root, new, data);
	else if (new->type == TOKEN_RED2_OUT || new->type == TOKEN_RED_OUT)
		root = parc_red_out(scan, root, new, data);
	else if (new->type == TOKEN_HEREDOC)
		ast_add_left(&root, new);
	return (root);
}

t_ast	*parcing(t_data *data, t_ast *ast, t_scanner *scan)
{
	ast = NULL;
	if (!scan && scan->curr_token->cmd == NULL)
		return (NULL);
	while (scan->curr_token)
	{
		if (scan->curr_token->type == TOKEN_WORD
			|| scan->curr_token->type == TOKEN_PIPE)
		{
			if (ast && ast->cmd != NULL)
				ast = parc_word(scan, data, ast);
			else
				ast = parc_word(scan, data, NULL);
		}
		else if (scan->curr_token->type == TOKEN_AND
			|| scan->curr_token->type == TOKEN_OR)
			ast = parc_opera(scan, ast, data);
		else if (is_redirection(scan->curr_token->type))
			ast = parc_heredoc(scan, ast, data);
		else if (scan->curr_token->type == TOKEN_PAREN_IN)
		{
			if (!ast)
				ast = parc_paren(scan, ast, data);
			else
				ast->left = parc_paren(scan, ast, data);
		}
		else if (scan->curr_token->type == TOKEN_PAREN_OUT)
		{
			scanner_token(data->token, &scan);
			return (ast);
		}
	}
	if (ast == NULL || ast->cmd == NULL)
		return (NULL);
	return (ast);
}
