/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 07:39:34 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/26 15:48:52 by aaggoujj         ###   ########.fr       */
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
	*token = NULL;
}

// void	free_ast(t_data *data)
// {
// 	t_ast	*tmp;
// 	t_ast	*tmp2;

// 	tmp = data->ast;
// 	tmp = data->ast;
// 	while (data->ast != NULL)
// 	{
// 		tmp = data->ast;
// 		data->ast = data->ast->left;
// 		free();
// 		free(tmp);
// 	}
// 	data->ast = NULL;
// }