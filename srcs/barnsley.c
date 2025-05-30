/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barnsley.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:12:31 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 14:58:34 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

static void	next_point(t_complex *x, int r)
{
	t_complex	next;

	if (r < 2)
	{
		next.re = 0;
		next.im = 0.16 * x->im;
	}
	else if (r < 87)
	{
		next.re = 0.85 * x->re + 0.04 * x->im;
		next.im = -0.04 * x->re + 0.85 * x->im + 1.6;
	}
	else if (r < 94)
	{
		next.re = 0.2 * x->re - 0.26 * x->im;
		next.im = 0.23 * x->re + 0.22 * x->im + 1.6;
	}
	else
	{
		next.re = -0.15 * x->re + 0.28 * x->im;
		next.im = 0.26 * x->re + 0.24 * x->im + 0.44;
	}
	x->re = next.re;
	x->im = next.im;
}

void	barnsley(t_data *data)
{
	int			i;
	t_complex	x;

	white_image(data);
	i = -1;
	while (++i < data->max_iter)
	{
		x.re = ((int)((data->c.re - data->min.re) / data->delta.re));
		x.im = -1 * ((int)((data->c.im - data->max.im) / data->delta.im));
		if (x.re < W_WIDTH && x.im < W_HEIGHT && x.re > 0 && x.im > 0)
			color(data, i % 3, x.re, x.im);
		next_point(&data->c, rand() % 101);
	}
}
