#!/bin/bash
# Script to view graphics using VNC (optional - for viewing the virtual display)

echo "Starting VNC server on display :99..."
echo ""
echo "VNC server will be accessible at:"
echo "  - From Mac: localhost:5900"
echo "  - Or use Screen Sharing: vnc://localhost:5900"
echo ""
echo "Press Ctrl+C to stop the VNC server"
echo ""

# Kill any existing x11vnc
pkill x11vnc 2>/dev/null || true
sleep 1

# Start VNC server
# -display :99: use Xvfb display
# -nopw: no password (for local use)
# -listen 0.0.0.0: listen on all interfaces (needed for port mapping)
# -xkb: enable X keyboard extension
# -forever: keep running after client disconnects
# -shared: allow multiple clients
# -rfbport 5900: VNC port
# -noxdamage: don't use X damage extension (better compatibility)
# -wait 10: wait 10ms between screen updates
x11vnc -display :99 -nopw -listen 0.0.0.0 -xkb -forever -shared -rfbport 5900 -noxdamage -wait 10 -noxfixes
