# Fract'ol - Fractal Explorer

![Fract'ol Banner](https://img.shields.io/badge/42-Paris-blue?style=for-the-badge&logo=42) ![C](https://img.shields.io/badge/C-Language-blue?style=for-the-badge&logo=c) ![MinilibX](https://img.shields.io/badge/MinilibX-Graphics-green?style=for-the-badge)

> **Note:** This project is an extension of the original 42 School fract-ol subject. It incorporates features beyond the initial scope, aiming for a richer user experience and more comprehensive fractal exploration.

## 🚀 What is this?

This is a high-performance, feature-rich fractal explorer written in C, using MinilibX for graphics. It started as a 42 project and has been expanded to include:

- Multiple fractal types: Mandelbrot, Julia, Burning Ship, Newton, Tricorn, Barnsley Fern, Mandelbar (Buffalo), and **Multibrot** (with adjustable power).
- **13 beautiful, optimized color palettes** with real-time switching and smooth interpolation.
- Multi-threaded rendering for significant speed improvements.
- Anti-aliasing (adaptive supersampling).
- Image export to **BMP and PPM** formats.
- Animation export (zoom and color cycling).
- Configuration system (save/load views and settings).
- **Advanced performance profiling and benchmarking tools.**
- Enhanced navigation: **Mouse panning (left-click drag)**, scroll-wheel zoom.
- Interactive Julia set parameter modification.

## 🧑‍💻 Installation

### Prerequisites
- GCC compiler
- X11 development libraries
- MinilibX library (included as a submodule)
- Make

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install gcc make libx11-dev libxext-dev
```

### Building
```bash
git clone --recursive https://github.com/tham-le/fractol.git
cd fractol
make
```

## 🎮 Usage

```bash
# Launch with Mandelbrot fractal
./fractol mandelbrot

# Launch with Julia fractal (default C values)
./fractol julia

# Launch Julia with custom C parameters
./fractol julia [real_value] [imaginary_value]

# Launch Multibrot (default power 2)
./fractol multibrot

# View help and controls
./fractol help

# Quick animation demo:
# 1. Run: ./fractol mandelbrot
# 2. Press 'U' for enhanced infinite zoom
# 3. Press 'H' for fractal showcase tour
# 4. Press 'G' for color palette showcase
```

## 🌈 Color Palettes & Visuals
- **13 carefully curated palettes**: Default gradients, Rainbow, Fire, Ice, Psychedelic, Ocean, Forest, Smooth HSV, Greyscale, Vintage, Angle-based  trap coloring.
- Smooth color interpolation and enhanced gradients.
- Real-time palette switching (press 'C').
- Color cycling animation (press 'X' to generate frames).

## 🏎️ Performance & Features
- Multi-threaded rendering (toggle with 'T').
- Anti-aliasing (toggle with 'A').
- **Advanced benchmarking suite (press 'B').**
- **Print detailed profiler statistics (press 'P').**
- Export current view:
    - **Quick export (BMP with timestamp) (press 'E').**
    - (PPM export is available programmatically via `export_image`, can be hooked to a key if desired).
- Create zoom/color animations (press 'Z', 'X' to generate frames).
- Save/load view configuration (press 'O', 'L').
- **Mouse panning: Left-click and drag.**
- Scroll wheel to zoom towards mouse pointer.
- **Multibrot power adjustment (PageUp/PageDown when Multibrot is active).**
- **Julia parameter adjustment: Q/D for real part, W/S for imaginary part.**

## 🎬 Spectacular Animation Features
- **Enhanced Infinite Zoom (U)**: Smooth, targeted zoom with automatic color cycling and iteration scaling
- **Spiral Zoom Animation (Y)**: Hypnotic zoom combined with rotational camera movement
- **Julia Set Morphing (J)**: Seamless transitions between famous Julia set parameters (Julia sets only)
- **Fractal Showcase Tour (H)**: Automated tour through all fractal types with optimal settings
- **Color Palette Showcase (G)**: Dynamic demonstration of all 13 color palettes with subtle motion effects
- **Basic Infinite Zoom (I)**: Simple infinite zoom for quick demonstrations

## 🧩 Fractals Supported
- Mandelbrot
- Julia (interactive C params: left-click (non-drag); cycle presets: right-click)
- Burning Ship
- Newton (for z^3 - 1)
- Tricorn
- Mandelbar (Buffalo variant)
- Barnsley Fern
- **Multibrot (z -> z^N + c, power N adjustable via PageUp/PageDown)**

## 🗺️ Project Structure

```
fractol/
├── includes/         # Header files (*.h)
├── srcs/             # Core source code (*.c)
├── libft/            # Custom C library (libft.a)
├── minilibx-linux/   # MinilibX graphics library
├── improvements/     # Folder with prior experimental/additional code
├── Makefile, README.md, etc.
```

## 🏆 Beyond the 42 Subject
This project has significantly expanded upon the original 42 requirements, featuring:
- Multi-threading.
- A wider variety of fractals and color schemes.
- Advanced export options (BMP, PPM, animations).
- A robust configuration and preset system.
- Detailed performance analysis tools.
- More intuitive user interaction (mouse panning).

## 📄 License
This project is part of the 42 School curriculum. Enhancements and additional code are provided for educational and experimental purposes.

---

**Explore, experiment, and enjoy the mathematical beauty of fractals! 🌀**