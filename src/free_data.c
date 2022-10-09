/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:21:11 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/07 15:21:36 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data, int pos)
{
	if (pos >= 1)
	{
		free_ast(data->root);
		if (data->token && data->token->cmd)
			free_token(&data->token);
		else
			free(data->token);
		free(data->scanner);
	}
	if (pos == 2)
	{
		free_table(data->path);
		free_list(data->envp);
	}
}

void	free_signal(t_data *data)
{
	if (data->root)
		free_ast(data->root);
	if (data->token && data->token->cmd)
		free_token(&data->token);
	else
		free(data->token);
	free_table(data->path);
	free_list(data->envp);
}