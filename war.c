#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Programa: WAR Estruturado - Missões Estratégicas
    Objetivo: Integrar cadastro de territórios, ataques e missões para cada jogador.

    Funcionalidades:
    - Cadastro dinâmico de territórios
    - Exibição do mapa
    - Ataques entre territórios com dados aleatórios
    - Missões estratégicas sorteadas e armazenadas dinamicamente
    - Verificação de vitória baseada na missão
    - Liberação de memória

    Autor: [Seu Nome]
    Data: [Data]
*/

// ======== Estrutura de Território ========
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ======== Funções ========

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
        getchar(); // limpa buffer

        printf("------------------------------------\n");
    }
}

// Exibe o estado atual dos territórios
void exibirMapa(Territorio* mapa, int total) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < total; i++) {
        printf("(%d) %s | Cor: %s | Tropas: %d\n",
               i + 1, (mapa + i)->nome, (mapa + i)->cor, (mapa + i)->tropas);
    }
    printf("---------------------------------\n\n");
}

// Função de ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) ataca %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d | Dado do defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        printf("%s agora pertence a %s com %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    } else {
        printf("O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}

// Função para sortear a missão de um jogador
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(*destino, missoes[sorteio]);
}

// Verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Implementação inicial simples: verifica se jogador conquistou todos os territórios de uma cor específica
    if (strstr(missao, "Eliminar todas as tropas da cor Vermelho") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp((mapa + i)->cor, "Vermelho") == 0) {
                return 0; // missão não cumprida
            }
        }
        return 1; // missão cumprida
    }

    // Outras verificações podem ser implementadas aqui
    return 0;
}

// Libera memória alocada dinamicamente
void liberarMemoria(Territorio* mapa, char* missaoJogador) {
    free(mapa);
    free(missaoJogador);
    printf("Memoria liberada com sucesso!\n");
}

// ======== Função principal ========
int main() {
    srand(time(NULL));

    int total;
    printf("Informe o numero total de territorios: ");
    scanf("%d", &total);
    getchar();

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*) calloc(total, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    // Cadastro de territórios
    cadastrarTerritorios(mapa, total);
    exibirMapa(mapa, total);

    // Vetor de missões
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor Vermelho",
        "Controlar 5 territorios",
        "Ter ao menos 10 tropas em um territorio",
        "Conquistar o territorio Chile"
    };
    int totalMissoes = 5;

    // Alocação dinâmica da missão do jogador
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    if (!missaoJogador) {
        printf("Erro de alocacao da missao!\n");
        free(mapa);
        return 1;
    }

    atribuirMissao(&missaoJogador, missoes, totalMissoes);
    printf("Missao do jogador: %s\n\n", missaoJogador);

    // Simulação de ataque simples
    int atacanteIdx, defensorIdx;
    printf("Escolha o territorio atacante (1 a %d): ", total);
    scanf("%d", &atacanteIdx);
    printf("Escolha o territorio defensor (1 a %d): ", total);
    scanf("%d", &defensorIdx);

    if (atacanteIdx < 1 || atacanteIdx > total || defensorIdx < 1 || defensorIdx > total) {
        printf("Escolha invalida!\n");
    } else if (strcmp((mapa + atacanteIdx - 1)->cor, (mapa + defensorIdx - 1)->cor) == 0) {
        printf("Nao pode atacar territorio da mesma cor!\n");
    } else {
        atacar((mapa + atacanteIdx - 1), (mapa + defensorIdx - 1));
    }

    exibirMapa(mapa, total);

    // Verificação de missão
    if (verificarMissao(missaoJogador, mapa, total)) {
        printf("Parabens! Missao cumprida!\n");
    } else {
        printf("Missao ainda nao cumprida.\n");
    }

    // Liberação de memória
    liberarMemoria(mapa, missaoJogador);

    return 0;
}
