#ifndef TICTACTOE5X5_H
#define TICTACTOE5X5_H

#include <QWidget>
#include "BoardGames_Classes.hpp"

namespace Ui {
class TicTacToe5x5;
}

class TicTacToe5x5 : public QWidget, public Board
{
    Q_OBJECT

public:
    explicit TicTacToe5x5(QWidget *parent = nullptr);
    TicTacToe5x5(QWidget *parent = nullptr, bool isComputer = false);
    ~TicTacToe5x5();
    void switch_player();
    void random_move();
    bool determineWinner();
    void countThreeInARows();
    bool is_winner();
    bool is_draw();
    bool game_is_over();

private slots:
    void on_gridButtonClicked();

    void on_reset_clicked();

private:
    Ui::TicTacToe5x5 *ui;
    int c1p1 = 0, c2p2 = 0;
};

#endif // TICTACTOE5X5_H
