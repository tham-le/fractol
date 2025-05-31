/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:00:00 by Your Name         #+#    #+#             */
/*   Updated: 2023/03/12 12:00:00 by Your Name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <unistd.h>
#include <math.h>

// Enhanced infinite zoom with better targeting and smooth transitions
void enhanced_infinite_zoom(t_data *data)
{
	int frames = 300;
	double zoom_factor = 0.992;
	double iter_increase = 1.001;
	
	t_complex target;
	if (data->fractal_index == MANDELBROT) {
		target.re = -0.235125;
		target.im = 0.827215;
	} else if (data->fractal_index == JULIA) {
		target.re = -0.1;
		target.im = 0.8;
	} else if (data->fractal_index == BURNING_SHIP) {
        target.re = -1.8;
		target.im = -0.08;
	} else if (data->fractal_index == TRICORN) {
		target.re = -0.5;
		target.im = 0.6;
	} else {
		target.re = (data->min.re + data->max.re) / 2.0 + 0.1;
		target.im = (data->min.im + data->max.im) / 2.0 + 0.1;
	}
	
	for (int i = 0; i < frames; i++)
	{
		double current_center_re = (data->min.re + data->max.re) / 2.0;
		double current_center_im = (data->min.im + data->max.im) / 2.0;
		
		double new_center_re = current_center_re + (target.re - current_center_re) * 0.01;
		double new_center_im = current_center_im + (target.im - current_center_im) * 0.01;
		
		double width = (data->max.re - data->min.re) * zoom_factor;
		double height = (data->max.im - data->min.im) * zoom_factor;
		
		data->min.re = new_center_re - width / 2.0;
		data->max.re = new_center_re + width / 2.0;
		data->min.im = new_center_im - height / 2.0;
		data->max.im = new_center_im + height / 2.0;
		
		if (i % 30 == 0 && data->max_iter < 500) {
			data->max_iter = (int)(data->max_iter * iter_increase) + 1;
		}
			
		if (i % 40 == 0)
			data->color_shift = (data->color_shift + 1) % MAX_COLOR_PALETTES;
		
		render_fractal(data);
		usleep(35000);
	}
}

// Spiral zoom animation - zoom while rotating the view
void spiral_zoom_animation(t_data *data)
{
	int frames = 300;
	double zoom_factor = 0.99;
	t_complex center;
	center.re = (data->min.re + data->max.re) / 2.0;
	center.im = (data->min.im + data->max.im) / 2.0;
	
	for (int i = 0; i < frames; i++)
	{
		double angle = (double)i * 0.05;
		double width = (data->max.re - data->min.re) * zoom_factor;
		double height = (data->max.im - data->min.im) * zoom_factor;
		
		double offset_x = width * 0.1 * cos(angle);
		double offset_y = height * 0.1 * sin(angle);
		
		data->min.re = center.re - width / 2.0 + offset_x;
		data->max.re = center.re + width / 2.0 + offset_x;
		data->min.im = center.im - height / 2.0 + offset_y;
		data->max.im = center.im + height / 2.0 + offset_y;
		
		if (i % 20 == 0 && data->max_iter < 300)
			data->max_iter += 5;
		
		render_fractal(data);
		usleep(25000);
	}
}

// Julia parameter sweep animation - smoothly morph Julia set
void julia_morph_animation(t_data *data)
{
	if (data->fractal_index != JULIA) {
		return;
	}
	
	int frames = 400;
	double start_re = data->c.re;
	double start_im = data->c.im;
	
	t_complex julia_points[] = {
		{-0.4, 0.6}, {-0.75, 0.11}, {-0.1, 0.651}, {0.285, 0.01},
		{-0.8, 0.156}, {-0.123, 0.745}, {0.3, 0.5}, {-0.235, 0.827}
	};
	int num_points = 8;
	
	for (int i = 0; i < frames; i++)
	{
		double progress = (double)i / frames;
		int current_point = (int)(progress * num_points) % num_points;
		int next_point = (current_point + 1) % num_points;
		double local_progress = fmod(progress * num_points, 1.0);
		
		data->c.re = julia_points[current_point].re + 
					 (julia_points[next_point].re - julia_points[current_point].re) * local_progress;
		data->c.im = julia_points[current_point].im + 
					 (julia_points[next_point].im - julia_points[current_point].im) * local_progress;
		
		if (i % 40 == 0)
			data->color_shift = (data->color_shift + 1) % MAX_COLOR_PALETTES;
		
		render_fractal(data);
		usleep(40000);
	}
	
	data->c.re = start_re;
	data->c.im = start_im;
	render_fractal(data);
}

// Fractal showcase - cycle through different fractal types
void fractal_showcase_animation(t_data *data)
{
	int original_fractal = data->fractal_index;
	int original_iterations = data->max_iter;
	t_complex original_c = data->c;
	t_complex original_min = data->min;
	t_complex original_max = data->max;
	
	// Fractal tour with optimal settings for each
	typedef struct {
		int fractal_type;
		int iterations;
		t_complex c_param;
		t_complex view_min;
		t_complex view_max;
		int duration_frames;
	} fractal_showcase_t;
	
	fractal_showcase_t showcase[] = {
		{MANDELBROT, 150, {0, 0}, {-2.5, -1.5}, {1.5, 1.5}, 80},
		{JULIA, 120, {-0.4, 0.6}, {-2, -1.5}, {2, 1.5}, 80},
		{BURNING_SHIP, 180, {0, 0}, {-2.5, -2}, {1.5, 1}, 80},
		{TRICORN, 140, {0, 0}, {-2.5, -1.5}, {1.5, 1.5}, 80},
		{NEWTON, 100, {0, 0}, {-2, -1.5}, {2, 1.5}, 80},
		{MULTIBROT, 160, {0, 0}, {-2.5, -1.5}, {1.5, 1.5}, 80}
	};
	int num_fractals = 6;
	
	for (int f = 0; f < num_fractals; f++)
	{
		data->fractal_index = showcase[f].fractal_type;
		data->max_iter = showcase[f].iterations;
		data->c = showcase[f].c_param;
		data->min = showcase[f].view_min;
		data->max = showcase[f].view_max;
		
		if (showcase[f].fractal_type == MULTIBROT)
			data->fractal_power = 3; // Set interesting power for Multibrot
		
		// Show the fractal with some dynamic effects
		for (int i = 0; i < showcase[f].duration_frames; i++)
		{
			// Slight zoom and color cycling for visual appeal
			if (i > 10) {
				double zoom = 0.998;
				double center_re = (data->min.re + data->max.re) / 2.0;
				double center_im = (data->min.im + data->max.im) / 2.0;
				double width = (data->max.re - data->min.re) * zoom;
				double height = (data->max.im - data->min.im) * zoom;
				
				data->min.re = center_re - width / 2.0;
				data->max.re = center_re + width / 2.0;
				data->min.im = center_im - height / 2.0;
				data->max.im = center_im + height / 2.0;
			}
			
			// Color cycling for visual variety
			if (i % 20 == 0)
				data->color_shift = (data->color_shift + 1) % MAX_COLOR_PALETTES;
			
			render_fractal(data);
			usleep(50000); // 50ms per frame
		}
	}
	
	// Restore original settings
	data->fractal_index = original_fractal;
	data->max_iter = original_iterations;
	data->c = original_c;
	data->min = original_min;
	data->max = original_max;
	render_fractal(data);
}

// Color palette animation - clean showcase without ugly effects
void color_palette_showcase(t_data *data)
{
	int original_palette = data->color_shift;
	int frames_per_palette = 80; // Longer display time for each palette
	
	// Set up a nice viewing area that works well with all fractals
	t_complex original_min = data->min;
	t_complex original_max = data->max;
	int original_iterations = data->max_iter;
	
	// Choose optimal view based on fractal type
	if (data->fractal_index == MANDELBROT) {
		data->min.re = -2.0; data->min.im = -1.2;
		data->max.re = 1.0; data->max.im = 1.2;
		data->max_iter = 150;
	} else if (data->fractal_index == JULIA) {
		data->min.re = -1.5; data->min.im = -1.2;
		data->max.re = 1.5; data->max.im = 1.2;
		data->max_iter = 120;
	} else if (data->fractal_index == BURNING_SHIP) {
		data->min.re = -2.2; data->min.im = -1.5;
		data->max.re = 1.0; data->max.im = 0.5;
		data->max_iter = 180;
	} else {
		// Keep original view for other fractals
		data->max_iter = 150;
	}
	
	for (int palette = 0; palette < MAX_COLOR_PALETTES; palette++)
	{
		data->color_shift = palette;
		
		for (int i = 0; i < frames_per_palette; i++)
		{
			// Simple, subtle effect - slight zoom for dynamic feel
			if (i > 10 && i < frames_per_palette - 10) {
				double zoom_factor = 1.0 + 0.0001 * sin((double)i * 0.1); // Very subtle zoom
				double center_re = (data->min.re + data->max.re) / 2.0;
				double center_im = (data->min.im + data->max.im) / 2.0;
				double width = (data->max.re - data->min.re) * zoom_factor;
				double height = (data->max.im - data->min.im) * zoom_factor;
				
				data->min.re = center_re - width / 2.0;
				data->max.re = center_re + width / 2.0;
				data->min.im = center_im - height / 2.0;
				data->max.im = center_im + height / 2.0;
			}
			
			render_fractal(data);
			usleep(25000); // 25ms per frame for smooth display
		}
	}
	
	// Restore original settings
	data->color_shift = original_palette;
	data->min = original_min;
	data->max = original_max;
	data->max_iter = original_iterations;
	render_fractal(data);
} 