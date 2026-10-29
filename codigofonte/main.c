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
        printf("Memoria cheia!\n");
        return;
    }

    printf("Codigo: ");
    scanf("%d", &codigo);
    while (buscar(codigo) != -1) {
        printf("Erro: codigo ja existe!\n");
        printf("Codigo: ");
        scanf("%d", &codigo);
    }
    acoes[total].codigo = codigo;

    /* O " %[^\n]" le a linha inteira, inclusive os espacos */
    printf("Escola: ");
    scanf(" %[^\n]", acoes[total].escola);
    printf("Tema: ");
    scanf(" %[^\n]", acoes[total].tema);
    printf("Data (dd/mm/aaaa): ");
    scanf(" %[^\n]", acoes[total].data);
    printf("Publico-alvo: ");
    scanf(" %[^\n]", acoes[total].publico);
    printf("Responsavel: ");
    scanf(" %[^\n]", acoes[total].responsavel);

    printf("Quantidade prevista: ");
    scanf("%d", &acoes[total].qtdPrevista);
    while (acoes[total].qtdPrevista <= 0) {
        printf("Erro: a quantidade deve ser maior que zero!\n");
        printf("Quantidade prevista: ");
        scanf("%d", &acoes[total].qtdPrevista);
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
    }
    for (i = 0; i < total; i++) {
        mostrar(i);
    }
}

void pesquisar() {
    int codigo, pos;

    printf("Codigo: ");
    scanf("%d", &codigo);
    pos = buscar(codigo);

    if (pos == -1) {
        printf("Acao nao encontrada!\n");
    } else {
        mostrar(pos);
    }
}

void atualizar() {
    int codigo, pos, nova;

    printf("Codigo: ");
    scanf("%d", &codigo);
    pos = buscar(codigo);

    if (pos == -1) {
        printf("Acao nao encontrada!\n");
        return;
    }

    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");
    printf("Nova situacao: ");
    scanf("%d", &nova);

    if (nova < 1 || nova > 3) {
        printf("Opcao invalida!\n");
        return;
    }

    acoes[pos].situacao = nova;
    acoes[pos].qtdEfetiva = 0;

    if (nova == 2) {
        printf("Quantidade efetiva: ");
        scanf("%d", &acoes[pos].qtdEfetiva);
        while (acoes[pos].qtdEfetiva < 0) {
            printf("Erro: nao pode ser negativa!\n");
            printf("Quantidade efetiva: ");
            scanf("%d", &acoes[pos].qtdEfetiva);
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
        printf("Opcao: ");
        scanf("%d", &opcao);

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
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}
