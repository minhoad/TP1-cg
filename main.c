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


Jogador personagem_principal;

Auxiliar_de_criacao_de_obj inimigo_aux;
Auxiliar_de_criacao_de_obj inimigo_aux_fase3;

Arma shuriken; // aliado
Arma kunai; // inimigo
formacao inimigo_primeira_fase; // PRIMEIRA FASE
formacao matriz_inimigos[3][10]; // SEGUNDA FASE
formacao vetor_de_inimigos[5]; // TERCEIRA FASE
bool pause = false;
bool flag = true; // trocar a direção movimento dos inimigos
int fase=1;
int descida_fase2 = 0; 
int descida_fase3 = 0;

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

/*void criaVetorInimigos(){
    for(int i=0;i<5;i++){
        vetor_de_inimigos[i].posX = inimigo_aux_fase3.posX;
        vetor_de_inimigos[i].posY = inimigo_aux_fase3.posY;
        vetor_de_inimigos[i].altura = inimigo_aux_fase3.altura;
        vetor_de_inimigos[i].largura = inimigo_aux_fase3.largura;
        if(vetor_de_inimigos[i].vivo==true){
            contador_de_inimigos=i;
            desenhaInimigo(inimigo_aux.posX,inimigo_aux.posY,inimigo_aux.largura,inimigo_aux.altura);
        }
        inimigo_aux_fase3.posX+=10;
    }
    inimigo_aux_fase3.posY = 80 - descida_fase3;
}*/

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
    /*else if(fase==3){
        criaVetorInimigos();    
    } */
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
        if(contador_de_inimigos_mortos==30){
            fase++;
        }
        contador_de_inimigos_mortos = 0;   
    }
    
    else if(fase == 3){
            
    
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
    glutPostRedisplay();
    id_textura_personagem_principal=0;
    id_textura_fundo=0;
    id_textura_inimigo=0;
    id_textura_projetil=0;
    id_pause=0;
    id_textura_projetil_inimigo=0;
    contador_vezes_carrega_textura=1;
}

void teclaIPressionada(int tecla, int x, int y){
    switch(tecla){
        case GLUT_KEY_RIGHT: // Seta para a direita ->
            if(personagem_principal.posX < 90){
                personagem_principal.posX++;        
            }
            
            //glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: // Seta para a esquerda <-
            if(personagem_principal.posX > 10){
                personagem_principal.posX--;        
            }
            //glutPostRedisplay();
            break;
        
        default:
            break;
        }
}

/*void movimentoInimigoTerceiraFase(){
    if(flag){
        if(inimigo_aux.posX <34){
            inimigo_aux_fase3.posX++;
        }
        else{
            descida_fase3++;
            flag = !flag;        
        }
    }
    else{
        if(inimigo_aux.posX >3){
            inimigo_aux_fase3.posX--;
        }
        else{
            descida_fase3++;
            flag = !flag;
        }    
    }

}*/

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

bool verificaPosicaoMorta(int x, int y){// aq
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
    while(verificaPosicaoMorta(aux,linha)){
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
    //else if(fase==3)movimentoInimigoTerceiraFase();
    
    if(!pause){      
        glutPostRedisplay(); // PEDE PARA A CENA SER REDESENHADA ASSIM QUE POSSIVEL 
        glutTimerFunc(1000/33,gameloop,0); // CHAMA NOVAMENTE A FUNÇÃO DE ATT A TELA (recursividade).
         
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

    inimigo_aux.posX = 7;
    inimigo_aux.posY = 80;
    inimigo_aux.largura = 7;
    inimigo_aux.altura = 7;

     
    inimigo_aux_fase3.posX = 10;
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

    shuriken.largura = 4;
    shuriken.altura = 4;
    shuriken.atirar = false;

    for(int i=0;i<3;i++){
        for(int j = 0;j<10;j++){
            matriz_inimigos[i][j].vivo = true;        
        }    
    }

    for(int i=0;i<5;i++)vetor_de_inimigos[i].vivo = true;
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
