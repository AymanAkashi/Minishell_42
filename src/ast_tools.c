/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:43:52 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 17:45:43 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*last_ast(t_ast *root)
{
	t_ast	*ast;

	ast = root;
	if (!ast)
		return (NULL);
	if (ast->right == NULL && ast->left == NULL)
		return (ast);
	else if (ast->left && !ast->right)
		return (ast->left);
	else
		return (last_ast(ast->right));
}

char	**copy_args(char **args)
{
	char	**new;
	int		i;

	i = 0;
	while (args[i])
		i++;
	new = ft_any_alloc(sizeof(char *), i + 1);
	i = -1;
	while (args[++i])
		new[i] = ft_strdup(args[i]);
	new[i] = NULL;
	return (new);
}

t_ast	*copy_ast(t_ast *ast)
{
	t_ast	*new;

	new = ft_create_ast();
	new->cmd = ft_strdup(ast->cmd);
	new->type = ast->type;
	new->args = copy_args(ast->args);
	return (new);
}

void	add_pipe(t_ast *ast)
{
	if (ast->left)
		ast->left->in = ast->in;
	if (ast->right)
		ast->right->in = ast->in;
}

void	add_pipe2(t_ast *ast, int *pip)
{
	if (ast->right)
		ast->right->in = pip[0];
	if (ast->left)
		ast->left->out = pip[1];
}
