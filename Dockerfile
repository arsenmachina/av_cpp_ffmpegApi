FROM ubuntu:latest



WORKDIR /home/dev

RUN apt update && apt install -y libavfilter-dev libavcodec-dev libavformat-dev libavdevice-dev \
    libavutil-dev libswresample-dev ffmpeg \
    libswscale-dev cmake pkg-config make git \
    gcc g++

