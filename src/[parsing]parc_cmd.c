/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [parsing]parc_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:23:56 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/27 22:35:44 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
t_ast *parc_word(t_scanner *scan, t_data *data);

t_ast *ft_create_ast()
{
	t_ast *new;

	new = malloc(sizeof(t_ast));
	new->cmd = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast *parc_opera(t_scanner *scan, t_ast *ast, t_data *data)
{
	t_ast *new;

	new = ft_create_ast();
	new->left = ast;
	if (scan->next_token == TOKEN_WORD)
		new->right = parc_word(scan, data);
	return (new);
}

void	parcing(t_data *data)
{
	scanner_token(data->token, &data->scanner);
	// data->ast = ft_create_ast(0);
 	while (data->scanner->curr_token)
	{
		if (data->scanner->curr_token->type == TOKEN_WORD)
			data->root = parc_word(data->scanner, data);
		else if (data->scanner->curr_token->type == TOKEN_AND
			|| data->scanner->curr_token->type == TOKEN_OR)
			data->root = parc_opera(data->scanner, data->root, data);
	}
}

char *ft_alloc_cmd(char *str, char *str2)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	i = -1;
	if(!str)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(str2) + 2;
	dest = ft_any_alloc(sizeof(char), len);
	while(str[++i])
		dest[i] = str[i];
	j = -1;
	dest[i++] = ' ';
	if(str2)
	while(str2[++j])
		dest[j + 1] = str2[j];
	dest[j + i] = '\0';
	return (dest);
}

char	**alloc_tab(t_data *data, t_type_token type)
{
	int i;
	char **tab;
	t_token *tmp;

	i = 0;
	tmp = data->token;
	while (data->token && data->token->type == type)
	{
		data->token = data->token->next;
		i++;
	}
	tab = ft_any_alloc(sizeof(char *), i + 1);
	data->token = tmp;
	return (tab);
}

t_ast *parc_word(t_scanner *scan, t_data *data)
{
	int	i;
	t_ast *ast;
	t_ast *root;

	ast = ft_create_ast();
	root = NULL;
	i = 0;
	while (scan->curr_token && scan->curr_token)
	{
		if (scan->curr_token->type == TOKEN_WORD)
		{
			ast->cmd = ft_strdup(scan->curr_token->cmd);
			ast->args= alloc_tab(data, TOKEN_WORD);
			ast->args[i++] = ft_strdup(scan->curr_token->cmd);
			ast->type = TOKEN_WORD;
			scanner_token(scan->curr_token, &scan);
			while(scan->curr_token && scan->curr_token->type == TOKEN_WORD)
			{
				ast->args[i++] = ft_strdup(scan->curr_token->cmd);
				scanner_token(data->token, &scan);
			}
		}
		else if (scan->curr_token->type == TOKEN_PIPE)
		{
			root = ft_create_ast();
			root->cmd = ft_strdup("|");
			root->left = ast;
			root->type = TOKEN_PIPE;
			scanner_token(scan->curr_token, &scan);
			root->right = parc_word(scan, data);
			scanner_token(scan->curr_token, &scan);
			return (root);
		}
		else
		{
			if(root)
				return (root);
			else
				return (ast);
		}
	}
	scanner_token(scan->curr_token, &scan);
	return(ast);
}
