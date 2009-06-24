{
//=========Macro generated from canvas: c1/Bragg peaks for different energies
//=========  (Wed Jun 24 14:15:51 2009) by ROOT version5.23/05
   TCanvas *c1 = new TCanvas("c1", "Bragg peaks for different energies",203,48,750,724);
   c1->Range(-6,-109.3675,34,619.7489);
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.15);
   c1->SetBottomMargin(0.15);
   c1->SetFrameFillColor(0);
   c1->SetFrameLineWidth(3);
   
   TH1 *bp = new TH1F("bp","slice, energy",400,0,400);
   bp->SetBinContent(1,152.6695);
   bp->SetBinContent(2,158.7263);
   bp->SetBinContent(3,171.632);
   bp->SetBinContent(4,189.0227);
   bp->SetBinContent(5,214.033);
   bp->SetBinContent(6,252.7878);
   bp->SetBinContent(7,332.2003);
   bp->SetBinContent(8,520.7974);
   bp->SetBinContent(9,8.138844);
   bp->SetEntries(9);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.835,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(2);
   ptstats->SetFillColor(10);
   ptstats->SetLineWidth(3);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("braggPeak");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 9      ");
   text = ptstats->AddText("Mean  =  4.946");
   text = ptstats->AddText("RMS   =  2.318");
   ptstats->SetOptStat(1);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   bp->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(bp->GetListOfFunctions());

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   bp->SetLineColor(ci);
   bp->SetLineWidth(3);
   bp->GetXaxis()->SetRange(1,30);

   ci = TColor::GetColor("#0000ff");
   bp->GetXaxis()->SetLabelColor(ci);
   bp->GetXaxis()->SetLabelSize(0.05);
   bp->GetXaxis()->SetTitleSize(0.06);

   ci = TColor::GetColor("#0000ff");
   bp->GetYaxis()->SetLabelColor(ci);
   bp->GetYaxis()->SetLabelOffset(0.01);
   bp->GetYaxis()->SetLabelSize(0.05);
   bp->GetYaxis()->SetTitleSize(0.06);
   bp->GetYaxis()->SetTitleOffset(1.3);
   bp->GetZaxis()->SetLabelSize(0.05);
   bp->GetZaxis()->SetTitleSize(0.06);
   bp->Draw("");
   
   TH1 *braggPeak = new TH1F("bla","slice, energy",400,0,400);
   braggPeak->SetBinContent(1,179.6287);
   braggPeak->SetBinContent(2,185.5305);
   braggPeak->SetBinContent(3,199.5378);
   braggPeak->SetBinContent(4,216.4599);
   braggPeak->SetBinContent(5,242.6645);
   braggPeak->SetBinContent(6,282.2909);
   braggPeak->SetBinContent(7,362.749);
   braggPeak->SetBinContent(8,552.6453);
   braggPeak->SetBinContent(9,40.85238);
   braggPeak->SetBinContent(10,33.51675);
   braggPeak->SetBinContent(11,35.19225);
   braggPeak->SetBinContent(12,37.29899);
   braggPeak->SetBinContent(13,39.02097);
   braggPeak->SetBinContent(14,41.14077);
   braggPeak->SetBinContent(15,43.05803);
   braggPeak->SetBinContent(16,47.19661);
   braggPeak->SetBinContent(17,51.08226);
   braggPeak->SetBinContent(18,57.25814);
   braggPeak->SetBinContent(19,66.80163);
   braggPeak->SetBinContent(20,85.67361);
   braggPeak->SetBinContent(21,121.1125);
   braggPeak->SetBinContent(22,55.633);
   braggPeak->SetBinContent(23,15.05565);
   braggPeak->SetBinContent(24,5.457128);
   braggPeak->SetEntries(24);

   ci = TColor::GetColor("#ff0000");
   braggPeak->SetLineColor(ci);
   braggPeak->SetLineWidth(3);
   braggPeak->GetXaxis()->SetRange(1,30);

   ci = TColor::GetColor("#0000ff");
   braggPeak->GetXaxis()->SetLabelColor(ci);
   braggPeak->GetXaxis()->SetLabelSize(0.05);
   braggPeak->GetXaxis()->SetTitleSize(0.06);

   ci = TColor::GetColor("#0000ff");
   braggPeak->GetYaxis()->SetLabelColor(ci);
   braggPeak->GetYaxis()->SetLabelOffset(0.01);
   braggPeak->GetYaxis()->SetLabelSize(0.05);
   braggPeak->GetYaxis()->SetTitleSize(0.06);
   braggPeak->GetYaxis()->SetTitleOffset(1.3);
   braggPeak->GetZaxis()->SetLabelSize(0.05);
   braggPeak->GetZaxis()->SetTitleSize(0.06);
   braggPeak->Draw("same");
   
   TPaveText *pt = new TPaveText(0.01,0.9417049,0.2980965,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(10);
   pt->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   pt->SetTextColor(ci);
   pt->SetTextSize(0.05);
   text = pt->AddText("slice, energy");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
