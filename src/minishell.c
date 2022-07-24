/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:07:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/24 23:58:05 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token **token)
{
	t_token	*tmp;

	while (*token != NULL)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp);
	}
	*token = NULL;
}

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

int	main(void)
{
	char	*line;
	t_token	*token;

	while (1)
	{
		_ctrl_handler();
		line = readline("Minishell $> ");
		if (line != NULL && line[0] != '\0')
		{
			token = (t_token *)malloc(sizeof(t_token));
			token->cmd = NULL;
			token->next = NULL;
			tokenizetion(&token, line);
			// test_tokenization(token);
			add_history(line);
			if (ft_strncmp(line, "exit", 5) == 0)
				break ;
			free(line);
			free_token(&token);
		}
		else if (line == NULL)
			ctrl_d_handler();
	}
	return (0);
}
