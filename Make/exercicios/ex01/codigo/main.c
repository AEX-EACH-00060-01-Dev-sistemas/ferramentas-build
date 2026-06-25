#include <stdio.h>
#include "math_utils.h"

int main() {
    int a = 10;
    int b = 5;
    
    printf("Calculadora Simples\n");
    printf("%d + %d = %d\n", a, b, add(a, b));
    printf("%d - %d = %d\n", a, b, subtract(a, b));
    
    return 0;
}