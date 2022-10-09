/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:53:03 by aaggoujj          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/20 12:41:55 by aaggoujj         ###   ########.fr       */
=======
/*   Updated: 2022/10/06 20:16:01 by aaggoujj         ###   ########.fr       */
>>>>>>> origin/update
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	print_err(char *str, char *s, int fd)
{
	int i;

	i = -1;
	while(str[++i] && str[i] != '%')
=======
int	ft_exit_ps(char *str, char *str2)
{
	ft_putstr_fd(str, 1);
	if (str2[0] != '\0')
	{
		ft_putstr_fd(str2, 1);
		ft_putstr_fd("\'\n", 1);
	}
	return (0);
}

void	print_err(char *str, char *s, int fd)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '%')
>>>>>>> origin/update
		write(fd, &str[i], 1);
	if (str[i] == '%' && str[i + 1] == 's')
		ft_putstr_fd(s, fd);
	i++;
<<<<<<< HEAD
	while(str[++i])
		write(fd, &str[i], 1);
}
=======
	while (str[++i])
		write(fd, &str[i], 1);
	write(1, "\n", 1);
}
>>>>>>> origin/update
