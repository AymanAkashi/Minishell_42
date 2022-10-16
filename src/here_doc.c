/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:10:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 18:02:12 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

char	*ft_strjoin_nl(char *str, char *dest)
{
	char	*src;
	char	*tmp;

	tmp = NULL;
	if (!dest)
		return (NULL);
	if (str)
		tmp = ft_strjoin2(str, "\n");
	src = ft_strjoin2(tmp, dest);
	return (src);
}

int	check_empty_line(char *str)
{
	if (str && ((str[0] == '\"' && str[1] == '\"' && str[2] == '\0')
			|| (str[0] == '\'' && str[1] == '\'' && str[2] == '\0')))
		return (1);
	return (0);
}

void	child_here_doc(int p[2], t_token **token)
{
	char	*line;

	close(p[0]);
	__reset_sig(1);
	while (1)
	{
		line = readline("heredoc> ");
		if ((ft_strcmp((*token)->next->cmd, line) == 0) || !line)
			child_eof(line, token, p[1]);
		if (line[0] == '\0' && check_empty_line((*token)->next->cmd))
		{
			free_token(token);
			exit(2);
		}
		if (!line || line[0] == '\0')
		{
			line = ft_strdup("\n");
			write_heredoc(p[1], line);
		}
		else if (line)
			write_heredoc(p[1], line);
		free(line);
	}
	free_token(token);
	exit(1);
}

int	parent_here_doc(int p[2], t_token **token, int pid, t_data *data)
{
	char			*tmp;
	int				byte;
	static int		len;

	parent_rest_signal(p[1]);
	tmp = read_heredoc(p[0], len, &byte);
	while (byte > 0)
	{
		if (!strcmp(tmp, "\n"))
		{
			free(tmp);
			tmp = ft_strdup("");
		}
		(*token)->here_doc = ft_strjoin_nl((*token)->here_doc, tmp);
		free(tmp);
		tmp = read_heredoc(p[0], len, &byte);
	}
	(*token)->here_doc = ft_strjoin2((*token)->here_doc, "\n");
	free(tmp);
	waitpid(pid, &len, 0);
	if (WIFSIGNALED(len))
		return (0);
	if ((*token)->exp == 1 && (*token)->here_doc)
		(*token)->here_doc = expand_heredoc((*token)->here_doc, data);
	return (close(p[0]), 1);
}

int	type_heredoc(t_token **token, t_data *data, char *eof)
{
	int	pid;
	int	p[2];

	(*token)->exp = 1;
	if ((*token)->next->cmd)
		if (search_quote((*token)->next->cmd))
			(*token)->exp = 0;
	if ((eof[0] == '\"' && eof[1] == '\"' && eof[2] == '\0')
		|| (eof[0] == '\'' && eof[1] == '\'' && eof[2] == '\0'))
	{
		free((*token)->next->cmd);
		(*token)->next->cmd = ft_strdup("");
	}
	if (search_quote((*token)->next->cmd))
			(*token)->next->cmd = remove_quotes((*token)->next->cmd);
	if (pipe(p) == -1)
		return (print_err("Error Pipe:", NULL, 2), 0);
	pid = fork();
	if (pid == 0)
		child_here_doc(p, token);
	else
		if (!parent_here_doc(p, token, pid, data))
			return (0);
	return (1);
}
