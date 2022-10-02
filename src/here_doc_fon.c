/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_fon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:40:54 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/02 20:52:46 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighere_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
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

void	write_heredoc(int p, char *line)
{
	int	byte;

	byte = ft_strlen(line);
	write(p, &byte, sizeof(int));
	write (p, line, ft_strlen(line));
}
char	*read_heredoc(int p, int len, int *byte)
{
	char	*tmp;

	*byte = read (p, &len, sizeof(int));
	tmp = ft_any_alloc(sizeof(char), len + 1);
	*byte = read (p, tmp, len);
	return (tmp);
}
