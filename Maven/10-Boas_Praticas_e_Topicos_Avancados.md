# 10. Boas Práticas e Tópicos Avançados

## Introdução

Chegamos à última aula desse bloco introdutório sobre o Maven! Ao longo das aulas anteriores, vimos desde os conceitos mais básicos, como a estrutura de um projeto e o `pom.xml`, até tópicos mais avançados, como plugins, perfis e projetos multimódulo. Nessa aula, vamos reunir alguns tópicos adicionais e boas práticas que ainda não vimos, mas que são bastante relevantes no dia a dia com o Maven.

---

## Maven Wrapper

Um problema comum ao compartilhar um projeto Maven é garantir que todos os desenvolvedores (e também ambientes de CI/CD) estejam utilizando exatamente a mesma versão do Maven, evitando problemas de compatibilidade. Para resolver isso, existe o **Maven Wrapper (`mvnw`)**.

O Maven Wrapper é um pequeno script (`mvnw` para Linux/macOS, e `mvnw.cmd` para Windows) que fica na raiz do projeto e permite executar o Maven sem que ele precise estar previamente instalado na máquina. Caso a versão especificada não esteja disponível localmente, o próprio wrapper se encarrega de baixá-la automaticamente.

Para adicionar o wrapper a um projeto já existente, basta rodar:

```bash
mvn wrapper:wrapper
```

Após isso, ao invés de rodar `mvn install`, os desenvolvedores podem rodar:

```bash
./mvnw install
```

Isso garante que, independente de quem estiver rodando o comando, a mesma versão do Maven configurada no projeto será sempre utilizada.

---

## Versionamento e SNAPSHOT

Como vimos ao longo do curso, é bastante comum encontrar versões terminando em `-SNAPSHOT`, como `1.0-SNAPSHOT`. Esse sufixo indica que aquela versão ainda está em desenvolvimento ativo e pode mudar a qualquer momento, mesmo mantendo o mesmo número de versão.

Isso se diferencia de uma **versão de release** (como `1.0`, sem o sufixo), que representa uma versão final e imutável: uma vez publicada com um determinado número, ela nunca deve ser alterada novamente.

Um fluxo de trabalho comum envolve alternar entre esses dois estados: desenvolver normalmente em uma versão `SNAPSHOT`, e, ao finalizar uma nova versão estável, "promovê-la" para uma versão de release, para então voltar a trabalhar na próxima `SNAPSHOT` (por exemplo, indo de `1.0-SNAPSHOT` para `1.0`, e depois para `1.1-SNAPSHOT`).

O Maven já lida de forma diferente com dependências `SNAPSHOT`: por padrão, ele verifica periodicamente se existe uma versão mais recente disponível no repositório remoto, ao invés de simplesmente reutilizar a versão já baixada no repositório local, como acontece com versões de release.

---

## BOM (Bill of Materials)

Vimos na aula sobre projetos multimódulo que é possível centralizar versões de dependências no POM pai, através da tag `<dependencyManagement>`. Porém, e se você quiser compartilhar esse gerenciamento de versões entre **múltiplos projetos independentes**, que não fazem parte da mesma estrutura multimódulo?

Para esses casos, existe o conceito de **BOM (Bill of Materials)**: um `pom.xml` especial, com `packaging` do tipo `pom`, cujo único propósito é declarar um conjunto de versões de dependências relacionadas entre si (geralmente de um mesmo framework ou biblioteca), através da tag `<dependencyManagement>`.

Um projeto pode "importar" um BOM através da combinação de escopo `import` com o tipo `pom`:

```xml
<dependencyManagement>
    <dependencies>
        <dependency>
            <groupId>com.exemplo</groupId>
            <artifactId>exemplo-bom</artifactId>
            <version>2.5.0</version>
            <type>pom</type>
            <scope>import</scope>
        </dependency>
    </dependencies>
</dependencyManagement>
```

A partir disso, todas as versões definidas naquele BOM ficam disponíveis para uso no projeto, sem que seja necessário especificá-las manualmente em cada dependência.

---

## Verificando Dependências Desatualizadas

Manter as dependências de um projeto atualizadas é uma boa prática importante, tanto por questões de segurança quanto de manutenção. O plugin `versions-maven-plugin` oferece um goal bastante útil para isso:

```bash
mvn versions:display-dependency-updates
```

Esse comando analisa todas as dependências do projeto e informa quais delas possuem versões mais recentes disponíveis nos repositórios configurados.

---

## Boas Práticas

Para fechar, alguns pontos gerais que valem a pena ter em mente ao trabalhar com Maven no dia a dia:

- **Nunca versione a pasta `target/`**: como já mencionado, ela é gerada automaticamente e não deve fazer parte do controle de versão (Git);
- **Prefira `mvn clean install` a `mvn install`** ao testar builds importantes, para evitar resquícios de builds anteriores;
- **Fixe as versões de plugins importantes**, ao invés de depender apenas dos plugins padrão do Maven, garantindo builds mais previsíveis e reprodutíveis;
- **Centralize versões de dependências** utilizando `dependencyManagement`, seja em um projeto multimódulo ou através de um BOM, evitando divergências de versão entre módulos ou projetos;
- **Use o Maven Wrapper** em projetos compartilhados, para garantir consistência entre diferentes ambientes e desenvolvedores;
- **Evite dependências com escopo `system`**, preferindo sempre repositórios (locais ou remotos) adequados.

---

## Considerações Finais

Com essa aula, encerramos o bloco de conteúdos essenciais sobre o Maven, cobrindo desde sua história e propósito até tópicos mais avançados, como multimódulos, perfis e boas práticas. Com esse conhecimento, você já possui uma base sólida para utilizar o Maven no dia a dia em seus projetos Java.

## Referências
[Maven Wrapper](https://maven.apache.org/wrapper/)

[Guide to Managing Dependencies with a BOM](https://maven.apache.org/guides/introduction/introduction-to-dependency-mechanism.html)

[Versions Maven Plugin](https://www.mojohaus.org/versions/versions-maven-plugin/)

[Guide to Naming Conventions on groupId, artifactId, and version](https://maven.apache.org/guides/mini/guide-naming-conventions.html)