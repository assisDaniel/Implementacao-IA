#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char nome[255];
    int aptidao;
}node;

int *roleta(int numeroDePais, node cidade[], int qtdCidades){
    //Somando as aptidões das cidades.
    double aptidaoTot=0;
    for(int i=0; i<qtdCidades; i++){
        aptidaoTot+= cidade[i].aptidao;
    }
//    printf("%lf", aptidaoTot);

    // Calculando os pesos da roleta.
    double porcentagens[qtdCidades];
    for(int i=0; i<qtdCidades; i++){
        porcentagens[i]= cidade[i].aptidao / aptidaoTot;
//        printf("%.2lf\n", porcentagens[i]);
    }

    // Gerando os pais.
    int *pais= (int*) calloc(numeroDePais, sizeof(int));
    for(int i=0; i<numeroDePais; i++) {
        double numeroAleatorio = rand() / (RAND_MAX + 1.0);
//        printf("Rand: %lf\n", numeroAleatorio);

        int cidadeEscolhida = 0;
        double acumulador = 0;
        while (numeroAleatorio > acumulador) {
            acumulador += porcentagens[cidadeEscolhida];
            cidadeEscolhida++;
        }
        pais[i]= cidadeEscolhida;
    }

    return pais;
}
int main(void){
    int qtdCidades= 5;
    node cidade[qtdCidades];


    cidade[0].aptidao= 1.0;
    cidade[1].aptidao= 3.0;
    cidade[2].aptidao= 4.0;
    cidade[3].aptidao= 6.0;
    cidade[4].aptidao= 8.0;

    int numeroPais= 2;
    int *pais= roleta(numeroPais, cidade, qtdCidades);
    for(int i=0; i<numeroPais; i++) printf("Pai %d: %d\n", i+1, pais[i]);
}