/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [parsing]parc_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:19:17 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/04 16:30:38 by aaggoujj         ###   ########.fr       */
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
	new->args = NULL;
	scanner_token(data->token, &scan);
	if (scan->curr_token && (scan->curr_token->type == TOKEN_WORD
			|| scan->curr_token->type == TOKEN_PIPE))
		new->right = parc_word(scan, data, NULL);
	else if (scan->curr_token && scan->curr_token->type == TOKEN_PAREN_IN)
		new->right = parc_paren(scan, NULL, data);
	return (new);
}

t_ast	*parc_paren(t_scanner *scan, t_ast *ast, t_data *data)
{
	t_ast	*new;

	data->state = PARENT;
	new = ft_create_ast();
	scanner_token(data->token, &scan);
	new = parcing(data, NULL, scan);
	if (scan->curr_token && is_redirection(scan->curr_token->type))
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
		ast = parcing(data, NULL, scan);
		if (!ast)
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
	new->args = NULL;
	if (ast && ast->cmd)
		new->left = ast;
	else if (root && root->cmd
		&& (root->type == TOKEN_OR || root->type == TOKEN_AND))
		new->left = root->right;
	else if (root)
		new->left = root;
	scanner_token(scan->curr_token, &scan);
	if (scan->curr_token && scan->curr_token->type == TOKEN_WORD)
		new->right = parc_word(scan, data, NULL);
	if (scan->curr_token && scan->curr_token->type == TOKEN_PAREN_IN)
		new->right = parc_paren(scan, NULL, data);
	return (new);
}

char	**d_alloc_tabs(char **args, char *str)
{
	char	**d_table;
	int		i;

	i = -1;
	if (!args || !args[0])
	{
		d_table = ft_calloc(sizeof(char *), 2);
		d_table[0] = ft_strdup(str);
		d_table[1] = NULL;
		return (d_table);
	}
	while (args[++i])
		i++;
	d_table = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (args[++i])
		d_table[i] = ft_strdup(args[i]);
	d_table[i++] = ft_strdup(str);
	d_table[i] = NULL;
	free_table(args);
	return (d_table);
}

t_ast	*parc_cmd(t_scanner *scan, t_data *data)
{
	t_ast	*new;
	int		i;

	i = 0;
	new = ft_create_ast();
	new->cmd = ft_strdup(scan->curr_token->cmd);
	new->args = d_alloc_tabs(new->args, scan->curr_token->cmd);
	new->type = TOKEN_WORD;
	scanner_token(scan->curr_token, &scan);
	while (scan->curr_token && (scan->curr_token->type == TOKEN_WORD
			|| is_redirection(scan->curr_token->type)))
	{
		if (is_redirection(scan->curr_token->type))
		{
			if (scan->curr_token->type == TOKEN_RED2_OUT || scan->curr_token->type == TOKEN_RED_OUT)
				ast_add_right(&new, just_red(scan, data));
			else
				ast_add_left(&new, just_red(scan, data));
		}
		else
		{
			new->args = d_alloc_tabs(new->args, scan->curr_token->cmd);
			scanner_token(scan->curr_token, &scan);
		}
	}
	return (new);
}

t_ast	*parc_word(t_scanner *scan, t_data *data, t_ast *root)
{
	t_ast	*ast;

	ast = NULL;
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
