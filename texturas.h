GLuint id_textura_personagem_principal;
GLuint id_textura_fundo;
GLuint id_textura_inimigo;
GLuint id_textura_projetil;

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


void defineTexturas(){
    id_textura_personagem_principal = carregaTextura("unnamed.png");
    id_textura_fundo = carregaTextura("folha.png");
    id_textura_inimigo = carregaTextura("zetsu.png");
    id_textura_projetil = carregaTextura("shuriken.png");
}


