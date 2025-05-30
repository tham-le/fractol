/* Enhanced User Interface Features */
#include "fractol.h"

// On-screen display for parameters
void draw_info_overlay(t_data *data)
{
    char info_text[256];
    snprintf(info_text, sizeof(info_text), 
        "Fractal: %s | Iterations: %d | Threading: %s | Zoom: %.2e",
        get_fractal_name(data->fractal_index),
        data->max_iter,
        data->use_threading ? "ON" : "OFF",
        get_zoom_level(data));
    
    // Draw semi-transparent background
    draw_text_background(data, 10, 10, 400, 60);
    
    // Draw text (would need a text rendering library)
    draw_text(data, info_text, 15, 25, 0xFFFFFF);
}

// Minimap showing current view
void draw_minimap(t_data *data)
{
    int minimap_size = 150;
    int minimap_x = W_WIDTH - minimap_size - 10;
    int minimap_y = 10;
    
    // Draw minimap border
    draw_rectangle(data, minimap_x-2, minimap_y-2, 
                   minimap_size+4, minimap_size+4, 0xFFFFFF);
    
    // Render low-resolution fractal for minimap
    render_minimap_fractal(data, minimap_x, minimap_y, minimap_size);
    
    // Draw current view rectangle
    draw_view_indicator(data, minimap_x, minimap_y, minimap_size);
}

// Save/Load presets
typedef struct s_preset {
    char name[32];
    int fractal_type;
    t_complex min, max;
    t_complex c;
    int max_iter;
    int color_shift;
} t_preset;

void save_preset(t_data *data, const char *name)
{
    FILE *file = fopen("fractol_presets.dat", "ab");
    if (!file) return;
    
    t_preset preset;
    strncpy(preset.name, name, 31);
    preset.name[31] = '\0';
    preset.fractal_type = data->fractal_index;
    preset.min = data->min;
    preset.max = data->max;
    preset.c = data->c;
    preset.max_iter = data->max_iter;
    preset.color_shift = data->color_shift;
    
    fwrite(&preset, sizeof(t_preset), 1, file);
    fclose(file);
}

void load_preset(t_data *data, const char *name)
{
    FILE *file = fopen("fractol_presets.dat", "rb");
    if (!file) return;
    
    t_preset preset;
    while (fread(&preset, sizeof(t_preset), 1, file)) {
        if (strcmp(preset.name, name) == 0) {
            data->fractal_index = preset.fractal_type;
            data->min = preset.min;
            data->max = preset.max;
            data->c = preset.c;
            data->max_iter = preset.max_iter;
            data->color_shift = preset.color_shift;
            break;
        }
    }
    fclose(file);
}
