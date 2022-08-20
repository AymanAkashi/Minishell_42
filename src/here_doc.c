/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashi <akashi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:10:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/19 22:18:11 by akashi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

char	*ft_strjoin_nl(char *str, char *dest, char c)
{
	char	*src;
	int		i;
	int		j;

	i = -1;
	if (!dest)
		return (NULL);
	if (!str)
	{
		str = ft_any_alloc(sizeof(char), 2);
		str[0] = '\0';
	}
		src = ft_any_alloc(sizeof(char), (ft_strlen(str) + ft_strlen(dest)) + 2);
	if (!src)
		return (NULL);
	while (str[++i])
		src[i] = str[i];
	if (str[0] != '\0')
		src[i++] = c;
	j = -1;
	while (dest[++j])
		src[i++] = dest[j];
	src[i] = '\0';
	free(str);
	free(dest);
	return (src);
}

void	child_here_doc(int p[2], t_token **token)
{
	char	*line;
	int		byte;

	close(p[0]);
	_reset_ctrl_handler();
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp((*token)->next->cmd, line,
				ft_strlen((*token)->next->cmd) + 1) == 0)
		{
			free (line);
			free_token(token);
			close(p[1]);
			exit(1);
		}
		if (line[0] == '\0' && (((*token)->next->cmd[0] == '\"'
			&& (*token)->next->cmd[1] == '\"') || ((*token)->next->cmd[0] == '\''
			&& (*token)->next->cmd[1] == '\'')))
			break ;
		if (!line || line[0] == '\0')
			continue ;
		else if (line)
		{
			byte = ft_strlen(line);
			write(p[1], &byte, sizeof(int));
			write (p[1], line, ft_strlen(line));
			free (line);
		}
	}
	free_token(token);
}

void	parent_here_doc(int p[2], t_token **token, int pid)
{
	char	*tmp;
	int		byte;
	int		len;

		close(p[1]);
		_ctrl_handler();
		byte = read (p[0], &len, sizeof(int));
		tmp = ft_any_alloc(sizeof(char), len + 1);
		if(!tmp)
			printf("Error\n");
		byte = read (p[0], tmp, len);
		while (byte > 0)
		{
			(*token)->here_doc = ft_strjoin_nl((*token)->here_doc, tmp, '\n');
			ft_bzero(tmp, len);
			// free(tmp);
			byte = read (p[0], &len, sizeof(int));
			tmp = ft_any_alloc(sizeof(char), len + 1);
			byte = read (p[0], tmp, len);
		}
		free(tmp);
		waitpid(pid, NULL, 0);	
		close(p[0]);
}

char	*remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 1;
	j = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = ft_any_alloc(sizeof(char), len - 1);
	if (!new)
		return (NULL);
	while (str[i] && len - 1 > i)
	{
		new[j++] = str[i];
		i++;
	}
	free(str);
	new[j] = '\0';
	return (new);
}

void	type_heredoc(t_token **token)
{
	int	pid;
	int	p[2];

	if((*token)->next->cmd)
		if ((*token)->next->cmd[0] == '\"' || (*token)->next->cmd[0] == '\'')
			(*token)->exp = 0;
	if (((*token)->next->cmd[0] == '\"' && (*token)->next->cmd[1] == '\"')
		|| ((*token)->next->cmd[0] == '\'' && (*token)->next->cmd[1] == '\''))
	{
		free((*token)->next->cmd);
		(*token)->next->cmd = ft_strdup("");
	}
	if (((*token)->next->cmd[0] == '\"'
			&& (*token)->next->cmd[ft_strlen((*token)->next->cmd) - 1] == '\"')
		|| ((*token)->next->cmd[0] == '\''
			&& (*token)->next->cmd[ft_strlen((*token)->next->cmd) - 1] == '\''))
			(*token)->next->cmd = remove_quotes((*token)->next->cmd);
	if (pipe(p) == -1)
		return ;
	pid = fork();
	if (pid == 0)
		child_here_doc(p, token);
	else
		parent_here_doc(p, token, pid);
}
