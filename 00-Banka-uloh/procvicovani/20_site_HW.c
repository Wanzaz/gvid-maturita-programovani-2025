#include <stdio.h>
#include <stdbool.h>

bool validIPv4(char ip[])
{
    int test[4];
    if (sscanf(ip, "%d.%d.%d.%d", &test[0], &test[1], &test[2], &test[3]) != 4) { return false; }

    for (int i = 0; i < 4; i++) {
        if (test[i] < 0 || test[i] > 255) {
            return false;
        }
    }

    return true;
}


typedef unsigned int uint_t;
int main(int argc, char *argv[])
{
    char test[50] = "255.255.100.100";
    if (validIPv4(test)) {
        printf("Valid");
    }

    char _mask[4] = {255, 255, 240, 0};
    char _net[4] = {192, 124, 36, 10};

    uint_t mask = *((uint_t*)_mask);
    uint_t net = *((uint_t*)_net);

    uint_t result = net & ~mask; // to get host network address
    /* uint_t result = net & mask; // to get network address */

    unsigned char* subnet = (unsigned char*) &result;


    printf("%i", subnet[3]);
    return 0;
}
