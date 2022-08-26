/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:35:26 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/08/26 14:40:57 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander_dollar(char *str, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i])
	{
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
	while(str[i])
	{
		if(str[i] == '$')
		{
			str = expander_dollar(str, data);
			break ;
		}
		i++;
	}
	return (str);
}