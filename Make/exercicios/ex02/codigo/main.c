#include <stdio.h>
#include "str_utils.h"

int main() {
    char texto[] = "Makefile eh incrivel e automatiza tudo!";
    
    printf("Texto Original: %s\n", texto);
    to_uppercase(texto);
    printf("Texto Maiusculo: %s\n", texto);
    
    return 0;
}