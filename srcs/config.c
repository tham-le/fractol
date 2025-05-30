/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:00:00 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/25 10:00:00 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <string.h>

#define CONFIG_FILE "fractol_config.ini"

// Save current configuration to file
int	save_config(t_data *data, const char *filename)
{
	FILE *file = fopen(filename, "w");
	if (!file)
	{
		printf("Error: Could not save configuration\n");
		return (-1);
	}
	
	fprintf(file, "# Fractol Configuration File\n");
	fprintf(file, "fractal_index=%d\n", data->fractal_index);
	fprintf(file, "min_re=%f\n", data->min.re);
	fprintf(file, "min_im=%f\n", data->min.im);
	fprintf(file, "max_re=%f\n", data->max.re);
	fprintf(file, "max_im=%f\n", data->max.im);
	fprintf(file, "max_iter=%d\n", data->max_iter);
	fprintf(file, "color_shift=%d\n", data->color_shift);
	fprintf(file, "julia_c_re=%f\n", data->c.re);
	fprintf(file, "julia_c_im=%f\n", data->c.im);
	fprintf(file, "use_threading=%d\n", data->use_threading);
	fprintf(file, "use_antialiasing=%d\n", data->use_antialiasing);
	
	fclose(file);
	printf("Configuration saved to %s\n", filename);
	return (0);
}

// Load configuration from file
int	load_config(t_data *data, const char *filename)
{
	FILE	*file;
	char	line[256];
	char	key[64];
	char	value[64];

	file = fopen(filename, "r");
	if (!file)
	{
		printf("No configuration file found, using defaults\n");
		return (-1);
	}
	
	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == '#' || line[0] == '\n')
			continue;
			
		if (sscanf(line, "%63[^=]=%63s", key, value) == 2)
		{
			if (strcmp(key, "fractal_index") == 0)
				data->fractal_index = atoi(value);
			else if (strcmp(key, "min_re") == 0)
				data->min.re = atof(value);
			else if (strcmp(key, "min_im") == 0)
				data->min.im = atof(value);
			else if (strcmp(key, "max_re") == 0)
				data->max.re = atof(value);
			else if (strcmp(key, "max_im") == 0)
				data->max.im = atof(value);
			else if (strcmp(key, "max_iter") == 0)
				data->max_iter = atoi(value);
			else if (strcmp(key, "color_shift") == 0)
				data->color_shift = atoi(value);
			else if (strcmp(key, "julia_c_re") == 0)
				data->c.re = atof(value);
			else if (strcmp(key, "julia_c_im") == 0)
				data->c.im = atof(value);
			else if (strcmp(key, "use_threading") == 0)
				data->use_threading = atoi(value);
			else if (strcmp(key, "use_antialiasing") == 0)
				data->use_antialiasing = atoi(value);
		}
	}
	
	fclose(file);
	printf("Configuration loaded from %s\n", filename);
	return (0);
}

// Save preset with custom name
void	save_preset(t_data *data, const char *name)
{
	char	filename[100];
	FILE	*file;

	snprintf(filename, sizeof(filename), "preset_%s.ini", name);
	file = fopen(filename, "w");
	if (!file)
	{
		printf("Error: Could not save preset\n");
		return;
	}
	
	fprintf(file, "# Fractol Preset: %s\n", name);
	fprintf(file, "fractal_index=%d\n", data->fractal_index);
	fprintf(file, "min_re=%f\n", data->min.re);
	fprintf(file, "min_im=%f\n", data->min.im);
	fprintf(file, "max_re=%f\n", data->max.re);
	fprintf(file, "max_im=%f\n", data->max.im);
	fprintf(file, "max_iter=%d\n", data->max_iter);
	fprintf(file, "color_shift=%d\n", data->color_shift);
	fprintf(file, "julia_c_re=%f\n", data->c.re);
	fprintf(file, "julia_c_im=%f\n", data->c.im);
	
	fclose(file);
	printf("Preset saved as %s\n", filename);
}

// Load preset by name
void	load_preset(t_data *data, const char *name)
{
	char	filename[100];
	FILE	*file;
	char	line[256];
	char	key[64];
	char	value[64];

	snprintf(filename, sizeof(filename), "preset_%s.ini", name);
	file = fopen(filename, "r");
	if (!file)
	{
		printf("Preset %s not found\n", name);
		return;
	}
	
	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == '#' || line[0] == '\n')
			continue;
			
		if (sscanf(line, "%63[^=]=%63s", key, value) == 2)
		{
			if (strcmp(key, "fractal_index") == 0)
				data->fractal_index = atoi(value);
			else if (strcmp(key, "min_re") == 0)
				data->min.re = atof(value);
			else if (strcmp(key, "min_im") == 0)
				data->min.im = atof(value);
			else if (strcmp(key, "max_re") == 0)
				data->max.re = atof(value);
			else if (strcmp(key, "max_im") == 0)
				data->max.im = atof(value);
			else if (strcmp(key, "max_iter") == 0)
				data->max_iter = atoi(value);
			else if (strcmp(key, "color_shift") == 0)
				data->color_shift = atoi(value);
			else if (strcmp(key, "julia_c_re") == 0)
				data->c.re = atof(value);
			else if (strcmp(key, "julia_c_im") == 0)
				data->c.im = atof(value);
		}
	}
	
	fclose(file);
	printf("Preset %s loaded\n", name);
	render_fractal(data);
}
