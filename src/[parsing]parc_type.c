/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [parsing]parc_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:19:17 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/20 15:13:18 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parc_opera(t_scanner *scan, t_ast *ast, t_data *data)
{
	t_ast	*new;

	new = ft_create_ast();
	new->cmd = ft_strdup(scan->curr_token->cmd);
	new->type = scan->curr_token->type;
	new->left = ast;
	scanner_token(data->token, &scan);
	if (scan->curr_token && (scan->curr_token->type == TOKEN_WORD
			|| scan->curr_token->type == TOKEN_PIPE))
		new->right = parc_word(scan, data, NULL);
	else if (scan->curr_token && scan->curr_token->type == TOKEN_PAREN_IN)
		new->right = parc_paren(scan, NULL, data);
	return (new);
}

void	add_ast(t_ast *ast, t_ast *new)
{
	if (ast && ast->type == TOKEN_WORD && (ast->left == NULL || ast->right == NULL))
	{
		if (ast->left == NULL)
			ast->left = new;
		else if (ast->right == NULL)
			ast->right = new;
	}
	else
	{
	if (ast && ast->left)
		add_ast(ast->left, new);
	if(ast && ast->right)
		add_ast(ast->right, new);
	}
}

void	add_redirection(t_ast *ast, t_scanner *scan, t_data *data)
{
	t_ast *new;

	new = ft_create_ast();
	if (scan->curr_token && scan->curr_token->type == TOKEN_HEREDOC)
		new = ast_here_doc(new, scan, data);
	else
	{
		new->cmd = ft_strdup(scan->curr_token->cmd);
		new->args = ft_any_alloc(sizeof(char *), 3);
		new->args[0] = ft_strdup(scan->curr_token->cmd);
		new->type = scan->curr_token->type;
		scanner_token(data->token, &scan);
		new->args[1] = ft_strdup(scan->curr_token->cmd);
		new->args[2] = NULL;
	}
	scanner_token(data->token, &scan);
	add_ast(ast, new);
}

t_ast	*parc_paren(t_scanner *scan, t_ast *ast, t_data *data)
{
	t_ast	*new;

	data->state = PARENT;
	new = ft_create_ast();
	new->in = 1;
	scanner_token(data->token, &scan);
	new = parcing(data, ast, scan);
	if(is_redirection(scan->curr_token->type))
		add_redirection(new, scan, data);
	if (scan->curr_token && scan->curr_token->type == TOKEN_PAREN_OUT)
	{
		data->state = DEFAULT;
		return (new);
	}
	if (ast)
		ast->left = new;
	else
	{
		ast = parcing(data, ast, scan);
		if(!ast)
			ast = new;
		else
			ast_add_left(&ast, new);
	}
	data->state = DEFAULT;
	return (ast);
}

t_ast	*parc_pipe(t_scanner *scan, t_data *data, t_ast *root, t_ast *ast)
{
	t_ast	*new;

	new = ft_create_ast();
	new->cmd = ft_strdup(scan->curr_token->cmd);
	new->type = scan->curr_token->type;
	if (ast && ast->cmd)
		new->left = ast;
	else if (root && root->cmd
		&& (root->type == TOKEN_OR || root->type == TOKEN_AND))
		new->left = root->right;
	else if (data->state == DEFAULT && root)
		new->left = root;
	scanner_token(scan->curr_token, &scan);
	if (scan->curr_token && scan->curr_token->type == TOKEN_WORD)
		new->right = parc_word(scan, data, NULL);
	if (scan->curr_token && scan->curr_token->type == TOKEN_PAREN_IN)
		new->right = parc_paren(scan, NULL, data);
	return (new);
}

t_ast	*parc_cmd(t_scanner *scan, t_data *data)
{
	t_ast	*new;
	int		i;

	i = 0;
	new = ft_create_ast();
	new->cmd = ft_strdup(scan->curr_token->cmd);
	new->args = alloc_tab(data, TOKEN_WORD, scan);
	new->args[i++] = ft_strdup(scan->curr_token->cmd);
	new->type = TOKEN_WORD;
	scanner_token(scan->curr_token, &scan);
	while (scan->curr_token && (scan->curr_token->type == TOKEN_WORD
			|| is_redirection(scan->curr_token->type)))
	{
		if (is_redirection(scan->curr_token->type))
			new = parc_heredoc(scan, new, data);
		else
		{
			new->args[i++] = ft_strdup(scan->curr_token->cmd);
			scanner_token(scan->curr_token, &scan);
		}
	}
	return (new);
}

t_ast	*parc_word(t_scanner *scan, t_data *data, t_ast *root)
{
	t_ast	*ast;

	// ast = ft_create_ast();
	while (scan->curr_token)
	{
		if (scan->curr_token->type == TOKEN_WORD)
			ast = parc_cmd(scan, data);
		else if (scan->curr_token->type == TOKEN_PIPE)
		{
			if (root && (root->type == TOKEN_OR || root->type == TOKEN_AND))
			{
				root->right = parc_pipe(scan, data, root, ast);
				return (root);
			}
			else
				return (parc_pipe(scan, data, root, ast));
		}
		else
			return (ast);
	}
	return (ast);
}
