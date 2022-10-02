/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:28:04 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/02 20:53:12 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_thecmd(char **path, char *cmd)
{
	char	*tmp;
	char	*arg;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		arg = ft_strjoin(tmp, cmd);
		if (access(arg, 0) == 0)
			return (arg);
		free(arg);
		free(tmp);
		i++;
	}
	return (NULL);
}

int	check_if_path(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

int	check_cmd(char *str, t_data *data)
{
	char	*cmd;

	if (!str)
		return (0);
	if (ft_strchr(str, '/'))
	{
		return (2);
	}
	else
	{
		cmd = get_thecmd(data->path, str);
		if (cmd == NULL)
			return (0);
	}
	return (1);
}

void	set_here_doc(t_token **token, t_data *data)
{
	(*token)->type = TOKEN_HEREDOC;
	data->here_doc = 1;
}
