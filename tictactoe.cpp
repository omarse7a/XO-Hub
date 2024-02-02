#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QTimer>

/*Default constructor for setting the ui*/
TicTacToe::TicTacToe(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

}

/*Setting ui, intializing game info and connenting buttons to the board array*/
TicTacToe::TicTacToe(QWidget *parent, bool isComputer)
    : QWidget(parent),
    ui(new Ui::TicTacToe)
{
    ui->setupUi(this);

    isComp = isComputer;    //a computer player is added if true
    player = "X";
    n_rows = n_cols = 3;
    // Initializing the board array with button pointers
    board = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j); //getting the button's name
            board[i][j] = findChild<QPushButton*>(buttonName); //connecting the buttons to board array

            //connecting the button click to it's handler(on_gridButtonClicked)
            if (board[i][j]) {  //checking if the board[i][j] is connected to a button
                connect(board[i][j], &QPushButton::clicked, this, &TicTacToe::on_gridButtonClicked);
            }
        }
    }
}

/*Destructing the ui*/
TicTacToe::~TicTacToe()
{
    delete ui;
}

/*Handles switching the turns*/
void TicTacToe::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

/*It makes a move in random position on the board*/
void TicTacToe::random_move(){
    int x, y;
    x = (int) (rand()/(RAND_MAX + 1.0) * 3);
    y = (int) (rand()/(RAND_MAX + 1.0) * 3);
    if(board[x][y]->text() == ""){  //checking if empty
        n_moves++;
        board[x][y]->setText(player);
    }
    else{
        random_move();
    }
}

/*Checking for a winner*/
bool TicTacToe::is_winner() {
    int Xc, Oc;
    // Checking rows
    for (int i = 0; i < 3; i++) {
        Xc = Oc = 0;
        for (int j = 0; j < 3; j++) {
            if (board[i][j]->text() == "X") Xc++; //increment the X counter
            else if (board[i][j]->text() == "O") Oc++; //increment the O counter
        }
        if (Xc == 3 || Oc == 3){
            return true;
        }
    }

    // Checking columns
    for (int i = 0; i < 3; i++) {
        Xc = Oc = 0;
        for (int j = 0; j < 3; j++) {
            if (board[j][i]->text() == "X") Xc++;   //increment the X counter
            else if (board[j][i]->text() == "O") Oc++; //increment the O counter
        }
        if (Xc == 3 || Oc == 3){
            return true;
        }
    }

    // Checking diagonals
    if (board[1][1]->text() == "X") { //middle position is X
        if (board[0][0]->text() == "X" && board[2][2]->text() == "X") {
            return true;
        } else if (board[0][2]->text() == "X" && board[2][0]->text() == "X") {
            return true;
        }
    } else if (board[1][1]->text() == "O") { //middle position is O
        if (board[0][0]->text() == "O" && board[2][2]->text() == "O") {
            gameEnd = true;
            return true;
        } else if (board[0][2]->text() == "O" && board[2][0]->text() == "O") {
            return true;
        }
    }
    return false;
}

/*Checking for a draw*/
bool TicTacToe::is_draw(){
    gameEnd = true;
    return (n_moves == 9);  //when the board is full
}

/*When a winner is decided or a draw*/
bool TicTacToe::game_is_over(){
    return gameEnd;
}

/*Board button handler, It manages the game with each click*/
void TicTacToe::on_gridButtonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());//detecting which button is clicked
    if (clickedButton && !game_is_over()) {
        if (clickedButton->text() == "") { //checking whether this position is empty
            clickedButton->setText(player);
            n_moves++;
            if (is_winner()) { //checking for a winner
                QString text = "The winner is player " + player;
                ui->result->setText(text);
                ui->turn->setText("");
                gameEnd = true;
                return;
            } else if (is_draw()) { //checking for a draw
                QString text = "Draw, no one wins!";
                ui->result->setText(text);
                ui->turn->setText("");
                gameEnd = true;
                return;
            }
            switch_player();
            if(isComp && !game_is_over()){ //when player 2 is computer
                QTimer::singleShot(200, qApp, [this](){ //this makes 200ms delay to see the turn switching
                    random_move();  //computer move
                    if (is_winner()) {  //checking for a winner
                        QString text = "The winner is player " + player;
                        ui->result->setText(text);
                        ui->turn->setText("");
                        gameEnd = true;
                        return;
                    } else if (is_draw()) { //checking for a draw
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


/*This button resets the game info to how it was in the beginning of the game*/
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
            board[i][j]->setText(""); //emptying the board
        }
    }
}

