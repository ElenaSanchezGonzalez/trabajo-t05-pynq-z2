#include "color_invert_hls.h"
#include <iostream>

void color_invert(axis_stream_t& in_stream, axis_stream_t& out_stream);

int main() {
    axis_stream_t in_s, out_s;

    axis_pixel_t px;
    px.data = 0x112233;  // R=0x11, G=0x22, B=0x33
    px.keep = -1;
    px.strb = -1;
    px.user = 0;
    px.last = 1;
    px.id   = 0;
    px.dest = 0;

    in_s.write(px);

    color_invert(in_s, out_s);

    if (out_s.empty()) {
        std::cout << "ERROR: output stream empty\n";
        return 1;
    }

    axis_pixel_t out = out_s.read();
    ap_uint<24> expected = 0xEEDDCC; // (255-11, 255-22, 255-33)

    std::cout << "Out: 0x" << std::hex << (unsigned)out.data
              << " Expected: 0x" << (unsigned)expected << "\n";

    return (out.data == expected) ? 0 : 1;
}
