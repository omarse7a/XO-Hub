#include "include/connect4.h"
#include "ui_connect4.h"
#include <QTimer>

/*Default constructor for setting the ui*/
Connect4::Connect4(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Connect4)
{
    ui->setupUi(this);
}

/*Setting ui, intializing game info and connenting buttons to the board array*/
Connect4::Connect4(QWidget *parent, bool isComputer)
    : QWidget(parent)
    , ui(new Ui::Connect4)
{
    ui->setupUi(this);

    isComp = isComputer;    //a computer player is added if true
    player = "X";
    n_rows = 6;
    n_cols = 7;
    // Initializing the board array with button pointers
    board = new QPushButton**[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        board[i] = new QPushButton*[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j); //getting the button's name
            board[i][j] = findChild<QPushButton*>(buttonName); //connecting the buttons to board array

            //connecting the button click to it's handler(on_gridButtonClicked)
            if (board[i][j]) {  //checking if the board[i][j] is connected to a button
                connect(board[i][j], &QPushButton::clicked, this, &Connect4::on_gridButtonClicked);
            }
        }
    }
}

//Destroying the memory allocated for the ui
Connect4::~Connect4()
{
    delete ui;
}

/*Handles switching the turns*/
void Connect4::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

/*Generates a random move on any of the 7 columns and puts the symbol
  at the lowest available position*/
void Connect4::random_move(){
    int y;
    y = (int) (rand()/(RAND_MAX + 1.0) * 7); //0-6
    for(int i = 5; i >= 0; i--){
        if(board[i][y]->text() == ""){  //checking availability
            board[i][y]->setText(player);
            n_moves++;
            return;
        }
    }
    random_move();
}

/*Checks for a winner*/
bool Connect4::is_winner(){
    int Xc, Oc;
    //check rows
    for (int i = 0; i < n_rows; i++) {
        Xc = Oc = 0;    //reset the counters for each row
        for (int j = 0; j < n_cols; j++){
            if(Xc < 4 && Oc < 4){
                if (board[i][j]->text() == "X"){
                    Oc = 0; //reset O's counter
                    Xc++;   //increment the X's counter
                }
                else if (board[i][j]->text() == "O") {
                    Xc = 0; //reset X's counter
                    Oc++;   //increment the O's counter
                }
                else{   //when a position is empty
                    Xc = Oc = 0;
                }
            }
        }
        if (Xc == 4 || Oc == 4){ //a winner is determined
            return true;
        }
    }
    //checking columns
    for (int i = 0; i < n_cols; i++) {
        Xc = Oc = 0;    //reset the counters for each column
        for (int j = 0; j < n_rows; j++){
            if(Xc < 4 && Oc < 4){
                if (board[j][i]->text() == "X"){
                    Oc = 0; //reset O's counter
                    Xc++;   //increment the X's counter
                }
                else if (board[j][i]->text() == "O") {
                    Xc = 0; //reset X's counter
                    Oc++;   //increment the O's counter
                }
                else{   //when a position is empty
                    Xc = Oc = 0;
                }
            }
        }
        if (Xc == 4 || Oc == 4){ //a winner is determined
            return true;
        }
    }
    //check from bottom-right to top-left diagonals
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
    //check from bottom-left to top-right diagonals
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
    return false;
}

/*Checks for a draw*/
bool Connect4::is_draw(){
    return n_moves == 42; //the board in full
}

/*When a winner is decided or a draw*/
bool Connect4::game_is_over(){
    return gameEnd;
}

/*Grid button handler, it puts the player's symbol in the lowest available position
  in the specified column and manages the game logic with each click*/
void Connect4::on_gridButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender()); //detects which button is clicked
    if (clickedButton && !game_is_over()) {
        int x, y;
        //getting the clicked button indices
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                if(clickedButton == board[i][j]){
                    x = i;
                    y = j;
                    break;
                }
            }
        }
        //putting the player's symbol in the lowest available position
        for(int i = 5; i >= x; i--){
            if(board[i][y]->text() == ""){  //checking whether this position is empty
                board[i][y]->setText(player);
                n_moves++;
                break;
            }
        }
        if (is_winner()) { //checking for a winner
            QString text = "The winner is player " + player;
            ui->result->setText(text);
            ui->turn->setText("");  //clearing the turn text
            gameEnd = true;
            return;
        } else if (is_draw()) { //checking for a draw
            QString text = "Draw, no one wins!";
            ui->result->setText(text);
            ui->turn->setText("");  //clearing the turn text
            gameEnd = true;
            return;
        }
        switch_player();

        if(isComp && !game_is_over()){
            QTimer::singleShot(200, qApp, [this](){ //this makes 200ms delay to see the turn switching each play
                random_move();
                if (is_winner()) {  //checking for a winner
                    QString text = "The winner is player " + player;
                    ui->result->setText(text);
                    ui->turn->setText("");  //clearing the turn text
                    gameEnd = true;
                    return;
                } else if (is_draw()) { //checking for a draw
                    QString text = "Draw, no one wins!";
                    ui->result->setText(text);
                    ui->turn->setText("");  //clearing the turn text
                    gameEnd = true;
                    return;
                }
                switch_player();
            });
        }
    }
}

/*This button resets the game info to how it was in the beginning of the game*/
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
            board[i][j]->setText(""); //clearing the board
        }
    }
}
