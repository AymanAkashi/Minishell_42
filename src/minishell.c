/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:07:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/03 16:21:43 by aaggoujj         ###   ########.fr       */
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
// 		printf("[%s]-->[%s]\n", tmp->cmd,str[tmp->type]);
// 		tmp = tmp->next;
// 	}
// }
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
			ft_export_new(data);
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

void	init_print_env(t_list *env)
{
	t_env	*e;

	while (env)
	{
		e = env->content;
		e->print = 0;
		env = env->next;
	}
}

void	init_data(t_data *data, char *envp[])
{
	data->token = (t_token *)malloc(sizeof(t_token));
	data->scanner = NULL;
	data->token->cmd = NULL;
	data->token->here_doc = NULL;
	data->token->next = NULL;
	data->root = NULL;
	data->env = envp;
	data->dou_quothe = 0;
	data->sin_quothe = 0;
	data->here_doc = 0;
	init_print_env(data->envp);
	//********PAth test*********************//
	// for (int i = 0; data->path[i]; i++)
	// 	printf("[%d]==%s\n",i,data->path[i]);
	// //***********************envp**************************//
	// t_env *e;
	// t_list *lst;
	// lst = data->envp;
	// for (int i = 0;data->envp; i++)
	// {
	// 	e = data->envp->content;
	// 	printf("[name]%s === [value]%s\n", e->name, e->value);
	// 	data->envp = data->envp->next;
	// }
	// data->envp = lst  ;
	// //************************ *****************************//
}

void	add_here_doc(t_token **token, t_data *data)
{
	t_token *tmp;

	tmp = *token;
	while(tmp && tmp->type != TOKEN_HEREDOC)
		tmp = tmp->next;
	type_heredoc(&tmp, data);
}

char **copy_table(char **envp)
{
	char **dest;
	int i;

	i = 0;
	while (envp[i])
		i++;
	dest = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (envp[++i])
		dest[i] = ft_strdup(envp[i]);
	dest[i] = NULL;
	return (dest);
}


int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	(void)ac, (void)av;
	data.env = copy_table(envp);
	alloc_envp(&data, data.env,data.envp);
	add_path(&data);
	g_exitstatus = 0;
	_hidectrl();
	while (1)
	{
		_ctrl_handler();
		line = readline("\001\x1B[1;1;33m\002Minishell $> \001\e[00m\002");
		if (line != NULL && line[0] != '\0')
		{
			init_data(&data, envp);
			if (ft_strncmp(line, "exit", 5) == 0)
				break ;
			tokenizetion(&data.token, line, &data);
			add_history(line);
			if (!check_line(data.token, &data, line))
			{
				free(line);
				free_token(&data.token);
				free(data.token);
				continue ;
			}
			if (data.here_doc == 1)
				add_here_doc(&data.token, &data);
			scanner_token(data.token, &data.scanner);
			data.root = parcing(&data, data.root, data.scanner);
			// disp(data.root, 0, "ROOT", &data);
			execution(&data, data.root);
			// wait_all();
			_hidectrl();
			free_token(&data.token);
			free_ast(data.root);
			free(data.scanner);
		}
		else if (line == NULL)
			ctrl_d_handler(&data);
		free(line);
	}
	_restctrl();
	free_token(&data.token);
	free_ast(data.root);
	free(data.scanner);
	free(line);
	return (0);
}
