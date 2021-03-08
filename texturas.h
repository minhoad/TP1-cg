#ifndef TEXTURAS_H
#define TEXTURAS_H
#include<SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<stdio.h>

GLuint id_textura_personagem_principal=0;
GLuint id_textura_fundo=0;
GLuint id_textura_inimigo=0;
GLuint id_textura_inimigo0=0; // INIMIGOS
GLuint id_textura_inimigo1=0; //
GLuint id_textura_inimigo2=0; //        DA 
GLuint id_textura_inimigo3=0; // 
GLuint id_textura_inimigo4=0; // 		FASE 3
GLuint id_textura_projetil=0; 
GLuint id_pause=0;
GLuint id_textura_projetil_inimigo=0;
GLuint id_textura_cabecanaruto = 0;
GLuint id_textura_vidaNaruto = 0;
GLuint id_textura_sapin = 0;
GLuint id_textura_nome1=0;
GLuint id_textura_nome2=0;
GLuint id_textura_nome3=0;
GLuint id_textura_nome4=0;
GLuint id_textura_nome5=0;
GLuint id_texturas = 0;
GLuint id_textura_nomeBoss = 0;
GLuint id_vidaBoss = 0;
GLuint id_textura_menu = 0;
GLuint id_textura_menu_jogar = 0;
GLuint id_textura_menu_creditos = 0;
GLuint id_textura_menu_pontuacaomax = 0;
GLuint id_textura_menu_sair = 0;
GLuint id_textura_creditos = 0;
GLuint id_textura_pontuacao_maxima = 0;
GLuint id_textura_vida3fase =0;

GLuint id_textura_lose = 0;
GLuint id_textura_win = 0;
GLuint id_textura_numeros = 0;
int contador_vezes_carrega_textura=0;
int contador_de_texturas_inimigos =0;


GLuint carregaTextura(const char* arquivo){
    GLuint id_textura = SOIL_load_OGL_texture(
                                arquivo,
                                SOIL_LOAD_AUTO,
                                SOIL_CREATE_NEW_ID,
                                SOIL_FLAG_INVERT_Y
                                );                                                                                        
    if(id_textura == 0){
        printf("Erro SOIL: %s", SOIL_last_result());
    }

    return id_textura;
}


void defineTexturas(int fase){
 
    switch(fase){
        case 0:
            if(contador_vezes_carrega_textura==0){
                id_textura_menu = carregaTextura("menu.png");
                id_textura_menu_jogar = carregaTextura("menu_jogar.png");
                id_textura_menu_creditos = carregaTextura("menu_creditos.png");
                id_textura_menu_pontuacaomax = carregaTextura("menu_pontuacao.png"); 
                id_textura_menu_sair = carregaTextura("menu_sair.png");
                id_textura_creditos = carregaTextura("credito.png");
                id_textura_pontuacao_maxima = carregaTextura("highscore.png");
                id_textura_numeros = carregaTextura("numeros_pixel.png");
                id_textura_win = carregaTextura("win.png");
                id_textura_lose = carregaTextura("gameover.png");
                id_textura_sapin = carregaTextura("sprites_naruto_sapo.png");
                contador_vezes_carrega_textura++;
            }
            break;    
        case 1:
            if(contador_vezes_carrega_textura==1){
            	id_textura_cabecanaruto = carregaTextura("cabecita_naruto.png");
            	id_textura_vidaNaruto = carregaTextura("vidaBoss.png");
                id_textura_personagem_principal = carregaTextura("unnamed.png");
                id_textura_inimigo = carregaTextura("kakashi_intro.png");
                id_textura_fundo = carregaTextura("cenario.png");
                id_pause = carregaTextura("pausescreen.png");
                id_textura_projetil = carregaTextura("shuriken.png");
                id_textura_projetil_inimigo= carregaTextura("kunai.png");
                contador_vezes_carrega_textura++;
            }
            break;
        case 2:
            if(contador_vezes_carrega_textura==2){
                id_textura_fundo = carregaTextura("folha.png");
                id_textura_inimigo = carregaTextura("zetsu.png");               
                contador_vezes_carrega_textura++;
            }            
            break;
        case 3:
            if(contador_vezes_carrega_textura==3){
            	 //id_textura_inimigo =0;
                 id_textura_fundo = carregaTextura("fundo3.png"); 
              	 id_textura_inimigo0 = carregaTextura("hidan.png");  
              	 id_textura_inimigo1 = carregaTextura("deidara.png"); 
              	 id_textura_inimigo2 = carregaTextura("pain1.png"); 
              	 id_textura_inimigo3 = carregaTextura("kisame.png"); 
              	 id_textura_inimigo4 = carregaTextura("sasore.png"); 
                 id_textura_nome1 = carregaTextura("nome_deidara.png");
                 id_textura_nome2 = carregaTextura("nome_hidan.png");
                 id_textura_nome3 = carregaTextura("nome_pain.png");
                 id_textura_nome4 = carregaTextura("nome_kisame.png");
                 id_textura_nome5 = carregaTextura("nome_sasore.png");
                 id_textura_vida3fase = carregaTextura("vida_3fase.png");
                 contador_vezes_carrega_textura++;
            }
            break;
        case 4:
            if(contador_vezes_carrega_textura==4){
            	id_vidaBoss = carregaTextura("vidaBoss.png");
            	id_textura_nomeBoss = carregaTextura("nome_tobi.png");
                id_textura_fundo = carregaTextura("fundo4.png"); 
                id_textura_inimigo = carregaTextura("tobi_sprite.png");  
                contador_vezes_carrega_textura++;
            }
        default:
            break;
    }
}

 
#endif    
