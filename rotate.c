#include "major1.h"

// Rotate bits of a 32-bit number to the right by 'amount'
uint32_t rotate_right(uint32_t num, uint32_t amount) {
    amount %= 32; // Ensure it's within 0–31
    return (num >> amount) | (num << (32 - amount));
}
