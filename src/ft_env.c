/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaggoujj <aaggoujj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:53:27 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/09/20 20:03:53 by aaggoujj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *data)
{
	t_env	*e;
	t_list	*lst;

	lst = data->envp;
	while (lst)
	{
		e = lst->content;
		printf("%s=%s\n", e->name, e->value);
		lst = lst->next;
	}
}