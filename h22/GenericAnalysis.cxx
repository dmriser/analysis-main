/****************************************************************** 
 *     David Riser, University of Connecticut
 *     Dec 5, 2016 
 *     
 *     Generic analysis code to be extended by specific analysis 
 *     packages.  
 *
 ********************************************************************/

#ifndef generic_analysis_cxx
#define generic_analysis_cxx

#include <iostream>
using std::cout; 
using std::endl; 
using std::flush; 

#include "GenericAnalysis.h"

void GenericAnalysis::AddFiles(std::vector<TString> files){
  for (int ifile=0; ifile<files.size(); ifile++){
    AddFile(files[ifile]);
  }
}

void GenericAnalysis::AddFile(TString file){
  fchain->AddFile(file);
}

void GenericAnalysis::RunAnalysis(int numberOfEvents){

  if (GetEntries() == 0){
    cout << "[GenericAnalysis::RunAnalysis] Abort: No events. " << endl; 
    return;
  }

  else {
    Init();
    Loop(numberOfEvents);
    Save();
  }


}

void GenericAnalysis::Loop(int numberOfEvents){

  if (numberOfEvents > GetEntries()){ numberOfEvents = GetEntries(); }

  for (int ievent=0; ievent<numberOfEvents; ievent++){
    GetEntry(ievent);
    ProcessEvent();

    if (ievent%10000 == 0) { cout << "\r done " << ievent << flush; }
  }

  cout << endl;
}

void GenericAnalysis::ProcessEvent(){
  // Do something with event.vars
  event.printEvent();
}

void GenericAnalysis::Save(){
  
}

#endif
