#include "include/tictactoe5x5.h"
#include "ui_tictactoe5x5.h"
#include <QTimer>

/*Default constructor for setting the ui*/
TicTacToe5x5::TicTacToe5x5(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicTacToe5x5)
{
    ui->setupUi(this);
}


/*Setting ui, intializing game info and connenting buttons to the board array*/
TicTacToe5x5::TicTacToe5x5(QWidget *parent, bool isComputer)
    : QWidget(parent)
    , ui(new Ui::TicTacToe5x5)
{
    ui->setupUi(this);
    
    isComp = isComputer;    //a computer player is added if true
    player = "X";
    QString score = QString::number(c1p1) + "      :      " + QString::number(c2p2);
    ui->score->setText(score);
    n_rows = n_cols = 5;
    // Initializing the board array with button pointers
    board = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j); //getting the button's name
            board[i][j] = findChild<QPushButton*>(buttonName); //connecting the buttons to board array

            //connecting the button click to it's handler(on_gridButtonClicked)
            if (board[i][j]) {  //checking if the board[i][j] is connected to a button
                connect(board[i][j], &QPushButton::clicked, this, &TicTacToe5x5::on_gridButtonClicked);
            }
        }
    }
}

//Destroying the memory allocated for the ui
TicTacToe5x5::~TicTacToe5x5()
{
    delete ui;
}

/*Switches the player's turn*/
void TicTacToe5x5::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

/*It makes a move in a random position on the board*/
void TicTacToe5x5::random_move(){
    int x, y;
    x = (int) (rand()/(RAND_MAX + 1.0) * 5); //0-4
    y = (int) (rand()/(RAND_MAX + 1.0) * 5); //0-4
    if(board[x][y]->text() == ""){ //checking if empty
        board[x][y]->setText(player);
    }
    else{
        random_move();
        return;
    }
    n_moves++;
}

/*Counts the points each player scored*/
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

/*Returns true if player 1 wins*/
bool TicTacToe5x5::is_winner(){
    if (c1p1 > c2p2) {
        return true;
    }
    return false;
}

/*Returns true in case of a draw*/
bool TicTacToe5x5::is_draw(){
    return c1p1==c2p2;
}

/*Returns true when the board is full except for 1 position*/
bool TicTacToe5x5::game_is_over(){
    return n_moves >= 24;
}

/*Board button handler, It manages the game with each click*/
void TicTacToe5x5::on_gridButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender()); //detects which button is clicked
    if (clickedButton && !game_is_over()) {
        if (clickedButton->text() == "") {  //checks if this psoition is empty
            clickedButton->setText(player);
            n_moves++;
            countThreeInARows();    //calculates the score
            QString score = QString::number(c1p1) + "      :      " + QString::number(c2p2);
            ui->score->setText(score);
            switch_player();
            if(game_is_over()){
                if (is_winner()) {  //checking if player X is the winner
                    QString text = "The winner is player X";
                    ui->result->setText(text);
                }
                else if (is_draw()) {   //checking for a draw
                    QString text = "Draw, no one wins!";
                    ui->result->setText(text);
                }
                else{   //checking if player O is the winner
                    QString text = "The winner is player O";
                    ui->result->setText(text);
                }
                ui->turn->setText(""); //clearing the turn text
            }
            else if(isComp && !game_is_over()){
                QTimer::singleShot(200, qApp, [this](){ //this makes 200ms delay to see the turn switching for each computer play
                    random_move();
                    countThreeInARows();
                    QString score = QString::number(c1p1) + "      :      " + QString::number(c2p2);
                    ui->score->setText(score);
                    if(!game_is_over()){
                        switch_player();
                    }
                    else{
                        countThreeInARows();
                        if (is_winner()) { //checking if player X is the winner
                            QString text = "The winner is player X";
                            ui->result->setText(text);
                        }
                        else if (is_draw()) { //checking for a draw
                            QString text = "Draw, no one wins!";
                            ui->result->setText(text);
                        }
                        else{   //checking if player O is the winner
                            QString text = "The winner is player O";
                            ui->result->setText(text);
                        }
                        ui->turn->setText("");  //clearing the turn text
                    }
                });
            }
        }
    }
}

/*This button resets the game info to how it was in the beginning of the game*/
void TicTacToe5x5::on_reset_clicked() {
    c1p1 = 0, c2p2 = 0; //reseting the score
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
            board[i][j]->setText("");   //clearing the board
        }
    }
}
