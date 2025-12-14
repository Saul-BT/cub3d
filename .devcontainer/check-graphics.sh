#!/bin/bash
# Graphics configuration checker for cub3d dev container

echo "=== Graphics Configuration Check ==="
echo ""

echo "1. Checking DISPLAY environment:"
echo "   DISPLAY=$DISPLAY"
echo ""

echo "2. Checking OpenGL/Mesa environment variables:"
echo "   LIBGL_ALWAYS_SOFTWARE=$LIBGL_ALWAYS_SOFTWARE"
echo "   GALLIUM_DRIVER=$GALLIUM_DRIVER"
echo "   MESA_GL_VERSION_OVERRIDE=$MESA_GL_VERSION_OVERRIDE"
echo ""

echo "3. Checking Mesa software rendering:"
if command -v glxinfo &> /dev/null; then
    echo "   glxinfo found, checking OpenGL renderer:"
    DISPLAY=$DISPLAY glxinfo | grep -E "(OpenGL vendor|OpenGL renderer|OpenGL version)" || echo "   glxinfo failed - X11 connection issue"
else
    echo "   glxinfo not found (install mesa-utils if needed)"
fi
echo ""

echo "4. Checking X11 connection:"
if [ -n "$DISPLAY" ]; then
    if xset q &> /dev/null; then
        echo "   ✓ X11 connection working (Display: $DISPLAY)"
        if [ "$DISPLAY" = ":99" ]; then
            echo "   Using Xvfb virtual framebuffer (headless mode)"
            echo "   To view graphics, use VNC: .devcontainer/view-graphics.sh"
        fi
    else
        echo "   ✗ X11 connection failed"
        if [ "$DISPLAY" = ":99" ]; then
            echo "   Xvfb may not be running. Try: .devcontainer/start-xvfb.sh"
        else
            echo "   On macOS: Make sure XQuartz is installed and running"
            echo "   Run: xhost +localhost (in XQuartz terminal)"
        fi
    fi
else
    echo "   ✗ DISPLAY not set"
fi
echo ""

echo "5. Checking required libraries:"
ldconfig -p | grep -E "(libGL|libglfw|libX11)" | head -5 || echo "   Some libraries may be missing"
echo ""

echo "=== Check Complete ==="
