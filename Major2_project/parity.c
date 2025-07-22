#include "major1.h"

int parity(uint32_t num) {
    int count = 0;
    while (num) {
        count ^= (num & 1);
        num >>= 1;
    }
    return count;
}
