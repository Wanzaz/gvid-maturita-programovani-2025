#include <stdio.h>

typedef unsigned int uint_t;

int main(void) 
{
    // we first define mask and ip as array
    unsigned char _mask[4] = {255, 255, 240, 0};
    unsigned char _net[4] = {192, 124, 36, 10};

    // then we convert list of numbers into 4byte number (unsinged int)
    uint_t mask = *((uint_t*)_mask);
    uint_t net = *((uint_t*)_net);

    // then we perform operation to get subnet
    uint_t result = net & ~mask; // to get host network address
    /* uint_t result = net & mask; // to get network address */

    // and then we turn our new net back to array of numbers
    unsigned char* subnet = (unsigned char*) &result;


    printf("%i.%i.%i.%i\n", subnet[0], subnet[1], subnet[2], subnet[3]);
}
