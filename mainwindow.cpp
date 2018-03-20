// Qt includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qrootfile.h"

#include "map"
#include "QFileDialog"
#include "QFile"
#include "QString"
#include "QStandardItemModel"
#include "QAbstractItemModel"



// ROOT Includes
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TBrowser.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "cstring"
#include "bits/stdc++.h"
#include "cstdio"

const QString filter = "ROOT file (*.root*)";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // setting the ui
    ui->setupUi(this);

    // resetting the graph variable
    fPlot = 0;

    fRootFile = NULL;


  //  connect(ui->histo_list, SIGNAL(clicked(QModelIndex)), this , SLOT(on_histo_list_clicked(QModelIndex)));
}

MainWindow::~MainWindow()
{
    if (fRootFile) {
        delete fRootFile;
    }
    delete ui;
}

void MainWindow::plot_data(TObject *pGraph)
{
    // delete the old plot if it exists
    if(fPlot != 0) ui->qcanvas->getCanvas()->Clear();

    // assign the object (to be able to delete later)
    fPlot = pGraph;
    // set our canvas settings (not fact if all is necessary)

    ui->qcanvas->getCanvas()->cd();
    ui->qcanvas->getCanvas()->GetFrame()->SetFillColor(42);
    ui->qcanvas->getCanvas()->GetFrame()->SetBorderMode(-1);
    ui->qcanvas->getCanvas()->GetFrame()->SetBorderSize(1);

    // draw the graph
    fPlot->Draw();

    // update the canvas
    this->updateCanvas();

}

void MainWindow::on_change_file_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "/home/", filter);
    std::string flnm1 = fileName.toStdString();
    fRootFile = new QROOTFile(flnm1);
    std::map<std::string , TObject *>* newMap = fRootFile->getMap();

    QStandardItemModel *model = new QStandardItemModel(this);
    int h=0;
    for(auto x: (*newMap)){
        QString str=QString::fromStdString(x.first);
        QStandardItem *item = new QStandardItem(str);
        model->setItem(h , item);
        model->index(h, 0);
        h++;
        }

    ui->histo_list->setModel(model);
    ui->histo_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_histo_list_clicked(QModelIndex mIndex)
{
    QString str = mIndex.data().toString();
    std::string objName = str.toStdString();
    std::cout << objName << std::endl;

    plot_data(fRootFile->GetObject(objName));

}

void MainWindow::updateCanvas()
{
    // update the canvas
    ui->qcanvas->getCanvas()->Modified();
    ui->qcanvas->getCanvas()->Update();
}
