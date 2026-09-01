# 9. Projetos Multimódulo

## Introdução

Até agora, trabalhamos sempre com um único projeto Maven, contendo um único `pom.xml`. Porém, à medida que uma aplicação cresce, é bastante comum que ela precise ser dividida em partes menores e mais independentes, como, por exemplo, separar a camada de API, a camada de acesso a dados e bibliotecas compartilhadas em módulos distintos. Para isso, o Maven oferece suporte nativo a **projetos multimódulo**.

---

## O que é um Projeto Multimódulo?

Um projeto multimódulo é, basicamente, um projeto Maven "pai" (também chamado de *parent* ou *aggregator*), que agrupa e gerencia diversos outros projetos Maven "filhos" (os *módulos*), permitindo que todos sejam construídos em conjunto, através de um único comando, e que compartilhem configurações comuns entre si.

Essa abordagem traz diversas vantagens:

- Permite compilar e testar todos os módulos relacionados de uma só vez;
- Facilita o compartilhamento de configurações (como versões de dependências e plugins) entre os módulos;
- Ajuda a manter uma separação clara de responsabilidades dentro da aplicação;
- Permite que módulos dependam uns dos outros dentro do mesmo projeto, sem a necessidade de publicá-los em um repositório remoto antes.

---

## Estrutura de um Projeto Multimódulo

De maneira geral, um projeto multimódulo segue uma estrutura parecida com essa:

```text
meu-projeto/
├── pom.xml                 (POM pai)
├── modulo-core/
│   ├── pom.xml
│   └── src/
├── modulo-api/
│   ├── pom.xml
│   └── src/
└── modulo-web/
    ├── pom.xml
    └── src/
```

Repare que existe um `pom.xml` na raiz do projeto (o POM pai), e cada módulo possui seu próprio `pom.xml`, além de sua própria estrutura de diretórios (`src/main/java`, etc.), exatamente como vimos na aula sobre a estrutura de um projeto Maven.

---

## O POM Pai (Parent POM)

O POM pai é responsável por agregar os módulos e, opcionalmente, centralizar configurações comuns entre eles. Sua principal característica é o uso do `packaging` do tipo `pom` (mencionado rapidamente na aula sobre a estrutura de um projeto Maven), já que ele não gera nenhum artefato executável, servindo apenas como ponto de agregação.

```xml
<project>
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.mycompany.app</groupId>
    <artifactId>meu-projeto</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>pom</packaging>

    <modules>
        <module>modulo-core</module>
        <module>modulo-api</module>
        <module>modulo-web</module>
    </modules>
</project>
```

A tag `<modules>` é quem informa ao Maven quais subpastas devem ser tratadas como módulos daquele projeto. Ao executar um comando Maven a partir da pasta do POM pai (como `mvn install`), o Maven automaticamente identifica a ordem correta de build entre os módulos (baseado em suas dependências entre si) e os constrói em sequência.

---

## Herança (Inheritance)

Além de agregar módulos, o POM pai também pode ser utilizado para que os módulos filhos **herdem** configurações comuns, evitando repetição. Para isso, cada módulo filho declara o POM pai através da tag `<parent>`:

```xml
<project>
    <modelVersion>4.0.0</modelVersion>

    <parent>
        <groupId>com.mycompany.app</groupId>
        <artifactId>meu-projeto</artifactId>
        <version>1.0-SNAPSHOT</version>
    </parent>

    <artifactId>modulo-core</artifactId>
</project>
```

Repare que o módulo filho não precisa mais declarar o `groupId` e a `version`, já que ambos são herdados automaticamente do pai (a não ser que o filho queira explicitamente sobrescrever algum desses valores).

Configurações como `properties`, `dependencies`, `plugins`, entre outras, declaradas no POM pai, também são herdadas por todos os módulos filhos, permitindo centralizar configurações comuns em um único lugar.

### Dependency Management

Uma prática bastante comum em projetos multimódulo é centralizar as **versões** das dependências no POM pai, através da tag `<dependencyManagement>`, sem necessariamente adicioná-las diretamente ao build de todos os módulos:

```xml
<!-- No POM pai -->
<dependencyManagement>
    <dependencies>
        <dependency>
            <groupId>org.apache.commons</groupId>
            <artifactId>commons-lang3</artifactId>
            <version>3.14.0</version>
        </dependency>
    </dependencies>
</dependencyManagement>
```

Dessa forma, qualquer módulo filho que precisar dessa dependência pode declará-la sem especificar a versão, já que ela será herdada automaticamente do que foi definido no `dependencyManagement` do pai:

```xml
<!-- Em um módulo filho -->
<dependencies>
    <dependency>
        <groupId>org.apache.commons</groupId>
        <artifactId>commons-lang3</artifactId>
    </dependency>
</dependencies>
```

Isso garante que todos os módulos utilizem sempre a mesma versão de uma dependência, evitando conflitos e facilitando futuras atualizações (que passam a ser feitas em um único lugar).

---

## Dependências Entre Módulos

Um módulo também pode depender de outro módulo do mesmo projeto multimódulo, declarando-o normalmente como uma dependência, através de suas coordenadas GAV:

```xml
<!-- No pom.xml do modulo-api -->
<dependencies>
    <dependency>
        <groupId>com.mycompany.app</groupId>
        <artifactId>modulo-core</artifactId>
        <version>1.0-SNAPSHOT</version>
    </dependency>
</dependencies>
```

O Maven é inteligente o suficiente para entender essa relação e, durante o build, garantir que o `modulo-core` seja construído antes do `modulo-api`, já que este último depende dele.

---

## Agregação vs. Herança

É importante destacar que agregação (a tag `<modules>`) e herança (a tag `<parent>`) são conceitos relacionados, mas independentes:

- Um POM pode **agregar** outros módulos (definir quais projetos fazem parte do build conjunto) sem que os módulos necessariamente **herdem** dele;
- Da mesma forma, um módulo pode **herdar** de um POM pai, mesmo que esse pai não o agregue diretamente através de `<modules>`.

Na prática, porém, é bastante comum (e recomendado, na maioria dos casos) que o mesmo POM pai desempenhe os dois papéis ao mesmo tempo, como fizemos nos exemplos anteriores.

---

## Próximos Passos

Agora que você já entende como estruturar projetos maiores utilizando módulos, o próximo (e último, por enquanto) capítulo vai reunir algumas **boas práticas e tópicos avançados** que ainda não vimos, fechando os conhecimentos essenciais sobre o Maven. Você pode encontrá-lo dentro do repositório ou clicando [aqui](10-Boas_Praticas_e_Topicos_Avancados.md).

## Referências
[Guide to Working with Multiple Modules](https://maven.apache.org/guides/mini/guide-multiple-modules.html)

[POM Reference - Inheritance vs Aggregation](https://maven.apache.org/pom.html)

[Introduction to the POM - Dependency Management](https://maven.apache.org/guides/introduction/introduction-to-dependency-mechanism.html)