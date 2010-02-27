#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class State;
class Plot;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    State *state;
    Plot *plot;
};

#endif // MAINWINDOW_H
