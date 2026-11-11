#include <stdio.h>
#include <stdlib.h>

#define MAX_ACOES 100
#define TAM_TEXTO 50

struct Acao {
    int codigo;
    char escola[TAM_TEXTO];
    char tema[TAM_TEXTO];
    char data[15];
    char publico[TAM_TEXTO];
    char responsavel[TAM_TEXTO];
    int qtdPrevista;
    int qtdEfetiva;
    int situacao;   /* 1 = Planejada, 2 = Realizada, 3 = Cancelada */
};

struct Acao acoes[MAX_ACOES];
int total = 0;

/* Le uma linha inteira do teclado e remove o '\n' final */
void lerLinha(char destino[], int tamanho) {
    int c;
    int fim = 0;

    if (fgets(destino, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada.\n");
        exit(0);
    }

    while (destino[fim] != '\0') {
        fim++;
    }

    if (fim > 0 && destino[fim - 1] == '\n') {
        destino[fim - 1] = '\0';
    } else {
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }
}

/* Retorna 1 se o texto estiver vazio ou apenas com espacos */
int textoVazio(char texto[]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != ' ' && texto[i] != '\t' && texto[i] != '\r') {
            return 0;
        }
    }
    return 1;
}

/* Le um texto obrigatorio (conforme Tabela 5.6) */
void lerTexto(char mensagem[], char destino[], int tamanho) {
    printf("%s", mensagem);
    lerLinha(destino, tamanho);
    while (textoVazio(destino)) {
        printf("Erro: campo obrigatorio! Digite o valor do campo pedido.\n");
        printf("%s", mensagem);
        lerLinha(destino, tamanho);
    }
}

/* Le um numero inteiro e trata entradas invalidas */
int lerInteiro(char mensagem[]) {
    char linha[100];
    char sobra;
    int numero;

    while (1) {
        printf("%s", mensagem);
        lerLinha(linha, 100);
        if (sscanf(linha, "%d %c", &numero, &sobra) == 1) {
            return numero;
        }
        printf("Erro: opcao invalida! Escolha um número que aparece no menu.\n");
    }
}

/* Valida formato dd/mm/aaaa e calendario */
int dataValida(char data[]) {
    int dia, mes, ano;
    char sobra;
    int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (sscanf(data, "%d/%d/%d %c", &dia, &mes, &ano, &sobra) != 3) {
        return 0;
    }
    if (mes < 1 || mes > 12 || ano < 2000 || ano > 2100) {
        return 0;
    }

    /* Ano bissexto */
    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        diasNoMes[1] = 29;
    }

    if (dia < 1 || dia > diasNoMes[mes - 1]) {
        return 0;
    }
    return 1;
}

char minuscula(char letra) {
    if (letra >= 'A' && letra <= 'Z') {
        return letra + ('a' - 'A');
    }
    return letra;
}

int textosIguais(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (minuscula(a[i]) != minuscula(b[i])) {
            return 0;
        }
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

/* Procura o codigo no vetor; devolve a posicao ou -1 */
int buscar(int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void mostrar(int i) {
    printf("\nCodigo: %d\n", acoes[i].codigo);
    printf("Escola: %s\n", acoes[i].escola);
    printf("Tema: %s\n", acoes[i].tema);
    printf("Data: %s\n", acoes[i].data);
    printf("Publico-alvo: %s\n", acoes[i].publico);
    printf("Responsavel: %s\n", acoes[i].responsavel);
    printf("Quantidade prevista: %d\n", acoes[i].qtdPrevista);
    printf("Quantidade efetiva: %d\n", acoes[i].qtdEfetiva);

    if (acoes[i].situacao == 1) {
        printf("Situacao: Planejada\n");
    } else if (acoes[i].situacao == 2) {
        printf("Situacao: Realizada\n");
    } else if (acoes[i].situacao == 3) {
        printf("Situacao: Cancelada\n");
    }
}

void cadastrar() {
    int codigo;

    if (total == MAX_ACOES) {
        printf("Erro: Limite de acoes atingido! Nao e possivel cadastrar mais acoes nesta execucao.\n");
        return;
    }

    codigo = lerInteiro("Codigo: ");
    while (codigo <= 0 || buscar(codigo) != -1) {
        if (codigo <= 0) {
            printf("Erro: Digite um numero igual ou maior que zero.\n");
        } else {
            printf("Erro: codigo ja cadastrado! Informe outro codigo.\n");
        }
        codigo = lerInteiro("Codigo: ");
    }
    acoes[total].codigo = codigo;

    lerTexto("Escola: ", acoes[total].escola, TAM_TEXTO);
    lerTexto("Tema: ", acoes[total].tema, TAM_TEXTO);

    lerTexto("Data prevista (dd/mm/aaaa): ", acoes[total].data, 15);
    while (dataValida(acoes[total].data) == 0) {
        printf("Erro: data invalida!\n");
        lerTexto("Data prevista (dd/mm/aaaa): ", acoes[total].data, 15);
    }

    lerTexto("Publico-alvo: ", acoes[total].publico, TAM_TEXTO);
    lerTexto("Responsavel: ", acoes[total].responsavel, TAM_TEXTO);

    acoes[total].qtdPrevista = lerInteiro("Quantidade prevista de participantes: ");
    while (acoes[total].qtdPrevista <= 0) {
        printf("Erro: Digite um numero igual ou maior que zero.\n");
        acoes[total].qtdPrevista = lerInteiro("Quantidade prevista de participantes: ");
    }

    acoes[total].situacao = 1;
    acoes[total].qtdEfetiva = 0;
    total++;

    printf(">> Acao cadastrada com sucesso! Situacao: Planejada\n");
}

void listar() {
    int i;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }
    printf("\n--- %d ACAO(OES) CADASTRADA(S) ---\n", total);
    for (i = 0; i < total; i++) {
        mostrar(i);
    }
}

void pesquisar() {
    int tipo, codigo, pos, i;
    int achou = 0;
    char texto[TAM_TEXTO];

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("1 - Codigo\n");
    printf("2 - Escola\n");
    printf("3 - Tema\n");
    tipo = lerInteiro("Pesquisar por: ");
    while (tipo < 1 || tipo > 3) {
        printf("Opcao invalida! Escolha um numero que aparece no menu.\n");
        tipo = lerInteiro("Pesquisar por: ");
    }

    if (tipo == 1) {
        codigo = lerInteiro("Codigo: ");
        pos = buscar(codigo);
        if (pos == -1) {
            printf("Acao nao encontrada! Confira o codigo na opcao 2 (Listar) e tente de novo.\n");
        } else {
            mostrar(pos);
        }
        return;
    }

    if (tipo == 2) {
        lerTexto("Escola: ", texto, TAM_TEXTO);
    } else {
        lerTexto("Tema: ", texto, TAM_TEXTO);
    }

    for (i = 0; i < total; i++) {
        if ((tipo == 2 && textosIguais(acoes[i].escola, texto)) ||
            (tipo == 3 && textosIguais(acoes[i].tema, texto))) {
            mostrar(i);
            achou = 1;
        }
    }
    if (achou == 0) {
        printf("Nenhuma acao encontrada!\n");
    }
}

int lerEfetivos() {
    int qtd = lerInteiro("Quantidade efetiva de participantes: ");
    while (qtd < 0) {
        printf("Erro: Digite um numero igual ou maior que zero.\n");
        qtd = lerInteiro("Quantidade efetiva de participantes: ");
    }
    return qtd;
}

void atualizar() {
    int codigo, pos, nova;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ");
    pos = buscar(codigo);

    if (pos == -1) {
        printf("Acao nao encontrada! Confira o codigo na opcao 2 (Listar) e tente de novo.\n");
        return;
    }

    printf("Nova situacao (1-Planejada 2-Realizada 3-Cancelada): ");
    nova = lerInteiro("");
    while (nova < 1 || nova > 3) {
        printf("Opcao invalida! Escolha um numero que aparece no menu.\n");
        printf("Nova situacao (1-Planejada 2-Realizada 3-Cancelada): ");
        nova = lerInteiro("");
    }

    acoes[pos].situacao = nova;
    acoes[pos].qtdEfetiva = 0;

    if (nova == 2) {
        acoes[pos].qtdEfetiva = lerEfetivos();
    }

    printf(">> Situacao atualizada com sucesso!\n");
}

void resumo() {
    int i;
    int planejadas = 0, realizadas = 0, canceladas = 0;
    int previstosRealizadas = 0, efetivos = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        if (acoes[i].situacao == 1) {
            planejadas++;
        } else if (acoes[i].situacao == 2) {
            realizadas++;
            previstosRealizadas += acoes[i].qtdPrevista;
            efetivos += acoes[i].qtdEfetiva;
        } else if (acoes[i].situacao == 3) {
            canceladas++;
        }
    }

    printf("\n===== RESUMO GERAL =====\n");
    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes realizadas: %d\n", realizadas);
    printf("Acoes canceladas: %d\n", canceladas);
    printf("Total de participantes: %d\n", efetivos);

    if (previstosRealizadas > 0) {
        printf("Participacao em relacao ao previsto: %.1f%%\n",
               efetivos * 100.0 / previstosRealizadas);
    } else {
        printf("Participacao em relacao ao previsto: 0.0%%\n");
    }
}

int main() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Acao\n");
        printf("2 - Listar Acoes\n");
        printf("3 - Pesquisar Acoes\n");
        printf("4 - Atualizar Situacao\n");
        printf("5 - Gerar Resumo\n");
        printf("0 - Sair\n");
        opcao = lerInteiro("Opcao: ");

        if (opcao == 1) {
            cadastrar();
        } else if (opcao == 2) {
            listar();
        } else if (opcao == 3) {
            pesquisar();
        } else if (opcao == 4) {
            atualizar();
        } else if (opcao == 5) {
            resumo();
        } else if (opcao == 0) {
            printf("Saindo...\n");
        } else {
            printf("Opcao invalida! Escolha um numero que aparece no menu.\n");
        }
    }

    return 0;
}
