# PSE em Ação

### Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

Projeto desenvolvido para a AEP 2026.2 — Unicesumar
Engenharia de Software

---

## Sumário

- [O projeto](#o-projeto)
- [Equipe](#equipe)
- [Funcionalidades](#funcionalidades)
- [Tecnologias utilizadas](#tecnologias-utilizadas)
- [Como compilar e executar](#como-compilar-e-executar)
- [Como usar](#como-usar)
- [Exemplo de uso](#exemplo-de-uso)
- [Validações e mensagens de erro](#validações-e-mensagens-de-erro)
- [Limitações](#limitações)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Documentação e vídeo](#documentação-e-vídeo)

---

## O projeto

O **PSE em Ação** é uma aplicação de terminal desenvolvida em linguagem C para
apoiar a equipe intersetorial fictícia **IntegraPSE** no planejamento, registro e
acompanhamento de ações coletivas do **Programa Saúde na Escola (PSE)**,
programa federal que une as redes de Saúde e de Educação.

O sistema reúne em um só lugar as ações planejadas em diferentes escolas e
temas, permite atualizar a situação de cada ação e gera um resumo com os totais
e o percentual de participação em relação ao previsto.

> **Limites éticos:** o sistema trabalha apenas com dados **fictícios, administrativos
> e coletivos**. Ele não armazena nome, diagnóstico, prontuário ou qualquer dado
> clínico individual de estudantes.

---

## Equipe

### Felipe José Laverdi
**RA:** 26000536-2

- **1ª etapa:** contextualização, problema de pesquisa, objetivos e justificativa;
  engenharia de software (escopo, requisitos funcionais e não funcionais, sprints)
- **2ª etapa:** implementação do código em C; validação de entradas e tratamento de erros; registros dos testes; manual do usuário.

### João Vitor Cardoso da Silva
**RA:** 26001322-2

- **1ª etapa:** algoritmos e lógica de programação (fluxogramas); engenharia de
  software (sprints)
- **2ª etapa:** implementação do código em C; organização do código fonte; diagrama de casos de uso; descrição dos casos de uso.

### Yasser Abdel Nasser Haj Ahmad
**RA:** 26001346-2

- **1ª etapa:** contextualização, problema de pesquisa, objetivos e justificativa;
  engenharia de software (escopo, requisitos funcionais e não funcionais, sprints)
- **2ª etapa:** implementação do código em C; atualização dos requisitos; descrição dos casos de uso; repositório README e GitHub.

---

## Funcionalidades

| Opção | Funcionalidade | Descrição |
|:---:|---|---|
| 1 | **Cadastrar ação** | Registra código, escola, tema, data prevista, público-alvo, responsável e quantidade prevista de participantes. Toda ação nova começa como **Planejada**. |
| 2 | **Listar ações** | Exibe todas as ações cadastradas com seus dados e situação atual. |
| 3 | **Pesquisar ações** | Busca por **código**, **escola** ou **tema** (sem diferenciar maiúsculas e minúsculas). |
| 4 | **Atualizar situação** | Altera a situação para **Planejada**, **Realizada** ou **Cancelada**. |
| 4 | **Registrar participantes** | Quando a ação passa a **Realizada**, o sistema pede a quantidade efetiva de participantes. |
| 5 | **Resumo geral** | Mostra quantas ações estão planejadas, realizadas e canceladas, o total de participantes e o percentual de participação em relação ao previsto. |
| — | **Validação de entradas** | Impede códigos repetidos, campos vazios, datas inválidas, quantidades inválidas e opções inexistentes. |
| 0 | **Sair** | Encerra o programa. |

O percentual de participação considera apenas as ações realizadas:

```
Participação (%) = (soma dos participantes efetivos ÷ soma dos participantes previstos das ações realizadas) × 100
```

---

## Tecnologias utilizadas

- **Linguagem:** C (padrão ANSI, apenas `stdio.h` e `stdlib.h`)
- **Compilador:** GCC (Linux) ou MinGW/GCC (Windows)
- **Execução:** terminal (Linux, Prompt de Comando ou PowerShell)
- **Estruturas usadas:** `struct` para representar uma ação, vetor de `struct`
  para armazenar até 100 ações, funções separadas por responsabilidade,
  condicionais e laços de repetição
- **Versionamento:** Git e GitHub

---

## Como compilar e executar

### Pré-requisitos

- GCC instalado
  - **Linux:** `sudo apt install gcc` (Debian/Ubuntu)
  - **Windows:** instalar o [MinGW-w64](https://www.mingw-w64.org/) e adicionar a pasta `bin` ao `PATH`
- Git (opcional, apenas para clonar o repositório)

### 1. Baixar o projeto

Clone o repositório:

```bash
git clone https://github.com/Laverdii/AEP-2-Semestre.git
cd AEP-2-Semestre/codigofonte
```

Ou baixe pelo botão **Code → Download ZIP**, extraia e abra o terminal na pasta
`codigofonte`.

### 2. Compilar

```bash
gcc main.c -o pse_em_acao
```

### 3. Executar

**Linux:**
```bash
./pse_em_acao
```

**Windows (Prompt de Comando ou PowerShell):**
```bash
pse_em_acao.exe
```

---

## Como usar

1. Ao iniciar, o programa mostra o menu principal:

   ```
   ===== MENU =====
   1 - Cadastrar Acao
   2 - Listar Acoes
   3 - Pesquisar Acoes
   4 - Atualizar Situacao
   5 - Resumo Geral
   0 - Sair
   Opcao:
   ```

2. Digite o número da opção desejada e pressione **Enter**.
3. Responda aos campos pedidos. Se algum valor for inválido, o sistema explica o
   erro e pede o valor novamente.
4. Ao terminar cada operação, o programa volta ao menu.
5. Digite **0** para sair.

**Formatos esperados:**

| Campo | Formato |
|---|---|
| Código | Número inteiro maior que zero, sem repetir |
| Data prevista | `dd/mm/aaaa` (ex.: `10/11/2026`), ano entre 2000 e 2100 |
| Quantidade prevista | Número inteiro maior que zero |
| Quantidade efetiva | Número inteiro igual ou maior que zero |
| Situação | `1` Planejada, `2` Realizada, `3` Cancelada |

---

## Exemplo de uso

Cadastro de uma ação, atualização para "Realizada" e consulta do resumo:

```
Opcao: 1
Codigo: 1
Escola: Escola Municipal Aurora
Tema: Alimentacao saudavel
Data prevista (dd/mm/aaaa): 10/11/2026
Publico-alvo: Alunos do 5o ano
Responsavel: Equipe UBS Centro
Quantidade prevista de participantes: 30
>> Acao cadastrada com sucesso! Situacao: Planejada

Opcao: 4
Codigo da acao: 1
Nova situacao (1-Planejada 2-Realizada 3-Cancelada): 2
Quantidade efetiva de participantes: 27
>> Situacao atualizada com sucesso!

Opcao: 5

===== RESUMO GERAL =====
Acoes planejadas: 0
Acoes realizadas: 1
Acoes canceladas: 0
Total de participantes: 27
Participacao em relacao ao previsto: 90.0%
```

---

## Validações e mensagens de erro

| Situação | Comportamento do sistema |
|---|---|
| Código já cadastrado | Informa o erro e pede outro código |
| Código ou quantidade prevista menor ou igual a zero | Informa o erro e pede novo valor |
| Quantidade efetiva negativa | Informa o erro e pede novo valor |
| Campo obrigatório vazio | Pede o campo novamente |
| Data em formato errado ou inexistente (ex.: `31/02/2026`) | Exibe "data invalida" e pede a data de novo |
| Texto digitado onde se espera número | Informa o erro e pede novo valor |
| Opção inexistente no menu | Informa que a opção é inválida |
| Código não encontrado (pesquisa ou atualização) | Informa que a ação não foi encontrada |
| Limite de 100 ações atingido | Informa que não é possível cadastrar mais ações |
| Nenhuma ação cadastrada (listar, pesquisar, atualizar, resumo) | Informa que não há ações cadastradas |

---

## Limitações

- Os dados ficam apenas na memória e são perdidos ao encerrar o programa.
- O limite é de 100 ações por execução (constante `MAX_ACOES`).
- Não há edição dos demais campos nem exclusão de ações.
- A pesquisa por escola ou tema só encontra o nome completo; não encontra partes do texto.
- Não há controle de acesso por usuário.

**Possibilidades de melhoria:** salvar os dados em arquivo, usar alocação
dinâmica, permitir editar e excluir ações, pesquisar por parte do nome e exportar
o resumo em CSV.

---

## Estrutura do repositório

```text
AEP-2-Semestre/
├── README.md
├── codigofonte/
│   └── main.c                         # código-fonte completo do sistema
└── Documentação/
    ├── 1ª entrega/
    │   └── AEP 2 SEM - 1ª entrega.pdf  # planejamento e modelagem
    ├── 2ª entrega/
    │   └── AEP 2 SEM - final.pdf       # documento final
    ├── diagramas/
    │   ├── fluxograma geral.png
    │   ├── fluxograma detalhado.png
    │   └── diagrama de casos de uso.png
    └── capturas/                       # prints do sistema em execução
```

---

## Documentação e vídeo

| Item | Onde encontrar |
|---|---|
| Documento da 1ª entrega (contextualização, requisitos, fluxogramas, pseudocódigos, sprints) | [`Documentação/1ª entrega`](Documentação/1ª%20entrega) |
| Documento final (casos de uso, testes, manual do usuário, considerações finais) | [`Documentação/2ª entrega`](Documentação/2ª%20entrega) |
| Fluxogramas e diagrama de casos de uso | [`Documentação/diagramas`](Documentação/diagramas) |
| Vídeo de apresentação (até 7 minutos) | [`Link do vídeo no YouTube`](https://www.youtube.com/watch?v=5s53UTEGX7Q) |

---

## AEP 2026.2

Unicesumar - Engenharia de Software
