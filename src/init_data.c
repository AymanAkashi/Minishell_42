/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:59:42 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/07 09:19:28 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_path(t_data *data)
{
	char	*value;

	if (data->found_env == 0 && data->check_path == 0)
	{
		data->path = ft_split(_PATH_STDPATH, ':');
		data->check_path++;
	}
	else
	{
		value = search_env("PATH", data);
		data->path = ft_split(value, ':');
		free(value);
	}
	if (!data->path)
		perror(*data->path);
}

char	**copy_table(char **envp)
{
	char	**dest;
	int		i;

	i = 0;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
		i++;
	dest = ft_calloc(i + 1, sizeof(char **));
	i = -1;
	while (envp[++i])
		dest[i] = ft_strdup(envp[i]);
	dest[i] = NULL;
	return (dest);
}

void	first_init(char **envp, t_data *data)
{
	data->root = NULL;
	data->env = copy_table(envp);
	alloc_envp(data, data->env, data->envp);
	add_shlvl(data);
	add_path(data);
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
	(void)envp;
	data->token = (t_token *)malloc(sizeof(t_token));
	data->scanner = NULL;
	data->token->cmd = NULL;
	data->token->here_doc = NULL;
	data->token->next = NULL;
	data->root = NULL;
	data->dou_quothe = 0;
	data->sin_quothe = 0;
	data->here_doc = 0;
	data->num_heredoc = 0;
	data->state = DEFAULT;
	init_print_env(data->envp);
	tokenizetion(&data->token, line, data);
	add_history(line);
}
