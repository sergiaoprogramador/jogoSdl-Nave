    // Universidade do Estado de Mato Grosso - UNEMAT
    // Bacharelado em Sistemas de Informação
    // Professor Tales Nereu Bogoni - tales@unemat.br
    // Exemplo de Jogo2d para ser melhorado na disciplina de Algoritmos II
    // Para complementar o jogo podem ser utilizados os tutoriais disponíveis em http://lazyfoo.net/tutorials/SDL/

    #include "SDL2/SDL.h"
    #include "SDL2/SDL_opengl.h"
    #include "SDL2/SDL_image.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include <time.h>
    #define LARGURA 800
    #define ALTURA 600
    #define INIMIGO 28 //Valor constante para quantidade de inimigo
    SDL_Window *janelaprincipal = NULL; // nome da janela principal do jogo
    SDL_Surface *content = NULL; // área de trabalho da janela

    SDL_Renderer *visualizacao;

    //usando para regenciar as teclas de interação com o jogo
    typedef struct{
        bool esquerda;
        bool direita;
        bool espaco;
    } Teclas;

    Teclas teclas;

    void inicializaTeclas(){
        teclas.esquerda=false;
        teclas.direita=false;
        teclas.espaco=false;
    }



    typedef struct {
        SDL_Rect area; // cria um retângulo area.x, area.y, area.w (largurra), area.h (altura)
        float velocidade; // velocidade que o objeto se move
        SDL_Texture* textura=NULL; // textura da imagem
        bool morto = false;
    } Objeto;

    Objeto nave;
    Objeto background;
    Objeto tiro;
    Objeto inimigo[INIMIGO]; //Vetor de objeto inimigo


    bool tironatela;

    //diretivas do jogo
    bool fim=false; // encerra o jogo com true

    void carregaObjeto(Objeto *o, const char *caminho_da_imagem){
        o->area.w=64; //largura da nave
        o->area.h=64; //altura da nave
        SDL_Surface* imagem = IMG_Load(caminho_da_imagem); // le a imagem
        if( imagem == NULL ){
            printf( "Erro ao carregar nave %s\n", SDL_GetError() );
        }else {
            o->textura = SDL_CreateTextureFromSurface(visualizacao, imagem); // cria a textura
            SDL_FreeSurface(imagem); // apaga a imagem da tela
        }
    }

    //Função para carregar os objetos
    void carregaObjetos()
    {
        //Carrega as imagens
        carregaObjeto(&background,"imagens\\background.png");
        background.area.x=0;
        background.area.y=0;
        background.area.w=LARGURA;
        background.area.h=ALTURA;
        carregaObjeto(&nave,"imagens\\minhanave2.png");
        nave.area.x=LARGURA/2; //posicao x do meio da janela
        nave.area.y=ALTURA - nave.area.h - 1; // posiciona no fim da tela
        nave.velocidade = 8.0f;
        carregaObjeto(&tiro,"imagens\\tiro3.png");
        tiro.area.w=22;
        tiro.area.h=54;
        tiro.velocidade=14.0f;
    }

    void fase2(){
        carregaObjeto(&background,"imagens\\background2.png");
        background.area.x=0;
        background.area.y=0;
        background.area.w=LARGURA;
        background.area.h=ALTURA;

    }

    void criaInimigo(){
        carregaObjeto(&inimigo[0],"imagens\\ovni.png");
        inimigo[0].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[0].area.y= 0 ; // posiciona no fim da tela
        inimigo[0].velocidade = 1.0f;
    }

    void criaInimigo2(){
        carregaObjeto(&inimigo[1],"imagens\\ovni2.png");
        inimigo[1].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[1].area.y=0; // posiciona no fim da tela
        inimigo[1].velocidade = 1.0f;
    }

    void criaInimigo3(){
        carregaObjeto(&inimigo[2],"imagens\\ovni3.png");
        inimigo[2].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[2].area.y=0; // posiciona no fim da tela
        inimigo[2].velocidade = 1.0f;
    }
    void criaInimigo4(){
        carregaObjeto(&inimigo[3],"imagens\\ovni4.png");
        inimigo[3].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[3].area.y=0; // posiciona no fim da tela
        inimigo[3].velocidade = 1.0f;
    }
    void criaInimigo5(){
        carregaObjeto(&inimigo[4],"imagens\\ovni5.png");
        inimigo[4].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[4].area.y=0; // posiciona no fim da tela
        inimigo[4].velocidade = 1.0f;
    }

    void criaInimigo6(){
        carregaObjeto(&inimigo[5],"imagens\\ovni6.png");
        inimigo[5].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[5].area.y= 0 ; // posiciona no fim da tela
        inimigo[5].velocidade = 1.0f;
    }

    void criaInimigo7(){
        carregaObjeto(&inimigo[6],"imagens\\ovni20.png");
        inimigo[6].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[6].area.y= 0 ; // posiciona no fim da tela
        inimigo[6].velocidade = 2.0f;
    }

    void criaInimigo8(){
        carregaObjeto(&inimigo[7],"imagens\\ovni.png");
        inimigo[7].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[7].area.y=0; // posiciona no fim da tela
        inimigo[7].velocidade = 2.0f;
    }

    void criaInimigo9(){
        carregaObjeto(&inimigo[8],"imagens\\ovni2.png");
        inimigo[8].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[8].area.y=0; // posiciona no fim da tela
        inimigo[8].velocidade = 2.0f;
    }
    void criaInimigo10(){
        carregaObjeto(&inimigo[9],"imagens\\ovni3.png");
        inimigo[9].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[9].area.y=0; // posiciona no fim da tela
        inimigo[9].velocidade = 2.0f;
    }
    void criaInimigo11(){
        carregaObjeto(&inimigo[10],"imagens\\ovni4.png");
        inimigo[10].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[10].area.y=0; // posiciona no fim da tela
        inimigo[10].velocidade = 2.0f;
    }

    void criaInimigo12(){
        carregaObjeto(&inimigo[11],"imagens\\ovni5.png");
        inimigo[11].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[11].area.y= 0 ; // posiciona no fim da tela
        inimigo[11].velocidade = 2.0f;
    }

    void criaInimigo13(){
        carregaObjeto(&inimigo[12], "imagens\\ovni6.png");
        inimigo[12].area.x = rand() % 750; //posicao x do meio da janela
        inimigo[12].area.y = 0; // posiciona no fim da tela
        inimigo[12].velocidade = 2.0f;
    }

    void criaInimigo14(){
        carregaObjeto(&inimigo[13],"imagens\\ovni20.png");
        inimigo[13].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[13].area.y=0; // posiciona no fim da tela
        inimigo[13].velocidade = 3.0f;
    }

    void criaInimigo15(){
        carregaObjeto(&inimigo[14],"imagens\\ovni.png");
        inimigo[14].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[14].area.y=0; // posiciona no fim da tela
        inimigo[14].velocidade = 3.0f;
    }

    void criaInimigo16(){
        carregaObjeto(&inimigo[15],"imagens\\ovni2.png");
        inimigo[15].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[15].area.y= 0 ; // posiciona no fim da tela
        inimigo[15].velocidade = 3.0f;
    }

    void criaInimigo17(){
        carregaObjeto(&inimigo[16],"imagens\\ovni3.png");
        inimigo[16].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[16].area.y= 0 ; // posiciona no fim da tela
        inimigo[16].velocidade = 3.0f;
    }

    void criaInimigo18(){
        carregaObjeto(&inimigo[17],"imagens\\ovni4.png");
        inimigo[17].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[17].area.y=0; // posiciona no fim da tela
        inimigo[17].velocidade = 3.0f;
    }

    void criaInimigo19(){
        carregaObjeto(&inimigo[18],"imagens\\ovni5.png");
        inimigo[18].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[18].area.y=0; // posiciona no fim da tela
        inimigo[18].velocidade = 3.0f;
    }
    void criaInimigo20(){
        carregaObjeto(&inimigo[19],"imagens\\ovni6.png");
        inimigo[19].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[19].area.y=0; // posiciona no fim da tela
        inimigo[19].velocidade = 3.0f;
    }
    void criaInimigo21(){
        carregaObjeto(&inimigo[20],"imagens\\ovni20.png");
        inimigo[20].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[20].area.y=0; // posiciona no fim da tela
        inimigo[20].velocidade = 4.0f;
    }
    void criaInimigo22(){
        carregaObjeto(&inimigo[21],"imagens\\ovni.png");
        inimigo[21].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[21].area.y=0; // posiciona no fim da tela
        inimigo[21].velocidade = 4.0f;
    }

    void criaInimigo23(){
        carregaObjeto(&inimigo[22],"imagens\\ovni2.png");
        inimigo[22].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[22].area.y= 0 ; // posiciona no fim da tela
        inimigo[22].velocidade = 4.0f;
    }

    void criaInimigo24(){
        carregaObjeto(&inimigo[23],"imagens\\ovni3.png");
        inimigo[23].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[23].area.y= 0 ; // posiciona no fim da tela
        inimigo[23].velocidade = 4.0f;
    }
    void criaInimigo25(){
        carregaObjeto(&inimigo[24],"imagens\\ovni4.png");
        inimigo[24].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[24].area.y=0; // posiciona no fim da tela
        inimigo[24].velocidade = 4.0f;
    }
     void criaInimigo26(){
        carregaObjeto(&inimigo[25],"imagens\\ovni5.png");
        inimigo[25].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[25].area.y=0; // posiciona no fim da tela
        inimigo[25].velocidade = 4.0f;
    }
     void criaInimigo27(){
        carregaObjeto(&inimigo[26],"imagens\\ovni6.png");
        inimigo[26].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[26].area.y=0; // posiciona no fim da tela
        inimigo[26].velocidade = 4.0f;
    }
     void criaInimigo28(){
        carregaObjeto(&inimigo[27],"imagens\\ovni20.png");
        inimigo[27].area.x= rand() % 750; //posicao x do meio da janela
        inimigo[27].area.y=0; // posiciona no fim da tela
        inimigo[27].velocidade = 5.0f;
    }


    bool init()
    {
        bool success = true;

        //Inicializa a SDL
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "Erro ao carregar a SDL: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
                 //Cria a janela principal
            janelaprincipal = SDL_CreateWindow( "Meu Jogo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       LARGURA, ALTURA, SDL_WINDOW_SHOWN );
            if( janelaprincipal == NULL )
            {
                printf( "Erro na criação da janela: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                visualizacao = SDL_CreateRenderer(janelaprincipal, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            }
        }
        return success;

    }

    // função calculo de colisão
    bool colisao(float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bcomp, float Balt ){
        if (Ay+Aalt < By) return false;
        else if (Ay > By+Balt) return false;
        else if (Ax+Acomp < Bx) return false;
        else if (Ax > Bx+Bcomp) return false;

        return true; //     houve colisao
        }

    void desenhaNave(){
        SDL_RenderCopy(visualizacao,nave.textura,NULL, &nave.area);
    }

    void desenhaBackgound(){
        SDL_RenderCopy(visualizacao,background.textura,NULL, &background.area);
    }

    void detectaColisao2();
    void detectaColisao(){
        // executa função calculo de colisão
        if(inimigo[0].morto == false){
        if(colisao(inimigo[0].area.x, inimigo[0].area.y, inimigo[0].area.w, inimigo[0].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[0].morto = true;
            carregaObjeto(&inimigo[0],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[0].textura);
            criaInimigo2();
        }
        }

        if(inimigo[1].morto == false){
        if(colisao(inimigo[1].area.x, inimigo[1].area.y, inimigo[1].area.w, inimigo[1].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[1].morto = true;
            carregaObjeto(&inimigo[1],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[1].textura);
            criaInimigo3();
        }
        }

        if(inimigo[2].morto == false){
        if(colisao(inimigo[2].area.x, inimigo[2].area.y, inimigo[2].area.w, inimigo[2].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[2].morto = true;
            carregaObjeto(&inimigo[2],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[2].textura);
            criaInimigo4();
        }
        }

        if(inimigo[3].morto == false){
        if(colisao(inimigo[3].area.x, inimigo[3].area.y, inimigo[3].area.w, inimigo[3].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[3].morto = true;
            carregaObjeto(&inimigo[3],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[3].textura);
            criaInimigo5();
        }
        }

        if(inimigo[4].morto == false){
        if(colisao(inimigo[4].area.x, inimigo[4].area.y, inimigo[4].area.w, inimigo[4].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[4].morto = true;
            carregaObjeto(&inimigo[4],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[4].textura);
            criaInimigo6();
        }
        }

        if(inimigo[5].morto == false){
        if(colisao(inimigo[5].area.x, inimigo[5].area.y, inimigo[5].area.w, inimigo[5].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[5].morto = true;
            carregaObjeto(&inimigo[5],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[5].textura);
            criaInimigo7();
        }
        }

        if(inimigo[6].morto == false){
        if(colisao(inimigo[6].area.x, inimigo[6].area.y, inimigo[6].area.w, inimigo[6].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[6].morto = true;
            carregaObjeto(&inimigo[6],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[6].textura);
            criaInimigo8();
        }
        }

        if(inimigo[7].morto == false){
        if(colisao(inimigo[7].area.x, inimigo[7].area.y, inimigo[7].area.w, inimigo[7].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[7].morto = true;
            carregaObjeto(&inimigo[7],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[7].textura);
            criaInimigo9();
        }
        }

        if(inimigo[8].morto == false){
        if(colisao(inimigo[8].area.x, inimigo[8].area.y, inimigo[8].area.w, inimigo[8].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[8].morto = true;
            carregaObjeto(&inimigo[8],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[8].textura);
            criaInimigo10();
        }
        }

        if(inimigo[9].morto == false){
        if(colisao(inimigo[9].area.x, inimigo[9].area.y, inimigo[9].area.w, inimigo[9].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[9].morto = true;
            carregaObjeto(&inimigo[9],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[9].textura);
            criaInimigo11();
        }
        }

        if(inimigo[10].morto == false){
        if(colisao(inimigo[10].area.x, inimigo[10].area.y, inimigo[10].area.w, inimigo[10].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[10].morto = true;
            carregaObjeto(&inimigo[10],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[10].textura);
            criaInimigo12();
        }
        }

        if(inimigo[11].morto == false){
        if(colisao(inimigo[11].area.x, inimigo[11].area.y, inimigo[11].area.w, inimigo[11].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela = false;
            inimigo[11].morto = true;
            carregaObjeto(&inimigo[11],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[11].textura);
            criaInimigo13();
        }
        }

        if(inimigo[12].morto == false){
        if(colisao(inimigo[12].area.x, inimigo[12].area.y, inimigo[12].area.w, inimigo[12].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[12].morto = true;
            carregaObjeto(&inimigo[12],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[12].textura);
            criaInimigo14();
            fase2();
        }
        }

        if(inimigo[13].morto == false){
        if(colisao(inimigo[13].area.x, inimigo[13].area.y, inimigo[13].area.w, inimigo[13].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[13].morto = true;
            carregaObjeto(&inimigo[13],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[13].textura);
            criaInimigo15();
        }
        }

        if(inimigo[14].morto == false){
        if(colisao(inimigo[14].area.x, inimigo[14].area.y, inimigo[14].area.w, inimigo[14].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[14].morto = true;
            carregaObjeto(&inimigo[14],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[14].textura);
            criaInimigo16();
        }
        }
        //if(inimigo[0].morto && inimigo[1].morto && inimigo[2].morto && inimigo[3].morto
          // && inimigo[4].morto && inimigo[5].morto && inimigo[6].morto ){
           //}
           detectaColisao2();
    }

    void detectaColisao2(){

        if(inimigo[15].morto == false){
        if(colisao(inimigo[15].area.x, inimigo[15].area.y, inimigo[15].area.w, inimigo[15].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[15].morto = true;
            carregaObjeto(&inimigo[15],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[15].textura);
            criaInimigo17();
        }
        }

        if(inimigo[16].morto == false){
        if(colisao(inimigo[16].area.x, inimigo[16].area.y, inimigo[16].area.w, inimigo[16].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[16].morto = true;
            carregaObjeto(&inimigo[16],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[16].textura);
            criaInimigo18();
        }
        }

        if(inimigo[17].morto == false){
        if(colisao(inimigo[17].area.x, inimigo[17].area.y, inimigo[17].area.w, inimigo[17].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[17].morto = true;
            carregaObjeto(&inimigo[17],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[17].textura);
            criaInimigo19();
        }
        }

        if(inimigo[18].morto == false){
        if(colisao(inimigo[18].area.x, inimigo[18].area.y, inimigo[18].area.w, inimigo[18].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[18].morto = true;
            carregaObjeto(&inimigo[18],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[18].textura);
            criaInimigo20();
        }
        }

        if(inimigo[19].morto == false){
        if(colisao(inimigo[19].area.x, inimigo[19].area.y, inimigo[19].area.w, inimigo[19].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[19].morto = true;
            carregaObjeto(&inimigo[19],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[19].textura);
            criaInimigo21();
        }
        }

        if(inimigo[20].morto == false){
        if(colisao(inimigo[20].area.x, inimigo[20].area.y, inimigo[20].area.w, inimigo[20].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[20].morto = true;
            carregaObjeto(&inimigo[20],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[20].textura);
            criaInimigo22();
        }
        }

        if(inimigo[21].morto == false){
        if(colisao(inimigo[21].area.x, inimigo[21].area.y, inimigo[21].area.w, inimigo[21].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[21].morto = true;
            carregaObjeto(&inimigo[21],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[21].textura);
            criaInimigo23();
        }
        }

        if(inimigo[22].morto == false){
        if(colisao(inimigo[22].area.x, inimigo[22].area.y, inimigo[22].area.w, inimigo[22].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[22].morto = true;
            carregaObjeto(&inimigo[22],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[22].textura);
            criaInimigo24();
        }
        }

        if(inimigo[23].morto == false){
        if(colisao(inimigo[23].area.x, inimigo[23].area.y, inimigo[23].area.w, inimigo[23].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[23].morto = true;
            carregaObjeto(&inimigo[23],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[23].textura);
            criaInimigo25();
        }
        }

        if(inimigo[24].morto == false){
        if(colisao(inimigo[24].area.x, inimigo[24].area.y, inimigo[24].area.w, inimigo[24].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[24].morto = true;
            carregaObjeto(&inimigo[24],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[24].textura);
            criaInimigo26();
        }
        }

        if(inimigo[25].morto == false){
        if(colisao(inimigo[25].area.x, inimigo[25].area.y, inimigo[25].area.w, inimigo[25].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[25].morto = true;
            carregaObjeto(&inimigo[25],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[25].textura);
            criaInimigo27();
        }
        }

        if(inimigo[26].morto == false){
        if(colisao(inimigo[26].area.x, inimigo[26].area.y, inimigo[26].area.w, inimigo[26].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[26].morto = true;
            carregaObjeto(&inimigo[26],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[26].textura);
            criaInimigo28();
        }
        }

        if(inimigo[27].morto == false){
        if(colisao(inimigo[27].area.x, inimigo[27].area.y, inimigo[27].area.w, inimigo[27].area.h, tiro.area.x, tiro.area.y, tiro.area.w, tiro.area.h) == true){
            tironatela=false;
            inimigo[27].morto = true;
            carregaObjeto(&inimigo[27],"imagens\\explosion.png");
            SDL_DestroyTexture(inimigo[27].textura);
            carregaObjeto(&background,"imagens\\youwin.png");
            background.area.x=0;
            background.area.y=0;
            background.area.w=LARGURA;
            background.area.h=ALTURA;
            SDL_DestroyTexture(nave.textura);
            SDL_DestroyTexture(tiro.textura);
        }
        }

    }


    void desenhaTiro() {
        SDL_RenderCopy(visualizacao,tiro.textura,NULL, &tiro.area);
        tiro.area.y-=tiro.velocidade; // movimenta o tiro
        if(tiro.area.y<0) // ate sair da tela
            tironatela=false;
        detectaColisao();

    }

    //Função que desenha inimigos e controla movimentação dele
    void desenhaInimigo(){
    //Movimento do inimigo no eixo y
    for(int i = 0; i <= 28; i++){
    inimigo[i].area.y += inimigo[i].velocidade;
    //encerra jogo caso inimigo chegue ao final
    if (inimigo[i].area.y > 550 && inimigo[i].morto == false)
        fim = true;
    if (inimigo[i].area.y < 0){
        inimigo[i].velocidade = -inimigo[i].velocidade;
    }
    else if(inimigo[i].area.y+inimigo[i].area.w > 800){
        inimigo[i].velocidade = -inimigo[i].velocidade;
    }

    }

    //Cria 28 inimigos na tela
    SDL_RenderCopy(visualizacao,inimigo[0].textura,NULL, &inimigo[0].area);
    SDL_RenderCopy(visualizacao,inimigo[1].textura,NULL, &inimigo[1].area);
    SDL_RenderCopy(visualizacao,inimigo[2].textura,NULL, &inimigo[2].area);
    SDL_RenderCopy(visualizacao,inimigo[3].textura,NULL, &inimigo[3].area);
    SDL_RenderCopy(visualizacao,inimigo[4].textura,NULL, &inimigo[4].area);
    SDL_RenderCopy(visualizacao,inimigo[5].textura,NULL, &inimigo[5].area);
    SDL_RenderCopy(visualizacao,inimigo[6].textura,NULL, &inimigo[6].area);
    SDL_RenderCopy(visualizacao,inimigo[7].textura,NULL, &inimigo[7].area);
    SDL_RenderCopy(visualizacao,inimigo[8].textura,NULL, &inimigo[8].area);
    SDL_RenderCopy(visualizacao,inimigo[9].textura,NULL, &inimigo[9].area);
    SDL_RenderCopy(visualizacao,inimigo[10].textura,NULL, &inimigo[10].area);
    SDL_RenderCopy(visualizacao,inimigo[11].textura,NULL, &inimigo[11].area);
    SDL_RenderCopy(visualizacao,inimigo[12].textura,NULL, &inimigo[12].area);
    SDL_RenderCopy(visualizacao,inimigo[13].textura,NULL, &inimigo[13].area);
    SDL_RenderCopy(visualizacao,inimigo[14].textura,NULL, &inimigo[14].area);
    SDL_RenderCopy(visualizacao,inimigo[15].textura,NULL, &inimigo[15].area);
    SDL_RenderCopy(visualizacao,inimigo[16].textura,NULL, &inimigo[16].area);
    SDL_RenderCopy(visualizacao,inimigo[17].textura,NULL, &inimigo[17].area);
    SDL_RenderCopy(visualizacao,inimigo[18].textura,NULL, &inimigo[18].area);
    SDL_RenderCopy(visualizacao,inimigo[19].textura,NULL, &inimigo[19].area);
    SDL_RenderCopy(visualizacao,inimigo[20].textura,NULL, &inimigo[20].area);
    SDL_RenderCopy(visualizacao,inimigo[21].textura,NULL, &inimigo[21].area);
    SDL_RenderCopy(visualizacao,inimigo[22].textura,NULL, &inimigo[22].area);
    SDL_RenderCopy(visualizacao,inimigo[23].textura,NULL, &inimigo[23].area);
    SDL_RenderCopy(visualizacao,inimigo[24].textura,NULL, &inimigo[24].area);
    SDL_RenderCopy(visualizacao,inimigo[25].textura,NULL, &inimigo[25].area);
    SDL_RenderCopy(visualizacao,inimigo[26].textura,NULL, &inimigo[26].area);
    SDL_RenderCopy(visualizacao,inimigo[27].textura,NULL, &inimigo[27].area);

        //tiro.area.y -= tiro.velocidade;

    }

    void close()
    {
        SDL_FreeSurface( content );
        content = NULL;
        SDL_DestroyWindow( janelaprincipal );
        janelaprincipal= NULL;
        IMG_Quit();
        SDL_DestroyRenderer(visualizacao);
        SDL_DestroyTexture(nave.textura);
        SDL_DestroyTexture(background.textura);
        SDL_DestroyTexture(tiro.textura);
        SDL_DestroyTexture(inimigo[0].textura);
        SDL_DestroyTexture(inimigo[1].textura);
        SDL_DestroyTexture(inimigo[2].textura);
        SDL_DestroyTexture(inimigo[3].textura);
        SDL_DestroyTexture(inimigo[4].textura);
        SDL_DestroyTexture(inimigo[5].textura);
        SDL_DestroyTexture(inimigo[6].textura);
        SDL_DestroyTexture(inimigo[7].textura);
        SDL_DestroyTexture(inimigo[8].textura);
        SDL_DestroyTexture(inimigo[9].textura);
        SDL_DestroyTexture(inimigo[10].textura);
        SDL_DestroyTexture(inimigo[11].textura);
        SDL_DestroyTexture(inimigo[12].textura);
        SDL_DestroyTexture(inimigo[13].textura);
        SDL_DestroyTexture(inimigo[14].textura);
        SDL_DestroyTexture(inimigo[15].textura);
        SDL_DestroyTexture(inimigo[16].textura);
        SDL_DestroyTexture(inimigo[17].textura);
        SDL_DestroyTexture(inimigo[18].textura);
        SDL_DestroyTexture(inimigo[19].textura);
        SDL_DestroyTexture(inimigo[20].textura);
        SDL_DestroyTexture(inimigo[21].textura);
        SDL_DestroyTexture(inimigo[22].textura);
        SDL_DestroyTexture(inimigo[23].textura);
        SDL_DestroyTexture(inimigo[24].textura);
        SDL_DestroyTexture(inimigo[25].textura);
        SDL_DestroyTexture(inimigo[26].textura);
        SDL_DestroyTexture(inimigo[27].textura);
        SDL_Quit(); // fecha a SDL
    }

    void display(){
        SDL_RenderClear(visualizacao); //limpa a tela
        desenhaBackgound(); // desenha o fundo
        desenhaNave(); // mostra os objetos
        if(tironatela)  // condição bool
            desenhaTiro(); // animação do tiro
        desenhaInimigo();
        SDL_RenderPresent(visualizacao);
    }

    //movimento nave
    void executaAcao()
    {

        if(teclas.direita){
        if(nave.area.x <= 725)
            nave.area.x+=nave.velocidade;}
        if(teclas.esquerda){
        if (nave.area.x >= 0)
            nave.area.x-=nave.velocidade;}
        if(teclas.espaco){
            tironatela=true;
            teclas.espaco=false; // apenas um tiro de cada vez
            tiro.area.x=nave.area.x+(nave.area.w/4  );
            tiro.area.y=nave.area.y;
        }
    }

    int main( int argc, char* args[] )
    {
        inicializaTeclas();
        tironatela=false;
        //Eventos
        SDL_Event evento;

        //Inicializa a SDL
        if( !init() )
        {
            printf( "Falha na inicialização!\n" );
        }
        else
        {
            carregaObjetos();
            criaInimigo();

            while(!fim){
                while( SDL_PollEvent( &evento ))
                {
                    switch(evento.type){
                        case SDL_QUIT :
                            fim = true;
                            break;
                        case SDL_KEYDOWN: // tecla pressionada
                            if(evento.key.keysym.sym == SDLK_LEFT)
                                teclas.esquerda=true;
                            if (evento.key.keysym.sym == SDLK_RIGHT)
                                teclas.direita=true;
                            if (evento.key.keysym.sym == SDLK_SPACE)
                                if(!tironatela)
                                    teclas.espaco=true;
                            break;
                        case SDL_KEYUP: // tecla solta
                            if(evento.key.keysym.sym == SDLK_LEFT)
                                teclas.esquerda=false;
                            if (evento.key.keysym.sym == SDLK_RIGHT)
                                teclas.direita=false;
                            if (evento.key.keysym.sym == SDLK_SPACE)
                                teclas.espaco=false;
                            break;
                    }
                }
                executaAcao();
                display();
            }
        }

        //Libera a memória
        close();

        return 0;
    }
