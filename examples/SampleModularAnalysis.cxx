#include <iostream>
#include <vector>
using namespace std;

// My Includes 
#include "DCut.h"
#include "DSelection.h"
#include "h22Reader.h"
#include "h22Event.h"


class SampleSelection : public DSelection 
{
public:
  SampleSelection();
  ~SampleSelection();
};

SampleSelection::SampleSelection()
{
  set_name(" Sample Selection ");

  ChargeCut negative;
  negative.set_max(0);
  negative.set_min(-2);
  add_cut( negative );
  
}

SampleSelection::~SampleSelection()
{

}


// This Analysis 
class SampleAnalysis : public h22Reader
{
public:
  SampleAnalysis();
  ~SampleAnalysis();

public:
  void loop();
    
};

SampleAnalysis::SampleAnalysis() : h22Reader(0)
{
  // Nothing to do.
  Init();
}

SampleAnalysis::~SampleAnalysis()
{
  // Nothing to do. 
}

void SampleAnalysis::loop()
{

  SampleSelection selection; 
  
  // Loop over events. 
  for (int ievent=0; ievent< fchain->GetEntries(); ievent++)
    {
      GetEntry(ievent);
      h22Event event = GetEvent();
      if (selection.passes(event, 0)) cout << " - " << endl;
    }
  
}



int main(int argc, char * argv[])
{
  
  SampleAnalysis analysis;
  
  for (int iarg=1; iarg<argc; iarg++) { analysis.AddFile(argv[iarg]); } 

  analysis.loop();
  
  return 0;
}