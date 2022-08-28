/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:47:21 by yjarhbou          #+#    #+#             */
/*   Updated: 2022/08/27 20:15:27 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_pwd(void)
{
	char *result;

	result = getcwd(NULL, 0);
	printf("%s\n", result);
	if (!result)
		return 1;
	return 0;
}



