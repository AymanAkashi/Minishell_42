/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 07:39:34 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/29 11:13:22 by aaggoujj         ###   ########.fr       */
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
			free((*token)->here_doc);
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

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(((t_env *)tmp->content)->name);
		free(((t_env *)tmp->content)->value);
		free(tmp->content);
		free(tmp);
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
	if (root && root->args)
		free_table(root->args);
	if (root && root->cmd)
		free(root->cmd);
	root->cmd = NULL;
	root->args = NULL;
	free(root);
}

void	free_all(t_data *data)
{
	free_ast(data->ast);
	free_token(&data->token);
	// free_list(data->envp);
	free(data->path);
	// free(data);
}