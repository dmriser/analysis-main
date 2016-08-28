#include <iostream>
using namespace std;

#include "DBins.h"

int main()
{

  DBinsAsymmetric b;
  b.add_bin_edge(0.00);
  b.add_bin_edge(1.00);
  b.add_bin_edge(2.05);
  b.add_bin_edge(123.2340);

  cout << " Found " << b.number() << " bins. " << endl;
  cout.width(12); cout << " Min ";
  cout.width(12); cout << " Max ";
  cout.width(12); cout << " Center ";
  cout.width(12); cout << " Width " << endl;
  

  for (int ibin=0; ibin<b.number(); ibin++) 
    {
      cout.width(12); cout << b.min(ibin); 
      cout.width(12); cout << b.max(ibin);
      cout.width(12); cout << b.center(ibin);
      cout.width(12); cout << b.width(ibin) << endl;
    }


  return 0;
}