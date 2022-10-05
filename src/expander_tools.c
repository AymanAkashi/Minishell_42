/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:14:40 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/05 15:22:01 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_exitstatue(char **result)
{
	char	*tmp;

	tmp = ft_itoa(g_exitstatus);
	*result = ft_strjoin2(*result, tmp);
	free(tmp);
	return (1);
}

int	expand_dou_quote(char *line, int i, char **result, t_data *data)
{
	while (line[i] && data->state == DOU_QUOTHE)
	{
		if (line[i] == '\"')
		{
			data->state = check_state(line[i +1]);
			i++;
			break ;
		}
		if (line[i] == '$')
			i = exporting(result, line, i, data);
		else
			append_char(result, line[i++]);
	}
	return (i);
}

int	expand_sin_quote(char *line, int i, t_state *state, char **result)
{
	while (line[i] && *state == SIN_QUOTHE)
	{
		if (line[i] == '\'')
		{
			*state = check_state(line[i +1]);
			i++;
			break ;
		}
		append_char(result, line[i]);
		i++;
	}
	return (i);
}
