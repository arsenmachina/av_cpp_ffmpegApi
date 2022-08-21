#include <iostream>
#include "cmath"
#include "iomanip"

 double get_frame_rate(int frame_in_sec, int duration_video_stream_microsec){

    double duration_sec = double(duration_video_stream_microsec) / 1000000;  
    double frame_rate = frame_in_sec * duration_sec;

    return frame_rate;
}


void get_info_v_stream(char type_frame, int frame_number, int pts, int dts, int key_frame, int codec_picther_number, int display_picther_number){
    std::cout << "Type frame: " << type_frame << std::endl 
								<< "number frame: " << frame_number << std::endl 
								<< "PTS: "  << pts << std::endl << "DTS: " << dts << std::endl
								<< "Key Frame: " << key_frame << std::endl 
								<< "Codec Picther number: " << codec_picther_number << std::endl 
								<< "Display Picther number: " << display_picther_number << std::endl;
						
        
    }	


