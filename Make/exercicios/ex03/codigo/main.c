#include <stdio.h>
#include "physics.h"

int main() {
    double massa = 1500.0; // kg
    double aceleracao = 3.5; // m/s^2
    
    printf("--- Simulador de Fisica Basica ---\n");
    printf("Massa do objeto: %.2f kg\n", massa);
    printf("Aceleracao: %.2f m/s^2\n", aceleracao);
    
    double forca = calcular_forca(massa, aceleracao);
    printf("Forca resultante: %.2f Newtons\n", forca);
    
    return 0;
}