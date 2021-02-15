#include<SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<stdlib.h>
#include<stdio.h>
#include"global.h"

Personagens personagem_principal;
GLuint id_textura_personagem_principal;
GLuint id_textura_fundo;

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
        glFlush();
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


void desenhaMinhaCena(){
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaFundo();
    //glClear(GL_COLOR_BUFFER_BIT);
    desenhaPersonagemPrincipal();
    glFlush();
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
        default:
            break;        
    }
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

void setup(){
    glClearColor(0,0,0,0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    id_textura_personagem_principal = carregaTextura("unnamed.png");
    id_textura_fundo = carregaTextura("folha.png");

    personagem_principal.posX = 50;
    personagem_principal.posY = 20;
    personagem_principal.largura = 10;
    personagem_principal.altura = 10;
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

    setup();
    glutMainLoop();
    return 0;
}
