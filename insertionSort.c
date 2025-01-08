#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
        vetor[i] = rand() % 100000;  // Números entre 0 e 99.999
    }
}

void medirTempo(void (*algoritmo)(int *, int), int *vetor, int tamanho) {
    clock_t inicio = clock();
    algoritmo(vetor, tamanho);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%.4f segundos\n", tempo);
}


void insertionSort(int vetor[], int tamanho) {
	for (int i = 1; i < tamanho; i++) { 
		
		int j = i;
	
		while (j > 0 && vetor[j] < vetor[j-1]) {
			int aux = vetor[j];
			vetor[j] = vetor[j - 1];
			vetor[j - 1] = aux;
			j -= 1;
		}
	}	
}

#define TAMANHO 100000  // Tamanho do vetor

int main() {
    int *vetor = (int *)malloc(TAMANHO * sizeof(int));
    if (!vetor) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    gerarCrescente(vetor, TAMANHO);
    medirTempo(insertionSort, vetor, TAMANHO);

    gerarDecrescente(vetor, TAMANHO);
    medirTempo(insertionSort, vetor, TAMANHO);

    gerarAleatorio(vetor, TAMANHO);
    medirTempo(insertionSort, vetor, TAMANHO);

    free(vetor);
    return 0;
}