////////////////////////////////////////
/*
 David Riser, University of Connecticut
 
 July 17, 2016
 
 template.cxx -> Your info here.
 
 */
////////////////////////////////////////

// c++ includes
#include <iostream>
using namespace std;

// my includes from h22 library
#include "CommonTools.h"
#include "Corrections.h"
#include "h22Event.h"
#include "h22Option.h"
#include "h22Reader.h"
#include "pars.h"
#include "ParticleFilter.h"

// root includes
#include "TStopwatch.h"

int main(int argc, char * argv[])
{
    
    // Setup Options
    h22Options opts;
    opts.set(argc,argv);
    int GSIM     = opts.args["MC"].arg;
    long int nev = opts.args["N"].arg;
    string eparfile = opts.args["EPARS"].args;
    string hparfile = opts.args["HPARS"].args;
    
    hpars hpars; epars epars;
    epars.load(eparfile);
    hpars.load(hparfile);
    
    
    // Setup Reader
    h22Reader fReader(GSIM);
    for (auto it=opts.ifiles.begin(); it<opts.ifiles.end(); it++) { fReader.AddFile(*it); }
    fReader.Init();
    
    // If you ask for more the loop will analyze garbage
    nev = smallest(nev, fReader.GetEntries());
    
    // Setting important constants
    int runno = fReader.runno();
    
    // Setting up PID and Corrections
    ParticleFilter filter(eparfile);
    filter.set_info(GSIM, runno);
    Corrections corr;
    
    // Example of physics
    int elastic_candidates = 0;
    int sidis_candidates   = 0;
    
    // Keep track of time.
    TStopwatch timer;
    timer.Reset();
    timer.Start();
    
    for (int iev=0; iev<nev; iev++)
    {
        fReader.GetEntry(iev);
        h22Event event = fReader.GetEvent();
        
        // keeping track of run number and making sure particle filter knows about it as well.
        if ( runno != fReader.runno() ){ runno = fReader.runno(); filter.set_info(GSIM, runno); }
        
        // Load up hadrons if we've electron.
        if (filter.has_electron(event))
        {
            // Example Elastic Event Candidate
            int prot_index = filter.getByPID(event,2212);
            int pip_index  = filter.getByPID(event,211);
            int pim_index  = filter.getByPID(event,-211);
            
            if (prot_index > -123)                    elastic_candidates++;
            if (pim_index > -123 || pip_index > -123) sidis_candidates++;
            
        }
        
        // Tell the user
        if ( (int)iev%(int)opts.args["PRINT"].arg == 0) cout << "\r done " << iev << " of " << nev << flush;
    }
    
    // If you changed anything in the parfiles
    epars.save(eparfile);
    hpars.save(hparfile);

    cout << "\n Found " << elastic_candidates << " candidate elastic events " << endl;
    cout << " Found " << sidis_candidates << " candidate sidis events " << endl;

    double loop_time  = timer.RealTime();
    double event_rate = (double)nev/loop_time;
    
    cout << " Event loop finished in " << loop_time << " seconds w/ rate " << event_rate << " events/sec " << endl;
    
}