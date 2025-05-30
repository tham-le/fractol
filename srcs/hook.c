/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:07:18 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 18:00:14 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	red_cross(t_data *data)
{
	free_all_ok(data);
	return (0);
}

void	toggle_threading(t_data *data)
{
	data->use_threading = !data->use_threading;
	printf("Threading %s\n", data->use_threading ? "enabled" : "disabled");
	render_fractal(data);
}

void	toggle_antialiasing(t_data *data)
{
	data->use_antialiasing = !data->use_antialiasing;
	printf("Anti-aliasing %s\n", data->use_antialiasing ? "enabled" : "disabled");
	render_fractal(data);
}

int	key_press(int key, t_data *data)
{
	if (key == XK_Escape)
		free_all_ok(data);
	else if (key == XK_r)
	{
		init_defaults(data);
		render_fractal(data);
	}
	else if (key == XK_t || key == XK_T)
		toggle_threading(data);
	else if (key == XK_p || key == XK_P)
		toggle_antialiasing(data);
	else if (key == XK_minus || key == XK_plus || key == XK_equal
		|| key == XK_KP_Add || key == XK_KP_Subtract)
		change_max_iteration(key, data);
	else if (key == XK_Left || key == XK_Right || key == XK_Up
		|| key == XK_Down)
		move(key, data);
	else if (key == XK_c || key == XK_C)
		change_color_shift(data);
	else if (key >= XK_1 && key <= XK_8)
		change_type(key, data);
	else if (key == XK_d || key == XK_a || key == XK_w || key == XK_s)
		change_param_key(key, data);
	else if (key == XK_e || key == XK_z || key == XK_x || key == XK_o 
		|| key == XK_l || key == XK_b)
		handle_export_and_config(key, data);
	else if (key == XK_i)
		infinite_zoom(data);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, &key_press, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, &mouse_press, data);
	mlx_hook(data->win, DestroyNotify, 0, &red_cross, data);
}
