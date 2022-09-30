/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:07:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/30 18:33:00 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitstatus;

//************____Test_Tokenization____*****************//
void	test_tokenization(t_token *token)
{
	t_token	*tmp;
	char *str[] = {"word","pipe","red_out","red_in",
			"red2_out","heredoc","and","or","paren_in","paren_out"};

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == TOKEN_HEREDOC)
		printf("[%s]-->[%s] == %s\n", tmp->cmd,str[tmp->type],tmp->here_doc);
		else
		printf("[%s]-->[%s]\n", tmp->cmd,str[tmp->type]);
		tmp = tmp->next;
	}
}
//********************************************************/

//************************Test_scanner********************//
// void	test_scanner(t_data *data)
// {
// 	t_token *token;

// 	token = data->token;
// 	t_scanner	*scan = NULL;
// 	char *str[] = {"word","pipe","red_out","red_in",
// 			"red2_out","heredoc","and","or","paren_in","paren_out"};

// 	scanner_token(token, &scan);
// 	while(scan)
// 	{
// 		printf("[%s]-->[%s]\n", scan->curr_token->cmd,
// 				 str[scan->curr_token->type]);
// 		if(scan->next_token)
// 			printf("[%s]-->[%s]\n", scan->next_token->cmd,
// 			str[scan->next_token->type]);
// 		printf("--------------------------\n");
// 		scanner_token(token, &scan);
// 		if(!scan->next_token)
// 				break;
// 	}
// }
//********************************************************/

//************************Test_parcing********************//

void	disp(t_ast *tree, int ident, char *str, t_data *data) {
	if (!tree) return ;
	for (int i = 0; i < ident; i++)
		printf("---- ");
	if (tree && tree->type == TOKEN_WORD && tree->cmd) {
		if(!ft_strcmp(tree->cmd, "export"))
			sort_list(data->envp, data->envp);
		else
			printf("[%s]%s",str, tree->cmd);
	}
	else if (tree->type == TOKEN_PIPE && tree->cmd) {
		printf("[%s]PIPE",str);
	}
	else if (tree->type == TOKEN_AND && tree->cmd)
		printf("[%s] AND", str);
	else if (tree->type == TOKEN_OR && tree->cmd)
		printf("[%s] OR", str);
	else if (tree->type == TOKEN_RED_OUT && tree->cmd)
		printf("[%s] REDIR_OUT", str);
	else if (tree->type == TOKEN_RED_IN && tree->cmd)
		printf("[%s] REDIR_IN", str);
	else if (tree->type == TOKEN_RED2_OUT && tree->cmd)
		printf("[%s] REDIR2_OUT", str);
	else if (tree->type == TOKEN_HEREDOC && tree->cmd)
		printf("[%s] HEREDOC = %s", str, tree->here_doc);
	else if (tree->type == TOKEN_PAREN_IN)
		printf("(");
	else if (tree->type == TOKEN_PAREN_OUT)
		printf(")");
	printf("\n");
	disp(tree->left, ident + 1, "left",data);
	disp(tree->right, ident + 1, "Right",data);
}

//********************************************************/

int	size_ast(t_ast *ast)
{
	t_ast	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ast;
	while (tmp)
	{
		i++;
		tmp = tmp->right;
	}
	tmp = ast;
	while (tmp)
	{
		j++;
		tmp = tmp->left;
	}
	if (j > i)
		return (j);
	else
		return (i);
}

int	add_here_doc(t_token **token, t_data *data)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			if (!type_heredoc(&tmp, data))
				return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	beg_minishell(t_data *data)
{
	if (data->here_doc == 1)
		if (!add_here_doc(&data->token, data))
			return ;
	// test_tokenization(data->token);
	scanner_token(data->token, &data->scanner);
	data->root = parcing(data, data->root, data->scanner);
	// disp(data->root, 0, "root", data);
	execution(data, data->root);
	wait_all(0);
	_hidectrl();
}
