#include "major1.h"

int count_leading_zeros(uint32_t num) {
    int count = 0;
    for (int i = 31; i >= 0; i--) {
        if ((num >> i) & 1)
            break;
        count++;
    }
    return count;
}
