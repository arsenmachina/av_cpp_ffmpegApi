#include <iostream>
#include "check_input_parameters.h"
#include "save_gray_frame.h"

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}




int main(int argc, char* argv[]){
	AVCodec *pCodec = NULL;
	AVCodecParameters *pCodecParameters =  NULL;
	int video_stream_index = -1, response = 0;

	if (!check_input_parametrs(argc))
		return false;
	
	AVFormatContext *pFormatContext = avformat_alloc_context(); //Allocate memory for context 
	
	avformat_open_input(&pFormatContext, argv[argc-1], NULL, NULL); //Open file and fill context pFormatContext
	
	avformat_find_stream_info(pFormatContext,  NULL); // Read streams from disk

	for(int i = 0; i < pFormatContext->nb_streams; i++){

		AVCodecParameters *pLocalCodecParameters = pFormatContext->streams[i]->codecpar; // For every stream get information
		
		AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);		//std::cout << pLocalCodecParameters->bit_rate << std::endl;
		
			if(pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO){
				 if (video_stream_index == -1){
					video_stream_index = i;
					pCodec = pLocalCodec;
					pCodecParameters = pLocalCodecParameters;
				 }
			}
																						
		                       
	}
		
		if (video_stream_index == -1) {
    		std::cout << "File %s does not contain a video stream!" << argv[1] << std::endl;
    		return -1;
	    } 

	
	AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec); //Alloc memory for context proccess decode/code
	avcodec_parameters_to_context(pCodecContext, pCodecParameters); //Fill context pCodecContext with parametrs pCodecParametrs
	
	avcodec_open2(pCodecContext, pCodec, NULL); //Open codec 
	
	
	////Read packeg from stream and write frame 

	AVPacket *pPacket = av_packet_alloc();
	AVFrame *pFrame = av_frame_alloc();  		//allocate memory from components

	while(av_read_frame(pFormatContext, pPacket) >= 0) {
  
			if(pPacket->stream_index == video_stream_index){
					
					response = avcodec_send_packet(pCodecContext, pPacket);
					std::cout << response << std::endl;
					response = avcodec_receive_frame(pCodecContext, pFrame);
					std::cout << response << std::endl;
					//std::cout << "Error while sending a packet to the decoder: %s" <<  av_err2str(response);
			}
	}

	save_gray_frame(pFrame->data[0], pFrame->linesize[0], pFrame->width, pFrame->height, "./out");

	
	return 0;
}

