#!/bin/bash
# Start Xvfb virtual framebuffer for graphics support

# Kill any existing Xvfb on display :99
pkill -f "Xvfb :99" 2>/dev/null || true
sleep 1

# Start Xvfb with proper configuration for OpenGL
# -screen 0: first screen
# 1920x1080x24: resolution and color depth
# -ac: disable access control
# +extension GLX: enable GLX extension
# +render: enable render extension
# -noreset: don't reset after last client disconnects
Xvfb :99 -screen 0 1920x1080x24 -ac +extension GLX +render -noreset > /tmp/xvfb.log 2>&1 &
XVFB_PID=$!

# Wait for Xvfb to start
sleep 2

# Verify Xvfb is running
if ps -p $XVFB_PID > /dev/null 2>&1; then
    echo "✓ Xvfb started on display :99 (PID: $XVFB_PID)"
    export DISPLAY=:99
    echo "DISPLAY set to :99"
    exit 0
else
    echo "✗ Failed to start Xvfb"
    echo "Check /tmp/xvfb.log for details"
    exit 1
fi
