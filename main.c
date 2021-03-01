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


Jogador personagem_principal;

Auxiliar_de_criacao_de_obj inimigo_aux;
Auxiliar_de_criacao_de_obj inimigo_aux_fase3;

Arma shuriken; // aliado
Arma kunai; // inimigo

//int contador_de_tiros;
//int maximo_de_tiros_na_tela_fase3 = 2;
int posicao_de_dash;

formacao inimigo_primeira_fase; // PRIMEIRA FASE
formacao matriz_inimigos[3][10]; // SEGUNDA FASE
formacao vetor_de_inimigos[5]; // TERCEIRA FASE

animacao kakashi;
animacao zetsu;

bool pause = false;

bool pode_dar_dash = true;
bool flag = true; // trocar a direção movimento dos inimigos
int fase=1;

int descida_fase2; 
//int descida_fase3 = 0;

//          IMPLEMENTAR
//int maximo_de_tiros_tela_fase2 = 2;         
//int contador_de_tiros_tela = 0;       

double frame_count = 0,initial_time, final_time, contador_fps=0; // para o contador de fps

void desenhaPersonagemPrincipal(){

    
    glColor3f(1,1,1);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id_textura_personagem_principal);
    glPushMatrix();
    
    glTranslatef(personagem_principal.posX, personagem_principal.posY, 0);
    
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0);
        glVertex2f(-personagem_principal.largura/2, -personagem_principal.altura/2);

        glTexCoord2f(1,0);
        glVertex2f(personagem_principal.largura/2, -personagem_principal.altura/2);
        
        glTexCoord2f(1,1);
        glVertex2f(personagem_principal.largura/2, personagem_principal.altura/2);

        glTexCoord2f(0,1);
        glVertex2f(-personagem_principal.largura/2, personagem_principal.altura/2);

        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        
}

void desenhaInimigo(int posX,int posY,int largura,int altura){
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
    
            if(zetsu.frameAtual >= zetsu.qtdTotalFrame/2){//volta para posicao inicial da imagem para fazer a animaçao dnv
                //printf("ok\n");
                zetsu.frameAtual = 0;
                zetsu.contadorDeFrame =  0;
                zetsu.vert1_x = 0.0;
                zetsu.vert2_x = 1/zetsu.qtdTotalFrame;
                zetsu.vert3_x = 1/zetsu.qtdTotalFrame;
                zetsu.vert4_x = 0.0;
                zetsu.somador = 1/zetsu.qtdTotalFrame;
             }
        
    }
          
    if(!flag){
            if(zetsu.frameAtual >= zetsu.contadorDeFrame && zetsu.frameAtual != zetsu.contadorDeFrame){//Sempre que o FrameAtual for igual a qtdDeFrame passa para a proxima imagem
                printf("%f\n",zetsu.contadorDeFrame);
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
            
            if(zetsu.frameAtual >= zetsu.qtdTotalFrame){//volta para posicao inicial da imagem para fazer a animaçao dnv
                //printf("ok\n");
                zetsu.frameAtual = (zetsu.qtdTotalFrame/2)-zetsu.velocidadeDoFrame;
                zetsu.contadorDeFrame =  (zetsu.qtdTotalFrame/2)-zetsu.velocidadeDoFrame;
                zetsu.somador = 1/zetsu.qtdTotalFrame;
                zetsu.vert1_x = zetsu.somador *zetsu.contadorDeFrame;
                zetsu.vert2_x = 1/zetsu.qtdTotalFrame*zetsu.contadorDeFrame;
                zetsu.vert3_x = 1/zetsu.qtdTotalFrame*zetsu.contadorDeFrame;
                zetsu.vert4_x = zetsu.somador *zetsu.contadorDeFrame;
                
             }
            
    }


        zetsu.frameAtual = zetsu.frameAtual + zetsu.velocidadeDoFrame;    

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


    }else{
    if(fase == 4)glBindTexture(GL_TEXTURE_2D, id_textura_inimigo);
    
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
       
}}

void desenhaDashInimigo(int posX,int posY, int altura,int largura){
    glColor3f(1,1,1);
    
    //glEnable(GL_TEXTURE_2D);

    switch(posicao_de_dash){
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
       
}


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
        glBindTexture(GL_TEXTURE_2D, id_textura_projetil);
        glPushMatrix();

        glTranslatef(shuriken.posX,shuriken.posY,0);
        
        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(0,0);
            glVertex2f(-shuriken.largura/2, -shuriken.altura/2);

            glTexCoord2f(1,0);
            glVertex2f(shuriken.largura/2, -shuriken.altura/2);
            
            glTexCoord2f(1,1);
            glVertex2f(shuriken.largura/2, shuriken.altura/2);

            glTexCoord2f(0,1);
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
                if(vetor_de_inimigos[i].dash == false){
                    desenhaInimigo(inimigo_aux_fase3.posX,inimigo_aux_fase3.posY,inimigo_aux_fase3.largura,inimigo_aux_fase3.altura);
                }
            }
        
        inimigo_aux_fase3.posX+=10;
    }
    inimigo_aux_fase3.posX-=50;
}

bool colisao(int posX_projetil,
            int posY_projetil,
            int largura_projetil,
            int altura_projetil, 
            int posX_inimigo, 
            int posY_inimigo, 
            int altura_inimigo, 
            int largura_inimigo,
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

bool colisao_no_player(int posX_projetil,
            int posY_projetil,
            int largura_projetil,
            int altura_projetil, 
            int posX_inimigo, 
            int posY_inimigo, 
            int altura_inimigo, 
            int largura_inimigo,
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
            desenhaInimigo(inimigo_primeira_fase.posX,inimigo_primeira_fase.posY,inimigo_primeira_fase.altura,inimigo_primeira_fase.largura);                        
        
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
        if(vetor_de_inimigos[posicao_de_dash].dash==true){
            Auxiliar_de_criacao_de_obj aux;  
            int a = posicao_de_dash;         
            aux.posX = vetor_de_inimigos[posicao_de_dash].posX;
            aux.posY =vetor_de_inimigos[posicao_de_dash].posY;
            aux.altura =vetor_de_inimigos[posicao_de_dash].altura;
            aux.largura =vetor_de_inimigos[posicao_de_dash].largura;            

    
            desenhaDashInimigo(aux.posX,
                                aux.posY,
                                aux.altura,
                                aux.largura);

                if(colisao_no_player(aux.posX,
                                    aux.posY,
                                    aux.largura,
                                    aux.altura,
                                    personagem_principal.posX, 
                                    personagem_principal.posY,
                                    personagem_principal.altura, 
                                    personagem_principal.largura,
                                    personagem_principal.qtdvidas)){
                    
                    personagem_principal.qtdvidas--;
                    vetor_de_inimigos[a].dash = false;
                    pode_dar_dash = true;

                }
                aux.posY-=2;
                if(aux.posY<0){
                               vetor_de_inimigos[a].dash=false;
                               pode_dar_dash = true;
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
    
    //else if(fase == 3){
            
    
    //}
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
    //glutPostRedisplay();
    id_textura_personagem_principal=0;
    id_textura_fundo=0;
    id_textura_inimigo=0;
    id_textura_projetil=0;
    id_pause=0;
    id_textura_projetil_inimigo=0;
    contador_vezes_carrega_textura=1;
    glutPostRedisplay();
}

void teclaIPressionada(int tecla, int x, int y){
    switch(tecla){
        case GLUT_KEY_RIGHT: // Seta para a direita ->
            if(personagem_principal.posX < 90){
                personagem_principal.posX++;        
            }
            break;
        case GLUT_KEY_LEFT: // Seta para a esquerda <-
            if(personagem_principal.posX > 10){
                personagem_principal.posX--;        
            }
            break;
        default:
            break;
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

int dashInimigo(){
    int aux;
    aux = projetilrandom_fase3();
    vetor_de_inimigos[aux].dash = true;
    return aux;
}

void movimentoInimigoTerceiraFase(){
    int aux, contador_de_tiros_dados=0;
    if(flag){
        if(inimigo_aux_fase3.posX < 57){
            
            if(kunai.atirar==false){
                aux = projetilrandom_fase3();
                kunai.posX = vetor_de_inimigos[aux].posX;
                kunai.posY = vetor_de_inimigos[aux].posY;       
                kunai.atirar = true; 
                contador_de_tiros_dados++;        
                glutPostRedisplay();
            }
            inimigo_aux_fase3.posX++;
            if(contador_de_tiros_dados%10==0 && pode_dar_dash){
                posicao_de_dash = dashInimigo();  
                pode_dar_dash = !pode_dar_dash;
            }
           
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
            if(contador_de_tiros_dados%10==0 && pode_dar_dash){ // true
                posicao_de_dash = dashInimigo();
                pode_dar_dash = !pode_dar_dash;  
                          
            }
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
            if(inimigo_aux.posX%5==0 && kunai.atirar==false ){//contador_de_tiros_tela < maximo_de_tiros_tela_fase2){               
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
        
            if(inimigo_aux.posX%5==0 && kunai.atirar==false ){//contador_de_tiros_tela < maximo_de_tiros_tela_fase2){
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

            if(inimigo_primeira_fase.posX%14==0 && kunai.atirar == false){
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

            if(inimigo_primeira_fase.posX%14==0 && kunai.atirar == false){ // contador de tiros 

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
    if(fase==1)movimentoInimigoPrimeiraFase();
    else if(fase==2)movimentoInimigoSegundaFase();
    else if(fase==3)movimentoInimigoTerceiraFase();
    
    if(!pause){      
        glutPostRedisplay(); // PEDE PARA A CENA SER REDESENHADA ASSIM QUE POSSIVEL 
        glutTimerFunc(1000/33,gameloop,0); // CHAMA NOVAMENTE A FUNÇÃO DE ATT A TELA (recursividade).
         
    }else{
        desenhaPause();           
        glutPostRedisplay(); 
         
    }
  
}

int relogio(int tempo, int tempo_limite, bool crescente){
	if(crescente){
		tempo++;
		if(tempo>tempo_limite){
			tempo = 0;
		}
	}else{
		tempo--;
		if(tempo<0){
			tempo = tempo_limite;
		}
	}
	return tempo;
}


void defineAtributos(){
    //contador_de_tiros=0;

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
