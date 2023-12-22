#include "pyramid_xo.h"
#include "ui_pyramid_xo.h"
#include <QTimer>

Pyramid_XO::Pyramid_XO(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pyramid_XO)
{
    ui->setupUi(this);
}


Pyramid_XO::Pyramid_XO(QWidget *parent, bool isComputer)
    : QWidget(parent)
    , ui(new Ui::Pyramid_XO)
{
    ui->setupUi(this);

    isComp = isComputer;

    player = "X";
    n_rows = 3;
    n_cols = 1;
    // Initialize the board with button pointers
    board = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j);
            board[i][j] = findChild<QPushButton*>(buttonName);

            if (board[i][j]) {
                connect(board[i][j], &QPushButton::clicked, this, &Pyramid_XO::on_gridButtonClicked);
            }
        }
        n_cols += 2;
    }
}

Pyramid_XO::~Pyramid_XO()
{
    delete ui;
}

void Pyramid_XO::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

void Pyramid_XO::random_move(){
    int x, y;
    // srand(time(0));
    x = (int) (rand()/(RAND_MAX + 1.0) * 3);
    if(x == 0)
        y = 0;
    else if(x == 1){
        y = (int) (rand()/(RAND_MAX + 1.0) * 3);
    }
    else{
        y = (int) (rand()/(RAND_MAX + 1.0) * 5);
    }
    if(board[x][y]->text() == ""){
        board[x][y]->setText(player);
        n_moves++;
    }
    else{
        random_move();
        return;
    }
}

bool Pyramid_XO::is_winner(){
    //Checking rows
    n_cols = 1;
    int Xc, Oc;
    for (int i = 0; i < n_rows; i++) {
        Xc = Oc = 0;
        for (int j = 0; j < n_cols; j++){
            if(Xc < 3 && Oc <3){
                if (board[i][j]->text() == "X"){
                    Oc = 0;
                    Xc++;
                }
                else if (board[i][j]->text() == "O") {
                    Xc = 0;
                    Oc++;
                }
                else{
                    Xc = Oc = 0;
                }
            }
        }
        if (Xc == 3 || Oc == 3){
            return true;
        }
        n_cols += 2;
    }

    //Checking the column and diagonals
    if(n_moves > 4)
        if(board[0][0]->text() != "" && ((board[0][0]->text() == board[1][1]->text() && board[1][1]->text() == board[2][2]->text())
             ||(board[0][0]->text() == board[1][0]->text() && board[1][0]->text() == board[2][0]->text())
             || (board[0][0]->text() == board[1][2]->text() && board[1][2]->text() == board[2][4]->text()))){
            return true;
        }
    return false;
}

bool Pyramid_XO::is_draw(){
    return n_moves == 9;
}

bool Pyramid_XO::game_is_over(){
    return gameEnd;
}

void Pyramid_XO::on_gridButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton && !game_is_over()) {
        if (clickedButton->text() == "") {
            clickedButton->setText(player);
            n_moves++;
            if (is_winner()) {
                QString text = "The winner is player " + player;
                ui->result->setText(text);
                ui->turn->setText("");
                gameEnd = true;
                return;
            } else if (is_draw()) {
                QString text = "Draw, no one wins!";
                ui->result->setText(text);
                ui->turn->setText("");
                gameEnd = true;
                return;
            }
            switch_player();

            if(isComp && !game_is_over()){
                QTimer::singleShot(200, qApp, [this](){
                    random_move();
                    if (is_winner()) {
                        QString text = "The winner is player " + player;
                        ui->result->setText(text);
                        ui->turn->setText("");
                        gameEnd = true;
                        return;
                    } else if (is_draw()) {
                        QString text = "Draw, no one wins!";
                        ui->result->setText(text);
                        ui->turn->setText("");
                        gameEnd = true;
                        return;
                    }
                    switch_player();
                });
            }
        }
    }
}

void Pyramid_XO::on_reset_clicked()
{
    gameEnd = false;
    n_moves = 0;
    player = "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
    ui->result->setText("");
    n_cols = 1;
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            board[i][j]->setText("");
        }
        n_cols += 2;
    }
}

