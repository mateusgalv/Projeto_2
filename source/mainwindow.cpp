#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Trem::iniciar_semaforos();
    
    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1, 125,  50);
    trem2 = new Trem(2, 125, 150);
    trem3 = new Trem(3, 275, 150);
    trem4 = new Trem(4,  50, 250);
    trem5 = new Trem(5, 200, 250);
    trem6 = new Trem(6, 350, 250);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
        case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
            ui->label_trem1->setGeometry(x, y, 20, 20);
            break;
        case 2:
            ui->label_trem2->setGeometry(x, y, 20, 20);
            break;
        case 3:
            ui->label_trem3->setGeometry(x, y, 20, 20);
            break;
        case 4:
            ui->label_trem4->setGeometry(x, y, 20, 20);
            break;
        case 5:
            ui->label_trem5->setGeometry(x, y, 20, 20);
            break;
        case 6:
            ui->label_trem6->setGeometry(x, y, 20, 20);
            break;
        default:
            break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
    trem6->terminate();
}
