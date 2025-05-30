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
int	calculate_fractal_iterations(t_data *data, t_complex c_pixel)
{
	t_complex	z_iter; // Renamed z to z_iter to avoid confusion with data->z
	int			iteration;

	// Initialize z_iter based on the fractal type
	if (data->fractal_index == JULIA)
		z_iter = c_pixel; // For Julia, z starts as the pixel coordinate, c is data->c
	else // For Mandelbrot, Tricorn, Burning Ship (if added here), z starts at 0
		z_iter = init_complex(0, 0);
	
	iteration = 0;
	while (iteration < data->max_iter)
	{
		double temp_re, temp_im;
		if (data->fractal_index == MANDELBROT)
		{
			temp_re = z_iter.re * z_iter.re - z_iter.im * z_iter.im + c_pixel.re;
			temp_im = 2 * z_iter.re * z_iter.im + c_pixel.im;
			z_iter.re = temp_re;
			z_iter.im = temp_im;
		}
		else if (data->fractal_index == JULIA)
		{
			// For Julia, c_pixel is the initial z, data->c is the constant
			temp_re = z_iter.re * z_iter.re - z_iter.im * z_iter.im + data->c.re;
			temp_im = 2 * z_iter.re * z_iter.im + data->c.im;
			z_iter.re = temp_re;
			z_iter.im = temp_im;
		}
		else if (data->fractal_index == TRICORN)
		{
			temp_re = z_iter.re * z_iter.re - z_iter.im * z_iter.im + c_pixel.re;
			temp_im = -2 * z_iter.re * z_iter.im + c_pixel.im; // Conjugate's imaginary part
			z_iter.re = temp_re;
			z_iter.im = temp_im;
		}
		// Add other fractals here if they are to be anti-aliased by this function
		// e.g., Burning Ship:
		/* else if (data->fractal_index == BURNING_SHIP)
		{
			double abs_re = fabs(z_iter.re);
			double abs_im = fabs(z_iter.im);
			temp_re = abs_re * abs_re - abs_im * abs_im + c_pixel.re;
			temp_im = 2 * abs_re * abs_im + c_pixel.im;
			z_iter.re = temp_re;
			z_iter.im = temp_im;
		} */

		if ((z_iter.re * z_iter.re + z_iter.im * z_iter.im) > 4)
		{
			data->z2 = z_iter; // Store the z that escaped, for smooth coloring
			break;
		}
		iteration++;
	}
	if (iteration == data->max_iter) // If it didn't escape
	{
		data->z2 = z_iter; // Store the last z, for smooth coloring
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
