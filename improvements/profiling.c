/* Performance Profiling System */
#include "fractol.h"
#include <sys/time.h>
#include <stdio.h>

typedef struct s_profiler {
    struct timeval start_time;
    struct timeval end_time;
    double render_times[100];  // Store last 100 render times
    int render_count;
    double total_render_time;
    double min_render_time;
    double max_render_time;
    int threading_samples;
    int non_threading_samples;
    double threading_avg;
    double non_threading_avg;
} t_profiler;

static t_profiler g_profiler = {0};

void profiler_start(void)
{
    gettimeofday(&g_profiler.start_time, NULL);
}

void profiler_end(t_data *data)
{
    gettimeofday(&g_profiler.end_time, NULL);
    
    double elapsed = (g_profiler.end_time.tv_sec - g_profiler.start_time.tv_sec) * 1000.0;
    elapsed += (g_profiler.end_time.tv_usec - g_profiler.start_time.tv_usec) / 1000.0;
    
    // Store render time
    int index = g_profiler.render_count % 100;
    g_profiler.render_times[index] = elapsed;
    g_profiler.render_count++;
    
    // Update statistics
    g_profiler.total_render_time += elapsed;
    if (g_profiler.min_render_time == 0 || elapsed < g_profiler.min_render_time)
        g_profiler.min_render_time = elapsed;
    if (elapsed > g_profiler.max_render_time)
        g_profiler.max_render_time = elapsed;
    
    // Track threading vs non-threading performance
    if (data->use_threading) {
        g_profiler.threading_samples++;
        g_profiler.threading_avg = (g_profiler.threading_avg * (g_profiler.threading_samples - 1) + elapsed) / g_profiler.threading_samples;
    } else {
        g_profiler.non_threading_samples++;
        g_profiler.non_threading_avg = (g_profiler.non_threading_avg * (g_profiler.non_threading_samples - 1) + elapsed) / g_profiler.non_threading_samples;
    }
}

void profiler_print_stats(void)
{
    if (g_profiler.render_count == 0) {
        printf("No profiling data available.\n");
        return;
    }
    
    double avg_time = g_profiler.total_render_time / g_profiler.render_count;
    double fps = 1000.0 / avg_time;
    
    printf("\n=== Performance Statistics ===\n");
    printf("Total renders: %d\n", g_profiler.render_count);
    printf("Average render time: %.2f ms (%.1f FPS)\n", avg_time, fps);
    printf("Min render time: %.2f ms\n", g_profiler.min_render_time);
    printf("Max render time: %.2f ms\n", g_profiler.max_render_time);
    
    if (g_profiler.threading_samples > 0 && g_profiler.non_threading_samples > 0) {
        double speedup = g_profiler.non_threading_avg / g_profiler.threading_avg;
        printf("\nThreading Performance:\n");
        printf("With threading: %.2f ms avg (%d samples)\n", 
               g_profiler.threading_avg, g_profiler.threading_samples);
        printf("Without threading: %.2f ms avg (%d samples)\n", 
               g_profiler.non_threading_avg, g_profiler.non_threading_samples);
        printf("Speedup: %.2fx\n", speedup);
    }
    
    // Calculate recent performance (last 10 renders)
    if (g_profiler.render_count >= 10) {
        double recent_total = 0;
        int recent_count = MIN(10, g_profiler.render_count);
        int start_index = (g_profiler.render_count - recent_count) % 100;
        
        for (int i = 0; i < recent_count; i++) {
            int index = (start_index + i) % 100;
            recent_total += g_profiler.render_times[index];
        }
        
        double recent_avg = recent_total / recent_count;
        printf("Recent average (last %d): %.2f ms\n", recent_count, recent_avg);
    }
    printf("===============================\n\n");
}

// Benchmark different settings
void run_benchmark(t_data *data)
{
    printf("Running benchmark...\n");
    
    int original_threading = data->use_threading;
    int original_max_iter = data->max_iter;
    
    // Test different iteration counts
    printf("\nTesting different iteration counts:\n");
    int iter_tests[] = {50, 100, 200, 500, 1000};
    for (int i = 0; i < 5; i++) {
        data->max_iter = iter_tests[i];
        
        profiler_start();
        render_fractal(data);
        profiler_end(data);
        
        printf("Iterations %d: %.2f ms\n", iter_tests[i], 
               g_profiler.render_times[(g_profiler.render_count - 1) % 100]);
    }
    
    // Test threading vs non-threading
    printf("\nTesting threading performance:\n");
    data->max_iter = 200;  // Use moderate iteration count
    
    // Non-threaded test
    data->use_threading = 0;
    double non_threaded_times[5];
    for (int i = 0; i < 5; i++) {
        profiler_start();
        render_fractal(data);
        profiler_end(data);
        non_threaded_times[i] = g_profiler.render_times[(g_profiler.render_count - 1) % 100];
    }
    
    // Threaded test
    data->use_threading = 1;
    double threaded_times[5];
    for (int i = 0; i < 5; i++) {
        profiler_start();
        render_fractal(data);
        profiler_end(data);
        threaded_times[i] = g_profiler.render_times[(g_profiler.render_count - 1) % 100];
    }
    
    // Calculate averages
    double non_threaded_avg = 0, threaded_avg = 0;
    for (int i = 0; i < 5; i++) {
        non_threaded_avg += non_threaded_times[i];
        threaded_avg += threaded_times[i];
    }
    non_threaded_avg /= 5;
    threaded_avg /= 5;
    
    printf("Non-threaded average: %.2f ms\n", non_threaded_avg);
    printf("Threaded average: %.2f ms\n", threaded_avg);
    printf("Speedup: %.2fx\n", non_threaded_avg / threaded_avg);
    
    // Restore original settings
    data->use_threading = original_threading;
    data->max_iter = original_max_iter;
    
    printf("Benchmark complete!\n");
}
