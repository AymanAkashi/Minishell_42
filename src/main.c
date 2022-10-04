/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:56:22 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/04 16:13:27 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_data *data, int pos)
{
	if (pos >= 1)
	{
		free_ast(data->ast);
		free_token(&data->token);
		// free_table(data->path);
		// free(data->scanner);
	}
	if (pos == 2)
	{
		free_list(data->envp);
	}
}

int	line_check(t_data *data, char *line)
{
	if (!check_line(data->token, data, line))
	{
		free_all(data, 1);
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
	line = NULL;
	while (1)
	{
		data.root = NULL;
		_ctrl_handler();
		line = readline("\001\x1B[1;1;33m\002Minishell $> \001\e[00m\002");
		if (line != NULL && line[0] != '\0')
		{
			init_data(&data, envp, line);
			if (!line_check(&data, line))
				continue ;
			beg_minishell(&data);
			free_all(&data, 1);
		}
		else if (line == NULL)
			ctrl_d_handler(&data);
		free(line);
	}
	_restctrl();
	free_all(&data, 2);
	free(line);
	return (0);
}
