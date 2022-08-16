cmake_minimum_required(VERSION 3.13)
project(FF_MS)


add_subdirectory(lib/FFmpeg)
add_subdirectory(lib/glfw)

set(SOURCE src/main.cpp
src/save_gray_frame.cpp
src/check_input_parameters.cpp


)



set(HEADER

    src/check_input_parameters.h
    src/save_gray_frame.h
)

add_executable(ff_ms ${SOURCE})
target_link_libraries(ff_ms FFmpeg glfw)

	


