/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:39:29 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/06 12:07:00 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_any_alloc(size_t size, size_t len)
{
	void	*ptr;

	ptr = ft_calloc(len, size);
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*ft_alloc_cmd(char *str, char *str2)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	i = -1;
	if (!str)
		return (NULL);
	len = ft_strlen(str) + ft_strlen(str2) + 2;
	dest = ft_any_alloc(sizeof(char), len);
	while (str[++i])
		dest[i] = str[i];
	j = -1;
	dest[i++] = ' ';
	if (str2)
		while (str2[++j])
			dest[j + 1] = str2[j];
	dest[j + i] = '\0';
	return (dest);
}

void	move_to_next_n(t_token **token, int n)
{
	while (n > 0)
	{
		(*token) = (*token)->next;
		n--;
	}
}

char	**alloc_tab(t_data *data, t_type_token type, t_token *token)
{
	int		i;
	char	**tab;
	t_token	*tmp;

	i = 0;
	tmp = data->token;
	while (tmp && tmp != token)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	while (tmp && (tmp->type == type || is_redirection(tmp->type)))
	{
		while (tmp && is_redirection(tmp->type))
			move_to_next_n(&tmp, 2);
		if (!tmp)
			break ;
		tmp = tmp->next;
		i++;
	}
	tab = ft_any_alloc(sizeof(char *), i + 1);
	return (tab);
}

void	alloc_token(t_token **token)
{
	(*token)->next = ft_any_alloc(sizeof(t_token), 1);
	(*token) = (*token)->next;
}
