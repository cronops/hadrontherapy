void braggPeaks(){
   gROOT->Reset();
   TFile *f1 = TFile::Open("../../../DoseDistribution400MeV.root");
   TH1F* h1 = (TH1F*)f1->Get("braggPeak");
   TFile *f2 = TFile::Open("../../../DoseDistribution200MeV.root");
   TH1F* h2 = (TH1F*)f2->Get("braggPeak");
   c1 = new TCanvas("c1","Bragg peaks for different particles",200,10,750,940);
   h1->Draw();
   h2->Draw("same");
}
