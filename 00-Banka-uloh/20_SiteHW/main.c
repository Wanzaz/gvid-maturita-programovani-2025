#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValidMAC(const char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$", REG_EXTENDED);
    if (reti) return false;

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return reti == 0;
}

bool isValidIPv6(const char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$", REG_EXTENDED);
    if (reti) return false;

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return reti == 0;
}

bool isValidEmail(const char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$", REG_EXTENDED);
    if (reti) return false;

    reti = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return reti == 0;
}

bool isValidIPv4(const char *str) {
    if (str == NULL) return false;

    int len = strlen(str);
    if (len < 7 || len > 15) return false;

    int num, dots = 0;
    const char *ptr = str;
    char part[4];
    int i = 0;

    while (*ptr) {
        if (*ptr == '.') {
            if (i == 0) return false;

            part[i] = '\0';
            num = atoi(part);
            if (num < 0 || num > 255) return false;
            if (part[0] == '0' && i > 1) return false;

            i = 0;
            dots++;
        } else {
            if (!isdigit(*ptr) || i >= 3) return false;
            part[i++] = *ptr;
        }
        ptr++;
    }

    if (i == 0) return false;
    part[i] = '\0';
    num = atoi(part);
    if (num < 0 || num > 255) return false;
    if (part[0] == '0' && i > 1) return false;

    return dots == 3;
}

int main() {
    const char *mac = "01:23:45:67:89:AB";
    const char *ipv4 = "192.168.1.1";
    const char *ipv6 = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    const char *email = "user@example.com";

    // Výsledky testů
    printf("MAC: %s => %s\n", mac, isValidMAC(mac) ? "VALID" : "INVALID");
    printf("IPv4: %s => %s\n", ipv4, isValidIPv4(ipv4) ? "VALID" : "INVALID");
    printf("IPv6: %s => %s\n", ipv6, isValidIPv6(ipv6) ? "VALID" : "INVALID");
    printf("Email: %s => %s\n", email, isValidEmail(email) ? "VALID" : "INVALID");
    char input[100];

    /* printf("Zadejte retezec: "); */
    /* fgets(input, sizeof(input), stdin); */
    /* for (int i = 0; input[i] != '\0'; i++) { */
    /*     if (input[i] == '\n') { */
    /*         input[i] = '\0'; */
    /*         break; */
    /*     } */
    /* } */

    /* if (isValidMAC(input)) { */
    /*     printf("Validní MAC adresa\n"); */
    /* } else if (isValidIPv4(input)) { */
    /*     printf("Validní IPv4 adresa\n"); */
    /* } else if (isValidIPv6(input)) { */
    /*     printf("Validní IPv6 adresa\n"); */
    /* } else if (isValidEmail(input)) { */
    /*     printf("Validní e-mailová adresa\n"); */
    /* } else { */
    /*     printf("Neplatný vstup\n"); */
    /* } */

    return 0;
}

