# Fract'ol - Fractal Explorer

![Fract'ol Banner](https://img.shields.io/badge/42-Paris-blue?style=for-the-badge&logo=42) ![C](https://img.shields.io/badge/C-Language-blue?style=for-the-badge&logo=c) ![MinilibX](https://img.shields.io/badge/MinilibX-Graphics-green?style=for-the-badge)

> **Note:** This project is a extension of the original 42 School fract-ol subject. It is not in the 42 norm style. The code is experimental, pragmatic, and prioritizes features, performance, and fun. Please enjoy the peer-learning and don't copy!

## 🚀 What is this?

This is a high-performance, feature-rich fractal explorer written in C, using MinilibX for graphics. It started as a 42 project, but now includes:

- 7+ fractal types (Mandelbrot, Julia, Burning Ship, Newton, Mandelbar, Tricorn, Barnsley...)
- 15+ beautiful color palettes (rainbow, fire, ice, HSV gradients, psychedelic, and more)
- Real-time color cycling and palette switching
- Multi-threaded rendering for speed
- Anti-aliasing (MSAA, adaptive supersampling)
- Export to BMP/PPM, batch and animation export
- Config system (save/load your favorite setups)
- Performance benchmarking and profiling
- Advanced navigation (smooth zoom, mouse gestures, minimap, presets)
- On-screen overlays, GUI enhancements, and more

## 🧑‍💻 Installation

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
git clone --recursive https://github.com/tham-le/fractol.git
cd fractol
make
```

## 🎮 Usage

```bash
# Launch with Mandelbrot fractal
./fractol mandelbrot

# Launch with Julia fractal
./fractol julia

# Launch Julia with custom parameters
./fractol julia [real] [imaginary]

# View help and controls
./fractol help
```

## 🌈 Color Palettes & Visuals
- 15+ palettes: rainbow, fire, ice, beach, pastel, HSV gradients, psychedelic, and more
- Smooth color interpolation (HSV, sine waves)
- Real-time palette switching (press 'C')
- Color cycling animation (press 'X')
- Custom palette scripting (see improvements/)

## 🏎️ Performance & Features
- Multi-threaded rendering (toggle with 'T')
- Anti-aliasing (toggle with 'P')
- Performance benchmarking (press 'B')
- Export current view as BMP (press 'E')
- Create zoom/color animations (press 'Z', 'X')
- Save/load config (press 'O', 'L')
- Advanced navigation: smooth zoom, mouse pan, minimap, presets

## 🧩 Fractals Supported
- Mandelbrot
- Julia (with real-time parameter control)
- Burning Ship
- Newton
- Mandelbar (conjugate)
- Tricorn
- Barnsley Fern
- ...and more in improvements/ (e.g., Multibrot)

## 🗺️ Project Structure

```
fractol/
├── includes/         # Headers
├── srcs/             # Core source code
├── improvements/     # Experimental features, enhancements, new fractals
├── libft/            # Custom C library
├── minilibx-linux/   # MinilibX graphics library
├── Makefile, scripts, README.md, ...
```

## 🏆 Beyond the 42 Subject
This project goes **way beyond** the original 42 requirements:
- Multi-threading
- More fractals, more palettes, more export options
- Real configuration system, animation, benchmarking
- GUI/UX improvements, scripting hooks, and more


## 📄 License
This project is part of the 42 School curriculum, but all enhancements are open for educational and experimental use.

---

**Explore,   and enjoy the mathematical beauty of fractals! 🌀**