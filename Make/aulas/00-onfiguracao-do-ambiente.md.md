<!-- Aula 00: Configuração do Ambiente (C e Make) -->

## 1. Introdução Teórica

Antes de automatizarmos a construção de um software, precisamos ter as ferramentas que realmente realizam o trabalho de tradução do código. No nosso curso, utilizaremos a linguagem **C** como base pedagógica.

Para que o computador entenda e execute um programa em C, precisamos de duas coisas essenciais:

1. **Compilador (GCC ou Clang):** O programa que transforma o texto que você escreve (código-fonte `.c`) em linguagem de máquina (o arquivo executável).
2. **Automatizador (GNU Make):** A ferramenta que gerencia a ordem e a necessidade de compilação de cada arquivo do projeto.

---

## 2. Mão na Massa: Passo a Passo de Instalação

Escolha a seção correspondente ao seu sistema operacional e execute os comandos no seu terminal.

### 🐧 No Linux (Ubuntu / Debian e derivados)

O Linux é o ambiente nativo para a maioria dessas ferramentas. O processo é o mais direto de todos.

1. Abra o seu terminal e atualize a lista de pacotes do sistema:

```bash
sudo apt update
```

2. Instale o pacote `build-essential`, que já inclui o compilador GCC, o GNU Make e outras bibliotecas básicas de desenvolvimento:

```bash
sudo apt install build-essential -y
```

### 🍏 No macOS

No ecossistema Apple, as ferramentas de compilação são fornecidas oficialmente através do pacote de desenvolvimento do Xcode.

1. Abra o terminal e execute o comando abaixo para instalar as ferramentas de linha de comando:

```bash
xcode-select --install

```

2. Uma janela pop-up será exibida solicitando a confirmação. Clique em "Instalar" e aceite os termos de licença.

*(Opcional recomendado)* Se você utiliza o gerenciador de pacotes **Homebrew**, você também pode garantir a versão mais recente do GNU Make executando:

```bash
brew install make
```

### 🪟 No Windows (Via MSYS2)

O ecossistema Windows não possui o `make` nativamente. A forma mais moderna, limpa e profissional de instalar o GCC e o Make nativos no Windows (sem precisar recorrer a máquinas virtuais ou WSL neste primeiro momento) é utilizando o **MSYS2**.

1. Abra o **PowerShell** como Administrador e instale o MSYS2 usando o gerenciador de pacotes padrão do Windows:

```powershell
winget install MSYS2.MSYS2
```

2. Após o término da instalação, procure no Menu Iniciar por **"MSYS2 UCRT64"** e abra-o. Esse terminal fornece um ambiente de desenvolvimento compatível com as ferramentas GNU utilizadas em sistemas Linux.

3. Dentro do terminal do MSYS2, execute o comando abaixo para atualizar a base de dados de pacotes:

```bash
pacman -Syu
```

*(Se o terminal fechar sozinho durante a atualização, reabra o "MSYS2 UCRT64" e continue).*

4. Agora, instale o compilador GCC e a ferramenta Make executando:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make --noconfirm
```

5. Para conseguir usar esses comandos no prompt de comando padrão do Windows (cmd ou PowerShell), precisamos adicionar o caminho deles às **Variáveis de Ambiente** do Windows:
* No menu iniciar do Windows, digite: `Editar as variáveis de ambiente do sistema` e clique na opção.
* Clique no botão **Variáveis de Ambiente...** na parte inferior.
* Na caixa de "Variáveis do sistema", selecione a linha **Path** e clique em **Editar...**.
* Clique em **Novo** e cole o seguinte caminho: `C:\msys64\ucrt64\bin`
* Clique em OK em todas as janelas para salvar.

---

## 3. Validando a Instalação (O Teste Definitivo)

Feche todos os seus terminais abertos e abra um novo terminal (Prompt de Comando/PowerShell no Windows, ou o Terminal padrão no Linux/Mac).

### Passo 1: Verificar as versões das ferramentas

Digite os comandos abaixo. Eles devem retornar informações sobre as versões instaladas, e não mensagens de erro.

```bash
gcc --version
```

*(Espera-se uma saída indicando a versão do GCC ou Clang).*

```bash
# No Windows (se instalado via MSYS2), o comando pode se chamar mingw32-make
# No Linux e Mac, use apenas 'make'
make --version
```

### Passo 2: Compilação de Teste

Vamos criar e compilar um programa rápido para garantir que o compilador está conversando com o seu sistema operacional.

1. Crie um arquivo chamado `teste.c` e salve o código abaixo dentro dele:

```c
#include <stdio.h>

int main() {
    printf("Hello World!\n");
    return 0;
}
```

2. No terminal, navegue até a pasta onde salvou o arquivo e compile-o manualmente:

```bash
gcc teste.c -o teste_programa
```

3. Execute o programa gerado:
* **No Linux/Mac:** `./teste_programa`
* **No Windows:** `.\teste_programa.exe`

Se a frase *"Hello World"* apareceu na sua tela, você está pronto para prosseguir.

---

## 4. Resumo / Cheat Sheet

| Sistema Operacional | Comando de Instalação Principal | Comando do Compilador | Comando do Make |
| --- | --- | --- | --- |
| **Linux (Ubuntu/Debian)** | `sudo apt install build-essential` | `gcc` | `make` |
| **macOS** | `xcode-select --install` | `gcc` (ou `clang`) | `make` |
| **Windows (MSYS2)** | `pacman -S mingw-w64-ucrt-x86-64-gcc ...` | `gcc` | `mingw32-make` |