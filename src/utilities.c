#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <utilities.h>

bayer_array split_raw12(uchar *raw12_src, size_t width, size_t height,
                cfa_pattern pattern) {
    uchar *red = (uchar *)malloc(height * width);
    uchar *blue = (uchar *)malloc(height * width);
    uchar *green1 = (uchar *)malloc(height * width);
    uchar *green2 = (uchar *)malloc(height * width);

    int buffer_width = 3 * (width / 2);
    uchar(*raw12)[buffer_width] = (uchar(*)[buffer_width])raw12_src;

    int ridx = 0, bidx = 0;
    for (int k = 0; k < height; k++) {
        if (!(k % 2)) {
            for (int i = 0; i < buffer_width; i += 3) {
                red[ridx] = (raw12[k][i] << 4) | (raw12[k][i + 1] >> 4);
                green1[ridx] = ((raw12[k][i + 1] & 0x0F) << 8) | raw12[k][i + 2];
                ridx++;
            }
        } else {
            for (int i = 0; i < buffer_width; i += 3) {
                green2[bidx] = (raw12[k][i] << 4) | (raw12[k][i + 1] >> 4);
                blue[bidx] = ((raw12[k][i + 1] & 0x0F) << 8) | raw12[k][i + 2];
                bidx++;
            }
        }
    }

    bayer_array res = {red, green1, green2, blue};
    return res;
}

uchar *load_raw12(const char *path) {
    int fp = open(path, O_RDONLY);
    // 4096 * 12bits / 8 ~ bytes in a row
    const int row_size = (4096 * 12) / 8;
    const int col_size = 3072;
    const int buffer_size = col_size * row_size;
    uchar *buffer = malloc(buffer_size);
    uchar *image_buffer = buffer;

    ssize_t read_bytes = 0;
    // Only image data, we forget about the extra appended register data
    size_t len = col_size * row_size;
    while (len != 0 && (read_bytes = read(fp, buffer, buffer_size)) != 0) {
        if (read_bytes == -1) {
            if (errno == EINTR || errno == EAGAIN)
                continue;
            else {
                // More serious error
                perror ("Error while loading image");
                break;
            }
        }

        len    -= read_bytes;
        buffer += read_bytes;
    }

    return image_buffer;
}
