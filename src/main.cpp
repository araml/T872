#include <nearest.h>
#include <image_utils.h>
#include <unistd.h>

int main() {
    chdir("..");
    uchar *image_buffer = load_raw12("data/portrait-gainx2-offset2047-20ms-02.raw12");
    bayer_array channels = split_raw12(image_buffer, 4096, 3072, RGGB);
    write_ppm("output_image_g.pgm", channels.r, 2048, 1536, GRAY);
    write_ppm("output_image_r1.pgm", channels.g1, 2048, 1536, GRAY);
    write_ppm("output_image_r2.pgm", channels.g2, 2048, 1536, GRAY);
    write_ppm("output_image_b.pgm", channels.b, 2048, 1536, GRAY);
    return 0;
}
