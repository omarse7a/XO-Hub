#include "tictactoe5x5.h"
#include "ui_tictactoe5x5.h"
#include <QTimer>

TicTacToe5x5::TicTacToe5x5(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicTacToe5x5)
{
    ui->setupUi(this);
}

TicTacToe5x5::TicTacToe5x5(QWidget *parent, bool isComputer)
    : QWidget(parent)
    , ui(new Ui::TicTacToe5x5)
{
    ui->setupUi(this);

    isComp = isComputer;

    player = "X";
    QString score = QString::number(c1p1) + "      :      " + QString::number(c2p2);
    ui->score->setText(score);
    n_rows = n_cols = 5;
    // Initialize the board with button pointers
    board = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j);
            board[i][j] = findChild<QPushButton*>(buttonName);

            if (board[i][j]) {
                connect(board[i][j], &QPushButton::clicked, this, &TicTacToe5x5::on_gridButtonClicked);
            }
        }
    }
}

TicTacToe5x5::~TicTacToe5x5()
{
    delete ui;
}

void TicTacToe5x5::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

void TicTacToe5x5::random_move(){
    int x, y;
    x = (int) (rand()/(RAND_MAX + 1.0) * 5);
    y = (int) (rand()/(RAND_MAX + 1.0) * 5);
    if(board[x][y]->text() == ""){

        board[x][y]->setText(player);
    }
    else{
        random_move();
        return;
    }
    n_moves++;
}

void TicTacToe5x5::countThreeInARows(){
    c1p1 = 0, c2p2 = 0;
    // Check rows
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= 2; ++j) {
            if (board[i][j]->text() == "X" && board[i][j + 1]->text() == "X" && board[i][j + 2]->text() == "X") {
                c1p1++;
            }
            else if (board[i][j]->text() == "O" && board[i][j + 1]->text() == "O" && board[i][j + 2]->text() == "O") {
                c2p2++;
            }
        }
    }

    // Check columns
    for (int j = 0; j < 5; ++j) {
        for (int i = 0; i <= 2; ++i) {
            if (board[i][j]->text() == "X" && board[i + 1][j]->text() == "X" && board[i + 2][j]->text() == "X") {
                c1p1++;
            }
            else if (board[i][j]->text() == "O" && board[i + 1][j]->text() == "O" && board[i + 2][j]->text() == "O") {
                c2p2++;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 2; ++j) {
            if (board[i][j]->text() == "X" && board[i + 1][j + 1]->text() == "X" && board[i + 2][j + 2]->text() == "X") {
                c1p1++;
            }
            else if (board[i][j]->text() == "O" && board[i + 1][j + 1]->text() == "O" && board[i + 2][j + 2]->text() == "O") {
                c2p2++;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= 2; ++i) {
        for (int j = 4; j >= 2; --j) {
            if (board[i][j]->text() == "X" && board[i + 1][j - 1]->text() == "X" && board[i + 2][j - 2]->text() == "X") {
                c1p1++;
            }
            if (board[i][j]->text() == "O" && board[i + 1][j - 1]->text() == "O" && board[i + 2][j - 2]->text() == "O") {
                c2p2++;
            }
        }
    }
    return;

}

bool TicTacToe5x5::is_winner(){
    if (c1p1 > c2p2) {
        return true;
    }
    return false;
}

bool TicTacToe5x5::is_draw(){
    return c1p1==c2p2;
}

bool TicTacToe5x5::game_is_over(){
    return n_moves >= 24;
}

void TicTacToe5x5::on_gridButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton && !game_is_over()) {
        if (clickedButton->text() == "") {
            clickedButton->setText(player);
            n_moves++;
            countThreeInARows();
            QString score = QString::number(c1p1) + "      :      " + QString::number(c2p2);
            ui->score->setText(score);
            switch_player();
            if(game_is_over()){
                if (is_winner()) {
                    QString text = "The winner is player X";
                    ui->result->setText(text);
                }
                else if (is_draw()) {
                    QString text = "Draw, no one wins!";
                    ui->result->setText(text);
                }
                else{
                    QString text = "The winner is player O";
                    ui->result->setText(text);
                }
                ui->turn->setText("");
            }
            else if(isComp && !game_is_over()){
                QTimer::singleShot(200, qApp, [this](){
                    random_move();
                    countThreeInARows();
                    QString score = QString::number(c1p1) + "      :      " + QString::number(c2p2);
                    ui->score->setText(score);
                    if(!game_is_over()){
                        switch_player();
                    }
                    else{
                        countThreeInARows();
                        if (is_winner()) {
                            QString text = "The winner is player X";
                            ui->result->setText(text);
                        }
                        else if (is_draw()) {
                            QString text = "Draw, no one wins!";
                            ui->result->setText(text);
                        }
                        else{
                            QString text = "The winner is player O";
                            ui->result->setText(text);
                        }
                        ui->turn->setText("");
                    }
                });
            }
        }
    }
}

void TicTacToe5x5::on_reset_clicked() {
    c1p1 = 0, c2p2 = 0;
    gameEnd = false;
    n_moves = 0;
    player = "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
    ui->result->setText("");
    QString score = QString::number(c1p1) + "      :      " + QString::number(c2p2);
    ui->score->setText(score);
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            board[i][j]->setText("");
        }
    }
}
