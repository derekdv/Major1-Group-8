#ifndef MAJOR1_H
#define MAJOR1_H

#include <stdio.h>
#include <stdint.h>

// Function for parity check (returns 0 for even, 1 for odd)
int parity(uint32_t num);

// Function for rotating bits to the right
uint32_t rotate_right(uint32_t num, uint32_t amount);

#endif
