#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "trem.h"
#include <QtCore>

#define TRUE 1

// ESTADOS E DEFINICOES DOS TRENS
#define N_TRENS 6
#define ESPERANDO 0
#define TRABALHANDO 1

// ESTADOS E DEFINICOES DOS TRILHOS
#define N_TRILHOS 21
#define LIVRE 1
#define OCUPADO 0

typedef struct {
    int id;
    int id_proximo;
    int x_inicial;
    int y_inicial;
    int x_final;
    int y_final;
} Trilho;

// ESTADOS E DEFINICOES DOS SEMAFOROS
sem_t sem_trilhos[N_TRILHOS];

// DADOS
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
const int percursos_pontos[N_TRENS][5] = {
    // trilho em uso = percurso[ID-1][i]
    {  1,  2,  3,  4,  5 }, // Trem 1
    {  2,  6,  7,  8,  3 }, // Trem 2
    {  3,  8,  9, 10,  4 }, // Trem 3
    { 11, 12, 13,  7,  6 }, // Trem 4
    {  7, 13, 14,  9,  8 }, // Trem 5
    {  9, 14, 15, 16, 10 }  // Trem 6
};

const int percursos_trilhos[N_TRENS][5] = {
    {  1,  2,  3,  4,  5 }, // Trem 1
    {  6,  7,  8,  9,  2 }, // Trem 2
    {  9, 10, 11, 12,  3 }, // Trem 3
    { 14, 15, 16,  7, 13 }, // Trem 4
    { 16, 17, 18, 10,  8 }, // Trem 5
    { 18, 19, 20, 21, 11 }  // Trem 6
};

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

void Trem::iniciar_semaforos() {
    // trilhos iniciais devem começar OCUPADOS
    for (int i = 0; i < N_TRILHOS; i++) {
        if ( i == 0 || i == 5 || i == 8 || i == 13 || i == 15 || i == 17) {
            // trilhos 1, 6, 9, 14, 16, 18 OCUPADOS
            sem_init(&sem_trilhos[i], 0, OCUPADO);
        } else {
            sem_init(&sem_trilhos[i], 0, LIVRE);
        }
    }
}

int Trem::get_trilho(int p1, int p2) {
    // retorna o numero do trilho entre dois pontos p1 e p2
    if (p1 == 1 && p2 == 2) return 1;
    else if ((p1 ==  2 && p2 ==  3) || (p1 ==  3 && p2 ==  2)) return 2;
    else if ((p1 ==  3 && p2 ==  4) || (p1 ==  4 && p2 ==  3)) return 3;
    else if (p1 ==  4 && p2 ==  5) return 4;
    else if (p1 ==  5 && p2 ==  1) return 5;
    else if ((p1 ==  2 && p2 ==  6) || (p1 ==  6 && p2 ==  2)) return 6;
    else if ((p1 ==  6 && p2 ==  7) || (p1 ==  7 && p2 ==  6)) return 7;
    else if ((p1 ==  7 && p2 ==  8) || (p1 ==  8 && p2 ==  7)) return 8;
    else if ((p1 ==  8 && p2 ==  3) || (p1 ==  3 && p2 ==  8)) return 9;
    else if ((p1 ==  8 && p2 ==  9) || (p1 ==  9 && p2 ==  8)) return 10;
    else if ((p1 ==  9 && p2 == 10) || (p1 == 10 && p2 ==  9)) return 11;
    else if (p1 == 10 && p2 ==  4) return 12;
    else if (p1 ==  6 && p2 == 11) return 13;
    else if (p1 == 11 && p2 == 12) return 14;
    else if (p1 == 12 && p2 == 13) return 15;
    else if ((p1 == 13 && p2 ==  7) || (p1 ==  7 && p2 == 13)) return 16;
    else if (p1 == 13 && p2 == 14) return 17;
    else if ((p1 == 14 && p2 ==  9) || (p1 ==  9 && p2 == 14)) return 18;
    else if (p1 == 14 && p2 == 15) return 19;
    else if (p1 == 15 && p2 == 16) return 20;
    else if (p1 == 16 && p2 == 10) return 21;
    else return -1;
}

void Trem::percorrer_trilho() {
    int distancia_percorrida;
    const int *percurso_pontos = percursos_pontos[ID - 1];
    const int *percurso_trilhos = percursos_trilhos[ID - 1];
    Trilho trilho;
    
    int atual = 0;
    while(TRUE) {
        int ponto_atual = percurso_pontos[atual % 5];
        int ponto_seguinte = percurso_pontos[(atual + 1) % 5];
        
        int trilho_atual = (percurso_trilhos[atual % 5]);
        int trilho_seguinte = (percurso_trilhos[(atual + 1) % 5]);
        int trilho_pre_reserva = (percurso_trilhos[(atual + 2) % 5]);
        
        trilho.id = trilho_atual;
        trilho.id_proximo = trilho_seguinte;

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
            }
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
            }
        }
        
        emit updateGUI(ID, x, y);
        msleep(100);

        if (x == trilho.x_final && y == trilho.y_final) {
            printf("O trem %d deseja acessar o trilho %d\n", ID, trilho.id_proximo);
            sem_post(&sem_trilhos[trilho.id - 1]);
            sem_wait(&sem_trilhos[trilho.id_proximo - 1]);
            // sem_wait(&sem_trilhos[trilho_pre_reserva -1]);
            // sem_post(&sem_trilhos[trilho.id_proximo - 1]);
            // sem_post(&sem_trilhos[trilho_pre_reserva -1]);
            atual++;
        }
    }
}

//Função a ser executada após executar trem->START
void Trem::run() {

    percorrer_trilho(); 
}



