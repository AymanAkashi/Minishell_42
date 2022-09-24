/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [parsing]parc_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:23:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/23 15:47:25 by aaggoujj         ###   ########.fr       */
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
	return (ast);
}

t_ast	*next_parc_heredoc(t_ast *root, t_ast *new, t_ast *tmp,
t_scanner *scan, t_data *data)
{
	if (root)
	{
		if (!tmp->cmd)
			tmp = new;
		else if (!root->right)
			root->right = new;
		else
			tmp->left = new;
		return (root);
	}
	else
	{
		root = parc_word(scan, data, new);
		tmp = root;
		while (tmp && tmp->left)
			tmp = tmp->left;
		if (!tmp->cmd)
			tmp = new;
		else if (!root->right)
			root->right = new;
		else
			tmp->left = new;
		return (root);
	}
}

t_ast	*parc_heredoc(t_scanner *scan, t_ast *root, t_data *data)
{
	t_ast	*new;
	t_ast	*tmp;

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
	if (!scan->curr_token && !root)
		return (new);
	tmp = root;
	while (tmp && tmp->left)
		tmp = tmp->left;
	return (next_parc_heredoc(root, new, tmp, scan, data));
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
			return (scanner_token(data->token, &scan), ast);
	}
	return (ast);
}
