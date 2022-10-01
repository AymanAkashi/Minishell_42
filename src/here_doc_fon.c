/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_fon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:40:54 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/01 20:33:47 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_here_doc(t_token **token, t_data *data)
{
	(*token)->type = TOKEN_HEREDOC;
	data->here_doc = 1;
}

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
