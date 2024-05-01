#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define POPULACAO 5
#define N_CIDADES 10 // modificar populacaoInicial()

typedef struct cidade
{
    char nome[30];
    double cordenadaX;
    double cordenadaY;
} cidade;

typedef struct cromossomo
{
    double custo; //QUANTO MENOR MELHOR
    cidade cidades[N_CIDADES];
} cromossomo;

//funções principais
cromossomo *populacaoInicial();
void avaliar(cromossomo[]);

//funções auxiliares
void shuffle(int[], int);
void imprimirPopulacao(cromossomo[]);
double distancia(cidade, cidade);

int main(int argc, char const *argv[])
{
    cromossomo *populacao = populacaoInicial();
    avaliar(populacao);

    //Começo das iterações...




    imprimirPopulacao(populacao);
    free(populacao);
    return 0;
}

//Função de avaliação
void avaliar(cromossomo populacao[]) {
    int j;

    for (size_t i = 0; i < POPULACAO; i++)
    {
        double distanciaTotal = 0;

        for ( j = 0; j < N_CIDADES -1; j++)
        {
            distanciaTotal += distancia(populacao[i].cidades[j], populacao[i].cidades[j + 1]);
        }

        distanciaTotal += distancia(populacao[i].cidades[0], populacao[i].cidades[j + 1]);//Distancia da ultima cidade até a inicial
        populacao[i].custo = distanciaTotal;
    }
    
}

//Calcula distancia entre duas cidades
double distancia(cidade c1, cidade c2)
{
    double dist, cordX, cordY;
    cordX = c2.cordenadaX - c1.cordenadaX;
    cordY = c2.cordenadaY - c1.cordenadaY;
    dist = sqrt(pow(cordX, 2) + pow(cordY, 2));
    return dist;
}

void imprimirPopulacao(cromossomo populacao[])
{
    for (size_t i = 0; i < POPULACAO; i++)
    {
        printf("Cromossomo %d: [", i + 1);

        for (size_t j = 0; j < N_CIDADES; j++)
        {
            printf("%s, ", populacao[i].cidades[j].nome);
        }
        printf("\b\b] Custo: %f\n", populacao[i].custo);
    }
}

cromossomo *populacaoInicial()
{
    cromossomo *cromossomos = (cromossomo *)malloc(POPULACAO * sizeof(cromossomo));
    srand(time(NULL));

    // Definindo cidades {nome, x, y}
    cidade cidades[] = {
        {"Palmas", 200, 45},
        {"Curitiba", 300, 234},
        {"Sergipe", 450, 230},
        {"Alagoas", 235, 500},
        {"Manaus", -200, 25},
        {"Joao Pessoa", 20, 30},
        {"Goiania", 10, 100},
        {"Maroba", 324, 423},
        {"Guarai", 10, 100},
        {"Mato Grosso", -120, -400}};

    // Array auxiliar para ordernar as cidades
    int ordemDasCidades[N_CIDADES];
    for (size_t i = 0; i < N_CIDADES; i++)
    {
        ordemDasCidades[i] = i;
    }

    // Ordena as cidades de maneira aleatória
    for (size_t i = 0; i < POPULACAO; i++)
    {
        shuffle(ordemDasCidades, N_CIDADES);
        for (size_t j = 0; j < N_CIDADES; j++)
        {
            cromossomos[i].cidades[j] = cidades[ordemDasCidades[j]];
        }
    }

    return cromossomos;
}

//embaralha aleatoriamente os elementos do vetor
void shuffle(int arr[], int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}