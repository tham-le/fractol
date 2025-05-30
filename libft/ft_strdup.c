/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:06:19 by thi-le            #+#    #+#             */
/*   Updated: 2022/11/16 15:10:50 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* The  strdup()  function returns a pointer to a new string which is a 
duplicate of the string s.  Memory for the new string is ob‐
       tained with malloc(3), and can be freed with free(3). */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	char			*str;

	len = ft_strlen(s);
	str = (char *)malloc(len * sizeof(char) + 1);
	if (!str)
		return (0);
	str = ft_memcpy(str, s, len + 1);
	return (str);
}
