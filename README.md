# Fractol - Advanced Fractal Explorer

**High-performance fractal visualization in C with multi-threading and advanced graphics**

> **Note:** This project extends the original 42 School fract-ol assignment with advanced features demonstrating systems programming, optimization, and graphics expertise. Please enjoy peer-learning at 42 - don't copy.

## Technical Achievements

**Core Technologies:** C, MinilibX, POSIX threads, Computer Graphics
**Performance:** Multi-threaded rendering with 2-8x speed improvements
**Export Formats:** BMP, PPM with animation support

## Visual Showcase

**High-quality fractal renders demonstrating mathematical precision and artistic beauty:**

<div align="center">

### Mandelbrot Set - Color Variations
<img src="image/mandelbrot-smooth-color.bmp" width="300" alt="Mandelbrot Smooth Colors"/> <img src="image/mandelbrot-fire.bmp" width="300" alt="Mandelbrot Fire Palette"/>

### Newton Fractal - Advanced Mathematics
<img src="image/Newton.bmp" width="300" alt="Newton Fractal"/> <img src="image/Newton-rainbow.bmp" width="300" alt="Newton Rainbow"/>

### Julia Set Collection - Parameter Exploration
<img src="image/julia-1.bmp" width="200" alt="Julia Set 1"/> <img src="image/julia_2.bmp" width="200" alt="Julia Set 2"/> <img src="image/julia_3.bmp" width="200" alt="Julia Set 3"/> <img src="image/julia_6.bmp" width="200" alt="Julia Set 6"/>

### Barnsley Fern - Nature-Inspired Fractals
<img src="image/barnley.bmp" width="400" alt="Barnsley Fern"/>

</div>

*All images rendered in real-time with multi-threaded optimization*

### Key Features Beyond Original Assignment
- **Multi-threaded rendering** - Automatic CPU core detection and workload distribution
- **8 fractal types** - Mandelbrot, Julia, Burning Ship, Newton, Tricorn, Barnsley Fern, Mandelbar, Multibrot
- **13 optimized color palettes** - Real-time switching with smooth interpolation
- **Advanced interactions** - Mouse panning, scroll zoom, parameter modification
- **Export capabilities** - Image and animation export with timestamp management
- **Configuration system** - Save/load views and settings
- **Anti-aliasing** - Adaptive supersampling for quality rendering

## Installation & Usage

```bash
# Clone and build
git clone --recursive https://github.com/tham-le/fractol.git
cd fractol
make

# Run examples
./fractol mandelbrot
./fractol julia 0.285 0.01
./fractol help
```

## Technical Implementation

**Performance Optimizations:**
- Multi-threading with POSIX threads for parallel computation
- Efficient memory management and minimal overhead
- Adaptive algorithms based on fractal complexity

**Advanced Features:**
- Real-time parameter modification and smooth transitions
- Professional-grade color interpolation algorithms
- Cross-platform compatibility and robust error handling

**Interactive Controls:**
- Mouse-based navigation (drag to pan, scroll to zoom)
- Keyboard shortcuts for all features
- Real-time performance toggling and comparison


## Project Evolution

Started as a 42 School assignment and evolved into a comprehensive fractal explorer showcasing:
- Advanced C programming techniques
- Multi-threaded application development
- Graphics programming and mathematical computation
- Software engineering best practices

---

**A demonstration of technical growth and practical application of computer science fundamentals.**