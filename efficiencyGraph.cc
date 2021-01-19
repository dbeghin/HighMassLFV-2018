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


ZPrime_600.root   15.4251
ZPrime_1000.root  20.4253
ZPrime_1200.root  20.9638
ZPrime_1400.root  21.8124
ZPrime_1600.root  22.6064
ZPrime_1800.root  23.0804
ZPrime_2000.root  23.2793
ZPrime_3000.root  21.7026
ZPrime_3500.root  22.307
ZPrime_4500.root  16.8919
ZPrime_5000.root  17.0644
ZPrime_6000.root  16.4787


QBH_600.root   23.0691
QBH_1000.root  25.645
QBH_1200.root  25.8199
QBH_1400.root  26.3758
QBH_1600.root  26.405
QBH_1800.root  26.0373
QBH_2000.root  25.9904
QBH_3000.root  25.7469
QBH_3500.root  25.7892
QBH_4500.root  24.6179
QBH_5000.root  23.9553
QBH_6000.root  22.6394


RPV_600.root   18.1929
RPV_1000.root  24.3926
RPV_1200.root  25.3475
RPV_1400.root  26.0667
RPV_1600.root  26.6037
RPV_1800.root  26.865
RPV_2000.root  26.5357
RPV_3000.root  25.6609
RPV_3500.root  25.7475
RPV_4500.root  24.7026
RPV_5000.root  24.9506
RPV_6000.root  18.663


  vector<float> xpoints_zprime = {500.,   
				  600.,  
				  700.,  
				  800.,  
				  900., 
				  1000, 
				  1100, 
				  1200, 
				  1300, 
				  1400, 
				  1500, 
				  1600, 
				  1700, 
				  1800, 
				  1900, 
				  2000, 
				  2200, 
				  2400, 
				  2600, 
				  2800, 
				  3000, 
				  3500, 
				  4000,
				  4500,
				  5000,
				  5500,
				  6000};



//  vector<float> ypoints_zprime_emu = {54.06,
//				      56.29,
//				      55.64,
//				      57.84,
//				      60.92,
//				      61.64,
//				      61.44,
//				      62.65,
//				      62.34,
//				      61.39,
//				      60.19,
//				      57.60,
//				      60.13,
//				      60.51,
//				      62.32,
//				      63.42,
//				      56.11,
//				      50.55,
//				      62.66,
//				      47.16,
//				      56.13,
//				      33.90,
//				      24.97};


  vector<float> ypoints_zprime_mutau = {13.0286,   
				        15.4294,
				        17.3844,
				        18.7978,
				        19.4121,
				        20.3524,
				        21.024 ,
				        21.2787,
				        22.1911,
				        21.9765,
				        23.2024,
				        22.7113,
				        22.6982,
				        22.8732,
				        22.6235,
				        22.9992,
				        22.8837,
				        22.3779,
				        22.5618,
				        22.1224,
				        21.8179,
				        20.7752,
				        18.65  ,
					17.9067,
					16.7001,
					15.9732,
					15.3447};





//  vector<float> ypoints_zprime_etau =  {13.5539,
//				        15.4671,
//				        16.8475,
//				        17.6358,
//				        18.5062,
//				        19.1077,
//				        19.9501,
//				        19.9929,
//				        20.6545,
//				        20.4733,
//				        20.4801,
//				        20.6876,
//				        20.5944,
//				        21.023 ,
//				        20.6685,
//				        20.6934,
//				        20.7762,
//				        20.6494,
//				        20.3901,
//				        19.7579,
//				        17.7607,
//				        14.2737,
//				        12.8943};


  /////////////////////////////RPV\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


  vector<float> xpoints_rpv = {200 ,    
  			       300 ,
  			       400 ,
  			       500 ,
  			       600 ,
  			       700 ,
  			       800 ,
  			       900 ,
  			       1000,
  			       1200,
  			       1400,
  			       1600,
  			       1800,
  			       2000,
  			       2500,
  			       3000,
  			       3500,
  			       4000,
  			       4500,
  			       5000};
  

  
//  vector<float> ypoints_rpv_emu = {39.12,
//  				   48.33,
//  				   //50.19,
//  				   53.61,
//  				   54.30,
//  				   //56.56,
//  				   56.41,
//  				   //57.75,
//  				   60.48,
//  				   60.51,
//  				   60.57,
//  				   59.36,
//  				   55.51,
//  				   57.08,
//  				   59.46,
//  				   57.29,
//				   39.87,
//  				   51.03,
//  				   26.17,
//  				   24.32};
  
  vector<float> ypoints_rpv_mutau = {1.36204,
  				     7.42213,
  				     11.851786,
  				     15.7791,
  				     17.2568,
  				     20.077929,
  				     21.2053,
  				     22.506522,
  				     22.6599,
  				     23.2626,
  				     22.911 ,
  				     22.9399,
  				     22.4528,
  				     22.0841,
  				     19.9271,
  				     16.4726,
  				     14.0885,
  				     11.9697,
  				     9.99573,
  				     8.22123};


//  vector<float> ypoints_rpv_etau =  {01.18832,
//  				     06.24402,
//  				     13.0093 ,
//  				     15.4703 ,
//  				     19.5716 ,
//  				     20.9864 ,
//  				     21.8841 ,
//  				     22.9033 ,
//  				     22.5731 ,
//  				     22.8857 ,
//  				     22.9644 ,
//  				     23.5582 ,
//  				     23.5944 ,
//  				     23.6052 ,
//  				     22.2802 ,
//  				     12.8979 ,
//  				     08.46977};




  /////////////////////////////QBH\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

  vector<float> xpoints_qbh = {200.,   
			       400., 
			       600., 
			       800., 
			       1000,
			       1200,
			       1400,
			       1600,
			       1800,
			       2000,
			       2500,
			       3000,
			       3500,
			       4000,
			       4500,
			       5000,
			       5500,
			       6000,
			       7000};


//  vector<float> ypoints_qbh_emu = {48.88,  
//				   58.68,
//				   65.68,
//				   65.75,
//				   65.27,
//				   65.86,
//				   64.56,
//				   70.22,
//				   62.79,
//				   63.85,
//				   63.86,
//				   58.76,
//				   62.42,
//				   51.02,
//				   36.20,
//				   36.40};

  vector<float> ypoints_qbh_mutau = {12.931 ,
				     19.3131,
				     22.2294,
				     23.5738,
				     24.3995,
				     24.6162,
				     24.2214,
				     24.1376,
				     23.6422,
				     23.1877,
				     21.5624,
				     19.7665,
				     18.2321,
				     18.3559,
				     17.7118,
				     17.4495,
				     17.6562,
				     17.2683,
				     14.3943};


//  vector<float> ypoints_qbh_etau =  {11.3646 ,
//				     16.6423 ,
//				     20.2055 ,
//				     21.9062 ,
//				     22.1696 ,
//				     22.7276 ,
//				     23.1955 ,
//				     23.1941 ,
//				     23.1817 ,
//				     23.545  ,
//				     23.2986 ,
//				     23.5383 ,
//				     22.2766 ,
//				     16.381  ,
//				     10.2068 ,
//				     07.37597};

    




  int n_signals = 1;
  int n_channels = 1;
  vector<float> ypoints[n_signals][n_channels];
  ypoints[0][0] = ypoints_zprime_mutau;
  //ypoints[1][0] = ypoints_rpv_mutau;
  //ypoints[2][0] = ypoints_qbh_mutau;

  vector<float> xpoints[n_signals];
  xpoints[0] = xpoints_zprime;
  //xpoints[1] = xpoints_rpv;
  //xpoints[2] = xpoints_qbh;

  vector<int> color;
  color.push_back(kAzure+10);
  color.push_back(kOrange-1);
  color.push_back(kGreen+2);


  vector<TString> signals;
  signals.push_back("ZPrime");
  //signals.push_back("RPV");
  //signals.push_back("QBH");

  vector<TString> channels;
  channels.push_back("#mu #tau channel");
  //channels.push_back("e #mu channel");
  //channels.push_back("e #tau channel");


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
    //leg->SetHeader("channels");
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
    full->GetXaxis()->SetTitle(signals[iSig]+" mass (GeV)");
    full->GetYaxis()->SetTitle("Efficiency (%)");
    full->SetMinimum(0);
    full->SetMaximum(30);

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
