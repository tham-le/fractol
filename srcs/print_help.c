/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:18:08 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/24 17:10:34 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	fractal_list(void)
{
	ft_putendl("\033[32;1m\tUsage: ./fractol <fractal_name or number>\033[0;36m");
	ft_putendl("\tAvailable fractals:");
	ft_putendl("\t1 - Mandelbrot\n\t2 - Julia\n\t3 - Barnsley\n\t4 - Tricorn");
	ft_putendl("\t5 - Burning Ship\n\t6 - Newton\n\t7 - Phoenix\n\t8 - Buffalo");
	ft_putendl("You can use either the name or the number for <fractal_name> (e.g. ./fractol 1 or ./fractol mandelbrot)\n");
	ft_putendl("For Julia, you may specify starting values for the");
	ft_putendl("initial fractal shape. Values must contain a decimal point");
	ft_putendl("\033[32;1m\tExample: ./fractol julia 0.285 0.01 or ./fractol 2 0.285 0.01\033[0;36m");
}

static void	keyboard_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mKeyboard controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in the mlx window");
	ft_putendl("\n\t\033[33mNavigation:\033[36m");
	ft_putendl("\t- Move the view point (Arrow Keys: Up, Down, Left, Right)");
	ft_putendl("\t- Reset view point (R)");
	ft_putendl("\n\t\033[33mFractal Selection:\033[36m");
	ft_putendl("\t- Select fractal (1-8): 1=Mandelbrot, 2=Julia, 3=Barnsley,");
	ft_putendl("\t  4=Tricorn, 5=Burning Ship, 6=Newton, 7=Phoenix, 8=Mandelbar");
	ft_putendl("\n\t\033[33mRendering Options:\033[36m");
	ft_putendl("\t- Change color set (C) - 15 different palettes available");
	ft_putendl("\t- Change maximum iterations (+, -)");
	ft_putendl("\t- Toggle threading (T) - Enable/disable multi-threading");
	ft_putendl("\t- Toggle anti-aliasing (P) - Smooth edge rendering");
	ft_putendl("\n\t\033[33mJulia Parameters:\033[36m");
	ft_putendl("\t- Change Julia parameters: W(+Im), S(-Im), D(+Re), A(-Re)");
	ft_putendl("\n\t\033[33mExport & Animation:\033[36m");
	ft_putendl("\t- Export current fractal as BMP (E)");
	ft_putendl("\t- Create zoom animation (Z) - 30 frames zooming in");
	ft_putendl("\t- Create color animation (X) - 15 frames cycling colors");
	ft_putendl("\n\t\033[33mConfiguration:\033[36m");
	ft_putendl("\t- Save current settings (O) - Save to fractal_config.txt");
	ft_putendl("\t- Load saved settings (L) - Load from fractal_config.txt");
	ft_putendl("\n\t\033[33mPerformance:\033[36m");
	ft_putendl("\t- Run benchmark (B) - Test rendering performance");
	ft_putendl("\n\t\033[33mSystem:\033[36m");
	ft_putendl("\t- Close the window and exit the program (ESC)");
}

static void	mouse_controls(void)
{
	ft_putendl("\n\033[0m\033[32;1mMouse controls:\033[0;36m");
	ft_putendl("\n\tThe following inputs are handled in the mlx window");
	ft_putendl("\n\t- Zoom in/out (Mouse Scroll Wheel)");
	ft_putendl("\t- Change Julia set parameters (Left Click) - Interactive mode");
	ft_putendl("\t- Change Julia preset (Right Click) - Cycle through presets");
	ft_putendl("\n\t\033[33mTip:\033[36m Use mouse with Julia fractal for real-time parameter changes!");
}

static void	features_info(void)
{
	ft_putendl("\n\033[0m\033[32;1mAdvanced Features:\033[0;36m");
	ft_putendl("\n\t\033[33mAnti-aliasing:\033[36m Smooths fractal edges using 4x supersampling");
	ft_putendl("\t\033[33mMulti-threading:\033[36m Accelerates rendering using parallel processing");
	ft_putendl("\t\033[33mExport System:\033[36m Save fractals as high-quality BMP images");
	ft_putendl("\t\033[33mAnimation Creation:\033[36m Generate zoom and color-cycle animations");
	ft_putendl("\t\033[33mConfiguration System:\033[36m Save/load your favorite fractal settings");
	ft_putendl("\t\033[33mPerformance Benchmark:\033[36m Test and optimize rendering speed");
	ft_putendl("\t\033[33mEnhanced Color Palettes:\033[36m 15 beautiful color schemes including");
	ft_putendl("\t  HSV gradients, fire/ice themes, and smooth interpolation");
	ft_putendl("\t\033[33mExtended Fractal Library:\033[36m 8 different fractal types to explore");
}

int	ft_print_help(void)
{
	ft_putendl_fd("\n+====================================================+", 1);
	ft_putendl_fd("|                     FRACT'OL                      |", 1);
	ft_putendl_fd("|              Enhanced Fractal Explorer             |", 1);
	ft_putendl_fd("+====================================================+\n", 1);
	fractal_list();
	keyboard_controls();
	mouse_controls();
	features_info();
	ft_putendl("\n\033[0m\033[32;1mQuick Start:\033[0;36m");
	ft_putendl("1. Run: ./fractol mandelbrot");
	ft_putendl("2. Use scroll wheel to zoom, arrow keys to move");
	ft_putendl("3. Press 'C' to cycle through color palettes");
	ft_putendl("4. Press 'P' to toggle anti-aliasing for smoother edges");
	ft_putendl("5. Try different fractals with keys 1-8");
	ft_putendl("6. Press 'E' to export your favorite view as BMP");
	ft_putendl("\n\033[0m");
	return (0);
}
