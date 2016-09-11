#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void show_XO(short m[3][3]);
    void step(QString u, short x, short y);
    void log(QString msg);
    bool win();

private slots:
    void on_btnStart_clicked();
    void on_rPC_clicked();
    void on_rUser_clicked();
    void on_btn00_clicked();
    void on_btn01_clicked();
    void on_btn02_clicked();
    void on_btn10_clicked();
    void on_btn11_clicked();
    void on_btn12_clicked();
    void on_btn20_clicked();
    void on_btn21_clicked();
    void on_btn22_clicked();
    void on_rUvsU_clicked();

private:
    Ui::MainWindow *ui;
    short XO[3][3];     // Игровое поле
    bool startGame;     // Флаг начала игры
    bool full;          // Флаг заполнения игрового поля
    bool blockStep;     // Блокируем ходы, если игрок сходил на уже залятую клетку
    short symbolOfUser; // -1 - нолик, 0 - пробел, 1 - крестик
    short symbolOfPC;
    bool gameUvU;

    struct Point {
        Point(short a, short b) { x = a; y = b; }
        short x;
        short y;
    };
};

#endif // MAINWINDOW_H
