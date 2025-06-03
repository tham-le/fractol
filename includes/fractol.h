/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:52:16 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 17:12:33 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H

# define W_WIDTH 1800
# define W_HEIGHT 1800

# define MANDELBROT			1
# define JULIA				2
# define BARNSLEY			3
# define TRICORN			4
# define BURNING_SHIP		5
# define NEWTON				6
# define PHOENIX			7
# define MANDELBAR			8
# define MULTIBROT			9

# define COLOR_SHIFT_DEFAULT_1		0
# define COLOR_SHIFT_DEFAULT_2		1
# define COLOR_SHIFT_RAINBOW		2
# define COLOR_SHIFT_FIRE			3
# define COLOR_SHIFT_ICE			4
# define COLOR_SHIFT_PSYCHEDELIC	5
# define COLOR_SHIFT_OCEAN			6
# define COLOR_SHIFT_FOREST			7
# define COLOR_SHIFT_SMOOTH_HSV		8
# define COLOR_SHIFT_GREYSCALE		9
# define COLOR_SHIFT_VINTAGE		10
# define COLOR_SHIFT_ANGLE			11
# define MAX_COLOR_PALETTES			12

# define MIN_X	-2.0
# define MAX_X	1.5
# define MIN_Y	-1.5
# define MAX_Y	1.5
# define MAX_ITER	100
# define DEFAULT_COLOR 0
# define NUM_THREADS	4
# define MAX_THREADS	8

# define LEFT_CLICK			1
# define MIDDLE_CLICK		2
# define RIGHT_CLICK		3
# define SCROLL_UP			4
# define SCROLL_DOWN		5

# define ERR_NAME			"\t\033[31;1mError:\033[0m Fractal unavailable."
# define ERR_ARG_JULIA		"\t\033[31;1mError:\033[0m Julia Parameters not valid"
# define ERR_MALLOC			"\t\033[31;1mError :\033[0m Can't allocate memory."
# define ERR_FRACTOL_INIT	"\tERROR: Can\'t initialize fractol"
# define ERR_WINDOW_INIT	"\tERROR: Can\'t initialize window"
# define ERR_IMAGE_INIT		"\tERROR: Can\'t initialize image"
# define ERR_MLX_INIT		"\tERROR: Can\'t initialize minilibx display"

# include <../minilibx-linux/mlx.h>
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct s_color
{
	int8_t	channel[4];
}					t_color;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_complex		min;
	t_complex		max;
	int				max_iter;
	t_complex		delta;
	t_color			color;
	int				fractal_index;
	t_complex		c;
	t_complex		z;
	t_complex		z2;
	int				color_shift;
	int				julia_set;
	int				use_threading;
	int				use_antialiasing;
	int				fractal_power;
	int				pan_active;
	t_complex		pan_start_coord;
	int				**iteration_buffer;
	t_complex		**z_buffer;
}					t_data;

typedef struct s_thread_data
{
	t_data		*data;
	int			start_y;
	int			end_y;
	int			thread_id;
}				t_thread_data;

void		free_all(t_data *data, int state);
void		free_all_ok(t_data *data);
void		free_all_error(t_data *data, int state, char *error);

void		color(t_data *data, int n, int x, int y, t_complex z);
int			create_trgb(int t, int r, int g, int b);
int			get_color_default(int n, t_data *data);
int			get_color_palette(int n, t_data *data);
int			get_color_2(int iteration, t_data *data);
int			hsv_to_rgb(double h, double s, double v);
int			get_smooth_color(double iteration, t_complex z, t_data *data);
int			get_fire_palette(int iteration, t_data *data);
int			get_ice_palette(int iteration, t_data *data);
int			get_psychedelic_palette(int n, t_data *data);
int			get_ocean_palette(int n, t_data *data);
int			get_forest_palette(int n, t_data *data);
int			get_greyscale_palette(int n, t_data *data);
int			get_vintage_palette(int n, t_data *data);
int			get_angle_color(int n, t_complex z, t_data *data);
int			get_palette_color(int n, t_complex z, t_data *data);

int			calculate_fractal_iterations(t_data *data, t_complex c);
int			get_iterations_at_pixel(t_data *data, int x, int y);
int			get_antialiased_color(t_data *data, int x, int y);
int			needs_antialiasing(t_data *data, int x, int y);
void		color_with_antialiasing(t_data *data, int n, int x, int y);

void		change_type(int key, t_data *data);
void		change_color_shift(t_data *data);
void		change_param_key(int key, t_data *data);
void		change_max_iteration(int key, t_data *data);
void		move(int key, t_data *data);
void		change_multibrot_power(int key, t_data *data);
void		handle_export_and_config(int key, t_data *data);

int			key_press(int key, t_data *data);
int			mouse_press_hook(int button, int x, int y, t_data *data);
int			mouse_release_hook(int button, int x, int y, t_data *data);
int			mouse_motion_hook(int x, int y, t_data *data);
int			zoom_at_point(int button, int x, int y, t_data *data);
int			set_julia_c_from_mouse(int x, int y, t_data *data);
int			cycle_julia_presets(t_data *data);
t_complex screen_to_world(int x, int y, t_data *data);
void		hooks(t_data *data);
void		toggle_threading(t_data *data);
void		toggle_antialiasing(t_data *data);

void		white_image(t_data *data);
void		*init_img(t_data *data, char *argv);
void		*init_defaults(t_data *f);
t_complex	init_complex(double re, double im);

void		start_draw(t_data *data);
void		render_fractal(t_data *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

int			ft_print_help(void);
void		fractal_list(void);

void		julia(t_data *f);
void		mandelbrot(t_data *f);
void		tricorn(t_data *f);
void		barnsley(t_data *data);

void		julia_threaded(t_data *f);
void		mandelbrot_threaded(t_data *f);
void		tricorn_threaded(t_data *f);
void		*mandelbrot_thread(void *thread_data);
void		*julia_thread(void *thread_data);
void		*tricorn_thread(void *thread_data);
int			get_optimal_threads(void);

void		burning_ship(t_data *data);
void		newton(t_data *data);
void		multibrot(t_data *data);
void		mandelbar(t_data *data);
void		phoenix(t_data *data);
t_complex	complex_add(t_complex a, t_complex b);
t_complex	complex_multiply(t_complex a, t_complex b);
t_complex	complex_divide(t_complex a, t_complex b);
t_complex	complex_power(t_complex z, int n);
double		complex_magnitude_squared(t_complex z);

int			export_bmp(t_data *data, const char *filename);
void		export_ppm(t_data *data, const char *filename);
void		export_image(t_data *data, const char *filename_base, const char *format);
void		quick_export(t_data *data);
void		create_zoom_animation(t_data *data, const char *prefix, int frames);
void		create_color_animation(t_data *data, const char *prefix, int frames);

int			save_config(t_data *data, const char *filename);
int			load_config(t_data *data, const char *filename);

void		infinite_zoom(t_data *data);

void render_pixels_from_buffer(t_data *data);

void		enhanced_infinite_zoom(t_data *data);
void		spiral_zoom_animation(t_data *data);
void		julia_morph_animation(t_data *data);
void		fractal_showcase_animation(t_data *data);
void		color_palette_showcase(t_data *data);

# ifndef MIN
#  define MIN(a,b) (((a)<(b))?(a):(b))
# endif
# ifndef MAX
#  define MAX(a,b) (((a)>(b))?(a):(b))
# endif

#endif