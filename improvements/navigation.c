/* Advanced Navigation Features */
#include "fractol.h"

// Smooth zooming with interpolation
typedef struct s_zoom_animation {
    t_complex start_min, start_max;
    t_complex target_min, target_max;
    double progress;
    int duration_frames;
    int current_frame;
} t_zoom_animation;

void start_zoom_animation(t_data *data, t_complex center, double zoom_factor)
{
    t_zoom_animation *anim = &data->zoom_anim;
    
    anim->start_min = data->min;
    anim->start_max = data->max;
    
    double current_width = data->max.re - data->min.re;
    double current_height = data->max.im - data->min.im;
    double new_width = current_width / zoom_factor;
    double new_height = current_height / zoom_factor;
    
    anim->target_min.re = center.re - new_width / 2;
    anim->target_max.re = center.re + new_width / 2;
    anim->target_min.im = center.im - new_height / 2;
    anim->target_max.im = center.im + new_height / 2;
    
    anim->duration_frames = 30; // 30 frames animation
    anim->current_frame = 0;
    anim->progress = 0.0;
}

void update_zoom_animation(t_data *data)
{
    t_zoom_animation *anim = &data->zoom_anim;
    
    if (anim->current_frame >= anim->duration_frames)
        return;
    
    // Easing function for smooth animation
    double t = (double)anim->current_frame / anim->duration_frames;
    double eased_t = t * t * (3.0 - 2.0 * t); // Smoothstep
    
    data->min.re = lerp(anim->start_min.re, anim->target_min.re, eased_t);
    data->min.im = lerp(anim->start_min.im, anim->target_min.im, eased_t);
    data->max.re = lerp(anim->start_max.re, anim->target_max.re, eased_t);
    data->max.im = lerp(anim->start_max.im, anim->target_max.im, eased_t);
    
    anim->current_frame++;
    
    if (anim->current_frame < anim->duration_frames) {
        render_fractal(data);
    }
}

// Mouse gesture recognition
typedef struct s_gesture {
    int start_x, start_y;
    int current_x, current_y;
    int is_dragging;
    struct timeval start_time;
} t_gesture;

void handle_mouse_gesture(t_data *data, int x, int y, int button_state)
{
    static t_gesture gesture = {0};
    
    if (button_state == LEFT_CLICK) {
        gesture.start_x = x;
        gesture.start_y = y;
        gesture.is_dragging = 1;
        gettimeofday(&gesture.start_time, NULL);
    }
    else if (gesture.is_dragging) {
        gesture.current_x = x;
        gesture.current_y = y;
        
        // Pan the fractal view
        double dx = (gesture.current_x - gesture.start_x) * data->delta.re;
        double dy = (gesture.current_y - gesture.start_y) * data->delta.im;
        
        data->min.re -= dx;
        data->max.re -= dx;
        data->min.im += dy;
        data->max.im += dy;
        
        gesture.start_x = gesture.current_x;
        gesture.start_y = gesture.current_y;
        
        render_fractal(data);
    }
    else {
        gesture.is_dragging = 0;
    }
}

// Zoom to interesting areas automatically
void find_interesting_points(t_data *data)
{
    t_complex interesting_points[] = {
        {-0.7269, 0.1889},      // Mandelbrot spiral
        {-0.8, 0.156},          // Mandelbrot seahorse valley
        {-0.74529, 0.11307},    // Mandelbrot lightning
        {0.285, 0.0},           // Julia set interesting point
        {-0.4, 0.6},            // Julia set default
        {-0.8, 0.156}           // Another interesting area
    };
    
    int num_points = sizeof(interesting_points) / sizeof(t_complex);
    static int current_point = 0;
    
    start_zoom_animation(data, interesting_points[current_point], 2.0);
    current_point = (current_point + 1) % num_points;
}
