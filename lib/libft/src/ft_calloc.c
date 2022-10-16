/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 09:55:28 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/16 01:29:13 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc( size_t size, size_t num)
{
	void	*ptr;

	ptr = (void *)malloc(num * size);
	if (!ptr)
		return (ft_exit3(ALLOCATION_FAILED, 1), NULL);
	ft_bzero (ptr, num * size);
	return (ptr);
}
