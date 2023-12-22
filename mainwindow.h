#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tictactoe.h"
#include "pyramid_xo.h"
#include "connect4.h"
#include "tictactoe5x5.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void confirm();

    void on_btn_confirm_clicked();

    void on_btn_XO_clicked();

    void on_btn_XO_pyr_clicked();

    void on_btn_connect_4_clicked();

    void on_btn_XO_5_clicked();

    void on_backToMain_clicked();

    void on_add_player_toggled(bool checked);

    void on_name1_returnPressed();

    void on_name2_returnPressed();

private:
    Ui::MainWindow *ui;
    TicTacToe* XO;
    Pyramid_XO* pyr_XO;
    Connect4* connect4;
    TicTacToe5x5* XO5by5;
};
#endif // MAINWINDOW_H
