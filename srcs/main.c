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
	else if (!ft_strcmp(ft_strlowcase(name), "multibrot") || !ft_strcmp(name, "7"))
		return (MULTIBROT);
	else if (!ft_strcmp(ft_strlowcase(name), "mandelbar") || !ft_strcmp(name, "8"))
		return (MANDELBAR);
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
	data->delta.re = (data->max.re - data->min.re) / (W_WIDTH - 1);
	data->delta.im = (data->max.im - data->min.im) / (W_HEIGHT - 1);
	
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
	else if (data->fractal_index == BARNSLEY)
		barnsley(data);
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
	else if (data->fractal_index == MULTIBROT)
		multibrot(data);
	else if (data->fractal_index == MANDELBAR)
		mandelbar(data);
	
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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

/*
* check  args => if not, print help
* if yes, but wrong name => print names
* if, start draw
*/
int	main(int argc, char **argv)
{
	t_data		data;
	int			fractal_index;

	if (argc != 2 && argc != 4)
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
