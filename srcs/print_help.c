/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:18:08 by thi-le            #+#    #+#             */
/*   Updated: 2023/03/12 11:00:00 by Your Name         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	fractal_list(void)
{
	ft_putendl("\033[32;1m\tUsage: ./fractol <fractal_name or number> [julia_real julia_imag]\033[0;36m");
	ft_putendl("\tAvailable fractals:");
	ft_putendl("\t1 - Mandelbrot\n\t2 - Julia\n\t3 - Barnsley\n\t4 - Tricorn");
	ft_putendl("\t5 - Burning Ship\n\t6 - Newton\n\t7 - Phoenix\n\t8 - Buffalo (Mandelbar)");
	ft_putendl("\t9 - Multibrot");
	ft_putendl("\nYou can use either the name or the number (e.g. ./fractol 1 or ./fractol mandelbrot)");
	ft_putendl("For Julia, you may specify C_real and C_imaginary values.");
	ft_putendl("\033[32;1m\tExample: ./fractol julia 0.285 0.01 or ./fractol 2 0.285 0.01\033[0;36m");
	ft_putendl("\033[32;1m\tExample: ./fractol multibrot\033[0;36m");
}

static void	keyboard_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mKeyboard controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in the mlx window");
	ft_putendl("\n\t\033[33mNavigation & View:\033[36m");
	ft_putendl("\t- Move view: Arrow Keys (Up, Down, Left, Right)");
	ft_putendl("\t- Reset view: R");
	ft_putendl("\n\t\033[33mFractal Selection & Parameters:\033[36m");
	ft_putendl("\t- Select fractal (1-9): 1=Mandelbrot, 2=Julia, 3=Barnsley, 4=Tricorn,");
	ft_putendl("\t  5=Burning Ship, 6=Newton, 7=Phoenix, 8=Buffalo, 9=Multibrot");
	ft_putendl("\t- Change Julia C params (interactive): W(+Im), S(-Im), D(+Re), Q(-Re)");
	ft_putendl("\t- Change Multibrot power (for Multibrot only): PageUp (increase), PageDown (decrease)");
	ft_putendl("\n\t\033[33mRendering & Color:\033[36m");
	ft_putendl("\t- Change color palette (C) - Cycles through 13 beautiful palettes");
	ft_putendl("\t- Adjust max iterations: + (increase), - (decrease)");
	ft_putendl("\t- Toggle multi-threading (T)");
	ft_putendl("\t- Toggle anti-aliasing (A) - Smoother edges");
	ft_putendl("\n\t\033[33mExport & Animation:\033[36m");
	ft_putendl("\t- Quick export current view as BMP (E) - Timestamped filename");
	ft_putendl("\t- Generate zoom animation frames (Z)");
	ft_putendl("\t- Generate color animation frames (X)");
	ft_putendl("\n\t\033[33mLive Animations & Showcases:\033[36m");
	ft_putendl("\t- Basic infinite zoom (I) - Simple zoom animation");
	ft_putendl("\t- Enhanced infinite zoom (U) - Smooth targeting with color cycling");
	ft_putendl("\t- Spiral zoom animation (Y) - Zoom with rotation effects");
	ft_putendl("\t- Julia morphing animation (J) - Smooth parameter transitions (Julia sets only)");
	ft_putendl("\t- Fractal showcase tour (H) - Auto-tour through all fractal types");
	ft_putendl("\t- Color palette showcase (G) - Cycle through all 13 color palettes");
	ft_putendl("\n\t\033[33mConfiguration:\033[36m");
	ft_putendl("\t- Save current view/settings (O) - To fractal_config.txt");
	ft_putendl("\t- Load view/settings (L) - From fractal_config.txt");
	ft_putendl("\n\t\033[33mSystem:\033[36m");
	ft_putendl("\t- Close window and exit (ESC)");
}

static void	mouse_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mMouse controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in the mlx window");
	ft_putendl("\n\t- Zoom in/out: Mouse Scroll Wheel (zooms towards cursor position)");
	ft_putendl("\t- Pan view: Left-Click and Drag");
	ft_putendl("\t- Julia specific:");
	ft_putendl("\t    - Set C params (interactive): Left Click (without dragging) when Julia is active");
	ft_putendl("\t    - Cycle Julia presets: Right Click");
}

static void	features_info(void)
{
	ft_putendl("\n\033[0m\033[32;1mAdvanced Features Overview:\033[0;36m");
	ft_putendl("\n\t\033[33mExtended Fractal Library:\033[36m Explore 9 types including Mandelbrot, Julia, Tricorn, Multibrot, etc.");
	ft_putendl("\t\033[33mOptimized Color Palettes:\033[36m 13 beautiful schemes with smooth interpolation.");
	ft_putendl("\t\033[33mMulti-threading & Anti-aliasing:\033[36m For faster and smoother rendering.");
	ft_putendl("\t\033[33mImage Export:\033[36m Save views as BMP or PPM. Create zoom/color animations.");
	ft_putendl("\t\033[33mConfiguration System:\033[36m Save and load your favorite fractal views and settings.");
	ft_putendl("\t\033[33mInteractive Navigation:\033[36m Mouse panning, scroll zoom, keyboard controls.");
}

int	ft_print_help(void)
{
	ft_putendl_fd("\n+================================================================================+", 1);
	ft_putendl_fd("|                                FRACT'OL                                |", 1);
	ft_putendl_fd("|                         Enhanced Fractal Explorer                          |", 1);
	ft_putendl_fd("+================================================================================+\n", 1);
	fractal_list();
	keyboard_controls();
	mouse_controls();
	features_info();
	ft_putendl("\n\033[0m\033[32;1mQuick Start Examples:\033[0;36m");
	ft_putendl("  ./fractol mandelbrot");
	ft_putendl("  ./fractol julia -0.745 0.113");
	ft_putendl("  ./fractol multibrot");
	ft_putendl("\n\033[0m\033[32;1mBasic Interaction:[0;36m");
	ft_putendl("  - Scroll mouse wheel to zoom.");
	ft_putendl("  - Left-click and drag to pan the view.");
	ft_putendl("  - Use Arrow Keys to move the view.");
	ft_putendl("  - Press 'C' to cycle through color palettes.");
	ft_putendl("  - Press 'A' to toggle anti-aliasing.");
	ft_putendl("  - Press keys 1-9 to switch fractals.");
	ft_putendl("  - Press 'E' to quick-export current view as BMP.");
	ft_putendl("\n\033[0m\033[32;1mAwesome Animations:\033[0;36m");
	ft_putendl("  - Press 'U' for enhanced infinite zoom with color cycling!");
	ft_putendl("  - Press 'Y' for spiral zoom animation!");
	ft_putendl("  - Press 'H' for automatic fractal showcase tour!");
	ft_putendl("  - Press 'G' for color palette showcase!");
	ft_putendl("  - Press 'J' for Julia set morphing (Julia sets only)!");
	ft_putendl("\n\033[0m");
	return (0);
}
