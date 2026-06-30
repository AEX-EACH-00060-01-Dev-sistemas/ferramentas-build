# Aula Extra: Modularização em C (Entendendo arquivos .h e .o)

## 1. Introdução

Quando começamos a programar, é natural colocar todo o código dentro de um único arquivo (`main.c`). Para projetos pequenos, isso funciona bem. Mas o que acontece quando o projeto cresce e passa a ter milhares de linhas?

O arquivo vira um pesadelo para ler, entender e dar manutenção. A solução é a **Modularização**: dividir o programa em partes menores, onde cada arquivo é responsável por uma tarefa específica.

Para o computador juntar todas essas partes, a compilação é dividida em etapas — e é aqui que entram os diferentes tipos de arquivo:

| Tipo | Papel no projeto |
| --- | --- |
| `.c` (Source) | Contém a lógica real. É onde as funções são **implementadas** (o "como fazer"). |
| `.h` (Header) | Funciona como um "cardápio". Contém apenas as **declarações** das funções, avisando ao resto do programa: *"essa função existe em algum lugar, pode usá-la."* |
| `.o` (Object) | Resultado da compilação de um único `.c`. Contém código de máquina, mas **ainda não é um executável** — é uma peça de quebra-cabeça que precisa ser conectada (linkada) às outras. |

### Por que isso importa para o Make?

O Make brilha justamente por observar esses arquivos `.o`. Se você tem 50 arquivos `.c` e modifica apenas um, não faz sentido recompilar os outros 49. O Make detecta o que mudou, gera apenas o `.o` daquele arquivo e costura tudo de novo — economizando tempo de compilação em projetos grandes.

---

## 2. Mão na Massa: Compilando em Partes

Vamos criar uma mini-calculadora dividida em múltiplos arquivos para entender o fluxo completo do compilador.

### Passo 1: Criando os Arquivos

Crie uma pasta para este exercício e dentro dela crie os três arquivos abaixo:

**`matematica.h`** — O cardápio

```c
// Include Guards: impedem que este arquivo seja incluído mais de uma vez.
// Sem eles, o compilador reclamaria de definições duplicadas.
#ifndef MATEMATICA_H
#define MATEMATICA_H

// Apenas declaramos que a função existe. Não dizemos como ela funciona.
int somar(int a, int b);

#endif
```

**`matematica.c`** — A implementação

```c
#include "matematica.h"

int somar(int a, int b) {
    return a + b;
}
```

**`main.c`** — O ponto de entrada do programa

```c
#include <stdio.h>
#include "matematica.h" // Informa ao main.c que a função "somar" existe

int main() {
    int resultado = somar(5, 3);
    printf("O resultado da soma é: %d\n", resultado);
    return 0;
}
```

---

### Passo 2: Compilação — Gerando os Arquivos `.o`

Antes de tentar compilar tudo de uma vez, experimente:

```
$ gcc main.c -o programa
/usr/bin/ld: /tmp/ccXXXXXX.o: undefined reference to 'somar'
collect2: error: ld returned 1 exit status
```

O `main.c` sabe que `somar` existe (graças ao `.h`), mas o código dela não está lá. O linker não consegue encontrá-la e falha. Precisamos compilar em etapas.

Compile cada arquivo individualmente com a flag `-c` ("compile, mas não linke"):

```
$ gcc -c matematica.c
$ gcc -c main.c
```

Após esses dois comandos, liste os arquivos da pasta:

```
$ ls
main.c  main.o  matematica.c  matematica.h  matematica.o
```

Dois novos arquivos `.o` foram criados — as peças do quebra-cabeça em código de máquina.

---

### Passo 3: Linkagem — Juntando as Peças

Agora pedimos ao GCC (agora atuando como *linker*) que junte os `.o` e gere o executável final:

```
$ gcc main.o matematica.o -o calculadora
```

Execute o programa:

```
$ ./calculadora
O resultado da soma é: 8
```

Você acaba de fazer **manualmente** exatamente o trabalho que ensinaremos o Make a automatizar na Aula 01.

---

## 3. Resumo / Cheat Sheet

| Tipo de Arquivo | Função no Projeto |
| --- | --- |
| `.c` | Código-fonte. Contém a implementação real das funções. |
| `.h` | Cabeçalho. Contém declarações; usado com `#include`. |
| `.o` | Código objeto. Resultado da compilação de um único `.c`; ainda não é executável. |

**Include local vs. sistema:**

```c
#include <stdio.h>     // Busca na pasta de bibliotecas padrão do sistema
#include "matematica.h" // Busca na pasta do projeto
```

**A flag `-c`:** `gcc -c arquivo.c` cria `arquivo.o` sem linkar. Fundamental para compilação modular e para o funcionamento eficiente do Make.

**Include Guards:** sempre envolva o conteúdo dos seus `.h` com `#ifndef`, `#define` e `#endif`. Isso evita erros de redefinição quando vários `.c` incluem o mesmo cabeçalho.