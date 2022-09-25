/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:56:22 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/24 20:10:08 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_check(t_data *data, char *line)
{
	if (!check_line(data->token, data, line))
	{
		free_all(data);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	(void)ac, (void)av;
	first_init(envp, &data);
	while (1)
	{
		_ctrl_handler();
		line = readline("\001\x1B[1;1;33m\002Minishell $> \001\e[00m\002");
		if (line != NULL && line[0] != '\0')
		{
			init_data(&data, envp, line);
			if (!line_check(&data, line))
				continue ;
			beg_minishell(&data);
			free_all(&data);
		}
		else if (line == NULL)
			ctrl_d_handler(&data);
		free(line);
	}
	_restctrl();
	free_all(&data);
	free(line);
	return (0);
}
