#include "include/mainwindow.h"
#include "ui_mainwindow.h"

/*initiating the ui settings*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->backToMain->hide();
}

/*Destructing the ui settings*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*Confirm button handler*/
void MainWindow::on_btn_confirm_clicked()
{
    if(ui->add_player->isChecked() || ui->add_comp->isChecked()){   //checking whether the a radio button is selected
        ui->stackedWidget->setCurrentIndex(1);  //going to main menu
    }
}

/*Tictactoe button handler*/
void MainWindow::on_btn_XO_clicked()
{
    //creating a tictactoe widget
    if(ui->add_comp->isChecked())
        XO = new TicTacToe(ui->stackedWidget, true); //add a computer player as player 2
    else{
        XO = new TicTacToe(ui->stackedWidget, false); //add a normal player as player 2
    }
    XO->setObjectName("XO");
    int index = ui->stackedWidget->addWidget(XO);   //adds a tictactoe widget to the stacked widget
    ui->stackedWidget->setCurrentIndex(index);  //opens the tictactoe form
    ui->backToMain->show(); //displaying back to main menu button
}

/*Pyramid tictactoe button handler*/
void MainWindow::on_btn_XO_pyr_clicked()
{
    //creating a pyramid tictactoe widget
    if(ui->add_comp->isChecked())
        pyr_XO = new Pyramid_XO(ui->stackedWidget, true); //add a computer player as player 2
    else{
        pyr_XO = new Pyramid_XO(ui->stackedWidget, false); //add a normal player as player 2
    }
    pyr_XO->setObjectName("pyr_XO");
    int index = ui->stackedWidget->addWidget(pyr_XO); //adds a pyramid tictactoe widget to the stacked widget
    ui->stackedWidget->setCurrentIndex(index); //opens the pyramid tictactoe form
    ui->backToMain->show(); //displaying back to main menu button
}

/*Connect-four button handler*/
void MainWindow::on_btn_connect_4_clicked()
{
    //creating a connect-four widget
    if(ui->add_comp->isChecked())
        connect4 = new Connect4(ui->stackedWidget, true); //add a computer player as player 2
    else{
        connect4 = new Connect4(ui->stackedWidget, false); //add a normal player as player 2
    }
    connect4->setObjectName("connect4");
    int index = ui->stackedWidget->addWidget(connect4); //adds a connect-four widget to the stacked widget
    ui->stackedWidget->setCurrentIndex(index); //opens the connect-four form
    ui->backToMain->show(); //displaying back to main menu button
}

/*5x5 tictactoe button handler*/
void MainWindow::on_btn_XO_5_clicked()
{
    //creating a 5x5 tictactoe widget
    if(ui->add_comp->isChecked())
        XO5by5 = new TicTacToe5x5(ui->stackedWidget, true); //add a computer player as player 2
    else{
        XO5by5 = new TicTacToe5x5(ui->stackedWidget, false); //add a normal player as player 2
    }
    XO5by5->setObjectName("XO5by5");
    int index = ui->stackedWidget->addWidget(XO5by5); //adds a 5x5 tictactoe widget to the stacked widget
    ui->stackedWidget->setCurrentIndex(index);  //opens the 5x5 tictactoe form
    ui->backToMain->show(); //displaying back to main menu button
}



void MainWindow::on_backToMain_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);  //return to the main menu
    ui->backToMain->hide(); //hiding the button
}

void MainWindow::on_btn_instructions_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->backToMain->show(); //displaying back to main menu button
}

