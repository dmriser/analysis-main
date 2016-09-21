
// c++ 
#include <iostream>

// me 
#include "DBins.h"
#include "PhysicsEvent.h"

// root 
#include "TH2.h"

#ifndef base_dis_histograms_h
#define base_dis_histograms_h

class BaseDISHistograms{
 public:
  BaseDISHistograms();
  ~BaseDISHistograms();

  int numberOfXBins = 200;
  int numberOfQQBins = 200; 
  int numberOfWBins = 200;

  double xMin  = 0.05;  double xMax  = 0.7; 
  double qqMin = 1.0;   double qqMax = 4.8;
  double wMin  = 2.05;  double wMax  = 3.1; 
  
  TH2D * xByQQ[7]; 
  TH2D * wByQQ[7]; 

  void Init(std::string name, std::string title);
  void Load(std::string filename, std::string name); 
  void Save(std::string filename);
  void Fill(PhysicsEvent event, int sector); 
  
  //ClassDef(BaseDISHistograms, 1); 
};

#endif
