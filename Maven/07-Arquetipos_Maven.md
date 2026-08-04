# 7. Arquétipos Maven (Archetypes)

## Introdução

Ao longo das aulas anteriores, sempre partimos de um projeto Maven já existente, com sua estrutura de diretórios e `pom.xml` já criados. Mas como criar um novo projeto Maven do zero, de maneira rápida e já seguindo a estrutura padrão que vimos? É aí que entram os **arquétipos (archetypes)**, assunto que inclusive já foi mencionado rapidamente na aula extra sobre o Maven no VSCode.

---

## O que é um Arquétipo?

Um arquétipo é, basicamente, um **modelo (template)** de projeto Maven. Ele contém uma estrutura de diretórios e arquivos pré-definida, que serve como ponto de partida para a criação de um novo projeto, evitando que você precise montar tudo manualmente toda vez que for iniciar algo novo.

O próprio Maven já disponibiliza diversos arquétipos oficiais para os casos de uso mais comuns, como a criação de uma aplicação Java simples ou de uma aplicação web. Além disso, também é possível encontrar diversos arquétipos criados pela comunidade, voltados para frameworks e tecnologias específicas, e também é possível criar seus próprios arquétipos personalizados.

---

## Gerando um Projeto a Partir de um Arquétipo

Para gerar um novo projeto a partir de um arquétipo, utilizamos o goal `generate` do `maven-archetype-plugin`:

```bash
mvn archetype:generate
```

Repare que esse comando é um pouco diferente dos que vimos na aula anterior sobre plugins: normalmente, para executar um goal de um plugin, é necessário já estar dentro de um projeto Maven (ou seja, já ter um `pom.xml`). O `archetype:generate`, porém, é uma exceção a essa regra, já que seu propósito é justamente criar a estrutura inicial de um novo projeto, incluindo o próprio `pom.xml`. Por isso, ele pode (e deve) ser executado a partir de uma pasta vazia, fora de qualquer projeto Maven já existente.

Ao rodar esse comando sem nenhum parâmetro adicional, o Maven entra em um modo interativo, pedindo que você escolha, entre uma extensa lista, qual arquétipo deseja utilizar. Depois disso, ele também vai pedir que você informe as coordenadas do seu novo projeto (`groupId`, `artifactId` e `version`, conceitos que já vimos na aula sobre a estrutura de um projeto Maven).

### Gerando de Forma Não-Interativa

Também é possível pular o modo interativo, informando todos os parâmetros necessários diretamente no comando, através da flag `-D`:

```bash
mvn archetype:generate \
  -DgroupId=com.mycompany.app \
  -DartifactId=my-app \
  -DarchetypeArtifactId=maven-archetype-quickstart \
  -DarchetypeVersion=1.4 \
  -DinteractiveMode=false
```

Esse comando cria um novo projeto chamado `my-app`, utilizando o arquétipo `maven-archetype-quickstart` (que veremos a seguir), sem precisar de nenhuma interação manual.

---

## Arquétipos Oficiais Comuns

Dentre os diversos arquétipos oficiais disponibilizados pelo próprio Maven, alguns dos mais utilizados são:

- **`maven-archetype-quickstart`**: gera uma aplicação Java simples, já com uma classe `App` inicial e um teste unitário de exemplo. É o arquétipo mais comum para começar um projeto Java básico;
- **`maven-archetype-simple`**: parecido com o `quickstart`, mas com uma estrutura ainda mais enxuta, sem classes ou testes de exemplo;
- **`maven-archetype-webapp`**: gera a estrutura inicial de uma aplicação web Java (com `packaging` do tipo `war`), já incluindo a pasta `src/main/webapp` e um `web.xml` de exemplo;
- **`maven-archetype-archetype`**: um arquétipo especial, utilizado justamente para criar novos arquétipos personalizados.

---

## Criando um Arquétipo Personalizado

Caso sua equipe ou empresa costume criar projetos que sempre seguem uma mesma estrutura específica (com certas dependências, configurações e pastas padrão, por exemplo), é possível criar um arquétipo personalizado a partir de um projeto já existente, através do goal `create-from-project`:

```bash
mvn archetype:create-from-project
```

Esse comando analisa o projeto atual e gera, dentro da pasta `target/generated-sources/archetype`, um novo projeto de arquétipo baseado nele, que depois pode ser instalado no seu repositório local (ou publicado em um repositório remoto) para ser reutilizado futuramente por qualquer pessoa da equipe.

---

## Próximos Passos

Agora que você já sabe como criar novos projetos rapidamente a partir de arquétipos, o próximo capítulo vai explicar sobre os **perfis (profiles)** do Maven, que permitem customizar o comportamento do seu build de acordo com diferentes ambientes ou condições. Você pode encontrá-lo dentro do repositório ou clicando [aqui](08-Perfis_Maven.md).

## Referências
[Introduction to Archetypes](https://maven.apache.org/guides/introduction/introduction-to-archetypes.html)

[Maven Archetype Plugin](https://maven.apache.org/archetype/maven-archetype-plugin/)

[Guide to Creating Archetypes](https://maven.apache.org/guides/mini/guide-creating-archetypes.html)