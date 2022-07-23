/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:07:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/23 23:45:19 by aaggoujj         ###   ########.fr       */
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

int	main(void)
{
	char	*line;
	t_token	*token;
	t_token	*tmp;

	while (1)
	{
		_ctrl_handler();
		line = readline("Minishell $> ");
		if (line != NULL)
		{
			token = (t_token *)malloc(sizeof(t_token));
			token->cmd = NULL;
			token->next = NULL;
			tokenizetion(&token, line);
			tmp = token;
			while (tmp != NULL)
			{
				printf("[%s]\n", tmp->cmd);
				tmp = tmp->next;
			}
			add_history(line);
			if (ft_strncmp(line, "exit", 5) == 0)
				break ;
			free(line);
			free_token(&token);
		}
		else
			ctrl_d_handler();
	}
	return (0);
}
