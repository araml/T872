#include <nearest.h>
#include <image_utils.h>
#include <unistd.h>

int main() {
    chdir("..");
    uchar *image_buffer = load_raw12("data/portrait-gainx2-offset2047-20ms-02.raw12");
    bayer_array channels = split_raw12(image_buffer, 4096, 3072, RGGB);

    size_t width = 2048, height = 1536;
    auto red_s = nearest(channels.r, width, height);
    auto blue_s = nearest(channels.b, width, height);
    auto green1_s = nearest(channels.g1, width, height);
    auto green2_s = nearest(channels.g2, width, height);


    // width * 2 * height * 2 (we copy each component into 4 pixels
    // the value 3 is because each pixel has RGB components
    uchar *merged_image_src = (uchar *) malloc(width * height * 4 * 3);
    uchar(*merged_image)[width * 2 * 3] = (uchar(*)[width * 2 * 3])merged_image_src;
    uchar(*red)[width * 2] = (uchar(*)[width * 2])red_s;
    uchar(*blue)[width * 2] = (uchar(*)[width * 2])blue_s;
    uchar(*green1)[width * 2] = (uchar(*)[width * 2])green1_s;
    uchar(*green2)[width * 2] = (uchar(*)[width * 2])green2_s;



    for (size_t k = 0; k < height * 2; k++) {
        for (size_t i = 0; i < width * 2; i++) {
            merged_image[k][(3 * i) + 0] = red[k][i];
            merged_image[k][(3 * i) + 1] = blue[k][i];
            if (!(k % 2))
                merged_image[k][(3 * i) + 2] = green1[k][i];
            else
                merged_image[k][(3 * i) + 2] = green2[k][i];
        }
    }

    write_ppm("image.ppm", merged_image_src, width * 2, height * 2, RGB);

    return 0;
}
