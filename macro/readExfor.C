#include "Riostream.h"
void readExfor() {
//   example of macro to read data from an ascii file and
//   create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
//in.open(Form("../data/fragmentEnergySpctra279mmWater0deg.dat",dir.Data()));
in.open(Form("data/fragmentEnergySpctra279mmWater0deg.dat",dir.Data()));
Float_t f1,f2,f3, f4,f5,f6;
   Int_t nlines = 0;
   TFile *f = new TFile("basic.root","RECREATE");
   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z");
	  
   Char_t DATAFLAG[4];
   Int_t NDATA;
   Char_t n1[2], n2[2], n3[2], n4[2], n5[2], n6[2],;
   in >> DATAFLAG >> NDATA ; // Read EXFOR line: 'DATA 6'
   in >> n1 >> n2 >> n3 >> n4 >> n5 >> n6; // Read  column titles: 'Energy He B [...]'

   cout <<n1<<" "<<n2<<" "<<n3<<"    "<<n4<<"    "<<n5<<"   "<<n6<<"\n";
   while (1) {
      in >> f1 >> f2 >> f3 >>f4 >> f5 >> f6;
      if (!in.good()) break;
      if (nlines < 500 ) printf("%i  %0.2f %0.2f %0.2f %0.2f %0.2f \n",f1,f2,f3,f4,f5,f6);
      h1->Fill(f1);
      ntuple->Fill(f1,f2,f3);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}
