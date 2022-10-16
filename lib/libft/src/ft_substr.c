/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjarhbou <yjarhbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 10:45:49 by aaggoujj          #+#    #+#             */
/*   Updated: 2022/10/16 01:32:11 by yjarhbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_submalloc(char *str, size_t i)
{
	str = (char *)malloc(sizeof(char) * i);
	if (!str)
		return (ft_exit3(ALLOCATION_FAILED, 1), NULL);
	ft_bzero(str, i);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*str;
	size_t			end;

	str = NULL;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	end = start + len;
	if (ft_strlen(s) - start <= len)
		str = ft_submalloc(str, (ft_strlen(s) - start));
	else
		str = ft_submalloc(str, len + 1);
	if (!str)
		return (exit(1), NULL);
	j = 0;
	if (start <= ft_strlen(s))
		while (start < end && s[start] != '\0')
			str[j++] = s[start++];
	return (str);
}
/*
#include<stdio.h>

int main()
{
    char *str = "1";
    char* dest = ft_substr(ft_strdup(str), 42, 42000000);

    printf("%s\n", dest);

    return 0;
}*/
