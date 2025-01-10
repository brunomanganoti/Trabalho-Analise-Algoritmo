#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 30000  // Tamanho do vetor

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

void medirTempo(void (*algoritmo)(int *, int, int), int *vetor, int tamanho) {
    clock_t inicio = clock();
    algoritmo(vetor, 0, tamanho - 1);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%.4f segundos\n", tempo);
}

void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int particiona(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            troca(&array[i], &array[j]);
        }
    }

    troca(&array[i + 1], &array[high]);
    return i + 1;
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = particiona(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main() {
    int *vetor = (int *)malloc(TAMANHO * sizeof(int));
    if (!vetor) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    gerarCrescente(vetor, TAMANHO);
    medirTempo(quickSort, vetor, TAMANHO);

    gerarDecrescente(vetor, TAMANHO);
    medirTempo(quickSort, vetor, TAMANHO);

    gerarAleatorio(vetor, TAMANHO);
    medirTempo(quickSort, vetor, TAMANHO);

    free(vetor);
    return 0;
}
