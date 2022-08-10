/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [parsing]parc_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:23:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/07 15:35:59 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast	*ft_create_ast(void)
{
	t_ast	*new;

	new = ft_any_alloc(sizeof(t_ast), 1);
	new->here_doc = NULL;
	new->cmd = NULL;
	new->left = NULL;
	new->right = NULL;
	new->in = 0;
	new->out = 0;
	return (new);
}

void	ast_here_doc(t_ast **ast, t_scanner *scan, t_data *data)
{	(*ast)->here_doc = ft_strdup(scan->curr_token->here_doc);
	free(scan->curr_token->here_doc);
	scan->curr_token->here_doc = NULL;
	(*ast)->type = scan->curr_token->type;
	(*ast)->cmd = ft_strdup(scan->curr_token->cmd);
	(*ast)->args = ft_any_alloc(sizeof(char *), 3);
	(*ast)->args[0] = ft_strdup(scan->curr_token->cmd);
	(*ast)->type = scan->curr_token->type;
	scanner_token(data->token, &scan);
	
	(*ast)->args[1] = ft_strdup(scan->curr_token->cmd);
	(*ast)->args[2] = NULL;
}

t_ast	*parc_heredoc(t_scanner *scan, t_ast *root, t_data *data)
{
	t_ast	*new;
	t_ast	*tmp;

	new = ft_create_ast();
	if (scan->curr_token && scan->curr_token->type == TOKEN_HEREDOC)
		ast_here_doc(&new, scan, data);
	else
	{
		new->cmd = ft_strdup(scan->curr_token->cmd);
		new->args = ft_any_alloc(sizeof(char *), 3);
		new->args[0] = ft_strdup(scan->curr_token->cmd);
		new->type = scan->curr_token->type;
		new->args[1] = ft_strdup(scan->curr_token->cmd);
		scanner_token(data->token, &scan);
		new->args[2] = NULL;
	}
	scanner_token(data->token, &scan);
	tmp = root;
	while (tmp && tmp->left)
		tmp = tmp->left;
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
		if (root)
			free_ast(root);
		root = parc_word(scan, data, new);
		if (!root->cmd)
			return (new);
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
	return (root);
}

t_ast	*parcing(t_data *data, t_ast *ast, t_scanner **scan)
{
	scanner_token(data->token, scan);
	if (!scan && (*scan)->curr_token->cmd == NULL)
		return (NULL);
	while ((*scan)->curr_token)
	{
		if ((*scan)->curr_token->type == TOKEN_WORD
			|| (*scan)->curr_token->type == TOKEN_PIPE)
		{
			if (ast && ast->cmd != NULL)
				ast = parc_word(*scan, data, ast);
			else
				ast = parc_word(*scan, data, NULL);
		}
		else if ((*scan)->curr_token->type == TOKEN_AND
			|| (*scan)->curr_token->type == TOKEN_OR)
			ast = parc_opera(*scan, ast, data);
		else if ((*scan)->curr_token->type == TOKEN_HEREDOC
			|| (*scan)->curr_token->type == TOKEN_RED_IN
			|| (*scan)->curr_token->type == TOKEN_RED_OUT
			|| (*scan)->curr_token->type == TOKEN_RED2_OUT)
			ast = parc_heredoc(*scan, ast, data);
		else if ((*scan)->curr_token->type == TOKEN_PAREN_IN)
		{
			if (!ast)
				ast = parc_paren(*scan, ast, data);
			else
				ast->left = parc_paren(*scan, ast, data);
		}
		else if ((*scan)->curr_token->type == TOKEN_PAREN_OUT)
		{
			scanner_token(data->token, scan);
			return (ast);
		}
	}
	return (ast);
}
