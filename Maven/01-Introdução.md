<!--Sobre o maven historinha papa e como instalar-->

# 1. Introdução

Explicando mais sobre o maven e ensinando como instala-lo.

## Sobre o Maven

O Maven, nomeado a partir de uma palavra na língua iídiche que significa "acumulador de conhecimento", é um projeto desenvolvido pela Apache Software Foundation e teve seu início em 2001 como parte do projeto Jakarta Alexandria e depois foi movido para o projeto [Apache Turbine](https://turbine.apache.org/). Naquela época cada projeto costumava possuir sua própria estrutura e mecanismos de compilação, algo que dificultava a manutenção, compartilhamento de código e a colaboração de desenvolvedores. O objetivo do Maven foi criar uma solução simples e padrão para o desenvolvimento de software.

Também é possível conhecer mais sobre a história no Maven no próprio [site do projeto](https://maven.apache.org/background/history-of-maven.html).

### O Problema que o Maven Soluciona
Antes, além de não existir qualquer tipo de padrão para a estrutura de projetos, o desenvolvedor precisava realizar, de maneira manual, a execução de diversas tarefas de maneira repetida e consecutiva, como:

- Compilação de código-fonte;
- Execução de testes;
- Geração de arquivos distribuíveis;
- Gerenciamento de bibliotecas e depêndencias externas;
- Publicação de novas versões;

Ademas, era necessário sempre garantir que os diversos ambientes de trabalho estivessem todos configurados de maneira constante, caso contrário poderiam ocorrer diversos problemas. Diversos programas possuíam diversos scripts e maneiras de executar esse processos, mas a falta de padrão dificultava a manutenção e aumentava a complexidade do projeto.

O Maven chega como uma forma de resolver tudo isso: ele simplifica e padroniza a organização de projetos, a automatização de tarefas e o gerenciamento de dependências. Com ele o desenvolvedor consegue acelerar o processo de desenvolvimento e facilitar o desenvolvimento em vários ambientes.

### Funcionamento
Apesar de explicarmos melhor sobre o maven nos capítulos seguintes, vamos tentar entender: como o Maven faz tudo isso?

Os projetos Maven são configurados usando um Project Object Model (POM) que está descrito em um arquivo nomeado `pom.xml`. Nele, são descritos diversas informações sobre o projeto, como seu nome, versão, depêndencias, entre outros. Com ele, o Maven consegue entender tudo sobre seu projeto e executa-lo de maneira adequada. Abaixo segue um exemplo mínimo de um `pom.xml`:

```
<project>
  <!-- model version é sempre 4.0.0 para POMs do Maven 2.x -->
  <modelVersion>4.0.0</modelVersion>

  <!-- "coordenadas do projeto", em outras palavras, 
  um grupo de valores que identificam esse projeto -->

  <groupId>com.mycompany.app</groupId>
  <artifactId>my-app</artifactId>
  <version>1.0</version>

  <!-- Dependências -->

  <dependencies>
    <dependency>

      <!-- identificação da dependência -->

      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>3.8.1</version>

      <!-- essa depêndencia é usada para execução e compilação de testes -->

      <scope>test</scope>

    </dependency>
  </dependencies>
</project>
```

*Esse exemplo foi retirada [daqui](https://pt.wikipedia.org/wiki/Apache_Maven) no dia 21/06/2026.*

Mais sobre tudo isso será explicado a frente, mas saiba que esse único arquivo que faz toda a "mágica" do Maven ser possível.

### Próximos Passos

O próximo capítulo explicará sobre como instalar e configurar o Maven em seu computador para os sistemas operacionais Windows, Linux e MacOS. Você pode encontra-lo dentro do repositório ou clicando [aqui](02-Como_Instalar_o_Maven.md).

## Referências
[History of Maven](https://maven.apache.org/background/history-of-maven.html)
[What is Maven](https://maven.apache.org/what-is-maven.html)