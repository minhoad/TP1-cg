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
bool verificaFimDeFase();

Jogador personagem_principal;
Personagens inimigo;
Arma shuriken; // aliado
Arma kunai; // inimigo
formacao inimigo_primeira_fase;
formacao matriz_inimigos[3][10];
bool pause = false;
bool flag = true; // !=0
int fase=1;


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
            matriz_inimigos[i][j].posX = inimigo.posX;
            matriz_inimigos[i][j].posY = inimigo.posY;
            matriz_inimigos[i][j].altura = inimigo.altura;
            matriz_inimigos[i][j].largura = inimigo.largura;
            if(matriz_inimigos[i][j].vivo==true)            
                desenhaInimigo(inimigo.posX,inimigo.posY,inimigo.largura,inimigo.altura);
            inimigo.posX+=7;          
        }    
        inimigo.posX -= 70;// settando novamente pra posição inicial pra fazer outra fileira
        inimigo.posY+=7;
    }
    inimigo.posY = 80;
    
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
            //if(qtdvidas>0){
                return true;        
           // }        
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

                           inimigo_primeira_fase.vivo = false;                            
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
                       if(kunai.posY<8){
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

                                   matriz_inimigos[i][j].vivo = false;                            
                                   shuriken.atirar = false;         
                                                                  }
                    }
                }
                shuriken.posY++;
                if(shuriken.posY > 99){//QUando sair da tela
                    shuriken.atirar = false;  
                }
            }
    }  
    if(pause)desenhaPause();
         
    //if(verificaFimDeFase())     
    
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
        if(contador_de_inimigos_mortos==30){
            fase++;
        }   
    }
    contador_de_inimigos_mortos = 0;
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
    setup();
    criaMatrizInimigos(); 
}

void teclaIPressionada(int tecla, int x, int y){
    switch(tecla){
        case GLUT_KEY_RIGHT: // Seta para a direita ->
            if(personagem_principal.posX < 90){
                personagem_principal.posX++;        
            }
            
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: // Seta para a esquerda <-
            if(personagem_principal.posX > 10){
                personagem_principal.posX--;        
            }
            glutPostRedisplay();
            break;
        
        default:
            break;
        }
}


void movimentoInimigoSegundaFase(){
    if(flag){
        if(inimigo.posX <34){
            inimigo.posX++;        
        }
        else{
            flag = !flag;        
                  
        }
    }
    else{
        if(inimigo.posX>3){
            inimigo.posX--;
        }
        else{
                       
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
        else
            flag=!flag;
        
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
        else
            flag=!flag;
    }

}

void gameloop(int tempo){
// DELIMITA ATÉ ONDE A TROPA VAI
    contadorFases();
    if(fase==1)movimentoInimigoPrimeiraFase();
    else if(fase==2)movimentoInimigoSegundaFase();
// "BORDA" DA TELA
    
    if(!pause){      
        glutPostRedisplay(); // PEDE PARA A CENA SER REDESENHADA ASSIM QUE POSSIVEL 
        glutTimerFunc(1000/33,gameloop,1); // CHAMA NOVAMENTE A FUNÇÃO DE ATT A TELA (recursividade).
         
    }else{
        desenhaPause();           
        glutPostRedisplay(); 
         
    }
  
}



void defineAtributos(){
    personagem_principal.posX = 50;
    personagem_principal.posY = 10;
    personagem_principal.largura = 8;
    personagem_principal.altura = 8;
    personagem_principal.qtdvidas = 3;

    inimigo.posX = 7;
    inimigo.posY = 80;
    inimigo.largura = 7;
    inimigo.altura = 7;
    
    kunai.largura = 4;
    kunai.altura = 4;
    kunai.atirar = false;
    kunai.posY = 80;

    inimigo_primeira_fase.posX=50;
    inimigo_primeira_fase.posY = 80;
    inimigo_primeira_fase.largura = 10;
    inimigo_primeira_fase.altura = 10;
    inimigo_primeira_fase.vivo = true;

    shuriken.largura = 4;
    shuriken.altura = 4;
    shuriken.atirar = false;

    for(int i=0;i<3;i++){
        for(int j = 0;j<10;j++){
            matriz_inimigos[i][j].vivo = true;        
        }    
    }
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
