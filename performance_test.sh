#!/bin/bash

# Performance test script for fractal threading implementation
# This script tests the rendering speed differences between threaded and non-threaded versions

echo "=== Fractal Threading Performance Test ==="
echo "This test compares rendering performance with and without threading."
echo ""

# Check if the executable exists
if [ ! -f "./fractol" ]; then
    echo "Error: fractol executable not found. Please run 'make' first."
    exit 1
fi

echo "System Information:"
echo "CPU cores: $(nproc)"
echo "Threads available: $(nproc)"
echo ""

echo "Instructions for manual testing:"
echo "1. Run: ./fractol mandelbrot"
echo "2. Wait for the fractal to render (threading enabled by default)"
echo "3. Press 't' to toggle threading OFF"
echo "4. Press 'r' to reset and re-render (now without threading)"
echo "5. Press 't' to toggle threading ON again"
echo "6. Press 'r' to reset and re-render (now with threading)"
echo "7. Compare the rendering times visually"
echo ""

echo "Key controls:"
echo "- 't' or 'T': Toggle threading on/off"
echo "- 'r': Reset fractal and re-render"
echo "- 'Esc': Exit program"
echo "- Arrow keys: Move around"
echo "- '+/-': Increase/decrease iterations"
echo "- 'c': Change color scheme"
echo "- '1-4': Switch between fractal types"
echo ""

echo "Threading status messages will be printed to the terminal."
echo "You should see noticeable performance differences on multi-core systems."
echo ""

echo "Ready to start manual testing!"
