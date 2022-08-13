cmake_minimum_required(VERSION 3.13)
project(video_app C CXX)

add_subdirectory(lib/glfw)
add_subdirectory(lib/FFmpeg)

add_executable(video-app src/main.cpp)
target_link_libraries(video-app FFmpeg glfw)
	


