#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QTimer>


TicTacToe::TicTacToe(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

}
TicTacToe::TicTacToe(QWidget *parent, bool isComputer)
    : QWidget(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    isComp = isComputer;

    player = "X";
    n_rows = n_cols = 3;
    // Initialize the board with button pointers
    board = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j);
            board[i][j] = findChild<QPushButton*>(buttonName);

            if (board[i][j]) {
                connect(board[i][j], &QPushButton::clicked, this, &TicTacToe::on_gridButtonClicked);
            }
        }
    }
}

TicTacToe::~TicTacToe()
{
    delete ui;
}

void TicTacToe::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

void TicTacToe::random_move(){
    int x, y;
    x = (int) (rand()/(RAND_MAX + 1.0) * 3);
    y = (int) (rand()/(RAND_MAX + 1.0) * 3);
    if(board[x][y]->text() == ""){
        n_moves++;
        board[x][y]->setText(player);
    }
    else{
        random_move();
    }
}

bool TicTacToe::is_winner() {
    int Xc, Oc;
    // Checking rows
    for (int i = 0; i < 3; i++) {
        Xc = Oc = 0;
        for (int j = 0; j < 3; j++) {
            if (board[i][j]->text() == "X") Xc++;
            else if (board[i][j]->text() == "O") Oc++;
        }
        if (Xc == 3 || Oc == 3){
            return true;
        }
    }

    // Checking columns
    for (int i = 0; i < 3; i++) {
        Xc = Oc = 0;
        for (int j = 0; j < 3; j++) {
            if (board[j][i]->text() == "X") Xc++;
            else if (board[j][i]->text() == "O") Oc++;
        }
        if (Xc == 3 || Oc == 3){
            return true;
        }
    }

    // Checking diagonals
    if (board[1][1]->text() == "X") {
        if (board[0][0]->text() == "X" && board[2][2]->text() == "X") {
            return true;
        } else if (board[0][2]->text() == "X" && board[2][0]->text() == "X") {
            return true;
        }
    } else if (board[1][1]->text() == "O") {
        if (board[0][0]->text() == "O" && board[2][2]->text() == "O") {
            gameEnd = true;
            return true;
        } else if (board[0][2]->text() == "O" && board[2][0]->text() == "O") {
            return true;
        }
    }
    return false;
}

bool TicTacToe::is_draw(){
    return (n_moves == 9);
}

bool TicTacToe::game_is_over(){
    return gameEnd;
}


void TicTacToe::on_gridButtonClicked() {
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



void TicTacToe::on_reset_clicked()
{
    gameEnd = false;
    n_moves = 0;
    player = "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
    ui->result->setText("");
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            board[i][j]->setText("");
        }
    }
}

