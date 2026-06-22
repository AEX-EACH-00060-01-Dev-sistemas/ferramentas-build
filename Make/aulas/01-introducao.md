# Aula 01: Introdução e o Primeiro Makefile

> 🛑 **Pré-requisito Importante:** 

> Para aproveitar esta aula ao máximo, é fundamental que você entenda como funciona a modularização em C — ou seja, como trabalhar com múltiplos arquivos, o que são *headers* (`.h`) e o que são arquivos objeto (`.o`). Se você ainda não domina esses conceitos, não se preocupe! Preparamos uma aula extra sobre eles [Modularização-em-c](../aulas-extras/01-modularizacao-em-c.md). Recomendamos fortemente a leitura antes de prosseguir.

## 1. Introdução Teórica

O **Make** é uma ferramenta clássica de automação de *build* (construção) criada nos anos 70. Ele atua como um maestro: lê um arquivo de partitura chamado `Makefile` e executa os comandos necessários para compilar e montar o seu programa na ordem correta.

### O Problema que Resolvemos Aqui

Imagine um projeto real com dezenas ou centenas de arquivos `.c`. Compilar tudo manualmente digitando `gcc arquivo1.c arquivo2.c arquivo3.c ... -o meu_programa` no terminal, toda vez que você alterar uma única linha de código, traz três problemas:

1. **Lentidão:** Você vai cansar de digitar comandos enormes.
2. **Propensão a erros:** É muito fácil esquecer de incluir um arquivo novo ou atualizado.
3. **Ineficiência extrema:** O compilador vai traduzir *todos* os arquivos novamente, mesmo aqueles em que você não tocou.

O Make resolve isso rastreando as **dependências**. Ele analisa o seu projeto e deduz: *"Opa, você só alterou o `arquivo2.c`. Vou recompilar apenas ele e juntar com o restante que já estava pronto"*. Em projetos grandes, isso economiza horas de processamento.

---

## 2. Mão na Massa: Criando o seu primeiro Makefile

Para entendermos o Make na prática, precisamos de um pequeno projeto em C. Vamos construir um programa simples que exibe uma saudação.

> 💡 **Dica de Ouro:** Todos os códigos que vamos criar neste passo a passo já estão prontos e disponíveis no nosso repositório. Você pode encontrá-los na pasta `exemplos/aula-01/`. Fique à vontade para consultá-los se quiser comparar com o seu trabalho!

### Passo 1: Preparando o código-fonte

Crie uma pasta para o seu projeto, abra o terminal nela e crie os três arquivos abaixo:

**`mensagem.h`** (Declaração da nossa função)

```c
#ifndef MENSAGEM_H
#define MENSAGEM_H

void imprimir_saudacao();

#endif

```

**`mensagem.c`** (A implementação real)

```c
#include <stdio.h>
#include "mensagem.h"

void imprimir_saudacao() {
    printf("Olá! Seu Make está funcionando perfeitamente.\n");
}

```

**`main.c`** (O arquivo principal)

```c
#include "mensagem.h"

int main() {
    imprimir_saudacao();
    return 0;
}

```

Para compilar isso manualmente, o comando seria: `gcc main.c mensagem.c -o programa`. Vamos automatizar esse processo.

### Passo 2: A Anatomia de uma Regra do Make

O Make funciona com base em **regras**. A sintaxe fundamental de toda regra é:

```makefile
alvo: dependencias
	comando

```

* **Alvo (Target):** O nome do arquivo que queremos gerar (ou o nome de uma ação a ser executada).
* **Dependências (Prerequisites):** Os arquivos estritamente necessários para construir o alvo.
* **Comando (Recipe):** A instrução que o terminal deve executar para transformar as dependências no alvo.

> ⚠️ **A REGRA DE OURO DO MAKE:** O espaço antes do `comando` **TEM QUE SER UM `TAB`**. Você não pode usar espaços comuns (barra de espaço). Se usar espaços, o Make vai falhar imediatamente com o erro `missing separator`.

### Passo 3: Escrevendo o Makefile

Na mesma pasta dos seus arquivos `.c`, crie um arquivo chamado exatamente **`Makefile`** (sem extensão e com "M" maiúsculo) e escreva as regras abaixo:

```makefile
# Nossa primeira regra gera o executável final chamado 'programa'
programa: main.o mensagem.o
	gcc main.o mensagem.o -o programa

# Regra para compilar apenas o main.c
main.o: main.c mensagem.h
	gcc -c main.c

# Regra para compilar apenas o mensagem.c
mensagem.o: mensagem.c mensagem.h
	gcc -c mensagem.c

# Uma regra especial (phony target) para limpar os arquivos gerados
clean:
	rm -f *.o programa

```

*(Nota: Se você estiver no Windows usando o prompt padrão, o comando da regra `clean` seria `del /Q *.o programa.exe`), mas se estiver usando o ambiente MSYS2 configurado na Aula 00, mantenha o comando rm exatamente como está. O terminal MSYS2 fornece as ferramentas GNU normalmente.*.

### Passo 4: Executando a Mágica

1. No seu terminal, dentro da pasta do projeto, simplesmente digite:
```bash
make

```

2. O Make lerá a primeira regra (`programa`) e perceberá que precisa de `main.o` e `mensagem.o`. Ele irá procurar as regras para criá-los, executará os comandos na ordem exata e gerará o seu executável.
3. Execute `./programa` (ou `.\programa.exe` no Windows) para ver a mensagem!

**O Teste Definitivo da Eficiência:**
Execute o comando `make` de novo, sem alterar nenhum arquivo. Ele responderá: `make: 'programa' is up to date.` O Make percebeu que nada mudou e não perdeu tempo recompilando o que já estava pronto.

---

## 3. Resumo / Cheat Sheet

* **A estrutura básica:**
```makefile
alvo: dependencia1 dependencia2
[TAB]comando_a_ser_executado

```

* **O Tab Obrigatório:** O Make exige estritamente o caractere `Tab` antes de qualquer comando da regra.
* **Execução:** Digitar apenas `make` no terminal executa o **primeiro alvo** que aparecer no seu arquivo `Makefile`.
* **A flag `-c` do GCC:** Instrui o compilador a gerar apenas o arquivo objeto (`.o`), sem tentar criar o executável final. Essencial para compilação modular.
* **Limpeza (`clean`):** É uma boa prática ter um alvo `clean` para apagar os arquivos compilados (`.o` e executáveis), forçando o Make a reconstruir tudo do zero quando necessário. Basta digitar `make clean`.

---

## 4. O que veremos na próxima aula?

Se você observar o nosso `Makefile`, vai notar que repetimos palavras várias vezes — como os nomes dos arquivos `.o` e a chamada ao compilador `gcc`. Em projetos reais que crescem rápido, essa repetição vira uma dor de cabeça para manter.

Na **Aula 02**, vamos resolver isso aprendendo sobre **Variáveis e Macros** no Make, deixando o nosso script de build muito mais limpo, dinâmico e com cara de código profissional!