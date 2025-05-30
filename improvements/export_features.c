/* Image Export and Animation Features */
#include "fractol.h"
#include <time.h>

// Export current fractal as PNG/BMP
void export_image(t_data *data, const char *filename, const char *format)
{
    if (strcmp(format, "bmp") == 0) {
        export_bmp(data, filename);
    } else if (strcmp(format, "ppm") == 0) {
        export_ppm(data, filename);
    }
}

// Simple BMP export
void export_bmp(t_data *data, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (!file) return;
    
    int width = W_WIDTH;
    int height = W_HEIGHT;
    int padding = (4 - (width * 3) % 4) % 4;
    int file_size = 54 + (width * 3 + padding) * height;
    
    // BMP Header
    unsigned char header[54] = {
        'B', 'M',           // Signature
        0, 0, 0, 0,         // File size (filled below)
        0, 0, 0, 0,         // Reserved
        54, 0, 0, 0,        // Data offset
        40, 0, 0, 0,        // Header size
        0, 0, 0, 0,         // Width (filled below)
        0, 0, 0, 0,         // Height (filled below)
        1, 0,               // Planes
        24, 0,              // Bits per pixel
        0, 0, 0, 0,         // Compression
        0, 0, 0, 0,         // Image size
        0, 0, 0, 0,         // X pixels per meter
        0, 0, 0, 0,         // Y pixels per meter
        0, 0, 0, 0,         // Colors used
        0, 0, 0, 0          // Important colors
    };
    
    // Fill in file size, width, height
    *(int*)&header[2] = file_size;
    *(int*)&header[18] = width;
    *(int*)&header[22] = height;
    
    fwrite(header, 1, 54, file);
    
    // Write pixel data (BMP is bottom-up)
    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            int color = get_pixel_color(data, x, y);
            unsigned char pixel[3] = {
                color & 0xFF,           // Blue
                (color >> 8) & 0xFF,    // Green
                (color >> 16) & 0xFF    // Red
            };
            fwrite(pixel, 1, 3, file);
        }
        // Write padding
        for (int p = 0; p < padding; p++) {
            fputc(0, file);
        }
    }
    
    fclose(file);
}

// PPM export (simpler format)
void export_ppm(t_data *data, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file) return;
    
    fprintf(file, "P3\n%d %d\n255\n", W_WIDTH, W_HEIGHT);
    
    for (int y = 0; y < W_HEIGHT; y++) {
        for (int x = 0; x < W_WIDTH; x++) {
            int color = get_pixel_color(data, x, y);
            int r = (color >> 16) & 0xFF;
            int g = (color >> 8) & 0xFF;
            int b = color & 0xFF;
            fprintf(file, "%d %d %d ", r, g, b);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

// Create zoom animation sequence
void create_zoom_animation(t_data *data, t_complex center, int frames, double zoom_factor)
{
    char filename[256];
    time_t timestamp = time(NULL);
    
    double initial_width = data->max.re - data->min.re;
    double initial_height = data->max.im - data->min.im;
    
    for (int frame = 0; frame < frames; frame++) {
        double progress = (double)frame / (frames - 1);
        double current_zoom = pow(zoom_factor, progress);
        
        double new_width = initial_width / current_zoom;
        double new_height = initial_height / current_zoom;
        
        data->min.re = center.re - new_width / 2;
        data->max.re = center.re + new_width / 2;
        data->min.im = center.im - new_height / 2;
        data->max.im = center.im + new_height / 2;
        
        data->delta.re = (data->max.re - data->min.re) / (W_WIDTH - 1);
        data->delta.im = (data->max.im - data->min.im) / (W_HEIGHT - 1);
        
        render_fractal(data);
        
        snprintf(filename, sizeof(filename), "animation_%ld_frame_%04d.bmp", 
                timestamp, frame);
        export_bmp(data, filename);
        
        printf("Exported frame %d/%d\n", frame + 1, frames);
    }
}

// Color cycling animation
void create_color_animation(t_data *data, int frames)
{
    char filename[256];
    time_t timestamp = time(NULL);
    int original_color_shift = data->color_shift;
    
    for (int frame = 0; frame < frames; frame++) {
        data->color_shift = (frame * 8) / frames;
        render_fractal(data);
        
        snprintf(filename, sizeof(filename), "color_anim_%ld_frame_%04d.bmp", 
                timestamp, frame);
        export_bmp(data, filename);
        
        printf("Exported color frame %d/%d\n", frame + 1, frames);
    }
    
    data->color_shift = original_color_shift;
    render_fractal(data);
}
