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

void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}

int main() {
    int *vetor = (int *)malloc(TAMANHO * sizeof(int));
    if (!vetor) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    gerarCrescente(vetor, TAMANHO);
    medirTempo(mergeSort, vetor, TAMANHO);

    gerarDecrescente(vetor, TAMANHO);
    medirTempo(mergeSort, vetor, TAMANHO);

    gerarAleatorio(vetor, TAMANHO);
    medirTempo(mergeSort, vetor, TAMANHO);

    free(vetor);
    return 0;
}