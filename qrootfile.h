#ifndef QROOTFILE_H
#define QROOTFILE_H


#include "TObject.h"
#include "TFile.h"

#include "map"
#include "cstring"

class QROOTFile
{
private:
  std::map<std::string , TObject *> *fileMap;
  TFile* file;
  std::string fFileName;
  void makeMap(TDirectory*);
public:
  QROOTFile(std::string flnm);
  QROOTFile();
  ~QROOTFile();
  TObject *GetObject(std::string);
  std::map<std::string , TObject *>* getMap ();
};



#endif // QROOTFILE_H
