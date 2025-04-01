#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

unsigned get_bit(uint16_t reg, int n)
{
    return (reg >> n) & 1;
}

void lfsr_calculate(uint16_t *reg)
{
    /* YOUR CODE HERE */
    unsigned MSB = get_bit(*reg, 0) ^ get_bit(*reg, 2) ^ get_bit(*reg, 3) ^ get_bit(*reg, 5);
    *reg = (MSB << 15) | (*reg >> 1);
}
