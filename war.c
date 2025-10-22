#include <stdio.h>
#include <string.h>

/*
    Programa: Cadastro de Territórios
    Objetivo: Demonstrar o uso de structs em C para armazenar dados compostos.
    Autor: [Seu Nome]
    Data: [Data de Criação]

    Descrição:
    O programa permite cadastrar 5 territórios, informando:
    - Nome do território
    - Cor do exército
    - Quantidade de tropas

    Após o cadastro, todos os territórios são exibidos com formatação clara.
*/

// Definição da estrutura (struct) que representa um território
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
};

int main() {
    struct Territorio territorios[5]; // Vetor de 5 estruturas do tipo Territorio
    int i; // Variável para controle do loop

    printf("===== CADASTRO DE TERRITORIOS =====\n\n");

    // Laço para entrada de dados dos 5 territórios
    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);

        // Limpa o buffer do teclado antes de usar fgets (boa prática)
        fflush(stdin);

        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // remove o '\n'

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
        getchar(); // Consome o '\n' deixado pelo scanf
    }

    // Exibição dos dados cadastrados
    printf("===== LISTA DE TERRITORIOS CADASTRADOS =====\n\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("--------------------------------------\n");
    }

    return 0;
}
