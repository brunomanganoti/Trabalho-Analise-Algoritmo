#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 100000  // Tamanho do vetor

void gerarCrescente(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i;
    }
}

void gerarDecrescente(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i;
    }
}

void gerarAleatorio(int *vetor, int tamanho) {
    srand(time(NULL));
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 100000;
    }
}

void medirTempo(void (*algoritmo)(int *, int), int *vetor, int tamanho) {
    clock_t inicio = clock();
    algoritmo(vetor, tamanho);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%.4f segundos\n", tempo);
}

void bubbleSort(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

int main() {
    int *vetor = (int *)malloc(TAMANHO * sizeof(int));
    if (!vetor) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    gerarCrescente(vetor, TAMANHO);
    medirTempo(bubbleSort, vetor, TAMANHO);

    gerarDecrescente(vetor, TAMANHO);
    medirTempo(bubbleSort, vetor, TAMANHO);

    gerarAleatorio(vetor, TAMANHO);
    medirTempo(bubbleSort, vetor, TAMANHO);

    free(vetor);
    return 0;
}