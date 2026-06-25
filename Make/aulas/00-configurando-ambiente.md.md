# Aula 00: Configuração do Ambiente (C e Make)

## 1. Introdução

Antes de automatizarmos a construção de um software, precisamos ter as ferramentas que realmente realizam o trabalho de tradução do código. No nosso curso, utilizaremos a linguagem **C** como base pedagógica.

Para que o computador entenda e execute um programa em C, precisamos de duas coisas essenciais:

| Ferramenta | Função |
| --- | --- |
| **Compilador (GCC ou Clang)** | Transforma o código-fonte `.c` em linguagem de máquina (o arquivo executável). |
| **Automatizador (GNU Make)** | Gerencia a ordem e a necessidade de compilação de cada arquivo do projeto. |

---

## 2. Instalação

Escolha a seção correspondente ao seu sistema operacional.

---

### 🐧 Linux (Ubuntu / Debian e derivados)

O Linux é o ambiente nativo para a maioria dessas ferramentas. O processo é o mais direto de todos.

**1.** Atualize a lista de pacotes do sistema:

```bash
sudo apt update
```

**2.** Instale o pacote `build-essential`, que já inclui o GCC, o GNU Make e bibliotecas básicas de desenvolvimento:

```bash
sudo apt install build-essential -y
```

---

### 🍏 macOS

No ecossistema Apple, as ferramentas de compilação são fornecidas pelo pacote de desenvolvimento do Xcode.

**1.** Execute o comando abaixo para instalar as ferramentas de linha de comando:

```bash
xcode-select --install
```

**2.** Uma janela pop-up será exibida solicitando confirmação. Clique em "Instalar" e aceite os termos de licença.

> **Nota:** No macOS, o comando `gcc` é na verdade um alias para o compilador **Clang** da Apple. Para o nosso curso isso não faz diferença prática — os comandos e flags que usaremos funcionam igualmente nos dois. Mas se em algum momento você ver `Apple clang` na saída do `gcc --version`, é completamente normal.

**(Opcional recomendado)** Se você usa o **Homebrew**, pode garantir a versão mais recente do GNU Make com:

```bash
brew install make
```

---

### 🪟 Windows (Via MSYS2)

O Windows não possui `make` nativamente. A forma mais moderna e profissional de instalar o GCC e o Make no Windows é utilizando o **MSYS2**.

**1.** Abra o **PowerShell como Administrador** e instale o MSYS2:

```powershell
winget install MSYS2.MSYS2
```

**2.** Após a instalação, procure no Menu Iniciar por **"MSYS2 UCRT64"** e abra-o. Esse terminal fornece um ambiente compatível com as ferramentas GNU do Linux.

**3.** Atualize a base de dados de pacotes:

```bash
pacman -Syu
```

> Se o terminal fechar sozinho durante a atualização, reabra o "MSYS2 UCRT64" e execute `pacman -Syu` novamente até não haver mais atualizações.

**4.** Instale o GCC e o Make:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make --noconfirm
```

**5.** Adicione as ferramentas ao PATH do Windows para poder usá-las em qualquer terminal:

- No menu Iniciar, busque por **"Editar as variáveis de ambiente do sistema"** e clique.
- Clique em **Variáveis de Ambiente...**.
- Em "Variáveis do sistema", selecione **Path** e clique em **Editar...**.
- Clique em **Novo** e cole: `C:\msys64\ucrt64\bin`
- Clique em OK em todas as janelas para salvar.

---

## 3. Validando a Instalação

Feche todos os terminais abertos e abra um novo (importante para o PATH atualizado ser carregado).

### Passo 1: Verificar as Versões

Execute os comandos abaixo. Eles devem retornar informações de versão, não erros.

**Compilador:**

```
$ gcc --version
```

Saída esperada (Linux/macOS):
```
gcc (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
```

Saída esperada (macOS):
```
Apple clang version 15.0.0 (clang-1500.3.9.4)
```

**Make:**

```
$ make --version
```

Saída esperada (Linux/macOS):
```
GNU Make 4.3
Built for x86_64-pc-linux-gnu
```

> **Usuários Windows:** o comando do Make instalado via MSYS2 se chama `mingw32-make`, não `make`. Use `mingw32-make --version` para validar. No terminal MSYS2 UCRT64, `make` também funciona diretamente.

---

### Passo 2: Compilação de Teste

Vamos compilar um programa rápido para garantir que o compilador está funcionando corretamente.

**1.** Crie um arquivo chamado `teste.c` com o seguinte conteúdo:

```c
#include <stdio.h>

int main() {
    printf("Hello World!\n");
    return 0;
}
```

**2.** No terminal, navegue até a pasta onde salvou o arquivo e compile:

```
$ gcc teste.c -o teste_programa
```

Nenhuma saída significa sucesso — o compilador só fala quando há um erro.

**3.** Execute o programa:

```
$ ./teste_programa
Hello World!
```

> **Usuários Windows (cmd/PowerShell):** use `.\teste_programa.exe` para executar.

Se "Hello World!" apareceu na tela, o ambiente está pronto.

---

## 4. Resumo / Cheat Sheet

| Sistema Operacional | Instalação | Compilador | Make |
| --- | --- | --- | --- |
| **Linux (Ubuntu/Debian)** | `sudo apt install build-essential` | `gcc` | `make` |
| **macOS** | `xcode-select --install` | `gcc` (alias para `clang`) | `make` |
| **Windows (MSYS2)** | `pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make` | `gcc` | `mingw32-make` |

---

## 5. O que veremos na próxima aula?

Com o ambiente configurado, estamos prontos para começar. Antes de escrever o primeiro `Makefile`, é importante entender como a compilação em C funciona em múltiplos arquivos — o que são `.h`, `.c` e `.o` e por que eles existem.

Se está familiarizado com esses temas, consulte a [Aula Extra: Modularização em C](../aulas-extras/01-modularizacao-em-c.md) antes de prosseguir para a Aula 01.