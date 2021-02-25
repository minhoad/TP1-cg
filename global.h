#include<stdbool.h>

typedef struct{
    int posX;
    int posY;
    int altura;
    int largura;
}Personagens; // criar personagens inimigos

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
}formacao;

int cont=0;

// 3 shurikens; atirar mais rapido; vara ; em area*/
