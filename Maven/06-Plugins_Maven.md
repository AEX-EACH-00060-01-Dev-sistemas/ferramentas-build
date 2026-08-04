# 6. Plugins Maven

## Introdução

Nas aulas anteriores, comentamos algumas vezes sobre os **plugins** do Maven, principalmente quando falamos sobre o ciclo de vida de build: vimos que, na prática, quem executa o trabalho por trás de cada fase são os *goals* fornecidos pelos plugins. Nessa aula, vamos entender melhor o que são os plugins, como configurá-los e ver alguns dos mais utilizados no dia a dia.

---

## O que é um Plugin?

Na verdade, o Maven, por si só, não sabe compilar código, rodar testes ou empacotar um projeto. Todo esse trabalho é realizado por **plugins**, que são responsáveis por fornecer os *goals* que efetivamente executam essas tarefas.

Ou seja, o Maven funciona como uma espécie de "orquestrador": ele define o ciclo de vida (as fases), e os plugins fornecem a implementação real do que deve acontecer em cada uma delas.

Inclusive, mesmo as tarefas mais básicas do Maven, como compilar o código com a fase `compile`, são executadas por um plugin (nesse caso, o `maven-compiler-plugin`).

### Plugins Padrão (Default Bindings)

Você deve ter reparado que, nos exemplos de `pom.xml` das aulas anteriores, nunca declaramos nenhum plugin manualmente, mas, apesar disso, ainda conseguiriamos compilar, testar e empacotar o projeto normalmente. Isso acontece porque o Maven já vem, por padrão, com um conjunto de plugins pré-configurados e vinculados às fases do ciclo de vida `default`, de acordo com o `packaging` do projeto.

Ou seja, você **não precisa declarar** um plugin no seu `pom.xml` para que ele funcione, caso o comportamento padrão já atenda sua necessidade. Um projeto com `packaging` do tipo `jar`, por exemplo, já possui automaticamente os plugins `maven-compiler-plugin`, `maven-surefire-plugin`, `maven-jar-plugin`, entre outros, vinculados às fases correspondentes, mesmo sem nenhuma configuração adicional.

Você só precisa declarar um plugin explicitamente no `<build>` quando quiser:

- Fixar uma versão específica dele (evitando surpresas com atualizações automáticas);
- Alterar alguma configuração padrão (como a versão do Java, no caso do `maven-compiler-plugin`);
- Adicionar um plugin que não faz parte do conjunto padrão do Maven.

### Plugins de Build vs. Plugins de Reporting

Os plugins do Maven podem ser divididos em duas categorias principais:

- **Plugins de Build**: são executados durante o processo de build do projeto, sendo vinculados a fases do ciclo de vida (como compilar ou empacotar);
- **Plugins de Reporting**: são executados durante a geração do site do projeto (ciclo de vida `site`, visto na aula anterior), gerando relatórios e documentação.

Vamos focar principalmente nos plugins de build, já que são os mais utilizados no dia a dia.

---

## Configurando um Plugin

Plugins são configurados dentro da tag `<build>`, na seção `<plugins>`, no `pom.xml`:

```xml
<build>
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-compiler-plugin</artifactId>
            <version>3.13.0</version>
            <configuration>
                <source>17</source>
                <target>17</target>
            </configuration>
        </plugin>
    </plugins>
</build>
```

Assim como dependências, plugins também são identificados através de coordenadas (`groupId`, `artifactId` e `version`), e podem receber configurações específicas através da tag `<configuration>`, que varia de acordo com cada plugin.

### Vinculando um Goal a uma Fase

Por padrão, muitos plugins já possuem seus goals vinculados automaticamente a fases específicas do ciclo de vida (como vimos, o `maven-compiler-plugin` já está vinculado à fase `compile`). Porém, é possível vincular manualmente um goal específico de um plugin a uma fase, através da tag `<executions>`:

```xml
<plugin>
    <groupId>org.apache.maven.plugins</groupId>
    <artifactId>maven-antrun-plugin</artifactId>
    <version>3.1.0</version>
    <executions>
        <execution>
            <phase>validate</phase>
            <goals>
                <goal>run</goal>
            </goals>
        </execution>
    </executions>
</plugin>
```

No exemplo acima, o goal `run` do plugin `maven-antrun-plugin` foi configurado para ser executado durante a fase `validate`.

---

## Executando um Plugin Diretamente

Como vimos na aula sobre o ciclo de vida, também é possível executar um goal específico de um plugin diretamente pela linha de comando, sem depender do ciclo de vida:

```bash
mvn <groupId>:<artifactId>:<goal>
```

Um exemplo prático, utilizando o plugin `maven-dependency-plugin` para exibir a árvore de dependências (comando que já vimos na aula anterior):

```bash
mvn org.apache.maven.plugins:maven-dependency-plugin:tree
```

Para plugins bastante conhecidos e utilizados, o Maven também permite uma sintaxe reduzida, sem a necessidade do `groupId` completo:

```bash
mvn dependency:tree
```

---

## Alguns Plugins Comuns

Existem centenas de plugins disponíveis para o Maven, desenvolvidos tanto pela própria Apache quanto pela comunidade. Abaixo, alguns dos mais utilizados no dia a dia:

- **`maven-compiler-plugin`**: responsável pela compilação do código-fonte Java, permitindo configurar, por exemplo, a versão do Java utilizada;
- **`maven-surefire-plugin`**: responsável pela execução dos testes unitários durante a fase `test`;
- **`maven-failsafe-plugin`**: parecido com o `surefire`, mas focado em testes de integração, executados durante a fase `verify`;
- **`maven-jar-plugin`** / **`maven-war-plugin`**: responsáveis por empacotar o projeto em seu formato final (`.jar` ou `.war`), durante a fase `package`;
- **`maven-shade-plugin`** / **`maven-assembly-plugin`**: permitem gerar um artefato "fat jar" (ou "uber jar"), ou seja, um `.jar` que já inclui todas as dependências necessárias para rodar a aplicação;
- **`maven-clean-plugin`**: responsável por limpar a pasta `target/`, durante o ciclo `clean`;
- **`exec-maven-plugin`**: permite executar a aplicação diretamente através do Maven, através do goal `exec:java` (mencionado na aula extra sobre o Maven no VSCode).

---

## Próximos Passos

Agora que você já entende como os plugins funcionam e como configurá-los, o próximo capítulo vai explicar sobre os **arquétipos (archetypes)**, que permitem gerar rapidamente a estrutura inicial de um novo projeto Maven. Você pode encontrá-lo dentro do repositório ou clicando [aqui](07-Arquetipos_Maven.md).

## Referências
[Introduction to the Build Lifecycle - Plugins](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)

[Available Plugins](https://maven.apache.org/plugins/)

[Guide to Configuring Plug-ins](https://maven.apache.org/guides/mini/guide-configuring-plugins.html)