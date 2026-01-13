#include "color_invert_hls.h"

void color_invert(axis_stream_t& in_stream, axis_stream_t& out_stream) {
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE axis port=out_stream
#pragma HLS INTERFACE ap_ctrl_none port=return

    while (!in_stream.empty()) {
#pragma HLS PIPELINE II=1

        axis_pixel_t in_px = in_stream.read();

        // TDATA de 32 bits
        ap_uint<32> data_in = in_px.data;

        // RGB en los 24 bits menos significativos
        ap_uint<8> r = data_in.range(23,16);
        ap_uint<8> g = data_in.range(15,8);
        ap_uint<8> b = data_in.range(7,0);

        // Invertimos colores
        ap_uint<8> r_inv = 255 - r;
        ap_uint<8> g_inv = 255 - g;
        ap_uint<8> b_inv = 255 - b;

        axis_pixel_t out_px = in_px;

        // Reconstruimos TDATA de 32 bits
        out_px.data = 0;
        out_px.data.range(23,16) = r_inv;
        out_px.data.range(15,8)  = g_inv;
        out_px.data.range(7,0)   = b_inv;

        out_stream.write(out_px);
    }
}

