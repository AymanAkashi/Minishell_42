/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:55:53 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/23 12:56:05 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_init(char **envp, t_data *data)
{
	data->env = copy_table(envp);
	alloc_envp(data, data->env,data->envp);
	// add_path(data);
	g_exitstatus = 0;
	_hidectrl();
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

void	init_data(t_data *data, char *envp[], char *line)
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
	add_path(data);
	tokenizetion(&data->token, line, data);
	add_history(line);
}