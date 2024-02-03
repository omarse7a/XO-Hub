#include "include/pyramid_xo.h"
#include "ui_pyramid_xo.h"
#include <QTimer>

/*Default constructor for setting the ui*/
Pyramid_XO::Pyramid_XO(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pyramid_XO)
{
    ui->setupUi(this);
}

/*Setting ui, intializing game info and connenting buttons to the board array*/
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
            QString buttonName = QString("btn_grid%1%2").arg(i).arg(j); //getting the button's name
            board[i][j] = findChild<QPushButton*>(buttonName);  //connecting the buttons to board array

            //connecting the button click to it's handler(on_gridButtonClicked)
            if (board[i][j]) {  //checking if the board[i][j] is connected to a button
                connect(board[i][j], &QPushButton::clicked, this, &Pyramid_XO::on_gridButtonClicked);
            }
        }
        n_cols += 2;  //incrementing the # of columns for each row to make a pyramid shape
    }
}

/*Destructing the ui*/
Pyramid_XO::~Pyramid_XO()
{
    delete ui;
}

/*Handles switching the turns*/
void Pyramid_XO::switch_player(){
    player = (player == "X") ? "O" : "X";
    QString turn = "Turn: Player " + player;
    ui->turn->setText(turn);
}

/*This function makes a move in random position on the board*/
void Pyramid_XO::random_move(){
    int x, y;
    x = (int) (rand()/(RAND_MAX + 1.0) * 3); //0-2
    if(x == 0) //the top of the pyramid
        y = 0;
    else if(x == 1){ //the second row
        y = (int) (rand()/(RAND_MAX + 1.0) * 3); //0-2
    }
    else{   //the third row
        y = (int) (rand()/(RAND_MAX + 1.0) * 5); //0-4
    }
    if(board[x][y]->text() == ""){ //checking availability
        board[x][y]->setText(player);
        n_moves++;
    }
    else{
        random_move();
        return;
    }
}

/*Checks for a winner*/
bool Pyramid_XO::is_winner(){
    //Checking rows
    n_cols = 1;
    int Xc, Oc;
    for (int i = 0; i < n_rows; i++) {
        Xc = Oc = 0;    //reset the counters
        for (int j = 0; j < n_cols; j++){
            if(Xc < 3 && Oc < 3){
                if (board[i][j]->text() == "X"){ //when X is detected
                    Oc = 0; //reset O's counter
                    Xc++;   //increment the X's counter
                }
                else if (board[i][j]->text() == "O") { //when O is detected
                    Xc = 0; //reset X's counter
                    Oc++;   //increment the X's counter
                }
                else{   //when a position is empty
                    Xc = Oc = 0;
                }
            }  
        }
        if (Xc == 3 || Oc == 3){ //a winner is determined
            return true;
        }
        n_cols += 2;
    }
    //Checking the column and diagonals where the top position is not empty
    if(board[0][0]->text() != "" && ((board[0][0]->text() == board[1][1]->text() && board[1][1]->text() == board[2][2]->text())
         ||(board[0][0]->text() == board[1][0]->text() && board[1][0]->text() == board[2][0]->text())
         || (board[0][0]->text() == board[1][2]->text() && board[1][2]->text() == board[2][4]->text()))){
        return true;
    }
    return false;
}

/*Checks for a draw*/
bool Pyramid_XO::is_draw(){
    return n_moves == 9;    //the board is full
}

/*When a winner is decided or a draw*/
bool Pyramid_XO::game_is_over(){
    return gameEnd;
}

/*Board button handler, It manages the game with each click*/
void Pyramid_XO::on_gridButtonClicked(){
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender()); //detects which button is clicked
    if (clickedButton && !game_is_over()) {
        if (clickedButton->text() == "") {  //checking if this position is empty
            clickedButton->setText(player);
            n_moves++;
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
            switch_player(); //switching turns
            if(isComp && !game_is_over()){ //when a computer player option is selected
                QTimer::singleShot(200, qApp, [this](){ //this makes 200ms delay to see the turn switching each play
                    random_move();
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
                    switch_player();  //switching turns
                });
            }
        }
    }
}

/*This button resets the game info to how it was in the beginning of the game*/
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
            board[i][j]->setText("");   //clearing the board
        }
        n_cols += 2;
    }
}

