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
 * @author Gillis Danielsen
 * **************************/


void fragmentAngularDistribution() {

	TCanvas *c1 = new TCanvas("AngularDistribution", "Angular distribution with discrete measurement annuluses");
	
//   gROOT->SetStyle("clearRetro");
 //this will be used as base for pulling the experimental data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("experimentalData/iaeaBenchmark/H27.9.dat",dir.Data()));
   Float_t f1,f2;
   Int_t nlines = 0;
   TFile *f = new TFile("fragmentAngularDistribution.root","RECREATE");
   TNtuple *ntuple = new TNtuple("ntuple","Data from ascii file","x:y");
	  
   Char_t DATAFLAG[4];
   Int_t NDATA;
   Char_t n1[15], n2[15];
   in >> DATAFLAG >> NDATA ; // Read EXFOR line: 'DATA 6'
   in >> n1 >> n2; // Read  column titles: 'Energy He B [...]'

   cout <<n1<<"   "<<n2<<"\n";
   while (1) {
      in >> f1 >> f2;
      if (!in.good()) break;
      if (nlines < 500 ) printf("%f %f\n",f1,f2);
      ntuple->Fill(f1,f2);
      nlines++;
   }
   

   //Let's pull in the simulation-data
   TFile *MCData = TFile::Open("IAEA.root");
   TNtuple *fragments = (TNtuple*) MCData->Get("fragmentNtuple");

   //Block bellow pulls out the simulation's metadata from the metadata ntuple.
   TNtuple *metadata = (TNtuple*) MCData->Get("metaData");
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
	
	//ALL UNITS ARE cm!
	Double_t detectorSideLength = 1.6; //40mm, as e.haettner H1 detector
	Double_t scatteringDistance = detectorDistance - phantomCenterDistance; //temporarily hard-coded, should be distance from target-center to detector

	Double_t r;
	Double_t degrees;
	TString rMinString;
	TString rMaxString;
	
	//TCanvas *c3 = new TCanvas("histograms", "Distribution (at different angles)");
	int i = 0; //so that the degree steps can be varied to unevenly spaced values separate counter is used
	TString Znum = "1"; //set here what will be put in the selection for z
	TNtuple* distrib = new TNtuple("angularDistrib","FragmentAngularDistrib","angle:particleAmount:normalized");

	std::cout << "The following numbers also make it possible to make number of fragments comparison to the graph in A1 of E.Haettner\n";
	//has to start from .5 to avoid error when annulus space angle becomes large due to the usage of max
	for(Double_t j = 0.5; j <= 20.0; j=j+.2){
		i++;
		degrees = j * TMath::DegToRad();
		//std::cout << "plotting for Z = " << Znum << " at " << j << " degrees\n";
		//Distance from straight beam at the requested angle
		r = scatteringDistance * TMath::Tan(degrees);
		//now the "detector is rotated around all possible perpendicularlynangle values to beamline".
		//This forms an annulus with rMin and Rmax as otuer and inner radiuses
		//Notice this will give a bit of approximation at small angles where at 0 degrees this gives a round sensor.
		rMin = TMath::Max(0.0,r - (detectorSideLength/2));
		rMax = r + (detectorSideLength/2);
		rMinString = Form("%f", rMin);
		rMaxString = Form("%f", rMax);
		
		//deltaPhi calculated so that phi+deltaphi points to the sides of the detector and phi-deltaphi the other side
		Double_t deltaPhi = degrees - TMath::ATan(TMath::Tan(degrees) - detectorSideLength/scatteringDistance); // this should be around arctan(detectorsidelength/sd)
		/*
		* From Gunzert-marx. Solid angle of annulus with rmin trmax, 
		* a bit of an aproximation especially at small phi.
		* However, one should notice this will go to zero and
		* crash the simulation at 0. Also at distances smaller than
		* arctan(detectorSidelength/(scatteringDistance/2)) this will not be trustworthy
		* because the solid angle will be very small as long as rMin is zero which gives big values
		* in the normalization.
		*/
		Double_t deltaOmega = 2*TMath::Pi()*(TMath::Cos(degrees-deltaPhi) - TMath::Cos(degrees+deltaPhi));
		int numEntries = fragments->GetEntries("(Z == " + Znum + " && energy > 0 && sqrt(posY^2 + posZ^2) < " + rMaxString + "&& sqrt(posY*posY + posZ*posZ) > " + rMinString + ")");
		distrib->Fill(j,numEntries,numEntries/(deltaOmega * events)); //< degrees, entyamount, normalized result for graph
		distrib->Fill(-j,numEntries,numEntries/(deltaOmega * events)); //< To get gaussian shape better visible
		}
	distrib->SetMarkerStyle(22);
	distrib->SetMarkerColor(kBlue);
	distrib->Draw("normalized:angle","angle > -3 && angle < 14","p"); //similar axises to e.haettner
	ntuple->SetMarkerStyle(22);
    ntuple->SetMarkerColor(kRed);
	ntuple->Draw(".1*y:x","","p,same"); //Why, oh why dear Emma does it match so well with a tenth.
	c1->SaveAs("angularDistribComparedToEHaettner.png");
	in.close();
	f->Write();
}
