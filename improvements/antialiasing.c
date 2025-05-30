/* Anti-aliasing Implementation */
#include "fractol.h"

// Multi-sample anti-aliasing (MSAA)
void render_with_antialiasing(t_data *data, int samples)
{
    double sample_offsets[][2] = {
        {0.25, 0.25}, {0.75, 0.25}, {0.25, 0.75}, {0.75, 0.75}  // 4x MSAA
    };
    
    for (int y = 0; y < W_HEIGHT; y++) {
        for (int x = 0; x < W_WIDTH; x++) {
            int total_r = 0, total_g = 0, total_b = 0;
            
            for (int s = 0; s < samples; s++) {
                double sub_x = x + sample_offsets[s][0];
                double sub_y = y + sample_offsets[s][1];
                
                t_complex c;
                c.re = data->min.re + sub_x * data->delta.re;
                c.im = data->max.im - sub_y * data->delta.im;
                
                int iterations = calculate_fractal_at_point(data, c);
                int color = get_color_smooth(iterations, data);
                
                total_r += (color >> 16) & 0xFF;
                total_g += (color >> 8) & 0xFF;
                total_b += color & 0xFF;
            }
            
            int final_color = create_trgb(0, 
                total_r / samples,
                total_g / samples, 
                total_b / samples);
                
            my_mlx_pixel_put(data, x, y, final_color);
        }
    }
}

// Adaptive sampling based on gradient
int needs_supersampling(t_data *data, int x, int y)
{
    if (x == 0 || y == 0 || x >= W_WIDTH-1 || y >= W_HEIGHT-1)
        return 0;
        
    // Calculate iterations at neighboring pixels
    int center = get_iterations_at_pixel(data, x, y);
    int neighbors[4] = {
        get_iterations_at_pixel(data, x-1, y),
        get_iterations_at_pixel(data, x+1, y),
        get_iterations_at_pixel(data, x, y-1),
        get_iterations_at_pixel(data, x, y+1)
    };
    
    // Check for high gradient (edge detection)
    for (int i = 0; i < 4; i++) {
        if (abs(center - neighbors[i]) > data->max_iter * 0.1)
            return 1;
    }
    return 0;
}
