#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define qtdCidades 5 // Define a quantidade de cidades

// Estrutura que representa um indivíduo (um tour no problema do caixeiro-viajante)
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

// Função para aplicar crossover e gerar dois filhos a partir de dois pais
void crossover(individuo pai1, individuo pai2, individuo *filho1, individuo *filho2) {
    // Marca cidades usadas para evitar duplicatas
    bool usado[qtdCidades];
    for (int i = 0; i < qtdCidades; i++) {
        usado[i] = false; // Inicializa todas as cidades como não usadas
    }

    // Seleciona pontos de corte aleatórios para o crossover
    int pontoCorte1 = rand() % qtdCidades; // Primeiro ponto de corte
    int pontoCorte2 = rand() % qtdCidades; // Segundo ponto de corte

    // seguinte com os cortes eu fiz assim eu peguei o meio entre o corte 1 e o corte 2 e coloquei no filho
    // ai depois eu prenchi o restante do filho com os elementos que tão faltando so que usando a ordem do pai que eu não usei o corte

    // Garante que pontoCorte1 seja menor que pontoCorte2
    if (pontoCorte1 > pontoCorte2) {
        int temp = pontoCorte1;
        pontoCorte1 = pontoCorte2;
        pontoCorte2 = temp;
    }

    // Copia o segmento entre os pontos de corte do pai1 para o filho1
    for (int i = pontoCorte1; i <= pontoCorte2; i++) {
        filho1->cidades[i] = pai1.cidades[i]; // Copia a parte do pai1
        usado[pai1.cidades[i]] = true; // Marca a cidade como usada
    }

    // Preenche o restante do filho1 com elementos do pai2, mantendo a ordem
    int j = (pontoCorte2 + 1) % qtdCidades; // Define a posição inicial
    for (int i = 0; i < qtdCidades; i++) {
        int cidade = pai2.cidades[i];
        if (!usado[cidade]) { // Se a cidade não foi usada
            filho1->cidades[j] = cidade; // Adiciona ao filho1
            j = (j + 1) % qtdCidades; // Avança para a próxima posição
        }
    }

    // Reinicia o array 'usado' para o segundo filho
    for (int i = 0; i < qtdCidades; i++) {
        usado[i] = false; // Marca todas as cidades como não usadas
    }

    // Copia o segmento entre os pontos de corte do pai2 para o filho2
    for (int i = pontoCorte1; i <= pontoCorte2; i++) {
        filho2->cidades[i] = pai2.cidades[i]; // Copia o segmento do pai2
        usado[pai2.cidades[i]] = true; // Marca a cidade como usada
    }

    // Preenche o restante do filho2 com elementos do pai1, mantendo a ordem
    j = (pontoCorte2 + 1) % qtdCidades; // Define a posição inicial
    for (int i = 0; i < qtdCidades; i++) {
        int cidade = pai1.cidades[i];
        if (!usado[cidade]) { // Se a cidade não foi usada
            filho2->cidades[j] = cidade; // Adiciona ao filho2
            j = (j + 1) % qtdCidades; // Avança para a próxima posição
        }
    }
}

// Função principal para demonstrar a aplicação do crossover
int main() {
    // Define dois pais com tours iniciais
    individuo pai1 = { { 0, 1, 2, 3, 4 }, 0 };
    individuo pai2 = { { 4, 3, 2, 1, 0 }, 0 };

    // Define dois filhos para serem gerados a partir do crossover
    individuo filho1 = { { 0, 0, 0, 0, 0 }, 0 };
    individuo filho2 = { { 0, 0, 0, 0, 0 }, 0 };

    // Chama a função crossover para gerar dois filhos a partir dos pais
    crossover(pai1, pai2, &filho1, &filho2);

    // Imprime os pais e os filhos para verificar o resultado
    printf("Pai 1: ");
    imprimeTour(pai1);

    printf("Pai 2: ");
    imprimeTour(pai2);

    printf("Filho 1: ");
    imprimeTour(filho1);

    printf("Filho 2: ");
    imprimeTour(filho2);

    return 0;
}
