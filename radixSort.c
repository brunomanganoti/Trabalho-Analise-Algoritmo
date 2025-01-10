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

int obterMaior(int array[], int n) {
    int maior = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > maior) {
            maior = array[i];
        }
    }
    return maior;
}

void contar(int array[], int n, int exp) {
    int *saida = (int *)malloc(n * sizeof(int));
    int contagem[10] = {0};

    for (int i = 0; i < n; i++) {
        contagem[(array[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        contagem[i] += contagem[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        saida[contagem[(array[i] / exp) % 10] - 1] = array[i];
        contagem[(array[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        array[i] = saida[i];
    }

    free(saida);
}

void radixSort(int array[], int n) {
    int maior = obterMaior(array, n);

    for (int exp = 1; maior / exp > 0; exp *= 10) {
        contar(array, n, exp);
    }
}

int main() {
    int *vetor = (int *)malloc(TAMANHO * sizeof(int));
    if (!vetor) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    gerarCrescente(vetor, TAMANHO);
    medirTempo(radixSort, vetor, TAMANHO);

    gerarDecrescente(vetor, TAMANHO);
    medirTempo(radixSort, vetor, TAMANHO);

    gerarAleatorio(vetor, TAMANHO);
    medirTempo(radixSort, vetor, TAMANHO);

    free(vetor);
    return 0;
}