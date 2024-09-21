// Trabalho de Multiplicação de Matrizes - Camily e Pedro

#include <stdio.h>
#include <stdlib.h>

// STRUCTS
//Aqui vamos definir uma struct dos pixels, pois todas as matrizes vão utilizar de 3 pixels 
typedef struct pixel pixel;
struct pixel{
    int px1;
    int px2;
    int px3;
};

//-----------------------------------------------------------------------------

//FUNÇÕES
// Decidimos utilizar funções para a maior parte das operações com o objetivo de deixar nosso código mais limpo e de mais fácil entendimento

//Aqui fazemos a função pra criar as matrizes e preencher, elas devolvem o endereço de memória de onde a alocação foi feita
pixel **criar_matriz(int n){
    //alocamos a matrz
    pixel **matriz = (pixel**)malloc(n * sizeof(pixel*));
    if(matriz == NULL){
        printf("erro ao alocar");
        exit(1);
    }
    for(int i=0; i<n; i++){
        matriz[i] = (pixel *)malloc(n * sizeof(pixel));
        if(matriz[i] == NULL){
            printf("erro ao alocar");
            exit(1);
        }
    }
    
    //preenchendo ela
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d %d %d", &matriz[i][j].px1, &matriz[i][j].px2, &matriz[i][j].px3);
        }
    }
    return matriz;
}

//Aqui é a criação da função que aloca a matriz do resultado, ela também devolve um endereço para o local alocado na memória
pixel **criar_mresultado(int n){
    //alocamos a matrz
    pixel **matriz = (pixel**)malloc(n * sizeof(pixel*));
    if(matriz == NULL){
        printf("erro ao alocar");
        exit(1);
    }
    for(int i=0; i<n; i++){
        matriz[i] = (pixel *)malloc(n * sizeof(pixel));
        if(matriz[i] == NULL){
            printf("erro ao alocar");
            exit(1);
        }
    }
    return matriz;
}

/* Funcao para liberar a memoria das matrizes, ele libera linha por linha e quando chega na ultima ele
libera a matriz como um todo, que eh o que restou*/
void liberar_memoria(pixel **matriz, int n, int i)
{
    //caso base, o indice começa no 0 e quando for igual ao valor da linha ele libera a matriz geral
    if(i == n)
    {
        free(matriz);
        return;
    }
    //liberando linha por linha e cada pixel
    free(matriz[i]);
    //utilizando a recursividade para liber todas as linhas
    liberar_memoria(matriz, n, i + 1);
}

//-----------------------------------------------------------------------------
//MAIN
int main(){

//Aqui temos os 3 primeiros dados de entrada padrão da imagem PPM
    char formato[3];
    int n;
    int escala;
    scanf("%s", formato);
    scanf("%d %d", &n, &n);
    scanf("%d", &escala);
    

//Agora vamos criar as matrizes através da função que vai alocar essas matrizes dinamicamente e preencher, como a função devolve o endereço de memória de onde a matriz foi alocada, a chamada da função é feita com ponteiros para aponter para estes locais da memória
    pixel **imagem = NULL;
    pixel **filtro = NULL;

    imagem = criar_matriz(n);
    filtro = criar_matriz(n);
    
// a matriz do resultado tivemos que alocar em uma função separada pois ela n será preenchida como as outras
    //pixel **resultado = criar_mresultado(n);
    printf("1\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d %d %d ", imagem[i][j].px1, imagem[i][j].px2, imagem[i][j].px3);
        }
        printf("\n");
    }
    printf("\n");
    printf("2\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d %d %d ", filtro[i][j].px1, filtro[i][j].px2, filtro[i][j].px3);
        }
        printf("\n");
    }


    liberar_memoria(imagem, n, 0);
    liberar_memoria(filtro, n, 0);


    return 0;
}