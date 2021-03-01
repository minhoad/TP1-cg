#include<stdbool.h>

typedef struct{
    int posX;
    int posY;
    int altura;
    int largura;
}Auxiliar_de_criacao_de_obj; // criar personagens inimigos TROCAR DEPOIS PARA OBJETOS

typedef struct{
    int posX;
    int posY;
    int altura;
    int largura;
    int qtdvidas;
}Jogador;

typedef struct{
    //int velocidade_do_projetil; // settar as padrões 
    //int quantidade_de_projeteis;
    //int tamanho_do_projetil; 
    int posX;
    int posY;
    int largura;
    int altura; 
    bool atirar;   
}Arma;

typedef struct{
    int posX;
    int posY;
    int largura;
    int altura;
    bool vivo;
    int qtdvidas;
    bool dash; 
}formacao;

typedef struct{
    double vert1_x;
    double vert1_y;
    double vert2_x;
    double vert2_y;
    double vert3_x;
    double vert3_y;
    double vert4_x;
    double vert4_y;
    double frameAtual;
    double somador;
    double qtdAtual;
    double qtdTotalFrame;
    double contadorDeFrame;
    double velocidadeDoFrame;
}animacao;


int cont=0;

// 3 shurikens; atirar mais rapido; vara ; em area*/
