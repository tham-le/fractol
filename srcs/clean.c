/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:18:57 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 11:29:23 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

/*
ERROR  CODE: 
1: error malloc of t_data data (no display or window created)
2: can not init mlx (calloc data done)
3: can not init window (ptr pour mlx et win)
4: can not init image

Exit code with ESC: 5 (not error)
*/
void	free_all(t_data *data, int state)
{
	if (state > 1)
	{
		if (state > 4)
			mlx_destroy_image(data->mlx, data->img);
		if (state > 3)
			mlx_destroy_window(data->mlx, data->win);
		if (state > 2)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	}
}

void	free_all_ok(t_data *data)
{
	free_all(data, 5);
	exit(0);
}

void	free_all_error(t_data *data, int state, char *error)
{
	free_all(data, state);
	ft_print_error(error, state);
}
