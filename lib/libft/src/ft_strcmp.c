/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:51:29 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/01 19:42:20 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!str1 || !str2)
		return (-1);
	while ((str1[i] != '\0' || str2[i] != '\0') && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
