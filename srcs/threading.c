/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:00:00 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 18:00:00 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/*
* Get optimal number of threads based on system capabilities
* Uses the number of CPU cores but caps it at MAX_THREADS
*/
int	get_optimal_threads(void)
{
	long	num_threads;

	num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (num_threads <= 0)
		num_threads = NUM_THREADS;
	if (num_threads > MAX_THREADS)
		num_threads = MAX_THREADS;
	return ((int)num_threads);
}
