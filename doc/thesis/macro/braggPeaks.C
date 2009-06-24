void braggPeaks(){
   gROOT->Reset();
   gROOT->SetStyle("Pub");
//   TFile *f1 = TFile::Open("../../../DoseDistribution400MeV.root");
	TFile *f1 = TFile::Open("DoseDistribution400MeV.root");
   TH1F* h1 = (TH1F*)f1->Get("braggPeak");
//   TFile *f2 = TFile::Open("../../../DoseDistribution200MeV.root");
   TFile *f2 = TFile::Open("DoseDistribution200MeV.root");
   TH1F* h2 = (TH1F*)f2->Get("braggPeak");
   c1 = new TCanvas("c1","Bragg peaks for different energies",200,10,750,940);
   (h1->GetXaxis())->SetRange(0,200);
   (h2->GetXaxis())->SetRange(0,200);
   h1->Draw();
   h2->Draw("same");
}
