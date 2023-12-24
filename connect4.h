#ifndef CONNECT4_H
#define CONNECT4_H

#include <QWidget>
#include "BoardGames_Classes.hpp"

namespace Ui {
class Connect4;
}

class Connect4 : public QWidget, public Board
{
    Q_OBJECT

public:
    explicit Connect4(QWidget *parent = nullptr);
    Connect4(QWidget *parent = nullptr, bool isComputer = false);
    ~Connect4();
    void switch_player();
    void random_move();
    bool is_winner();
    bool is_draw();
    bool game_is_over();

private slots:
    void on_gridButtonClicked();

    void on_reset_clicked();

private:
    Ui::Connect4 *ui;
};

#endif // CONNECT4_H
