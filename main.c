#include"texturas.h"
#include<stdlib.h>
#include<stdio.h>
#include"global.h"
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>



void contador();
void gameloop(int tempo);
void reiniciar();
void setup();
int* projetilrandom_fase2();
void criaVetorInimigos();
void desenhaDashInimigo();
void relogio();
void salvar_pontuacao();

Jogador personagem_principal;

Auxiliar_de_criacao_de_obj inimigo_aux;// auxiliar da segunda fase p/criar os zetsu`s
Auxiliar_de_criacao_de_obj inimigo_aux_fase3; // auxiliar da segunda fase
Auxiliar_de_criacao_de_obj sapin_obj;


Arma shuriken; // aliado
Arma kunai; // inimigo

formacao inimigo_primeira_fase; // PRIMEIRA FASE
formacao matriz_inimigos[3][10]; // SEGUNDA FASE
formacao vetor_de_inimigos[5]; // TERCEIRA FASE
formacao boss;

animacao kakashi;
animacao zetsu;
animacao naruto;
animacao attack_naruto;
animacao hidan;
animacao deidara;
animacao pain;
animacao kisame;
animacao sasore;
animacao vidaFase3;
animacao tobi;
animacao vidaBoss;
animacao sapin;
animacao vidaNaruto;
animacao pontuacao;
animacao pontuacao2;
animacao pontuacao3;

int escolha_no_menu = 0;

int verificaSAVE;

bool pause_t = false;

int perdeu_ou_jogando_ou_ganhou=0; // 0=jogando ;-1 = perdeu; +1 = ganhou

bool pode_dar_dash = true;
bool flag = true; // trocar a direção movimento dos inimigos
int fase=0;

int creditos_ou_pontuacao;

int descida_fase2; 

int tempo,tempo_limite;

int pontuacao_total, maior_pontuacao, tempo_de_jogo; 
     

double frame_count = 0,initial_time, final_time, contador_fps=0; // para o contador de fps

FILE *data;

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
    			if(flag){
            
                    if(hidan.frameAtual >= hidan.contadorDeFrame && hidan.frameAtual != hidan.contadorDeFrame){//Sempre que o FrameAtual for    igual a qtdDeFrame passa para a proxima imagem
                    //printf("okok\n");
                    //printf("|%f\n",hidan.frameAtual);
                    //printf("|%f|\n",hidan.contadorDeFrame);
                    
                        hidan.vert1_x = 0.0 + hidan.somador * hidan.contadorDeFrame;
                        hidan.vert2_x = 1/hidan.qtdTotalFrame + hidan.somador * hidan.contadorDeFrame;
                        hidan.vert3_x = 1/hidan.qtdTotalFrame + hidan.somador* hidan.contadorDeFrame;
                        hidan.vert4_x = 0.0 + hidan.somador * hidan.contadorDeFrame;

                        hidan.vert1_y = 0.0;
                        hidan.vert2_y = 0.0;
                        hidan.vert3_y = 1.0;
                        hidan.vert4_y = 1.0;  
                            
                        //printf("%f\n", hidan.vert1_x);
                        //printf("%f\n", hidan.vert2_x);

                        hidan.somador = 1/hidan.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        hidan.contadorDeFrame++;  
                }

                    if(hidan.frameAtual > hidan.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        hidan.frameAtual = 0;
                        hidan.contadorDeFrame =  0;
                        hidan.vert1_x = 0.0;
                        hidan.vert2_x = 1/hidan.qtdTotalFrame;
                        hidan.vert3_x = 1/hidan.qtdTotalFrame;
                        hidan.vert4_x = 0.0;
                        hidan.somador = 0;
                     }

                    hidan.frameAtual = hidan.frameAtual + hidan.velocidadeDoFrame;
                    
                }
                      
                if(!flag){
                        
                        if(hidan.frameAtual >= hidan.contadorDeFrame && hidan.frameAtual != hidan.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                        //printf("okok\n");
                        
                        hidan.vert1_x = 0.0 + hidan.somador * hidan.contadorDeFrame;
                        hidan.vert2_x = 1/hidan.qtdTotalFrame + hidan.somador * hidan.contadorDeFrame;
                        hidan.vert3_x = 1/hidan.qtdTotalFrame + hidan.somador* hidan.contadorDeFrame;
                        hidan.vert4_x = 0.0 + hidan.somador * hidan.contadorDeFrame;

                        hidan.vert1_y = 0.0;
                        hidan.vert2_y = 0.0;
                        hidan.vert3_y = 1.0;
                        hidan.vert4_y = 1.0;  

                        hidan.somador = 1/hidan.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        hidan.contadorDeFrame++;  
                    }

                    if(hidan.frameAtual > hidan.qtdTotalFrame || hidan.vert1_x < 1/hidan.qtdTotalFrame * hidan.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        hidan.frameAtual = (hidan.qtdTotalFrame/2)-1;
                        hidan.contadorDeFrame =  hidan.qtdTotalFrame/2;
                        hidan.somador = 1/hidan.qtdTotalFrame;
                        hidan.vert1_x = hidan.somador * hidan.contadorDeFrame;
                        hidan.vert2_x = 1/hidan.qtdTotalFrame + hidan.somador * hidan.contadorDeFrame;
                        hidan.vert3_x = 1/hidan.qtdTotalFrame + hidan.somador * hidan.contadorDeFrame;
                        hidan.vert4_x = hidan.somador * hidan.contadorDeFrame;
                        
                     }

        hidan.frameAtual = hidan.frameAtual + hidan.velocidadeDoFrame;    
    }

    glBindTexture(GL_TEXTURE_2D, id_textura_inimigo0);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
                            
        glTexCoord2f(hidan.vert1_x, hidan.vert1_y); //
        glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

        glTexCoord2f(hidan.vert2_x, hidan.vert2_y); //
        glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
 
        glTexCoord2f(hidan.vert3_x, hidan.vert3_y); //
        glVertex3f(largura/2, altura/2,0); // |     | // 15 , 20

        glTexCoord2f(hidan.vert4_x, hidan.vert4_y); //
        glVertex3f(-largura/2, altura/2,0); // v1---v2 // -15, 20

    glEnd();
    
    glPopMatrix();

			break;
		case 1:
			if(deidara.frameAtual >= deidara.contadorDeFrame && deidara.frameAtual != deidara.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    //printf("okok\n");
                    //printf("|%f\n",deidara.frameAtual);
                    //printf("|%f|\n",deidara.contadorDeFrame);
                    
                        deidara.vert1_x = 0.0 + deidara.somador * deidara.contadorDeFrame;
                        deidara.vert2_x = 1/deidara.qtdTotalFrame + deidara.somador * deidara.contadorDeFrame;
                        deidara.vert3_x = 1/deidara.qtdTotalFrame + deidara.somador* deidara.contadorDeFrame;
                        deidara.vert4_x = 0.0 + deidara.somador * deidara.contadorDeFrame;

                        deidara.vert1_y = 0.0;
                        deidara.vert2_y = 0.0;
                        deidara.vert3_y = 1.0;
                        deidara.vert4_y = 1.0;  
                            
                        //printf("%f\n", deidara.vert1_x);
                        //printf("%f\n", deidara.vert2_x);

                        deidara.somador = 1/deidara.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        deidara.contadorDeFrame++;  
                }

                    if(deidara.frameAtual > deidara.qtdTotalFrame){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        deidara.frameAtual = 0;
                        deidara.contadorDeFrame =  0;
                        deidara.vert1_x = 0.0;
                        deidara.vert2_x = 1/deidara.qtdTotalFrame;
                        deidara.vert3_x = 1/deidara.qtdTotalFrame;
                        deidara.vert4_x = 0.0;
                        deidara.somador = 0;
                     }

                    deidara.frameAtual = deidara.frameAtual + deidara.velocidadeDoFrame;
                    
                

    glBindTexture(GL_TEXTURE_2D, id_textura_inimigo1);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
                            
        glTexCoord2f(deidara.vert1_x, deidara.vert1_y); //
        glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

        glTexCoord2f(deidara.vert2_x, deidara.vert2_y); //
        glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
 
        glTexCoord2f(deidara.vert3_x, deidara.vert3_y); //
        glVertex3f(largura/2, altura/2,0); // |     | // 15 , 20

        glTexCoord2f(deidara.vert4_x, deidara.vert4_y); //
        glVertex3f(-largura/2, altura/2,0); // v1---v2 // -15, 20
    glEnd();
    
    glPopMatrix();
			break;
		case 2:
    			
        if(flag){
            
                    if(pain.frameAtual >= pain.contadorDeFrame && pain.frameAtual != pain.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    //printf("okok\n");
                    //printf("|%f\n",pain.frameAtual);
                    //printf("|%f|\n",pain.contadorDeFrame);
                    
                        pain.vert1_x = 0.0 + pain.somador * pain.contadorDeFrame;
                        pain.vert2_x = 1/pain.qtdTotalFrame + pain.somador * pain.contadorDeFrame;
                        pain.vert3_x = 1/pain.qtdTotalFrame + pain.somador* pain.contadorDeFrame;
                        pain.vert4_x = 0.0 + pain.somador * pain.contadorDeFrame;

                        pain.vert1_y = 0.0;
                        pain.vert2_y = 0.0;
                        pain.vert3_y = 1.0;
                        pain.vert4_y = 1.0;  
                            
                        //printf("%f\n", pain.vert1_x);
                        //printf("%f\n", pain.vert2_x);

                        pain.somador = 1/pain.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        pain.contadorDeFrame++;  
                }

                    if(pain.frameAtual > pain.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        pain.frameAtual = 0;
                        pain.contadorDeFrame =  0;
                        pain.vert1_x = 0.0;
                        pain.vert2_x = 1/pain.qtdTotalFrame;
                        pain.vert3_x = 1/pain.qtdTotalFrame;
                        pain.vert4_x = 0.0;
                        pain.somador = 0;
                     }

                    pain.frameAtual = pain.frameAtual + pain.velocidadeDoFrame;
                    
                }
                      
                if(!flag){
                        
                        if(pain.frameAtual >= pain.contadorDeFrame && pain.frameAtual != pain.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                        //printf("okok\n");
                        
                        pain.vert1_x = 0.0 + pain.somador * pain.contadorDeFrame;
                        pain.vert2_x = 1/pain.qtdTotalFrame + pain.somador * pain.contadorDeFrame;
                        pain.vert3_x = 1/pain.qtdTotalFrame + pain.somador* pain.contadorDeFrame;
                        pain.vert4_x = 0.0 + pain.somador * pain.contadorDeFrame;

                        pain.vert1_y = 0.0;
                        pain.vert2_y = 0.0;
                        pain.vert3_y = 1.0;
                        pain.vert4_y = 1.0;  

                        pain.somador = 1/pain.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        pain.contadorDeFrame++;  
                    }

                    if(pain.frameAtual > pain.qtdTotalFrame || pain.vert1_x < 1/pain.qtdTotalFrame * pain.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        pain.frameAtual = (pain.qtdTotalFrame/2)-1;
                        pain.contadorDeFrame =  pain.qtdTotalFrame/2;
                        pain.somador = 1/pain.qtdTotalFrame;
                        pain.vert1_x = pain.somador * pain.contadorDeFrame;
                        pain.vert2_x = 1/pain.qtdTotalFrame + pain.somador * pain.contadorDeFrame;
                        pain.vert3_x = 1/pain.qtdTotalFrame + pain.somador * pain.contadorDeFrame;
                        pain.vert4_x = pain.somador * pain.contadorDeFrame;
                        
                     }

        pain.frameAtual = pain.frameAtual + pain.velocidadeDoFrame;    
    }

    glBindTexture(GL_TEXTURE_2D, id_textura_inimigo2);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
                            
        glTexCoord2f(pain.vert1_x, pain.vert1_y); //
        glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

        glTexCoord2f(pain.vert2_x, pain.vert2_y); //
        glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
 
        glTexCoord2f(pain.vert3_x, pain.vert3_y); //
        glVertex3f(largura/2, altura/2,0); // |     | // 15 , 20

        glTexCoord2f(pain.vert4_x, pain.vert4_y); //
        glVertex3f(-largura/2, altura/2,0); // v1---v2 // -15, 20

    glEnd();
    
    glPopMatrix();


			break;
		case 3:
            if(flag){
            
                    if(kisame.frameAtual >= kisame.contadorDeFrame && kisame.frameAtual != kisame.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    //printf("okok\n");
                    //printf("|%f\n",kisame.frameAtual);
                    //printf("|%f|\n",kisame.contadorDeFrame);
                    
                        kisame.vert1_x = 0.0 + kisame.somador * kisame.contadorDeFrame;
                        kisame.vert2_x = 1/kisame.qtdTotalFrame + kisame.somador * kisame.contadorDeFrame;
                        kisame.vert3_x = 1/kisame.qtdTotalFrame + kisame.somador* kisame.contadorDeFrame;
                        kisame.vert4_x = 0.0 + kisame.somador * kisame.contadorDeFrame;

                        kisame.vert1_y = 0.0;
                        kisame.vert2_y = 0.0;
                        kisame.vert3_y = 1.0;
                        kisame.vert4_y = 1.0;  
                            
                        //printf("%f\n", kisame.vert1_x);
                        //printf("%f\n", kisame.vert2_x);

                        kisame.somador = 1/kisame.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        kisame.contadorDeFrame++;  
                }

                    if(kisame.frameAtual > kisame.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        kisame.frameAtual = 0;
                        kisame.contadorDeFrame =  0;
                        kisame.vert1_x = 0.0;
                        kisame.vert2_x = 1/kisame.qtdTotalFrame;
                        kisame.vert3_x = 1/kisame.qtdTotalFrame;
                        kisame.vert4_x = 0.0;
                        kisame.somador = 0;
                     }

                    kisame.frameAtual = kisame.frameAtual + kisame.velocidadeDoFrame;
                    
                }
                      
                if(!flag){
                        
                        if(kisame.frameAtual >= kisame.contadorDeFrame && kisame.frameAtual != kisame.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                        //printf("okok\n");
                        
                        kisame.vert1_x = 0.0 + kisame.somador * kisame.contadorDeFrame;
                        kisame.vert2_x = 1/kisame.qtdTotalFrame + kisame.somador * kisame.contadorDeFrame;
                        kisame.vert3_x = 1/kisame.qtdTotalFrame + kisame.somador* kisame.contadorDeFrame;
                        kisame.vert4_x = 0.0 + kisame.somador * kisame.contadorDeFrame;

                        kisame.vert1_y = 0.0;
                        kisame.vert2_y = 0.0;
                        kisame.vert3_y = 1.0;
                        kisame.vert4_y = 1.0;  

                        kisame.somador = 1/kisame.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        kisame.contadorDeFrame++;  
                    }

                    if(kisame.frameAtual > kisame.qtdTotalFrame || kisame.vert1_x < 1/kisame.qtdTotalFrame * kisame.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        kisame.frameAtual = (kisame.qtdTotalFrame/2)-1;
                        kisame.contadorDeFrame =  kisame.qtdTotalFrame/2;
                        kisame.somador = 1/kisame.qtdTotalFrame;
                        kisame.vert1_x = kisame.somador * kisame.contadorDeFrame;
                        kisame.vert2_x = 1/kisame.qtdTotalFrame + kisame.somador * kisame.contadorDeFrame;
                        kisame.vert3_x = 1/kisame.qtdTotalFrame + kisame.somador * kisame.contadorDeFrame;
                        kisame.vert4_x = kisame.somador * kisame.contadorDeFrame;
                        
                     }

        kisame.frameAtual = kisame.frameAtual + kisame.velocidadeDoFrame;    
    }

    glBindTexture(GL_TEXTURE_2D, id_textura_inimigo3);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
                            
        glTexCoord2f(kisame.vert1_x, kisame.vert1_y); //
        glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

        glTexCoord2f(kisame.vert2_x, kisame.vert2_y); //
        glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
 
        glTexCoord2f(kisame.vert3_x, kisame.vert3_y); //
        glVertex3f(largura/2, altura/2,0); // |     | // 15 , 20

        glTexCoord2f(kisame.vert4_x, kisame.vert4_y); //
        glVertex3f(-largura/2, altura/2,0); // v1---v2 // -15, 20

    glEnd();
    
    glPopMatrix();
			

			break;
		case 4:
            if(flag){
            
                    if(sasore.frameAtual >= sasore.contadorDeFrame && sasore.frameAtual != sasore.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    //printf("okok\n");
                    //printf("|%f\n",sasore.frameAtual);
                    //printf("|%f|\n",sasore.contadorDeFrame);
                    
                        sasore.vert1_x = 0.0 + sasore.somador * sasore.contadorDeFrame;
                        sasore.vert2_x = 1/sasore.qtdTotalFrame + sasore.somador * sasore.contadorDeFrame;
                        sasore.vert3_x = 1/sasore.qtdTotalFrame + sasore.somador* sasore.contadorDeFrame;
                        sasore.vert4_x = 0.0 + sasore.somador * sasore.contadorDeFrame;

                        sasore.vert1_y = 0.0;
                        sasore.vert2_y = 0.0;
                        sasore.vert3_y = 1.0;
                        sasore.vert4_y = 1.0;  
                            
                        //printf("%f\n", sasore.vert1_x);
                        //printf("%f\n", sasore.vert2_x);

                        sasore.somador = 1/sasore.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        sasore.contadorDeFrame++;  
                }

                    if(sasore.frameAtual > sasore.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        sasore.frameAtual = 0;
                        sasore.contadorDeFrame =  0;
                        sasore.vert1_x = 0.0;
                        sasore.vert2_x = 1/sasore.qtdTotalFrame;
                        sasore.vert3_x = 1/sasore.qtdTotalFrame;
                        sasore.vert4_x = 0.0;
                        sasore.somador = 0;
                     }

                    sasore.frameAtual = sasore.frameAtual + sasore.velocidadeDoFrame;
                    
                }
                      
                if(!flag){
                        
                        if(sasore.frameAtual >= sasore.contadorDeFrame && sasore.frameAtual != sasore.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                        //printf("okok\n");
                        
                        sasore.vert1_x = 0.0 + sasore.somador * sasore.contadorDeFrame;
                        sasore.vert2_x = 1/sasore.qtdTotalFrame + sasore.somador * sasore.contadorDeFrame;
                        sasore.vert3_x = 1/sasore.qtdTotalFrame + sasore.somador* sasore.contadorDeFrame;
                        sasore.vert4_x = 0.0 + sasore.somador * sasore.contadorDeFrame;

                        sasore.vert1_y = 0.0;
                        sasore.vert2_y = 0.0;
                        sasore.vert3_y = 1.0;
                        sasore.vert4_y = 1.0;  

                        sasore.somador = 1/sasore.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                        sasore.contadorDeFrame++;  
                    }

                    if(sasore.frameAtual > sasore.qtdTotalFrame || sasore.vert1_x < 1/sasore.qtdTotalFrame * sasore.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                        //printf("ok\n");
                        sasore.frameAtual = (sasore.qtdTotalFrame/2)-1;
                        sasore.contadorDeFrame =  sasore.qtdTotalFrame/2;
                        sasore.somador = 1/sasore.qtdTotalFrame;
                        sasore.vert1_x = sasore.somador * sasore.contadorDeFrame;
                        sasore.vert2_x = 1/sasore.qtdTotalFrame + sasore.somador * sasore.contadorDeFrame;
                        sasore.vert3_x = 1/sasore.qtdTotalFrame + sasore.somador * sasore.contadorDeFrame;
                        sasore.vert4_x = sasore.somador * sasore.contadorDeFrame;
                        
                     }

        sasore.frameAtual = sasore.frameAtual + sasore.velocidadeDoFrame;    
    }

    glBindTexture(GL_TEXTURE_2D, id_textura_inimigo4);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
                            
        glTexCoord2f(sasore.vert1_x, sasore.vert1_y); //
        glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

        glTexCoord2f(sasore.vert2_x, sasore.vert2_y); //
        glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
 
        glTexCoord2f(sasore.vert3_x, sasore.vert3_y); //
        glVertex3f(largura/2, altura/2,0); // |     | // 15 , 20

        glTexCoord2f(sasore.vert4_x, sasore.vert4_y); //
        glVertex3f(-largura/2, altura/2,0); // v1---v2 // -15, 20

    glEnd();
    
    glPopMatrix();			
    
			break;
		default:
			break;
    	}
        
    }
    else if(fase == 4){
        if(boss.dash==false){
            if(flag){
                if(tobi.frameAtual >= tobi.contadorDeFrame && tobi.frameAtual != tobi.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    //printf("okok\n");
                    tobi.vert1_x = 0.0 + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame + tobi.somador* tobi.contadorDeFrame;
                    tobi.vert4_x = 0.0 + tobi.somador * tobi.contadorDeFrame;

                    tobi.vert1_y = 0.0;
                    tobi.vert2_y = 0.0;
                    tobi.vert3_y = 1.0;
                    tobi.vert4_y = 1.0;

                    tobi.somador = 1/tobi.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                    tobi.contadorDeFrame++;  
                }
        
                if(tobi.frameAtual > tobi.qtdTotalFrame-16){//volta para posicao inicial da imagem para fazer a animaçao dnv
                    //printf("ok\n");
                    tobi.frameAtual = 0;
                    tobi.contadorDeFrame =  0;
                    tobi.vert1_x = 0.0;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame;
                    tobi.vert4_x = 0.0;
                    tobi.somador = 0;
            
                 }
        


            tobi.frameAtual = tobi.frameAtual + tobi.velocidadeDoFrame;
            }
        if(!flag){
                if(tobi.frameAtual >= tobi.contadorDeFrame && tobi.frameAtual != tobi.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    
                    tobi.vert1_x = 0.0 + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame + tobi.somador* tobi.contadorDeFrame;
                    tobi.vert4_x = 0.0 + tobi.somador * tobi.contadorDeFrame;

                    tobi.vert1_y = 0.0;
                    tobi.vert2_y = 0.0;
                    tobi.vert3_y = 1.0;
                    tobi.vert4_y = 1.0;  

                    tobi.somador = 1/tobi.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                    tobi.contadorDeFrame++;  
                }
                
                if(tobi.frameAtual > tobi.qtdTotalFrame-10 || tobi.vert1_x < 1/tobi.qtdTotalFrame * (tobi.qtdTotalFrame-16)){//volta para posicao inicial da imagem para fazer a animaçao dnv
     


                    tobi.somador=1/tobi.qtdTotalFrame;
                    tobi.frameAtual = tobi.qtdTotalFrame - 16;
                    tobi.contadorDeFrame =  tobi.qtdTotalFrame - 16;
                    tobi.vert1_x = tobi.somador * tobi.contadorDeFrame;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert4_x = tobi.somador * tobi.contadorDeFrame;
                    
                 }
       
            tobi.frameAtual = tobi.frameAtual + tobi.velocidadeDoFrame;
            }
        }

    if(boss.dash == true){
        if(flag){
                if(tobi.frameAtual >= tobi.contadorDeFrame && tobi.frameAtual != tobi.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    //printf("okok\n");
                    tobi.vert1_x = tobi.somador * tobi.contadorDeFrame;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame + tobi.somador* tobi.contadorDeFrame;
                    tobi.vert4_x = tobi.somador * tobi.contadorDeFrame;

                    tobi.vert1_y = 0.0;
                    tobi.vert2_y = 0.0;
                    tobi.vert3_y = 1.0;
                    tobi.vert4_y = 1.0;

                    tobi.somador = 1/tobi.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                    tobi.contadorDeFrame++;  
                }
        
                if(tobi.frameAtual > tobi.qtdTotalFrame-5 || tobi.vert1_x < 1/tobi.qtdTotalFrame * (tobi.qtdTotalFrame-10)){//volta para posicao inicial da imagem para fazer a animaçao dnv
                    //printf("ok\n");
                    tobi.frameAtual = 12;
                    tobi.contadorDeFrame =  12;
                    tobi.somador = 1/tobi.qtdTotalFrame;
                    tobi.vert1_x = tobi.somador * tobi.contadorDeFrame;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert4_x = tobi.somador * tobi.contadorDeFrame;
                    
            
                 }
     
            tobi.frameAtual = tobi.frameAtual + 0.3;
            }

        if(!flag){
                if(tobi.frameAtual >= tobi.contadorDeFrame && tobi.frameAtual != tobi.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                    
                    tobi.vert1_x = tobi.somador * tobi.contadorDeFrame;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame + tobi.somador* tobi.contadorDeFrame;
                    tobi.vert4_x = tobi.somador * tobi.contadorDeFrame;

                    tobi.vert1_y = 0.0;
                    tobi.vert2_y = 0.0;
                    tobi.vert3_y = 1.0;
                    tobi.vert4_y = 1.0;  

                    tobi.somador = 1/tobi.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
                    tobi.contadorDeFrame++;  
                }
                
                if(tobi.frameAtual > tobi.qtdTotalFrame || tobi.vert1_x < 1/tobi.qtdTotalFrame * (tobi.qtdTotalFrame-5)){//volta para posicao inicial da imagem para fazer a animaçao dnv
     


                    tobi.somador=1/tobi.qtdTotalFrame;
                    tobi.frameAtual = 17;
                    tobi.contadorDeFrame =  17;
                    tobi.vert1_x = tobi.somador * tobi.contadorDeFrame;
                    tobi.vert2_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert3_x = 1/tobi.qtdTotalFrame + tobi.somador * tobi.contadorDeFrame;
                    tobi.vert4_x = tobi.somador * tobi.contadorDeFrame;
                    
                 }
       
            tobi.frameAtual = tobi.frameAtual + 0.3;
            }


    }
        


        glBindTexture(GL_TEXTURE_2D, id_textura_inimigo);
        
        glPushMatrix();

        glTranslatef(posX, posY, 0);
        
        glBegin(GL_TRIANGLE_FAN);
                                
            glTexCoord2f(tobi.vert1_x, tobi.vert1_y); //
            glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

            glTexCoord2f(tobi.vert2_x, tobi.vert2_y); //
            glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
     
            glTexCoord2f(tobi.vert3_x, tobi.vert3_y); //
            glVertex3f( largura/2,  altura/2,0); // |     | // 15 , 20

            glTexCoord2f(tobi.vert4_x, tobi.vert4_y); //
            glVertex3f(-largura/2,  altura/2,0); // v1---v2 // -15, 20

        glEnd();
        
        glPopMatrix();

        }

       
}


void desenhaFundo(GLuint x){
    
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, x);
    
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

void desenhaNomeDoInimigo(int posX,int posY,GLuint id_texturas){// Ainda em teste, pois a barra de vida nao esta tao bonita.
    
    //glColor3f(1.0,1.0,1.0);

    glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
    glBindTexture(GL_TEXTURE_2D,id_texturas);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(0, 0);
        glVertex2f(-7.5, -1); // v3---v2

        glTexCoord2f(1, 0);
        glVertex2f(7.5, -1); // |     |

        glTexCoord2f(1, 1);
        glVertex2f(7.5, 1); // |     |

        glTexCoord2f(0, 1);
        glVertex2f(-7.5, 1); // v0---v1

    glEnd();
   
    glPopMatrix();



}

void desenhaBarraDeVidaInimigo(int posX,int posY,int i){// Ainda em teste, pois a barra de vida nao esta tao bonita.
    
    //glColor3f(1.0,1.0,1.0);
    if(vetor_de_inimigos[i].qtdvidas==2){
                vidaFase3.vert1_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i];
                vidaFase3.vert2_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i] + 1/vidaFase3.qtdTotalFrame;
                vidaFase3.vert3_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i] + 1/vidaFase3.qtdTotalFrame;
                vidaFase3.vert4_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i];

                vidaFase3.vert1_y = 0.0;
                vidaFase3.vert2_y = 0.0;
                vidaFase3.vert3_y = 1.0;
                vidaFase3.vert4_y = 1.0;



    }

    else if(vetor_de_inimigos[i].qtdvidas==1){
                vidaFase3.vert1_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i];
                vidaFase3.vert2_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i] + 1/vidaFase3.qtdTotalFrame;
                vidaFase3.vert3_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i] + 1/vidaFase3.qtdTotalFrame;
                vidaFase3.vert4_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i];

                vidaFase3.vert1_y = 0.0;
                vidaFase3.vert2_y = 0.0;
                vidaFase3.vert3_y = 1.0;
                vidaFase3.vert4_y = 1.0;



    }
    else if(vetor_de_inimigos[i].qtdvidas==0){
                vidaFase3.vert1_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i];
                vidaFase3.vert2_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i] + 1/vidaFase3.qtdTotalFrame;
                vidaFase3.vert3_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i] + 1/vidaFase3.qtdTotalFrame;
                vidaFase3.vert4_x = vidaFase3.somador_vetor[i] * vidaFase3.frameAtual_vetor[i];

                vidaFase3.vert1_y = 0.0;
                vidaFase3.vert2_y = 0.0;
                vidaFase3.vert3_y = 1.0;
                vidaFase3.vert4_y = 1.0;
}

    glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
    glBindTexture(GL_TEXTURE_2D,id_textura_vida3fase);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(vidaFase3.vert1_x, vidaFase3.vert1_y);
        glVertex2f(-4, -2.0); // v3---v2

        glTexCoord2f(vidaFase3.vert2_x, vidaFase3.vert2_y);
        glVertex2f(4, -2.0); // |     |

        glTexCoord2f(vidaFase3.vert3_x, vidaFase3.vert3_y);
        glVertex2f(4, 2.0); // |     |

        glTexCoord2f(vidaFase3.vert4_x, vidaFase3.vert4_y);
        glVertex2f(-4, 2.0); // v0---v1

    glEnd();
   
    glPopMatrix();



}

void desenhaBarraBoss(){// Ainda em teste, pois a barra de vida nao esta tao bonita.
    
    //glColor3f(1.0,1.0,1.0);
    if(boss.qtdvidas==3){
                vidaBoss.vert1_x = vidaBoss.somador * vidaBoss.frameAtual;
                vidaBoss.vert2_x = vidaBoss.somador * vidaBoss.frameAtual + 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert3_x = vidaBoss.somador * vidaBoss.frameAtual + 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert4_x = vidaBoss.somador * vidaBoss.frameAtual;

                vidaBoss.vert1_y = 0.0;
                vidaBoss.vert2_y = 0.0;
                vidaBoss.vert3_y = 1.0;
                vidaBoss.vert4_y = 1.0;



    }

    else if(boss.qtdvidas==2){
                vidaBoss.vert1_x = vidaBoss.somador * vidaBoss.frameAtual;
                vidaBoss.vert2_x = vidaBoss.somador * vidaBoss.frameAtual + 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert3_x = vidaBoss.somador * vidaBoss.frameAtual+ 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert4_x = vidaBoss.somador * vidaBoss.frameAtual;

                vidaBoss.vert1_y = 0.0;
                vidaBoss.vert2_y = 0.0;
                vidaBoss.vert3_y = 1.0;
                vidaBoss.vert4_y = 1.0;



    }
    else if(boss.qtdvidas==1){
                vidaBoss.vert1_x = vidaBoss.somador* vidaBoss.frameAtual;
                vidaBoss.vert2_x = vidaBoss.somador * vidaBoss.frameAtual + 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert3_x = vidaBoss.somador * vidaBoss.frameAtual + 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert4_x = vidaBoss.somador * vidaBoss.frameAtual;

                vidaBoss.vert1_y = 0.0;
                vidaBoss.vert2_y = 0.0;
                vidaBoss.vert3_y = 1.0;
                vidaBoss.vert4_y = 1.0;
}
    else if(boss.qtdvidas==0){
                vidaBoss.vert1_x = vidaBoss.somador * vidaBoss.frameAtual;
                vidaBoss.vert2_x = vidaBoss.somador * vidaBoss.frameAtual + 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert3_x = vidaBoss.somador * vidaBoss.frameAtual + 1/vidaBoss.qtdTotalFrame;
                vidaBoss.vert4_x = vidaBoss.somador * vidaBoss.frameAtual;

                vidaBoss.vert1_y = 0.0;
                vidaBoss.vert2_y = 0.0;
                vidaBoss.vert3_y = 1.0;
                vidaBoss.vert4_y = 1.0;
}

    glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
    glBindTexture(GL_TEXTURE_2D,id_vidaBoss);
    
    glPushMatrix();

    glTranslatef(50, 95, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(vidaBoss.vert1_x, vidaBoss.vert1_y);
        glVertex2f(-4, -2.0); // v3---v2

        glTexCoord2f(vidaBoss.vert2_x, vidaBoss.vert2_y);
        glVertex2f(4, -2.0); // |     |

        glTexCoord2f(vidaBoss.vert3_x, vidaBoss.vert3_y);
        glVertex2f(4, 2.0); // |     |

        glTexCoord2f(vidaBoss.vert4_x, vidaBoss.vert4_y);
        glVertex2f(-4, 2.0); // v0---v1

    glEnd();
   
    glPopMatrix();



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

    //if(posY_projetil+altura_projetil == posY_inimigo){
        //if(posX_projetil+largura_projetil/2 >= posX_inimigo && posX_projetil+largura_projetil/2 <= posX_inimigo+largura_inimigo){
            //if(vivo){
                  //  return true;        
                //} 
    if(posY_projetil+altura_projetil>= posY_inimigo && posY_projetil+altura_projetil <= posY_inimigo+altura_inimigo){
        if(posX_projetil+largura_projetil/2 >= posX_inimigo && posX_projetil+largura_projetil/2 <= posX_inimigo+largura_inimigo){ 
              
                if(vivo){
                    return true;        
                }        
            }
        }    
      
    
   
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

void desenhaMenuPrincipal(){
    glColor3f(1.0,1.0,1.0);
    glEnable(GL_TEXTURE_2D);
    switch(escolha_no_menu){
        case 1:
            glBindTexture(GL_TEXTURE_2D, id_textura_menu_jogar);
            break;
        case 2:
            glBindTexture(GL_TEXTURE_2D, id_textura_menu_creditos);
            break;
        case 3:
            glBindTexture(GL_TEXTURE_2D, id_textura_menu_pontuacaomax);
            break;        
        case 4:
            glBindTexture(GL_TEXTURE_2D, id_textura_menu_sair);
            break;
        default:
            glBindTexture(GL_TEXTURE_2D, id_textura_menu);
            break;
        
    }
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

void desenhaSapin(float posX,float posY,float largura,float altura){
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
    
        if(sapin.frameAtual >= sapin.contadorDeFrame && sapin.frameAtual != sapin.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
            //printf("okok\n");
            sapin.vert1_x = 0.0 + sapin.somador * sapin.contadorDeFrame;
            sapin.vert2_x = 1/sapin.qtdTotalFrame + sapin.somador * sapin.contadorDeFrame;
            sapin.vert3_x = 1/sapin.qtdTotalFrame + sapin.somador* sapin.contadorDeFrame;
            sapin.vert4_x = 0.0 + sapin.somador * sapin.contadorDeFrame;

            sapin.vert1_y = 0.0;
            sapin.vert2_y = 0.0;
            sapin.vert3_y = 1.0;
            sapin.vert4_y = 1.0;  

            sapin.somador = 1/sapin.qtdTotalFrame;// O somador mais os vertice da a proxima imagem
            sapin.contadorDeFrame++;  
        }

        if(sapin.frameAtual > sapin.qtdTotalFrame){//volta para posicao inicial da imagem para fazer a animaçao dnv
            //printf("ok\n");
            sapin.frameAtual = 0;
            sapin.contadorDeFrame =  0;
            sapin.vert1_x = 0.0;
            sapin.vert2_x = 1/sapin.qtdTotalFrame;
            sapin.vert3_x = 1/sapin.qtdTotalFrame;
            sapin.vert4_x = 0.0;
            sapin.somador = 1/sapin.qtdTotalFrame;
         }

        sapin.frameAtual = sapin.frameAtual + sapin.velocidadeDoFrame;   

        glBindTexture(GL_TEXTURE_2D, id_textura_sapin);
    
        glPushMatrix();

        glTranslatef(posX, posY, 0);
    
        glBegin(GL_TRIANGLE_FAN);
                            
            glTexCoord2f(sapin.vert1_x, sapin.vert1_y); //
            glVertex3f(-largura/2, -altura/2,0); // v4---v3 // -15 ,-20

            glTexCoord2f(sapin.vert2_x, sapin.vert2_y); //
            glVertex3f( largura/2, -altura/2,0); // |     | // 15 ,-20
     
            glTexCoord2f(sapin.vert3_x, sapin.vert3_y); //
            glVertex3f( largura/2,  altura/2,0); // |     | // 15 , 20

            glTexCoord2f(sapin.vert4_x, sapin.vert4_y); //
            glVertex3f(-largura/2,  altura/2,0); // v1---v2 // -15, 20

    glEnd();
    
    glPopMatrix();
}

void desenhaCabecaNaruto(int posX,int posY, GLuint x){// Ainda em teste, pois a barra de vida nao esta tao bonita.
    
    //glColor3f(1.0,1.0,1.0);

    glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
    glBindTexture(GL_TEXTURE_2D,x);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(0, 0);
        glVertex2f(-3, -3); // v3---v2

        glTexCoord2f(1, 0);
        glVertex2f(3, -3); // |     |

        glTexCoord2f(1, 1);
        glVertex2f(3, 3); // |     |

        glTexCoord2f(0, 1);
        glVertex2f(-3, 3); // v0---v1

    glEnd();
   
    glPopMatrix();



}

void desenhaBarraNaruto(){// Ainda em teste, pois a barra de vida nao esta tao bonita.
    
    //glColor3f(1.0,1.0,1.0);
    if(personagem_principal.qtdvidas==3){
                vidaNaruto.vert1_x = vidaNaruto.somador * vidaNaruto.frameAtual;
                vidaNaruto.vert2_x = vidaNaruto.somador * vidaNaruto.frameAtual + 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert3_x = vidaNaruto.somador * vidaNaruto.frameAtual + 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert4_x = vidaNaruto.somador * vidaNaruto.frameAtual;

                vidaNaruto.vert1_y = 0.0;
                vidaNaruto.vert2_y = 0.0;
                vidaNaruto.vert3_y = 1.0;
                vidaNaruto.vert4_y = 1.0;



    }

    else if(personagem_principal.qtdvidas==2){
                vidaNaruto.vert1_x = vidaNaruto.somador * vidaNaruto.frameAtual;
                vidaNaruto.vert2_x = vidaNaruto.somador * vidaNaruto.frameAtual + 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert3_x = vidaNaruto.somador * vidaNaruto.frameAtual+ 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert4_x = vidaNaruto.somador * vidaNaruto.frameAtual;

                vidaNaruto.vert1_y = 0.0;
                vidaNaruto.vert2_y = 0.0;
                vidaNaruto.vert3_y = 1.0;
                vidaNaruto.vert4_y = 1.0;



    }
    else if(personagem_principal.qtdvidas==1){
                vidaNaruto.vert1_x = vidaNaruto.somador* vidaNaruto.frameAtual;
                vidaNaruto.vert2_x = vidaNaruto.somador * vidaNaruto.frameAtual + 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert3_x = vidaNaruto.somador * vidaNaruto.frameAtual + 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert4_x = vidaNaruto.somador * vidaNaruto.frameAtual;

                vidaNaruto.vert1_y = 0.0;
                vidaNaruto.vert2_y = 0.0;
                vidaNaruto.vert3_y = 1.0;
                vidaNaruto.vert4_y = 1.0;
}
    else if(personagem_principal.qtdvidas==0){
                vidaNaruto.vert1_x = vidaNaruto.somador * vidaNaruto.frameAtual;
                vidaNaruto.vert2_x = vidaNaruto.somador * vidaNaruto.frameAtual + 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert3_x = vidaNaruto.somador * vidaNaruto.frameAtual + 1/vidaNaruto.qtdTotalFrame;
                vidaNaruto.vert4_x = vidaNaruto.somador * vidaNaruto.frameAtual;

                vidaNaruto.vert1_y = 0.0;
                vidaNaruto.vert2_y = 0.0;
                vidaNaruto.vert3_y = 1.0;
                vidaNaruto.vert4_y = 1.0;
}

    glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
    glBindTexture(GL_TEXTURE_2D,id_textura_vidaNaruto);
    
    glPushMatrix();

    glTranslatef(11, 3, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(vidaNaruto.vert1_x, vidaNaruto.vert1_y);
        glVertex2f(-4, -2.0); // v3---v2

        glTexCoord2f(vidaNaruto.vert2_x, vidaNaruto.vert2_y);
        glVertex2f(4, -2.0); // |     |

        glTexCoord2f(vidaNaruto.vert3_x, vidaNaruto.vert3_y);
        glVertex2f(4, 2.0); // |     |

        glTexCoord2f(vidaNaruto.vert4_x, vidaNaruto.vert4_y);
        glVertex2f(-4, 2.0); // v0---v1

    glEnd();
   
    glPopMatrix();



}

void desenhaAuxPontuacaoCasa1(int auxPontuacao,int posX, int posY){

glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
    if(auxPontuacao%10==5){
        pontuacao.frameAtual=5;
        pontuacao.vert1_x = 0.0 + pontuacao.somador * pontuacao.frameAtual;
        pontuacao.vert2_x = 1/pontuacao.qtdTotalFrame + pontuacao.somador * pontuacao.frameAtual;
        pontuacao.vert3_x = 1/pontuacao.qtdTotalFrame + pontuacao.somador* pontuacao.frameAtual;
        pontuacao.vert4_x = 0.0 + pontuacao.somador * pontuacao.frameAtual;

        pontuacao.vert1_y = 0.0;
        pontuacao.vert2_y = 0.0;
        pontuacao.vert3_y = 1.0;
        pontuacao.vert4_y = 1.0;    

    }
    else if(auxPontuacao%10==0){
        pontuacao.frameAtual=0;
        pontuacao.vert1_x = 0.0 + pontuacao.somador * pontuacao.frameAtual;
        pontuacao.vert2_x = 1/pontuacao.qtdTotalFrame + pontuacao.somador * pontuacao.frameAtual;
        pontuacao.vert3_x = 1/pontuacao.qtdTotalFrame + pontuacao.somador* pontuacao.frameAtual;
        pontuacao.vert4_x = 0.0 + pontuacao.somador * pontuacao.frameAtual;

        pontuacao.vert1_y = 0.0;
        pontuacao.vert2_y = 0.0;
        pontuacao.vert3_y = 1.0;
        pontuacao.vert4_y = 1.0;    

    }
    
    glBindTexture(GL_TEXTURE_2D,id_textura_numeros);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(pontuacao.vert1_x, pontuacao.vert1_y);
        glVertex2f(-5, -5); // v3---v2

        glTexCoord2f(pontuacao.vert2_x, pontuacao.vert2_y);
        glVertex2f(5, -5); // |     |

        glTexCoord2f(pontuacao.vert3_x, pontuacao.vert3_y);
        glVertex2f(5, 5); // |     |

        glTexCoord2f(pontuacao.vert4_x, pontuacao.vert4_y);
        glVertex2f(-5, 5); // v0---v1

    glEnd();
   
    glPopMatrix();

}

void desenhaAuxPontuacaoCasa2(int auxPontuacao,int posX, int posY){

glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
        if((auxPontuacao%100)/10 == 0){
            pontuacao2.frameAtual=0;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 1){
            pontuacao2.frameAtual=1;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 2){
            pontuacao2.frameAtual=2;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 3){
            pontuacao2.frameAtual=3;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 4){
            pontuacao2.frameAtual=4;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 5){
            pontuacao2.frameAtual=5;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 0){
            pontuacao2.frameAtual=5;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 6){
            pontuacao2.frameAtual=6;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 7){
            pontuacao2.frameAtual=7;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 8){
            pontuacao2.frameAtual=8;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
        if((auxPontuacao%100)/10 == 9){
            pontuacao2.frameAtual=9;
            pontuacao2.vert1_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert2_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador * pontuacao2.frameAtual;
            pontuacao2.vert3_x = 1/pontuacao2.qtdTotalFrame + pontuacao2.somador* pontuacao2.frameAtual;
            pontuacao2.vert4_x = 0.0 + pontuacao2.somador * pontuacao2.frameAtual;

            pontuacao2.vert1_y = 0.0;
            pontuacao2.vert2_y = 0.0;
            pontuacao2.vert3_y = 1.0;
            pontuacao2.vert4_y = 1.0;    

        }
    
    glBindTexture(GL_TEXTURE_2D,id_textura_numeros);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(pontuacao2.vert1_x, pontuacao2.vert1_y);
        glVertex2f(-5, -5); // v3---v2

        glTexCoord2f(pontuacao2.vert2_x, pontuacao2.vert2_y);
        glVertex2f(5, -5); // |     |

        glTexCoord2f(pontuacao2.vert3_x, pontuacao2.vert3_y);
        glVertex2f(5, 5); // |     |

        glTexCoord2f(pontuacao2.vert4_x, pontuacao2.vert4_y);
        glVertex2f(-5, 5); // v0---v1

    glEnd();
   
    glPopMatrix();


}

void desenhaAuxPontuacaoCasa3(int auxPontuacao,int posX, int posY){

glEnable(GL_TEXTURE_2D); //comandos para ativar a textura colocada
    
        if(auxPontuacao/100 == 0){
            pontuacao3.frameAtual=0;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 1){
            pontuacao3.frameAtual=1;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 2){
            pontuacao3.frameAtual=2;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100== 3){
            pontuacao3.frameAtual=3;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 4){
            pontuacao3.frameAtual=4;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 5){
            pontuacao3.frameAtual=5;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 0){
            pontuacao3.frameAtual=5;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 6){
            pontuacao3.frameAtual=6;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 7){
            pontuacao3.frameAtual=7;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 8){
            pontuacao3.frameAtual=8;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
        if(auxPontuacao/100 == 9){
            pontuacao3.frameAtual=9;
            pontuacao3.vert1_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert2_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador * pontuacao3.frameAtual;
            pontuacao3.vert3_x = 1/pontuacao3.qtdTotalFrame + pontuacao3.somador* pontuacao3.frameAtual;
            pontuacao3.vert4_x = 0.0 + pontuacao3.somador * pontuacao3.frameAtual;

            pontuacao3.vert1_y = 0.0;
            pontuacao3.vert2_y = 0.0;
            pontuacao3.vert3_y = 1.0;
            pontuacao3.vert4_y = 1.0;    

        }
    
    glBindTexture(GL_TEXTURE_2D,id_textura_numeros);
    
    glPushMatrix();

    glTranslatef(posX, posY, 0);
    glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(pontuacao3.vert1_x, pontuacao3.vert1_y);
        glVertex2f(-5, -5); // v3---v2

        glTexCoord2f(pontuacao3.vert2_x, pontuacao3.vert2_y);
        glVertex2f(5, -5); // |     |

        glTexCoord2f(pontuacao3.vert3_x, pontuacao3.vert3_y);
        glVertex2f(5, 5); // |     |

        glTexCoord2f(pontuacao3.vert4_x, pontuacao3.vert4_y);
        glVertex2f(-5, 5); // v0---v1

    glEnd();
   
    glPopMatrix();


}





void desenhaMinhaCena(){
    glClear(GL_COLOR_BUFFER_BIT);    
	
    if(perdeu_ou_jogando_ou_ganhou==0){
    	
        if(fase<=0){
            desenhaMenuPrincipal();
            if(creditos_ou_pontuacao==0){
            	desenhaSapin(sapin_obj.posX, sapin_obj.posY, sapin_obj.largura, sapin_obj.altura);
            	sapin_obj.posX++;
            	if(sapin_obj.posX>100)sapin_obj.posX=0;
            }
            if(creditos_ou_pontuacao==1)desenhaFundo(id_textura_creditos);
            if(creditos_ou_pontuacao==-1){
            	int aux1=0,aux2=0;
            	desenhaFundo(id_textura_pontuacao_maxima);
            	FILE* auxiliar = fopen("data.txt", "r");
            	if(auxiliar!=NULL){
            		while(!feof(auxiliar)){
            			fscanf(auxiliar, "Pontos:(%d), Tempo: (%d)", &aux1, &aux2);  
            		}
            		fclose(auxiliar);	
            		desenhaAuxPontuacaoCasa1(aux1,32,65);
		    	desenhaAuxPontuacaoCasa2(aux1,24,65);
		    	desenhaAuxPontuacaoCasa3(aux1,16,65);
		    	desenhaAuxPontuacaoCasa1(aux2,82,65);
		    	desenhaAuxPontuacaoCasa2(aux2,74,65);
		    	desenhaAuxPontuacaoCasa3(aux2,66,65);
            	}
            	
            }
            
        }
        else{
            defineTexturas(fase);
            desenhaFundo(id_textura_fundo);
            desenhaPersonagemPrincipal();

            if(fase==1){
            	desenhaCabecaNaruto(3,4,id_textura_cabecanaruto);
            	desenhaBarraNaruto();
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
			        
			        pontuacao_total+=10; // QUANDO ACERTA 
			        
			        if(inimigo_primeira_fase.qtdvidas==0){
                                   inimigo_primeira_fase.vivo = false;
                               }                            
                                   shuriken.atirar = false;         
                                                                  }
                    shuriken.posY++;
                    if(shuriken.posY > 99){//QUando sair da tela
                        shuriken.atirar = false;  
                        pontuacao_total-=5; // QUANDO ERRA
                    }
             
                }
          
                if(kunai.atirar){
                    desenhaProjetil(2);
                    if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                               personagem_principal.posX, personagem_principal.posY,
                               personagem_principal.altura, personagem_principal.largura,
                               personagem_principal.qtdvidas)){
                                
                               personagem_principal.qtdvidas--;
                               pontuacao_total-=10; // QUANDO EH ACERTADO
                               kunai.atirar = false;
                               if(personagem_principal.qtdvidas ==2){
                                                vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                                vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                                             }  
                               else if(personagem_principal.qtdvidas ==1){
                                          vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                          vidaNaruto.somador= 1/vidaNaruto.qtdTotalFrame;
                               }
                               else if(personagem_principal.qtdvidas ==0){
                                        vidaNaruto.frameAtual= vidaNaruto.frameAtual+1;
                                        vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                             }

                               
                               }
                               kunai.posY--;
                               if(kunai.posY<0){
                                   kunai.atirar=false;
                               }            
                }        
                
            }else if(fase==2){
            	     desenhaCabecaNaruto(3,4,id_textura_cabecanaruto);
            	     desenhaBarraNaruto();	
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
                                            pontuacao_total+=10; // QUANDO ACERTA
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
                            pontuacao_total-=5; // QUANDO ERRA
                        }
                    }
                    if(kunai.atirar){
                        desenhaProjetil(2);
                        if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                               personagem_principal.posX, personagem_principal.posY,
                               personagem_principal.altura, personagem_principal.largura,
                               personagem_principal.qtdvidas)){
                                
                               personagem_principal.qtdvidas--;
                               pontuacao_total-=10; // QUANDO EH ACERTADO
                               kunai.atirar = false;
                               if(personagem_principal.qtdvidas ==2){
                                                vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                                vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                                             }  
                               else if(personagem_principal.qtdvidas ==1){
                                          vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                          vidaNaruto.somador= 1/vidaNaruto.qtdTotalFrame;
                               }
                               else if(personagem_principal.qtdvidas ==0){
                                        vidaNaruto.frameAtual= vidaNaruto.frameAtual+1;
                                        vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                             }
                               
                               }
                               kunai.posY--;
                               if(kunai.posY<0){
                                   kunai.atirar=false;
                               }               
                    
                    }
            } 
            else if(fase==3){
                desenhaCabecaNaruto(3,4,id_textura_cabecanaruto);
                desenhaBarraNaruto();
                desenhaNomeDoInimigo(10,98,id_textura_nome1);
                desenhaNomeDoInimigo(10,92,id_textura_nome2);
                desenhaNomeDoInimigo(90,98,id_textura_nome5);
                desenhaNomeDoInimigo(90,92,id_textura_nome4);
                desenhaNomeDoInimigo(50,98,id_textura_nome3);        
                            
                desenhaBarraDeVidaInimigo(10,95,1);
                desenhaBarraDeVidaInimigo(10,89,0);
                desenhaBarraDeVidaInimigo(90,95,4);
                desenhaBarraDeVidaInimigo(90,89,3);
                desenhaBarraDeVidaInimigo(50,95,2);
                
            
                criaVetorInimigos();
                
                if(shuriken.atirar){
                        desenhaProjetil(1);
                        for(int i=0;i<5;i++){
                               if(colisao(shuriken.posX,shuriken.posY, shuriken.largura,    
                                           shuriken.altura, vetor_de_inimigos[i].posX,
                                           vetor_de_inimigos[i].posY, vetor_de_inimigos[i].altura,
                                           vetor_de_inimigos[i].largura,vetor_de_inimigos[i].vivo)){
                                            
                                            vetor_de_inimigos[i].qtdvidas--;
                                            pontuacao_total+=10; // QUANDO ACERTA
                                        

                                            if(vetor_de_inimigos[i].qtdvidas ==1){
                                                vidaFase3.frameAtual_vetor[i] = vidaFase3.frameAtual_vetor[i]+1;
                                                vidaFase3.somador_vetor[i] = 1/vidaFase3.qtdTotalFrame;
                                             }  
                                            else if(vetor_de_inimigos[i].qtdvidas ==0){
                                                vidaFase3.frameAtual_vetor[i] = vidaFase3.frameAtual_vetor[i]+1;
                                                vidaFase3.somador_vetor[i] = 1/vidaFase3.qtdTotalFrame;
                                             }  


                        





			                                if(vetor_de_inimigos[i].qtdvidas==0){
                                                    vetor_de_inimigos[i].vivo = false;
                                            }                                                                                       
                                           shuriken.atirar = false;  
                                               
                                }
                            
                        }
                        shuriken.posY++;
                        if(shuriken.posY > 99){//QUando sair da tela
                            shuriken.atirar = false;  
                            pontuacao_total-=5; // QUANDO ERRA
                      
                        }
                    }
                if(kunai.atirar){
                        desenhaProjetil(2);
                        if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                               personagem_principal.posX, personagem_principal.posY,
                               personagem_principal.altura, personagem_principal.largura,
                               personagem_principal.qtdvidas)){
                                
                               personagem_principal.qtdvidas--;
                               pontuacao_total-=10; // QUANDO EH ACERTADO
                               kunai.atirar = false;
                               
                               if(personagem_principal.qtdvidas ==2){
                                                vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                                vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                                             }  
                               else if(personagem_principal.qtdvidas ==1){
                                          vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                          vidaNaruto.somador= 1/vidaNaruto.qtdTotalFrame;
                               }
                               else if(personagem_principal.qtdvidas ==0){
                                        vidaNaruto.frameAtual= vidaNaruto.frameAtual+1;
                                        vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                             }
                               
                               }
                               kunai.posY-=2;
                               if(kunai.posY<0){
                                   kunai.atirar=false;
                               }               
                    
                    }    
                
            }
            else if(fase==4){
                 desenhaCabecaNaruto(3,4,id_textura_cabecanaruto);
                 desenhaBarraNaruto();
            	 desenhaNomeDoInimigo(50,98,id_textura_nomeBoss);
            	 desenhaBarraBoss();
                desenhaInimigo(boss.posX,boss.posY,boss.altura,boss.largura);
                if(shuriken.atirar){
                        desenhaProjetil(1);
                        
                               if(colisao(shuriken.posX,shuriken.posY, shuriken.largura,    
                                           shuriken.altura, boss.posX,
                                           boss.posY, boss.altura,
                                           boss.largura,boss.vivo)){

                                            boss.qtdvidas--;
                                            pontuacao_total+=10;
                                            
                                            if(boss.qtdvidas ==2){
                                                vidaBoss.frameAtual = vidaBoss.frameAtual+1;
                                                vidaBoss.somador = 1/vidaBoss.qtdTotalFrame;
                                             }  
                                            else if(boss.qtdvidas ==1){
                                                vidaBoss.frameAtual = vidaBoss.frameAtual+1;
                                                vidaBoss.somador= 1/vidaBoss.qtdTotalFrame;
                                             }
						else if(boss.qtdvidas ==0){
                                                vidaBoss.frameAtual= vidaBoss.frameAtual+1;
                                                vidaBoss.somador = 1/vidaBoss.qtdTotalFrame;
                                             }

                                            
			                     if(boss.qtdvidas==0){
                                                    boss.vivo = false;
                                            }                                                                                       
                                           shuriken.atirar = false;  
                                               
                                }
                            
                       
                        shuriken.posY++;
                        if(shuriken.posY > 99){//QUando sair da tela
                            shuriken.atirar = false;  
                      	     pontuacao_total-=5; // QUANDO ERRA
                        }
                }
                if(kunai.atirar){
                    desenhaProjetil(2);
                    if(colisao_no_player(kunai.posX, kunai.posY, kunai.largura, kunai.altura,
                               personagem_principal.posX, personagem_principal.posY,
                               personagem_principal.altura, personagem_principal.largura,
                               personagem_principal.qtdvidas)){
                                
                               personagem_principal.qtdvidas--;
                               pontuacao_total-=10; // QUANDO EH ACERTADO
                               kunai.atirar = false;
                               if(personagem_principal.qtdvidas ==2){
                                                vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                                vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                                             }  
                               else if(personagem_principal.qtdvidas ==1){
                                          vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                          vidaNaruto.somador= 1/vidaNaruto.qtdTotalFrame;
                               }
                               else if(personagem_principal.qtdvidas ==0){
                                        vidaNaruto.frameAtual= vidaNaruto.frameAtual+1;
                                        vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                             }
                               
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
                                   pontuacao_total-=10;
                                   boss.dash = false;
                                   boss.posY=80;
                                   boss.posX=50;
                           if(personagem_principal.qtdvidas ==2){
                                                vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                                vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                             }  
                               else if(personagem_principal.qtdvidas ==1){
                                          vidaNaruto.frameAtual = vidaNaruto.frameAtual+1;
                                          vidaNaruto.somador= 1/vidaNaruto.qtdTotalFrame;
                               }
                               else if(personagem_principal.qtdvidas ==0){
                                        vidaNaruto.frameAtual= vidaNaruto.frameAtual+1;
                                        vidaNaruto.somador = 1/vidaNaruto.qtdTotalFrame;
                             	}
                               }
                               boss.posY--;
                               if(boss.posY<0){
                                   boss.dash=false;
                                   boss.posY=80;
                                   boss.posX=50;
                               }            
                }         
            
            } 
            
            if(pause_t)desenhaPause();

            frame_count++;
	        final_time = time(NULL);
	        if (final_time - initial_time > 0){
		        contador_fps = frame_count/(final_time-initial_time);
		        printf("FPS: %f\n", contador_fps);
		        frame_count = 0;
		        initial_time = final_time;
		        
	        }     
        }
    }
    else if(perdeu_ou_jogando_ou_ganhou==1){
        desenhaFundo(id_textura_win);    
    }
    else if(perdeu_ou_jogando_ou_ganhou==-1){
        desenhaFundo(id_textura_lose);    
    }
    glutSwapBuffers();   
}

void contadorFases(){
    int contador_de_inimigos_mortos=0;   
    if(fase==1){
        
        if(!inimigo_primeira_fase.vivo){
            fase++;      
            pontuacao_total+=100; // QUANDO PASSA DE FASE 
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
        //contador_de_inimigos_mortos=30; //PARA VERIFICAR 3° FASE DIRETO DPS DA PRIMEIRA
        if(contador_de_inimigos_mortos==30){
            fase++;
            pontuacao_total+=100; // QUANDO PASSA DE FASE
        }
        
        contador_de_inimigos_mortos = 0;   
    }
    
    else if(fase == 3){
            for(int i=0;i<5;i++){
                    if(vetor_de_inimigos[i].vivo == false){
                        contador_de_inimigos_mortos++;                
                    }
            }
            //contador_de_inimigos_mortos=5;
            if(contador_de_inimigos_mortos==5){
                fase++;            
                pontuacao_total+=100; // QUANDO PASSA DE FASE
            }
           
            contador_de_inimigos_mortos = 0;
    }
    if(fase == 4){
    	//boss.qtdvidas = 0;
        if(boss.qtdvidas==0){
            perdeu_ou_jogando_ou_ganhou = 1;
            pontuacao_total+=150; // QUANDO GANHA O JOGO
            if(verificaSAVE==0)
            salvar_pontuacao();
        }    
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

void salvar_pontuacao(){
	int aux_pontos, aux_tempo;
	if(access("data.txt",F_OK) != 0){		
		data = fopen("data.txt", "w");
		if(data==NULL)exit(1);
		fprintf(data,"Pontos:(%d), Tempo: (%d)", pontuacao_total, tempo_de_jogo);
		fclose(data);
		return; 
	}
	data = fopen("data.txt", "r");
	if(data==NULL)exit(1);	
	
	while(!feof(data)){
		fscanf(data, "Pontos:(%d), Tempo: (%d)", &aux_pontos, &aux_tempo); 
	}
	fclose(data);
	if(pontuacao_total>=aux_pontos){
		
			FILE* aux = fopen("data.txt", "w+");
			fprintf(aux,"Pontos:(%d), Tempo: (%d)", pontuacao_total, (tempo_de_jogo<aux_tempo)?tempo_de_jogo:aux_tempo);
			fclose(aux);		
	}
	verificaSAVE=1;
}

void teclaPressionada(unsigned char tecla, int x, int y){
    switch(tecla){
        case 27: //Esc
            if(pause_t){
                pause_t=false;                
                fase = 0;                 
                glutTimerFunc(1000/33,gameloop,1); 
            }
            else if(escolha_no_menu==2 && creditos_ou_pontuacao==1){
                creditos_ou_pontuacao = 0;           
            }
            else if(escolha_no_menu==3 && creditos_ou_pontuacao==-1){
            	creditos_ou_pontuacao = 0;
            }
            else exit(0);

            break;
        case 32: // espaço
            if(fase>0){
                if(!shuriken.atirar){
                    shuriken.posX  = personagem_principal.posX;
                    shuriken.posY  = personagem_principal.posY;
                    shuriken.atirar = true;
                    naruto.frameAtual = 17;
                    naruto.contadorDeFrame=17;
                    estado = 3;
                    glutPostRedisplay();
                }
            }
            else if(fase<=0){
                switch(escolha_no_menu){
                    case 1:
                        reiniciar();
                        break;
                    case 2:
                        creditos_ou_pontuacao = 1; // Quando eh 1 credito
                        break;
                    case 3:
                        creditos_ou_pontuacao = -1; // Quando eh -1 pontuacao max
                        break;        
                    case 4:
                        exit(0);
                        break;
                    default:
                        break;
                }            
            }

            break; 
        case 'p':
        case 'P':
            if(fase>0){
                if(!pause_t){
                    pause_t = true;    
                  
                    break;            
                }else{
                    pause_t = false;
                    glutTimerFunc(1000/33,gameloop,1);  
                    break;
                }
            }
            break; 
        case 'r':
        case 'R':
            if(fase>0){
                if(pause_t){
                    pause_t = false;   
                    reiniciar();  
                    glutTimerFunc(1000/33,gameloop,1);             
                }
                reiniciar();
            }
            break; 
        case 'b':
        case 'B':
            if(perdeu_ou_jogando_ou_ganhou!=0){
       		fase=0;
       		perdeu_ou_jogando_ou_ganhou=0;
       		setup();
       		glutPostRedisplay();
                        
            } 
          
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
        
        case GLUT_KEY_UP:
            if(fase<=0)if(escolha_no_menu>0)escolha_no_menu --;
            break;
        case GLUT_KEY_DOWN:
            if(fase<=0)if(escolha_no_menu<5)escolha_no_menu++;
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
                tobi.frameAtual = 12;
                tobi.contadorDeFrame =  12;
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
                tobi.frameAtual = 17;
                tobi.contadorDeFrame =  17;
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

void verificaSePerdeu(){
    if(personagem_principal.qtdvidas==0 && perdeu_ou_jogando_ou_ganhou != -1){
        perdeu_ou_jogando_ou_ganhou=-1;
    }
    if(fase==1 && perdeu_ou_jogando_ou_ganhou != -1){
        if(inimigo_primeira_fase.posY <= 10){
            perdeu_ou_jogando_ou_ganhou = -1;
        }
    }
    if(fase == 2 && perdeu_ou_jogando_ou_ganhou != -1){ // AQUI
        for(int i=0;i<3;i++){
            for(int j=0;j<10;j++){
                if(matriz_inimigos[i][j].vivo==true && matriz_inimigos[i][j].posY<=10){
                        //printf("meu pau");
                        perdeu_ou_jogando_ou_ganhou = -1;      
                        break;                            
                }        
            }
        }    
    }
}

void gameloop(int tempo){
    contadorFases();
    
    relogio();
    if(fase==1)movimentoInimigoPrimeiraFase();
    else if(fase==2)movimentoInimigoSegundaFase();
    else if(fase==3)movimentoInimigoTerceiraFase();
    else if(fase==4)movimentoInimigoUltimaFase();
    
    if(!pause_t){      
        glutPostRedisplay(); // PEDE PARA A CENA SER REDESENHADA ASSIM QUE POSSIVEL 
        glutTimerFunc(1000/33,gameloop,0); // CHAMA NOVAMENTE A FUNÇÃO DE ATT A TELA (recursividade).
         
    }else{
        desenhaPause();           
        glutPostRedisplay(); 
         
    }
    verificaSePerdeu();
    
}

void relogio(){
		tempo++;
		tempo_de_jogo++;
		if(tempo>tempo_limite){
			tempo = 0;
		}
	
}


void defineAtributos(){
   
    verificaSAVE=0;	
    perdeu_ou_jogando_ou_ganhou=0;
    
    pontuacao_total = 0;
    tempo_de_jogo = 0;		
		
    tempo=0;
    tempo_limite = 100;

    sapin_obj.posX = 3;	
    sapin_obj.posY = 10;	
    sapin_obj.largura = 15;
    sapin_obj.altura = 15;	

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
    inimigo_aux_fase3.posY = 70;
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
    boss.qtdvidas = 3;
    boss.dash =false;

    shuriken.largura = 4;
    shuriken.altura = 4;
    shuriken.atirar = false;

    for(int i=0;i<3;i++){
        for(int j = 0;j<10;j++){
            matriz_inimigos[i][j].vivo = true;   
            matriz_inimigos[i][j].qtdvidas=1;
            matriz_inimigos[i][j].dash = false; 
            matriz_inimigos[i][j].posY=80;    
        }    
    }

    for(int i=0;i<5;i++){
        vetor_de_inimigos[i].vivo = true;
        vetor_de_inimigos[i].qtdvidas=2;
        vetor_de_inimigos[i].dash=false;
        vidaFase3.frameAtual_vetor[i]=0;
        vidaFase3.somador_vetor[i]=0;

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

    hidan.frameAtual = 0;
    hidan.somador = 0;
    hidan.contadorDeFrame = 0;
    hidan.qtdTotalFrame=12;
    hidan.velocidadeDoFrame = 1.0;
    
    deidara.frameAtual = 0;
    deidara.somador = 0;
    deidara.contadorDeFrame = 0;
    deidara.qtdTotalFrame=4;
    deidara.velocidadeDoFrame = 0.4;
    
    pain.frameAtual = 0;
    pain.somador = 0;
    pain.contadorDeFrame = 0;
    pain.qtdTotalFrame=16;
    pain.velocidadeDoFrame = 0.8;
    
    kisame.frameAtual = 0;
    kisame.somador = 0;
    kisame.contadorDeFrame = 0;
    kisame.qtdTotalFrame=10;
    kisame.velocidadeDoFrame = 0.6;

    sasore.frameAtual = 0;
    sasore.somador = 0;
    sasore.contadorDeFrame = 0;
    sasore.qtdTotalFrame=12;
    sasore.velocidadeDoFrame = 0.8;

    vidaFase3.qtdTotalFrame=3;
    vidaFase3.contadorDeFrame = 0;

    tobi.frameAtual = 0;
    tobi.somador = 0;
    tobi.contadorDeFrame = 0;
    tobi.qtdTotalFrame=22;
    tobi.velocidadeDoFrame = 0.4;

    vidaBoss.qtdTotalFrame=4;
    vidaBoss.contadorDeFrame = 0;
    vidaBoss.frameAtual=0;
    vidaBoss.somador=0;
    
    sapin.frameAtual = 0;
    sapin.somador = 0;
    sapin.contadorDeFrame = 0;
    sapin.qtdTotalFrame=4;
    sapin.velocidadeDoFrame = 0.1;
    
    vidaNaruto.qtdTotalFrame=4;
    vidaNaruto.contadorDeFrame = 0;
    vidaNaruto.frameAtual=0;
    vidaNaruto.somador=0;
 
    pontuacao.qtdTotalFrame = 10;
    pontuacao.somador = 1/pontuacao.qtdTotalFrame;
    

    pontuacao2.qtdTotalFrame = 10;
    pontuacao2.somador = 1/pontuacao2.qtdTotalFrame;
    

    pontuacao3.qtdTotalFrame = 10;
    pontuacao3.somador = 1/pontuacao3.qtdTotalFrame;
    
	 
 
    creditos_ou_pontuacao = 0;
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
