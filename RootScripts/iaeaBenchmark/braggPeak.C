#include "Riostream.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "THStack.h"
#include "TCut.h"
#include "TString.h"
#include "TMath.h"

/***************************
 * Root script that produces a graph of the angular distribution of
 * a certain type of charged fragment (default Z=1).
 * 
 * Results are not stored in a histogram.
 * 
 * This can be compared to measurements made with a square 
 * detector that is being moved around. Such as that of E.Haettner[1].
 * 
 * Results are normalized to the 0-angle because documentation on E.Haettner's 
 * normalization is not found.
 * 
 * @author Gillis Danielsen
 * **************************/


void braggPeak() {

	//TCanvas *c1 = new TCanvas("BraggPeaks", "Energy depositions along x-axis in phantom");
	
//   gROOT->SetStyle("clearRetro");
 //this will be used as base for pulling the experimental data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("experimentalData/iaeaBenchmark/400tdk.dat",dir.Data())); //also set Znum!
   TString Znum = "2"; //set here what will be put in the selection for z, does not automatically change imoprted data.
   Float_t f1,f2,f3,f4;
   Int_t nlines = 0;
   TFile *f = new TFile("fragmentAngularDistribution.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","Data from ascii file","d:i:err1:err2");
	  
   Char_t DATAFLAG[4];
   Int_t NDATA;
   Char_t n1[15], n2[15], n3[15], n4[15];
   in >> DATAFLAG >> NDATA ; // Read EXFOR line: 'DATA 4'
   in >> n1 >> n2 >> n3 >> n4; // Read  column titles: 'Energy He B [...]'

   cout <<n1<<"   "<<n2<<"   "<<n3<<"   "<<n4<<"\n";
   while (1) {
      in >> f1 >> f2 >> f3 >> f4;
      if (!in.good()){ 
		  break;
	  }
      if (nlines < 500 ) printf("%f %f %f %f\n",f1,f2,f3,f4);
      ntuple->Fill(f1,f2,f3,f4);
      nlines++;
   }   
   
   //Let's pull in the simulation data
   TFile* simulation = TFile::Open("IAEA.root");
   TH1F* simBragg = (TH1F*) simulation->Get("braggPeak");

   //Block bellow pulls out the simulation's metadata from the metadata ntuple.
   TNtuple *metadata = (TNtuple*) simulation->Get("metaData");
   Float_t events, detectorDistance,waterThickness,beamEnergy,energyError,phantomCenterDistance;
   metadata->SetBranchAddress("events",&events);
   metadata->SetBranchAddress("waterThickness",&waterThickness);
   metadata->SetBranchAddress("detectorDistance",&detectorDistance);
   metadata->SetBranchAddress("beamEnergy",&beamEnergy);
   metadata->SetBranchAddress("energyError",&energyError);
   metadata->SetBranchAddress("phantomCenterDistance",&phantomCenterDistance);
   metadata->GetEntry(0); //there is just one row to consider.
   
	//good to keep for ref. G4 might give weird units due to change.
	metadata->Scan();
	//let's project the experimental data.
   //TH1F* expBragg = new TH1F("ExperimentalBragg", 400, 0, waterThickness);

	simBragg->SetLineColor(kBlue);
	//simBragg->GetXaxis()->SetName("test");
	simBragg->SetXTitle("Depth (cm)");
	simBragg->SetYTitle("Ionization (MeV/m)");
	//simBragg->GetXaxis()->SetTitleOffset(1);
	simBragg->GetYaxis()->SetTitleOffset(1.5);
	std::cout << "Maximum (Bragg peak) for simulation data is at: " << simBragg->GetBinCenter(simBragg->GetMaximumBin()) << endl;
	std::cout << "Bin width is " << simBragg->GetBinWidth(simBragg->GetMaximumBin()) << endl;
	simBragg->Scale(1.0/(100*events*simBragg->GetBinWidth(0)));
	simBragg->Draw();
	ntuple->SetMarkerColor(kRed);
	ntuple->SetMarkerStyle(22);
	std::cout << ntuple->GetEntries() << endl;
	ntuple->Draw("i:d-(0.478/2)","","p,same"); // .478/2 comes from half plexi glas water equivalent.
	/*
	TH1F combinedBragg("Bragg peaks","slice, energy", 400, 0., 400);
	
	for(int bin = 0; bin <= hist1->GetNbinsX(); bin++){
		value = hist1->GetBinContent(bin); //the incident-particle normalized amount of hits
		width = hist1->GetBinWidth(bin); //so this is degrees/radians
		degrees = hist1->GetBinCenter(bin);
		deltaPhi = width/2;
		binNormalization = 2*TMath::Pi()*(TMath::Cos(TMath::DegToRad()*(degrees-deltaPhi)) - TMath::Cos(TMath::DegToRad()*(degrees+deltaPhi))); //Gunzer-marx uses this , which is a tad of an approximation
		std::cout << bin << "\t(" << hist1->GetNbinsX()-bin << ")" << value << "\t" << binNormalization << endl;
		symmetricHist->SetBinContent(bin+hist1->GetNbinsX(), value/(binNormalization*events)); //Solid angle and amount of events
		symmetricHist->SetBinContent(hist1->GetNbinsX()-bin+1, value/(binNormalization*events)); //Solid angle and amount of events
	  }
	  */
}
