/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:42:50 by thi-le            #+#    #+#             */
/*   Updated: 2023/03/12 10:00:00 by Your Name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
// For gettimeofday if we add click vs drag distinction later
// #include <sys/time.h> 

// Structure to keep track of mouse dragging for panning
typedef struct s_gesture {
    int start_x_screen;
    int start_y_screen;
    t_complex initial_min; // To store data->min at drag start
    t_complex initial_max; // To store data->max at drag start
} t_gesture;

static t_gesture gesture_state; // Static global for this file

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

// Converts screen coordinates to world coordinates
t_complex screen_to_world(int x, int y, t_data *data)
{
    t_complex world_pos;
    world_pos.re = data->min.re + (double)x * data->delta.re;
    world_pos.im = data->max.im - (double)y * data->delta.im;
    return world_pos;
}

int	zoom_at_point(int button, int x, int y, t_data *data) // Renamed from zoom
{
	t_complex	mouse_world;
	double		interpolation_factor;
	double		zoom_val;

	mouse_world = screen_to_world(x, y, data);
	if (button == SCROLL_UP)
		zoom_val = 0.85; // Zoom in
	else // SCROLL_DOWN
		zoom_val = 1.15; // Zoom out

	interpolation_factor = 1.0 / zoom_val;
	data->min.re = interpolate(mouse_world.re, data->min.re, interpolation_factor);
	data->min.im = interpolate(mouse_world.im, data->min.im, interpolation_factor);
	data->max.re = interpolate(mouse_world.re, data->max.re, interpolation_factor);
	data->max.im = interpolate(mouse_world.im, data->max.im, interpolation_factor);
	render_fractal(data);
	return (0);
}

// This function is called when Julia is active and a non-drag left click occurs
int	set_julia_c_from_mouse(int x, int y, t_data *data) // Renamed from change_param
{
	// Map mouse position to a typical range for Julia C parameters (e.g., -2 to 2)
	data->c.re = (data->min.re + (data->max.re - data->min.re) * ((double)x / W_WIDTH));
	data->c.im = (data->max.im - (data->max.im - data->min.im) * ((double)y / W_HEIGHT));
	render_fractal(data);
	return (0);
}

int	cycle_julia_presets(t_data *data) // Renamed from change_julia
{
	const double	set[13][2] = {{-0.4, 0.6}, {0.285, 0.0}, {0.285, 0.01},
	{0.54, 0.1428}, {-0.70176, -0.3842}, {-0.835, -0.2321},
	{-0.8, 0.156}, {-0.7269, 0.1889}, {0, -0.8}, {0.37, 0.1}, {0.355, 0.355},
	{0.355534, 0.337292}, {-1.34882125854492, -0.454237874348958}};

	data->julia_set = (data->julia_set + 1) % 13;
	data->c = init_complex (set[data->julia_set][0], set[data->julia_set][1]);
	render_fractal(data);
	return (0);
}

// Hook for mouse button press
int	mouse_press_hook(int button, int x, int y, t_data *data)
{
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		zoom_at_point(button, x, y, data);
	}
	else if (button == LEFT_CLICK)
	{
		// Start panning
		data->pan_active = 1;
		gesture_state.start_x_screen = x;
		gesture_state.start_y_screen = y;
        // Store the initial view boundaries at the start of the drag
        gesture_state.initial_min = data->min;
        gesture_state.initial_max = data->max;
	}
	else if (button == RIGHT_CLICK)
	{
		cycle_julia_presets(data);
	}
	return (0);
}

// Hook for mouse button release
int	mouse_release_hook(int button, int x, int y, t_data *data)
{
	if (button == LEFT_CLICK)
	{
		if (data->pan_active)
		{
			data->pan_active = 0;
			// Check if it was a "click" (mouse didn't move much) vs a "drag"
			int dx = abs(x - gesture_state.start_x_screen);
			int dy = abs(y - gesture_state.start_y_screen);
			if (dx < 5 && dy < 5 && data->fractal_index == JULIA) // Threshold for click
			{
				set_julia_c_from_mouse(x, y, data);
			}
		}
	}
	return (0);
}

// Hook for mouse motion
int	mouse_motion_hook(int x, int y, t_data *data)
{
	if (data->pan_active)
	{
		double delta_x_screen = (double)(x - gesture_state.start_x_screen);
		double delta_y_screen = (double)(y - gesture_state.start_y_screen);

        // Calculate how much the world coordinates should shift
        // based on the initial view and mouse screen delta
		double world_dx = delta_x_screen * (gesture_state.initial_max.re - gesture_state.initial_min.re) / W_WIDTH;
		double world_dy = delta_y_screen * (gesture_state.initial_max.im - gesture_state.initial_min.im) / W_HEIGHT;

        // Pan by adjusting min/max relative to the initial state
		data->min.re = gesture_state.initial_min.re - world_dx;
		data->max.re = gesture_state.initial_max.re - world_dx;
		data->min.im = gesture_state.initial_min.im + world_dy; // Y-axis is inverted in screen vs world
		data->max.im = gesture_state.initial_max.im + world_dy;

		render_fractal(data);
	}
	return (0);
}
