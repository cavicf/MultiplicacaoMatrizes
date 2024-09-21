// Trabalho de Multiplicação de Matrizes - Camily Victal Finamor e Pedro Luiz de Moraes Ferreira
//-----------------------------------------------------------------------------------------------
//OBSERVAÇÕES:
//Professor, para uma melhor visualização de nossos comentários, recomendamos que use o word wrap
//Decidimos utilizar funções para a maior parte das nossas operações com o objetivo de deixar nosso código mais limpo e de mais fácil entendimento. Também  decidimos utilizar dos comentários para criar "sessões" como esta das observações, para ficar mais fácil pro professor corrigir e ver onde está cada coisa e também para nós não nos perdermos enquanto fazemos o trabalho
//-----------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

// STRUCT:
//Aqui vamos definir uma struct pros pixels, pois todas as matrizes vão utilizar de 3 pixels 
typedef struct pixel pixel;
struct pixel{
    int px1;
    int px2;
    int px3;
};

//--------------------------------------------------------------------------------------------
// ASSINATURAS DAS FUNÇÕES:
//Aprendemos com o professor Olmes que é melhor e mais organizado pro código colocar as assinaturas das funções antes do main e implementar elas depois do main, então fizemos assim
//Estas são as assinaturas das funções que fizemos para nosso trabalho
pixel **criar_matriz(int n);
pixel **criar_mresultado(int n);
void multiplicar_matriz(pixel **imagem, pixel **filtro, pixel **resultado, int n);
void imprimir_resultado(pixel **resultado, char *formato, int n, int escala);
void liberar_memoria(pixel **matriz, int n, int i);

//--------------------------------------------------------------------------------------------
//MAIN:
int main(){
//Aqui vamos criar e ler os 3 primeiros dados de entrada padrão da imagem PPM
    char formato[3];
    int n;
    int escala;
    scanf("%s", formato);
    scanf("%d %d", &n, &n);
    scanf("%d", &escala);
    

//Agora vamos criar as matrizes através da função que vai alocar essas matrizes dinamicamente e preencher elas, por ser matriz alocada temos que utilizar o conceito de ponteiro de ponterio
    pixel **imagem = NULL;
    pixel **filtro = NULL;
    imagem = criar_matriz(n);
    filtro = criar_matriz(n);
    
// a matriz do resultado tivemos que alocar em uma função separada pois ela ñão vai ser preenchida como as outras
    pixel **resultado = criar_mresultado(n);
 
// Agora aqui vamos chamar a nossa função que vai fazer a multiplicação das matrizes e guardar as respostas na matriz do resultado
    multiplicar_matriz(imagem, filtro, resultado, n);

// Agora aqui vamos chamar a nossa função que vai imprimir os dados padrão ppm e a matriz do resultado
    imprimir_resultado(resultado, formato, n, escala);

//Aqui é a chamada da função que vai liberar toda a memória alocada dinamicamente, fizemos ela de forma recursiva
    liberar_memoria(imagem, n, 0);
    liberar_memoria(filtro, n, 0);
    liberar_memoria(resultado, n, 0);
    return 0;
}

//----------------------------------------------------------------------------------------------
//CRIAÇÃO DAS FUNÇÕES
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

//Aqui criamos a função que vai multiplicar as matrizes 
void multiplicar_matriz(pixel **imagem, pixel **filtro, pixel **resultado, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            resultado[i][j].px1 = 0;
            resultado[i][j].px2 = 0;
            resultado[i][j].px3 = 0;
            for(int k=0; k<n; k++){
                resultado[i][j].px1 += imagem[i][k].px1 * filtro[k][j].px1;
                resultado[i][j].px2 += imagem[i][k].px2 * filtro[k][j].px2;
                resultado[i][j].px3 += imagem[i][k].px3 * filtro[k][j].px3;
            }
        }
    }
}

//Aqui é crição da função que imprime o resultado final da multiplicação
void imprimir_resultado(pixel **resultado, char *formato, int n, int escala){
    printf("%s\n", formato);
    printf("%d %d\n", n, n);
    printf("%d\n", escala);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d %d %d ", resultado[i][j].px1, resultado[i][j].px2, resultado[i][j].px3);
        }
        printf("\n");
    }
}

//Aqui criamos a função para liberar a memória alocada das matrizes, fizemos ela de forma recursiva
void liberar_memoria(pixel **matriz, int n, int i)
{
    //no nosso caso base, o indice começa no 0 e quando for igual ao valor da linha ele libera a matriz geral
    if(i == n)
    {
        free(matriz);
        return;
    }
    //aqui libera linha por linha
    free(matriz[i]);
    //utilizando a recursividade para liber todas as linhas
    liberar_memoria(matriz, n, i + 1);
}