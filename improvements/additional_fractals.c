/* Additional Fractal Types */
#include "fractol.h"
#include <math.h>

// Burning Ship fractal
void burning_ship(t_data *f)
{
    t_complex x;
    int n;

    x.im = -1;
    while (++x.im < W_HEIGHT)
    {
        x.re = -1;
        f->c.im = f->max.im - x.im * f->delta.im;
        while (++x.re < W_WIDTH)
        {
            f->c.re = f->min.re + x.re * f->delta.re;
            f->z = f->c;
            f->z2 = f->z;
            n = -1;
            while ((++n < f->max_iter) && (f->z2.re + f->z2.im < 4))
            {
                f->z2 = init_complex(f->z.re * f->z.re, f->z.im * f->z.im);
                // Key difference: absolute values before squaring
                f->z = init_complex(f->z2.re - f->z2.im + f->c.re,
                        2 * fabs(f->z.re) * fabs(f->z.im) + f->c.im);
            }
            color(f, n, x.re, x.im);
        }
    }
}

// Multibrot sets (generalization of Mandelbrot)
void multibrot(t_data *f, int power)
{
    t_complex x;
    int n;

    x.im = -1;
    while (++x.im < W_HEIGHT)
    {
        x.re = -1;
        f->c.im = f->max.im - x.im * f->delta.im;
        while (++x.re < W_WIDTH)
        {
            f->c.re = f->min.re + x.re * f->delta.re;
            f->z = f->c;
            n = -1;
            while ((++n < f->max_iter) && (f->z.re * f->z.re + f->z.im * f->z.im < 4))
            {
                t_complex temp = complex_power(f->z, power);
                f->z = init_complex(temp.re + f->c.re, temp.im + f->c.im);
            }
            color(f, n, x.re, x.im);
        }
    }
}

// Newton fractal
void newton_fractal(t_data *f)
{
    t_complex x;
    int n;

    x.im = -1;
    while (++x.im < W_HEIGHT)
    {
        x.re = -1;
        while (++x.re < W_WIDTH)
        {
            f->z.re = f->min.re + x.re * f->delta.re;
            f->z.im = f->max.im - x.im * f->delta.im;
            
            n = -1;
            while (++n < f->max_iter)
            {
                // Newton's method: z = z - f(z)/f'(z)
                // For f(z) = z^3 - 1
                t_complex z_cubed = complex_power(f->z, 3);
                t_complex f_z = init_complex(z_cubed.re - 1, z_cubed.im);
                
                t_complex z_squared = complex_power(f->z, 2);
                t_complex f_prime_z = init_complex(3 * z_squared.re, 3 * z_squared.im);
                
                t_complex ratio = complex_divide(f_z, f_prime_z);
                f->z = init_complex(f->z.re - ratio.re, f->z.im - ratio.im);
                
                // Check convergence to roots
                if (check_newton_convergence(f->z))
                    break;
            }
            color(f, n, x.re, x.im);
        }
    }
}

// Mandelbrot variants with different escape conditions
void mandelbar(t_data *f)
{
    t_complex x;
    int n;

    x.im = -1;
    while (++x.im < W_HEIGHT)
    {
        x.re = -1;
        f->c.im = f->max.im - x.im * f->delta.im;
        while (++x.re < W_WIDTH)
        {
            f->c.re = f->min.re + x.re * f->delta.re;
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
            color(f, n, x.re, x.im);
        }
    }
}

// Helper functions for complex arithmetic
t_complex complex_power(t_complex z, int n)
{
    if (n == 0) return init_complex(1, 0);
    if (n == 1) return z;
    if (n == 2) return init_complex(z.re * z.re - z.im * z.im, 2 * z.re * z.im);
    
    // For higher powers, use polar form
    double r = sqrt(z.re * z.re + z.im * z.im);
    double theta = atan2(z.im, z.re);
    
    double new_r = pow(r, n);
    double new_theta = n * theta;
    
    return init_complex(new_r * cos(new_theta), new_r * sin(new_theta));
}

t_complex complex_divide(t_complex a, t_complex b)
{
    double denominator = b.re * b.re + b.im * b.im;
    if (denominator == 0) return init_complex(INFINITY, INFINITY);
    
    return init_complex(
        (a.re * b.re + a.im * b.im) / denominator,
        (a.im * b.re - a.re * b.im) / denominator
    );
}
