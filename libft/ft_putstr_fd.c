/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:29:57 by thi-le            #+#    #+#             */
/*   Updated: 2022/11/16 14:08:50 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ((void) NULL);
	while (*s)
		write(fd, s++, 1);
}

void	ft_putnstr_fd(char *s, int fd, int n)
{
	if (s == NULL)
		return ((void) NULL);
	while (*s && n-- > 0)
		write(fd, s++, 1);
}
