#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->backToMain->hide();
    ui->playerLabel2->hide();
    ui->name2->hide();
    ui->name1->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::confirm(){
    if(ui->add_player->isChecked()){
        if(ui->name1->text() != "" && ui->name2->text() != "")
            ui->stackedWidget->setCurrentIndex(1);
    }
    else if(ui->add_comp->isChecked() && ui->name1->text() != ""){
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_btn_confirm_clicked()
{
    confirm();

}

void MainWindow::on_name1_returnPressed()
{
    if(ui->add_comp->isChecked())
        confirm();
    else
        ui->name2->setFocus();
}

void MainWindow::on_name2_returnPressed()
{
    confirm();
}

void MainWindow::on_btn_XO_clicked()
{

    if(ui->add_comp->isChecked())
        XO = new TicTacToe(ui->stackedWidget, true);
    else{
        XO = new TicTacToe(ui->stackedWidget, false);
    }
    XO->setObjectName("XO");
    int index = ui->stackedWidget->addWidget(XO);
    ui->stackedWidget->setCurrentIndex(index);
    ui->backToMain->show();
}


void MainWindow::on_btn_XO_pyr_clicked()
{


    if(ui->add_comp->isChecked())
        pyr_XO = new Pyramid_XO(ui->stackedWidget, true);
    else{
        pyr_XO = new Pyramid_XO(ui->stackedWidget, false);
    }
    pyr_XO->setObjectName("pyr_XO");
    int index = ui->stackedWidget->addWidget(pyr_XO);
    ui->stackedWidget->setCurrentIndex(index);
    ui->backToMain->show();
}


void MainWindow::on_btn_connect_4_clicked()
{

    if(ui->add_comp->isChecked())
        connect4 = new Connect4(ui->stackedWidget, true);
    else{
        connect4 = new Connect4(ui->stackedWidget, false);
    }
    connect4->setObjectName("connect4");
    int index = ui->stackedWidget->addWidget(connect4);
    ui->stackedWidget->setCurrentIndex(index);
    ui->backToMain->show();
}


void MainWindow::on_btn_XO_5_clicked()
{


    if(ui->add_comp->isChecked())
        XO5by5 = new TicTacToe5x5(ui->stackedWidget, true);
    else{
        XO5by5 = new TicTacToe5x5(ui->stackedWidget, false);
    }
    XO5by5->setObjectName("XO5by5");
    int index = ui->stackedWidget->addWidget(XO5by5);
    ui->stackedWidget->setCurrentIndex(index);
    ui->backToMain->show();
}



void MainWindow::on_backToMain_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->backToMain->hide();
}


void MainWindow::on_add_player_toggled(bool checked)
{
    if(checked){
        ui->playerLabel1->setText("Player 1 Name:");
        ui->playerLabel2->show();
        ui->name2->show();
    }
    else{
        ui->playerLabel1->setText("Player Name:");
        ui->playerLabel2->hide();
        ui->name2->hide();
    }
}
