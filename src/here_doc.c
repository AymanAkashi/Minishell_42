/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:10:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/02 20:50:48 by aaggoujj         ###   ########.fr       */
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
	if (str && ((str[0] == '\"' && str[1] == '\"')
			|| (str[0] == '\'' && str[1] == '\'')))
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
		if (ft_strncmp((*token)->next->cmd, line,
				ft_strlen((*token)->next->cmd) + 1) == 0)
		{
			free (line);
			free_token(token);
			close(p[1]);
			exit(1);
		}
		if (line[0] == '\0' && check_empty_line((*token)->next->cmd))
			break ;
		if (!line || line[0] == '\0')
			continue ;
		else if (line)
			write_heredoc(p[1], line);
		free(line);
	}
	free_token(token);
	exit(1);
}

int	parent_here_doc(int p[2], t_token **token, int pid, t_data *data)
{
	char	*tmp;
	int		byte;
	int		len;

	tmp = NULL;
	len = 0;
	close(p[1]);
	signal(SIGINT, sighere_handler);
	signal(SIGQUIT, SIG_IGN);
	tmp = read_heredoc(p[0], len, &byte);
	while (byte > 0)
	{
		(*token)->here_doc = ft_strjoin_nl((*token)->here_doc, tmp);
		// ft_bzero(tmp, len - 1);
		tmp = read_heredoc(p[0], len, &byte);
	}
	(*token)->here_doc = ft_strjoin((*token)->here_doc, "\n");
	free(tmp);
	waitpid(pid, &len, 0);
	if (WIFSIGNALED(len))
		return (0);
	if ((*token)->exp == 1 && (*token)->here_doc)
		(*token)->here_doc = expand_heredoc((*token)->here_doc, data);
	close(p[0]);
	return (1);
}

int	type_heredoc(t_token **token, t_data *data)
{
	int	pid;
	int	p[2];

	(*token)->exp = 1;
	if ((*token)->next->cmd)
		if (search_quote((*token)->next->cmd))
			(*token)->exp = 0;
	if (((*token)->next->cmd[0] == '\"' && (*token)->next->cmd[1] == '\"')
		|| ((*token)->next->cmd[0] == '\'' && (*token)->next->cmd[1] == '\''))
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
