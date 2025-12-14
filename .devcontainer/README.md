# Graphics Setup for cub3d Dev Container

This dev container uses **Xvfb (X Virtual Framebuffer)** to provide a virtual X server with full OpenGL/GLX support. This solves compatibility issues with XQuartz on macOS.

## How It Works

The container automatically starts Xvfb on display `:99` when it starts. This provides:
- Full GLX support (unlike XQuartz which has limited GLX)
- OpenGL 3.3 Core Profile support via Mesa software rendering
- No dependency on host X11 server

## Viewing Graphics

Since Xvfb is headless (no visible window), you have two options:

### Option 1: Use VNC (Recommended)

1. **Verify setup** (in container terminal):
   ```bash
   .devcontainer/test-vnc.sh
   ```

2. **Start VNC server** (in container terminal - this will run in foreground):
   ```bash
   .devcontainer/view-graphics.sh
   ```
   Keep this terminal open while using VNC.

3. **On your Mac**, connect using one of these methods:
   - **Screen Sharing** (built-in): Press `Cmd+K`, then enter `vnc://localhost:5900`
   - **VNC Viewer** (if installed): Connect to `localhost:5900`
   - **Terminal**: `open vnc://localhost:5900`

**Important**: The VNC server must be running in a container terminal. If Screen Sharing hangs, make sure:
- The `.devcontainer/view-graphics.sh` script is running in the container
- Port 5900 is forwarded (VS Code should show a notification)
- You're connecting to `localhost:5900` (not `127.0.0.1:5900`)

### Option 2: Use X11 Forwarding (Alternative - may have GLX issues)

If you prefer to try X11 forwarding (though it may have the GLX issues we saw):

1. **Install XQuartz** (macOS):
   ```bash
   brew install --cask xquartz
   ```

2. **Restart your Mac**, then open XQuartz

3. **Configure XQuartz**:
   - Preferences > Security > Check "Allow connections from network clients"
   - In terminal: `xhost +localhost`

4. **Change DISPLAY in container**:
   ```bash
   export DISPLAY=host.docker.internal:0
   ```

**Note**: This may still have GLX errors due to XQuartz limitations.

## Troubleshooting

### Xvfb Not Starting

If Xvfb fails to start:

1. **Manually start Xvfb**:
   ```bash
   .devcontainer/start-xvfb.sh
   ```

2. **Check if Xvfb is running**:
   ```bash
   ps aux | grep Xvfb
   ```

3. **Verify DISPLAY is set**:
   ```bash
   echo $DISPLAY
   ```
   Should be `:99`

### Error: "libGL error: No matching fbConfigs or visuals found"

This should be resolved with Xvfb. If you still see this:

1. **Verify Xvfb is running**:
   ```bash
   .devcontainer/check-graphics.sh
   ```

2. **Restart Xvfb**:
   ```bash
   pkill Xvfb
   .devcontainer/start-xvfb.sh
   ```

3. **Check Mesa software rendering**:
   ```bash
   echo $LIBGL_ALWAYS_SOFTWARE
   ```
   Should be `1`

### VNC Connection Issues

If Screen Sharing hangs or can't connect:

1. **Verify Xvfb and VNC setup**:
   ```bash
   .devcontainer/test-vnc.sh
   ```

2. **Check VNC server is running**:
   ```bash
   ps aux | grep x11vnc
   ```
   If not running, start it: `.devcontainer/view-graphics.sh`

3. **Verify port 5900 is listening** (in container):
   ```bash
   netstat -tlnp | grep 5900
   # or
   ss -tlnp | grep 5900
   ```
   Should show `0.0.0.0:5900` or `:::5900`

4. **Check port forwarding**:
   - VS Code should show a notification about port 5900
   - Check VS Code's "Ports" tab to see if 5900 is forwarded
   - If not, manually forward it: Right-click port 5900 → "Forward Port"

5. **Try connecting with explicit address**:
   - Instead of `vnc://localhost:5900`, try `vnc://127.0.0.1:5900`
   - Or check VS Code's port forwarding address (might be different)

6. **Restart VNC server**:
   ```bash
   pkill x11vnc
   .devcontainer/view-graphics.sh
   ```

7. **Check firewall** (on Mac):
   - System Settings > Network > Firewall
   - Make sure it's not blocking localhost connections

## Environment Variables

The container sets these automatically:
- `DISPLAY=host.docker.internal:0` (macOS) or `:0` (Linux)
- `LIBGL_ALWAYS_SOFTWARE=1` - Forces software rendering
- `GALLIUM_DRIVER=llvmpipe` - Uses LLVM-based software renderer
- `MESA_GL_VERSION_OVERRIDE=3.3` - Sets OpenGL version to 3.3

## Testing Graphics

After setup, test with:
```bash
# In the dev container
make
./cub3d maps/your_map.cub
```

If you see the window open, graphics are working correctly!
