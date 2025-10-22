#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Programa: WAR Estruturado - Fase de Ataque
    Objetivo: Implementar um sistema interativo de territórios com simulação de ataques.

    Funcionalidades:
    - Cadastro dinâmico de territórios usando ponteiros
    - Exibição dos territórios cadastrados
    - Função de ataque com simulação aleatória (dados)
    - Atualização de cores e tropas após o ataque
    - Liberação de memória ao final

    Autor: [Seu Nome]
    Data: [Data]
*/

// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ======= FUNÇÕES =======

// Função para cadastrar territórios dinamicamente
void cadastrarTerritorios(Territorio* mapa, int total) {
    printf("===== CADASTRO DE TERRITORIOS =====\n\n");
    for (int i = 0; i < total; i++) {
        printf("Territorio %d:\n", i + 1);
        fflush(stdin);

        printf("Nome: ");
        fgets((mapa + i)->nome, 30, stdin);
        (mapa + i)->nome[strcspn((mapa + i)->nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets((mapa + i)->cor, 10, stdin);
        (mapa + i)->cor[strcspn((mapa + i)->cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &((mapa + i)->tropas));
        getchar(); // limpa o buffer do scanf

        printf("------------------------------------\n");
    }
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n===== ESTADO ATUAL DOS TERRITORIOS =====\n\n");
    for (int i = 0; i < total; i++) {
        printf("(%d) %s | Cor: %s | Tropas: %d\n",
               i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("-----------------------------------------\n\n");
}

// Função que realiza o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n===== INICIO DO ATAQUE =====\n");
    printf("%s (%s) esta atacando %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // Rolagem de dados de 1 a 6
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Resultado da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: O atacante venceu!\n");

        // Atualiza o defensor com os dados do atacante
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // metade das tropas do atacante

        printf("%s agora pertence a %s!\n", defensor->nome, defensor->cor);
    } else {
        printf("Resultado: O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1; // o atacante perde uma tropa
    }

    printf("===== FIM DO ATAQUE =====\n\n");
}

// Função para liberar memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("Memoria liberada com sucesso!\n");
}

// ======= FUNÇÃO PRINCIPAL =======
int main() {
    srand(time(NULL)); // inicializa a aleatoriedade dos dados

    int total;
    printf("Informe o numero total de territorios: ");
    scanf("%d", &total);
    getchar(); // limpa o buffer

    // Alocação dinâmica de memória para os territórios
    Territorio* mapa = (Territorio*) calloc(total, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, total);
    exibirTerritorios(mapa, total);

    // Simulação de ataque
    int atacanteIdx, defensorIdx;
    printf("Escolha o territorio atacante (1 a %d): ", total);
    scanf("%d", &atacanteIdx);
    printf("Escolha o territorio defensor (1 a %d): ", total);
    scanf("%d", &defensorIdx);

    // Validação das escolhas
    if (atacanteIdx < 1 || atacanteIdx > total || defensorIdx < 1 || defensorIdx > total) {
        printf("Escolha invalida!\n");
    } else if (strcmp((mapa + atacanteIdx - 1)->cor, (mapa + defensorIdx - 1)->cor) == 0) {
        printf("Um territorio nao pode atacar outro da mesma cor!\n");
    } else {
        atacar((mapa + atacanteIdx - 1), (mapa + defensorIdx - 1));
    }

    // Exibe o estado final
    exibirTerritorios(mapa, total);

    // Libera memória
    liberarMemoria(mapa);

    return 0;
}
