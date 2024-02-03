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

/*This class manages the game menu and transitions from one form to another*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_confirm_clicked();

    void on_btn_XO_clicked();

    void on_btn_XO_pyr_clicked();

    void on_btn_connect_4_clicked();

    void on_btn_XO_5_clicked();

    void on_backToMain_clicked();

    void on_btn_instructions_clicked();

private:
    Ui::MainWindow *ui;
    TicTacToe* XO;
    Pyramid_XO* pyr_XO;
    Connect4* connect4;
    TicTacToe5x5* XO5by5;
};
#endif // MAINWINDOW_H
