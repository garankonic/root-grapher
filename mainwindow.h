#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "TObject.h"
#include "qrootfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Ui::MainWindow *ui;

private slots:
    void plot_data(TObject *pGraph);
    void on_change_file_clicked();
    void updateCanvas();
    void on_histo_list_clicked(QModelIndex mIndex);

private:
    TObject *fPlot;
    QROOTFile *fRootFile;
};

#endif // MAINWINDOW_H
