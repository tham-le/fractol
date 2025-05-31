/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:10:12 by thi-le            #+#    #+#             */
/*   Updated: 2023/03/10 11:48:55 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

/*
* INITIALIZATION ALL THE VARIABLE TO DRAW A FRACTAL. 
*/
void	*init_defaults(t_data *f)
{
	if (f->fractal_index == BARNSLEY)
	{
		f->c = init_complex (0.0, 0.0);
		f->min = init_complex(-6.0, -1.5);
		f->max = init_complex(8.5, 10);
		f->max_iter = MAX_ITER * 5000;
	}
	else
	{
		f->min = init_complex(MIN_X, MIN_Y);
		f->max = init_complex(MAX_X, MAX_Y);
		f->max_iter = MAX_ITER;
	}
	f->z2 = init_complex(0.0, 0.0);
	f->color_shift = 3;
	f->julia_set = 0;
	f->use_threading = 1;
	f->use_antialiasing = 0;
	f->fractal_power = 2;
	f->pan_active = 0;
	f->pan_start_coord = init_complex(0,0);
	return (0);
}

int allocate_render_buffers(t_data *data)
{
	data->iteration_buffer = (int **)malloc(sizeof(int *) * W_HEIGHT);
	data->z_buffer = (t_complex **)malloc(sizeof(t_complex *) * W_HEIGHT);
	if (!data->iteration_buffer || !data->z_buffer)
		return (1);
	for (int i = 0; i < W_HEIGHT; i++)
	{
		data->iteration_buffer[i] = (int *)malloc(sizeof(int) * W_WIDTH);
		data->z_buffer[i] = (t_complex *)malloc(sizeof(t_complex) * W_WIDTH);
		if (!data->iteration_buffer[i] || !data->z_buffer[i])
		{
			for (int j = 0; j < i; j++)
			{
				free(data->iteration_buffer[j]);
				free(data->z_buffer[j]);
			}
			free(data->iteration_buffer);
			free(data->z_buffer);
			return (1);
		}
	}
	return (0);
}

void free_render_buffers(t_data *data)
{
	if (data->iteration_buffer)
	{
		for (int i = 0; i < W_HEIGHT; i++)
			free(data->iteration_buffer[i]);
		free(data->iteration_buffer);
		data->iteration_buffer = NULL;
	}
	if (data->z_buffer)
	{
		for (int i = 0; i < W_HEIGHT; i++)
			free(data->z_buffer[i]);
		free(data->z_buffer);
		data->z_buffer = NULL;
	}
}

/*
* CREATE A DISPLAY, A WINDOW AND AN IMAGE
* print a error if not able to creat one of these
* and destroy in the inverse order of creation
*/
void	*init_img(t_data *data, char *argv)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		free_all_error(data, 2, ERR_MLX_INIT);
	data->win = mlx_new_window(data->mlx, W_WIDTH, W_HEIGHT, argv);
	if (data->win == NULL)
		free_all_error(data, 3, ERR_WINDOW_INIT);
	data->img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	if (data->img == NULL)
		free_all_error(data, 4, ERR_IMAGE_INIT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (allocate_render_buffers(data) != 0)
		free_all_error(data, 5, ERR_MALLOC);
	return (0);
}

void	white_image(t_data *data)
{
	t_complex	x;

	x.im = -1;
	while (++x.im < W_HEIGHT)
	{
		x.re = -1;
		while (++x.re < W_WIDTH)
		{
			my_mlx_pixel_put(data, x.re, x.im, 0x00FFFFFF);
		}
	}
}
