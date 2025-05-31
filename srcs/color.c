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

	if (data->color_shift == COLOR_SHIFT_RAINBOW)
		return (rainbow[(int)(n % 7)]);
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

int get_smooth_color(double iteration, t_complex z, t_data *data)
{
	if (iteration >= data->max_iter)
		return 0x000000;

	double mag2 = z.re * z.re + z.im * z.im;
	if (mag2 < 1e-8)
		mag2 = 1e-8;

	double smooth_iter = iteration + 1 - log2(log2(mag2) / 2.0);
	double t = fmod(smooth_iter * 0.05, 1.0);

	double h = fmod((t * 360.0 + data->color_shift * 40), 360.0);
	double s = 0.8 + 0.2 * sin(t * 6.28);
	double v = 0.5 + 0.5 * t;

	return hsv_to_rgb(h, s, v);
}

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

int get_psychedelic_palette(int n, t_data *data) {
	double t = (double)n / data->max_iter;
	int r = (int)(128 + 127 * sin(6.28 * t * 3.0));
	int g = (int)(128 + 127 * sin(6.28 * t * 2.0 + 2.094));
	int b = (int)(128 + 127 * sin(6.28 * t + 4.189));
	return create_trgb(0, r, g, b);
}

int get_ocean_palette(int n, t_data *data) {
	double t = (double)n / data->max_iter;
	int r = (int)(2 + t * 100);  // Deep blue to teal
	int g = (int)(40 + t * 180); // Dark to bright cyan
	int b = (int)(89 + t * 166); // Blue tones
	return create_trgb(0, MIN(255, r), MIN(255, g), MIN(255, b));
}

int get_forest_palette(int n, t_data *data) {
	double t = (double)n / data->max_iter;
	int r = (int)(21 + t * 100);  // Dark green to brown
	int g = (int)(68 + t * 150);  // Green gradient
	int b = (int)(4 + t * 50);    // Minimal blue
	return create_trgb(0, MIN(255, r), MIN(255, g), MIN(255, b));
}

int get_greyscale_palette(int n, t_data *data) {
	int v = (int)(255.0 * n / data->max_iter);
	return create_trgb(0, v, v, v);
}

int get_vintage_palette(int n, t_data *data) {
	if (n >= data->max_iter)
		return (0x403020);

	double t = (double)n / data->max_iter;
	int base_val = (int)(t * 255);

	int r = (int)(base_val * 0.393 + base_val * 0.769 + base_val * 0.189);
	int g = (int)(base_val * 0.349 + base_val * 0.686 + base_val * 0.168);
	int b = (int)(base_val * 0.272 + base_val * 0.534 + base_val * 0.131);

	r = MIN(255, MAX(0, r));
	g = MIN(255, MAX(0, g));
	b = MIN(255, MAX(0, b));
	
	return create_trgb(0, r, g, b);
}

int get_angle_color(int n, t_complex z, t_data *data) {
	if (n >= data->max_iter)
		return 0x222222;
	double angle = atan2(z.im, z.re);
	double norm = (angle + M_PI) / (2 * M_PI);
	int hue = (int)(norm * 360.0);
	return hsv_to_rgb(hue, 1.0, 1.0);
}


int get_palette_color(int n, t_complex z, t_data *data) {
	if (n >= data->max_iter)
		return 0x000000;
	
	switch (data->color_shift) {
		case COLOR_SHIFT_DEFAULT_1: return get_color_default(n, data);
		case COLOR_SHIFT_DEFAULT_2: return get_color_2(n, data);
		case COLOR_SHIFT_RAINBOW: return get_color_palette(n, data);
		case COLOR_SHIFT_FIRE: return get_fire_palette(n, data);
		case COLOR_SHIFT_ICE: return get_ice_palette(n, data);
		case COLOR_SHIFT_PSYCHEDELIC: return get_psychedelic_palette(n, data);
		case COLOR_SHIFT_OCEAN: return get_ocean_palette(n, data);
		case COLOR_SHIFT_FOREST: return get_forest_palette(n, data);
		case COLOR_SHIFT_SMOOTH_HSV: return get_smooth_color((double)n, z, data);
		case COLOR_SHIFT_GREYSCALE: return get_greyscale_palette(n, data);
		case COLOR_SHIFT_VINTAGE: return get_vintage_palette(n, data);
		case COLOR_SHIFT_ANGLE: return get_angle_color(n, z, data);
		default: return get_color_default(n, data);
	}
}

void render_pixels_from_buffer(t_data *data)
{
    for (int y = 0; y < W_HEIGHT; y++)
    {
        for (int x = 0; x < W_WIDTH; x++)
        {
            int n = data->iteration_buffer[y][x];
            t_complex z_val = data->z_buffer[y][x];
            int final_color;

            if (data->use_antialiasing)
            {
                // Anti-aliasing needs to be re-thought with buffers.
                color_with_antialiasing(data, n, x, y);
            }
            else
            {
                final_color = get_palette_color(n, z_val, data);
                my_mlx_pixel_put(data, x, y, final_color);
            }
        }
    }
}

void color(t_data *data, int n, int x, int y, t_complex z)
{
    // if (data->fractal_index == BARNSLEY)
    // {
    //      my_mlx_pixel_put(data, x, y, get_palette_color(n, z, data));
    //      return;
    // }

    if (data->use_antialiasing)
        color_with_antialiasing(data, n, x, y);
    else
    {
        my_mlx_pixel_put(data, x, y, get_palette_color(n, z, data));
    }
}
