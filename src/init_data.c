/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:59:42 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/25 20:23:53 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	first_init(char **envp, t_data *data)
{
	data->env = copy_table(envp);
	alloc_envp(data, data->env,data->envp);
	add_shlvl(data);
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

void	init_data(t_data *data, char *envp[],char *line)
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
	tokenizetion(&data->token, line, data);
	add_path(data);
	add_history(line);
}