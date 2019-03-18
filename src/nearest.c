#include <stdio.h>
#include <nearest.h>
#include <assert.h>

// we asume the height is a multiple of 2
// also I asume the width is a multiple of 2
// [  v  | (v)  | ...] even row v should be copied into the other rows
// [ (v) | (v) | ...]  odd row
uchar* nearest(uchar *cfa_s, size_t width, size_t height) {
    uchar *deb_s = (uchar *)malloc(width * height * 4); //, sizeof(char));

    uchar (*deb)[width * 2] = (uchar (*)[width * 2])deb_s;
    uchar (*cfa)[width] = (uchar (*)[width])cfa_s;

    for (size_t k = 0; k < height; k++) {
        for (size_t i = 0; i < width; i++) {
            deb[2 * k][2 * i]         = cfa[k][i];
            deb[2 * k][(2 * i) + 1]     = cfa[k][i]; // [ v  | ..] we expand to the right
            deb[(2 * k) + 1][2 * i]     = cfa[k][i];
            deb[(2 * k) + 1][(2 * i) + 1] = cfa[k][i]; // [ .. | .. ] copy previous row
        }
    }

    return deb_s;
}

uchar* nearest_single_row(uchar *cfa_s, size_t width, size_t height) {

}
