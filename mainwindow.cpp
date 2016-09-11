#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    for (int i = 0, j; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            XO[i][j] = 0;
        }
    }
    show_XO(XO);
    startGame = false;
    blockStep = false;

    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Выберите ходящего первым!");
    ui->btnStart->setHidden(true);

    srand(time(0));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnStart_clicked() {
    if (ui->rPC->isChecked() || ui->rUser->isChecked() || ui->rUvsU->isChecked()){
        if (!startGame){
            startGame = true;
            ui->statusBar->clearMessage();
            ui->log->clear();

            for (int i = 0, j; i < 3; ++i) {
                for (j = 0; j < 3; ++j) {
                    XO[i][j] = 0;
                }
            }
            show_XO(XO);

            ui->lblWind->clear();
            log("<p><b>Игра началась!</b></p>");
            ui->btnStart->setText("Стоп");
            ui->groupBox->setEnabled(false);
            if (ui->rPC->isChecked()) {
                step("pc", 0, 0);
            }
        } else {

            startGame = false;
            ui->statusBar->clearMessage();
            log("<p><b>Конец игры!</b></p>");
            ui->btnStart->setText("Старт");
            ui->groupBox->setEnabled(true);

            for (int i = 0, j; i < 3; ++i) {
                for (j = 0; j < 3; ++j) {
                    XO[i][j] = 0;
                }
            }
            show_XO(XO);
        }
    }
}

void MainWindow::on_rPC_clicked() {
    ui->btnStart->setText("Старт");
    ui->btnStart->setHidden(false);
    symbolOfUser = -1;
    symbolOfPC = 1;
    gameUvU = false;
}

void MainWindow::on_rUser_clicked() {
    ui->btnStart->setText("Старт");
    ui->btnStart->setHidden(false);
    symbolOfUser = 1;
    symbolOfPC = -1;
    gameUvU = false;
}

void MainWindow::on_rUvsU_clicked() {
    ui->btnStart->setText("Старт");
    ui->btnStart->setHidden(false);
    symbolOfUser = 1;
    gameUvU = true;
}

void MainWindow::show_XO(short m[3][3]) {
    if (m[0][0]) {
        if (m[0][0] == 1) {
            ui->btn00->setText("X");
        } else {
            ui->btn00->setText("O");
        }
    } else {
        ui->btn00->setText(" ");
    }

    if (m[0][1]) {
        if (m[0][1] == 1) {
            ui->btn01->setText("X");
        } else {
            ui->btn01->setText("O");
        }
    } else {
        ui->btn01->setText(" ");
    }

    if (m[0][2]) {
        if (m[0][2] == 1) {
            ui->btn02->setText("X");
        } else {
            ui->btn02->setText("O");
        }
    } else {
        ui->btn02->setText(" ");
    }

    if (m[1][0]) {
        if (m[1][0] == 1) {
            ui->btn10->setText("X");
        } else {
            ui->btn10->setText("O");
        }
    } else {
        ui->btn10->setText(" ");
    }

    if (m[1][1]) {
        if (m[1][1] == 1) {
            ui->btn11->setText("X");
        } else {
            ui->btn11->setText("O");
        }
    } else {
        ui->btn11->setText(" ");
    }

    if (m[1][2]) {
        if (m[1][2] == 1) {
            ui->btn12->setText("X");
        } else {
            ui->btn12->setText("O");
        }
    } else {
        ui->btn12->setText(" ");
    }

    if (m[2][0]) {
        if (m[2][0] == 1) {
            ui->btn20->setText("X");
        } else {
            ui->btn20->setText("O");
        }
    } else {
        ui->btn20->setText(" ");
    }

    if (m[2][1]) {
        if (m[2][1] == 1) {
            ui->btn21->setText("X");
        } else {
            ui->btn21->setText("O");
        }
    } else {
        ui->btn21->setText(" ");
    }

    if (m[2][2]) {
        if (m[2][2] == 1) {
            ui->btn22->setText("X");
        } else {
            ui->btn22->setText("O");
        }
    } else {
        ui->btn22->setText(" ");
    }

}

void MainWindow::step(QString u, short x, short y) {
    if (startGame){
        bool fStep = false;
        if (u == "pc") {
            std::vector<Point> freeCells;
            for (short i = 0, j; i < 3; ++i) {
                for (j = 0; j < 3; ++j) {
                    if (!XO[i][j]) {
                        Point x(i, j);
                        freeCells.push_back(x);
                    }
                }
            }
            if (freeCells.size()) {
                if (!blockStep) {
                        int step_pc = rand() % freeCells.size();
                        XO[freeCells[step_pc].x][freeCells[step_pc].y] = symbolOfPC;
                    }
                for (short i = 0, j; i < 3; ++i) {
                    for (j = 0; j < 3; ++j) {
                        if (!XO[i][j]) {
                            fStep = true;
                            break;
                        }
                    }
                }
            } else {
                fStep = false;
            }
        }
        if (u == "user") {
            bool st = false;
            for (short i = 0, j; i < 3; ++i) {
                for (j = 0; j < 3; ++j) {
                    if (!XO[i][j]) {
                        st = true;
                    }
                }
            }
            if (st) {
                if (!XO[x][y]) {
                    XO[x][y] = symbolOfUser;
                        if (gameUvU) { symbolOfUser = (symbolOfUser == 1) ? -1 : 1; }
                    blockStep = false;
                } else {
                    log("<p><b>Предупреждение!</b> Данная клетка уже занята! Выберите пустую!</p>");
                    blockStep = true;
                    return;
                }
                fStep = true;
            } else {
                fStep = false;
            }
        }

        if (fStep) {
            if (!blockStep) {
                log("<p>Игрок <b>" + u + (gameUvU ? (symbolOfUser == 1 ? " (O)" : " (X)") : "") + "</b> совершил ход!</p>");
            }
        } else {
            log("<p>Ходов больше нет!</p>");
            startGame = false;
            ui->btnStart->setText("Старт");
            ui->groupBox->setEnabled(true);
            ui->lblWind->setText("Ничья!");
        }

        if (win()) {
            ui->lblWind->setText(u + (gameUvU ? (symbolOfUser == 1 ? " (O)" : " (X)") : "")+ " win!");
        }
    }

    show_XO(XO);
}

void MainWindow::log(QString msg){
    ui->log->appendHtml(msg);
}

bool MainWindow::win() {
    bool w = false;
    if (XO[1][1]){
        if ((XO[1][0] == XO[1][1]) && (XO[1][1] == XO[1][2])) {
            w = true;
        }
        if ((XO[0][0] == XO[1][1]) && (XO[1][1] == XO[2][2])) {
            w = true;
        }
        if ((XO[0][1] == XO[1][1]) && (XO[1][1] == XO[2][1])) {
            w =  true;
        }
        if ((XO[2][0] == XO[1][1]) && (XO[1][1] == XO[0][2])) {
            w =  true;
        }
    }
    if (XO[1][0]) {
        if ((XO[0][0] == XO[1][0]) && (XO[1][0] == XO[2][0])) {
            w =  true;
        }
    }
    if (XO[0][1]) {
        if ((XO[0][0] == XO[0][1]) && (XO[0][1] == XO[0][2])) {
            w =  true;
        }
    }
    if (XO[1][2]) {
        if ((XO[0][2] == XO[1][2]) && (XO[1][2] == XO[2][2])) {
            w =  true;
        }
    }
    if (XO[2][1]) {
        if ((XO[2][0] == XO[2][1]) && (XO[2][1] == XO[2][2])) {
            w =  true;
        }
    }

    if (w) {
        startGame = false;
        ui->btnStart->setText("Старт");
        ui->groupBox->setEnabled(true);
        log("<p><b>Конец игры!</b></p>");
    }

    bool st = true;
    for (short i = 0, j; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (!XO[i][j]) {
                st = false;
            }
        }
    }
    if (st) {
        log("<p>Ходов больше нет!</p>");
        startGame = false;
        ui->btnStart->setText("Старт");
        ui->groupBox->setEnabled(true);
        ui->lblWind->setText("Ничья!");
    }

    return w;
}

void MainWindow::on_btn00_clicked(){
    step("user", 0, 0);
    if (!gameUvU) step("pc", 0, 0);
}


void MainWindow::on_btn01_clicked() {
    step("user", 0, 1);
    if (!gameUvU) step("pc", 0, 0);
}

void MainWindow::on_btn02_clicked() {
    step("user", 0, 2);
    if (!gameUvU) step("pc", 0, 0);
}

void MainWindow::on_btn10_clicked() {
    step("user", 1, 0);
    if (!gameUvU) step("pc", 0, 0);
}

void MainWindow::on_btn11_clicked() {
    step("user", 1, 1);
    if (!gameUvU) step("pc", 0, 0);
}

void MainWindow::on_btn12_clicked() {
    step("user", 1, 2);
    if (!gameUvU) step("pc", 0, 0);
}

void MainWindow::on_btn20_clicked() {
    step("user", 2, 0);
    if (!gameUvU) step("pc", 0, 0);
}

void MainWindow::on_btn21_clicked() {
    step("user", 2, 1);
    if (!gameUvU) step("pc", 0, 0);
}

void MainWindow::on_btn22_clicked() {
    step("user", 2, 2);
    if (!gameUvU) step("pc", 0, 0);
}
