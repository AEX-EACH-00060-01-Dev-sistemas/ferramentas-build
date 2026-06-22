# 2. Como Instalar o Maven

## Pré-Requisitos

Antes da instalação é necessário possuir o Java Development Kit (JDK) instalado.

Verifique a instalação com os comandos:

``java -version``
``javac -version``

## Instalação no Windows
### Passo 1: Download
Baixe a distribuição binária do Apache Maven em seu site oficial ([aqui](https://maven.apache.org/download.cgi)).

### Passo 2: Extração
Extraia o arquivo baixado em alguma pasta de seu computador. Para evitar confusões depois e evitar que os arquivos sejam apagados de maneira não intencional, recomendo que seja feito em algum lugar seguro, particularmente eu salvo em: `C:/Arquivos de Programa/Apache/Maven`.

### Passo 3: Variáveis de Ambiente

Agora, nós precisamos adicionar a pasta `bin` do diretório do Maven as variáveis de ambiente do windows. Para isso:

- Aperte a tecla `windows` para abrir o menu inicial e pesquise **"Editar as variáveis de ambiente do sistema"** e clique na opção;
- Clique no botão **Variáveis de Ambiente...** na parte inferior da janela;
- Na caixa de "Váriaveis do sistema" selecione a opcão **Path** e clique em **Editar**;
- Clique em novo e adicione o diretório criado anteriormente e a pasta bin nele. Caso tenha criado a pasta no mesmo diretório que eu, vai ficar algo do tipo `C:/Arquivos de Programa/Apache/Maven/apache-maven-x.x/bin` (atente-se que o *x.x* está aqui pois a versão pode variar);
- Clique em OK em todas as janelas para salvar;

### Passo 4: Verificação
Para testar que tudo foi instalado corretamente, abra o prompt de comando e digite:

``mvn -v`` ou ``mvn -version``

Caso tudo tenha sido instalado corretamente, uma mensagem no estilo abaixo deve aparecer:

```Apache Maven 3.9.15 (98b2cdbfdb5f1ac8781f537ea9acccaed7922349)
Maven home: C:\apache-maven-3.9.15
Java version: 17.0.18, vendor: Oracle Corporation, runtime: C:\Program Files\Java\jdk-17.0.18
Default locale: pt_BR, platform encoding: Cp1252
OS name: "windows 11", version: "10.0", arch: "amd64", family: "windows"
```

---

## Instalação no macOS
A instalação no MacOS está disponível através do [Homebrew](https://brew.sh/), [SDKMAN!](https://sdkman.io/) e [MacPorts](https://www.macports.org/).

### Passo 1: Download
### Homebrew
Digite o comando:
``brew install maven``

### SDKMAN!
Digite o comando:
``sdk install maven``

### MacPorts
Digite o comando:
``sudo port install maven3``

### Passo 2: Verificação
Para testar que tudo foi instalado corretamente, abra o prompt de comando e digite:

``mvn -v`` ou ``mvn -version``

Caso tudo tenha sido instalado corretamente, uma mensagem detalhando sobre a versão do Maven deve aparecer.

---

## Instalação no Linux
A instalação no Linux vária de acordo com o *packet manager* da sua distribuição.

### Passo 1: Download
### APT (Ubuntu/Debian)
Digite o comando:
``sudo apt install maven``

### DNF (Fedora)
Digite o comando:
``sudo dnf install maven``

### YUM
Digite o comando:
``sudo yum install maven``

### Passo 2: Verificação
Para testar que tudo foi instalado corretamente, abra o prompt de comando e digite:

``mvn -v`` ou ``mvn -version``

Caso tudo tenha sido instalado corretamente, uma mensagem detalhando sobre a versão do Maven deve aparecer.

## Próximos Passos
Pronto! Agora o maven foi instalado na sua máquina e você pode prosseguir para a próxima aula do curso clicando [aqui]() ou navegando através do nosso repositório.

## Referências
[Maven Installation](https://maven.apache.org/install.html)