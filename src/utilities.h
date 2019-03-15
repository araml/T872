#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char uchar;

struct rgb {
    uchar *r;
    uchar *g;
    uchar *b;
};

rgb split_raw12(const char *path_to_file);



#ifdef __cplusplus
}
#endif
#endif
