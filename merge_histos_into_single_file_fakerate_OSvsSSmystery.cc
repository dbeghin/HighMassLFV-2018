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
#include "TH3.h"

using namespace std;


TH3D* MC_histo_TH3(TString var, TFile* file_in, double xs, int rebin) {
  cout << file_in->GetName() << endl;

  double succ_data_ratio = 1;
  cout << "succesfull data ratio " << succ_data_ratio << endl;

  double lumi = 35.9 * pow(10,3) * succ_data_ratio; //luminosity in pb^-1

  TH1F* h_events = (TH1F*) file_in->Get("weighted_events");
  double Nevents = h_events->Integral();
  delete h_events;

  double e_Nevents = pow(Nevents,0.5);
  double e_xs = 0.01*xs;

  //Weight
  double w = 0;
  if (Nevents != 0) w = xs*lumi/Nevents;
  cout << "Events in data/events in MC " << w << endl;
  
  TH3D* h;
  h = (TH3D*) file_in -> Get(var);

  h -> Scale(w);
  h -> RebinX(rebin);
  h -> RebinY(rebin);
  
  return h;
}



int main(int argc, char** argv) {


  int rebin = 1;

  TString folder_in = "HighMassLFVMuTau/OSvsSSmystery";
  TString name_out = "";
  name_out = "histos_fakerate_OSvsSSmystery";

  TFile* file_out = new TFile("Figures/"+name_out+".root", "RECREATE");


  vector<TFile*> WJets_files;
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_inclusive.root", "R") );  
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_50to100.root", "R") );   
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_100to250.root", "R") );   
  //WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_250to400.root", "R") );   
  //WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_400to600.root", "R") );   
  WJets_files.push_back( new TFile(folder_in+"/Arranged_WJets/WJets_600toInf.root", "R") );   

  

  vector<TString> Mth;
  Mth.push_back("MtLow_OS");
  Mth.push_back("MtLow_SS");

  vector<TString> systs;
  systs.push_back("nominal");


  vector<TString> flavor;
  flavor.push_back("down");    
  flavor.push_back("up");      
  flavor.push_back("strange"); 
  flavor.push_back("charm");   
  flavor.push_back("bottom");  
  flavor.push_back("gluon");


  vector<TString> DM;
  DM.push_back("DM0");
  DM.push_back("DM1");
  DM.push_back("DM10");


  vector<TString> h_names;
  h_names.push_back("tauPt_chHadFrac_neutHadFrac_pass");
  h_names.push_back("taupt_chHadFrac_neutHadFrac_fail");
  h_names.push_back("chEmFrac_muonFrac_neutEmFrac_pass");
  h_names.push_back("chEmFrac_muonFrac_neutEmFrac_fail");


  vector<TString> muonCharge;
  muonCharge.push_back("MuPlus"); 
  muonCharge.push_back("MuMinus");

  vector<TString> eta;
  eta.push_back("barrel");
  eta.push_back("endcap");

  //cross-sections
  vector<double> xs_WJets;
  xs_WJets.push_back(60430);
  xs_WJets.push_back(3046.0);
  xs_WJets.push_back(627.1);
  //xs_WJets.push_back(21.83);
  //xs_WJets.push_back(2.635);
  xs_WJets.push_back(0.4102);

  TString var_in, var_out;

  file_out->cd();
  for (unsigned int i = 0; i<h_names.size(); ++i) {
    for (unsigned int m = 0; m<Mth.size(); ++m) {
      for (unsigned int j = 0; j<systs.size(); ++j) {
	for (unsigned int dd = 0; dd<flavor.size(); ++dd) {
	  for (unsigned int k = 0; k<eta.size(); ++k) {
	    for (unsigned int nn = 0; nn<muonCharge.size(); ++nn) {
	      for (unsigned int l = 0; l<DM.size(); ++l) {
		var_in = h_names[i]+"_"+systs[j]+"_"+Mth[m]+"_"+eta[k]+"_"+flavor[dd]+"_"+DM[l]+"_"+muonCharge[nn];
		var_out = var_in;
	    
		cout << endl << endl <<var_in << endl;
            
		vector<TH3D*> h_WJets_vector;
		for (unsigned int iBin = 0; iBin<WJets_files.size(); ++iBin) {
		  h_WJets_vector.push_back( MC_histo_TH3(systs[j]+"/"+var_in, WJets_files[iBin], xs_WJets[iBin], rebin) ); 
		}
		TH3D* h_WJets = (TH3D*) h_WJets_vector[0]->Clone("WJets_"+var_out);
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
      }
    }
  }
  file_out->Close();


  return 0;
}
