#pragma once
#include <ap_int.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

typedef ap_axiu<32,1,1,1> axis_pixel_t;
typedef hls::stream<axis_pixel_t> axis_stream_t;
