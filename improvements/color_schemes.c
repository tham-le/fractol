/* Enhanced Color Schemes for Fractal Rendering */
#include "fractol.h"
#include <math.h>

// Smooth color interpolation
int get_smooth_color(double iteration, t_data *data)
{
    double smooth_iter = iteration + 1 - log(log(sqrt(data->z2.re + data->z2.im)))/log(2);
    double t = fmod(smooth_iter * 0.1, 1.0);
    
    // HSV to RGB conversion for smooth gradients
    double h = t * 360.0;
    double s = 1.0;
    double v = 1.0;
    
    return hsv_to_rgb(h, s, v);
}

// Fire palette
int get_fire_palette(int iteration, t_data *data)
{
    const int fire_colors[] = {
        0x000000, 0x440000, 0x880000, 0xCC0000,
        0xFF0000, 0xFF4400, 0xFF8800, 0xFFCC00,
        0xFFFF00, 0xFFFF88, 0xFFFFCC, 0xFFFFFF
    };
    
    int index = (iteration * 12) / data->max_iter;
    return fire_colors[index % 12];
}

// Ice palette
int get_ice_palette(int iteration, t_data *data)
{
    const int ice_colors[] = {
        0x000044, 0x000088, 0x0000CC, 0x0044CC,
        0x0088CC, 0x00CCFF, 0x44CCFF, 0x88CCFF,
        0xCCFFFF, 0xFFFFFF
    };
    
    int index = (iteration * 10) / data->max_iter;
    return ice_colors[index % 10];
}

// Psychedelic palette with sine waves
int get_psychedelic_color(int iteration, t_data *data)
{
    double t = (double)iteration / data->max_iter;
    
    int r = (int)(128 + 127 * sin(t * 6.28 * 2 + data->color_shift));
    int g = (int)(128 + 127 * sin(t * 6.28 * 3 + data->color_shift + 2));
    int b = (int)(128 + 127 * sin(t * 6.28 * 5 + data->color_shift + 4));
    
    return create_trgb(0, r, g, b);
}
