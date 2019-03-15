#ifndef NEAREST_H
#define NEAREST_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char uchar;

uchar* nearest(uchar *src, size_t width, size_t height);

#ifdef __cplusplus
}
#endif

#endif // _NEAREST_H
