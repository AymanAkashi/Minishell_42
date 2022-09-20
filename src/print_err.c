/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:53:03 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/20 12:41:55 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err(char *str, char *s, int fd)
{
	int i;

	i = -1;
	while(str[++i] && str[i] != '%')
		write(fd, &str[i], 1);
	if (str[i] == '%' && str[i + 1] == 's')
		ft_putstr_fd(s, fd);
	i++;
	while(str[++i])
		write(fd, &str[i], 1);
}