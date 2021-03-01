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
int contador_vezes_carrega_textura=1;
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
        case 1:
            if(contador_vezes_carrega_textura==1){
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
              	 id_textura_inimigo0 = carregaTextura("deidara.png");  
              	 id_textura_inimigo1 = carregaTextura("sasore.png"); 
              	 id_textura_inimigo2 = carregaTextura("pain.png"); 
              	 id_textura_inimigo3 = carregaTextura("konan.png"); 
              	 id_textura_inimigo4 = carregaTextura("hidan.png"); 
                 contador_vezes_carrega_textura++;
            }
            break;
        case 4:
            if(contador_vezes_carrega_textura==4){
                id_textura_fundo = carregaTextura("fundo4.png"); 
                id_textura_inimigo = carregaTextura("konan.png");  
                contador_vezes_carrega_textura++;
            }
        default:
            break;
    }
}


