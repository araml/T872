#include <stdio.h>
#include <nearest.h>
#include <assert.h>

// we asume the height is a multiple of 2
// also I asume the width is a multiple of 2
// [ v |  | ...] even row v should be copied into the other rows
// [   |  | ...] odd row
uchar* nearest(uchar *cfa_s, size_t width, size_t height) {
    uchar *deb_s = (uchar *)malloc(width * height); //, sizeof(char));

    uchar (*deb)[width] = (uchar (*)[width])deb_s;
    uchar (*cfa)[width] = (uchar (*)[width])cfa_s;

    for (size_t k = 0; k < height; k += 2) {
        for (size_t i = 0; i < width; i += 2) {
            deb[k][i]         = cfa[k][i];
            deb[k][i + 1]     = cfa[k][i]; // [ v  | ..] we expand to the right
            deb[k + 1][i]     = cfa[k][i];
            deb[k + 1][i + 1] = cfa[k][i]; // [ .. | .. ] copy previous row
        }
    }

    return deb_s;
}
