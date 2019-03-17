#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

typedef unsigned char uchar;

typedef struct rgb {
    uchar *r;
    uchar *g;
    uchar *b;
} rgb;

typedef enum cfa_pattern {
    RGGB,  // raw12 pattern
    BGGR,  // gonna implement the first two only
    RGRB,
    RGBG,
} cfa_pattern;

rgb split_raw12(uchar *raw12, size_t width, size_t height, cfa_pattern pattern);

#ifdef __cplusplus
}
#endif
#endif
