cmake_minimum_required(VERSION 3.13)
project(FF_MS)


add_subdirectory(lib/FFmpeg)

set(SOURCE
 
src/main.cpp
src/check_input_parameters.cpp
src/save_gray_frame.c
src/info_video_stream.cpp

)

add_executable(ff_ms ${SOURCE})
target_link_libraries(ff_ms FFmpeg )



