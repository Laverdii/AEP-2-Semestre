#include <stdio.h>

struct Acao {
    int codigo;
    char escola[50];
    char tema[50];
    char data[15];
    char publico[50];
    char responsavel[50];
    int qtdPrevista;
    int qtdEfetiva;
    int situacao;   /* 1 = Planejada, 2 = Realizada, 3 = Cancelada */
};

struct Acao acoes[100];
int total = 0;

/* Le um numero inteiro. Se o usuario nao digitar um numero, devolve -1 */
int lerNumero(char mensagem[]) {
    char linha[30];
    int numero, i, achouEnter = 0, c;

    printf("%s", mensagem);
    fgets(linha, 30, stdin);

    /* se a linha era maior que o espaco, joga fora o que sobrou */
    for (i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '\n') {
            achouEnter = 1;
        }
    }
    if (achouEnter == 0) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (sscanf(linha, "%d", &numero) != 1) {
        return -1;
    }
    return numero;
}

/* Le um texto (aceita espacos) e nao deixa o campo ficar vazio */
void lerTexto(char mensagem[], char texto[], int tamanho) {
    int i, achouEnter, c;

    do {
        printf("%s", mensagem);
        fgets(texto, tamanho, stdin);

        /* tira o Enter que o fgets guarda no final */
        achouEnter = 0;
        for (i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == '\n') {
                texto[i] = '\0';
                achouEnter = 1;
            }
        }

        /* se o texto era maior que o espaco, joga fora o que sobrou */
        if (achouEnter == 0) {
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }

        if (texto[0] == '\0') {
            printf("Digite o valor do campo pedido.\n"); /* Conforme a tabela */
        }
    } while (texto[0] == '\0');
}

/* Procura o codigo no vetor. Devolve a posicao ou -1 se nao achar */
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
    printf("Previstos: %d\n", acoes[i].qtdPrevista);
    printf("Efetivos: %d\n", acoes[i].qtdEfetiva);

    if (acoes[i].situacao == 1) {
        printf("Situacao: Planejada\n");
    }
    if (acoes[i].situacao == 2) {
        printf("Situacao: Realizada\n");
    }
    if (acoes[i].situacao == 3) {
        printf("Situacao: Cancelada\n");
    }
}

void cadastrar() {
    int codigo;

    if (total == 100) {
        printf("Nao e possivel cadastrar mais acoes nesta execucao.\n"); /* Conforme a tabela */
        return;
    }

    codigo = lerNumero("Codigo: ");
    while (codigo <= 0 || buscar(codigo) != -1) {
        if (codigo <= 0) {
            printf("Digite um numero igual ou maior que zero.\n");
        } else {
            printf("Informe outro codigo.\n"); /* Conforme a tabela */
        }
        codigo = lerNumero("Codigo: ");
    }
    acoes[total].codigo = codigo;

    lerTexto("Escola: ", acoes[total].escola, 50);
    lerTexto("Tema: ", acoes[total].tema, 50);
    lerTexto("Data (dd/mm/aaaa): ", acoes[total].data, 15);
    lerTexto("Publico-alvo: ", acoes[total].publico, 50);
    lerTexto("Responsavel: ", acoes[total].responsavel, 50);

    acoes[total].qtdPrevista = lerNumero("Quantidade prevista: ");
    while (acoes[total].qtdPrevista <= 0) {
        printf("Digite um numero igual ou maior que zero.\n"); /* Conforme a tabela */
        acoes[total].qtdPrevista = lerNumero("Quantidade prevista: ");
    }

    acoes[total].situacao = 1;
    acoes[total].qtdEfetiva = 0;
    total++;

    printf("Acao cadastrada com sucesso!\n");
}

void listar() {
    int i;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }
    for (i = 0; i < total; i++) {
        mostrar(i);
    }
}

void pesquisar() {
    int codigo, pos;

    codigo = lerNumero("Codigo: ");
    pos = buscar(codigo);

    if (pos == -1) {
        printf("Confira o codigo na opcao 2 (Listar) e tente de novo.\n"); /* Conforme a tabela */
    } else {
        mostrar(pos);
    }
}

void atualizar() {
    int codigo, pos, nova;

    codigo = lerNumero("Codigo: ");
    pos = buscar(codigo);

    if (pos == -1) {
        printf("Confira o codigo na opcao 2 (Listar) e tente de novo.\n"); /* Conforme a tabela */
        return;
    }

    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");

    nova = lerNumero("Nova situacao: ");
    while (nova < 1 || nova > 3) {
        printf("Escolha um numero que aparece no menu.\n"); /* Conforme a tabela */
        nova = lerNumero("Nova situacao: ");
    }

    acoes[pos].situacao = nova;
    acoes[pos].qtdEfetiva = 0;

    if (nova == 2) {
        acoes[pos].qtdEfetiva = lerNumero("Quantidade efetiva: ");
        while (acoes[pos].qtdEfetiva < 0) {
            printf("Digite um numero igual ou maior que zero.\n"); /* Conforme a tabela */
            acoes[pos].qtdEfetiva = lerNumero("Quantidade efetiva: ");
        }
    }

    printf("Situacao atualizada!\n");
}

void resumo() {
    int i;
    int planejadas = 0, realizadas = 0, canceladas = 0;
    int previstos = 0, efetivos = 0;

    for (i = 0; i < total; i++) {
        previstos = previstos + acoes[i].qtdPrevista;
        efetivos = efetivos + acoes[i].qtdEfetiva;

        if (acoes[i].situacao == 1) {
            planejadas++;
        }
        if (acoes[i].situacao == 2) {
            realizadas++;
        }
        if (acoes[i].situacao == 3) {
            canceladas++;
        }
    }

    printf("\n--- RESUMO GERAL ---\n");
    printf("Total de acoes: %d\n", total);
    printf("Planejadas: %d\n", planejadas);
    printf("Realizadas: %d\n", realizadas);
    printf("Canceladas: %d\n", canceladas);
    printf("Total previsto: %d\n", previstos);
    printf("Total efetivo: %d\n", efetivos);
}

int main() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Acao\n");
        printf("2 - Listar Acoes\n");
        printf("3 - Pesquisar Acao\n");
        printf("4 - Atualizar Situacao\n");
        printf("5 - Resumo Geral\n");
        printf("0 - Sair\n");
        opcao = lerNumero("Opcao: ");

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
            printf("Escolha um numero que aparece no menu.\n"); /* Conforme a tabela */
        }
    }

    return 0;
}
