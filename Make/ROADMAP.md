# ROADMAP do Curso de Make

Bem-vindo ao curso prático de Make! Este documento serve como guia e roteiro de estudos para você dominar a construção de projetos usando Makefiles, focando nas melhores práticas e na evolução contínua da estrutura do seu código.

## 🗺️ Estrutura do Curso e Aulas

O curso foi desenhado em um formato de "refatoração contínua", onde evoluímos de um script de compilação básico para uma arquitetura profissional de build.

- **[Aula 00: Configurando o Ambiente](aulas/00-configurando-ambiente.md.md)** Preparação de compiladores (GCC) e ferramentas básicas para rodar os exemplos.

- **[Aula 01: Introdução e Modularização em C](aulas/01-introducao.md)** Como sair de comandos longos no terminal para o seu primeiro `Makefile` simples (Targets, dependências e a famosa regra do TAB).

- **[Aula 02: Variáveis e Macros](aulas/02-variaveis-e-macros.md)** Uso de variáveis (`CC`, `CFLAGS`) e introdução às variáveis automáticas (`$@`, `$<`, `$^`) para deixar o Makefile mais dinâmico.

- **[Aula 03: Pattern Rules e Targets Especiais](aulas/03-pattern-rules-e-targets.md)** Criação de regras genéricas (`%.o: %.c`) substituindo antigas Suffix Rules, e uso do `.PHONY` para garantir a execução correta de targets de limpeza como o `clean`.

- **[Aula 04: Finalização e Estrutura Profissional](aulas/04-finalizacao.md)** Organização do projeto em diretórios separados (`src/`, `include/`, `build/`, `bin/`) e o "Padrão Ouro" da geração automática de dependências utilizando as flags `-MMD` e `-MP`.

## 🛠️ Exercícios Práticos

* **[Exercício 01:](exercicios/ex01/enunciadoEx01.md)** Escrita de um Makefile simples contendo alvos (*targets*) explícitos para compilar arquivos-objeto separadamente e realizar a linkagem do executável final.

* **[Exercício 02:](exercicios/ex02/enunciadoEx02.md)** Refatoração do processo de build através da criação de variáveis (`CC`, `CFLAGS`) e da introdução de variáveis automáticas (`$@`, `$^`, `$<`) para enxugar as regras de compilação.

* **[Exercício 03:](exercicios/ex03/enunciadoEx03.md)** Implementação de regras genéricas (*Pattern Rules* como `%.o: %.c`) para escalar a compilação e criação de *targets* utilitários isolados (como `clean` utilizando a diretiva `.PHONY`).

---

## 📚 Referências e Como se Aprofundar

Este curso foi embasado na literatura canônica e nas melhores fontes online da comunidade. Abaixo estão listadas as referências utilizadas para construir o conteúdo e sugestões essenciais para você aprofundar seus estudos:

### 📖 Livros Recomendados

1. **Managing Projects with GNU Make, 3rd Edition** *(Robert Mecklenburg, O'Reilly Media)* *Por que ler:* É o guia definitivo e comercial sobre GNU Make. Ensina não apenas a sintaxe, mas o pensamento arquitetural por trás de projetos complexos, lidando com performance, ambientes de desenvolvimento e recursão. Excelente para entender como organizar sistemas de compilação grandes.
2. **The GNU Make Manual** *(Richard M. Stallman, Roland McGrath, Paul D. Smith - Free Software Foundation)* *Por que ler:* A "bíblia" oficial do Make. Qualquer dúvida de sintaxe, flag ou função obscura estará documentada aqui. Sugerimos a leitura das seções sobre *Functions*, *Pattern Rules* e *Target-specific Variables* para dominar completamente as capacidades embutidas na ferramenta.

### 🌐 Sites e Tutoriais Essenciais

1. **[Makefile Tutorial By Example](https://makefiletutorial.com/)** *Por que acessar:* Um guia moderno e prático, focado em exemplos testáveis. A seção "Makefile Cookbook" é extremamente recomendada, oferecendo templates profissionais que automatizam a detecção de arquivos em pastas e a geração de dependências sem esforço.
2. **[Introdução ao Makefile - Portal Embarcados](https://embarcados.com.br/introducao-ao-makefile/)** *(por Lincoln Uehara)* *Por que acessar:* Material riquíssimo em português que aborda o tema de maneira muito didática, contextualizando o uso do Make dentro da engenharia de sistemas embarcados, explorando a compilação cruzada (Cross-Compilation) e a integração entre módulos.