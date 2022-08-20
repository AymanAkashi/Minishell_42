/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 07:39:34 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/20 13:51:55 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	while (*token != NULL)
	{
		tmp = *token;
		free((*token)->cmd);
		*token = (*token)->next;
		free(tmp);
	}
	free(*token);
	*token = NULL;
}

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table && table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	free_ast(t_ast *root)
{
	if (!root)
		return ;
	if (root && root->left)
		free_ast(root->left);
	if (root && root->right)
		free_ast(root->right);
	if (root && root->args)
		free_table(root->args);
	if (root && root->cmd)
		free(root->cmd);
	root->cmd = NULL;
	root->args = NULL;
	free(root);
}
