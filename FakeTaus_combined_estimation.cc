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
#include "aux.h"

using namespace std;
int main(int argc, char** argv) {
  string nature = *(argv + 1);

  TFile* file_out;
  TFile* file_in;

  if (nature == "signal") {
    file_out = new TFile("HighMassLFVMuTau/Faketaus_CR0.root", "RECREATE");
    file_in = new TFile("Figures/histos_highmassmutau_CR101.root", "R");
  }
  else if (nature == "Wjets") {
    file_out = new TFile("HighMassLFVMuTau/Faketaus_CR102.root", "RECREATE");
    file_in = new TFile("Figures/histos_highmassmutau_CR103.root", "R");
  }
  

  vector<TString> names;
  names.push_back("data_");//0
  names.push_back("DY_");
  names.push_back("TT_");
  names.push_back("ST_");
  names.push_back("VV_");

  vector<TString> vars;
  vars.push_back("tau_pt");
  vars.push_back("ev_Mvis");
  vars.push_back("ev_Mtot");
  vars.push_back("tau_eta");
  vars.push_back("tau_phi");
  vars.push_back("mu_pt");
  vars.push_back("mu_eta");
  vars.push_back("mu_phi");
  vars.push_back("mu_isolation");
  vars.push_back("ev_DRmutau");
  vars.push_back("ev_Mt");
  vars.push_back("ev_MET");
  vars.push_back("ev_Mcol");
  vars.push_back("sign");
  vars.push_back("ev_Nvertex");
  vars.push_back("njet");
  vars.push_back("nbjet");
  //exclusively for TT region now
  int n_TT_plots = vars.size();
  vars.push_back("bjet_pt");
  vars.push_back("bjet_eta");
  vars.push_back("bjet_phi");

  
  vector<TString> Mth;
  Mth.push_back("MtLow_OS");
  Mth.push_back("MtLow_SS");
  Mth.push_back("MtHigh");
  Mth.push_back("MtLow_TT");  int k_low_TT = Mth.size()-1;
  Mth.push_back("MtHigh_TT");


  vector<TString> systs;
  systs.push_back("nominal");
  vector<TString> systs_aux = GetSys();
  for (unsigned int iAux=0; iAux<systs_aux.size(); ++iAux) {
    if (systs_aux[iAux] == "topPt") continue;
    systs.push_back(systs_aux[iAux]+"_up");
    systs.push_back(systs_aux[iAux]+"_down");
  }

  //retrieve histograms from all control regions
  vector<TH1F*> h[names.size()][vars.size()][Mth.size()];
  for (unsigned int j=0; j<names.size(); ++j) {
    for (unsigned int k=0; k<vars.size(); ++k) {
      for (unsigned int l=0; l<Mth.size(); ++l) {
	for (unsigned int m=0; m<systs.size(); ++m) {

          if (l < k_low_TT && k >= n_TT_plots) continue;

	  h[j][k][l].push_back( (TH1F*) file_in->Get(systs[m]+"/"+names[j]+vars[k]+"_realtau_"+systs[m]+"_"+Mth[l]) );
	  h[j][k][l][m]->SetName(names[j]+vars[k]+"_"+systs[m]+"_"+Mth[l]);
	}
      }
    }
  }


  file_out->cd();
  for (unsigned int k=0; k<vars.size(); ++k) {
    for (unsigned int l=0; l<Mth.size(); ++l) {
      for (unsigned int m=0; m<systs.size(); ++m) {

	if (l < k_low_TT && k >= n_TT_plots) continue;

	TH1F* h_faketau = (TH1F*) h[0][k][l][0]->Clone("faketau_"+systs[m]+"_"+vars[k]+"_"+Mth[l]);
	for (unsigned int j=1; j<names.size(); ++j) h_faketau->Add(h[j][k][l][m], -1);//subtract all real tau bg
	
	for (unsigned int iBin = 0; iBin<h_faketau->GetNbinsX(); ++iBin) {
	  if (h_faketau->GetBinContent(iBin) < 0) h_faketau->SetBinContent(iBin,0);
	}
	h_faketau->Write();
	delete h_faketau;
	for (unsigned int j=1; j<names.size(); ++j) delete h[j][k][l][m];
      }
    }
  }
  file_out->Close();


  return 0;
}
