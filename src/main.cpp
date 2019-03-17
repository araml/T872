#include <nearest.h>

int main() {
    uchar *image_buffer = load_raw12("../portrait-gainx2-offset2047-20ms-02.raw12");
    bayer_array channels = split_raw12(image_buffer, 4096, 3072, RGGB);

}
