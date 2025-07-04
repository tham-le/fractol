#include "fractol.h"


void	burning_ship(t_data *f)
{
	int x, y, n;
	t_complex c, z;
	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			c.re = f->min.re + x * f->delta.re;
			z.re = 0; // z0 = 0
			z.im = 0;
			n = -1;
			while ((++n < f->max_iter) && (z.re * z.re + z.im * z.im < 4))
			{
				double abs_re = fabs(z.re);
				double abs_im = fabs(z.im);
				double temp_re = abs_re * abs_re - abs_im * abs_im + c.re;
				double temp_im = 2 * abs_re * abs_im + c.im;
				z.re = temp_re;
				z.im = temp_im;
			}
			f->iteration_buffer[y][x] = n;
			f->z_buffer[y][x] = z;
		}
	}
}

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
	if (n == 3)
	{
		double z2_re = z.re * z.re - z.im * z.im;
		double z2_im = 2 * z.re * z.im;
		return (init_complex(z2_re * z.re - z2_im * z.im, 
							 z2_re * z.im + z2_im * z.re));
	}
	
	r = sqrt(z.re * z.re + z.im * z.im);
	theta = atan2(z.im, z.re);
	new_r = pow(r, n);
	new_theta = n * theta;
	
	return (init_complex(new_r * cos(new_theta), new_r * sin(new_theta)));
}

int	check_newton_convergence(t_complex z)
{
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

void	newton(t_data *f)
{
	int x, y, n;
	t_complex z, z_cubed, f_z, z_squared, f_prime_z, ratio;
	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			z.re = f->min.re + x * f->delta.re;
			z.im = f->max.im - y * f->delta.im;
			n = -1;
			while (++n < f->max_iter)
			{
				z_cubed = complex_power(z, 3);
				f_z = init_complex(z_cubed.re - 1, z_cubed.im);
				z_squared = complex_power(z, 2);
				f_prime_z = init_complex(3 * z_squared.re, 3 * z_squared.im);
				ratio = complex_divide(f_z, f_prime_z);
				z = init_complex(z.re - ratio.re, z.im - ratio.im);
				if (check_newton_convergence(z))
					break;
			}
			f->iteration_buffer[y][x] = n;
			f->z_buffer[y][x] = z;
		}
	}
}

void	buffalo(t_data *f)
{
	int x, y, n;
	t_complex c, z;
	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			c.re = f->min.re + x * f->delta.re;
			z = c;
			n = -1;
			while ((++n < f->max_iter) && (z.re * z.re + z.im * z.im < 4))
			{
				double abs_re = fabs(z.re);
				double abs_im = fabs(z.im);
				// (a + ib)^3 = a^3 + 3a^2ib + 3a(ib)^2 + (ib)^3
				double r = abs_re;
				double i = abs_im;
				double temp_re = r*r*r - 3*r*i*i + c.re;
				double temp_im = 3*r*r*i - i*i*i + c.im;
				z.re = temp_re;
				z.im = temp_im;
			}
			f->iteration_buffer[y][x] = n;
			f->z_buffer[y][x] = z;
		}
	}
}

void mandelbar(t_data *f) { buffalo(f); }

void	phoenix(t_data *f)
{
	int x, y, n;
	double p = -0.5;
	t_complex prev_z, z, temp, c;
	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		c.im = f->max.im - y * f->delta.im;
		while (++x < W_WIDTH)
		{
			c.re = f->min.re + x * f->delta.re;
			z = init_complex(0, 0);
			prev_z = init_complex(0, 0);
			n = -1;
			while (++n < f->max_iter && (z.re * z.re + z.im * z.im < 4))
			{
				temp = z;
				// z = z^2 + c + p * conj(prev_z)
				z = init_complex(
					temp.re * temp.re - temp.im * temp.im + c.re + p * prev_z.re,
					2 * temp.re * temp.im + c.im - p * prev_z.im
				);
				prev_z = temp;
			}
			f->iteration_buffer[y][x] = n;
			f->z_buffer[y][x] = z;
		}
	}
}

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

void multibrot(t_data *f)
{
    t_complex x_loop;
    int n_iter;
    int power = f->fractal_power;

    x_loop.im = -1;
    while (++x_loop.im < W_HEIGHT)
    {
        x_loop.re = -1;
        f->c.im = f->max.im - x_loop.im * f->delta.im;
        while (++x_loop.re < W_WIDTH)
        {
            f->c.re = f->min.re + x_loop.re * f->delta.re;
            f->z = f->c; // z0 = c
            n_iter = -1;
            while ((++n_iter < f->max_iter) && (f->z.re * f->z.re + f->z.im * f->z.im < 4))
            {
                t_complex temp = complex_power(f->z, power);
                f->z = init_complex(temp.re + f->c.re, temp.im + f->c.im);
            }
            f->iteration_buffer[(int)x_loop.im][(int)x_loop.re] = n_iter;
            f->z_buffer[(int)x_loop.im][(int)x_loop.re] = f->z;
        }
    }
}
