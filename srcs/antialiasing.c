/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:00:00 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/25 10:00:00 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Helper function to calculate iterations at a specific complex point
int	calculate_fractal_iterations(t_data *data, t_complex c)
{
	t_complex	z;
	int			iteration;

	z = init_complex(0, 0);
	iteration = 0;
	while (iteration < data->max_iter)
	{
		if (data->fractal_index == MANDELBROT)
		{
			data->z2.re = z.re * z.re - z.im * z.im;
			data->z2.im = 2 * z.re * z.im;
			z.re = data->z2.re + c.re;
			z.im = data->z2.im + c.im;
		}
		else if (data->fractal_index == JULIA)
		{
			data->z2.re = z.re * z.re - z.im * z.im;
			data->z2.im = 2 * z.re * z.im;
			z.re = data->z2.re + data->c.re;
			z.im = data->z2.im + data->c.im;
		}
		else if (data->fractal_index == TRICORN)
		{
			data->z2.re = z.re * z.re - z.im * z.im;
			data->z2.im = -2 * z.re * z.im;
			z.re = data->z2.re + c.re;
			z.im = data->z2.im + c.im;
		}
		if ((z.re * z.re + z.im * z.im) > 4)
			break;
		iteration++;
	}
	return (iteration);
}

// Get iterations at pixel coordinates
int	get_iterations_at_pixel(t_data *data, int x, int y)
{
	t_complex	point;

	point.re = data->min.re + x * data->delta.re;
	point.im = data->max.im - y * data->delta.im;
	return (calculate_fractal_iterations(data, point));
}

// Simple 2x2 supersampling for anti-aliasing
int	get_antialiased_color(t_data *data, int x, int y)
{
	double		sample_offsets[4][2] = {{0.25, 0.25}, {0.75, 0.25}, 
		{0.25, 0.75}, {0.75, 0.75}};
	int			total_r;
	int			total_g;
	int			total_b;
	int			i;

	total_r = 0;
	total_g = 0;
	total_b = 0;
	i = 0;
	while (i < 4)
	{
		t_complex	sub_point;
		int			iterations;
		int			sample_color;

		sub_point.re = data->min.re + (x + sample_offsets[i][0]) * data->delta.re;
		sub_point.im = data->max.im - (y + sample_offsets[i][1]) * data->delta.im;
		iterations = calculate_fractal_iterations(data, sub_point);
		sample_color = get_enhanced_color(iterations, data);
		total_r += (sample_color >> 16) & 0xFF;
		total_g += (sample_color >> 8) & 0xFF;
		total_b += sample_color & 0xFF;
		i++;
	}
	return (create_trgb(0, total_r / 4, total_g / 4, total_b / 4));
}

// Check if a pixel needs anti-aliasing based on edge detection
int	needs_antialiasing(t_data *data, int x, int y)
{
	int	center;
	int	neighbors[4];
	int	i;

	if (x == 0 || y == 0 || x >= W_WIDTH - 1 || y >= W_HEIGHT - 1)
		return (0);
	center = get_iterations_at_pixel(data, x, y);
	neighbors[0] = get_iterations_at_pixel(data, x - 1, y);
	neighbors[1] = get_iterations_at_pixel(data, x + 1, y);
	neighbors[2] = get_iterations_at_pixel(data, x, y - 1);
	neighbors[3] = get_iterations_at_pixel(data, x, y + 1);
	i = 0;
	while (i < 4)
	{
		if (abs(center - neighbors[i]) > data->max_iter * 0.1)
			return (1);
		i++;
	}
	return (0);
}

// Anti-aliasing enabled color function
void	color_with_antialiasing(t_data *data, int n, int x, int y)
{
	int	final_color;

	if (data->fractal_index == BARNSLEY)
		data->color_shift = data->color_shift % 3 + 3;
	if (n == data->max_iter && data->fractal_index != BARNSLEY)
		my_mlx_pixel_put(data, x, y, 0x0000000);
	else
	{
		if (needs_antialiasing(data, x, y))
			final_color = get_antialiased_color(data, x, y);
		else if (data->color_shift <= 2)
			final_color = get_color_default(n, data);
		else if (data->color_shift < 6)
			final_color = get_color_palette(n, data);
		else
			final_color = get_enhanced_color(n, data);
		my_mlx_pixel_put(data, x, y, final_color);
	}
}
