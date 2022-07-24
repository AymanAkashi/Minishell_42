/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 18:39:29 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/07/24 23:55:53 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_any_alloc(size_t size, size_t len)
{
	void	*ptr;

	ptr = malloc(size * len);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, size * len);
	return (ptr);
}

void	alloc_token(t_token **token)
{
	(*token)->next = ft_any_alloc(sizeof(t_token), 1);
	(*token) = (*token)->next;
}
