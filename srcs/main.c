/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:17:08 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 17:13:03 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"
#include <unistd.h> // for usleep

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
* CHECK ARGUMENT, CASE not matter
*/
int	valid_fractal(char *name)
{
	if (!ft_strcmp(ft_strlowcase(name), "mandelbrot") || !ft_strcmp(name, "1"))
		return (MANDELBROT);
	else if (!ft_strcmp(ft_strlowcase(name), "julia") || !ft_strcmp(name, "2"))
		return (JULIA);
	else if (!ft_strcmp(ft_strlowcase(name), "barnsley") || !ft_strcmp(name, "3"))
		return (BARNSLEY);
	else if (!ft_strcmp(ft_strlowcase(name), "tricorn") || !ft_strcmp(name, "4"))
		return (TRICORN);
	else if (!ft_strcmp(ft_strlowcase(name), "burning_ship") || !ft_strcmp(ft_strlowcase(name), "burning ship") || !ft_strcmp(name, "5"))
		return (BURNING_SHIP);
	else if (!ft_strcmp(ft_strlowcase(name), "newton") || !ft_strcmp(name, "6"))
		return (NEWTON);
	else if (!ft_strcmp(ft_strlowcase(name), "phoenix") || !ft_strcmp(name, "7"))
		return (PHOENIX);
	else if (!ft_strcmp(ft_strlowcase(name), "buffalo") || !ft_strcmp(name, "8"))
		return (MANDELBAR);
	else if (!ft_strcmp(ft_strlowcase(name), "multibrot") || !ft_strcmp(name, "9"))
		return (MULTIBROT);
	return (-1);
}

int	get_julia_param(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		data->c.re = -0.4;
		data->c.im = 0.6;
		return (0);
	}
	if (data->fractal_index != JULIA)
	{
		ft_print_help();
		exit(0);
	}
	if (!ft_strchr(argv[2], '.') || !ft_strchr(argv[3], '.'))
	{
		ft_print_help();
		ft_print_error(ERR_ARG_JULIA, 1);
	}
	data->c.re = ft_atof(argv[2]);
	data->c.im = ft_atof(argv[3]);
	return (0);
}

/*
* Calculate and render fractal - used for re-rendering during interactions
*/
void	render_fractal(t_data *data)
{
	profiler_start(); // Profiling start

	data->delta.re = (data->max.re - data->min.re) / (W_WIDTH - 1);
	data->delta.im = (data->max.im - data->min.im) / (W_HEIGHT - 1);
	
	// Special handling for Barnsley Fern - it draws directly
	if (data->fractal_index == BARNSLEY)
	{
		barnsley(data); // Assumes barnsley calls my_mlx_pixel_put directly
		profiler_end(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		mlx_do_sync(data->mlx);
		return;
	}

	// Call the appropriate fractal generation function (populates buffers)
	if (data->fractal_index == MANDELBROT)
	{
		if (data->use_threading)
			mandelbrot_threaded(data);
		else
			mandelbrot(data);
	}
	else if (data->fractal_index == JULIA)
	{
		if (data->use_threading)
			julia_threaded(data);
		else
			julia(data);
	}
	else if (data->fractal_index == TRICORN)
	{
		if (data->use_threading)
			tricorn_threaded(data);
		else
			tricorn(data);
	}
	else if (data->fractal_index == BURNING_SHIP)
		burning_ship(data);
	else if (data->fractal_index == NEWTON)
		newton(data);
	else if (data->fractal_index == PHOENIX)
		phoenix(data);
	else if (data->fractal_index == MANDELBAR) // Actually Buffalo
		mandelbar(data);
	else if (data->fractal_index == MULTIBROT)
		multibrot(data);

	// Now, color the pixels from the buffers
	render_pixels_from_buffer(data);
	
	profiler_end(data); // Profiling end
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_do_sync(data->mlx);
}

/*
* Initial fractal setup and main loop start
*/
void	start_draw(t_data *data)
{
	render_fractal(data);
	hooks(data);
	mlx_loop(data->mlx);
}

void infinite_zoom(t_data *data)
{
	int frames = 200; // Number of zoom steps
	double zoom_factor = 0.97; // Zoom per frame
	for (int i = 0; i < frames; i++)
	{
		double center_re = (data->min.re + data->max.re) / 2.0;
		double center_im = (data->min.im + data->max.im) / 2.0;
		double width = (data->max.re - data->min.re) * zoom_factor;
		double height = (data->max.im - data->min.im) * zoom_factor;
		data->min.re = center_re - width / 2.0;
		data->max.re = center_re + width / 2.0;
		data->min.im = center_im - height / 2.0;
		data->max.im = center_im + height / 2.0;
		data->max_iter = (int)(data->max_iter * 1.005);
		if (data->max_iter < 10)
			data->max_iter = 10;
		render_fractal(data);
		mlx_do_sync(data->mlx);
		usleep(20000); // 20ms per frame
	}
}

/*
* check  args => if not, print help
* if yes, but wrong name => print names
* if, start draw
*/
int	main(int argc, char **argv)
{
	t_data		data;
	int			fractal_index;

	if ((argc != 2 && argc != 4) || (argc == 2 && !ft_strcmp(argv[1], "help")))
		ft_print_help();
	else
	{
		fractal_index = valid_fractal(argv[1]);
		if (fractal_index == -1)
		{
			fractal_list();
			ft_print_error(ERR_NAME, 1);
		}
		else
		{
			data.fractal_index = fractal_index;
			get_julia_param(&data, argc, argv);
			init_img(&data, argv[1]);
			init_defaults(&data);
			start_draw(&data);
		}	
	}
	return (0);
}
