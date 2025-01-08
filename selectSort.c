void selecao_direta(int *vetor, int tamanho) {
  int i, j, menor, aux;

  for (i = 0; i < tamanho - 1; ++i) {
    menor = i;
    
    for (j = i + 1; j < tamanho; ++j) {
        if (vetor[j] < vetor[menor])
            menor = j;
    }

    aux = vetor[i];
    vetor[i] = vetor[menor];
    vetor[menor] = aux;
    }
}

int main() {
    return 0;
}