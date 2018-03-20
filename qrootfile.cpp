#include "qrootfile.h"
#include "mainwindow.h"

#include "QStandardItemModel"

#include "TFile.h"
#include "TObject.h"

#include <map>
#include <iostream>

QROOTFile::QROOTFile(std::string flnm)
{
    fFileName = flnm;
    file = new TFile(fFileName.c_str());
    fileMap = new std::map<std::string , TObject *>();
    TList* list = file->GetListOfKeys();
    TObject* tmp = NULL;

    for (TIter i = list->begin(); i != list->end(); ++i) {
        tmp = (*i);

        if (tmp->IsFolder()) {
            TDirectory* dir = file->GetDirectory(tmp->GetName());
            makeMap(dir);
        } else {
         //   std::cout << tmp->GetName() << std::endl;
            (*fileMap)[std::string(tmp->GetName())] = file->Get(tmp->GetName());
        }

    }
    std::cout << std::flush;

}

QROOTFile::~QROOTFile()
{
    delete file;
    delete fileMap;
}

void QROOTFile::makeMap(TDirectory *dir)
{

    TList* list = dir->GetListOfKeys();
    TObject* tmp = NULL;

    for (TIter i = list->begin(); i != list->end(); ++i) {
        tmp = (*i);

        if (tmp->IsFolder()) {
            TDirectory* dir2 = dir->GetDirectory(tmp->GetName());
            makeMap(dir2);
        } else {
            (*fileMap)[std::string(tmp->GetName())] = dir->Get(tmp->GetName());
        }

    }

}

std::map<std::string , TObject *>* QROOTFile::getMap()
{
    return fileMap;
}

TObject* QROOTFile::GetObject(std::string str)
{
    return (*fileMap)[str];
}
