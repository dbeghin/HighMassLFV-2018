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


int main() {
  TFile* file_out =  new TFile("HighMassLFVMuTau/signal_efficiencies.root", "RECREATE");



  vector<float> xxpoints        = {600 ,   
				  1000,  
				  1200,  
				  1400,  
				  1600, 
				  1800, 
				  2000, 
				  3000, 
				  3500, 
				  4500, 
				  5000, 
				  6000};




  vector<float> ypoints_zprime       = {15.4251,   
				        20.4253,
				        20.9638,
				        21.8124,
				        22.6064,
				        23.0804,
				        23.2793,
				        21.7026,
				        22.307 ,
				        16.8919,
				        17.0644,
				        16.4787};


  vector<float> ypoints_rpv          = {18.1929,   
				        24.3926,
				        25.3475,
				        26.0667,
				        26.6037,
				        26.865 ,
				        26.5357,
				        25.6609,
				        25.7475,
				        24.7026,
				        24.9506,
				        23.0401};


  vector<float> ypoints_qbh          = {23.0691,   
				        25.645 ,
				        25.8199,
				        26.3758,
				        26.405 ,
				        26.0373,
				        25.9904,
				        25.7469,
				        25.7892,
				        24.6179,
				        23.9553,
				        22.6394};






    




  int n_signals = 1;
  int n_channels = 3;
  vector<float> ypoints[n_signals][n_channels];
  ypoints[0][0] = ypoints_zprime;
  ypoints[0][1] = ypoints_rpv;
  ypoints[0][2] = ypoints_qbh;
  //ypoints[1][0] = ypoints_rpv_mutau;
  //ypoints[2][0] = ypoints_qbh_mutau;

  vector<float> xpoints[n_signals];
  xpoints[0] = xxpoints;
  //xpoints[1] = xpoints_rpv;
  //xpoints[2] = xpoints_qbh;

  vector<int> color;
  color.push_back(kAzure+10);
  color.push_back(kOrange-1);
  color.push_back(kGreen+2);


  vector<TString> signals;
  signals.push_back("mutau");
  //signals.push_back("RPV");
  //signals.push_back("QBH");

  vector<TString> channels;
  channels.push_back("Z'");
  channels.push_back("RPV");
  channels.push_back("QBH");


  TGraph* gr[n_signals][n_channels];
  //vector<TMultiGraph*> full;


  file_out->cd();
  for (unsigned int iSig = 0; iSig < n_signals; ++iSig) {
    int array_size = xpoints[iSig].size();
    float x_array[array_size];
    for (unsigned int kArray = 0; kArray < array_size; ++kArray) x_array[kArray] = xpoints[iSig][kArray];

    TLegend* leg = new TLegend(0.7,0.7,0.9,0.9, "", "brNDC");
    //leg->SetNColumns(2);
    leg->SetLineWidth(0);
    leg->SetLineStyle(0);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextFont(62);
    //leg->SetTextSize ( 0.06 );
    leg->SetHeader("#mu #tau channel");
    for (unsigned int jChan = 0; jChan < n_channels; ++jChan) {
      float y_array[array_size];
      for (unsigned int kArray = 0; kArray < array_size; ++kArray) y_array[kArray] = ypoints[iSig][jChan][kArray];
      gr[iSig][jChan] = new TGraph(array_size, x_array, y_array);
      gr[iSig][jChan]->SetMarkerStyle(25);
      //gr_norm->SetMarkerStyle(8);
      gr[iSig][jChan]->SetLineColor(color[jChan]);
      gr[iSig][jChan]->SetLineWidth(2);
      gr[iSig][jChan]->SetMarkerColor(color[jChan]);
      leg->AddEntry(gr[iSig][jChan], channels[jChan], "lp");
    }

    TCanvas* c = new TCanvas("canvas","",900,600);
    c->cd();
    gPad->SetGridx();
    gPad->SetGridy();
    //gPad->SetLogy();
    TMultiGraph *full = new TMultiGraph("multigraph","");
    for (unsigned int jChan = 0; jChan < n_channels; ++jChan) full->Add(gr[iSig][jChan]);
    full->Draw("APL");
    full->GetXaxis()->SetTitle("Signal mass (GeV)");
    full->GetYaxis()->SetTitle("Acceptance x Efficiency (%)");
    full->SetMinimum(0);
    full->SetMaximum(40);

    full->Draw("APL");
    leg->Draw("same");
    full->Write();
    c->SaveAs("HighMassLFVMuTau/Efficiency_"+signals[iSig]+".pdf");
    delete c;
    delete full;
  }
  file_out->Close();



  return 0;
}
