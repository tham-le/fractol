/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:22:43 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/22 17:41:02 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_print_error(char *desc, int error)
{
	ft_putendl(desc);
	exit(error);
}
