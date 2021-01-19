#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TLegend.h"
#include "THStack.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TMultiGraph.h"

using namespace std;


int main(int argc, char** argv) {
  TFile* file_in_fakes = new TFile("HighMassLFVMuTau/fakerate_factorised_wjets.root", "R");
  TString masspoint = *(argv+1);
  TString signal_in = "ZPrime_"+masspoint;
  TFile* file_in_signal = new TFile("HighMassLFVMuTau/MassResolution/Arranged_signal/"+signal_in+".root", "R");
  TFile* file_out =  new TFile("HighMassLFVMuTau/TauIDROC_"+signal_in+".root", "RECREATE");


  vector<TString> deepTauIDs_fakes;
  deepTauIDs_fakes.push_back("FakeRateByTauPt_total_DeepTauVVL");
  deepTauIDs_fakes.push_back("FakeRateByTauPt_total_DeepTauVL");
  deepTauIDs_fakes.push_back("FakeRateByTauPt_total_DeepTauL");
  deepTauIDs_fakes.push_back("FakeRateByTauPt_total_DeepTauM");
  deepTauIDs_fakes.push_back("FakeRateByTauPt_total_DeepTauT");
  deepTauIDs_fakes.push_back("FakeRateByTauPt_total_DeepTauVT");
  deepTauIDs_fakes.push_back("FakeRateByTauPt_total_DeepTauVVT");


  vector<TString> deepTauIDs_signal;
  deepTauIDs_signal.push_back("Mcol_jetvvloose");
  deepTauIDs_signal.push_back("Mcol_jetvloose");
  deepTauIDs_signal.push_back("Mcol_jetloose");
  deepTauIDs_signal.push_back("Mcol_jetmedium");
  deepTauIDs_signal.push_back("Mcol_jettight");
  deepTauIDs_signal.push_back("Mcol_jetvtight");
  deepTauIDs_signal.push_back("Mcol_jetvvtight");


  float ypoints_fakerate[deepTauIDs_fakes.size()];
  float xpoints_signaleff[deepTauIDs_signal.size()];

  TH1D* h_signal_den = (TH1D*) file_in_signal->Get("Mcol_nodisc");
  for (unsigned int k=0; k<deepTauIDs_fakes.size(); ++k) { 
    TH1D* h_temp_fakes = (TH1D*) file_in_fakes->Get(deepTauIDs_fakes[k]);
    ypoints_fakerate[k] = h_temp_fakes->Integral();
    delete h_temp_fakes;

    TH1D* h_temp_signal = (TH1D*) file_in_signal->Get(deepTauIDs_signal[k]);
    xpoints_signaleff[k] = h_temp_signal->Integral()/h_signal_den->Integral(); 
    delete h_temp_signal;
  }

  TH1D* h_temp_MVA_f = (TH1D*) file_in_fakes->Get("FakeRateByTauPt_total_MVATau");
  float MVA_y_fakerate[1];
  MVA_y_fakerate[0] = h_temp_MVA_f->Integral();
  delete h_temp_MVA_f;

  TH1D* h_temp_MVA_s = (TH1D*) file_in_signal->Get("Mcol_oldjettight");
  float MVA_x_signaleff[1];
  MVA_x_signaleff[0] = h_temp_MVA_s->Integral()/h_signal_den->Integral();
  delete h_temp_MVA_s;
  delete h_signal_den;


  TGraph *gr =  new TGraph(deepTauIDs_fakes.size(), xpoints_signaleff, ypoints_fakerate);
  gr->SetMarkerStyle(25);
  gr->SetLineColor(kAzure+10);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kAzure+10);


  TGraph *gr_norm =  new TGraph(1, MVA_x_signaleff, MVA_y_fakerate);
  gr_norm->SetMarkerStyle(8);
  gr_norm->SetLineColor(kOrange-1);
  gr_norm->SetLineWidth(2);
  gr_norm->SetMarkerColor(kOrange-1);



  file_out->cd();
  TCanvas* c = new TCanvas("canvas","",900,600);
  c->cd();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();

  TMultiGraph *full = new TMultiGraph("multigraph","");
  full->Add(gr);
  full->Add(gr_norm);
  cout << full << endl;
  cout << gr->GetXaxis() << endl;
  cout << gr_norm->GetYaxis() << endl;
  full->Draw("APL");
  full->GetXaxis()->SetTitle("efficiency of Z' #rightarrow e #tau ("+masspoint+" GeV)");
  full->GetYaxis()->SetTitle("mis-id rate (WJetsToLNu)");
  full->SetMinimum(0.0001);
  full->SetMaximum(0.1);

  full->Draw("APL");
  full->Write();
  c->SaveAs("HighMassLFVMuTau/ROC_"+signal_in+".pdf");
  file_out->Close();



  return 0;
}
