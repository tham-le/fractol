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

void free_render_buffers(t_data *data); // Forward declaration

int	red_cross(t_data *data)
{
	free_render_buffers(data);
	free_all_ok(data);
	return (0);
}

void	toggle_threading(t_data *data)
{
	data->use_threading = !data->use_threading;
	render_fractal(data);
}

void	toggle_antialiasing(t_data *data)
{
	data->use_antialiasing = !data->use_antialiasing;
	render_fractal(data);
}

int key_press(int key, t_data *data)
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
	else if (key == XK_a || key == XK_A)
		toggle_antialiasing(data);
	else if (key == XK_minus || key == XK_plus || key == XK_equal
		|| key == XK_KP_Add || key == XK_KP_Subtract)
		change_max_iteration(key, data);
	else if (key == XK_Left || key == XK_Right || key == XK_Up
		|| key == XK_Down)
		move(key, data);
	else if (key == XK_c || key == XK_C)
		change_color_shift(data);
	else if (key >= XK_1 && key <= XK_9)
		change_type(key, data);
	else if (key == XK_d || key == XK_w || key == XK_s || key == XK_q)
		change_param_key(key, data);
	else if (key == XK_Page_Up || key == XK_Page_Down)
		change_multibrot_power(key, data);
	else if (key == XK_e || key == XK_z || key == XK_x || key == XK_o 
		|| key == XK_l || key == XK_p || key == XK_P)
		handle_export_and_config(key, data);
	else if (key == XK_i)
		infinite_zoom(data);
	else if (key == XK_u)
		enhanced_infinite_zoom(data);
	else if (key == XK_y)
		spiral_zoom_animation(data);
	else if (key == XK_j)
		julia_morph_animation(data);
	else if (key == XK_h)
		fractal_showcase_animation(data);
	else if (key == XK_g)
		color_palette_showcase(data);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, &key_press, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, &mouse_press_hook, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask, &mouse_release_hook, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, &mouse_motion_hook, data);
	mlx_hook(data->win, DestroyNotify, 0, &red_cross, data);
}
