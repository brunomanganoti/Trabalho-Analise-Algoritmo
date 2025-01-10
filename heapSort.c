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

void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int array[], int n, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && array[esquerda] > array[maior]) {
        maior = esquerda;
    }

    if (direita < n && array[direita] > array[maior]) {
        maior = direita;
    }

    if (maior != i) {
        troca(&array[i], &array[maior]);
        heapify(array, n, maior);
    }
}

void heapSort(int array[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        troca(&array[0], &array[i]);
        heapify(array, i, 0);
    }
}

int main() {
    int *vetor = (int *)malloc(TAMANHO * sizeof(int));
    if (!vetor) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    gerarCrescente(vetor, TAMANHO);
    medirTempo(heapSort, vetor, TAMANHO);

    gerarDecrescente(vetor, TAMANHO);
    medirTempo(heapSort, vetor, TAMANHO);

    gerarAleatorio(vetor, TAMANHO);
    medirTempo(heapSort, vetor, TAMANHO);

    free(vetor);
    return 0;
}