/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:35:26 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/01 11:06:01 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_caracter(char c)
{
	if ((c >= '?' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'
		|| c == ' ' || c == '\t' || c == '\"' || c == '\'')
		return (1);
	return (0);
}

char	*expander_dollar(char *str, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i])
	{
		while (str[i] == '$' && str[i + 1] == '$')
			append_char(&result, str[i++]);
		if (str[i] == '$')
			i = exporting(&result, str, i, data);
		else
			append_char(&result, str[i++]);
	}
	return (result);
}

char	*expand_heredoc(char *str, t_data *data)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == '$' && str[i + 1] == '$')
			i++;
		if (str[i] == '$' && type_caracter(str[i + 1]))
		{
			str = expander_dollar(str, data);
			break ;
		}
		i++;
	}
	return (str);
}
