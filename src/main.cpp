#include <iostream>
#include "check_input_parameters.h"
#include "info_video_stream.h"



extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "save_gray_frame.h"
}




int main(int argc, char* argv[]){
	AVCodec *pCodec = NULL;
	AVCodecParameters *pCodecParameters =  NULL;
	int video_stream_index = -1, response = 0;
	const char* out_save_file = "out";
	

	if (!check_input_parametrs(argc))
		return false;
	
	AVFormatContext *pFormatContext = avformat_alloc_context(); //Allocate memory for context  Abstract format file 
	
	

	avformat_open_input(&pFormatContext, argv[argc-1], NULL, NULL); //Open file and fill context pFormatContext
	
	

	avformat_find_stream_info(pFormatContext,  NULL); // Read streams from disk

			//Find VIDEO_STREAM
		
	for(int i = 0; i < pFormatContext->nb_streams; i++){

		pCodecParameters = pFormatContext->streams[i]->codecpar; // For every stream get information
		
		pCodec = avcodec_find_decoder(pCodecParameters->codec_id);		//std::cout << pLocalCodecParameters->bit_rate << std::endl;
		
			if(pCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO){
				 if (video_stream_index == -1)
					video_stream_index = i;
					break;
			}
						
	}
		
		if (video_stream_index == -1) {
    		std::cout << "File " << argv[1] << " does not contain a video stream!" << std::endl;
    		return -1;
	    } 
		AVRational  frame_r = pFormatContext->streams[video_stream_index]->r_frame_rate;     
			double frame_rate = get_frame_rate(frame_r.num, pFormatContext->duration);
			std::cout << frame_rate << std::endl;
			
	
	AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec); //Alloc memory for context proccess decode/code
	avcodec_parameters_to_context(pCodecContext, pCodecParameters); //Fill context pCodecContext with parametrs pCodecParametrs
	
	avcodec_open2(pCodecContext, pCodec, NULL); //Open codec 
	
	
	////Read packet from stream and write frame 

	AVPacket *pPacket = av_packet_alloc();
	AVFrame *pFrame = av_frame_alloc();  		//allocate memory from components


	
	while(av_read_frame(pFormatContext, pPacket) >= 0) {

		
		
			if(pPacket->stream_index == video_stream_index){
					
					response = avcodec_send_packet(pCodecContext, pPacket);   //разобрать
						if(response < 0){
							std::cout << "Can not send encoded packet" << response << std::endl; continue; 
						}
						else{
							response = avcodec_receive_frame(pCodecContext, pFrame);   //разобрать если закомментить ломается 
							system("clear");
							std::cout << "Decoding progress: " << int((pCodecContext->frame_number * 100) / frame_rate) << "%" << std::endl;
							
						}	
						
			}
	} 

	if(response == 0){
		system("clear");
		std::cout << "100% Finish decode!" << std::endl;
	} else {
		std::cout << "Eror decode file!" << std::endl;
		return response;
	}

	save_gray_frame(pFrame->data[0], pFrame->linesize[0], pFrame->width, pFrame->height, out_save_file);

	
	return 0;
}

