/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 07:39:34 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 11:04:54 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void	**ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	while (*token != NULL)
	{
		tmp = *token;
		if ((*token)->type == TOKEN_HEREDOC)
		{
			free((*token)->here_doc);
			(*token)->here_doc = NULL;
		}
		if ((*token)->cmd)
		{
			free((*token)->cmd);
			(*token)->cmd = NULL;
		}
		*token = (*token)->next;
		free(tmp);
		tmp = NULL;
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
		table[i] = NULL;
		i++;
	}
	free(table);
	table = NULL;
}

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(((t_env *)tmp->content)->name);
		((t_env *)tmp->content)->name = NULL;
		free(((t_env *)tmp->content)->value);
		((t_env *)tmp->content)->value = NULL;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_ast(t_ast *root)
{
	if (!root)
		return ;
	if (root && root->left)
		free_ast(root->left);
	if (root && root->right)
		free_ast(root->right);
	free_table(root->args);
	free_null((void **)&root->cmd);
	if (root->here_doc)
		free_null((void **) &root->here_doc);
	root->here_doc = NULL;
	root->cmd = NULL;
	root->args = NULL;
	free(root);
}
