#ifndef data_loader_h
#define data_loader_h

// c++ includes 
#include <iostream>
#include <vector>
using namespace std;

// my includes 
//#include "BaseHistograms.h"
#include "CommonTools.h"
#include "h22Reader.h"
#include "HistogramLoader.h"
#include "NathanArchive.h"
#include "MomCorr.h"
#include "PhysicsEvent.h"
#include "PhysicsEventBuilder.h"
#include "PhysicsEventSelector.h"

// root 
#include "TFile.h"
#include "TLorentzVector.h"
#include "THnSparse.h"

class DataLoader : public HistogramLoader{
 public:
  DataLoader(PhysicsEventSelector *eventCriteria, MomCorr_e1f * momCorr, std::string outputFile, std::string saveOpts);
  ~DataLoader();

 protected:
  //  BaseHistograms dataEvents;
  const static int dimension = 4;
  
  THnSparseI *dataEvents; 
  int bins[dimension];
  double min[dimension];
  double max[dimension];

  NathanEIDWrapper eID; 
  MomCorr_e1f * momCorrector; 
  string outputFilename; 

 protected:
  void Initialize();
  void ProcessEvent();
  void Save();

};

DataLoader::DataLoader(PhysicsEventSelector *eventCriteria, MomCorr_e1f *momCorr, std::string outputFile, std::string saveOpts) : HistogramLoader(eventCriteria, outputFile, saveOpts){
  momCorrector = momCorr; 
  outputFilename = outputFile;
  // 4-Dimensional Binning 
  // 0 - Sector 
  // 1 - Momentum 
  // 2 - Theta 
  // 3 - Relative Phi
  bins[0] = 6;
  bins[1] = 100;
  bins[2] = 100;
  bins[3] = 100;

  min[0] = 1.0;      max[0] = 7.0; 
  min[1] = 2.05;     max[1] = 5.0; 
  min[2] = 18.0;     max[2] = 50.0; 
  min[3] = -20.0;    max[3] = 20.0; 

  dataEvents = new THnSparseI("dataEvents","dataEvents",dimension,bins,min,max);
}

DataLoader::~DataLoader(){
  // Anything to do here? 
}

void DataLoader::Initialize(){

}

// This is the core routine which conditionally fills histograms. 
void DataLoader::ProcessEvent(){

  eID.set_info(runno(),GSIM);
  int e_index = eID.get_electron(event);
  if (e_index > -123){
    TLorentzVector electron(event.cx[e_index]*event.p[e_index],
			    event.cy[e_index]*event.p[e_index],
			    event.cz[e_index]*event.p[e_index],
			    event.p[e_index]);

    electron = momCorrector->PcorN(electron, -1, 11); 

    int sector = event.dc_sect[e_index]; 
    PhysicsEvent physicsEvent = builder.getPhysicsEvent(electron);
    
    if (eventSelector->passes(physicsEvent) && sector > 0) {
      double dataPoint[dimension] = {(double)sector,electron.E(),electron.Theta()*to_degrees,electron.Phi()*to_degrees};
      dataEvents->Fill(dataPoint);
    }
  } 
}

void DataLoader::Save(){
  TFile *outputFile = new TFile(outputFilename.c_str(), "RECREATE");
  dataEvents->Write();
  outputFile->Write();
  outputFile->Close();
}

#endif