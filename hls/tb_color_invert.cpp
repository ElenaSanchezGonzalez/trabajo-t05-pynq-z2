#include "color_invert_hls.h"
#include <iostream>

void color_invert(axis_stream_t& in_stream, axis_stream_t& out_stream);

static axis_pixel_t make_px(ap_uint<32> data, ap_uint<1> last) {
    axis_pixel_t px;
    px.data = data;
    px.keep = -1;
    px.strb = -1;
    px.user = 0;
    px.last = last;
    px.id   = 0;
    px.dest = 0;
    return px;
}

int main() {
    axis_stream_t in_s, out_s;

    // Enviamos 2 píxeles (frame de 2 palabras)
    in_s.write(make_px(0x00112233, 0));  // last=0
    in_s.write(make_px(0x00ABCDEF, 1));  // last=1 (fin de frame)

    color_invert(in_s, out_s);

    if (out_s.empty()) {
        std::cout << "ERROR: output stream empty\n";
        return 1;
    }

    axis_pixel_t o1 = out_s.read();
    axis_pixel_t o2 = out_s.read();

    ap_uint<32> exp1 = 0x00EEDDCC; // inv de 0x00112233
    // 0x00ABCDEF -> R=AB, G=CD, B=EF => inv = 54,32,10 -> 0x00543210
    ap_uint<32> exp2 = 0x00543210;

    std::cout << "Out1: 0x" << std::hex << (unsigned)o1.data
              << " Expected: 0x" << (unsigned)exp1
              << " last=" << (unsigned)o1.last << "\n";

    std::cout << "Out2: 0x" << std::hex << (unsigned)o2.data
              << " Expected: 0x" << (unsigned)exp2
              << " last=" << (unsigned)o2.last << "\n";

    int ok = (o1.data == exp1) && (o2.data == exp2) && (o2.last == 1);
    return ok ? 0 : 1;
}
