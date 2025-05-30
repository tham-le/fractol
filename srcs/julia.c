/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:21:46 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/22 14:55:08 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_data *f)
{
	t_complex	x;
	int			n;

	x.im = -1;
	while (++x.im < W_HEIGHT)
	{
		x.re = -1;
		while (++x.re < W_WIDTH)
		{
			f->z.im = f->max.im - x.im * f->delta.im;
			f->z.re = f->min.re + x.re * f->delta.re;
			n = -1;
			while ((++n < f->max_iter) && (f->z.re * f->z.re + f->z.im * f->z.im < 4))
			{
				double temp_re = f->z.re * f->z.re - f->z.im * f->z.im + f->c.re;
				double temp_im = 2 * f->z.re * f->z.im + f->c.im;
				f->z.re = temp_re;
				f->z.im = temp_im;
			}
			color(f, n, x.re, x.im, f->z);
		}
	}
}

void	*julia_thread(void *thread_data)
{
	t_thread_data	*td = (t_thread_data *)thread_data;
	t_data		*f = td->data;
	t_complex	x, z;
	int			n;

	x.im = td->start_y - 1;
	while (++x.im < td->end_y)
	{
		x.re = -1;
		while (++x.re < W_WIDTH)
		{
			z.im = f->max.im - x.im * f->delta.im;
			z.re = f->min.re + x.re * f->delta.re;
			n = -1;
			while ((++n < f->max_iter) && (z.re * z.re + z.im * z.im < 4))
			{
				double temp_re = z.re * z.re - z.im * z.im + f->c.re;
				double temp_im = 2 * z.re * z.im + f->c.im;
				z.re = temp_re;
				z.im = temp_im;
			}
			color(f, n, x.re, x.im, z);
		}
	}
	return (NULL);
}

void	julia_threaded(t_data *f)
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
		pthread_create(&threads[i], NULL, julia_thread, &thread_data[i]);
	}
	
	i = -1;
	while (++i < num_threads)
		pthread_join(threads[i], NULL);
}
