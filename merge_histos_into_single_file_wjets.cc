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
#include "TDirectory.h"


using namespace std;


TH1F* MC_histo(TString var, TFile* file_in, double xs, int rebin) {

  cout << file_in->GetName() << endl;

  double succ_data_ratio = 1;
  cout << "succesfull data ratio " << succ_data_ratio << endl;
  double lumi = 35.9 * pow(10,3) * succ_data_ratio; //luminosity in pb^-1

  TH1F* h_events = (TH1F*) file_in->Get("weighted_events");
  double Nevents = h_events->Integral();

  double e_Nevents = pow(Nevents,0.5);
  double e_xs = 0.01*xs;

  //Weight
  double w = 0;
  if (Nevents != 0) w = xs*lumi/Nevents;
  cout << "xs: " << xs << "  Nevents: " << Nevents << endl;
  cout << "Events in data/events in MC " << w << endl;
  
  TH1F* h;
  h = (TH1F*) file_in -> Get(var);

  h -> Scale(w);
  h -> Rebin(rebin);
  
  return h;

}



int main(int argc, char** argv) {


  //string CR = *(argv + 1);

  TString folder_in = "HighMassLFVMuTau/WJetsControl_";
  TString name_out = "";
  name_out = "histos_wjets";
  //name_out = "histos_wjets_OS";
  //name_out = "histos_wjets_SS";

  TFile* file_out = new TFile("Figures/"+name_out+".root", "RECREATE");

  vector<TFile*> WJets_files_CR100;
  TFile* file_in_WJets_CR100_lowpt = new TFile(folder_in+"CR100/Arranged_WJets/WJets_inclusive.root", "R");     WJets_files_CR100.push_back(file_in_WJets_CR100_lowpt);
  TFile* file_in_WJets_CR100_50to100 = new TFile(folder_in+"CR100/Arranged_WJets/WJets_50to100.root", "R");     WJets_files_CR100.push_back(file_in_WJets_CR100_50to100);
  TFile* file_in_WJets_CR100_100to250 = new TFile(folder_in+"CR100/Arranged_WJets/WJets_100to250.root", "R");   WJets_files_CR100.push_back(file_in_WJets_CR100_100to250);
  //TFile* file_in_WJets_CR100_250to400 = new TFile(folder_in+"CR100/Arranged_WJets/WJets_250to400.root", "R");   WJets_files_CR100.push_back(file_in_WJets_CR100_250to400);
  TFile* file_in_WJets_CR100_400to600 = new TFile(folder_in+"CR100/Arranged_WJets/WJets_400to600.root", "R");   WJets_files_CR100.push_back(file_in_WJets_CR100_400to600);
  TFile* file_in_WJets_CR100_600toInf = new TFile(folder_in+"CR100/Arranged_WJets/WJets_600toInf.root", "R");   WJets_files_CR100.push_back(file_in_WJets_CR100_600toInf);


  vector<TFile*> WJets_files_CR101;
  TFile* file_in_WJets_CR101_lowpt = new TFile(folder_in+"CR101/Arranged_WJets/WJets_inclusive.root", "R");     WJets_files_CR101.push_back(file_in_WJets_CR101_lowpt);
  TFile* file_in_WJets_CR101_50to100 = new TFile(folder_in+"CR101/Arranged_WJets/WJets_50to100.root", "R");     WJets_files_CR101.push_back(file_in_WJets_CR101_50to100);
  TFile* file_in_WJets_CR101_100to250 = new TFile(folder_in+"CR101/Arranged_WJets/WJets_100to250.root", "R");   WJets_files_CR101.push_back(file_in_WJets_CR101_100to250);
  //TFile* file_in_WJets_CR101_250to400 = new TFile(folder_in+"CR101/Arranged_WJets/WJets_250to400.root", "R");   WJets_files_CR101.push_back(file_in_WJets_CR101_250to400);
  TFile* file_in_WJets_CR101_400to600 = new TFile(folder_in+"CR101/Arranged_WJets/WJets_400to600.root", "R");   WJets_files_CR101.push_back(file_in_WJets_CR101_400to600);
  TFile* file_in_WJets_CR101_600toInf = new TFile(folder_in+"CR101/Arranged_WJets/WJets_600toInf.root", "R");   WJets_files_CR101.push_back(file_in_WJets_CR101_600toInf);

  

  vector<TString> vars;                vector<int> rebin;  
  vars.push_back("ev_Mvis");           rebin.push_back(25); 
  vars.push_back("ev_Mtot");           rebin.push_back(25); 
  vars.push_back("tau_pt");            rebin.push_back(25); 
  vars.push_back("tau_eta");           rebin.push_back(5); 
  vars.push_back("tau_phi");           rebin.push_back(5); 
  vars.push_back("mu_pt");             rebin.push_back(25); 
  vars.push_back("mu_eta");            rebin.push_back(5); 
  vars.push_back("mu_phi");            rebin.push_back(5); 
  vars.push_back("mu_isolation");      rebin.push_back(5); 
  vars.push_back("ev_DRmutau");        rebin.push_back(5); 
  vars.push_back("ev_MET");            rebin.push_back(25); 
  vars.push_back("ev_Mcol");           rebin.push_back(50); 
  vars.push_back("ev_Mt");             rebin.push_back(25); 
  vars.push_back("sign");              rebin.push_back(1);
  //vars.push_back("weight");            rebin.push_back(10);

  vector<TString> taun;
  taun.push_back("realtau");

  vector<TString> systs;              
  systs.push_back("nominal");


  vector<double> xs_wjets;
  xs_wjets.push_back(60430);
  xs_wjets.push_back(3046.0);
  xs_wjets.push_back(627.1);
  //xs_wjets.push_back(21.83);
  xs_wjets.push_back(2.635);
  xs_wjets.push_back(0.4102);

  TString var_in, var_out;

  file_out->cd();
  //options = is it the DY Sig?, variable name, which file to get the histo from, process cross-section
  for (unsigned int k = 0; k<systs.size(); ++k) {
    TDirectory* dir = file_out->mkdir( systs[k] );
    dir->cd();
    for (unsigned int i = 0; i<vars.size(); ++i) {
      for (unsigned int j = 0; j<taun.size(); ++j) {

	var_in = systs[k]+"/"+vars[i]+"_"+taun[j]+"_"+systs[k];
	var_out = vars[i];
	cout << endl << endl <<var_in << endl;
          
          
	vector<TH1F*> h_WJets_CR100;
	for (unsigned int iFile=0; iFile<WJets_files_CR100.size(); ++iFile) {
	  h_WJets_CR100.push_back( MC_histo(var_in+"_MtLow_OS", WJets_files_CR100[iFile], xs_wjets[iFile], rebin[i]) );
	  //h_WJets_CR100.push_back( MC_histo(var_in+"_MtLow_SS", WJets_files_CR100[iFile], xs_wjets[iFile], rebin[i]) );
	  TH1F* htemp = MC_histo(var_in+"_MtLow_SS", WJets_files_CR100[iFile], xs_wjets[iFile], rebin[i]);
	  //TH1F* htemp2 = MC_histo(var_in+"_MtHigh", WJets_files_CR100[iFile], xs_wjets[iFile], rebin[i]);
	  h_WJets_CR100[iFile]->Add(htemp);
	  //h_WJets_CR100[iFile]->Add(htemp2);
	  delete htemp;
	  //delete htemp2;
	}
	TH1F* h_WJets_tot_CR100 = (TH1F*) h_WJets_CR100[0]->Clone("WJets_signalregion_"+var_out);
	for (unsigned int iFile=1; iFile<WJets_files_CR100.size(); ++iFile) h_WJets_tot_CR100->Add(h_WJets_CR100[iFile]);
	for (unsigned int iBin=1; iBin<h_WJets_tot_CR100->GetNbinsX()+1; ++iBin) {
	  float bin_content = h_WJets_tot_CR100->GetBinContent(iBin);
	  if (bin_content < 0) h_WJets_tot_CR100->SetBinContent(iBin, 0);
	}
	double integral = h_WJets_tot_CR100->Integral();
	//h_WJets_tot_CR100->Scale(1./integral);
	h_WJets_tot_CR100->Write();
	delete h_WJets_tot_CR100;
	for (unsigned int iFile=0; iFile<WJets_files_CR100.size(); ++iFile) delete h_WJets_CR100[iFile];


	vector<TH1F*> h_WJets_CR101;
	for (unsigned int iFile=0; iFile<WJets_files_CR101.size(); ++iFile) {
	  h_WJets_CR101.push_back( MC_histo(var_in+"_MtLow_OS", WJets_files_CR101[iFile], xs_wjets[iFile], rebin[i]) );
	  //h_WJets_CR101.push_back( MC_histo(var_in+"_MtLow_SS", WJets_files_CR101[iFile], xs_wjets[iFile], rebin[i]) );
	  TH1F* htemp = MC_histo(var_in+"_MtLow_SS", WJets_files_CR101[iFile], xs_wjets[iFile], rebin[i]);
	  //TH1F* htemp2 = MC_histo(var_in+"_MtHigh", WJets_files_CR101[iFile], xs_wjets[iFile], rebin[i]);
	  h_WJets_CR101[iFile]->Add(htemp);
	  //h_WJets_CR101[iFile]->Add(htemp2);
	  delete htemp;
	  //delete htemp2;
	}
	TH1F* h_WJets_tot_CR101 = (TH1F*) h_WJets_CR101[0]->Clone("WJets_fakerate_"+var_out);
	for (unsigned int iFile=1; iFile<WJets_files_CR101.size(); ++iFile) h_WJets_tot_CR101->Add(h_WJets_CR101[iFile]);
	for (unsigned int iBin=1; iBin<h_WJets_tot_CR101->GetNbinsX()+1; ++iBin) {
	  float bin_content = h_WJets_tot_CR101->GetBinContent(iBin);
	  if (bin_content < 0) h_WJets_tot_CR101->SetBinContent(iBin, 0);
	}
	h_WJets_tot_CR101->Write();
	delete h_WJets_tot_CR101;
	for (unsigned int iFile=0; iFile<WJets_files_CR101.size(); ++iFile) delete h_WJets_CR101[iFile];
	  
      }
    }
    dir->Close();
  }
  cout << "almost" << endl;
  file_out->Close();
  cout << "done" << endl;


  return 0;
}
