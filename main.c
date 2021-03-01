#include<SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<stdlib.h>
#include<stdio.h>
#include"global.h"
#include<stdbool.h>
#include"texturas.h"
#include<time.h>
#include<stdlib.h>

void contador();
void gameloop(int tempo);
void reiniciar();
void setup();
int* projetilrandom_fase2();
void criaVetorInimigos();
void desenhaDashInimigo();
void relogio();

Jogador personagem_principal;

Auxiliar_de_criacao_de_obj inimigo_aux;// auxiliar da segunda fase p/criar os zetsu`s
Auxiliar_de_criacao_de_obj inimigo_aux_fase3; // auxiliar da segunda fase

Arma shuriken; // aliado
Arma kunai; // inimigo

//int contador_de_tiros;
//int maximo_de_tiros_na_tela_fase3 = 2;

formacao inimigo_primeira_fase; // PRIMEIRA FASE
formacao matriz_inimigos[3][10]; // SEGUNDA FASE
formacao vetor_de_inimigos[5]; // TERCEIRA FASE
formacao boss;

animacao kakashi;
animacao zetsu;
animacao naruto;
animacao attack_naruto;

bool pause = false;

bool pode_dar_dash = true;
bool flag = true; // trocar a direção movimento dos inimigos
int fase=1;

int descida_fase2; 

int tempo,tempo_limite;
//int descida_fase3 = 0;

//          IMPLEMENTAR
//int maximo_de_tiros_tela_fase2 = 2;         
//int contador_de_tiros_tela = 0;       

double frame_count = 0,initial_time, final_time, contador_fps=0; // para o contador de fps

void desenhaPersonagemPrincipal(){
    glEnable(GL_TEXTURE_2D);
    if(estado == 0){//naruto parado.
        if(naruto.frameAtual == 0){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                //printf("ok\n");
                naruto.vert1_x = 0.0;
                naruto.vert2_x = 1/naruto.qtdTotalFrame;
                naruto.vert3_x = 1/naruto.qtdTotalFrame;
                naruto.vert4_x = 0.0;

                naruto.vert1_y = 0.0;
                naruto.vert2_y = 0.0;
                naruto.vert3_y = 1.0;
                naruto.vert4_y = 1.0;
                 
        }
    
    
    }
    if(estado == 1){//naruto andando direita

        naruto.velocidadeDoFrame = 0.5;
        naruto.somador = 1/naruto.qtdTotalFrame;

        if(naruto.frameAtual >= naruto.contadorDeFrame && naruto.frameAtual != naruto.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                        //printf("okok\n");
                        naruto.vert1_x = 0.0 + naruto.somador * naruto.contadorDeFrame;
                        naruto.vert2_x = 1/naruto.qtdTotalFrame + naruto.somador * naruto.contadorDeFrame;
                        naruto.vert3_x = 1/naruto.qtdTotalFrame + naruto.somador* naruto.contadorDeFrame;
                        naruto.vert4_x = 0.0 + naruto.somador * naruto.contadorDeFrame;

                        naruto.vert1_y = 0.0;
                        naruto.vert2_y = 0.0;
                        naruto.vert3_y = 1.0;
                        naruto.vert4_y = 1.0;  

                        naruto.contadorDeFrame++;  
         }
            
                    if(naruto.frameAtual > naruto.qtdTotalFrame-12){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        naruto.frameAtual = 0;
                        naruto.contadorDeFrame =  0;
                        naruto.vert1_x = 0.0;
                        naruto.vert2_x = 1/naruto.qtdTotalFrame;
                        naruto.vert3_x = 1/naruto.qtdTotalFrame;
                        naruto.vert4_x = 0.0;
                        estado = 0;
                        
                     }
                naruto.frameAtual = naruto.frameAtual + naruto.velocidadeDoFrame;
    }
    if(estado == 2){//naruto andando esquerda

        naruto.velocidadeDoFrame = 0.5;
        naruto.somador = 1/naruto.qtdTotalFrame;

        if(naruto.frameAtual >= naruto.contadorDeFrame && naruto.frameAtual != naruto.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                        //printf("okok\n");
                        naruto.vert1_x = 0.0 + naruto.somador * naruto.contadorDeFrame;
                        naruto.vert2_x = 1/naruto.qtdTotalFrame + naruto.somador * naruto.contadorDeFrame;
                        naruto.vert3_x = 1/naruto.qtdTotalFrame + naruto.somador* naruto.contadorDeFrame;
                        naruto.vert4_x = 0.0 + naruto.somador * naruto.contadorDeFrame;

                        naruto.vert1_y = 0.0;
                        naruto.vert2_y = 0.0;
                        naruto.vert3_y = 1.0;
                        naruto.vert4_y = 1.0;  

                        naruto.contadorDeFrame++;  
         }
            
                    if(naruto.frameAtual > naruto.qtdTotalFrame-4){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        naruto.frameAtual = 0;
                        naruto.contadorDeFrame =  0;
                        naruto.vert1_x = 0.0;
                        naruto.vert2_x = 1/naruto.qtdTotalFrame;
                        naruto.vert3_x = 1/naruto.qtdTotalFrame;
                        naruto.vert4_x = 0.0;
                        estado = 0;
                        
                     }
                naruto.frameAtual = naruto.frameAtual + naruto.velocidadeDoFrame;
    }
    if(estado == 3){//naruto atacando
        naruto.velocidadeDoFrame = 0.3;
        naruto.somador = 1/naruto.qtdTotalFrame;
        if(naruto.frameAtual >= naruto.contadorDeFrame && naruto.frameAtual != naruto.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                        //printf("okok\n");
                        naruto.vert1_x = 0.0 + naruto.somador * naruto.contadorDeFrame;
                        naruto.vert2_x = 1/naruto.qtdTotalFrame + naruto.somador * naruto.contadorDeFrame;
                        naruto.vert3_x = 1/naruto.qtdTotalFrame + naruto.somador* naruto.contadorDeFrame;
                        naruto.vert4_x = 0.0 + naruto.somador * naruto.contadorDeFrame;

                        naruto.vert1_y = 0.0;
                        naruto.vert2_y = 0.0;
                        naruto.vert3_y = 1.0;
                        naruto.vert4_y = 1.0;  

                        naruto.contadorDeFrame++;  
                    }
            
                    if(naruto.frameAtual > naruto.qtdTotalFrame){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        naruto.frameAtual = 0;
                        naruto.contadorDeFrame =  0;
                        naruto.vert1_x = 0.0;
                        naruto.vert2_x = 1/naruto.qtdTotalFrame;
                        naruto.vert3_x = 1/naruto.qtdTotalFrame;
                        naruto.vert4_x = 0.0;   
                        estado = 0;
                        
                     }
            naruto.frameAtual = naruto.frameAtual + naruto.velocidadeDoFrame;

    }
    

    glBindTexture(GL_TEXTURE_2D, id_textura_personagem_principal);
    
    glPushMatrix();
    
    glTranslatef(personagem_principal.posX, personagem_principal.posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(naruto.vert1_x,naruto.vert1_y);
        glVertex2f(-personagem_principal.largura/2, -personagem_principal.altura/2);

        glTexCoord2f(naruto.vert2_x,naruto.vert2_y);
        glVertex2f(personagem_principal.largura/2, -personagem_principal.altura/2);
        
        glTexCoord2f(naruto.vert3_x,naruto.vert3_y);
        glVertex2f(personagem_principal.largura/2, personagem_principal.altura/2);

        glTexCoord2f(naruto.vert4_x,naruto.vert4_y);
        glVertex2f(-personagem_principal.largura/2, personagem_principal.altura/2);

     glEnd();
     glPopMatrix();
     glDisable(GL_TEXTURE_2D);
              
}

void desenhaInimigo(float posX,float posY,float largura,float altura){
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
    if(fase==1){
        if(kakashi.frameAtual >= kakashi.contadorDeFrame && kakashi.frameAtual != kakashi.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
            //printf("okok\n");
            kakashi.vert1_x = 0.0 + kakashi.somador * kakashi.contadorDeFrame;
            kakashi.vert2_x = 1/kakashi.qtdTotalFrame + kakashi.somador * kakashi.contadorDeFrame;
            kakashi.vert3_x = 1/kakashi.qtdTotalFrame + kakashi.somador* kakashi.contadorDeFrame;
            kakashi.vert4_x = 0.0 + kakashi.somador * kakashi.contadorDeFrame;

            kakashi.vert1_y = 0.0;
            kakashi.vert2_y = 0.0;
            kakashi.vert3_y = 1.0;
            kakashi.vert4_y = 1.0;  

            kakashi.somador = 1/kakashi.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
            kakashi.contadorDeFrame++;  
        }

        if(kakashi.frameAtual > kakashi.qtdTotalFrame){//volta para posicao inicial da imagem para fazer a animaçao dnv
            //printf("ok\n");
            kakashi.frameAtual = 0;
            kakashi.contadorDeFrame =  0;
            kakashi.vert1_x = 0.0;
            kakashi.vert2_x = 1/kakashi.qtdTotalFrame;
            kakashi.vert3_x = 1/kakashi.qtdTotalFrame;
            kakashi.vert4_x = 0.0;
            kakashi.somador = 1/kakashi.qtdTotalFrame;
         }

        kakashi.frameAtual = kakashi.frameAtual + kakashi.velocidadeDoFrame;   

        glBindTexture(GL_TEXTURE_2D, id_textura_inimigo);
    
        glPushMatrix();

        glTranslatef(posX, posY, 0);
    
        glBegin(GL_TRIANGLE_FAN);
                            
            glTexCoord2f(kakashi.vert1_x, kakashi.vert1_y); //
            glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

            glTexCoord2f(kakashi.vert2_x, kakashi.vert2_y); //
            glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
     
            glTexCoord2f(kakashi.vert3_x, kakashi.vert3_y); //
            glVertex3f( largura/2,  altura/2,0); // |     | // 15 , 20

            glTexCoord2f(kakashi.vert4_x, kakashi.vert4_y); //
            glVertex3f(-largura/2,  altura/2,0); // v1---v2 // -15, 20

    glEnd();
    
    glPopMatrix();
    }
    else if(fase==2){
        if(flag){
            
            if(zetsu.frameAtual >= zetsu.contadorDeFrame && zetsu.frameAtual != zetsu.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
            //printf("okok\n");
            //printf("|%f\n",zetsu.frameAtual);
            //printf("|%f|\n",zetsu.contadorDeFrame);
            
                zetsu.vert1_x = 0.0 + zetsu.somador * zetsu.contadorDeFrame;
                zetsu.vert2_x = 1/zetsu.qtdTotalFrame + zetsu.somador * zetsu.contadorDeFrame;
                zetsu.vert3_x = 1/zetsu.qtdTotalFrame + zetsu.somador* zetsu.contadorDeFrame;
                zetsu.vert4_x = 0.0 + zetsu.somador * zetsu.contadorDeFrame;

                zetsu.vert1_y = 0.0;
                zetsu.vert2_y = 0.0;
                zetsu.vert3_y = 1.0;
                zetsu.vert4_y = 1.0;  
                    
                //printf("%f\n", zetsu.vert1_x);
                //printf("%f\n", zetsu.vert2_x);

                zetsu.somador = 1/zetsu.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                zetsu.contadorDeFrame++;  
        }

        if(zetsu.frameAtual > zetsu.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
            //printf("ok\n");
            zetsu.frameAtual = 0;
            zetsu.contadorDeFrame =  0;
            zetsu.vert1_x = 0.0;
            zetsu.vert2_x = 1/zetsu.qtdTotalFrame;
            zetsu.vert3_x = 1/zetsu.qtdTotalFrame;
            zetsu.vert4_x = 0.0;
            zetsu.somador = 0;
         }

        zetsu.frameAtual = zetsu.frameAtual + zetsu.velocidadeDoFrame;
        
    }
          
    if(!flag){
            
            if(zetsu.frameAtual >= zetsu.contadorDeFrame && zetsu.frameAtual != zetsu.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
            //printf("okok\n");
            
            zetsu.vert1_x = 0.0 + zetsu.somador * zetsu.contadorDeFrame;
            zetsu.vert2_x = 1/zetsu.qtdTotalFrame + zetsu.somador * zetsu.contadorDeFrame;
            zetsu.vert3_x = 1/zetsu.qtdTotalFrame + zetsu.somador* zetsu.contadorDeFrame;
            zetsu.vert4_x = 0.0 + zetsu.somador * zetsu.contadorDeFrame;

            zetsu.vert1_y = 0.0;
            zetsu.vert2_y = 0.0;
            zetsu.vert3_y = 1.0;
            zetsu.vert4_y = 1.0;  

            zetsu.somador = 1/zetsu.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
            zetsu.contadorDeFrame++;  
        }

        if(zetsu.frameAtual > zetsu.qtdTotalFrame || zetsu.vert1_x < 1/zetsu.qtdTotalFrame * zetsu.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
            //printf("ok\n");
            zetsu.frameAtual = (zetsu.qtdTotalFrame/2)-1;
            zetsu.contadorDeFrame =  zetsu.qtdTotalFrame/2;
            zetsu.somador = 1/zetsu.qtdTotalFrame;
            zetsu.vert1_x = zetsu.somador * zetsu.contadorDeFrame;
            zetsu.vert2_x = 1/zetsu.qtdTotalFrame + zetsu.somador * zetsu.contadorDeFrame;
            zetsu.vert3_x = 1/zetsu.qtdTotalFrame + zetsu.somador * zetsu.contadorDeFrame;
            zetsu.vert4_x = zetsu.somador * zetsu.contadorDeFrame;
            
         }

        zetsu.frameAtual = zetsu.frameAtual + zetsu.velocidadeDoFrame;    
    }
 

        glBindTexture(GL_TEXTURE_2D, id_textura_inimigo);
    
        glPushMatrix();

        glTranslatef(posX, posY, 0);
    
        glBegin(GL_TRIANGLE_FAN);
                            
            glTexCoord2f(zetsu.vert1_x, zetsu.vert1_y); //
            glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

            glTexCoord2f(zetsu.vert2_x, zetsu.vert2_y); //
            glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
     
            glTexCoord2f(zetsu.vert3_x, zetsu.vert3_y); //
            glVertex3f( largura/2,  altura/2,0); // |     | // 15 , 20

            glTexCoord2f(zetsu.vert4_x, zetsu.vert4_y); //
            glVertex3f(-largura/2,  altura/2,0); // v1---v2 // -15, 20

        glEnd();
    
        glPopMatrix();


    }
    
    else if(fase == 3){
    	switch(contador_de_texturas_inimigos){
    		case 0:
    			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo0);
			break;
		case 1:
			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo1);
			break;
		case 2:
    			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo2);
			break;
		case 3:
			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo3);
			break;
		case 4:
			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo4);
			break;
		default:
			break;
    	}
        glPushMatrix();
    
        glTranslatef(posX, posY, 0);
    
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0,0);
            glVertex2f(-largura/2, -altura/2);

            glTexCoord2f(1,0);
            glVertex2f(largura/2, -altura/2);
            
            glTexCoord2f(1,1);
            glVertex2f(largura/2, altura/2);

            glTexCoord2f(0,1);
            glVertex2f(-largura/2, altura/2);

        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    else if(fase == 4){
        glBindTexture(GL_TEXTURE_2D, id_textura_inimigo);
        glPushMatrix();
        
        glTranslatef(posX, posY, 0);
        
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0,0);
            glVertex2f(-largura/2, -altura/2);

            glTexCoord2f(1,0);
            glVertex2f(largura/2, -altura/2);
            
            glTexCoord2f(1,1);
            glVertex2f(largura/2, altura/2);

            glTexCoord2f(0,1);
            glVertex2f(-largura/2, altura/2);

            glEnd();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
       }
}

/*void desenhaDashInimigo(int posX,int posY, int altura,int largura, int a){
    glColor3f(1,1,1);
    
    //glEnable(GL_TEXTURE_2D);

    switch(a){
    		case 0:
    			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo0);
			break;
		case 1:
			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo1);
			break;
		case 2:
    			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo2);
			break;
		case 3:
			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo3);
			break;
		case 4:
			glBindTexture(GL_TEXTURE_2D, id_textura_inimigo4);
			break;
		default:
			break;
    };
    glPushMatrix();
    
    glTranslatef(posX, posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);
        glVertex2f(-largura/2, -altura/2);

        glTexCoord2f(1,0);
        glVertex2f(largura/2, -altura/2);
        
        glTexCoord2f(1,1);
        glVertex2f(largura/2, altura/2);

        glTexCoord2f(0,1);
        glVertex2f(-largura/2, altura/2);

        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
       
}*/


void desenhaFundo(){
    
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id_textura_fundo);
    
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);
        glVertex2f(0, 0);

        glTexCoord2f(1,0);
        glVertex2f(100,0);
        
        glTexCoord2f(1,1);
        glVertex2f(100,100);

        glTexCoord2f(0,1);
        glVertex2f(0,100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void desenhaPause(){
    
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id_pause);
    
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);
        glVertex2f(0, 0);

        glTexCoord2f(1,0);
        glVertex2f(100,0);
        
        glTexCoord2f(1,1);
        glVertex2f(100,100);

        glTexCoord2f(0,1);
        glVertex2f(0,100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void desenhaProjetil(int x){
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
    if(x==1){
        
    if(attack_naruto.frameAtual >= attack_naruto.contadorDeFrame && attack_naruto.frameAtual != attack_naruto.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
            //printf("okok\n");
            
            attack_naruto.vert1_x = 0.0 + attack_naruto.somador * attack_naruto.contadorDeFrame;
            attack_naruto.vert2_x = 1/attack_naruto.qtdTotalFrame + attack_naruto.somador * attack_naruto.contadorDeFrame;
            attack_naruto.vert3_x = 1/attack_naruto.qtdTotalFrame + attack_naruto.somador* attack_naruto.contadorDeFrame;
            attack_naruto.vert4_x = 0.0 + attack_naruto.somador * attack_naruto.contadorDeFrame;

            attack_naruto.vert1_y = 0.0;
            attack_naruto.vert2_y = 0.0;
            attack_naruto.vert3_y = 1.0;
            attack_naruto.vert4_y = 1.0;  

            attack_naruto.somador = 1/attack_naruto.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
            attack_naruto.contadorDeFrame++;  
        }

        if(attack_naruto.frameAtual > attack_naruto.qtdTotalFrame){//volta para posicao inicial da imagem para fazer a animaçao dnv
            //printf("ok\n");
            attack_naruto.frameAtual = 0;
            attack_naruto.contadorDeFrame =  0;
            attack_naruto.vert1_x = 0.0;
            attack_naruto.vert2_x = 1/attack_naruto.qtdTotalFrame;
            attack_naruto.vert3_x = 1/attack_naruto.qtdTotalFrame;
            attack_naruto.vert4_x = 0.0;
            attack_naruto.somador = 0;
         }

        attack_naruto.frameAtual = attack_naruto.frameAtual + attack_naruto.velocidadeDoFrame;   

        
        glBindTexture(GL_TEXTURE_2D, id_textura_projetil);

        glPushMatrix();

        glTranslatef(shuriken.posX,shuriken.posY,0);
        
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(attack_naruto.vert1_x,attack_naruto.vert1_y);
            glVertex2f(-shuriken.largura/2, -shuriken.altura/2);

            glTexCoord2f(attack_naruto.vert2_x,attack_naruto.vert2_y);
            glVertex2f(shuriken.largura/2, -shuriken.altura/2);
            
            glTexCoord2f(attack_naruto.vert3_x,attack_naruto.vert3_y);
            glVertex2f(shuriken.largura/2, shuriken.altura/2);

            glTexCoord2f(attack_naruto.vert4_x,attack_naruto.vert4_y);
            glVertex2f(-shuriken.largura/2, shuriken.altura/2);

        
    }
    else if(x==2){
        glBindTexture(GL_TEXTURE_2D, id_textura_projetil_inimigo);
        glPushMatrix();

        glTranslatef(kunai.posX,kunai.posY,0);
        
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0,0);
            glVertex2f(-kunai.largura/2, -kunai.altura/2);

            glTexCoord2f(1,0);
            glVertex2f(kunai.largura/2, -kunai.altura/2);
            
            glTexCoord2f(1,1);
            glVertex2f(kunai.largura/2, kunai.altura/2);

            glTexCoord2f(0,1);
            glVertex2f(-kunai.largura/2, kunai.altura/2);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void criaMatrizInimigos(){

    for(int i=0;i<3;i++){
        for(int j=0;j<10;j++){
            matriz_inimigos[i][j].posX = inimigo_aux.posX;
            matriz_inimigos[i][j].posY = inimigo_aux.posY;
            matriz_inimigos[i][j].altura = inimigo_aux.altura;
            matriz_inimigos[i][j].largura = inimigo_aux.largura;
            if(matriz_inimigos[i][j].vivo==true){
                desenhaInimigo(inimigo_aux.posX,inimigo_aux.posY,inimigo_aux.largura,inimigo_aux.altura);
            }
            inimigo_aux.posX+=7;          
        }    
        inimigo_aux.posX -= 70;// settando novamente pra posição inicial pra fazer outra fileira
        inimigo_aux.posY+=7;
    }
    inimigo_aux.posY = 80-descida_fase2;
    
}

void criaVetorInimigos(){
    for(int i=0;i<5;i++){
            vetor_de_inimigos[i].posX = inimigo_aux_fase3.posX;
            vetor_de_inimigos[i].posY = inimigo_aux_fase3.posY;
            vetor_de_inimigos[i].altura = inimigo_aux_fase3.altura;
            vetor_de_inimigos[i].largura = inimigo_aux_fase3.largura;
        
            if(vetor_de_inimigos[i].vivo==true){
                contador_de_texturas_inimigos=i;
                desenhaInimigo(inimigo_aux_fase3.posX,inimigo_aux_fase3.posY,inimigo_aux_fase3.largura,inimigo_aux_fase3.altura);
               
            }
        
        inimigo_aux_fase3.posX+=10;
    }
    inimigo_aux_fase3.posX-=50;
}

bool colisao(float posX_projetil,
            float posY_projetil,
            float largura_projetil,
           float altura_projetil, 
            float posX_inimigo, 
            float posY_inimigo, 
            float altura_inimigo, 
            float largura_inimigo,
            bool vivo){

    if(posY_projetil+altura_projetil == posY_inimigo){
        if(posX_projetil+largura_projetil/2 >= posX_inimigo && posX_projetil+largura_projetil/2 <= posX_inimigo+largura_inimigo){
            if(vivo){
                return true;        
            }        
        }    
      
    }
    /*MELHORAR COLISÃO
    if(posY_projetil+altura_projetil == posY_inimigo){
        if((posX_projetil+largura_projetil)*altura_projetil>= posX_inimigo*altura_inimigo && posX_projetil+largura_projetil <= posX_inimigo+largura_inimigo){
            if(vivo){
                return true;        
            }        
        }    
      
    }*/
    
    
    return false;
}

bool colisao_no_player(float posX_projetil,
            float posY_projetil,
            float largura_projetil,
            float altura_projetil, 
            float posX_inimigo, 
            float posY_inimigo, 
            float altura_inimigo, 
            float largura_inimigo,
            int qtdvidas){

    if(posY_projetil-altura_projetil == posY_inimigo){//+altura_inimigo/2){
        if(posX_projetil+largura_projetil/2 >= posX_inimigo && posX_projetil+largura_projetil/2 <= posX_inimigo+largura_inimigo){
                return true;            
        }    
      
    }
    return false;
}


void desenhaMinhaCena(){
    glClear(GL_COLOR_BUFFER_BIT);
    defineTexturas(fase);
    desenhaFundo();
    desenhaPersonagemPrincipal();

    if(fase==1){
        if(inimigo_primeira_fase.vivo)
            desenhaInimigo(inimigo_primeira_fase.posX,
                            inimigo_primeira_fase.posY,
                            inimigo_primeira_fase.altura,
                            inimigo_primeira_fase.largura);                        
        
        if(shuriken.atirar){
            desenhaProjetil(1);  
            if(colisao(shuriken.posX,shuriken.posY, shuriken.largura,    
                           shuriken.altura, inimigo_primeira_fase.posX,
                           inimigo_primeira_fase.posY, inimigo_primeira_fase.altura,
                           inimigo_primeira_fase.largura,inimigo_primeira_fase.vivo)){
			
			inimigo_primeira_fase.qtdvidas--;
			if(inimigo_primeira_fase.qtdvidas==0){
                           inimigo_primeira_fase.vivo = false;
                       }                            
                           shuriken.atirar = false;         
                                                          }
            shuriken.posY++;
            if(shuriken.posY > 99){//QUando sair da tela
                shuriken.atirar = false;  
            }
        }
  
        if(kunai.atirar){
            desenhaProjetil(2);
            if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                       personagem_principal.posX, personagem_principal.posY,
                       personagem_principal.altura, personagem_principal.largura,
                       personagem_principal.qtdvidas)){
                        
                       personagem_principal.qtdvidas--;
                       kunai.atirar = false;
                       
                       }
                       kunai.posY--;
                       if(kunai.posY<0){
                           kunai.atirar=false;
                       }            
        }        
        
    }else if(fase==2){
            criaMatrizInimigos(); //2°fase
            if(shuriken.atirar){
                desenhaProjetil(1);
                for(int i=0;i<3;i++){
                    for(int j=0;j<10;j++){

                        if(colisao(shuriken.posX,shuriken.posY, shuriken.largura,    
                                   shuriken.altura, matriz_inimigos[i][j].posX,
                                   matriz_inimigos[i][j].posY, matriz_inimigos[i][j].altura,
                                   matriz_inimigos[i][j].largura,matriz_inimigos[i][j].vivo)){

                                    matriz_inimigos[i][j].qtdvidas--;
			                        if(matriz_inimigos[i][j].qtdvidas==0){
                                            matriz_inimigos[i][j].vivo = false;
                                    }                                                                                       
                                   shuriken.atirar = false;         
                        }
                    }
                }
                shuriken.posY++;
                if(shuriken.posY > 99){//QUando sair da tela
                    shuriken.atirar = false;  
                }
            }
            if(kunai.atirar){
                desenhaProjetil(2);
                if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                       personagem_principal.posX, personagem_principal.posY,
                       personagem_principal.altura, personagem_principal.largura,
                       personagem_principal.qtdvidas)){
                        
                       personagem_principal.qtdvidas--;
                       kunai.atirar = false;
                       
                       }
                       kunai.posY--;
                       if(kunai.posY<0){
                           kunai.atirar=false;
                       }               
            
            }
    } 
    else if(fase==3){
        criaVetorInimigos();
        if(shuriken.atirar){
                desenhaProjetil(1);
                for(int i=0;i<5;i++){
                       if(colisao(shuriken.posX,shuriken.posY, shuriken.largura,    
                                   shuriken.altura, vetor_de_inimigos[i].posX,
                                   vetor_de_inimigos[i].posY, vetor_de_inimigos[i].altura,
                                   vetor_de_inimigos[i].largura,vetor_de_inimigos[i].vivo)){

                                    vetor_de_inimigos[i].qtdvidas--;
			                        if(vetor_de_inimigos[i].qtdvidas==0){
                                            vetor_de_inimigos[i].vivo = false;
                                    }                                                                                       
                                   shuriken.atirar = false;  
                                       
                        }
                    
                }
                shuriken.posY++;
                if(shuriken.posY > 99){//QUando sair da tela
                    shuriken.atirar = false;  
              
                }
            }
        if(kunai.atirar){
                desenhaProjetil(2);
                if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                       personagem_principal.posX, personagem_principal.posY,
                       personagem_principal.altura, personagem_principal.largura,
                       personagem_principal.qtdvidas)){
                        
                       personagem_principal.qtdvidas--;
                       kunai.atirar = false;
                       
                       }
                       kunai.posY-=2;
                       if(kunai.posY<0){
                           kunai.atirar=false;
                       }               
            
            }    
        
    }
    else if(fase==4){
        desenhaInimigo(boss.posX,boss.posY,boss.altura,boss.largura);
        if(shuriken.atirar){
                desenhaProjetil(1);
                for(int i=0;i<5;i++){
                       if(colisao(shuriken.posX,shuriken.posY, shuriken.largura,    
                                   shuriken.altura, boss.posX,
                                   boss.posY, boss.altura,
                                   boss.largura,boss.vivo)){

                                    boss.qtdvidas--;
			                        if(boss.qtdvidas==0){
                                            boss.vivo = false;
                                    }                                                                                       
                                   shuriken.atirar = false;  
                                       
                        }
                    
                }
                shuriken.posY++;
                if(shuriken.posY > 99){//QUando sair da tela
                    shuriken.atirar = false;  
              
                }
        }
        if(kunai.atirar){
            desenhaProjetil(2);
            if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                       personagem_principal.posX, personagem_principal.posY,
                       personagem_principal.altura, personagem_principal.largura,
                       personagem_principal.qtdvidas)){
                        
                       personagem_principal.qtdvidas--;
                       kunai.atirar = false;
                       
                       }
                       kunai.posY-=2;
                       if(kunai.posY<0){
                           kunai.atirar=false;
                       }            
        }    
        if(boss.dash){
                
               if(colisao_no_player(boss.posX, boss.posY, boss.largura, boss.altura,
                       personagem_principal.posX, personagem_principal.posY,
                       personagem_principal.altura, personagem_principal.largura,
                       personagem_principal.qtdvidas)){
                        
                           personagem_principal.qtdvidas--;
                           boss.dash = false;
                           boss.posY=80;
                           boss.posX=50;
                       }
                       boss.posY--;
                       if(boss.posY<0){
                           boss.dash=false;
                           boss.posY=80;
                           boss.posX=50;
                       }            
        }         
        
    } 
        
    if(pause)desenhaPause();

    frame_count++;
	final_time = time(NULL);
	if (final_time - initial_time > 0){
		contador_fps = frame_count/(final_time-initial_time);
		printf("FPS: %f\n", contador_fps);
		frame_count = 0;
		initial_time = final_time;
		
	}     
    

    glutSwapBuffers();   
}

void contadorFases(){
    int contador_de_inimigos_mortos=0;   
    if(fase==1){
        
        if(!inimigo_primeira_fase.vivo){
            fase++;        
        }  
    }
    else if(fase==2){
        for(int i=0;i<3;i++){
            for(int j=0;j<10;j++){
                if(matriz_inimigos[i][j].vivo==false){
                    contador_de_inimigos_mortos++;            
                }
            }    
        }
        contador_de_inimigos_mortos=30; //PARA VERIFICAR 3° FASE DIRETO DPS DA PRIMEIRA
        if(contador_de_inimigos_mortos==30){
            fase++;
        }
        contador_de_inimigos_mortos = 0;   
    }
    
    else if(fase == 3){
            for(int i=0;i<5;i++){
                    if(vetor_de_inimigos[i].vivo == false){
                        contador_de_inimigos_mortos++;                
                    }
            }
            contador_de_inimigos_mortos=5;
            if(contador_de_inimigos_mortos==5){
                fase++;            
            }
            contador_de_inimigos_mortos = 0;
    }
}


void redimensionada(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclaPressionada(unsigned char tecla, int x, int y){
    switch(tecla){
        case 27: //Esc
            exit(0);
            break;
        case 32: // espaço
            if(!shuriken.atirar){
                shuriken.posX  = personagem_principal.posX;
                shuriken.posY  = personagem_principal.posY;
                shuriken.atirar = true;
                naruto.frameAtual = 17;
                naruto.contadorDeFrame=17;
                estado = 3;
                glutPostRedisplay();
            }
            break; 
        case 'p':
        case 'P':
            if(!pause){
                pause = true;    
                  
                break;            
            }else{
                pause = false;
                glutTimerFunc(1000/33,gameloop,1);  
                break;
            }
            break; 
        case 'r':
        case 'R':
            if(pause){
                pause = false;   
                reiniciar();  
                glutTimerFunc(1000/33,gameloop,1);             
            }
            reiniciar();
            break;  
        default:
            break;        
    }
}
//REINICIAR O JOGO
void reiniciar(){
    fase=1;
    setup();
    id_textura_personagem_principal=0;
    id_textura_fundo=0;
    id_textura_inimigo=0;
    id_textura_projetil=0;
    id_pause=0;
    id_textura_projetil_inimigo=0;
    id_textura_inimigo0=0;
    id_textura_inimigo1=0;
    id_textura_inimigo2=0;  
    id_textura_inimigo3=0;  
    id_textura_inimigo4=0;
    contador_vezes_carrega_textura = 1;
    contador_de_texturas_inimigos = 0;
    glutPostRedisplay();
}

void teclaIPressionada(int tecla, int x, int y){
    switch(tecla){
        case GLUT_KEY_RIGHT: // Seta para a direita ->
            if(personagem_principal.posX < 90){
                personagem_principal.posX++;  
                naruto.frameAtual = 1;
                naruto.contadorDeFrame = 1;
                estado = 1;      
            }
            break;
        case GLUT_KEY_LEFT: // Seta para a esquerda <-
            if(personagem_principal.posX > 10){
                personagem_principal.posX--; 
                naruto.frameAtual = 9;
                naruto.contadorDeFrame = 9;
                estado = 2;       
            }
            break;
        default:
            break;
        }
}

int randomize_tempo_dash(){
    srand(time(NULL));
    return rand()%101;
}

void movimentoInimigoUltimaFase(){
    int aux;
    if(flag){
        if(boss.posX < 97){
            aux = randomize_tempo_dash();
            if(kunai.atirar == false){
                kunai.posX = boss.posX;
                kunai.posY = boss.posY;
                kunai.atirar = true;         
                glutPostRedisplay();
            }
            if(tempo==aux){
                
                boss.dash = true;
            }
            boss.posX+=1;
        }
        else{
            
            flag=!flag;
        }
    }else{
        if(boss.posX > 3){
            aux = randomize_tempo_dash();
            if(kunai.atirar == false){ // contador de tiros 

                kunai.posX = boss.posX;
                kunai.posY = boss.posY;
                kunai.atirar = true;
                glutPostRedisplay();                
            }
            if(tempo==aux){
                
                boss.dash = true;
            }
            boss.posX -=1;
        }
        else{
            
            flag=!flag;
        }    
    }


}



 // Funções para escolher posição random da fase 3 para atirar
bool verificaPosicaoMortaFase3(int x){
    if(vetor_de_inimigos[x].vivo == false){
        return true; // Posição morta    
    }
    return false; // posição viva
}
int projetilrandom_fase3(){
    int aux;
    srand(time(NULL));    
    aux = rand()%5;  
    while(verificaPosicaoMortaFase3(aux)){
            aux = rand()%5;    
    }
    return aux;
}


void movimentoInimigoTerceiraFase(){
    int aux;
    if(flag){
        if(inimigo_aux_fase3.posX < 57){
            
            if(kunai.atirar==false){
                aux = projetilrandom_fase3();
                kunai.posX = vetor_de_inimigos[aux].posX;
                kunai.posY = vetor_de_inimigos[aux].posY;       
                kunai.atirar = true; 
                        
                glutPostRedisplay();
            }
            inimigo_aux_fase3.posX++;
            
           
        }
        else{
            flag = !flag;        
        }
    }
    else{
        if(inimigo_aux_fase3.posX > 3){
            
            if(kunai.atirar==false){
                aux = projetilrandom_fase3();           
                kunai.posX = vetor_de_inimigos[aux].posX;
                kunai.posY = vetor_de_inimigos[aux].posY;       
                kunai.atirar = true;         
                glutPostRedisplay();
               
            }
            inimigo_aux_fase3.posX--;
            
        }
        else{
            flag = !flag;
        }    
    }

}

void movimentoInimigoSegundaFase(){
    int *pAux;
    int x,y;
    if(flag){
        if(inimigo_aux.posX <34){
            pAux = projetilrandom_fase2();
                x=pAux[0];
                y=pAux[1];
                free(pAux); 
            if(kunai.atirar==false ){//contador_de_tiros_tela < maximo_de_tiros_tela_fase2){               
                kunai.posX = matriz_inimigos[x][y].posX;
                kunai.posY = matriz_inimigos[x][y].posY;        
                kunai.atirar = true;         
                glutPostRedisplay();
            } 
            inimigo_aux.posX++;
        }
        else{
            descida_fase2+=1;
            flag = !flag;        
                            
        }
    }
    else{
        if(inimigo_aux.posX>3){
            pAux = projetilrandom_fase2();
            x=pAux[0];
            y=pAux[1];
            free(pAux);           
        
            if(kunai.atirar==false ){//contador_de_tiros_tela < maximo_de_tiros_tela_fase2){
                kunai.posX = matriz_inimigos[x][y].posX;
                kunai.posY = matriz_inimigos[x][y].posY;               
                kunai.atirar = true;         
                glutPostRedisplay();
              
            }   
            inimigo_aux.posX--;
        }
        else{
            descida_fase2+=1;        
            flag = !flag;
            
        }
    }
}

void movimentoInimigoPrimeiraFase(){
    if(flag){
        if(inimigo_primeira_fase.posX < 97){

            if(kunai.atirar == false){
                kunai.posX = inimigo_primeira_fase.posX;
                kunai.posY = inimigo_primeira_fase.posY;
                kunai.atirar = true;         
                glutPostRedisplay();
            }
                inimigo_primeira_fase.posX+=2;
        }
        else{
            inimigo_primeira_fase.posY-=2;
            flag=!flag;
        }
    }else{
        if(inimigo_primeira_fase.posX > 3){

            if(kunai.atirar == false){ // contador de tiros 

                kunai.posX = inimigo_primeira_fase.posX;
                kunai.posY = inimigo_primeira_fase.posY;
                kunai.atirar = true;
                glutPostRedisplay();                
            }
            inimigo_primeira_fase.posX -=2;
        }
        else{
            inimigo_primeira_fase.posY-=2;
            flag=!flag;
        }    
    }

}

bool verificaPosicaoMortaFase2(int x, int y){// aq
    if(matriz_inimigos[y][x].vivo == false){
        return true; // posição morta
    }
    return false; // posicao ta viva
}

int* projetilrandom_fase2(){ // fase 2
    int *posXY,linha=0,aux;
    posXY = (int*)malloc(2*sizeof(int));    
    posXY[0] = 0;
    posXY[1] = 0;
  
    srand(time(NULL));    
    aux = rand()%10;
    linha = rand()%3;  
    while(verificaPosicaoMortaFase2(aux,linha)){
            aux = rand()%10;
            linha = rand()%3;
    }
    posXY[0] = linha;
    posXY[1] = aux;
    return posXY; // dar free nisso sempre
}


void gameloop(int tempo){
    contadorFases();
    relogio();
    if(fase==1)movimentoInimigoPrimeiraFase();
    else if(fase==2)movimentoInimigoSegundaFase();
    else if(fase==3)movimentoInimigoTerceiraFase();
    else if(fase==4)movimentoInimigoUltimaFase();
    
    if(!pause){      
        glutPostRedisplay(); // PEDE PARA A CENA SER REDESENHADA ASSIM QUE POSSIVEL 
        glutTimerFunc(1000/33,gameloop,0); // CHAMA NOVAMENTE A FUNÇÃO DE ATT A TELA (recursividade).
         
    }else{
        desenhaPause();           
        glutPostRedisplay(); 
         
    }
  
}

void relogio(){
		tempo++;
		if(tempo>tempo_limite){
			tempo = 0;
		}
	
}


void defineAtributos(){
    //contador_de_tiros=0;

    tempo=0;
    tempo_limite = 100;

    personagem_principal.posX = 50;
    personagem_principal.posY = 10;
    personagem_principal.largura = 8;
    personagem_principal.altura = 8;
    personagem_principal.qtdvidas = 3;

    inimigo_aux.posX = 7;
    inimigo_aux.posY = 80;
    inimigo_aux.largura = 7;
    inimigo_aux.altura = 7;
    descida_fase2=0;

     
    inimigo_aux_fase3.posX = 30; 
    inimigo_aux_fase3.posY = 80;
    inimigo_aux_fase3.largura = 7;
    inimigo_aux_fase3.altura = 7;
    
    kunai.largura = 4;
    kunai.altura = 4;
    kunai.atirar = false;

    inimigo_primeira_fase.posX=50;
    inimigo_primeira_fase.posY = 80;
    inimigo_primeira_fase.largura = 10;
    inimigo_primeira_fase.altura = 10;
    inimigo_primeira_fase.vivo = true;
    inimigo_primeira_fase.qtdvidas = 1;
    inimigo_primeira_fase.dash =false;

    boss.posX=50;
    boss.posY = 80;
    boss.largura = 10;
    boss.altura = 10;
    boss.vivo = true;
    boss.qtdvidas = 5;
    boss.dash =false;

    shuriken.largura = 4;
    shuriken.altura = 4;
    shuriken.atirar = false;

    for(int i=0;i<3;i++){
        for(int j = 0;j<10;j++){
            matriz_inimigos[i][j].vivo = true;   
            matriz_inimigos[i][j].qtdvidas=1;
            matriz_inimigos[i][j].dash = false;     
        }    
    }

    for(int i=0;i<5;i++){
        vetor_de_inimigos[i].vivo = true;
        vetor_de_inimigos[i].qtdvidas=2;
        vetor_de_inimigos[i].dash=false;
    }
    kakashi.frameAtual = 0;
    kakashi.somador = 0;
    kakashi.contadorDeFrame = 0;
    kakashi.qtdTotalFrame=2;
    kakashi.velocidadeDoFrame = 0.1;

    zetsu.frameAtual = 0;
    zetsu.somador = 0;
    zetsu.contadorDeFrame = 0;
    zetsu.qtdTotalFrame=12;
    zetsu.velocidadeDoFrame = 1;

    naruto.frameAtual = 0;
    naruto.somador = 0;
    naruto.contadorDeFrame = 0;
    naruto.qtdTotalFrame = 21;
    
    attack_naruto.frameAtual = 0;
    attack_naruto.somador = 0;
    attack_naruto.contadorDeFrame = 0;
    attack_naruto.qtdTotalFrame=4;
    attack_naruto.velocidadeDoFrame = 0.5;

}


void setup(){
    glClearColor(0,0,0,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    defineTexturas(fase);
    defineAtributos();
    
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);

    glutCreateWindow("Naruto Ultimate Ninja Storm: Invader's");

    glutDisplayFunc(desenhaMinhaCena);
    glutReshapeFunc(redimensionada);
    glutKeyboardFunc(teclaPressionada);
    glutSpecialFunc(teclaIPressionada);
    
    glutTimerFunc(1000/33,gameloop,1);   
    
    
    setup();
    glutMainLoop();
    return 0;
}
