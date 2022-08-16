#include <iostream>
#include "check_input_parameters.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

}

#ifdef av_err2str
#undef av_err2str
#include <string>
av_always_inline std::string av_err2string(int errnum) {
    char str[AV_ERROR_MAX_STRING_SIZE];
    return av_make_error_string(str, AV_ERROR_MAX_STRING_SIZE, errnum);
}
#define av_err2str(err) av_err2string(err).c_str()
#endif  // av_err2str

int a = 2;
int main(int argc, char* argv[]){
	
		int index_video_stream = -1;

	if(!check_input_parametrs(argc))
		return -1;
	

	//Open file using libavformat
	AVFormatContext* av_format_ctx = avformat_alloc_context(); 



	if (avformat_open_input(&av_format_ctx, argv[1] ,NULL ,NULL) != 0){
		std::cout << "Can`t open video file!" << std::endl;
		return -1;
	}
	//find video stream
			
	for(int i = 0; i < av_format_ctx->nb_streams; i++){
	 	
		
		AVCodecParameters *av_codec_params = av_format_ctx->streams[i]->codecpar;    //
		AVCodec *av_codec = avcodec_find_decoder(av_codec_params->codec_id);   //find codec for id 
		
	
		
		
			if(av_codec->type == AVMEDIA_TYPE_VIDEO){ 
				index_video_stream = i;
				//break;
			}
		
			if(index_video_stream == -1 && (i == (av_format_ctx->nb_streams - 1))){
				std::cout << "Not found video stream\n";
				return -1;
			}
		
			//set ip context for decoder 

	
			

	AVCodecContext *av_codec_ctx = avcodec_alloc_context3(av_codec);
	
	if(avcodec_parameters_to_context(av_codec_ctx, av_codec_params)) {
			std::cout << "Could not open codec\n";
			return false;
	}
	
			
	if(avcodec_open2(av_codec_ctx, av_codec, NULL) < 0 ){
		std::cout << "could not open codec!\n"; 
		return false;
	}

		AVFrame *av_frame = av_frame_alloc();
		AVPacket *av_packet = av_packet_alloc();
			int response ;
		while (av_read_frame(av_format_ctx, av_packet) >= 0){
			
			if(av_packet->stream_index != index_video_stream){
				continue;
			}
				
			response = avcodec_send_packet(av_codec_ctx, av_packet);
			if(response < 0){
				    printf("Failed to decode packet: %s\n", av_err2str(response));
				
				return false;
			}
			response =  avcodec_receive_frame(av_codec_ctx, av_frame);
			std::cout << response << " check\n";
			if(response == AVERROR(EAGAIN) || response == AVERROR_EOF){
				continue;
			} else if(response < 0 ){
				std::cout << "failed decode packet" << std::endl;
			}

			av_packet_unref(av_packet);
			
			break;
		}

			unsigned char *data = new unsigned char[ av_frame->width * av_frame->height *3];
			for(int i = 0; i < av_frame->width; i++){
				for(int j = 0; j < av_frame->height; j++){
					data[j * av_frame->width *3 + i * 3 ] = av_frame->data[0][j * av_frame->linesize[0] + i];
					data[j * av_frame->width *3 + i * 3 + 1 ] = av_frame->data[0][j * av_frame->linesize[0] + i];
					data[j * av_frame->width *3 + i * 3 + 2 ] = av_frame->data[0][j * av_frame->linesize[0] + i];
				}
			}
			


			
		
	}


	

	
	return 0;
}

