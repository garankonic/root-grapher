#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QShowEvent>
#include <QDebug>

#include <stdlib.h>

#include <TCanvas.h>
#include <TVirtualX.h>
#include <TSystem.h>
#include <TApplication.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1.h>
#include <TFrame.h>
#include <TTimer.h>
#include "canvas.h"


//--------------------------------------------------------------------------------

QRootCanvas::QRootCanvas(QWidget *parent) :
             QWidget(parent, 0), fCanvas(0)
{
   setMinimumSize(600, 500);
   setMouseTracking(kTRUE);

   int wid = gVirtualX->AddWindow((ULong_t)winId(),600,500);
   fCanvas = new TCanvas("Root Canvas",width(),height(),wid);
}

void QRootCanvas::mouseMoveEvent(QMouseEvent *e)
{
   if (fCanvas) {
      if (e->buttons() & Qt::LeftButton) {
         fCanvas->HandleInput(kButton1Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::MidButton) {
         fCanvas->HandleInput(kButton2Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::RightButton) {
         fCanvas->HandleInput(kButton3Motion, e->x(), e->y());
      } else {
         fCanvas->HandleInput(kMouseMotion, e->x(), e->y());
      }
   }
}

void QRootCanvas::mousePressEvent( QMouseEvent *e )
{
   if (fCanvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            fCanvas->HandleInput(kButton1Down, e->x(), e->y());
            break;
         case Qt::MidButton :
            fCanvas->HandleInput(kButton2Down, e->x(), e->y());
            break;
         case Qt::RightButton :
            // does not work properly on Linux...
#ifdef WIN32
            fCanvas->HandleInput(kButton3Down, e->x(), e->y());
#endif
            break;
         default:
            break;
      }
   }
}

void QRootCanvas::mouseReleaseEvent( QMouseEvent *e )
{
   if (fCanvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            fCanvas->HandleInput(kButton1Up, e->x(), e->y());
            break;
         case Qt::MidButton :
            fCanvas->HandleInput(kButton2Up, e->x(), e->y());
            break;
         case Qt::RightButton :
            // does not work properly on Linux...
#ifdef WIN32
            fCanvas->HandleInput(kButton3Up, e->x(), e->y());
#endif
            break;
         default:
            break;
      }
   }
}

void QRootCanvas::resizeEvent( QResizeEvent * )
{
   if (fCanvas) {
      fCanvas->Resize();
      fCanvas->Update();
   }
}

void QRootCanvas::paintEvent( QPaintEvent * )
{
   if (fCanvas) {
      fCanvas->Resize();
      fCanvas->Update();
   }
}
