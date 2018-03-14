# ROOT Grapher

This project is a playground for students. It contains a simple *TCanvas* integrated into the Qt GUI. In theory the project should converge into a simple histogram extractor from the *.root files.

## Prerequisites

- One needs ot have Qt installed (together with the QtCreator, better if you have local installation)
- ROOT has to be compiled and installed (also local installation)
- C++ skills

## Building the project

- **Fork the repository to your own page**
- Clone *your own* fork of the repository
- Open the project in QtCreator
- You will be offered to specify the build options
- Edit **root-grapher.pro** file to match the ROOT installation folder
- Run Build

The simple window should appear. If you click the **Change File** button - the ROOT histogram will appear there.

## Task

### Ideological Goals

- Getting used to the Git workflow
- Understanding ROOT
- Understanding Qt
- Practicing object-oriented programming

### Current Structure

The project contains following files:

- **root-grapher.pro** -- project file
- **main.cpp** - main file, in Qt contains only the class instantination
- **mainwindow.h(cpp)** - the MainWindow class describing the GUI
- **mainwindow.ui** - graphical form to build the interface
- **canvas.h(cxx)** - simple implementation of the TCanvas in Qt

### Practical Goals and Hints

The \*.root histogram browser has to be developed, based on the existing code. It should be a super simple analogy of the **TBrowser**. The development has to be done in your own Git fork.

For the moment once you push the button "Change File", the method *on\_change\_file\_clicked()* is called: it creates a simple random-filled histogram and plots it using the *plot\_data(TObject \*pGraph)* method. As one can see, the method accepts generic *TObject* file as the input, so any type of graphical data can be sent there: TH1F, TGraph, whatever. 

The goal, is to replace the existing method, which is executed once the "Change File" button is clicked with the real method, which opens the file system browser and shows only *.root files. The example is described [here](http://doc.qt.io/qt-5/qfiledialog.html), for instance. 

Once the file has been chosen, the object-oriented programming comes. The new class has to be instantiated and called **QROOTFile**. This class should contain the ```std::map<std::string, TObject*>``` private object, which is the map of the histogram (graph) name and its reference. When the **QROOTFile** constructor is called (takes a file name as the argument), it should open the *.root file (TFile), and load the histograms into the map. As the map is private, there should be a dedicated class method to get a histogram by its name, to get a list of histogram names, etc. 

Once this is done, the **hist_list** object of the MainWindow (just a list widget) has to be filled with the histogram names, so that user can select the histogram and it will be immidiately displayed in the canvas. Once the file is changed, the list has to be updated.

During the development, the code should be periodically commited in order to make version control possible. Once the development is done, the pull (merge) request has to b submitted to the initial (upstream) repository.

