# 3. Estrutura de um Projeto Maven

## Introdução

Como vimos no capítulo anterior, um dos grandes objetivos do Maven é padronizar a forma como projetos são organizados. Isso é feito através de duas coisas principais: uma **convenção de diretórios** que todo projeto Maven segue, e o arquivo `pom.xml`, que descreve tudo sobre o projeto.

Nessa aula, vamos entender em detalhes como essas duas partes funcionam.

---

## Convenção sobre Configuração

O Maven segue uma filosofia chamada *"Convention over Configuration"* (Convenção sobre Configuração). Isso significa que, ao invés de você precisar configurar manualmente onde ficam seus arquivos de código-fonte, testes, recursos, entre outros, o Maven já espera que eles estejam em locais pré-definidos.

Isso traz uma grande vantagem: qualquer desenvolvedor que já conheça Maven, ao abrir um novo projeto que também usa Maven, já sabe exatamente onde encontrar cada coisa, independente de quem o criou.

Claro, é possível customizar essa estrutura caso seja necessário, mas na maioria dos casos, seguir a convenção padrão é o suficiente e o recomendado.

## Estrutura de Diretórios

Um projeto Maven padrão possui uma estrutura de diretório definida. Qualquer projeto que siga a estrutura abaixo pode ser classificado como um projeto Maven.

```text
meu-projeto/
├── pom.xml
└── src/
    ├── main/
    │   ├── java/
    │   └── resources/
    └── test/
        ├── java/
        └── resources/
```

Vamos entender cada uma dessas pastas:

- **`pom.xml`**: arquivo principal de configuração do projeto, fica sempre na raiz;
- **`src/main/java`**: aqui fica todo o código-fonte principal da sua aplicação;
- **`src/main/resources`**: aqui ficam arquivos que não são código Java, mas que são necessários para a aplicação rodar, como arquivos `.properties`, `.xml`, `.yml`, entre outros;
- **`src/test/java`**: aqui fica o código-fonte dos seus testes;
- **`src/test/resources`**: assim como o `main/resources`, mas para arquivos usados durante a execução dos testes;

Após a compilação, o Maven também cria automaticamente uma pasta chamada `target/`, onde ficam todos os arquivos gerados durante o processo de build, como os arquivos `.class` compilados e o artefato final (`.jar`, `.war`, etc). Essa pasta não deve ser versionada no seu controle de versão (Git, por exemplo).

```text
meu-projeto/
├── pom.xml
├── target/
└── src/
    └── ...
```

> **Dica:** caso utilize Git, é recomendado adicionar a pasta `target/` no seu arquivo `.gitignore`, já que ela é gerada automaticamente pelo Maven e não deve ser versionada.

---

## O Arquivo `pom.xml`

O `pom.xml` (Project Object Model), assim como mencionado anteriormente, é o coração de qualquer projeto Maven. É nele que ficam descritas todas as informações e configurações do projeto: nome, versão, dependências, plugins, entre diversas outras coisas.

Abaixo vamos abordar como esse arquivo é divido e o uso de cada uma de suas tags.

### Coordenadas do Projeto (GAV)

Todo projeto Maven é identificado unicamente através de três informações, conhecidas popularmente como **GAV**:

```xml
<groupId>com.mycompany.app</groupId>
<artifactId>my-app</artifactId>
<version>1.0</version>
```

- **`groupId`**: identifica o grupo ou organização responsável pelo projeto. Geralmente segue o padrão de domínio invertido, como `com.empresa.projeto`;
- **`artifactId`**: nome do projeto/artefato em si;
- **`version`**: versão do projeto. É bastante comum encontrar versões terminando em `-SNAPSHOT`, o que indica que aquela versão ainda está em desenvolvimento e pode sofrer alterações;

Juntas, essas três informações formam as "coordenadas" que identificam de forma única qualquer projeto ou dependência dentro do ecossistema Maven.

### Model Version

```xml
<modelVersion>4.0.0</modelVersion>
```

Essa tag define a versão do modelo do POM que está sendo utilizada. Para o Maven 2.x e 3.x (as versões mais utilizadas atualmente), esse valor é sempre `4.0.0`.

### Packaging

```xml
<packaging>jar</packaging>
```

Define o tipo de artefato que será gerado ao final do build. Os valores mais comuns são:

- `jar`: gera um arquivo `.jar` (padrão, caso a tag não seja especificada);
- `war`: gera um arquivo `.war`, normalmente utilizado em aplicações web;
- `pom`: indica que esse projeto não gera um artefato "executável", sendo utilizado normalmente em projetos pai de estruturas multimódulo (assunto que veremos em uma aula futura).

### Properties

```xml
<properties>
    <maven.compiler.source>17</maven.compiler.source>
    <maven.compiler.target>17</maven.compiler.target>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
</properties>
```

A tag `<properties>` permite definir variáveis que podem ser reutilizadas em outras partes do `pom.xml`, evitando repetição e facilitando futuras alterações. É bastante comum utilizá-la para definir, por exemplo, a versão do Java utilizada no projeto ou o encoding dos arquivos.

### Dependencies

```xml
<dependencies>
    <dependency>
        <groupId>junit</groupId>
        <artifactId>junit</artifactId>
        <version>3.8.1</version>
        <scope>test</scope>
    </dependency>
</dependencies>
```

Lista todas as bibliotecas externas (dependências) que o projeto usa e precisa para funcionar de  maneira adequada. Falaremos mais sobre dependências, seus escopos e como o Maven as gerencia em uma aula futura dedicada a esse assunto.

### Build e Plugins

```xml
<build>
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-compiler-plugin</artifactId>
            <version>3.13.0</version>
        </plugin>
    </plugins>
</build>
```

A tag `<build>` permite customizar o processo de build do projeto, sendo um dos usos mais comuns a configuração de plugins, que estendem as funcionalidades padrão do Maven. Também veremos mais sobre isso em uma aula dedicada ao assunto.

---

## Exemplo Completo

Juntando um pouco do que vimos, um `pom.xml` um pouco mais completo se pareceria com algo do tipo:

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.mycompany.app</groupId>
    <artifactId>my-app</artifactId>
    <version>1.0-SNAPSHOT</version>
    <packaging>jar</packaging>

    <properties>
        <maven.compiler.source>17</maven.compiler.source>
        <maven.compiler.target>17</maven.compiler.target>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
    </properties>

    <dependencies>
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>3.8.1</version>
            <scope>test</scope>
        </dependency>
    </dependencies>
</project>
```

---

## Próximos Passos

Agora que você já entende como um projeto Maven é organizado e como seu `pom.xml` é estruturado, o próximo capítulo vai explicar como o Maven efetivamente executa suas tarefas através do seu **ciclo de vida de build (build lifecycle)**. Você pode encontrá-lo dentro do repositório ou clicando [aqui](04-Ciclo_de_Vida_do_Maven.md).

## Referências
[Introduction to the POM](https://maven.apache.org/guides/introduction/introduction-to-the-pom.html)

[POM Reference](https://maven.apache.org/pom.html)

[Introduction to the Standard Directory Layout](https://maven.apache.org/guides/introduction/introduction-to-the-standard-directory-layout.html)