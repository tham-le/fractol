/* Configuration System */
#include "fractol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_config {
    int window_width;
    int window_height;
    int max_iterations;
    int default_fractal;
    int threading_enabled;
    int default_color_scheme;
    double zoom_speed;
    double movement_speed;
    char default_julia_real[32];
    char default_julia_imag[32];
} t_config;

// Load configuration from file
int load_config(t_config *config, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        // Set default values
        config->window_width = 900;
        config->window_height = 900;
        config->max_iterations = 100;
        config->default_fractal = MANDELBROT;
        config->threading_enabled = 1;
        config->default_color_scheme = 0;
        config->zoom_speed = 1.5;
        config->movement_speed = 0.1;
        strcpy(config->default_julia_real, "-0.4");
        strcpy(config->default_julia_imag, "0.6");
        return 0;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char key[64], value[192];
        if (sscanf(line, "%63s = %191s", key, value) == 2) {
            if (strcmp(key, "window_width") == 0)
                config->window_width = atoi(value);
            else if (strcmp(key, "window_height") == 0)
                config->window_height = atoi(value);
            else if (strcmp(key, "max_iterations") == 0)
                config->max_iterations = atoi(value);
            else if (strcmp(key, "default_fractal") == 0)
                config->default_fractal = atoi(value);
            else if (strcmp(key, "threading_enabled") == 0)
                config->threading_enabled = atoi(value);
            else if (strcmp(key, "default_color_scheme") == 0)
                config->default_color_scheme = atoi(value);
            else if (strcmp(key, "zoom_speed") == 0)
                config->zoom_speed = atof(value);
            else if (strcmp(key, "movement_speed") == 0)
                config->movement_speed = atof(value);
            else if (strcmp(key, "julia_real") == 0)
                strncpy(config->default_julia_real, value, 31);
            else if (strcmp(key, "julia_imag") == 0)
                strncpy(config->default_julia_imag, value, 31);
        }
    }
    
    fclose(file);
    return 1;
}

// Save configuration to file
void save_config(const t_config *config, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file) return;
    
    fprintf(file, "# Fractol Configuration File\n");
    fprintf(file, "window_width = %d\n", config->window_width);
    fprintf(file, "window_height = %d\n", config->window_height);
    fprintf(file, "max_iterations = %d\n", config->max_iterations);
    fprintf(file, "default_fractal = %d\n", config->default_fractal);
    fprintf(file, "threading_enabled = %d\n", config->threading_enabled);
    fprintf(file, "default_color_scheme = %d\n", config->default_color_scheme);
    fprintf(file, "zoom_speed = %.2f\n", config->zoom_speed);
    fprintf(file, "movement_speed = %.2f\n", config->movement_speed);
    fprintf(file, "julia_real = %s\n", config->default_julia_real);
    fprintf(file, "julia_imag = %s\n", config->default_julia_imag);
    
    fclose(file);
}

// Apply configuration to data structure
void apply_config(t_data *data, const t_config *config)
{
    data->max_iter = config->max_iterations;
    data->fractal_index = config->default_fractal;
    data->use_threading = config->threading_enabled;
    data->color_shift = config->default_color_scheme;
    
    if (data->fractal_index == JULIA) {
        data->c.re = atof(config->default_julia_real);
        data->c.im = atof(config->default_julia_imag);
    }
}
