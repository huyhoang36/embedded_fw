/********************************************************************
 *      
 *          Author: Hoang Huy Nguyen
 *          UCSC Extension - Embedded Firmware Essentials
 *          Fall 2013
 *
 * File: hw1_lib.c
 * gcc -c hw1_lib.c -o hw1_lib.o
 * gcc -S hw1_lib.c -o hw1_lib.s
 * objdump -D hw1_lib.o
 *
 ********************************************************************
 */
#include "hw1_lib.h"

/********************************************************************
 *      
 * Function: gray_to_binary() 
 *
 * This file converts a 16-bit Gray code to 16-bit Binary Code.
 * The algorithm is like this:
 * - MSB of Binary code and Gray Code are the same.
 * - Bit[i] of Binary code = bit[i+1] of Binary Xor bit[i] of Gray Code
 *
 * Input:  16-bit Gray code
 * Output: 16-bit binary code
 *
 ********************************************************************
 */
uint16_t gray_to_binary(uint16_t gray)
{
    uint16_t bin = 0, result;
    int i;

    /* MSB of binary code is the same as Gray code */
    bin |= gray & BIT(15);

    /* Calculate the rest of the bits */
    for (i = 14; i >=0; i--) {
      result = ((gray & BIT(i)) >> i) ^ ((bin & BIT(i+1)) >> (i+1));
      bin |= result << i;
    }

    return bin;
}

/********************************************************************
 *      
 * Function: binary_to_gray() 
 *
 * This file converts a 16-bit Binary code to 16-bit Gray Code.
 * The algorithm is like this:
 * - MSB of Binary code and Gray Code are the same.
 * - Bit[i] of Gray code = bit[i+1] of Binary Xor bit[i] of Binary Code
 *
 * Input:  16-bit Binary code
 * Output: 16-bit Gray code
 *
 ********************************************************************
 */
uint16_t binary_to_gray(uint16_t binary)
{
    uint16_t gray;

    /* Calculate the Xor of all bits first */
    gray = binary ^ (binary >> 1);

    /* MSB of Gray code is the same as Binary */
    gray &= ~BIT(15);
    gray |= binary & BIT(15);

    return gray;
}

 
