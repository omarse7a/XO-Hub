#ifndef BOARDGAMES_CLASSES_HPP
#define BOARDGAMES_CLASSES_HPP

#include <QPushButton>

/*It represents a board of buttons for the XO games with options for
    player-vs-player or player-vs-computer modes*/
class Board {
protected:
    int n_rows, n_cols;
    QPushButton*** board;
    int  n_moves = 0;
    QString player;
    bool isComp, gameEnd = false;
public:
    //Switch the players' turns
    virtual void switch_player() = 0;
    // Makes random move for the computer player
    virtual void random_move() = 0;
    // Returns true if there is any winner
    // either X or O
    // Written in a complex way. DO NOT DO LIKE THIS.
    virtual bool is_winner() = 0;
    // Return true if all moves are done and no winner
    virtual bool is_draw() = 0;
    // Return true if game is over
    virtual bool game_is_over() = 0;

};

// class Player{
// protected:
//     QString name;
//     QString symbol;
//     bool isComp = false;
// public:
//     Player(QString n, QString s);
//     Player(QString n, QString s, bool c);
//     QString getName();
//     QString getSymbol();
//     bool isComputer();
// };


#endif // BOARDGAMES_CLASSES_HPP
