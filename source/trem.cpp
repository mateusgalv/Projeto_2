#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "trem.h"
#include <QtCore>

// ESTADOS E DEFINICOES
#define TRUE 1
#define VAZIO -1
#define N_TRENS 6
#define N_PONTOS 16
#define N_TRILHOS 21

#define OCUPADO 0
#define LIVRE 1
#define ESPERANDO 1

const int coordenadas[16][2] = {
    // PONTOS (x, y)
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
const int percursos_por_pontos[N_TRENS][5] = {
    // Ordem circular de acesso aos cruzamentos
    {  1,  2,  3,  4,  5 }, // Trem 1 
    {  2,  6,  7,  8,  3 }, // Trem 2
    {  3,  8,  9, 10,  4 }, // Trem 3
    { 11, 12, 13,  7,  6 }, // Trem 4
    {  7, 13, 14,  9,  8 }, // Trem 5
    {  9, 14, 15, 16, 10 }  // Trem 6
    /*
     * Um Ponto N está na posição (N-1) de coordenadas
    */ 
};
const int percursos_por_trilhos[N_TRENS][5] = {
    // Ordem circular de acesso aos trilhos
    {  1,  2,  3,  4,  5 }, // Trem 1
    {  6,  7,  8,  9,  2 }, // Trem 2
    {  9, 10, 11, 12,  3 }, // Trem 3
    { 14, 15, 16,  7, 13 }, // Trem 4
    { 16, 17, 18, 10,  8 }, // Trem 5
    { 18, 19, 20, 21, 11 }  // Trem 6
    /*
     * O semáforo de um trilho N está na posição (N-1) de sem_trilho[N_TRILHOS]
    */
};

// SEMAFOROS E REGIOES CRITICAS
sem_t sem_trilhos[N_TRILHOS];

//Construtor
Trem::Trem(int ID, int x, int y) {
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 5;
    this->estado_trem = ESPERANDO;
}

int Trem::get_velocidade() {
    return velocidade.load();
}
void Trem::set_velocidade(int nova_velocidade) {
    velocidade.store(nova_velocidade);
}

void Trem::mover_em_x(int distancia_percorrida) {
    x += distancia_percorrida;
}
void Trem::mover_em_y(int distancia_percorrida) {
    y += distancia_percorrida;
}


void Trem::iniciar_semaforos() {
        for (int j = 0; j < N_TRILHOS; j++) {
        // Todos os trilhos iniciam livres - Trens começam ocupando cruzamentos.
        sem_init(&sem_trilhos[j], 0, LIVRE);
    }
}

void Trem::run() {
    const int *percurso_por_pontos = percursos_por_pontos[ID - 1];
    const int *percurso_por_trilhos = percursos_por_trilhos[ID - 1];
    
    int ponto_index = 0;
    int trilho_index = 0;
    
    int ponto_atual = percurso_por_pontos[ponto_index];
    int proximo_ponto = percurso_por_pontos[ponto_index + 1];
    
    int trilho_ocupado = 0;
    int proximo_trilho = percurso_por_trilhos[trilho_index];
    
    while(TRUE) {
        
        if (estado_trem == ESPERANDO) {

            sem_wait(&sem_trilhos[proximo_trilho - 1]);
            trilho_ocupado = proximo_trilho;
            estado_trem = OCUPADO;

        } else if (estado_trem == OCUPADO) {

            // SE MOVE
            const int *coordenada_atual = coordenadas[ponto_atual - 1];
            const int *coordenada_seguinte = coordenadas[proximo_ponto - 1];

            const int x_inicial = coordenada_atual[0];
            const int y_inicial = coordenada_atual[1];
            const int x_final = coordenada_seguinte[0];
            const int y_final = coordenada_seguinte[1];

            const int velocidade_atual = get_velocidade();
            
            // Checa direção do trem:
            if (x_inicial == x_final) {                 // x = cte → move em y (vertical)

                const int delta_y = y_final - y_inicial;
                const int distancia_restante = abs(y_final - y);
                int distancia_a_percorrer, sentido = 0;

                if (delta_y > 0) {
                    sentido = 1;                        // topo → base (incrementa y)
                } else if (delta_y < 0) {
                    sentido = -1;                       // base → topo (decrementa y)
                }
                distancia_a_percorrer = ((distancia_restante < velocidade_atual) ?
                    distancia_restante : velocidade_atual
                );
                mover_em_y(distancia_a_percorrer * sentido);

            } else if (y_inicial == y_final) {          // y = cte → move em x (horizontal)
                const int delta_x = x_final - x_inicial;
                const int distancia_restante = abs(x_final - x);
                int distancia_a_percorrer, sentido = 0;

                if (delta_x > 0) {
                    sentido = 1;                        // esquerda → direita (incrementa x)
                } else if (delta_x < 0) {
                    sentido = -1;                       // direita → esquerda (decrementa x)
                }
                distancia_a_percorrer = ((distancia_restante < velocidade_atual) ?
                    distancia_restante : velocidade_atual
                );
                mover_em_x(distancia_a_percorrer * sentido);
            }
            
            // Atualiza estado do trem:
            if (x == x_final && y == y_final) {
                // Atualiza ponto
                ponto_atual = proximo_ponto;
                trilho_index = ponto_index;
                ponto_index = (ponto_index + 1) % 5;
                proximo_ponto = percurso_por_pontos[(ponto_index + 1) % 5];
                
                // Libera o trilho usado
                sem_post(&sem_trilhos[trilho_ocupado - 1]);
                proximo_trilho = percurso_por_trilhos[(trilho_index + 1) % 5];

                estado_trem = ESPERANDO;
            }
        }
        emit updateGUI(ID, x, y);
        msleep(60);
    }
}


