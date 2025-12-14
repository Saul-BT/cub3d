FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Pre-configure timezone to avoid interactive prompts
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install necessary packages & remove apt cache
RUN apt-get update && apt-get install -y \
  build-essential \
  libx11-dev \
  libxext-dev \
  zlib1g-dev \
  libbsd-dev \
  x11-apps \
  xorg \
  xvfb \
  xorg-dev \
  git \
  pkg-config \
  cmake \
  libgl1-mesa-dev \
  libglfw3-dev \
  mesa-utils \
  mesa-common-dev \
  libglu1-mesa-dev \
  libxrandr-dev \
  libxinerama-dev \
  libxcursor-dev \
  libxi-dev \
  x11vnc \
  fluxbox \
  python3 \
  python3-pip \
  valgrind \
  && rm -rf /var/lib/apt/lists/*

# Force software rendering for OpenGL in containerized environments
# This is critical for headless/containerized environments
ENV LIBGL_ALWAYS_SOFTWARE=1
ENV GALLIUM_DRIVER=llvmpipe
ENV MESA_GL_VERSION_OVERRIDE=3.3
ENV MESA_GLSL_VERSION_OVERRIDE=330

# Set DISPLAY to use Xvfb virtual framebuffer
# This provides full GLX support without requiring X11 forwarding
ENV DISPLAY=:99

# Install norminette, lefthook, and c-formatter-42 via pip3
RUN python3 -m pip install --upgrade pip && \
    python3 -m pip install -U norminette lefthook c-formatter-42

WORKDIR /workspaces/cub3d
