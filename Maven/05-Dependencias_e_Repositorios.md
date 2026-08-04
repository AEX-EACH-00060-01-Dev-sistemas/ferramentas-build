# 5. Dependências e Repositórios

## Introdução

Um dos principais problemas que o Maven resolve, como vimos na primeira aula, é o **gerenciamento de dependências**. Nessa aula vamos entender em profundidade como declarar dependências no seu projeto, o que são escopos, como funciona o conceito de dependências transitivas e de onde, afinal, o Maven consegue essas bibliotecas.

---

## Declarando uma Dependência

Como já vimos, dependências são declaradas dentro da tag `<dependencies>` no `pom.xml`, sendo cada uma delas identificada pelas mesmas coordenadas GAV que vimos na aula sobre a estrutura de um projeto Maven:

```xml
<dependencies>
    <dependency>
        <groupId>org.apache.commons</groupId>
        <artifactId>commons-lang3</artifactId>
        <version>3.14.0</version>
    </dependency>
</dependencies>
```

- **`groupId`**: identifica o grupo/organização responsável pela biblioteca;
- **`artifactId`**: nome da biblioteca em si;
- **`version`**: versão específica da biblioteca que deseja utilizar.

Ao rodar qualquer comando Maven que necessite dessa dependência (como `compile` ou `test`), o Maven vai automaticamente localizá-la, baixá-la (caso ainda não esteja disponível localmente) e disponibilizá-la para o seu projeto.

---

## Escopos de Dependência (Scope)

Nem toda dependência precisa estar disponível durante todas as fases do build. Para isso existe a tag `<scope>`, que define em quais contextos aquela dependência deve estar disponível. Os principais escopos são:

- **`compile`** (padrão, usado quando a tag não é especificada): a dependência fica disponível em todas as fases do build (compilação, testes e execução), sendo também incluída no artefato final;
- **`test`**: a dependência só fica disponível durante a compilação e execução dos testes, não sendo incluída no artefato final. Frameworks de teste como JUnit costumam usar esse escopo;
- **`provided`**: a dependência é necessária para compilação e testes, mas não é incluída no artefato final, pois espera-se que ela já esteja disponível no ambiente de execução (um exemplo clássico é a API do Servlet em aplicações web, geralmente já fornecida pelo servidor de aplicação);
- **`runtime`**: a dependência não é necessária para compilação, apenas durante a execução e testes (um exemplo comum são drivers de banco de dados);
- **`system`**: parecido com `provided`, mas exige que o caminho da dependência seja informado manualmente através da tag `<systemPath>`. O uso desse escopo não é recomendado, sendo preferível utilizar um repositório local próprio nesses casos.

Exemplo utilizando o escopo `test`:

```xml
<dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.13.2</version>
    <scope>test</scope>
</dependency>
```

---

## Dependências Transitivas

Uma das grandes vantagens do Maven é o gerenciamento automático de **dependências transitivas**. Isso significa que, se a biblioteca "A" que você declarou no seu projeto depende de outra biblioteca "B", o Maven automaticamente baixa e disponibiliza a biblioteca "B" para você também, sem que você precise declará-la manualmente.

Isso é extremamente útil, mas pode ocasionalmente gerar conflitos, principalmente quando duas dependências diferentes do seu projeto dependem de versões diferentes de uma mesma biblioteca transitiva. Nesses casos, o Maven utiliza uma estratégia chamada **"nearest definition"** (definição mais próxima), ou seja, ele prioriza a versão que está mais próxima do seu projeto na árvore de dependências.

### Visualizando a Árvore de Dependências

Você pode visualizar toda a árvore de dependências do seu projeto (incluindo as transitivas) através do comando:

```bash
mvn dependency:tree
```

Esse comando é bastante útil para identificar de onde uma dependência transitiva está vindo, principalmente ao lidar com conflitos de versão.

### Excluindo uma Dependência Transitiva

Caso não queira que uma dependência transitiva específica seja incluída no seu projeto (por exemplo, por conflito de versão ou por não ser necessária), é possível excluí-la manualmente através da tag `<exclusions>`:

```xml
<dependency>
    <groupId>com.example</groupId>
    <artifactId>biblioteca-exemplo</artifactId>
    <version>1.0.0</version>
    <exclusions>
        <exclusion>
            <groupId>org.exemplo</groupId>
            <artifactId>dependencia-indesejada</artifactId>
        </exclusion>
    </exclusions>
</dependency>
```

---

## Repositórios

Mas afinal, de onde vêm essas dependências? O Maven trabalha com o conceito de **repositórios**, que são locais onde as bibliotecas (artefatos) ficam armazenadas. Existem, basicamente, dois tipos:

### Repositório Local

Todo desenvolvedor que utiliza o Maven possui, em sua própria máquina, um repositório local. Por padrão, ele fica localizado na pasta `.m2`, dentro do diretório do usuário (`~/.m2/repository`, no Linux/macOS, ou `C:\Users\SeuUsuario\.m2\repository`, no Windows).

Sempre que uma dependência é baixada de um repositório remoto, ela é armazenada nesse repositório local, para que não seja necessário baixá-la novamente em builds futuros.

### Repositório Remoto

Repositórios remotos são locais, geralmente hospedados na internet, onde artefatos ficam disponíveis para download. O principal e mais utilizado é o **Maven Central**, repositório público que hospeda a grande maioria das bibliotecas open-source do ecossistema Java.

Caso uma dependência não esteja disponível no seu repositório local, o Maven automaticamente busca por ela nos repositórios remotos configurados, sendo o Maven Central o padrão utilizado quando nenhum outro é especificado.

É possível, também, configurar repositórios remotos adicionais (privados ou de terceiros) diretamente no `pom.xml`:

```xml
<repositories>
    <repository>
        <id>meu-repositorio</id>
        <url>https://repositorio.exemplo.com/maven2</url>
    </repository>
</repositories>
```

Isso é bastante comum em empresas que possuem seus próprios repositórios privados, hospedando bibliotecas internas que não são públicas.

---

## Próximos Passos

Agora que você já entende como o Maven gerencia dependências e de onde elas vêm, o próximo capítulo vai explicar sobre os **plugins**, peças fundamentais que na verdade executam todo o trabalho por trás das fases do ciclo de vida do Maven. Você pode encontrá-lo dentro do repositório ou clicando [aqui](06-Plugins_Maven.md).

## Referências
[Dependency Mechanism](https://maven.apache.org/guides/introduction/introduction-to-dependency-mechanism.html)

[Introduction to Repositories](https://maven.apache.org/guides/introduction/introduction-to-repositories.html)

[Guide to Maven Central Repository](https://central.sonatype.org/)