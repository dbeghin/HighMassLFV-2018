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
#include "aux.h"
#include "TDirectory.h"

using namespace std;


TH2D* MC_histo_TH2(TString var, TFile* file_in, double xs, int rebin) {
  cout << file_in->GetName() << endl;

  double succ_data_ratio = 1;
  cout << "succesfull data ratio " << succ_data_ratio << endl;

  double lumi = 59.74 * pow(10,3) * succ_data_ratio; //luminosity in pb^-1

  TH1F* h_events = (TH1F*) file_in->Get("weighted_events");
  double Nevents = h_events->Integral();
  delete h_events;

  double e_Nevents = pow(Nevents,0.5);
  double e_xs = 0.01*xs;

  //Weight
  double w = 0;
  if (Nevents != 0) w = xs*lumi/Nevents;
  cout << "Events in data/events in MC " << w << endl;
  
  TH2D* h;
  h = (TH2D*) file_in -> Get(var);

  h -> Scale(w);
  h -> RebinX(rebin);
  h -> RebinY(rebin);
  
  return h;
}



int main(int argc, char** argv) {


  int rebin = 1;

  TString folder_in = "HighMassLFVMuTau/WJetsControl_CR100";
  TString name_out = "";
  name_out = "histos_fakerate_wjets";

  TFile* file_out = new TFile("Figures/"+name_out+".root", "RECREATE");


  vector<TFile*> WJets_files;
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_inclusive.root", "R") );  
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_50to100.root", "R") );   
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_100to250.root", "R") );   
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_400to600.root", "R") );   
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_600toInf.root", "R") );   

  
  vector<TString> deepTauIDs;
  deepTauIDs.push_back("VVL");
  deepTauIDs.push_back("VL");
  deepTauIDs.push_back("L");
  deepTauIDs.push_back("M");
  deepTauIDs.push_back("T");
  deepTauIDs.push_back("VT");
  deepTauIDs.push_back("VVT");

  vector<TString> vars_TH2;
  for (unsigned int iDeep = 0; iDeep<deepTauIDs.size(); ++iDeep) {
    vars_TH2.push_back("taupt_ratio_DeepTau"+deepTauIDs[iDeep]+"_fail");
    vars_TH2.push_back("taupt_ratio_DeepTau"+deepTauIDs[iDeep]+"_pass");
  }
  vars_TH2.push_back("taupt_ratio_MVATau_pass");
  vars_TH2.push_back("taupt_ratio_MVATau_fail");


  vector<TString> Mth;
  Mth.push_back("MtLow_OS");
  Mth.push_back("MtLow_SS");

  vector<TString> systs;
  systs.push_back("nominal");


  vector<TString> eta;
  eta.push_back("barrel");
  eta.push_back("endcap");


  //cross-sections
  vector<double> xs_WJets;
  xs_WJets.push_back(60430);  //incl
  xs_WJets.push_back(3046.0); //50to100
  xs_WJets.push_back(627.1);  //100to250
  xs_WJets.push_back(2.635);  //400to600
  xs_WJets.push_back(0.4102); //600toInf

  TString var_in, var_out;

  file_out->cd();
  for (unsigned int i = 0; i<vars_TH2.size(); ++i) {
    for (unsigned int m = 0; m<Mth.size(); ++m) {
      for (unsigned int j = 0; j<systs.size(); ++j) {
	for (unsigned int k = 0; k<eta.size(); ++k) {
	  var_in = vars_TH2[i]+"_"+systs[j]+"_"+Mth[m]+"_"+eta[k];
	  var_out = var_in;
	  var_in += "_realtau";
	    
	  cout << endl << endl <<var_in << endl;
            
	  vector<TH2D*> h_WJets_vector;
	  for (unsigned int iBin = 0; iBin<WJets_files.size(); ++iBin) {
	    h_WJets_vector.push_back( MC_histo_TH2(systs[j]+"/"+var_in, WJets_files[iBin], xs_WJets[iBin], rebin) ); 
	  }
	  TH2D* h_WJets = (TH2D*) h_WJets_vector[0]->Clone("WJets_"+var_out);
	  for (unsigned int iBin = 1; iBin<WJets_files.size(); ++iBin) {
	    h_WJets->Add(h_WJets_vector[iBin]);
	    delete h_WJets_vector[iBin];
	  }
	  delete h_WJets_vector[0];
	  h_WJets->Write();
	  delete h_WJets;
	}
      }
    }
  }
  file_out->Close();


  return 0;
}
