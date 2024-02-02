#include "connect4.h"
#include "ui_connect4.h"
#include <QTimer>

Connect4::Connect4(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Connect4)
{
    ui->setupUi(this);
}

Connect4::Connect4(QWidget *parent, bool isComputer)
    : QWidget(parent)
    , ui(new Ui::Connect4)
{
    ui->setupUi(this);

    isComp = isComputer;

    player = "X";
    n_rows = 6;
    n_cols = 7;
    // Initializing array board with pointers to buttons
    board = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j);
            board[i][j] = findChild<QPushButton*>(buttonName);
            if (board[i][j]) {
                connect(board[i][j], &QPushButton::clicked, this, &Connect4::on_gridButtonClicked);
            }
        }
    }
}

Connect4::~Connect4()
{
    delete ui;
}

void Connect4::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

void Connect4::random_move(){
    int y;
    y = (int) (rand()/(RAND_MAX + 1.0) * 7);
    for(int i = 5; i >= 0; i--){
        if(board[i][y]->text() == ""){
            board[i][y]->setText(player);
            n_moves++;
            return;
        }
    }
    random_move();
}

bool Connect4::is_winner(){
    int Xc, Oc;
    // Checking rows
    for (int i = 0; i < n_rows; i++) {
        Xc = Oc = 0;
        for (int j = 0; j < n_cols; j++){
            if(Xc < 4 && Oc < 4){
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
        if (Xc == 4 || Oc == 4){
            return true;
        }
    }
    // Checking columns
    for (int i = 0; i < n_cols; i++) {
        Xc = Oc = 0;
        for (int j = 0; j < n_rows; j++){
            if(Xc < 4 && Oc < 4){
                if (board[j][i]->text() == "X"){
                    Oc = 0;
                    Xc++;
                }
                else if (board[j][i]->text() == "O") {
                    Xc = 0;
                    Oc++;
                }
                else{
                    Xc = Oc = 0;
                }
            }
        }
        if (Xc == 4 || Oc == 4){
            return true;
        }
    }
    // Check from bottom-left to top-right diagonals
    for (int i = 0; i < n_rows - 3; i++) {
        for (int j = 0; j < n_cols - 3; j++) {
            if (board[i][j]->text() != "" &&
                board[i][j]->text() == board[i + 1][j + 1]->text() &&
                board[i][j]->text() == board[i + 2][j + 2]->text() &&
                board[i][j]->text() == board[i + 3][j + 3]->text()) {
                return true;
            }
        }
    }

    // Check from bottom-right to top-left diagonals
    for (int i = 0; i < n_rows - 3; i++) {
        for (int j = 3; j < n_cols; j++) {
            if (board[i][j]->text() != "" &&
                board[i][j]->text() == board[i + 1][j - 1]->text() &&
                board[i][j]->text() == board[i + 2][j - 2]->text() &&
                board[i][j]->text() == board[i + 3][j - 3]->text()) {
                return true;
            }
        }
    }

    return false;

}

bool Connect4::is_draw(){
    return n_moves == 42;
}

bool Connect4::game_is_over(){
    return gameEnd;
}

void Connect4::on_gridButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton && !game_is_over()) {
        int x, y;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                if(clickedButton == board[i][j]){
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        for(int i = 5; i >= x; i--){
            if(board[i][y]->text() == ""){
                board[i][y]->setText(player);
                n_moves++;
                break;
            }
        }
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


void Connect4::on_reset_clicked()
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

