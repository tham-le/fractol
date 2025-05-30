/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:21:46 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 17:21:44 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	tricorn(t_data *f)
{
	int			x;
	int			y;
	int			n;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		f->c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			f->c.re = f->min.re + x * f->delta.re;
			f->z = f->c;
			f->z2 = f->z ;
			n = -1;
			while ((++n < f->max_iter) && (f->z2.re + f->z2.im < 4))
			{
				f->z2 = init_complex(f->z.re * f->z.re, f->z.im * f->z.im);
				f->z = init_complex(f->z2.re - f->z2.im + f->c.re,
						-2 * f->z.re * f->z.im + f->c.im);
			}
			color(f, n, x, y);
		}
	}
}

void	*tricorn_thread(void *thread_data)
{
	t_thread_data	*td = (t_thread_data *)thread_data;
	t_data			*f = td->data;
	int				x;
	int				y;
	int				n;
	t_complex		c;
	t_complex		z;
	t_complex		z2;

	y = td->start_y - 1;
	while (++y < td->end_y)
	{
		x = -1;
		c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			c.re = f->min.re + x * f->delta.re;
			z = c;
			z2 = z;
			n = -1;
			while ((++n < f->max_iter) && (z2.re + z2.im < 4))
			{
				z2 = init_complex(z.re * z.re, z.im * z.im);
				z = init_complex(z2.re - z2.im + c.re,
						-2 * z.re * z.im + c.im);
			}
			color(f, n, x, y);
		}
	}
	return (NULL);
}

void	tricorn_threaded(t_data *f)
{
	pthread_t		threads[MAX_THREADS];
	t_thread_data	thread_data[MAX_THREADS];
	int				i;
	int				rows_per_thread;
	int				remaining_rows;
	int				num_threads;

	num_threads = get_optimal_threads();
	rows_per_thread = W_HEIGHT / num_threads;
	remaining_rows = W_HEIGHT % num_threads;
	
	i = -1;
	while (++i < num_threads)
	{
		thread_data[i].data = f;
		thread_data[i].thread_id = i;
		thread_data[i].start_y = i * rows_per_thread;
		thread_data[i].end_y = (i + 1) * rows_per_thread;
		if (i == num_threads - 1)
			thread_data[i].end_y += remaining_rows;
		pthread_create(&threads[i], NULL, tricorn_thread, &thread_data[i]);
	}
	
	i = -1;
	while (++i < num_threads)
		pthread_join(threads[i], NULL);
}
