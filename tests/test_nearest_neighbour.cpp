#include <nearest.h>
#include <assert.h>
#include <stdio.h>

int main() {
    // We want to copy the nearest neighbour value in this 4x4 matrix
    uchar i[16] = {3, 6,
                   5, 7};


    uchar *result = nearest(i, 2, 2);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf("%d", result[(i * 4) + j]);
        printf("\n");
    }
    printf("\n");


    // Aftear a call to nearest we should get a matrix of the form
    uchar r[16] = {3, 3, 6, 6,
                   3, 3, 6, 6,
                   5, 5, 7, 7,
                   5, 5, 7, 7};


    for (int i = 0; i < sizeof(r); i++) {
        assert(r[i] == result[i]);
    }

    uchar *single_row = nearest_single_row(i, 2, 2);

    uchar s[8] = {3, 3, 6, 6,
                  5, 5, 7, 7};

    for (int i = 0; i < sizeof(s); i++) {
        assert(s[i] == single_row[i]);
    }


}
