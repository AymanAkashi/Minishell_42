/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 09:55:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/04 11:34:39 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc( size_t size, size_t num)
{
	void	*ptr;

	ptr = (void *)malloc(num * size);
	if (!ptr)
		return (NULL);
	ft_bzero (ptr, num * size);
	return (ptr);
}
