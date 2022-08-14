//#include <GLFW/glfw3.h>
#include <iostream>
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

}

int main(int argc, char* argv[]){

	
	AVFormatContext* av_format_ctx = avformat_alloc_context(); 



	if (avformat_open_input(&av_format_ctx, "/home/server/Downloads/sample-5s.mp4" ,NULL ,NULL) != 0)
		std::cout << "Can`t open video file!" << std::endl;

			
	for(int i = 0; i < av_format_ctx->nb_streams; i++){
	 	AVCodecParameters *pLocalCodecParameters = av_format_ctx->streams[i]->codecpar;
		AVCodec *pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);
		std::cout << pLocalCodec->long_name << std::endl;
		
	}
	

	
	return 0;
}

