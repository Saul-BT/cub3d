FROM ubuntu:22.04

# Install necessary packages & remove apt cache
RUN apt-get update && apt-get install -y \
  build-essential \
  libx11-dev \
  libxext-dev \
  zlib1g-dev \
  libbsd-dev \
  x11-apps \
  xorg \
  git \
  pkg-config \
  && rm -rf /var/lib/apt/lists/*

# Set DISPLAY environment variable for X11 forwarding
ENV DISPLAY=host.docker.internal:0

WORKDIR /cub3d
COPY . ./
CMD ["xeyes"]
