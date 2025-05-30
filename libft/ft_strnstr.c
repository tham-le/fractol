/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:30:56 by thi-le            #+#    #+#             */
/*   Updated: 2022/11/18 15:53:38 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * strnstr — locate a substring in a string */
/* *******************************************/
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big && little)
		return (0);
	i = ft_strlen (little);
	if (i == 0)
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] && little[j] == big[i + j] && i + j < len)
				j++;
			if (little[j] == 0)
				return ((char *)big + i);
		}
		if (++i == len)
			return (0);
	}
	return (0);
}
