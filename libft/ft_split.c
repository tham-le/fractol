/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:21:35 by thi-le            #+#    #+#             */
/*   Updated: 2022/11/23 14:47:24 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*sdup(const char *str, int n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (0);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static int	count(const char *s, char c)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (s[i - 1])
	{
		if ((s[i] == c || s[i] == 0) && s[i - 1] != c)
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char		**strings;
	size_t		len;
	size_t		i;
	size_t		j;

	strings = ft_calloc(count(s, c) + 1, sizeof(char *));
	len = 0;
	j = 0;
	i = 0;
	while (j < ft_strlen(s) + 1)
	{
		if (s[j] != c && s[j] != 0)
			len++;
		if (len && (s[j] == c || s[j] == 0))
		{
			strings[i] = sdup(&s[j] - len, len);
			len = 0;
			i++;
		}
		j++;
	}
	return (strings);
}
