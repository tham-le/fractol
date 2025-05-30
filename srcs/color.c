/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:18:20 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 17:13:18 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/*static int	g_rainbow[7][3] = {{255, 0, 0}, {255, 165, 0},
									{255, 255, 0}, {0, 128, 0},
	{0, 0, 255}, {75, 0, 130}, {238, 130, 238}};
*/

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_color_default(int n, t_data *data)
{
	t_color	color;

	if (n == 0)
		n++;
	color.channel[0] = 0;
	color.channel[(0 + data->color_shift) % 3 + 1]
		= 14 * (data ->max_iter % n);
	color.channel[(1 + data->color_shift) % 3 + 1]
		= 5 * (data ->max_iter % (2 * n));
	color.channel[(2 + data->color_shift) % 3 + 1]
		= (int8_t)(125 * n / data ->max_iter);
	return (create_trgb(color.channel[0], color.channel[1], color.channel[2],
			color.channel[3]));
}

int	get_color_palette(int n, t_data *data)
{
	const int	rainbow[7] = {0XFF0000, 0XFF7F00,
		0XFFFF00, 0X00FF00, 0X0000FF, 0X4B0082, 0X9400D3};
	const int	pal_2[5] = {0X99B898, 0XFECEAB, 0XFF847C, 0XE84A5F,
		0X2A3638};
	const int	beach[5] = {0X96ceb4, 0Xffeead, 0Xff6f69, 0Xffcc5c, 0X88d8b0};

	if (data -> color_shift == 3)
		return (rainbow[(int)(n % 7)]);
	if (data -> color_shift == 4)
		return (pal_2[(int)((n / 5) % 5)]);
	if (data -> color_shift == 5)
		return (beach[(n / 5) % 5]);
	return (0);
}

int	get_color_2(int iteration, t_data *data)
{
	double	t;
	t_color	color;

	t = (double)iteration / data->max_iter;
	color.channel[0] = 0;
	color.channel[(0 + data->color_shift) % 3 + 1]
		= (int8_t)(4 * (1 - t) * pow(t, 3) * 255);
	color.channel[(1 + data->color_shift) % 3 + 1]
		= (int8_t)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	color.channel[(2 + data->color_shift) % 3 + 1]
		= (int8_t)(8.5 * pow((1 - t), 3) * t * 255);
	return (create_trgb(color.channel[0], color.channel[1], color.channel[2],
			color.channel[3]));
}

// HSV to RGB conversion for smooth gradients
int	hsv_to_rgb(double h, double s, double v)
{
	double	c, x, m;
	double	r, g, b;
	int		h_sector;

	c = v * s;
	h_sector = (int)(h / 60.0) % 6;
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	m = v - c;
	
	if (h_sector == 0) { r = c; g = x; b = 0; }
	else if (h_sector == 1) { r = x; g = c; b = 0; }
	else if (h_sector == 2) { r = 0; g = c; b = x; }
	else if (h_sector == 3) { r = 0; g = x; b = c; }
	else if (h_sector == 4) { r = x; g = 0; b = c; }
	else { r = c; g = 0; b = x; }
	
	return create_trgb(0, (int)((r + m) * 255), (int)((g + m) * 255), (int)((b + m) * 255));
}

// Smooth color interpolation
int	get_smooth_color(double iteration, t_data *data)
{
	double	smooth_iter;
	double	t;
	double	h, s, v;

	if (iteration >= data->max_iter)
		return (0x000000);
	
	// Use magnitude of z for smooth coloring
	double magnitude = sqrt(data->z2.re + data->z2.im);
	smooth_iter = iteration + 1 - log(log(magnitude)) / log(2);
	t = fmod(smooth_iter * 0.05, 1.0);
	
	// Create smooth HSV gradient
	h = fmod((t * 360.0 + data->color_shift * 40), 360.0);
	s = 0.8 + 0.2 * sin(t * 6.28);
	v = 0.5 + 0.5 * t;
	
	return (hsv_to_rgb(h, s, v));
}

// Fire palette
int	get_fire_palette(int iteration, t_data *data)
{
	const int	fire_colors[] = {
		0x000000, 0x440000, 0x880000, 0xCC0000,
		0xFF0000, 0xFF4400, 0xFF8800, 0xFFCC00,
		0xFFFF00, 0xFFFF88, 0xFFFFCC, 0xFFFFFF
	};
	
	if (iteration >= data->max_iter)
		return (0x000000);
	
	int index = (iteration * 12) / data->max_iter;
	return (fire_colors[index % 12]);
}

// Ice palette
int	get_ice_palette(int iteration, t_data *data)
{
	const int	ice_colors[] = {
		0x000044, 0x000088, 0x0000CC, 0x0044CC,
		0x0088CC, 0x00CCFF, 0x44CCFF, 0x88CCFF,
		0xCCFFFF, 0xFFFFFF
	};
	
	if (iteration >= data->max_iter)
		return (0x000044);
	
	int index = (iteration * 10) / data->max_iter;
	return (ice_colors[index % 10]);
}

// Enhanced color function with new palettes
int	get_enhanced_color(int iteration, t_data *data)
{
	if (data->color_shift >= 6 && data->color_shift <= 8)
		return (get_fire_palette(iteration, data));
	else if (data->color_shift >= 9 && data->color_shift <= 11)
		return (get_ice_palette(iteration, data));
	else if (data->color_shift >= 12)
		return (get_smooth_color((double)iteration, data));
	else
		return (get_color_2(iteration, data));
}

void	color(t_data *data, int n, int x, int y)
{	
	if (data->use_antialiasing)
		color_with_antialiasing(data, n, x, y);
	else
	{
		if (data->fractal_index == BARNSLEY)
			data->color_shift = data->color_shift % 3 + 3;
		if (n == data->max_iter && data->fractal_index != BARNSLEY)
			my_mlx_pixel_put(data, x, y, 0x0000000);
		else
		{
			if (data->color_shift <= 2)
				my_mlx_pixel_put(data, x, y, get_color_default(n, data));
			else if (data->color_shift < 6)
				my_mlx_pixel_put(data, x, y, get_color_palette(n, data));
			else
				my_mlx_pixel_put(data, x, y, get_enhanced_color(n, data));
		}
	}
}
