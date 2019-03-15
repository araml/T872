#include <nearest.h>
#include <assert.h>

int main() {
    // We want to copy the nearest neighbour value in this 4x4 matrix
    char i[16] = {3, 0, 6, 0,
                  0, 0, 0, 0,
                  5, 0, 7, 0,
                  0, 0, 0, 0};

    char *result = nearest(i, 4, 4);

    // Aftear a call to nearest we should get a matrix of the form
    char r[16] = {3, 3, 6, 6,
                    3, 3, 6, 6,
                    5, 5, 7, 7,
                    5, 5, 7, 7};


    for (int i = 0; i < sizeof(r); i++) {
        assert(r[i] == result[i]);
    }
}
