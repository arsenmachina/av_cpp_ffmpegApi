#include <iostream>
#include "cmath"
#include "iomanip"

 double get_frame_rate(int frame_in_sec, int duration_video_stream_microsec){

    double duration_sec = double(duration_video_stream_microsec) / 1000000;
    std::cout << "f " << std::setprecision(11) << duration_sec << std::endl;  
    double frame_rate = frame_in_sec * duration_sec;

    return frame_rate;
}

