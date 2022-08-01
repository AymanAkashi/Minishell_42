/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:07:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/01 16:26:20 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//************____Test_Tokenization____*****************//
// void	test_tokenization(t_token *token)
// {
// 	t_token	*tmp;
// 	char *str[] = {"word","pipe","red_out","red_in",
// 			"red2_out","heredoc","and","or","paren_in","paren_out"};

// 	tmp = token;
// 	while (tmp != NULL)
// 	{
// 		printf("[%s]-->[%s]\n", tmp->cmd,str[tmp->type_token]);
// 		tmp = tmp->next;
// 	}
// }
//********************************************************/

//************************Test_scanner********************//
void	test_scanner(t_data *data)
{
	t_token *token;

	token = data->token;
	t_scanner	*scan = NULL;
	char *str[] = {"word","pipe","red_out","red_in",
			"red2_out","heredoc","and","or","paren_in","paren_out"};

	scanner_token(token, &scan);
	while(scan)
	{
		printf("[%s]-->[%s]\n", scan->curr_token->cmd,
				 str[scan->curr_token->type]);
		if(scan->next_token)
			printf("[%s]-->[%s]\n", scan->next_token->cmd,
			str[scan->next_token->type]);
		printf("--------------------------\n");
		scanner_token(token, &scan);
		if(!scan->next_token)
				break;
	}
}
//********************************************************/

//************************Test_parcing********************//

char *ft_str_len_char(char c, int len)
{
	char *str;
	int i;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		str[i] = c;
		i++;
		str[i] = '\n';
	}
	str[i] = '\0';
	return (str);
}


t_ast*	test_parcing(t_data *data, t_ast *root, int len)
{
	static int i;
	t_ast *ast;

	i = 2;
	ast = root;
	printf("%s(%s)\n",ft_str_len_char(' ', len - 1), ast->cmd);
	while(root)
	{
		if (root->left)
			printf("%s /",ft_str_len_char(' ', len / 2 + 1));
		if (root->right)
			printf("%s \\\n",ft_str_len_char(' ', len / 2 - 1));
		if (root->left->type == TOKEN_WORD)
			printf("%s[%s]",ft_str_len_char(' ', len / 2), root->left->cmd);
		if (root->right->type == TOKEN_WORD)
			printf("%s[%s]\n",ft_str_len_char(' ', len / 2 - 2), root->right->cmd);
		if (root->left->type != TOKEN_WORD)
			root = test_parcing(data, root->left, len / 2);
		if (root->right->type != TOKEN_WORD)
			root = test_parcing(data, root->right, len * 2);
		return (root);
	}
	i += 2;
	test_parcing(data, root->left, len / i);
	test_parcing(data, root->right, len / i);
	return (root);
		// if(data->root->right)
		// {
		// }
		// data->root = data->root->right;
		// sleep(1);
	// }
	// while (ast)
	// {
	// 	printf("LEft[%s]\n", ast->cmd);
	// 	ast = ast->left;
	// 	sleep(1);
	// }
}

void disp(t_ast *tree, int ident, char *str) {
	if (!tree) return ;
	// for (int i = 0; i < ident; i++){
	// 	printf("%s", ft_str_len_char('|', ident));
	// }
	for (int i = 0; i < ident; i++)
		printf("---- ");
	if (tree->type == TOKEN_WORD && tree->cmd) {
		printf("[%s]%s",str, tree->cmd);
	}
	else if (tree->type == TOKEN_PIPE && tree->cmd) {
		printf("PIPE");
	}
	else if (tree->type == TOKEN_AND && tree->cmd)
		printf("AND");
	else if (tree->type == TOKEN_OR && tree->cmd)
		printf("OR");
	else if (tree->type == TOKEN_RED_OUT && tree->cmd)
		printf("REDIR_OUT");
	else if (tree->type == TOKEN_RED_IN && tree->cmd)
		printf("REDIR_IN");
	else if (tree->type == TOKEN_RED2_OUT && tree->cmd)
		printf("REDIR2_OUT");
	else if (tree->type == TOKEN_HEREDOC && tree->cmd)
		printf("HEREDOC");
	else if (tree->type == TOKEN_PAREN_IN)
		printf("(");
	else if (tree->type == TOKEN_PAREN_OUT)
		printf(")");
	printf("\n");
	disp(tree->left, ident + 1, "left");
	disp(tree->right, ident + 1, "Right");
}

//********************************************************/

int size_ast(t_ast *ast)
{
	t_ast *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = ast;
	while(tmp)
	{
		i++;
		tmp = tmp->right;
	}
	tmp= ast;
	while(tmp)
	{
		j++;
		tmp = tmp->left;
	}
	if(j > i)
		return (j);
	else
		return (i);
}

void	init_data(t_data *data)
{
	data->token = (t_token *)malloc(sizeof(t_token));
	data->scanner = NULL;
	data->token->cmd = NULL;
	data->token->next = NULL;
	data->root = NULL;
}

int	main(void)
{
	char	*line;
	t_data	data;

	while (1)
	{
		_ctrl_handler();
		line = readline("\001\x1B[1;1;33m\002Minishell $> \001\e[00m\002");
		if(line != NULL && line[0] != '\0')
		{
			init_data(&data);
			tokenizetion(&data.token, line, &data);
			add_history(line);
			if (!check_line(data.token, &data, line))
			{
				free(line);
				free_token(&data.token);
				free(data.token);
				continue ;
			}
			// test_tokenization(data.token);
			data.root = parcing(&data, data.root, data.scanner);
			disp(data.root,0, "ROOT");
			// test_scanner(&data);
			if (ft_strncmp(line, "exit", 5) == 0)
				break ;
			free_token(&data.token);
			free_ast(data.root);
			free(data.scanner);
		}
		else if (line == NULL)
			ctrl_d_handler(&data);
		free(line);
	}
	free_token(&data.token);
	free(data.token);
	free_ast(data.root);
	free(data.scanner);
	free(line);
	return (0);
}
