#include <stdio.h>
#include <stdbool.h>


bool xor(int a, int b)
{
    return (a || b) && !(a && b);
}

void aritmetickySoucet(char a[], char b[], char c[])
{
    int a1;
    int b1;
    int z;
    int zbytek = 0;
    for (int i = 15 ; i > 0; i--) {
        a1 = a[i] - '0';
        b1 = b[i] - '0';
        z = xor(a1, b1);
        int s = xor(z, zbytek);
        zbytek = (a1 && b1) || (z && zbytek);
        c[i] = s + '0';
    }
}


int main(int argc, char *argv[])
{
    char c[17];
    c[16] = '\0';
    char a[17] = "1111111111111111";
    char b[17] = "1111111111111111";

    aritmetickySoucet(a, b, c);

    printf("%s", c);

    return 0;
}
