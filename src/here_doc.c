/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:10:14 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/31 18:04:27 by aaggoujj         ###   ########.fr       */
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

void	parent_here_doc(int p[2], t_token **token, int pid, t_data *data)
{
	char	*tmp;
	int		byte;
	int		len;

	tmp = NULL;
	close(p[1]);
	_ctrl_handler();
	byte = read (p[0], &len, sizeof(int));
	tmp = ft_any_alloc(sizeof(char), len + 1);
	byte = read (p[0], tmp, len);
	while (byte > 0)
	{
		(*token)->here_doc = ft_strjoin_nl((*token)->here_doc, tmp, '\n');
		ft_bzero(tmp, len - 1);
		byte = read (p[0], &len, sizeof(int));
		tmp = ft_any_alloc(sizeof(char), len + 1);
		byte = read (p[0], tmp, len);
	}
	(*token)->here_doc = ft_strjoin((*token)->here_doc,"\n");
	free(tmp);
	waitpid(pid, NULL, 0);
	if ((*token)->exp == 1 && (*token)->here_doc)
		(*token)->here_doc = expand_heredoc((*token)->here_doc, data);
	close(p[0]);
}

int	search_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	return (0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = -1;
	while(str[++i])
		if (str[i] != '\'' && str[i] != '\"')
			j++;
	dest = ft_any_alloc(sizeof(char), j + 1);
	if (!dest)
		perror("Error allocation");
	i = -1;
	j = -1;
	while(str[++i])
		if(str[i] != '\'' && str[i] != '\"')
			dest[++j] = str[i];
	dest[++j] = '\0';
	free(str);
	return (dest);
}

void	type_heredoc(t_token **token, t_data *data)
{
	int	pid;
	int	p[2];

	(*token)->exp = 1;
	if((*token)->next->cmd)
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
		return ;
	pid = fork();
	if (pid == 0)
		child_here_doc(p, token);
	else
		parent_here_doc(p, token, pid, data);
}
