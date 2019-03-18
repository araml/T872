#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef unsigned char uchar;

typedef struct bayer_array {
    uchar *r;
    uchar *g1;
    uchar *g2;
    uchar *b;
} bayer_array;

typedef enum cfa_pattern {
    RGGB,  // raw12 pattern
    BGGR,  // gonna implement the first two only
    RGRB,
    RGBG,
} cfa_pattern;

typedef enum image_type {
    GRAY,
    RGB,
    BGR,
} image_type;

bayer_array split_raw12(uchar *raw12, size_t width, size_t height, cfa_pattern pattern);
uchar *load_raw12(const char *path);

void write_ppm(const char *path, uchar *buffer, size_t width, size_t height,
               image_type type);







#ifdef __cplusplus
}
#endif
#endif
