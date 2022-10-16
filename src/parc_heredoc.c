/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parc_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:04:46 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 16:02:53 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_ast	*parc_redirection(t_scanner *scan, t_ast *root, t_data *data)
{
	t_ast	*ast;
	t_ast	*new;

	new = ft_create_ast();
	if (scan->curr_token && scan->curr_token->type == TOKEN_HEREDOC)
		new = ast_here_doc(new, scan, data);
	else
		new = ast_red(data, scan, new);
	scanner_token(data->token, &scan);
	multi_red(new, data, scan);
	if (scan->curr_token && scan->curr_token->type == TOKEN_WORD)
	{
		ast = parc_cmd(scan, data);
		if (new->type == TOKEN_HEREDOC || new->type == TOKEN_RED_IN)
			ast_add_left(&ast, new);
		else
			ast_add_right(&ast, new);
		return (ast);
	}
	else
		return (new);
	return (root);
}
