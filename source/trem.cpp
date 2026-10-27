#include "trem.h"
#include <QtCore>

#define ESPERANDO 0
#define MOVENDO 1
#define TRUE 1

//Construtor
Trem::Trem(int ID, int x, int y) {
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->estado = nullptr;
    velocidade = 100;
}

//Função a ser executada após executar trem->START
void Trem::run() {
    while(true) {
        switch(ID) {
            case 1:     //Trem 1
                if (x == 125 && y < 150) {
                    y += 10;                // topo-esquerdo → base-esquerda 
                } else if (x < 425 && y == 150) {
                    x += 10;                // base-esquerda → base-direita
                } else if (x == 425 && y > 50) {
                    y -= 10;                // base-direita → topo-direito
                } else {
                    x -= 10;                // topo-direito → topo-esquerdo
                }
                emit updateGUI(ID, x, y);   //Emite um sinal
                break;

            case 2:
                if (x == 125 && y < 250) {
                    y += 10;
                } else if (x < 275 && y == 250) {
                    x += 10;
                } else if (x == 275 && y > 150) {
                    y -= 10;
                } else {
                    x -= 10;
                }
                emit updateGUI(ID, x, y);
                break;

            case 3:
                if (x == 275 && y < 250) {
                    y += 10;
                } else if (x < 425 && y == 250) {
                    x += 10;
                } else if (x == 425 && y > 150) {
                    y -= 10;
                } else {
                    x -= 10;
                }
                emit updateGUI(ID, x, y);
                break;

            default:
                break;
        }
        msleep(velocidade);
    }
}

void Trem::testarTrecho(int i) {
    if (state == ESPERANDO) {
        state[i] = ANDANDO;
        // sem_post(&s[i]);
    }
}



