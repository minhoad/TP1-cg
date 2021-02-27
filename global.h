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
}formacao;

int cont=0;

// 3 shurikens; atirar mais rapido; vara ; em area*/
