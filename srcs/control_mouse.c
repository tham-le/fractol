/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:42:50 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 18:01:15 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int	zoom(int button, int x, int y, t_data *data)
{
	t_complex	mouse;
	double		interpolation;
	double		zoom;

	mouse = init_complex(
			(double)x / (W_WIDTH / (data->max.re - data->min.re))
			+ data->min.re,
			(double)y / (W_HEIGHT / (data->max.im - data->min.im))
			* -1 + data->max.im);
	if (button == SCROLL_UP)
		zoom = 0.85;
	else
		zoom = 1.15;
	interpolation = 1.0 / zoom;
	data->min.re = interpolate(mouse.re, data->min.re, interpolation);
	data->min.im = interpolate(mouse.im, data->min.im, interpolation);
	data->max.re = interpolate(mouse.re, data->max.re, interpolation);
	data->max.im = interpolate(mouse.im, data->max.im, interpolation);
	render_fractal(data);
	return (0);
}

int	change_param(int x, int y, t_data *data)
{
	data->c = init_complex(
			4 * ((double)x / W_WIDTH - 0.5),
			4 * ((double)(W_HEIGHT - y) / W_HEIGHT - 0.5));
	render_fractal(data);
	return (0);
}

int	change_julia(t_data *data)
{
	const double	set[13][2] = {{-0.4, 0.6}, {0.285, 0.0}, {0.285, 0.01},
	{0.54, 0.1428}, {-0.70176, -0.3842}, {-0.835, -0.2321},
	{-0.8, 0.156}, {-0.7269, 0.1889}, {0, -0.8}, {0.37, 0.1}, {0.355, 0.355},
	{0.355534, 0.337292}, {-1.34882125854492, -0.454237874348958}};

	data->julia_set = (data->julia_set + 1) % 13;
	data->c = init_complex (set[data->julia_set][0], data->julia_set[set][1]);
	render_fractal(data);
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	if ((button == SCROLL_UP || button == SCROLL_DOWN))
		zoom(button, x, y, data);
	if (button == LEFT_CLICK)
		change_param(x, y, data);
	if (button == RIGHT_CLICK)
		change_julia(data);
	return (0);
}
