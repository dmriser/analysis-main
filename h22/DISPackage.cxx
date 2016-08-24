////////////////////////////////////////////////////////////////////
/*

  David Riser, University of Connecticut 
  August 24, 2016 

  DISPackage.cxx 

*/
////////////////////////////////////////////////////////////////////

#ifndef dis_cxx
#define dis_cxx

// c++ includes 
#include <iostream>
#include <vector>
using namespace std; 

// my includes
#include "DBins.h"
#include "DCut.h"
#include "DEvent.h"
#include "DISPackage.h"
#include "DSelection.h"
#include "ElectronIDPackage.h"
#include "NathanArchive.h"

//  root includes
#include "TFile.h"
#include "TH1.h"

////////////////////////////////////////////////////////////////////////
/*

  DISHistograms 

*/
////////////////////////////////////////////////////////////////////////

DISHistograms::DISHistograms()
{
  sect[0] = "all";
  sect[1] = "s1";
  sect[2] = "s2";
  sect[3] = "s3";
  sect[4] = "s4";
  sect[5] = "s5";
  sect[6] = "s6";
  output_name = "unset";
}


DISHistograms::~DISHistograms()
{
  // Destroy things. 
}

void DISHistograms::init()
{
  // Initialize Histograms

  // Generated Events for x-by-qq
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(xBins.number()+1); b++)
      {
	string name  = Form("h1_gen_x_by_qq_%d_%s",b,sect[s].c_str());
	string title = Form("gen x-by-qq for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), xBins.number(), xBins.min(), xBins.max()) );
      }
    h1_gen_x_by_qq.push_back(v);
  }

  // Reconstructed Events for x-by-qq
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(xBins.number()+1); b++)
      {
	string name  = Form("h1_rec_x_by_qq_%d_%s",b,sect[s].c_str());
	string title = Form("rec x-by-qq for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), xBins.number(), xBins.min(), xBins.max()) );
      }
    h1_rec_x_by_qq.push_back(v);
  }

  // Data Events for x-by-qq
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(xBins.number()+1); b++)
      {
	string name  = Form("h1_hits_x_by_qq_%d_%s",b,sect[s].c_str());
	string title = Form("hits x-by-qq for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), xBins.number(), xBins.min(), xBins.max()) );
      }
    h1_hits_x_by_qq.push_back(v);
  }

  // Generated Events for x-by-w
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(xBins.number()+1); b++)
      {
	string name  = Form("h1_gen_x_by_w_%d_%s",b,sect[s].c_str());
	string title = Form("gen x-by-w for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), xBins.number(), xBins.min(), xBins.max()) );
      }
    h1_gen_x_by_w.push_back(v);
  }

  // Reconstructed Events for x-by-w
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(xBins.number()+1); b++)
      {
	string name  = Form("h1_rec_x_by_w_%d_%s",b,sect[s].c_str());
	string title = Form("rec x-by-w for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), xBins.number(), xBins.min(), xBins.max()) );
      }
    h1_rec_x_by_w.push_back(v);
  }

  // Data Events for x-by-w
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(xBins.number()+1); b++)
      {
	string name  = Form("h1_hits_x_by_w_%d_%s",b,sect[s].c_str());
	string title = Form("hits x-by-w for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), xBins.number(), xBins.min(), xBins.max()) );
      }
    h1_hits_x_by_w.push_back(v);
  }

  
  // Generated Events for qq-by-x
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(qqBins.number()+1); b++)
      {
	string name  = Form("h1_gen_qq_by_x_%d_%s",b,sect[s].c_str());
	string title = Form("gen qq-by-x for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), qqBins.number(), qqBins.min(), qqBins.max()) );
      }
    h1_gen_qq_by_x.push_back(v);
  }

  // Reconstructed Events for x-by-w
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(qqBins.number()+1); b++)
      {
	string name  = Form("h1_rec_qq_by_x_%d_%s",b,sect[s].c_str());
	string title = Form("rec qq-by-x for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), qqBins.number(), qqBins.min(), qqBins.max()) );
      }
    h1_rec_qq_by_x.push_back(v);
  }

  // Data Events for qq-by-x
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(qqBins.number()+1); b++)
      {
	string name  = Form("h1_hits_qq_by_x_%d_%s",b,sect[s].c_str());
	string title = Form("hits qq-by-x for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), qqBins.number(), qqBins.min(), qqBins.max()) );
      }
    h1_hits_qq_by_x.push_back(v);
  }

  // Generated Events for qq-by-w
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(qqBins.number()+1); b++)
      {
	string name  = Form("h1_gen_qq_by_w_%d_%s",b,sect[s].c_str());
	string title = Form("gen qq-by-w for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), qqBins.number(), qqBins.min(), qqBins.max()) );
      }
    h1_gen_qq_by_w.push_back(v);
  }

  // Reconstructed Events for qq-by-w
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(qqBins.number()+1); b++)
      {
	string name  = Form("h1_rec_qq_by_w_%d_%s",b,sect[s].c_str());
	string title = Form("rec qq-by-w for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), qqBins.number(), qqBins.min(), qqBins.max()) );
      }
    h1_rec_qq_by_w.push_back(v);
  }

  // Data Events for qq-by-w
  for (int s=0; s<7; s++) {
    vector<TH1F*> v;
    for (int b=0; b<(qqBins.number()+1); b++)
      {
	string name  = Form("h1_hits_qq_by_w_%d_%s",b,sect[s].c_str());
	string title = Form("hits qq-by-w for bin %d of %s",b,sect[s].c_str());
	v.push_back( new TH1F(name.c_str(), title.c_str(), qqBins.number(), qqBins.min(), qqBins.max()) );
      }
    h1_hits_qq_by_w.push_back(v);
  }

 
}

void DISHistograms::fill(DEvent event, int index)
{
  if (event.e_index == -123){ cout << " You must set DEvent::e_index before filling histograms! " << endl; return; }
  
  int s = event.tracks.dc_sect[event.e_index];
  int xbin  = 1+xBins .find_bin( event.x );
  int qqbin = 1+qqBins.find_bin( event.qq);
  int wbin  = 1+wBins .find_bin( event.w );

  // Protect agaisnt Seg fault 
  if (xbin < 0 || qqbin < 0 || wbin < 0) return;
  if (xbin >= xBins.number() || qqbin >= qqBins.number() || wbin >= wBins.number()) return; 

  // Monte Carlo 
  if (index == 1) {
    h1_rec_x_by_qq[0][0]     ->Fill(event.x);
    h1_rec_x_by_qq[0][qqbin] ->Fill(event.x);
    h1_rec_x_by_qq[s][0]     ->Fill(event.x);
    h1_rec_x_by_qq[s][qqbin] ->Fill(event.x);


    h1_rec_x_by_w[0][0]    ->Fill(event.x);
    h1_rec_x_by_w[0][wbin]    ->Fill(event.x);
    h1_rec_x_by_w[s][0]    ->Fill(event.x);
    h1_rec_x_by_w[s][wbin] ->Fill(event.x);

    h1_rec_qq_by_x[0][0]    ->Fill(event.qq);
    h1_rec_qq_by_x[0][xbin]    ->Fill(event.qq);
    h1_rec_qq_by_x[s][0]    ->Fill(event.qq);
    h1_rec_qq_by_x[s][xbin] ->Fill(event.qq);
    
    h1_rec_qq_by_w[0][0]    ->Fill(event.qq);
    h1_rec_qq_by_w[0][wbin]    ->Fill(event.qq);
    h1_rec_qq_by_w[s][0]    ->Fill(event.qq);
    h1_rec_qq_by_w[s][wbin] ->Fill(event.qq);

  }

  // Data Events
  else if (index == 0) {
    h1_hits_x_by_qq[0][0]     ->Fill(event.x);
    h1_hits_x_by_qq[0][qqbin]     ->Fill(event.x);
    h1_hits_x_by_qq[s][0]     ->Fill(event.x);
    h1_hits_x_by_qq[s][qqbin] ->Fill(event.x);

    h1_hits_x_by_w[0][0]    ->Fill(event.x);
    h1_hits_x_by_w[0][wbin]    ->Fill(event.x);
    h1_hits_x_by_w[s][0]    ->Fill(event.x);
    h1_hits_x_by_w[s][wbin] ->Fill(event.x);

    h1_hits_qq_by_x[0][0]    ->Fill(event.qq);
    h1_hits_qq_by_x[0][xbin]    ->Fill(event.qq);
    h1_hits_qq_by_x[s][0]    ->Fill(event.qq);
    h1_hits_qq_by_x[s][xbin] ->Fill(event.qq);

    h1_hits_qq_by_w[0][0]    ->Fill(event.qq);
    h1_hits_qq_by_w[0][wbin]    ->Fill(event.qq);
    h1_hits_qq_by_w[s][0]    ->Fill(event.qq);
    h1_hits_qq_by_w[s][wbin] ->Fill(event.qq);
  }

}

void DISHistograms::save()
{
  TFile out(output_name.c_str(),"recreate");

  for (int s=0; s<7; s++)
    {
      for (int b=0; b<=xBins.number(); b++)
	{
	  h1_hits_qq_by_x[s][b] ->Write();
	  h1_rec_qq_by_x[s][b]  ->Write();
	  h1_gen_qq_by_x[s][b]  ->Write();
	}
      
      for (int b=0; b<=qqBins.number(); b++)
	{
	  h1_hits_x_by_qq[s][b] ->Write();
	  h1_rec_x_by_qq[s][b]  ->Write();
	  h1_gen_x_by_qq[s][b]  ->Write();
	}

      for (int b=0; b<=wBins.number(); b++)
	{
	  h1_hits_x_by_w[s][b]  ->Write();
	  h1_rec_x_by_w[s][b]   ->Write();
	  h1_gen_x_by_w[s][b]   ->Write();
	  h1_hits_qq_by_w[s][b] ->Write();
	  h1_rec_qq_by_w[s][b]  ->Write();
	  h1_gen_qq_by_w[s][b]  ->Write();
	}
    }

  out.Write();
  out.Close();
}


////////////////////////////////////////////////////////////////////////
/*

  DISManager

*/
////////////////////////////////////////////////////////////////////////

DISManager::DISManager()
{
  outfile     = "unset";
  parfile[0]  = "unset";
  parfile[1]  = "unset";

  eid_version = 0; 
}

DISManager::~DISManager()
{
  // Destruir todo. 
}

void DISManager::init()
{
  // Warning for not setting parameters.  
  if (parfile[0] == "unset" || parfile[1] == "unset" || outfile == "unset")
    {
      cout << " Warning: Not all parameters have been set before initializing! " << endl;
      cout << " parfile[0] = " << parfile[0] << " parfile[1] = " << parfile[1] << " outfile = " << outfile << endl;  
    }

  reader[0].Init();
  reader[1].Init();

  if ( reader[0].GetEntries() == 0 || reader[1].GetEntries() == 0 ) { cout << " Fatal Error: Trying to initialize with no files in one of the readers. " << endl; exit(0); }  
  
  // Setup Histograms
  histos.output_name = outfile; 
  histos.set_bins(xBins, qqBins, wBins);
  histos.init();

  // Setting up ElectronSelector 
  eid[0].set_parfile( parfile[0] );
  eid[1].set_parfile( parfile[1] );
  eid[0].set_info(reader[0].runno(), reader[0].GSIM);
  eid[1].set_info(reader[1].runno(), reader[1].GSIM);
  eid[0].init();
  eid[1].init();

  // Setting up Electron ID from Nathan, needs to be updated while running. 
  nathan.set_info(reader[0].runno(), reader[0].GSIM);
}

void DISManager::add_files(vector<string> files, int index)
{
  for (int ifile=0; ifile<files.size(); ifile++) reader[index].AddFile(ifile);
}

#endif
