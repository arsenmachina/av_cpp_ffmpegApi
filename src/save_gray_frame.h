#ifndef _SAVE_GRAY_FRAME_
#define _SAVE_GRAY_FRAME_

void save_gray_frame(unsigned char *buf, int wrap, int xsize, int ysize,const char *filename);

#endif










/*
#ifdef av_err2str
#undef av_err2str

av_always_inline char* av_err2str(int errnum)
{
    // static char str[AV_ERROR_MAX_STRING_SIZE];
    // thread_local may be better than static in multi-thread circumstance
    thread_local char str[AV_ERROR_MAX_STRING_SIZE]; 
    memset(str, 0, sizeof(str));
    return av_make_error_string(str, AV_ERROR_MAX_STRING_SIZE, errnum);
}
#endif
*/