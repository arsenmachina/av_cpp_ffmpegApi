#include <iostream>
#include "check_input_parameters.h"
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

}

int main(int argc, char* argv[]){

	if(!check_input_parametrs(argc))
		return -1;
	

	
	AVFormatContext* av_format_ctx = avformat_alloc_context(); 



	if (avformat_open_input(&av_format_ctx, argv[1] ,NULL ,NULL) != 0){
		std::cout << "Can`t open video file!" << std::endl;
		return -1;
	}

			
	for(int i = 0; i < av_format_ctx->nb_streams; i++){
	 	AVCodecParameters *pLocalCodecParameters = av_format_ctx->streams[i]->codecpar;
		AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
		std::cout << pLocalCodec->long_name << std::endl;
		
	}
	

	
	return 0;
}

