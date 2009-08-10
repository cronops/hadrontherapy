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


void fragmentAngularDistribution() {

	TCanvas *c1 = new TCanvas("AngularDistribution", "Angular distribution with discrete measurement annuluses");
	
//   gROOT->SetStyle("clearRetro");
 //this will be used as base for pulling the experimental data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("experimentalData/iaeaBenchmark/He27.9.dat",dir.Data())); //also set Znum!
   TString Znum = "2"; //set here what will be put in the selection for z, does not automatically change imoprted data.
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
	Double_t detectorSideLength = 4; //40mm, as e.haettner H1 detector
	Double_t scatteringDistance = detectorDistance - phantomCenterDistance; //temporarily hard-coded, should be distance from target-center to detector

	Double_t r;
	Double_t degrees;
	Double_t rMin;
	Double_t rMax;
	TString rMinString;
	TString rMaxString;
	Double_t maxValue = 0.0; //When normalizing to 1 this will allways end up being 1)
	
	int i = 0; //so that the degree steps can be varied to unevenly spaced values separate counter is used
	TNtuple* distrib = new TNtuple("angularDistrib","FragmentAngularDistrib","angle:particleAmount:normalized");

	std::cout << "Fragments comparison to the graphs in appendices of E.Haettner\n";

	//This will norm it to the zero degree entry to get rid of Emma's weird normalization
	//fixme detectorsidelengthstring
	rMinString = "0.00";
	rMaxString = "2.00";
	//SA of a square Double_t zeroSAsquare = 4 * TMath::ASin(pow(detectorSideLength,2.0) / (4*pow(scatteringDistance,2) + pow(detectorSideLength,2)) );
	//SA with square approx squareApprox = (4*4) / (4*3.14*scatteringDistance*scatteringDistance);
	
	//First calculates the normalization from teh zero position
	//Normalization by events becomes redundant but is left in place for future needs
	Double_t normEntries = fragments->GetEntries("(Z == " + Znum + " && energy > 0 && sqrt(posY^2 + posZ^2) < " + rMaxString + "&& sqrt(posY*posY + posZ*posZ) > " + rMinString + ")");
	Double_t deltaPhi = TMath::ATan((detectorSideLength/2)/scatteringDistance);
	Double_t zeroSA = 2*TMath::Pi()*(TMath::Cos(0) - TMath::Cos(deltaPhi));
	Double_t zeroNorm = normEntries / (events * zeroSA);

	//Loop through all other wanted angles, too large angles will fall outside reach of phantom window.
	for(Double_t j = 0.0; j <= 15.0; j=j+.05){
		i++;
		degrees = j * TMath::DegToRad();
		//Distance from straight beam at the requested angle
		r = scatteringDistance * TMath::Tan(degrees);
		//now the "detector is rotated around all possible perpendicularlynangle values to beamline".
		//This forms an annulus with rMin and Rmax as otuer and inner radiuses
		//this will give a bit of approximation at small angles and at 0 degrees this gives a completely round sensor.
		rMin = TMath::Max(0.0,r - (detectorSideLength/2));
		rMax = r + (detectorSideLength/2);
		rMinString = Form("%f", rMin);
		rMaxString = Form("%f", rMax);
		
		//deltaPhi calculated so that phi+deltaphi points to one side of the detector and phi-deltaphi the other side
		Double_t deltaPhi = degrees - TMath::ATan(TMath::Tan(degrees) - (detectorSideLength/(2*scatteringDistance)));
		/*
		* From Gunzert-marx. Solid angle of annulus with rmin trmax, 
		* a bit of an aproximation especially at small phi.
		*/
		Double_t deltaOmega = 2*TMath::Pi()*(TMath::Cos(TMath::Max(0.0,degrees-deltaPhi)) - TMath::Cos(degrees+deltaPhi));
		int numEntries = fragments->GetEntries("(Z == " + Znum + " && energy > 0 && sqrt(posY^2 + posZ^2) < " + rMaxString + "&& sqrt(posY*posY + posZ*posZ) > " + rMinString + ")");
		distrib->Fill(j,numEntries,numEntries/(deltaOmega * events * zeroNorm)); //< degrees, entyamount, normalized result for graph
		distrib->Fill(-j,numEntries,numEntries/(deltaOmega * events * zeroNorm)); //< To get gaussian shape better visible
		maxValue = TMath::Max(maxValue, numEntries/(deltaOmega * events * zeroNorm)); //< for calculation of FWHM
		}
	distrib->SetMarkerStyle(1); //filled dot
	distrib->SetMarkerColor(kBlue);
	distrib->Draw("normalized:angle","angle > -3 && angle < 14","p"); //similar axises to e.haettner
	ntuple->SetMarkerStyle(22); //triangle
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
	TString experimentalNorm = Form("(1/%f)*", zeroPosData);
	ntuple->Draw(experimentalNorm + "y:x","","p,same");


	//Calculate FWHM, ineffective solution. (but works also without normalizing to 1)
	Float_t fwhm = 0.0, middle = 0.0, currentX, currentY;
	distrib->SetBranchAddress("normalized",&currentY);
	distrib->SetBranchAddress("angle",&currentX);
	for(int i = 0; i < distrib->GetEntries(); i++){
		distrib->GetEntry(i);
		if(pow(maxValue/2 - middle, 2.0) > pow(maxValue/2 - currentY, 2.0)){
				fwhm = 2*currentX;
				middle = currentY;
			}else{
				}
		}
		std::cout << "Calculated (closest point) FWHM of Monte-Carlo simulation to be: " << fwhm << " degrees" << endl; 
	
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
	
	
	c1->SaveAs("angularDistrib_for_Z_" + Znum + "_ComparedToEHaettner.png");
	in.close();
	f->Write();
}
