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
int get_smooth_color(double iteration, t_complex z, t_data *data)
{
	if (iteration >= data->max_iter)
		return 0x000000;

	// Use squared magnitude for stability
	double mag2 = z.re * z.re + z.im * z.im;
	if (mag2 < 1e-8)
		mag2 = 1e-8;

	// Standard smooth coloring formula
	double smooth_iter = iteration + 1 - log2(log2(mag2) / 2.0);

	// Normalize t to [0,1] for color mapping
	double t = fmod(smooth_iter * 0.05, 1.0);

	// HSV gradient (as before)
	double h = fmod((t * 360.0 + data->color_shift * 40), 360.0);
	double s = 0.8 + 0.2 * sin(t * 6.28);
	double v = 0.5 + 0.5 * t;

	return hsv_to_rgb(h, s, v);
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

// Psychedelic palette (sine wave based)
int get_psychedelic_palette(int n, t_data *data) {
	double t = (double)n / data->max_iter;
	int r = (int)(128 + 127 * sin(6.28 * t + data->color_shift));
	int g = (int)(128 + 127 * sin(6.28 * t * 2 + data->color_shift + 2));
	int b = (int)(128 + 127 * sin(6.28 * t * 3 + data->color_shift + 4));
	return create_trgb(0, r, g, b);
}

// Autumn palette
int get_autumn_palette(int n, t_data *data) {
	(void)data;
	const int autumn[5] = {0xFF7700, 0xFFB300, 0xFFD700, 0xFF6F00, 0xA0522D};
	return autumn[n % 5];
}

// Ocean palette
int get_ocean_palette(int n, t_data *data) {
	(void)data;
	const int ocean[5] = {0x022859, 0x1768AC, 0x44C2FD, 0x1B9AAA, 0x0D3B66};
	return ocean[n % 5];
}

// Forest palette
int get_forest_palette(int n, t_data *data) {
	(void)data;
	const int forest[5] = {0x154406, 0x38761D, 0x6AA84F, 0xB6D7A8, 0x783F04};
	return forest[n % 5];
}

// Greyscale palette
int get_greyscale_palette(int n, t_data *data) {
	int v = (int)(255.0 * n / data->max_iter);
	return create_trgb(0, v, v, v);
}

// Inverted palette
int get_inverted_palette(int n, t_data *data) {
	int base = get_color_default(n, data);
	int r = 255 - ((base >> 16) & 0xFF);
	int g = 255 - ((base >> 8) & 0xFF);
	int b = 255 - (base & 0xFF);
	return create_trgb(0, r, g, b);
}

// Angle-based coloring (color_shift 15)
int get_angle_color(int n, t_complex z, t_data *data) {
	if (n >= data->max_iter)
		return 0x222222;
	double angle = atan2(z.im, z.re);
	double norm = (angle + M_PI) / (2 * M_PI); // Normalize to [0,1]
	int hue = (int)(norm * 360.0);
	return hsv_to_rgb(hue, 1.0, 1.0);
}

// Orbit trap coloring (color_shift 16)
int get_orbit_trap_color(int n, t_complex z, t_data *data) {
	if (n >= data->max_iter)
		return 0x222222;
	double dist = fabs(z.im); // Distance to real axis
	double norm = fmin(dist * 10, 1.0); // Clamp for color effect
	int hue = (int)(norm * 240.0); // Blue for close, red for far
	return hsv_to_rgb(hue, 1.0, 1.0 - norm * 0.5);
}

// Distance estimation coloring (color_shift 17)
int get_distance_est_color(int n, t_complex z, t_data *data) {
	if (n >= data->max_iter)
		return 0x222222;
	double modulus = sqrt(z.re * z.re + z.im * z.im);
	double dist = 2.0 * modulus * log(modulus) / fabs(z.re * z.re + z.im * z.im);
	double norm = fmin(dist * 0.5, 1.0);
	int hue = (int)(norm * 360.0);
	return hsv_to_rgb(hue, 1.0, 1.0 - norm * 0.3);
}

// Enhanced color function with new palettes
int	get_enhanced_color(int iteration, t_data *data)
{
	if (data->color_shift >= COLOR_SHIFT_FIRE && data->color_shift <= COLOR_SHIFT_AUTUMN)
		return (get_fire_palette(iteration, data));
	else if (data->color_shift >= COLOR_SHIFT_ICE && data->color_shift <= COLOR_SHIFT_FOREST)
		return (get_ice_palette(iteration, data));
	else if (data->color_shift >= COLOR_SHIFT_SMOOTH_HSV)
		return (get_smooth_color((double)iteration, data->z2, data));
	else
		return (get_color_2(iteration, data));
}

// Remove angle and orbit trap color modes from get_palette_color
int get_palette_color(int n, t_complex z, t_data *data) {
	if (n >= data->max_iter)
		return 0x222222; // Neutral gray for inside set
	switch (data->color_shift) {
		case COLOR_SHIFT_DEFAULT_1: return get_color_default(n, data); // Default 1
		case COLOR_SHIFT_DEFAULT_2: return get_color_default(n, data); // Default 2 (channel shift)
		case COLOR_SHIFT_DEFAULT_3: return get_color_default(n, data); // Default 3 (channel shift)
		case COLOR_SHIFT_RAINBOW: return get_color_palette(n, data); // Rainbow
		case COLOR_SHIFT_PASTEL: return get_color_palette(n, data); // pal_2 (pastel)
		case COLOR_SHIFT_BEACH: return get_color_palette(n, data); // Beach
		case COLOR_SHIFT_FIRE: return get_fire_palette(n, data); // Fire
		case COLOR_SHIFT_PSYCHEDELIC: return get_psychedelic_palette(n, data); // Psychedelic
		case COLOR_SHIFT_AUTUMN: return get_autumn_palette(n, data); // Autumn
		case COLOR_SHIFT_ICE: return get_ice_palette(n, data); // Ice
		case COLOR_SHIFT_OCEAN: return get_ocean_palette(n, data); // Ocean
		case COLOR_SHIFT_FOREST: return get_forest_palette(n, data); // Forest
		case COLOR_SHIFT_SMOOTH_HSV: return get_smooth_color((double)n, z, data); // Smooth HSV
		case COLOR_SHIFT_GREYSCALE: return get_greyscale_palette(n, data); // Greyscale
		case COLOR_SHIFT_INVERTED: return get_inverted_palette(n, data); // Inverted
		case COLOR_SHIFT_ANGLE: return get_angle_color(n, z, data); // Angle-based
		case COLOR_SHIFT_ORBIT_TRAP: return get_orbit_trap_color(n, z, data); // Orbit trap
		case COLOR_SHIFT_DISTANCE_EST: return get_distance_est_color(n, z, data); // Distance estimation
		default: return get_color_default(n, data);
	}
}

void color(t_data *data, int n, int x, int y, t_complex z)
{
	if (data->use_antialiasing)
		color_with_antialiasing(data, n, x, y);
	else
	{
		my_mlx_pixel_put(data, x, y, get_palette_color(n, z, data));
	}
}
