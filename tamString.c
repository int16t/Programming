#include <stdio.h>

int tamString(char* str) {
    int i = 0;
    while (str[i] != '\0')i++;
    return i;
}


int main() {
    
    printf("%d\n", tamString("Limp Bizkit"));

    return 0;
}