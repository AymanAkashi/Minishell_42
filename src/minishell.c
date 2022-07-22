/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 08:07:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/22 20:48:34 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		_ctrl_handler();
		line = readline("Minishell $> ");
		if (line != NULL)
		{
			add_history(line);
			if (ft_strncmp(line, "exit", 5) == 0)
				break ;
			free(line);
		}
		else
		{
			ctrl_d_handler();
		}
	}
	return (0);
}
