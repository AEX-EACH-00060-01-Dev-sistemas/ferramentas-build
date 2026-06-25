#include "str_utils.h"

void to_uppercase(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        // Se a letra for minúscula, converte para maiúscula (Tabela ASCII)
        if(str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
        i++;
    }
}