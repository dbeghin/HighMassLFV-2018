#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TLegend.h"
#include "THStack.h"
#include "TStyle.h"

using namespace std;
int main(/*int argc, char** argv*/) {
  TFile* file_out = new TFile("Figures/histos_highmassmutau.root", "RECREATE");
  TFile* file_in  = new TFile("Figures/histos_highmassmutau_CR100.root", "R");

  vector<TString> names;
  names.push_back("data_");//0
  names.push_back("faketau_");
  names.push_back("DY_");
  names.push_back("TT_");
  //names.push_back("ST_");
  names.push_back("VV_");
  //names.push_back("Signal_");//FIXME


  //rebin vectors
  vector<float> xpoints {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000/*, 1500, 2000, 4000*/};
  cout << xpoints.size() << endl;

  vector<float> xpoints_MET {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 150, 200, 300, 500/*, 700, 1000*/};

  vector<float> xpoints_pt {0, 10, 20, 30, 40, 50, 60, 70, 80, 100, 150, 300, 1000};

  //vector<float> xpoints_Mt {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120}; //for Mt low FIXME
  vector<float> xpoints_Mt = xpoints; //for Mt high

  //float x[] = {0, 50, 60, 70, 80, 90, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1500, 2000, 4000};


  vector<TString> vars;                     vector<bool> simpleRebin;         vector<int> rebin;      vector<vector<float>> rebin_vector;
  vars.push_back("ev_Mvis");                simpleRebin.push_back(false);     rebin.push_back(1);     rebin_vector.push_back(xpoints);
  vars.push_back("ev_Mtot");		    simpleRebin.push_back(false);     rebin.push_back(1);     rebin_vector.push_back(xpoints);
  vars.push_back("tau_pt");		    simpleRebin.push_back(false);     rebin.push_back(1);     rebin_vector.push_back(xpoints_pt);
  vars.push_back("tau_eta");		    simpleRebin.push_back(true);      rebin.push_back(2);     rebin_vector.push_back(xpoints);
  vars.push_back("tau_phi");		    simpleRebin.push_back(true);      rebin.push_back(2);     rebin_vector.push_back(xpoints);
  vars.push_back("mu_pt");		    simpleRebin.push_back(false);     rebin.push_back(1);     rebin_vector.push_back(xpoints_pt);
  vars.push_back("mu_eta");		    simpleRebin.push_back(true);      rebin.push_back(2);     rebin_vector.push_back(xpoints);
  vars.push_back("mu_phi");		    simpleRebin.push_back(true);      rebin.push_back(2);     rebin_vector.push_back(xpoints);
  vars.push_back("mu_isolation");	    simpleRebin.push_back(true);      rebin.push_back(2);     rebin_vector.push_back(xpoints);
  vars.push_back("ev_DRmutau");		    simpleRebin.push_back(true);      rebin.push_back(2);     rebin_vector.push_back(xpoints);
  vars.push_back("ev_MET");		    simpleRebin.push_back(false);     rebin.push_back(1);     rebin_vector.push_back(xpoints_MET);
  vars.push_back("ev_Mcol");                simpleRebin.push_back(false);     rebin.push_back(1);     rebin_vector.push_back(xpoints);                
  vars.push_back("ev_Mt");                  simpleRebin.push_back(false);     rebin.push_back(1);     rebin_vector.push_back(xpoints_Mt);                
  vars.push_back("sign");                   simpleRebin.push_back(true);      rebin.push_back(1);     rebin_vector.push_back(xpoints_Mt);                

  vector<TString> Mth;
  Mth.push_back("_MtHigh");
  Mth.push_back("_MtHigh_TT");
  Mth.push_back("_MtLow_OS");
  Mth.push_back("_MtLow_SS");
  Mth.push_back("_MtLow_TT");


  //retrieve all histos and rebin them
  vector<TH1F*> h[names.size()][vars.size()];
  vector<TH1F*> h_rebinned[names.size()][vars.size()];
  for (unsigned int j=0; j<names.size(); ++j) {
    for (unsigned int k=0; k<vars.size(); ++k) { 
      for (unsigned int l=0; l<Mth.size(); ++l) {
	h[j][k].push_back( (TH1F*) file_in->Get(names[j]+vars[k]+Mth[l]) );
	h[j][k][l]->SetName(names[j]+vars[k]+Mth[l]+"_old");

	if (simpleRebin[k]) {
	  h_rebinned[j][k].push_back( (TH1F*) h[j][k][l]->Clone(names[j]+vars[k]+Mth[l]) );
	  h_rebinned[j][k][l]->Rebin(rebin[k]);
	}
	else {
	  int array_size = rebin_vector[k].size();
	  float rebin_array[array_size];
	  for (unsigned int ii=0; ii<array_size; ++ii) rebin_array[ii] = rebin_vector[k][ii];
	  h_rebinned[j][k].push_back( new TH1F(names[j]+vars[k]+Mth[l], names[j]+vars[k]+Mth[l], array_size-1, rebin_array) );

	  int jBin = 1;
	  float bin_content = 0, bin_error=0;
	  for (unsigned int iBin=1; iBin < h[j][k][l]->GetNbinsX()+1; ++iBin) {
	    if (h[j][k][l]->GetBinCenter(iBin) < rebin_array[jBin]) {
	      bin_content += h[j][k][l]->GetBinContent(iBin);
	      bin_error += pow(h[j][k][l]->GetBinError(iBin), 2);
	    }
	    else {
	      bin_content = bin_content/(rebin_array[jBin]-rebin_array[jBin-1]);
	      bin_error = sqrt(bin_error)/(rebin_array[jBin]-rebin_array[jBin-1]);
	      h_rebinned[j][k][l]->SetBinContent(jBin, bin_content);
	      h_rebinned[j][k][l]->SetBinError(jBin, bin_error);
	      bin_content = h[j][k][l]->GetBinContent(iBin);
	      bin_error = pow(h[j][k][l]->GetBinError(iBin), 2);
	      
	      ++jBin;
	    }
	  }
	  bin_content = bin_content/(rebin_array[jBin]-rebin_array[jBin-1]);
	  bin_error = sqrt(bin_error)/(rebin_array[jBin]-rebin_array[jBin-1]);
	  h_rebinned[j][k][l]->SetBinContent(jBin, bin_content);
	  h_rebinned[j][k][l]->SetBinError(jBin, bin_error);
	}
      }
    }
  }


  //Write the rebinned histos in the output file
  file_out->cd();
  for (unsigned int j=0; j<names.size(); ++j) {
    for (unsigned int k=0; k<vars.size(); ++k) {
      for (unsigned int l=0; l<Mth.size(); ++l) {
	h_rebinned[j][k][l]->Write();
      }
    }
  }
  file_out->Close();



  return 0;
}