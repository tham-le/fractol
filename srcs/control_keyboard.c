/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keyboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:55:21 by thi-le            #+#    #+#             */
/*   Updated: 2023/02/27 16:35:06 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include <X11/X.h>

void	move(int key, t_data *data)
{
	t_complex	delta;

	delta = init_complex(ft_abs(data->max.re - data->min.re),
			ft_abs(data->max.im - data->min.im));
	if (key == XK_Left)
	{
		data->min.re -= delta.re * 0.05;
		data->max.re -= delta.re * 0.05;
	}
	else if (key == XK_Right)
	{
		data->min.re += delta.re * 0.05;
		data->max.re += delta.re * 0.05;
	}
	else if (key == XK_Up)
	{
		data->min.im += delta.im * 0.05;
		data->max.im += delta.im * 0.05;
	}
	else if (key == XK_Down)
	{
		data->min.im -= delta.im * 0.05;
		data->max.im -= delta.im * 0.05;
	}
	render_fractal(data);
}

void	change_max_iteration(int key, t_data *data)
{
	if (key == XK_minus || key == XK_KP_Subtract)
	{
		if (data->max_iter > 50)
			data->max_iter = (int)(data->max_iter * 0.95);
		else if (data->max_iter > 1)
			data->max_iter -= 1;
	}
	else if (key == XK_plus || key == XK_equal || key == XK_KP_Add)
	{
		if (data->max_iter < 50)
			data->max_iter += 1;
		else if (data->max_iter < 1000000000)
			data->max_iter = (int)(data->max_iter * 1.05);
	}
	render_fractal(data);
}

void	change_color_shift(t_data *data)
{
	data->color_shift = (data->color_shift + 1) % 15;
	render_fractal(data);
}

void	change_param_key(int key, t_data *data)
{
	if (key == XK_d)
		data->c.re *= 1.1;
	if (key == XK_a)
		data->c.re *= 0.9;
	if (key == XK_w)
		data->c.im *= 1.1;
	if (key == XK_s)
		data->c.im *= 0.9;
	render_fractal(data);
}

void	change_type(int key, t_data *data)
{
	data->max_iter = MAX_ITER;
	data->c = init_complex(0.285, 0.0);
	data->min = init_complex(MIN_X, MIN_Y);
	data->max = init_complex(MAX_X, MAX_Y);
	if (key == XK_1)
		data->fractal_index = 1;
	if (key == XK_2)
		data->fractal_index = 2;
	if (key == XK_3)
	{
		data->fractal_index = 3;
		init_defaults(data);
	}
	if (key == XK_4)
		data->fractal_index = 4;
	if (key == XK_5)
		data->fractal_index = 5;  // Burning Ship
	if (key == XK_6)
		data->fractal_index = 6;  // Newton
	if (key == XK_7)
		data->fractal_index = 7;  // Multibrot
	if (key == XK_8)
		data->fractal_index = 8;  // Buffalo (was Mandelbar)
	render_fractal(data);
}

void	handle_export_and_config(int key, t_data *data)
{
	char	filename[100];
	static int	export_counter = 0;
	
	if (key == XK_e)
	{
		// Export current fractal as BMP
		sprintf(filename, "fractal_%d.bmp", ++export_counter);
		if (export_bmp(data, filename) == 0)
			printf("Fractal exported to %s\n", filename);
		else
			printf("Failed to export fractal\n");
	}
	else if (key == XK_z)
	{
		// Create zoom animation
		sprintf(filename, "zoom_anim_%d", ++export_counter);
		printf("Creating zoom animation (this may take a while)...\n");
		create_zoom_animation(data, filename, 30);
		printf("Zoom animation created with prefix %s\n", filename);
	}
	else if (key == XK_x)
	{
		// Create color animation
		sprintf(filename, "color_anim_%d", ++export_counter);
		printf("Creating color animation...\n");
		create_color_animation(data, filename, 15);
		printf("Color animation created with prefix %s\n", filename);
	}
	else if (key == XK_o)
	{
		// Save configuration
		if (save_config(data, "fractal_config.txt") == 0)
			printf("Configuration saved to fractal_config.txt\n");
		else
			printf("Failed to save configuration\n");
	}
	else if (key == XK_l)
	{
		// Load configuration
		if (load_config(data, "fractal_config.txt") == 0)
		{
			printf("Configuration loaded from fractal_config.txt\n");
			render_fractal(data);
		}
		else
			printf("Failed to load configuration\n");
	}
	else if (key == XK_b)
	{
		// Run benchmark
		printf("Running benchmark...\n");
		benchmark_fractal(data, 10);
	}
}

void change_color_mode(t_data *data)
{
	data->color_mode = (data->color_mode + 1) % 3;
	printf("Color mode: %d\n", data->color_mode);
	render_fractal(data);
}
