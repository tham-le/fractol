/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-le <thi-le@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:00:00 by thi-le            #+#    #+#             */
/*   Updated: 2023/01/25 10:00:00 by thi-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <sys/time.h>
#include <string.h>

typedef struct s_profiler
{
	struct timeval	start_time;
	struct timeval	end_time;
	double			render_times[100];
	int				render_count;
	double			total_time;
	double			average_time;
	double			min_time;
	double			max_time;
	int				fps_counter;
	struct timeval	fps_start;
}	t_profiler;

static t_profiler	g_profiler = {0};

// Start timing
void	profiler_start(void)
{
	gettimeofday(&g_profiler.start_time, NULL);
}

// End timing and calculate stats
void	profiler_end(t_data *data)
{
	double	elapsed;

	(void)data;  // Mark parameter as unused
	gettimeofday(&g_profiler.end_time, NULL);
	elapsed = (g_profiler.end_time.tv_sec - g_profiler.start_time.tv_sec) * 1000.0;
	elapsed += (g_profiler.end_time.tv_usec - g_profiler.start_time.tv_usec) / 1000.0;
	
	g_profiler.render_times[g_profiler.render_count % 100] = elapsed;
	g_profiler.render_count++;
	
	// Update statistics
	g_profiler.total_time += elapsed;
	g_profiler.average_time = g_profiler.total_time / g_profiler.render_count;
	
	if (g_profiler.render_count == 1 || elapsed < g_profiler.min_time)
		g_profiler.min_time = elapsed;
	if (g_profiler.render_count == 1 || elapsed > g_profiler.max_time)
		g_profiler.max_time = elapsed;
}

// Display performance statistics
void	show_performance_stats(void)
{
	int		recent_count;
	double	recent_average;
	int		i;

	recent_count = (g_profiler.render_count < 10) ? g_profiler.render_count : 10;
	recent_average = 0;
	
	for (i = 0; i < recent_count; i++)
	{
		int index = (g_profiler.render_count - i - 1) % 100;
		recent_average += g_profiler.render_times[index];
	}
	recent_average /= recent_count;
	
	printf("\n=== PERFORMANCE STATISTICS ===\n");
	printf("Total renders: %d\n", g_profiler.render_count);
	printf("Average render time: %.2f ms\n", g_profiler.average_time);
	printf("Recent average (last %d): %.2f ms\n", recent_count, recent_average);
	printf("Min render time: %.2f ms\n", g_profiler.min_time);
	printf("Max render time: %.2f ms\n", g_profiler.max_time);
	printf("Average FPS: %.1f\n", 1000.0 / g_profiler.average_time);
	printf("Recent FPS: %.1f\n", 1000.0 / recent_average);
	printf("==============================\n\n");
}

// Benchmark threading performance
void	benchmark_threading(t_data *data)
{
	double	threaded_times[5];
	double	non_threaded_times[5];
	double	threaded_avg;
	double	non_threaded_avg;
	int		original_threading;
	int		i;

	printf("Starting threading benchmark...\n");
	original_threading = data->use_threading;
	
	// Non-threaded test
	data->use_threading = 0;
	non_threaded_avg = 0;
	for (i = 0; i < 5; i++)
	{
		profiler_start();
		render_fractal(data);
		profiler_end(data);
		non_threaded_times[i] = g_profiler.render_times[(g_profiler.render_count - 1) % 100];
		non_threaded_avg += non_threaded_times[i];
		printf("Non-threaded run %d: %.2f ms\n", i + 1, non_threaded_times[i]);
	}
	non_threaded_avg /= 5;
	
	// Threaded test
	data->use_threading = 1;
	threaded_avg = 0;
	for (i = 0; i < 5; i++)
	{
		profiler_start();
		render_fractal(data);
		profiler_end(data);
		threaded_times[i] = g_profiler.render_times[(g_profiler.render_count - 1) % 100];
		threaded_avg += threaded_times[i];
		printf("Threaded run %d: %.2f ms\n", i + 1, threaded_times[i]);
	}
	threaded_avg /= 5;
	
	// Results
	printf("\n=== THREADING BENCHMARK RESULTS ===\n");
	printf("Non-threaded average: %.2f ms (%.1f FPS)\n", non_threaded_avg, 1000.0 / non_threaded_avg);
	printf("Threaded average: %.2f ms (%.1f FPS)\n", threaded_avg, 1000.0 / threaded_avg);
	printf("Speedup: %.2fx\n", non_threaded_avg / threaded_avg);
	printf("Performance improvement: %.1f%%\n", ((non_threaded_avg - threaded_avg) / non_threaded_avg) * 100);
	printf("===================================\n\n");
	
	data->use_threading = original_threading;
}

// Get system information
void	show_system_info(void)
{
	FILE	*file;
	char	line[256];
	int		cpu_cores;

	cpu_cores = sysconf(_SC_NPROCESSORS_ONLN);
	
	printf("\n=== SYSTEM INFORMATION ===\n");
	printf("CPU cores available: %d\n", cpu_cores);
	printf("Window size: %dx%d pixels\n", W_WIDTH, W_HEIGHT);
	printf("Total pixels: %d\n", W_WIDTH * W_HEIGHT);
	
	// Try to get CPU info
	file = fopen("/proc/cpuinfo", "r");
	if (file)
	{
		while (fgets(line, sizeof(line), file))
		{
			if (strncmp(line, "model name", 10) == 0)
			{
				char *name = strchr(line, ':');
				if (name)
				{
					name += 2; // Skip ": "
					printf("CPU: %s", name);
					break;
				}
			}
		}
		fclose(file);
	}
	printf("==========================\n\n");
}

// Benchmark fractal rendering performance
void	benchmark_fractal(t_data *data, int iterations)
{
	struct timeval	start_time, end_time;
	double			total_time = 0;
	double			min_time = 1000.0;
	double			max_time = 0;
	int				original_threading;
	
	printf("\n=== FRACTAL BENCHMARK ===\n");
	printf("Running %d iterations...\n", iterations);
	
	// Save original threading state
	original_threading = data->use_threading;
	
	// Benchmark without threading
	data->use_threading = 0;
	total_time = 0;
	printf("\nSingle-threaded performance:\n");
	
	for (int i = 0; i < iterations; i++)
	{
		gettimeofday(&start_time, NULL);
		render_fractal(data);
		gettimeofday(&end_time, NULL);
		
		double frame_time = (end_time.tv_sec - start_time.tv_sec) + 
			(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
		
		total_time += frame_time;
		if (frame_time < min_time) min_time = frame_time;
		if (frame_time > max_time) max_time = frame_time;
		
		printf("  Iteration %d: %.3f seconds\n", i + 1, frame_time);
	}
	
	printf("Single-thread Average: %.3f seconds\n", total_time / iterations);
	printf("Single-thread Min: %.3f seconds\n", min_time);
	printf("Single-thread Max: %.3f seconds\n", max_time);
	printf("Single-thread FPS: %.2f\n", 1.0 / (total_time / iterations));
	
	// Benchmark with threading
	data->use_threading = 1;
	total_time = 0;
	min_time = 1000.0;
	max_time = 0;
	printf("\nMulti-threaded performance:\n");
	
	for (int i = 0; i < iterations; i++)
	{
		gettimeofday(&start_time, NULL);
		render_fractal(data);
		gettimeofday(&end_time, NULL);
		
		double frame_time = (end_time.tv_sec - start_time.tv_sec) + 
			(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
		
		total_time += frame_time;
		if (frame_time < min_time) min_time = frame_time;
		if (frame_time > max_time) max_time = frame_time;
		
		printf("  Iteration %d: %.3f seconds\n", i + 1, frame_time);
	}
	
	printf("Multi-thread Average: %.3f seconds\n", total_time / iterations);
	printf("Multi-thread Min: %.3f seconds\n", min_time);
	printf("Multi-thread Max: %.3f seconds\n", max_time);
	printf("Multi-thread FPS: %.2f\n", 1.0 / (total_time / iterations));
	
	// Restore original threading state
	data->use_threading = original_threading;
	
	printf("=========================\n\n");
}

// Start profiling timer
void	start_profiling(void)
{
	profiler_start();
}

// End profiling and return elapsed time
double	end_profiling(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	
	return (current_time.tv_sec - g_profiler.start_time.tv_sec) + 
		(current_time.tv_usec - g_profiler.start_time.tv_usec) / 1000000.0;
}

// Print performance statistics
void	print_performance_stats(t_data *data)
{
	(void)data;
	show_performance_stats();
}
