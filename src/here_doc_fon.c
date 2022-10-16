/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_fon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:40:54 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/12 18:00:11 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_rest_signal(int pip)
{
	close(pip);
	signal(SIGINT, sighere_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sighere_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = -1;
	while (str[++i])
		if (str[i] != '\'' && str[i] != '\"')
			j++;
	dest = ft_any_alloc(sizeof(char), j + 1);
	if (!dest)
		perror("Error allocation");
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] != '\'' && str[i] != '\"')
			dest[++j] = str[i];
	dest[++j] = '\0';
	free(str);
	return (dest);
}

void	write_heredoc(int pipe, char *line)
{
	int	byte;

	byte = ft_strlen(line);
	write(pipe, &byte, sizeof(int));
	write (pipe, line, ft_strlen(line));
}

char	*read_heredoc(int pipe, int len, int *byte)
{
	char	*tmp;

	*byte = read (pipe, &len, sizeof(int));
	tmp = ft_any_alloc(sizeof(char), len + 1);
	*byte = read (pipe, tmp, len);
	return (tmp);
}
