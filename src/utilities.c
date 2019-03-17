#include <stdlib.h>
#include <utilities.h>

rgb split_raw12(uchar *raw12_src, size_t width, size_t height,
                cfa_pattern pattern) {
    uchar *red = (uchar *)malloc(height * width);
    uchar *blue = (uchar *)malloc(height * width);
    uchar *green = (uchar *)malloc(height * width * 2);

    int buffer_width = 3 * (width / 2);
    uchar(*raw12)[buffer_width] = (uchar(*)[buffer_width])raw12_src;

    int ridx = 0, bidx = 0;
    for (int k = 0; k < height; k++) {
        if (!(k % 2)) {
            for (int i = 0; i < buffer_width; i += 3) {
                red[ridx] = (raw12[k][i] << 4) | (raw12[k][i + 1] >> 4);
                green[ridx + bidx] = ((raw12[k][i + 1] & 0x0F) << 8) | raw12[k][i + 2];
                ridx++;
            }
        } else {
            for (int i = 0; i < buffer_width; i += 3) {
                green[ridx + bidx] = (raw12[k][i] << 4) | (raw12[k][i + 1] >> 4);
                blue[bidx] = ((raw12[k][i + 1] & 0x0F) << 8) | raw12[k][i + 2];
                bidx++;
            }
        }
    }

    rgb res = {red, green, blue};
    return res;
}
