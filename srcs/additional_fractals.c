/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fractals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:00:00 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/25 10:00:00 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Burning Ship fractal
void	burning_ship(t_data *f)
{
	int			x;
	int			y;
	int			n;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		f->c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			f->c.re = f->min.re + x * f->delta.re;
			f->z = f->c;
			f->z2 = f->z;
			n = -1;
			while ((++n < f->max_iter) && (f->z2.re + f->z2.im < 4))
			{
				// Key difference: absolute values before squaring
				f->z2 = init_complex(f->z.re * f->z.re, f->z.im * f->z.im);
				f->z = init_complex(f->z2.re - f->z2.im + f->c.re,
					2 * fabs(f->z.re) * fabs(f->z.im) + f->c.im);
			}
			color(f, n, x, y);
		}
	}
}

// Helper function for complex power
t_complex	complex_power(t_complex z, int n)
{
	double	r;
	double	theta;
	double	new_r;
	double	new_theta;

	if (n == 0)
		return (init_complex(1, 0));
	if (n == 1)
		return (z);
	if (n == 2)
		return (init_complex(z.re * z.re - z.im * z.im, 2 * z.re * z.im));
	
	r = sqrt(z.re * z.re + z.im * z.im);
	theta = atan2(z.im, z.re);
	new_r = pow(r, n);
	new_theta = n * theta;
	
	return (init_complex(new_r * cos(new_theta), new_r * sin(new_theta)));
}

// Multibrot sets (generalization of Mandelbrot)
void	multibrot(t_data *f)
{
	int			x;
	int			y;
	int			n;
	int			power = 3; // Default power for multibrot

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		f->c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			f->c.re = f->min.re + x * f->delta.re;
			f->z = f->c;
			n = -1;
			while ((++n < f->max_iter) && (f->z.re * f->z.re + f->z.im * f->z.im < 4))
			{
				t_complex temp = complex_power(f->z, power);
				f->z = init_complex(temp.re + f->c.re, temp.im + f->c.im);
			}
			color(f, n, x, y);
		}
	}
}

// Helper function for complex division
t_complex	complex_divide(t_complex a, t_complex b)
{
	double	denominator;

	denominator = b.re * b.re + b.im * b.im;
	if (denominator == 0)
		return (init_complex(INFINITY, INFINITY));
	
	return (init_complex(
		(a.re * b.re + a.im * b.im) / denominator,
		(a.im * b.re - a.re * b.im) / denominator
	));
}

// Check convergence for Newton fractal
int	check_newton_convergence(t_complex z)
{
	// Check convergence to the three cube roots of unity
	t_complex roots[3] = {
		{1.0, 0.0},
		{-0.5, 0.866025},
		{-0.5, -0.866025}
	};
	
	for (int i = 0; i < 3; i++)
	{
		double dist = sqrt((z.re - roots[i].re) * (z.re - roots[i].re) +
						   (z.im - roots[i].im) * (z.im - roots[i].im));
		if (dist < 0.001)
			return (1);
	}
	return (0);
}

// Newton fractal for z^3 - 1 = 0
void	newton(t_data *f)
{
	int			x;
	int			y;
	int			n;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			f->z.re = f->min.re + x * f->delta.re;
			f->z.im = f->max.im - y * f->delta.im;
			
			n = -1;
			while (++n < f->max_iter)
			{
				// Newton's method: z = z - f(z)/f'(z)
				// For f(z) = z^3 - 1, f'(z) = 3*z^2
				t_complex z_cubed = complex_power(f->z, 3);
				t_complex f_z = init_complex(z_cubed.re - 1, z_cubed.im);
				
				t_complex z_squared = complex_power(f->z, 2);
				t_complex f_prime_z = init_complex(3 * z_squared.re, 3 * z_squared.im);
				
				t_complex ratio = complex_divide(f_z, f_prime_z);
				f->z = init_complex(f->z.re - ratio.re, f->z.im - ratio.im);
				
				if (check_newton_convergence(f->z))
					break;
			}
			color(f, n, x, y);
		}
	}
}

// Mandelbar (conjugate Mandelbrot)
void	mandelbar(t_data *f)
{
	int			x;
	int			y;
	int			n;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		f->c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			f->c.re = f->min.re + x * f->delta.re;
			f->z = f->c;
			n = -1;
			while ((++n < f->max_iter) && (f->z.re * f->z.re + f->z.im * f->z.im < 4))
			{
				// Use complex conjugate
				double temp_re = f->z.re * f->z.re - f->z.im * f->z.im + f->c.re;
				double temp_im = -2 * f->z.re * f->z.im + f->c.im;
				f->z.re = temp_re;
				f->z.im = temp_im;
			}
			color(f, n, x, y);
		}
	}
}
