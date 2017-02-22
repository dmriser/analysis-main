#ifndef status_bar_cxx
#define status_bar_cxx

#include <iostream>
using std::cout; 
using std::endl; 

#include "StatusBar.h"
#include "TString.h"
#include "TStopwatch.h"
#include "CommonTools.h"

StatusBar::StatusBar(){
  stopwatch.Start(); 
}

StatusBar::~StatusBar(){
  cout << "\033[49m" << endl; 
}

double StatusBar::GetTime(){
  double time = stopwatch.RealTime(); 
  stopwatch.Continue(); 
  return time; 
}

void StatusBar::PrintStatus(int done, int total){
  PrintStatus((double)done/total); 
}

void StatusBar::PrintStatus(double doneFraction){
  cout << "\033[31m" << "[StatusBar::PrintStatus] Finished "; 
  cout.width(16); cout << doneFraction*100 << " %, Time Elapsed = "; 
  cout.width(16); cout << GetTime() << " Time left = "; 
  cout.width(16); cout << (1-doneFraction)/doneFraction *GetTime() << "\033[49m" << endl; 
}


#endif
