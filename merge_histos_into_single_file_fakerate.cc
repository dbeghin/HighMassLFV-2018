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


using namespace std;


TH1F* MC_histo(TString var, TFile* file_in, TFile* file_in_d, double xs, int rebin) {

  cout << file_in->GetName() << endl;

  TH1F* h_events_data = (TH1F*) file_in_d->Get("weighted_events");
  double full_data = 7.3968038e+08;
  double succ_data_ratio = h_events_data->Integral()/full_data;
  cout << "succesfull data ratio " << succ_data_ratio << endl;
  double lumi = 41.529 * pow(10,3) * succ_data_ratio; //luminosity in pb^-1                                                                                                                                 

  TH1F* h_events = (TH1F*) file_in->Get("weighted_events");
  double Nevents = h_events->Integral();

  double e_Nevents = pow(Nevents,0.5);
  double e_xs = 0.01*xs;

  //Weight                                                                                                                                                                                                  
  double w = 0;
  if (Nevents != 0) w = xs*lumi/Nevents;
  cout << "Events in data/events in MC " << w << endl;

  TH1F* h = (TH1F*) file_in -> Get(var);

  h -> Scale(w);
  h -> Rebin(rebin);

  return h;

}


TH2F* MC_histo_TH2(TString var, TFile* file_in, TFile* file_in_d, double xs, int rebin) {

  cout << file_in->GetName() << endl;

  TH1F* h_events_data = (TH1F*) file_in_d->Get("weighted_events");
  double full_data = 7.3968038e+08;
  double succ_data_ratio = h_events_data->Integral()/full_data;
  cout << "succesfull data ratio " << succ_data_ratio << endl;
  double lumi = 41.529 * pow(10,3) * succ_data_ratio; //luminosity in pb^-1                                                                                                                                 

  TH1F* h_events = (TH1F*) file_in->Get("weighted_events");
  double Nevents = h_events->Integral();

  double e_Nevents = pow(Nevents,0.5);
  double e_xs = 0.01*xs;

  //Weight                                                                                                                                                                                                  
  double w = 0;
  if (Nevents != 0) w = xs*lumi/Nevents;
  cout << "Events in data/events in MC " << w << endl;

  TH2F* h = (TH2F*) file_in -> Get(var);

  h -> Scale(w);
  h -> RebinX(rebin);
  h -> RebinY(rebin);

  return h;

}



int main(int argc, char** argv) {


  int rebin = 1;

  TString folder_in = "HighMassLFVMuTau/FakeRate";
  //TString folder_in = "HighMassLFVMuTau/SignalRegion_CR100";
  TString name_out = "histos_fakerate_DY";

  TFile* file_out = new TFile("Figures/"+name_out+".root", "RECREATE");

  TFile* file_in_data = new TFile(folder_in+"/Arranged_data/data.root", "R");
  

  vector<TString> vars_TH2;
  vars_TH2.push_back("taupt_ratio_pass");
  vars_TH2.push_back("taupt_ratio_fail");

  vector<TString> dms;
  dms.push_back("DM0");
  dms.push_back("DM1");
  dms.push_back("DM10");

  vector<TString> eta;
  eta.push_back("barrel");
  eta.push_back("endcap");


  TString var_in, var_out;

  file_out->cd();
  for (unsigned int i = 0; i<vars_TH2.size(); ++i) {
    for (unsigned int j = 0; j<dms.size(); ++j) {
      for (unsigned int k = 0; k<eta.size(); ++k) {
	var_in = vars_TH2[i]+"_"+dms[j]+"_"+eta[k];
	var_out = var_in;
	    
	cout << endl << endl <<var_in << endl;
	    
	TH2F* h_data = (TH2F*) file_in_data -> Get(var_in);//Data is, by definition, normalized
	h_data -> SetName("data_"+var_out);
	h_data->RebinX(rebin);
	h_data->RebinY(rebin);
	h_data->Write();
	delete h_data;
      }
    }
  }
  file_out->Close();


  return 0;
}
