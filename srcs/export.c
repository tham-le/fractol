/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:00:00 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/25 10:00:00 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <sys/time.h>
#include <time.h>
#include <math.h>

// Simple BMP export function
int	export_bmp(t_data *data, const char *filename)
{
	FILE	*file;
	int		file_size;
	int		header_size;
	int		padding;
	int		row_size;

	header_size = 54;
	padding = (4 - (W_WIDTH * 3) % 4) % 4;
	row_size = W_WIDTH * 3 + padding;
	file_size = header_size + row_size * W_HEIGHT;
	
	file = fopen(filename, "wb");
	if (!file)
		return (-1);
	
	// BMP Header
	fputc('B', file); fputc('M', file);
	fwrite(&file_size, 4, 1, file);
	fwrite("\0\0\0\0", 4, 1, file);
	fwrite(&header_size, 4, 1, file);
	
	// DIB Header
	int info_header_size = 40;
	int width = W_WIDTH;
	int height = W_HEIGHT;
	fwrite(&info_header_size, 4, 1, file);
	fwrite(&width, 4, 1, file);
	fwrite(&height, 4, 1, file);
	fwrite("\1\0", 2, 1, file);
	fwrite("\30\0", 2, 1, file);
	fwrite("\0\0\0\0", 4, 1, file);
	fwrite("\0\0\0\0", 4, 1, file);
	fwrite("\0\0\0\0", 4, 1, file);
	fwrite("\0\0\0\0", 4, 1, file);
	fwrite("\0\0\0\0", 4, 1, file);
	fwrite("\0\0\0\0", 4, 1, file);
	
	// Write pixel data (BGR format, bottom to top)
	for (int y = W_HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < W_WIDTH; x++)
		{
			int color = *(int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
			fputc((color & 0xFF), file);        // Blue
			fputc((color >> 8) & 0xFF, file);   // Green
			fputc((color >> 16) & 0xFF, file);  // Red
		}
		for (int p = 0; p < padding; p++)
			fputc(0, file);
	}
	
	fclose(file);
	printf("Exported fractal to %s\n", filename);
	return (0);
}

// Export current fractal with timestamp
void	quick_export(t_data *data)
{
	char		filename[100];
	time_t		timestamp;
	struct tm	*timeinfo;

	timestamp = time(NULL);
	timeinfo = localtime(&timestamp);
	
	snprintf(filename, sizeof(filename), "fractal_%04d%02d%02d_%02d%02d%02d.bmp",
		timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	
	export_bmp(data, filename);
}

// Create zoom animation sequence
void	create_zoom_animation(t_data *data, const char *prefix, int frames)
{
	char		filename[100];
	double		initial_width;
	double		initial_height;
	t_complex	center;
	double		zoom_factor = 2.0;
	
	// Get current center point
	center.re = (data->min.re + data->max.re) / 2;
	center.im = (data->min.im + data->max.im) / 2;
	
	initial_width = data->max.re - data->min.re;
	initial_height = data->max.im - data->min.im;
	
	printf("Creating zoom animation with %d frames...\n", frames);
	
	for (int frame = 0; frame < frames; frame++)
	{
		double progress = (double)frame / (frames - 1);
		double current_zoom = pow(zoom_factor, progress);
		
		double new_width = initial_width / current_zoom;
		double new_height = initial_height / current_zoom;
		
		data->min.re = center.re - new_width / 2;
		data->max.re = center.re + new_width / 2;
		data->min.im = center.im - new_height / 2;
		data->max.im = center.im + new_height / 2;
		
		data->delta.re = (data->max.re - data->min.re) / (W_WIDTH - 1);
		data->delta.im = (data->max.im - data->min.im) / (W_HEIGHT - 1);
		
		render_fractal(data);
		
		snprintf(filename, sizeof(filename), "%s_frame_%04d.bmp", prefix, frame);
		export_bmp(data, filename);
		
		printf("Frame %d/%d completed\n", frame + 1, frames);
	}
	
	printf("Animation sequence complete!\n");
}

// Create color animation sequence
void	create_color_animation(t_data *data, const char *prefix, int frames)
{
	char	filename[100];
	int		original_color_shift;
	
	original_color_shift = data->color_shift;
	printf("Creating color animation with %d frames...\n", frames);
	
	for (int frame = 0; frame < frames; frame++)
	{
		data->color_shift = frame % 15; // Cycle through all 15 color palettes
		render_fractal(data);
		
		snprintf(filename, sizeof(filename), "%s_frame_%04d.bmp", prefix, frame);
		export_bmp(data, filename);
		
		printf("Frame %d/%d completed\n", frame + 1, frames);
	}
	
	// Restore original color scheme
	data->color_shift = original_color_shift;
	render_fractal(data);
	printf("Color animation sequence complete!\n");
}
