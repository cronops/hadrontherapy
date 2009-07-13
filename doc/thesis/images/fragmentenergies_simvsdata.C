{
//=========Macro generated from canvas: histograms/Histograms
//=========  (Mon Jul 13 13:01:37 2009) by ROOT version5.23/05
   TCanvas *histograms = new TCanvas("histograms", "Histograms",13,48,700,500);
   histograms->Range(-56.25,-0.03337503,506.25,0.3003753);
   histograms->SetBorderSize(2);
   histograms->SetFrameFillColor(0);
   
   TH1 *histHe = new TH1F("histHe","Recorded fragments",60,0,450);
   histHe->SetBinContent(7,0.05714284);
   histHe->SetBinContent(8,0.05999998);
   histHe->SetBinContent(9,0.05714284);
   histHe->SetBinContent(10,0.06857141);
   histHe->SetBinContent(11,0.1114285);
   histHe->SetBinContent(12,0.1028571);
   histHe->SetBinContent(13,0.09142854);
   histHe->SetBinContent(14,0.1171428);
   histHe->SetBinContent(15,0.07999998);
   histHe->SetBinContent(16,0.1542857);
   histHe->SetBinContent(17,0.1228571);
   histHe->SetBinContent(18,0.1457143);
   histHe->SetBinContent(19,0.1342857);
   histHe->SetBinContent(20,0.1742858);
   histHe->SetBinContent(21,0.1514286);
   histHe->SetBinContent(22,0.1685715);
   histHe->SetBinContent(23,0.1542857);
   histHe->SetBinContent(24,0.1771429);
   histHe->SetBinContent(25,0.197143);
   histHe->SetBinContent(26,0.1914287);
   histHe->SetBinContent(27,0.2542859);
   histHe->SetBinContent(28,0.1771429);
   histHe->SetBinContent(29,0.2085716);
   histHe->SetBinContent(30,0.2228573);
   histHe->SetBinContent(31,0.2114287);
   histHe->SetBinContent(32,0.1514286);
   histHe->SetBinContent(33,0.1514286);
   histHe->SetBinContent(34,0.1342857);
   histHe->SetBinContent(35,0.1057142);
   histHe->SetBinContent(36,0.09999996);
   histHe->SetBinContent(37,0.07714283);
   histHe->SetBinContent(38,0.06857141);
   histHe->SetBinContent(39,0.05999998);
   histHe->SetBinContent(40,0.03142857);
   histHe->SetBinContent(41,0.02571429);
   histHe->SetBinContent(42,0.03428571);
   histHe->SetBinContent(43,0.01142857);
   histHe->SetBinContent(44,0.01142857);
   histHe->SetBinContent(45,0.002857143);
   histHe->SetBinContent(46,0.002857143);
   histHe->SetBinContent(47,0.005714286);
   histHe->SetEntries(1598);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.835,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(2);
   ptstats->SetFillColor(19);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("histogram");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 1598   ");
   text = ptstats->AddText("Mean  =  180.7");
   text = ptstats->AddText("RMS   =  62.91");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   histHe->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(histHe->GetListOfFunctions());

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   histHe->SetLineColor(ci);
   histHe->Draw("");
   
   TH1 *histB = new TH1F("histB","Boron",60,0,450);

   ci = TColor::GetColor("#ffff00");
   histB->SetLineColor(ci);
   histB->Draw("same");
   
   TH1 *histH = new TH1F("histH","Hydrogen",60,0,450);
   histH->SetBinContent(8,0.002857143);
   histH->SetBinContent(9,0.02571429);
   histH->SetBinContent(11,0.008571428);
   histH->SetBinContent(12,0.01714286);
   histH->SetBinContent(13,0.02);
   histH->SetBinContent(14,0.01714286);
   histH->SetBinContent(15,0.02571429);
   histH->SetBinContent(16,0.03142857);
   histH->SetBinContent(17,0.02571429);
   histH->SetBinContent(18,0.02571429);
   histH->SetBinContent(19,0.02285714);
   histH->SetBinContent(20,0.04857142);
   histH->SetBinContent(21,0.03142857);
   histH->SetBinContent(22,0.04857142);
   histH->SetBinContent(23,0.04285714);
   histH->SetBinContent(24,0.03714285);
   histH->SetBinContent(25,0.04);
   histH->SetBinContent(26,0.05714284);
   histH->SetBinContent(27,0.03142857);
   histH->SetBinContent(28,0.08285712);
   histH->SetBinContent(29,0.06857141);
   histH->SetBinContent(30,0.07428569);
   histH->SetBinContent(31,0.06571427);
   histH->SetBinContent(32,0.04857142);
   histH->SetBinContent(33,0.04285714);
   histH->SetBinContent(34,0.05714284);
   histH->SetBinContent(35,0.04857142);
   histH->SetBinContent(36,0.06857141);
   histH->SetBinContent(37,0.04857142);
   histH->SetBinContent(38,0.09714282);
   histH->SetBinContent(39,0.05999998);
   histH->SetBinContent(40,0.03714285);
   histH->SetBinContent(41,0.03714285);
   histH->SetBinContent(42,0.04);
   histH->SetBinContent(43,0.04);
   histH->SetBinContent(44,0.04571428);
   histH->SetBinContent(45,0.05142856);
   histH->SetBinContent(46,0.03714285);
   histH->SetBinContent(47,0.04);
   histH->SetBinContent(48,0.02857143);
   histH->SetBinContent(49,0.01428571);
   histH->SetBinContent(50,0.01714286);
   histH->SetBinContent(51,0.01428571);
   histH->SetBinContent(52,0.002857143);
   histH->SetBinContent(53,0.01714286);
   histH->SetBinContent(54,0.005714286);
   histH->SetBinContent(55,0.01428571);
   histH->SetBinContent(56,0.005714286);
   histH->SetBinContent(57,0.002857143);
   histH->SetBinContent(60,0.002857143);
   histH->SetBinContent(61,0.002857143);
   histH->SetEntries(623);
   histH->Draw("same");
   
   TH1 *histLi = new TH1F("histLi","Lithium",60,0,450);
   histLi->SetBinContent(7,0.01142857);
   histLi->SetBinContent(8,0.005714286);
   histLi->SetBinContent(9,0.01714286);
   histLi->SetBinContent(10,0.02285714);
   histLi->SetBinContent(11,0.008571428);
   histLi->SetBinContent(12,0.008571428);
   histLi->SetBinContent(13,0.02);
   histLi->SetBinContent(14,0.008571428);
   histLi->SetBinContent(15,0.01714286);
   histLi->SetBinContent(16,0.01714286);
   histLi->SetBinContent(17,0.01714286);
   histLi->SetBinContent(18,0.02285714);
   histLi->SetBinContent(19,0.02);
   histLi->SetBinContent(20,0.02285714);
   histLi->SetBinContent(21,0.008571428);
   histLi->SetBinContent(22,0.02857143);
   histLi->SetBinContent(23,0.03428571);
   histLi->SetBinContent(24,0.02285714);
   histLi->SetBinContent(25,0.008571428);
   histLi->SetBinContent(26,0.005714286);
   histLi->SetBinContent(27,0.002857143);
   histLi->SetBinContent(28,0.008571428);
   histLi->SetBinContent(29,0.005714286);
   histLi->SetBinContent(30,0.002857143);
   histLi->SetBinContent(34,0.002857143);
   histLi->SetEntries(123);

   ci = TColor::GetColor("#0000ff");
   histLi->SetLineColor(ci);
   histLi->Draw("same");
   
   TH1 *histBe = new TH1F("histBe","Beryllium",60,0,450);
   histBe->SetBinContent(7,0.002857143);
   histBe->SetBinContent(9,0.008571428);
   histBe->SetBinContent(10,0.005714286);
   histBe->SetBinContent(11,0.008571428);
   histBe->SetBinContent(12,0.002857143);
   histBe->SetBinContent(13,0.005714286);
   histBe->SetBinContent(14,0.005714286);
   histBe->SetBinContent(15,0.002857143);
   histBe->SetBinContent(16,0.002857143);
   histBe->SetBinContent(17,0.002857143);
   histBe->SetBinContent(18,0.002857143);
   histBe->SetBinContent(20,0.002857143);
   histBe->SetBinContent(23,0.005714286);
   histBe->SetEntries(21);

   ci = TColor::GetColor("#00ff00");
   histBe->SetLineColor(ci);
   histBe->Draw("same");
   
   TGraph *graph = new TGraph(11);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetMarkerStyle(22);
   graph->SetPoint(0,50,0.02);
   graph->SetPoint(1,100,0.03);
   graph->SetPoint(2,120,0.04);
   graph->SetPoint(3,170,0.07);
   graph->SetPoint(4,220,0.08);
   graph->SetPoint(5,260,0.1);
   graph->SetPoint(6,280,0.08);
   graph->SetPoint(7,320,0.07);
   graph->SetPoint(8,350,0.04);
   graph->SetPoint(9,400,0.02);
   graph->SetPoint(10,460,0.01);
   
   TH1 *Graph1 = new TH1F("Graph1","Graph",100,9,501);
   Graph1->SetMinimum(0.0009999996);
   Graph1->SetMaximum(0.109);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   graph->SetHistogram(Graph1);
   
   graph->Draw("p,");
   
   graph = new TGraph(11);
   graph->SetName("Graph");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#ff0000");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(22);
   graph->SetPoint(0,50,0.03);
   graph->SetPoint(1,100,0.06);
   graph->SetPoint(2,120,0.08);
   graph->SetPoint(3,170,0.15);
   graph->SetPoint(4,220,0.2);
   graph->SetPoint(5,260,0.23);
   graph->SetPoint(6,280,0.19);
   graph->SetPoint(7,320,0.11);
   graph->SetPoint(8,350,0.03);
   graph->SetPoint(9,400,0.01);
   graph->SetPoint(10,460,0);
   
   TH1 *Graph2 = new TH1F("Graph2","Graph",100,9,501);
   Graph2->SetMinimum(0);
   Graph2->SetMaximum(0.253);
   Graph2->SetDirectory(0);
   Graph2->SetStats(0);
   graph->SetHistogram(Graph2);
   
   graph->Draw("p,");
   
   graph = new TGraph(11);
   graph->SetName("Graph");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#0000ff");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(22);
   graph->SetPoint(0,50,0);
   graph->SetPoint(1,100,0.01);
   graph->SetPoint(2,120,0.02);
   graph->SetPoint(3,170,0.03);
   graph->SetPoint(4,220,0.04);
   graph->SetPoint(5,260,0.03);
   graph->SetPoint(6,280,0.02);
   graph->SetPoint(7,320,0.01);
   graph->SetPoint(8,350,0);
   graph->SetPoint(9,400,0);
   graph->SetPoint(10,460,0);
   
   TH1 *Graph3 = new TH1F("Graph3","Graph",100,9,501);
   Graph3->SetMinimum(0);
   Graph3->SetMaximum(0.044);
   Graph3->SetDirectory(0);
   Graph3->SetStats(0);
   graph->SetHistogram(Graph3);
   
   graph->Draw("p,");
   
   graph = new TGraph(11);
   graph->SetName("Graph");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#00ff00");
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(22);
   graph->SetPoint(0,50,0.01);
   graph->SetPoint(1,100,0.02);
   graph->SetPoint(2,120,0.03);
   graph->SetPoint(3,170,0.02);
   graph->SetPoint(4,220,0.02);
   graph->SetPoint(5,260,0.01);
   graph->SetPoint(6,280,0);
   graph->SetPoint(7,320,0);
   graph->SetPoint(8,350,0);
   graph->SetPoint(9,400,0);
   graph->SetPoint(10,460,0);
   
   TH1 *Graph4 = new TH1F("Graph4","Graph",100,9,501);
   Graph4->SetMinimum(0);
   Graph4->SetMaximum(0.033);
   Graph4->SetDirectory(0);
   Graph4->SetStats(0);
   graph->SetHistogram(Graph4);
   
   graph->Draw("p,");
   
   TPaveText *pt = new TPaveText(0.01,0.945,0.1334483,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("Helium");
   pt->Draw();
   histograms->Modified();
   histograms->cd();
   histograms->SetSelected(histograms);
}
