#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TObject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void plot_data(TObject *pGraph);
    void on_change_file_clicked();
    void updateCanvas();

private:
    Ui::MainWindow *ui;
    TObject *fPlot;
};

#endif // MAINWINDOW_H
