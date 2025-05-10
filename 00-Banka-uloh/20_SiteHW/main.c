#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100


void remove_invalid_characters(char *str) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] == '0' || str[i] == '1') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int check_address_validity(const char *hex) {
    // Zkontrolujeme, jestli řetězec je platné hexadecimální číslo
    for (int i = 0; i < strlen(hex); i++) {
        if (!((hex[i] >= '0' && hex[i] <= '9') || (hex[i] >= 'a' && hex[i] <= 'f') || (hex[i] >= 'A' && hex[i] <= 'F'))) {
            return 0; // Pokud je znak neplatný, vrátíme 0 (chyba)
        }
    }
    
    // Převedeme hexadecimální hodnotu na celé číslo
    unsigned long long value = strtoull(hex, NULL, 16);
    
    // Zkontrolujeme velikost
    if (value <= 0xFF) {
        return 8;   // 8 bitů
    } else if (value <= 0xFFFF) {
        return 16;  // 16 bitů
    } else if (value <= 0xFFFFFFFF) {
        return 32;  // 32 bitů
    } else if (value <= 0xFFFFFFFFFFFFFFFF) {
        return 64;  // 64 bitů
    } else {
        return 0;   // Pokud je hodnota příliš velká, vracíme 0
    }
}

bool overIpv4(const char *ip)
{
    int iptest[4];
    if(sscanf(ip, "%d.%d.%d.%d", &iptest[0], &iptest[1], &iptest[2], &iptest[3]) != 4) { return false; }

    for(int i = 0; i < 4; i++) {
        if((iptest[i] > 255) || (iptest[i] < 0)) {
            return false;
        }
    }

    return true;
}

// IPV6 Address: "^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$", REG_EXTENDED);
bool overIpv6(const char *ip)
{
    int iptest[8];
    if(sscanf(ip, "%x:%x:%x:%x:%x:%x:%x:%x", &iptest[0], &iptest[1], &iptest[2], &iptest[3], &iptest[4], &iptest[5], &iptest[6], &iptest[7]) != 8) { return false; }

    for(int i = 0; i < 8; i++) {
        if((iptest[i] < 0) || (iptest[i] > 0xFFFF)) {
            return false;
        }
    }

    return true;
}

// MAC Address "^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$"
bool overMac(const char *ip) // POZOR!!! muzou byt oddelene i - misto :
{
    int test[6];
    if (sscanf(ip, "%x:%x:%x:%x:%x:%x", &test[0], &test[1], &test[2], &test[3], &test[4], &test[5]) != 6) { return false; }

    for(int i = 0; i < 6; i++) {
        if((test[i] < 0) || test[i] > 0xFF) {
            return false;
        }
    }

    return true;
}

// Email Address: "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
bool overEmail(const char *email)
{
    char test[3][MAX];
    if(sscanf(email, "%99s@%99s.%99s", test[0], test[1], test[2]) != 3) { return false; }

    for (int i = 0; email[i] != '\0'; i++) {
        char c = email[i];
        if (c == ' ' || c == ',' || c == ';' || c == '(' || c == ')' || c == '"' || 
            c == '<' || c == '>' || c == '[' || c == ']' || c == '/') {
            return false;  // Jakýkoli zakázaný znak vrátí false
        }
    }

    return true;
}


int main() {
    const char *mac = "01:23:45:67:89:AB";
    const char *ipv4 = "192.168.1.1";
    const char *ipv6 = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";
    const char *email = "user@example.com";

    printf("MAC adresa '%s' je %s.\n", mac, overMac(mac) ? "platná" : "neplatná");
    printf("IPv4 adresa '%s' je %s.\n", ipv4, overIpv4(ipv4) ? "platná" : "neplatná");
    printf("IPv6 adresa '%s' je %s.\n", ipv6, overIpv6(ipv6) ? "platná" : "neplatná");
    printf("E-mail '%s' je %s.\n", email, overEmail(email) ? "platný" : "neplatný");

    // Test pro odstranění neplatných znaků
    char str[] = "101abc011x101";
    remove_invalid_characters(str);
    printf("\nVýsledek po odstranění neplatných znaků: %s\n", str); // Výsledek bude "101011101"

    // Test pro kontrolu platnosti hexadecimální hodnoty
    const char *hex_value = "FFFFFFFF";
    int result = check_address_validity(hex_value);
    printf("\nVelikost hexadecimální adresy '%s': %d bitů\n", hex_value, result); // Výsledek bude 32

    return 0;
}
