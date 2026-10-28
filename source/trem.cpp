#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "trem.h"
#include <QtCore>

#define TRUE 1

// ESTADOS E DEFINICOES DOS TRILHOS
#define N_TRILHOS 21
#define LIVRE 0
#define OCUPADO 1

// ESTADOS E DEFINICOES DOS TRENS
#define N_TRENS 6
#define ESPERANDO 0
#define TRABALHANDO 1

typedef struct {
    int x_inicial;
    int y_inicial;
    int x_final;
    int y_final;
} Trilho;

const int coordenadas[16][2] = {
    { 125,  50 },   // P1
    { 125, 150 },   // P2
    { 275, 150 },   // P3
    { 425, 150 },   // P4
    { 425,  50 },   // P5
    { 125, 250 },   // P6
    { 200, 250 },   // P7
    { 275, 250 },   // P8
    { 350, 250 },   // P9
    { 425, 250 },   // P10
    {  50, 250 },   // P11
    {  50, 350 },   // P12
    { 200, 350 },   // P13
    { 350, 350 },   // P14
    { 500, 350 },   // P15
    { 500, 250 },   // P16
};

const int percursos[N_TRENS][5] = {
    // Pontos ordenados que Trem N se move em direção
    {  1,  2,  3,  4,  5 }, // Trem 1
    {  2,  6,  7,  8,  3 }, // Trem 2
    {  3,  8,  9, 10,  4 }, // Trem 3
    { 11, 12, 13,  7,  6 }, // Trem 4
    {  7, 13, 14,  9,  8 }, // Trem 5
    {  9, 14, 15, 16, 10 }  // Trem 6
};

const Trilho trilhos[N_TRILHOS] = {
    { 425,  50, 125,  50 }, // trilho 1
    { 125,  50, 125, 150 }, // trilho 2
    { 125, 150, 275, 150 }, // trilho 3
    { 275, 150, 425, 150 },
    { 425, 150, 425,  50 },
    { 125, 150, 125, 250 }, // trilho 6
    { 125, 250, 200, 250 },
    { 200, 250, 275, 250 },
    { 275, 250, 275, 150 },
    { 275, 250, 350, 250 }, // trilho 10
    { 350, 250, 425, 250 },
    { 425, 250, 425, 150 },
    { 125, 250,  50, 250 },
    {  50, 250,  50, 350 },
    {  50, 350, 200, 350 },
    { 200, 350, 200, 250 },
    { 200, 350, 350, 350 },
    { 350, 350, 350, 250 },
    { 350, 350, 500, 350 },
    { 500, 350, 500, 250 },
    { 500, 250, 425, 250 }  // trilho 21
};

// REGIÃO CRÍTICA -> armazena o estado dos trilhos LIVRE <-> OCUPADO

//Construtor
Trem::Trem(int ID, int x, int y) {
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 50;
    this->estado = ESPERANDO;
}

void Trem::mover_em_x(int distancia_percorrida) {
    x += distancia_percorrida;
}

void Trem::mover_em_y(int distancia_percorrida) {
    y += distancia_percorrida;
}

void Trem::percorrer_trilho() {
    int distancia_percorrida;
    int atual = 0;
    const int *percurso = percursos[ID-1];
    Trilho trilho;
    
    while(TRUE) {
        int ponto_atual = percurso[atual % 5];
        int ponto_seguinte = percurso[(atual + 1) % 5];
        
        const int *coordenada_atual = coordenadas[ponto_atual - 1];
        const int *coordenada_seguinte = coordenadas[ponto_seguinte - 1];

        trilho.x_inicial = coordenada_atual[0];
        trilho.y_inicial = coordenada_atual[1];

        trilho.x_final = coordenada_seguinte[0];
        trilho.y_final = coordenada_seguinte[1];

        // Checa direção do trem:
        if (trilho.x_inicial == trilho.x_final) {
            // x = cte → move em Y (vertical)
            // Checa sentido do trem:
            if (trilho.y_final > trilho.y_inicial) {
                // Trem se movimenta cima → baixo (incrementa y)
                distancia_percorrida = ((trilho.y_final - y < velocidade) ?
                    trilho.y_final - y : velocidade
                );
                mover_em_y(distancia_percorrida);
            } else if (trilho.y_final < trilho.y_inicial) {
                // Trem se movimenta baixo → cima (decrementa y)
                distancia_percorrida = ((y - trilho.y_final < velocidade) ? 
                    y - trilho.y_final : velocidade
                );
                mover_em_y(-distancia_percorrida);
            } else {
                atual++;
            }
            emit updateGUI(ID, x, y);
            msleep(100);
        } else if (trilho.y_inicial == trilho.y_final) {
            // y = cte → move em X (horizontal)
            if (trilho.x_final > trilho.x_inicial) {
                // Trem se movimento esquerda → direita (incrementa x)
                distancia_percorrida = ((trilho.x_final - x < velocidade) ?
                    trilho.x_final - x : velocidade
                );
                mover_em_x(distancia_percorrida);
            } else if (trilho.x_final < trilho.x_inicial) {
                // Trem se movimenta direita → esquerda (decrementa x)
                distancia_percorrida = ((x - trilho.x_final < velocidade) ?
                    x - trilho.x_final : velocidade
                );
                mover_em_x(-distancia_percorrida);
            } else {
                atual++;
            }
            emit updateGUI(ID, x, y);
            msleep(100);
        } else {
            // Chegou ao fim do trilho
            // Vai pro próximo trilho:
            atual++;
        }


        if (x == trilho.x_final && y == trilho.y_final) {
            atual++;
        }
    }
}

//Função a ser executada após executar trem->START
void Trem::run() {
    percorrer_trilho();
    
    // percorrer trilho
    // tentar acessar proximo trilho
    
    
    // this->estado = TRABALHANDO;

    // while(TRUE) {
    //     if (this->estado == ESPERANDO) {
    //         // sleep
    //     } else if (this->estado == TRABALHANDO) {
    //         int limites = trilho_atual[1];
    //         int limite_x = limites[0];
    //         int limite_y = limites[1];

    //         while()
    //     }

    //     switch(ID) {
    //         case 1:     //Trem 1
    //             if (x == 125 && y < 150) {
    //                 mover_Y(this->velocidade);                // topo-esquerdo → base-esquerda 
    //             } else if (x < 425 && y == 150) {
    //                 mover_X(this->velocidade);                // base-esquerda → base-direita
    //             } else if (x == 425 && y > 50) {
    //                 mover_Y(-(this->velocidade));               // base-direita → topo-direito
    //             } else {
    //                 mover_X(-(this->velocidade));               // topo-direito → topo-esquerdo
    //             }
    //             emit updateGUI(ID, x, y);   //Emite um sinal
    //             break;

    //         case 2:
    //             if (x == 125 && y < 250) {
    //                 y += 10;
    //             } else if (x < 275 && y == 250) {
    //                 x += 10;
    //             } else if (x == 275 && y > 150) {
    //                 y -= 10;
    //             } else {
    //                 x -= 10;
    //             }
    //             emit updateGUI(ID, x, y);
    //             break;

    //         case 3:
    //             if (x == 275 && y < 250) {
    //                 y += 10;
    //             } else if (x < 425 && y == 250) {
    //                 x += 10;
    //             } else if (x == 425 && y > 150) {
    //                 y -= 10;
    //             } else {
    //                 x -= 10;
    //             }
    //             emit updateGUI(ID, x, y);
    //             break;

    //         case 4:
    //             if (x == 50 && y < 350) {
    //                 y += 10;
    //             } else if (x < 200 && y == 350) {
    //                 x += 10;
    //             } else if (x == 200 && y > 250) {
    //                 y -= 10;
    //             } else {
    //                 x -= 10;
    //             }
    //         default:
    //             break;
    //     }
    //     msleep(velocidade);
    // }
}



