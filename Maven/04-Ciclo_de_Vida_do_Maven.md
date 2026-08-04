# 4. O Ciclo de Vida do Maven

## Introdução

Vimos até agora como um projeto Maven é estruturado e como o `pom.xml` descreve suas informações. Mas afinal, como o Maven sabe *o que fazer* quando executamos um comando como `mvn install`? A resposta está no conceito de **ciclo de vida de build (build lifecycle)**.

Nessa aula vamos entender o que são esses ciclos de vida, quais são suas fases (*phases*) e como eles se relacionam com os *goals* dos plugins.

---

## O que é um Build Lifecycle?

Um *build lifecycle* é, basicamente, uma sequência pré-definida de etapas (chamadas de **fases**) que são executadas em uma ordem específica. Quando você pede para o Maven executar uma determinada fase, ele automaticamente executa, em ordem, todas as fases anteriores a ela também.

O Maven possui três ciclos de vida independentes entre si:

- **`default`**: cuida do processo de build e distribuição do projeto (compilar, testar, empacotar, etc);
- **`clean`**: cuida da limpeza dos artefatos gerados por builds anteriores;
- **`site`**: cuida da geração de documentação/site do projeto.

O mais utilizado no dia a dia, de longe, é o ciclo `default`, então vamos focar nele.

---

## Fases do Ciclo `default`

O ciclo `default` possui diversas fases, mas as mais relevantes para o dia a dia são:

1. **`validate`**: valida se o projeto está correto e se todas as informações necessárias estão disponíveis;
2. **`compile`**: compila o código-fonte do projeto (localizado em `src/main/java`);
3. **`test`**: executa os testes unitários (localizado em `src/test/java`), utilizando algum framework de testes adequado. Nessa fase o código ainda não é empacotado ou distribuído;
4. **`package`**: empacota o código compilado em seu formato distribuível, como um `.jar` ou `.war`, conforme definido na tag `<packaging>` do `pom.xml`;
5. **`verify`**: executa quaisquer verificações sobre os resultados de testes de integração, para garantir que os critérios de qualidade sejam atendidos;
6. **`install`**: instala o pacote gerado no repositório local (`.m2`), tornando-o disponível para ser usado como dependência em outros projetos na sua máquina;
7. **`deploy`**: copia o pacote final para um repositório remoto, para que ele possa ser compartilhado com outros desenvolvedores ou projetos.

### A Ordem Importa

Como comentado, ao executar uma fase, o Maven executa automaticamente todas as fases anteriores dela dentro do mesmo ciclo de vida. Ou seja, se você rodar:

```bash
mvn install
```

O Maven vai, na ordem, executar: `validate`, `compile`, `test`, `package`, `verify` e, por fim, `install`.

Isso significa que você não precisa (e nem deveria) chamar cada fase manualmente e em sequência; basta chamar a fase final que você deseja atingir.

---

## Fases vs. Goals

É importante entender a diferença entre **fase (phase)** e **goal**:

- Uma **fase** representa uma etapa do ciclo de vida (como `compile` ou `test`);
- Um **goal** é uma tarefa específica executada por um **plugin**, responsável por realizar o trabalho de fato.

Cada fase pode ter um ou mais *goals* vinculados a ela. Por exemplo, a fase `compile` está vinculada ao goal `compiler:compile`, do plugin `maven-compiler-plugin`, que é quem efetivamente realiza a compilação do código.

Ou seja, quando dizemos que o Maven "executa uma fase", o que realmente acontece é que ele executa todos os *goals* vinculados aquela fase, na ordem em que foram configurados.

É também possível executar um goal específico de um plugin diretamente, sem passar pelo ciclo de vida:

```bash
mvn compiler:compile
```

Falaremos mais sobre plugins e como configurá-los em uma aula futura dedicada a esse assunto.

---

## O Ciclo `clean`

O ciclo `clean` é responsável por limpar os artefatos gerados por builds anteriores, ou seja, apagar a pasta `target/` (vista na aula anterior). Ele possui três fases:

- `pre-clean`;
- `clean`;
- `post-clean`.

Para executá-lo, basta rodar:

```bash
mvn clean
```

É bastante comum combinar o ciclo `clean` com o `default` em um único comando, para garantir um build "limpo", sem restos de builds anteriores:

```bash
mvn clean install
```

---

## O Ciclo `site`

O ciclo `site` é responsável por gerar documentação do projeto em formato de site (HTML), com informações como relatórios de testes, dependências, entre outros. Ele é menos utilizado no dia a dia comparado aos outros dois ciclos, mas pode ser bastante útil dependendo do contexto do projeto.

```bash
mvn site
```

---

## Próximos Passos

Agora que você entende como o Maven executa suas tarefas através dos ciclos de vida, fases e goals, o próximo capítulo vai aprofundar em como o Maven gerencia as **dependências** do seu projeto e de onde elas vêm. Você pode encontrá-lo dentro do repositório ou clicando [aqui](05-Dependencias_e_Repositorios.md).

## Referências
[Introduction to the Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)

[Lifecycle Reference](https://maven.apache.org/ref/current/maven-core/lifecycles.html)