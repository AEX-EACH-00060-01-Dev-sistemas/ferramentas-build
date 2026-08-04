# 8. Perfis Maven (Profiles)

## Introdução

Até agora, sempre trabalhamos com um `pom.xml` que se comporta da mesma forma, independente de quem ou onde o build é executado. Mas, na prática, é bastante comum que um projeto precise se comportar de maneira diferente dependendo do contexto: talvez você queira usar um banco de dados diferente em ambiente de desenvolvimento e produção, ou talvez alguma configuração precise mudar dependendo do sistema operacional de quem está rodando o build. Para esses casos, o Maven oferece os **perfis (profiles)**.

---

## O que é um Perfil?

Um perfil é, basicamente, um conjunto alternativo de configurações que pode ser ativado (ou não) durante a execução de um build, permitindo alterar comportamentos do `pom.xml` sem precisar duplicar o projeto inteiro ou editá-lo manualmente toda vez que o contexto mudar.

Dentro de um perfil, é possível sobrescrever ou adicionar praticamente qualquer configuração que já vimos até agora: dependências, plugins, properties, entre outras.

---

## Declarando um Perfil

Perfis são declarados dentro da tag `<profiles>`, no `pom.xml`:

```xml
<profiles>
    <profile>
        <id>desenvolvimento</id>
        <properties>
            <ambiente.url>http://localhost:8080</ambiente.url>
        </properties>
    </profile>
    <profile>
        <id>producao</id>
        <properties>
            <ambiente.url>https://meuapp.com</ambiente.url>
        </properties>
    </profile>
</profiles>
```

No exemplo acima, temos dois perfis, `desenvolvimento` e `producao`, cada um definindo um valor diferente para a property `ambiente.url`. Dependendo de qual perfil for ativado durante o build, um valor diferente será utilizado.

---

## Ativando um Perfil

Existem diversas formas de ativar um perfil. Vamos ver as mais comuns.

### Manualmente, via Linha de Comando

A forma mais direta é ativar o perfil manualmente ao executar um comando Maven, através da flag `-P`, seguida do `id` do perfil desejado:

```bash
mvn install -Pproducao
```

Também é possível ativar múltiplos perfis ao mesmo tempo, separando-os por vírgula:

```bash
mvn install -Pproducao,outro-perfil
```

### Ativação Automática por Condição

Também é possível configurar um perfil para ser ativado automaticamente, de acordo com alguma condição, através da tag `<activation>`. Algumas das condições mais comuns são:

**Por propriedade do sistema:**

```xml
<profile>
    <id>windows</id>
    <activation>
        <os>
            <family>windows</family>
        </os>
    </activation>
</profile>
```

**Por ser (ou não) a versão padrão, caso nenhum outro perfil seja ativado manualmente:**

```xml
<profile>
    <id>desenvolvimento</id>
    <activation>
        <activeByDefault>true</activeByDefault>
    </activation>
</profile>
```

**Pela presença de um arquivo específico:**

```xml
<profile>
    <id>com-arquivo-especifico</id>
    <activation>
        <file>
            <exists>algum-arquivo.properties</exists>
        </file>
    </activation>
</profile>
```

### Verificando Quais Perfis Estão Ativos

Caso queira conferir quais perfis estão sendo ativados em um determinado build, é possível utilizar o comando:

```bash
mvn help:active-profiles
```

---

## Casos de Uso Comuns

Alguns exemplos práticos de onde perfis costumam ser bastante úteis:

- **Ambientes diferentes** (desenvolvimento, homologação, produção): alterando URLs, credenciais ou configurações específicas de cada ambiente;
- **Sistemas operacionais diferentes**: caso o build precise de alguma configuração ou dependência específica dependendo do SO de quem está rodando;
- **Builds opcionais**: como, por exemplo, um perfil que só executa testes de integração (que podem ser mais demorados), sendo ativado apenas quando necessário, e não em todo build;
- **Múltiplos ambientes de deploy**: alterando o repositório remoto de destino, dependendo de qual perfil for ativado.

---

## Próximos Passos

...

## Referências
[Introduction to Build Profiles](https://maven.apache.org/guides/introduction/introduction-to-profiles.html)

[Profile Activation - POM Reference](https://maven.apache.org/pom.html#profiles)