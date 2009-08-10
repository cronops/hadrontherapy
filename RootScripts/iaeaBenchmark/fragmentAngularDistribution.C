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
   in.open(Form("experimentalData/iaeaBenchmark/B27.9.dat",dir.Data()));
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
   TFile *MCData = TFile::Open("IAEA_qmd.root");
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
	Double_t detectorSideLength = 4; //40mm, as e.haettner H1 detector
	Double_t scatteringDistance = detectorDistance - phantomCenterDistance; //temporarily hard-coded, should be distance from target-center to detector

	Double_t r;
	Double_t degrees;
	TString rMinString;
	TString rMaxString;
	Double_t maxValue = 0.0;
	
	//TCanvas *c3 = new TCanvas("histograms", "Distribution (at different angles)");
	int i = 0; //so that the degree steps can be varied to unevenly spaced values separate counter is used
	TString Znum = "5"; //set here what will be put in the selection for z, does not automatically change imoprted data!!!
	TNtuple* distrib = new TNtuple("angularDistrib","FragmentAngularDistrib","angle:particleAmount:normalized");

	std::cout << "The following numbers also make it possible to make number of fragments comparison to the graph in A1 of E.Haettner\n";

	//This will norm it to the zero degree entry to get rid of Emma's weird normalization
	//fixme detectorsidelengthstring
	rMinString = "0.00";
	rMaxString = "2.00";
	Double_t normEntries = fragments->GetEntries("(Z == " + Znum + " && energy > 0 && sqrt(posY^2 + posZ^2) < " + rMaxString + "&& sqrt(posY*posY + posZ*posZ) > " + rMinString + ")");
	//fixme, this is not very good.
	Double_t zeroSAsquare = 4 * TMath::ASin(pow(detectorSideLength,2.0) / (4*pow(scatteringDistance,2) + pow(detectorSideLength,2)) );
	Double_t deltaPhi = TMath::ATan((detectorSideLength/2)/scatteringDistance);
	Double_t zeroSA = 2*TMath::Pi()*(TMath::Cos(0) - TMath::Cos(deltaPhi));
	squareApprox = (4*4) / (4*3.14*scatteringDistance*scatteringDistance);
	std::cout << "square approx" << squareApprox << endl << "square exact" << zeroSAsquare << endl << "circle exact" << zeroSA << endl;
	std::cout << "for zero there is " << normEntries << endl;
	Double_t zeroNorm = normEntries / (events * zeroSA);
	distrib->Fill(0,normEntries,zeroNorm/zeroNorm); //< degrees, entyamount, normalized result for graph

	std::cout << endl << "zeronorm: " << zeroNorm << "\n";

	//has to start from .5 to avoid error when annulus space angle becomes large due to the usage of max
	for(Double_t j = 0.1; j <= 20.0; j=j+.2){
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
		//Double_t deltaPhi = degrees - TMath::ATan(TMath::Tan(degrees) - detectorSideLength/scatteringDistance); // this should be around arctan(detectorsidelength/sd)
		Double_t deltaPhi = degrees - TMath::ATan(TMath::Tan(degrees) - (detectorSideLength/(2*scatteringDistance))); // this should be around arctan(detectorsidelength/sd)
		/*
		* From Gunzert-marx. Solid angle of annulus with rmin trmax, 
		* a bit of an aproximation especially at small phi.
		* However, one should notice this will go to zero and
		* crash the simulation at 0. Also at distances smaller than
		* arctan(detectorSidelength/(scatteringDistance/2)) this will not be trustworthy
		* because the solid angle will be very small as long as rMin is zero which gives big values
		* in the normalization.
		*/
		Double_t deltaOmega = 2*TMath::Pi()*(TMath::Cos(TMath::Max(0.0,degrees-deltaPhi)) - TMath::Cos(degrees+deltaPhi));
		int numEntries = fragments->GetEntries("(Z == " + Znum + " && energy > 0 && sqrt(posY^2 + posZ^2) < " + rMaxString + "&& sqrt(posY*posY + posZ*posZ) > " + rMinString + ")");
		if(j == .5){
			//zeroNorm = numEntries/(deltaOmega * events);
			}
		//std::cout << "detector shidelength should be 4: " << rMax - rMin << endl;
		distrib->Fill(j,numEntries,numEntries/(deltaOmega * events * zeroNorm)); //< degrees, entyamount, normalized result for graph
		distrib->Fill(-j,numEntries,numEntries/(deltaOmega * events * zeroNorm)); //< To get gaussian shape better visible
		maxValue = TMath::Max(maxValue, numEntries/(deltaOmega * events * zeroNorm));
		}
	distrib->SetMarkerStyle(20);
	distrib->SetMarkerColor(kBlue);
	distrib->Draw("normalized:angle","angle > -3 && angle < 14","p"); //similar axises to e.haettner
	ntuple->SetMarkerStyle(22);
    ntuple->SetMarkerColor(kRed);
	Float_t zeroPosData; //This is where we store what we norm the experimental data with
	Float_t zeroPosAngle; //okay, so this should be zero, but regrettably is not allways that
	ntuple->SetBranchAddress("y",&zeroPosData);
	ntuple->SetBranchAddress("x",&zeroPosAngle);
	int row = 0;	
	ntuple->GetEntry(row); //Pull the first row, usually is the right one
	while(zeroPosAngle*zeroPosAngle > .01){
		row++;
		ntuple->GetEntry(row);
		if(row == ntuple->GetEntries()){
			std::cerr << "Could not find zero angle data in imported experimental data. Change normalization or relax exactness of this check." << endl;
			exit();
			}
		}
	std::cout << "For zero-position of experimental data using angle " << zeroPosAngle << " with amount " << zeroPosData << " on row " << row << endl;
	std::cout << "zeroposdata: " << zeroPosData << endl;
	TString experimentalNorm = Form("(1/%f)*", zeroPosData);
	std::cout << "zeroposnorm: " << experimentalNorm << endl;
	
	ntuple->Draw(experimentalNorm + "y:x","","p,same");
	
	//Calculate FWHM
	//todo, find what the fw is at maxValue/2
	
	
	/*
	 * This code is left here because it allows to calcualte the values without using annuluses
	 * this of course is a bit more like the experimental data but statistically less precise.
	for(Double_t p = 0.0;p < 14.0; p = p + 1.0){
	rMinString = "0.00";
	rMaxString = "2.00";
	TString plusY = Form("(posY - %f)", p);
	TString plusZ = Form("(posZ - %f)", p);
		Double_t deltaPhi = TMath::ATan((detectorSideLength/2)/scatteringDistance);
	Double_t normEntries = fragments->GetEntries("(Z == " + Znum + " && energy > 0 && sqrt(" + plusY + "^2 + " + plusZ + "^2) < " + rMaxString + "&& sqrt("+plusY + "^2 + " + plusZ + "^2) > " + rMinString + ")");
	//std::cout << "(Z == " + Znum + " && energy > 0 && sqrt(" + plusY + "^2 + " + plusZ + "^2) < " + rMaxString + "&& sqrt("+plusY + "^2 + " + plusZ + "^2) > " + rMinString + ")";
	Double_t zeroSA = 2*TMath::Pi()*(TMath::Cos(0) - TMath::Cos(deltaPhi));
	std::cout << "with " << p << "cm the amount is " << normEntries << " / " << normEntries /(events*zeroSA) << endl;
		}
		*/
	
	
	c1->SaveAs("angularDistribComparedToEHaettner.png");
	in.close();
	f->Write();
}
