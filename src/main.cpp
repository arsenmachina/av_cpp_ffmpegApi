#include <iostream>
#include "check_input_parameters.h"
#include "info_video_stream.h"
#include <sys/stat.h>
#include <sys/types.h>


extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "save_gray_frame.h"
}




int main(int argc, char* argv[]){
	AVCodec *pCodec = NULL;
	AVCodecParameters *pCodecParameters =  NULL;
	int video_stream_index = -1, response = 0;
	const char* out_filename = "out/arsen_machina.m3u8"; 
	const char* dir_name = "out"; 
	int *streams_list;
	int stream_index = 0;
	AVPacket packet;
	

//	

	if (!check_input_parametrs(argc))
		return false;
	
	
	AVFormatContext *input_format_context = NULL;    //Create Format context
	AVFormatContext *output_format_context = NULL;

			if ((avformat_open_input(&input_format_context, argv[argc-1], NULL, NULL)) < 0) {
					std::cout << "Could not open! " << argv[argc-1] << std::endl;
					return -1;
				}
		if ((avformat_find_stream_info(input_format_context, NULL)) < 0) {
				std::cout << "Not found any streams! " << std::endl;
				return -1;
				}

		
		if (avformat_alloc_output_context2(&output_format_context, NULL, NULL, out_filename) < 0) {
			std::cout << "Could not create out_format_context!";
			return -1;
				}

		int number_of_streams =  input_format_context->nb_streams;
		streams_list = (int*)av_mallocz_array(number_of_streams, sizeof(*streams_list));  //Приведение с++ int* разобрать
			
//

			mkdir(dir_name, 0777);
			for (int i = 0; i < input_format_context->nb_streams; i++) {
			AVStream *out_stream;
			AVStream *in_stream = input_format_context->streams[i];
			AVCodecParameters *in_codecpar = in_stream->codecpar;
			if (in_codecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
				in_codecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
				in_codecpar->codec_type != AVMEDIA_TYPE_SUBTITLE) {
				streams_list[i] = -1;
				continue;
			}
			streams_list[i] = stream_index++;
			out_stream = avformat_new_stream(output_format_context, NULL);
			if (!out_stream) {
				std::cout << "Failed allocating output stream\n";
				continue;
				
			}
			
			if (avcodec_parameters_copy(out_stream->codecpar, in_codecpar) < 0) {
				std::cout <<  "Failed to copy codec parameters\n";
				continue;
			}
			}

			if (!(output_format_context->oformat->flags & AVFMT_NOFILE)) {
			
			if (avio_open(&output_format_context->pb, out_filename, AVIO_FLAG_WRITE) < 0) {
				std::cout <<  "Could not open output file " <<  out_filename ;
				return -1;
			}
			}

			
			if (avformat_write_header(output_format_context, NULL) < 0) {
			std::cout <<  "Error occurred when opening output file\n";
			
			}
	
			while (1) {
			AVStream *in_stream, *out_stream;
			
			if (av_read_frame(input_format_context, &packet) < 0)
				break;
			in_stream  = input_format_context->streams[packet.stream_index];
			if (packet.stream_index >= number_of_streams || streams_list[packet.stream_index] < 0) {
				av_packet_unref(&packet);
				continue;
			}
			packet.stream_index = streams_list[packet.stream_index];
			out_stream = output_format_context->streams[packet.stream_index];
			/* copy packet */
			packet.pts = av_rescale_q_rnd(packet.pts, in_stream->time_base, out_stream->time_base, static_cast<AVRounding>(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
			packet.dts = av_rescale_q_rnd(packet.dts, in_stream->time_base, out_stream->time_base, static_cast<AVRounding>(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
			packet.duration = av_rescale_q(packet.duration, in_stream->time_base, out_stream->time_base);
			
			packet.pos = -1;

			
			
			if (av_interleaved_write_frame(output_format_context, &packet) < 0) {
				std::cout <<  "Finish muxing packet\n";
				break;
			}
			
			av_packet_unref(&packet);
			}
			
		av_write_trailer(output_format_context);


	

	
	return 0;
}

