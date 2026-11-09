#ifndef TREM_H
#define TREM_H

#include <atomic>
#include <QThread>

class Trem: public QThread{
    Q_OBJECT
    
    public:
        Trem(int, int, int);                // construtor
        void run();                         // função a ser executada pela thread
        
        static void iniciar_semaforos();    // inicialização dos semaforos

        int get_velocidade();
        void set_velocidade(int);
        
        void mover_em_x(int);
        void mover_em_y(int);
        
    //Cria um sinal
    signals:
        void updateGUI(int,int,int);

    private:
        int ID;
        int x;
        int y;
        std::atomic<int> velocidade;
        int estado_trem;
};

#endif