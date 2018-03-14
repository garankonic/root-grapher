// Qt includes
#include "mainwindow.h"
#include "ui_mainwindow.h"

// ROOT Includes
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // setting the ui
    ui->setupUi(this);

    // resetting the graph variable
    fPlot = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::plot_data(TObject *pGraph) {

    // delete the old plot if it exists
    if(fPlot != 0) delete fPlot;

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
    // generate random data
    TH1F *h1f = new TH1F("h1f","Test random numbers",200,-10,10);
    h1f->SetFillColor(45);
    h1f->FillRandom("gaus",10000);

    // draw it
    plot_data((TObject*)h1f);
}

void MainWindow::updateCanvas()
{
    // update the canvas
    ui->qcanvas->getCanvas()->Modified();
    ui->qcanvas->getCanvas()->Update();
}
