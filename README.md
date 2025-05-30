# Fract'ol - Enhanced Fractal Explorer

![Fract'ol Banner](https://img.shields.io/badge/42-Paris-blue?style=for-the-badge&logo=42) ![C](https://img.shields.io/badge/C-Language-blue?style=for-the-badge&logo=c) ![MinilibX](https://img.shields.io/badge/MinilibX-Graphics-green?style=for-the-badge)

A high-performance, feature-rich fractal rendering engine built in C using MinilibX. This project explores the mathematical beauty of fractals through real-time visualization, offering multiple fractal types, advanced rendering features, and interactive controls.

## 🎨 Features

### Core Fractals (8 Types)
- **Mandelbrot Set** - The classic fractal showcasing infinite complexity
- **Julia Set** - Interactive fractal with customizable parameters
- **Barnsley Fern** - Nature-inspired fractal pattern
- **Tricorn** - Mandelbrot variant with conjugate complex numbers
- **Burning Ship** - Dramatic fractal with ship-like structures
- **Newton Fractal** - Based on Newton's method for finding roots
- **Multibrot** - Generalization of the Mandelbrot set
- **Mandelbar** - Another Mandelbrot variant with unique properties

### Advanced Rendering
- **Anti-aliasing** - 4x supersampling for smooth, professional-quality edges
- **Multi-threading** - Parallel processing for faster rendering
- **15 Color Palettes** - Including HSV gradients, fire/ice themes, and smooth interpolation
- **Real-time Navigation** - Smooth zooming and panning
- **Adaptive Performance** - Optimized algorithms for different fractal types

### Export & Animation
- **BMP Export** - Save high-quality fractal images
- **Zoom Animations** - Create mesmerizing zoom sequences (30 frames)
- **Color Animations** - Generate color-cycling videos (15 frames)
- **Batch Processing** - Export multiple variations automatically

### Configuration System
- **Save/Load Settings** - Preserve your favorite fractal configurations
- **Parameter Persistence** - Restore exact zoom levels, colors, and parameters
- **Quick Presets** - Store and recall multiple fractal setups

### Performance Tools
- **Benchmarking** - Test and optimize rendering performance
- **Threading Toggle** - Compare single vs multi-threaded performance
- **Memory Optimization** - Efficient algorithms for large-scale rendering

## 🚀 Installation

### Prerequisites
- GCC compiler
- X11 development libraries
- MinilibX library
- Make

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install gcc make libx11-dev libxext-dev
```

### Building
```bash
git clone <repository-url>
cd fract-ol
make
```

## 🎮 Usage

### Basic Usage
```bash
# Launch with Mandelbrot fractal
./fractol mandelbrot

# Launch with Julia fractal (default parameters)
./fractol julia

# Launch Julia with custom parameters
./fractol julia 0.285 0.01

# View all available fractals and controls
./fractol help
```

### Supported Fractal Names
- `mandelbrot` or `1`
- `julia` or `2` 
- `barnsley` or `3`
- `tricorn` or `4`
- `burning_ship` or `5`
- `newton` or `6`
- `multibrot` or `7`
- `mandelbar` or `8`

## 🎯 Controls

### Keyboard Controls

#### Navigation
- **Arrow Keys** - Move the viewport (Up, Down, Left, Right)
- **R** - Reset view to default position

#### Fractal Selection
- **1-8** - Switch between different fractal types
  - 1: Mandelbrot, 2: Julia, 3: Barnsley, 4: Tricorn
  - 5: Burning Ship, 6: Newton, 7: Multibrot, 8: Mandelbar

#### Rendering Options
- **C** - Cycle through 15 color palettes
- **+/-** - Increase/decrease iteration depth (affects detail level)
- **T** - Toggle multi-threading on/off
- **P** - Toggle anti-aliasing for smoother edges

#### Julia Parameters (Julia fractal only)
- **W** - Increase imaginary component
- **S** - Decrease imaginary component  
- **D** - Increase real component
- **A** - Decrease real component

#### Export & Animation
- **E** - Export current view as BMP image
- **Z** - Create zoom animation (30 frames)
- **X** - Create color animation (15 frames)

#### Configuration
- **O** - Save current settings to `fractal_config.txt`
- **L** - Load settings from `fractal_config.txt`

#### Performance
- **B** - Run performance benchmark

#### System
- **ESC** - Exit the program

### Mouse Controls
- **Scroll Wheel** - Zoom in/out at cursor position
- **Left Click** - Set Julia parameters (Julia fractal only)
- **Right Click** - Cycle through Julia presets

## 🎨 Color Palettes

The enhanced color system includes 15 beautiful palettes:

1. **Classic** - Traditional fractal colors
2. **Blue Ocean** - Deep blue gradients
3. **Fire** - Warm red/orange/yellow transitions
4. **Forest** - Green nature-inspired tones
5. **Sunset** - Purple/pink/orange blends
6. **Ice** - Cool blue/white/cyan palette
7. **Neon** - Bright, vibrant colors
8. **Grayscale** - Monochrome elegance
9. **Rainbow** - Full spectrum colors
10. **Copper** - Metallic bronze/gold tones
11. **Vintage** - Retro color combinations
12. **Plasma** - Electric purple/blue energy
13. **Autumn** - Warm fall colors
14. **Spring** - Fresh green/yellow palette
15. **Midnight** - Dark blue/black depths

## 📊 Performance

### Optimization Features
- **Multi-threading** - Utilizes all CPU cores for faster rendering
- **Adaptive Algorithms** - Different optimization strategies per fractal type
- **Memory Efficiency** - Minimal memory footprint for large images
- **Real-time Rendering** - Smooth interaction even during navigation

### Benchmarking
Run the built-in benchmark (press 'B') to test performance on your system. Results include:
- Frames per second (FPS)
- Render time per frame
- Threading efficiency comparison
- Memory usage statistics

## 🔧 Configuration File Format

When you save settings (press 'O'), a `fractal_config.txt` file is created:

```
fractal_type=1
min_real=-2.000000
max_real=1.000000
min_imag=-1.500000
max_imag=1.500000
max_iterations=100
color_shift=0
julia_real=0.285000
julia_imag=0.010000
use_threading=1
use_antialiasing=0
```

## 🎯 Project Structure

```
fract-ol/
├── includes/
│   └── fractol.h              # Header file with all declarations
├── srcs/
│   ├── main.c                 # Main program entry point
│   ├── mandelbrot.c           # Mandelbrot fractal implementation
│   ├── julia.c                # Julia set implementation
│   ├── barnsley.c             # Barnsley fern implementation
│   ├── tricorn.c              # Tricorn fractal implementation
│   ├── additional_fractals.c  # New fractal types (Burning Ship, Newton, etc.)
│   ├── color.c                # Enhanced color system
│   ├── antialiasing.c         # Anti-aliasing implementation
│   ├── hook.c                 # Event handling
│   ├── control_keyboard.c     # Keyboard input processing
│   ├── control_mouse.c        # Mouse input processing
│   ├── print_help.c           # Help system
│   ├── export.c               # BMP export and animations
│   ├── config.c               # Configuration save/load
│   ├── profiling.c            # Performance benchmarking
│   ├── init.c                 # Initialization functions
│   └── utils.c                # Utility functions
├── libft/                     # Custom C library
├── Makefile                   # Build configuration
└── README.md                  # This file
```

## 🧮 Mathematical Background

### Mandelbrot Set
The Mandelbrot set is defined by the iteration:
```
z(n+1) = z(n)² + c
```
Where z₀ = 0 and c is a complex number representing the pixel coordinate.

### Julia Set
Similar to Mandelbrot, but with a fixed parameter c and variable starting point z₀:
```
z(n+1) = z(n)² + c
```
Where c is constant and z₀ varies by pixel position.

### Newton Fractal
Based on Newton's method for finding roots:
```
z(n+1) = z(n) - f(z(n))/f'(z(n))
```
Using f(z) = z³ - 1 as the default polynomial.

## 🎓 Educational Value

This project demonstrates:
- **Complex Number Mathematics** - Practical application of complex arithmetic
- **Algorithm Optimization** - Performance tuning and parallel processing
- **Computer Graphics** - Real-time rendering and color theory
- **Software Architecture** - Modular design and clean code practices
- **Mathematical Visualization** - Making abstract concepts tangible

## 🐛 Troubleshooting

### Common Issues

**Black Screen on Launch**
- Ensure MinilibX is properly installed
- Check that your system supports X11

**Slow Performance**
- Enable multi-threading (press 'T')
- Reduce iteration count (press '-')
- Disable anti-aliasing if needed (press 'P')

**Export Not Working**
- Ensure write permissions in the current directory
- Check available disk space

**Memory Issues**
- Close other applications
- Use lower iteration counts for high zoom levels

## 🏆 42 Project Requirements

This project fulfills all requirements for the 42 School fract-ol project:
- ✅ Mandelbrot and Julia sets implemented
- ✅ Real-time parameter modification
- ✅ Zoom functionality with mouse wheel
- ✅ ESC and window close handling
- ✅ Additional fractal types (bonus)
- ✅ Color palette management (bonus)
- ✅ Multi-threading support (bonus)

### Bonus Features Implemented
- Multiple fractal types (8 total)
- Enhanced color palettes (15 options)
- Anti-aliasing for smooth rendering
- Export system with BMP format
- Animation generation
- Configuration persistence
- Performance benchmarking

## 📄 License

This project is part of the 42 School curriculum. Feel free to study the code for educational purposes.

## 🙏 Acknowledgments

- **42 School** - For the challenging and rewarding curriculum
- **MinilibX** - For the graphics library
- **Mathematical Community** - For the fascinating world of fractals
- **Open Source Contributors** - For inspiration and best practices

---

**Explore the infinite beauty of mathematics through fractals! 🌀**

*For questions or contributions, please feel free to reach out or submit issues/pull requests.*
