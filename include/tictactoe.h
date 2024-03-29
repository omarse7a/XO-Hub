#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>
#include "BoardGames_Classes.hpp"

namespace Ui {
class TicTacToe;
}

/*This class represents the tictactoe game handling the game's logic
  and board management*/
class TicTacToe : public QWidget, public Board  //multiple inheritance
{
    Q_OBJECT

public:
    explicit TicTacToe(QWidget *parent = nullptr);
    TicTacToe(QWidget *parent, bool isComputer = false);
    ~TicTacToe();
    void switch_player();
    void random_move();
    bool is_winner();
    bool is_draw();
    bool game_is_over();

private slots:
    void on_gridButtonClicked();

    void on_reset_clicked();

private:
    Ui::TicTacToe *ui;
};

#endif // TICTACTOE_H
