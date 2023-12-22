#ifndef PYRAMID_XO_H
#define PYRAMID_XO_H

#include <QWidget>
#include <QPushButton>
#include "BoardGames_Classes.hpp"

namespace Ui {
class Pyramid_XO;
}

class Pyramid_XO : public QWidget, public Board
{
    Q_OBJECT

public:
    explicit Pyramid_XO(QWidget *parent = nullptr);
    Pyramid_XO(QWidget *parent = nullptr, bool isComputer = false);
    ~Pyramid_XO();
    void switch_player();
    void random_move();
    bool is_winner();
    bool is_draw();
    bool game_is_over();

private slots:
    void on_gridButtonClicked();

    void on_reset_clicked();

private:
    Ui::Pyramid_XO *ui;
};

#endif // PYRAMID_XO_H
