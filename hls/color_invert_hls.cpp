#include "color_invert_hls.h"

void color_invert(axis_stream_t& in_stream, axis_stream_t& out_stream) {
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream
#pragma HLS INTERFACE ap_ctrl_none port=return

    bool done = false;

    while (!done) {
#pragma HLS PIPELINE II=1

        axis_pixel_t in_px = in_stream.read();   // Leer siempre (AXIS handshake)
        ap_uint<32> data_in = in_px.data;

        ap_uint<8> r = data_in.range(23,16);
        ap_uint<8> g = data_in.range(15,8);
        ap_uint<8> b = data_in.range(7,0);

        axis_pixel_t out_px = in_px;
        out_px.data = 0;
        out_px.data.range(23,16) = (ap_uint<8>)(255 - r);
        out_px.data.range(15,8)  = (ap_uint<8>)(255 - g);
        out_px.data.range(7,0)   = (ap_uint<8>)(255 - b);

        out_stream.write(out_px);

        // Termina el frame cuando TLAST = 1
        done = (in_px.last == 1);
    }
}


