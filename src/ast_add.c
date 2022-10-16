/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:23:07 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 18:08:54 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_add_left(t_ast **ast, t_ast *new)
{
	t_ast	*left;

	if (!*ast)
		*ast = new;
	else
	{
		left = *ast;
		while (left->left)
			left = left->left;
		left->left = new;
	}
}

void	ast_add_right(t_ast **ast, t_ast *new)
{
	t_ast	*right;

	if (!*ast)
		*ast = new;
	else
	{
		right = *ast;
		while (right->right)
			right = right->right;
		right->right = new;
	}
}

void	add_ast(t_ast *ast, t_ast *new)
{
	if (ast && ast->type == TOKEN_WORD
		&& (ast->left == NULL || ast->right == NULL))
	{
		if (ast->left == NULL)
			ast->left = copy_ast(new);
		else if (ast->right == NULL)
			ast->right = copy_ast(new);
	}
	else
	{
		if (ast->type == TOKEN_PIPE && (new->type == TOKEN_RED_OUT
				|| new->type == TOKEN_RED2_OUT))
			add_ast(ast->right, new);
		else
		{
			if (ast && ast->left)
				add_ast(ast->left, new);
			if (ast && ast->right)
				add_ast(ast->right, new);
		}
	}
}

void	add_redirection(t_ast *ast, t_scanner *scan, t_data *data)
{
	t_ast	*new;

	new = ft_create_ast();
	if (scan->curr_token && scan->curr_token->type == TOKEN_HEREDOC)
		new = ast_here_doc(new, scan, data);
	else
	{
		new->cmd = ft_strdup(scan->curr_token->cmd);
		new->args = ft_any_alloc(sizeof(char *), 4);
		new->args[0] = ft_strdup(scan->curr_token->cmd);
		new->type = scan->curr_token->type;
		scanner_token(data->token, &scan);
		new->args[1] = ft_strdup(scan->curr_token->cmd);
		new->args[2] = NULL;
	}
	scanner_token(data->token, &scan);
	add_ast(ast, new);
}

int	check_envp(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	if (i > 3)
		return (1);
	return (0);
}
