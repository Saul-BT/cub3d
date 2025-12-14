#!/bin/bash
# Quick test script to verify VNC setup

echo "=== VNC Setup Test ==="
echo ""

# Check if Xvfb is running
echo "1. Checking Xvfb:"
if ps aux | grep -v grep | grep "Xvfb :99" > /dev/null; then
    echo "   ✓ Xvfb is running on display :99"
else
    echo "   ✗ Xvfb is NOT running"
    echo "   Start it with: .devcontainer/start-xvfb.sh"
    exit 1
fi
echo ""

# Check DISPLAY
echo "2. Checking DISPLAY:"
if [ "$DISPLAY" = ":99" ]; then
    echo "   ✓ DISPLAY is set to :99"
else
    echo "   ⚠ DISPLAY is set to: $DISPLAY (should be :99)"
    export DISPLAY=:99
    echo "   → Fixed: DISPLAY now set to :99"
fi
echo ""

# Check if x11vnc is installed
echo "3. Checking x11vnc:"
if command -v x11vnc &> /dev/null; then
    echo "   ✓ x11vnc is installed"
else
    echo "   ✗ x11vnc is NOT installed"
    exit 1
fi
echo ""

# Test X11 connection
echo "4. Testing X11 connection:"
if DISPLAY=:99 xset q &> /dev/null; then
    echo "   ✓ X11 connection to :99 works"
else
    echo "   ✗ X11 connection to :99 failed"
    exit 1
fi
echo ""

# Check if port 5900 is in use
echo "5. Checking port 5900:"
if netstat -tlnp 2>/dev/null | grep -q ":5900" || ss -tlnp 2>/dev/null | grep -q ":5900"; then
    echo "   ⚠ Port 5900 is already in use (VNC may already be running)"
else
    echo "   ✓ Port 5900 is available"
fi
echo ""

echo "=== Setup looks good! ==="
echo ""
echo "To start VNC server, run:"
echo "  .devcontainer/view-graphics.sh"
echo ""
echo "Then connect from your Mac:"
echo "  - Screen Sharing: Cmd+K, then vnc://localhost:5900"
echo "  - Or VNC Viewer: localhost:5900"

