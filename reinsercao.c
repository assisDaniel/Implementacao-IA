#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define qtdCidades 5 // Define a quantidade de cidades

// Estrutura que representa um indivíduo (um tour no problema do
// caixeiro-viajante)
typedef struct {
  int cidades[qtdCidades]; // Array que representa o tour
  int custo;               // Custo total do tour (não utilizado neste exemplo)
} individuo;

// Função para imprimir um tour
void imprimeTour(individuo tour) {
  for (int i = 0; i < qtdCidades; i++) {
    printf("%d ", tour.cidades[i]);
  }
  printf("\n");
}

// Função para reinserir os melhores pais (elitismo)
void elitismo(individuo populacao[], individuo novaPopulacao[], int n) {
  // Ordena a população atual pelos custos
  for (int i = 0; i < qtdCidades; i++) {
    for (int j = i + 1; j < qtdCidades; j++) {
      if (populacao[j].custo < populacao[i].custo) {
        individuo temp = populacao[i];
        populacao[i] = populacao[j];
        populacao[j] = temp;
      }
    }
  }

  // Copia os n melhores indivíduos para a nova população
  for (int i = 0; i < n; i++) {
    novaPopulacao[i] = populacao[i];
  }
}

int main() {
  // Define a população inicial
  individuo populacao[] = {{{0, 1, 2, 3, 4}, 5},
                           {{4, 3, 2, 1, 0}, 8},
                           {{2, 0, 3, 4, 1}, 9},
                           {{3, 4, 1, 0, 2}, 10},
                           {{1, 2, 3, 4, 0}, 0}};

  // Define a nova população
  individuo novaPopulacao[qtdCidades];

  int n = 0;
  do {
    printf("Digite a quantidade de indivíduos que vão para a próxima geração "
           "(entre 1 e %d): ",
           qtdCidades);
    scanf("%d", &n);
    if (n <= 0 || n > qtdCidades) {
      printf("Quantidade inválida. Por favor, digite um valor entre 1 e %d.\n",
             qtdCidades);
    }
  } while (n <= 0 || n > qtdCidades);

  // Aplica o elitismo para manter os n melhores indivíduos
  elitismo(populacao, novaPopulacao, n);

  // Imprime a nova população
  printf("Nova Populacao (com Elitismo):\n");
  for (int i = 0; i < n; i++) {
    imprimeTour(novaPopulacao[i]);
  }

  return 0;
}
