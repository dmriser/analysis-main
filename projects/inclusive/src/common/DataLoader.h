#ifndef data_loader_h
#define data_loader_h

// c++ includes 
#include <iostream>
#include <vector>
using namespace std;

// my includes 
#include "BaseDISHistograms.h"
#include "CommonTools.h"
#include "h22Reader.h"
#include "HistogramLoader.h"
#include "NathanArchive.h"
#include "MomCorr.h"
#include "Parameters.h"
#include "ParticleFilter.h"
#include "PhysicsEvent.h"
#include "PhysicsEventBuilder.h"
#include "PhysicsEventSelector.h"

// root 
#include "TLorentzVector.h"

class DataLoader : public HistogramLoader{
 public:
  DataLoader(PhysicsEventSelector *eventCriteria, MomCorr_e1f *momCorr, Parameters *pars, std::string outputFile, std::string saveOpts);
  ~DataLoader();

 protected:
  BaseDISHistograms dataEvents;
  NathanEIDWrapper  eID; 
  MomCorr_e1f       *momCorrector; 
  ParticleFilter    *filter; 

 protected:
  long int eventsProcessed; 

  void Initialize();
  void ProcessEvent();
  void Save();

};

DataLoader::DataLoader(PhysicsEventSelector *eventCriteria, MomCorr_e1f * momCorr, Parameters *pars, std::string outputFile, std::string saveOpts) : HistogramLoader(eventCriteria, outputFile, saveOpts){
  momCorrector = momCorr; 
  filter       = new ParticleFilter(pars);
}

DataLoader::~DataLoader(){
  cout << "[DataLoader::~DataLoader] Destroying data loader with events processed: " << eventsProcessed << endl; 
}

void DataLoader::Initialize(){
  dataEvents.Init("dataEvents","Data Hits");
  eventsProcessed = 0;

  /*
  filter->getSelector(11)->disable_by_name("DC Region 1 Fid Cut");
  filter->getSelector(11)->disable_by_name("DC Region 3 Fid Cut");
  filter->getSelector(11)->disable_by_name("EC-U Cut");
  filter->getSelector(11)->disable_by_name("EC-V Cut");
  filter->getSelector(11)->disable_by_name("EC-W Cut");
  */

}

void DataLoader::ProcessEvent(){
  eventsProcessed++;
  //  eID.set_info(runno(),GSIM);
  //  int e_index = eID.get_electron(event);

  filter->set_info(GetRunNumber(), GSIM);
  int e_index = filter->getByPID(event, 11);
  if (e_index > -123){
    TLorentzVector electron(event.cx[e_index]*event.p[e_index],
			    event.cy[e_index]*event.p[e_index],
			    event.cz[e_index]*event.p[e_index],
			    event.p[e_index]);

    electron                  = momCorrector->PcorN(electron, -1, 11); 
    int sector                = event.dc_sect[e_index]; 
    PhysicsEvent physicsEvent = builder.getPhysicsEvent(electron);

    // -----------------------------------------------------------------
    // Adding this test code to try and identify Bethe-Heitler events and 
    // throw them out of the sample. 
    // -----------------------------------------------------------------

    /*
    bool isBetheHeitler = false; 
    vector<TLorentzVector> protons = filter->getVectorOfTLorentzVectors(event, 2212);
    if ( !protons.empty() ){
      for (int iprot=0; iprot<protons.size(); iprot++){
	PhysicsEvent betheHeitlerCandidate = builder.getPhysicsEvent(electron, protons[iprot]);
	if (betheHeitlerCandidate.finalState.Theta()*to_degrees < 3.5 && betheHeitlerCandidate.mm2 < 0.07){
	  isBetheHeitler = true; 
	} 
      }
    }
    */

    if (eventSelector->passes(physicsEvent) && sector > 0) {
      dataEvents.Fill(physicsEvent, sector); 
    }
  } 
}

void DataLoader::Save(){
  dataEvents.Save(outputFilenameWithExtension, saveOption);
}

#endif