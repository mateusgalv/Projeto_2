#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAbstractSlider>
#include <QSlider>

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

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();

    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    connect(ui->slider_1, &QSlider::valueChanged, trem1, &Trem::set_velocidade);
    connect(ui->slider_2, &QSlider::valueChanged, trem2, &Trem::set_velocidade);
    connect(ui->slider_3, &QSlider::valueChanged, trem3, &Trem::set_velocidade);
    connect(ui->slider_4, &QSlider::valueChanged, trem4, &Trem::set_velocidade);
    connect(ui->slider_5, &QSlider::valueChanged, trem5, &Trem::set_velocidade);
    connect(ui->slider_6, &QSlider::valueChanged, trem6, &Trem::set_velocidade);

    connect(ui->slider_geral, &QSlider::valueChanged, this, [this](int v) {
        ui->slider_1->setValue(v);
        ui->slider_2->setValue(v);
        ui->slider_3->setValue(v);
        ui->slider_4->setValue(v);
        ui->slider_5->setValue(v);
        ui->slider_6->setValue(v);

        trem1->set_velocidade(v);
        trem2->set_velocidade(v);
        trem3->set_velocidade(v);
        trem4->set_velocidade(v);
        trem5->set_velocidade(v);
        trem6->set_velocidade(v);
    });

    QGroupBox *groupBox = new QGroupBox(tr("Velocidades"), ui->centralWidget);
    QVBoxLayout *vbox = new QVBoxLayout(groupBox);

    auto adiciona_linha_vel = [&](const QString &texto, QSlider *slider) {
    QHBoxLayout *linha = new QHBoxLayout;
    linha->addWidget(new QLabel(texto));   // texto à esquerda
    linha->addWidget(slider);              // slider à direita
    vbox->addLayout(linha);
    };

    adiciona_linha_vel(tr("T1"), ui->slider_1);
    adiciona_linha_vel(tr("T2"), ui->slider_2);
    adiciona_linha_vel(tr("T3"), ui->slider_3);
    adiciona_linha_vel(tr("T4"), ui->slider_4);
    adiciona_linha_vel(tr("T5"), ui->slider_5);
    adiciona_linha_vel(tr("T6"), ui->slider_6);
    adiciona_linha_vel(tr("TM"),  ui->slider_geral);
    
    groupBox->setGeometry(50, 400, 340, 300);   // ajuste x, y, largura, altura
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
