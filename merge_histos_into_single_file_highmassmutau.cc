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
#include "TDirectory.h"
#include "aux.h"

using namespace std;


TH1F* MC_histo(TString var, TFile* file_in, TFile* file_in_d, double xs, int rebin) {

  cout << file_in->GetName() << endl;

  TH1F* h_events_data = (TH1F*) file_in_d->Get("weighted_events");
  double full_data = 9.3766734e+08;
  double succ_data_ratio = h_events_data->Integral()/full_data;
  cout << "succesfull data ratio " << succ_data_ratio << endl;
  double lumi = 58.36 * pow(10,3) * succ_data_ratio; //luminosity in pb^-1

  TH1F* h_events = (TH1F*) file_in->Get("weighted_events");
  double Nevents = h_events->Integral();

  double e_Nevents = pow(Nevents,0.5);
  double e_xs = 0.01*xs;

  //Weight
  double w = 0;
  if (Nevents != 0) w = xs*lumi/Nevents;
  cout << "Events in data/events in MC " << w << endl;
  
  TH1F* h;
  h = (TH1F*) file_in -> Get(var);

  h -> Scale(w);
  h -> Rebin(rebin);
  
  return h;

}



int main(int argc, char** argv) {


  int rebin = 1;
  string CR = *(argv + 1);

  TString folder_in = "";
  TString name_out = "";
  if (CR == "CR0" || CR == "CR00") {
    folder_in = "HighMassLFVMuTau/OSisomuisotau_CR0"; 
  }
  else if (CR == "CR1") {
    folder_in = "HighMassLFVMuTau/SSisomuisotau_CR1"; 
  }
  else if (CR == "CR2") {
    folder_in = "HighMassLFVMuTau/OSisomuantitau_CR2"; 
  }
  else if (CR == "CR3") {
    folder_in = "HighMassLFVMuTau/SSisomuantitau_CR3"; 
  }
  else if (CR == "CR4") {
    folder_in = "HighMassLFVMuTau/OSantimuantitau_CR4"; 
  }
  else if (CR == "CR5") {
    folder_in = "HighMassLFVMuTau/SSantimuantitau_CR5";
  }
  else if (CR == "CR7") {
    folder_in = "HighMassLFVMuTau/Wjets_CR7";
  }
  else if (CR == "CR9") {
    folder_in = "HighMassLFVMuTau/Wjets_CR9";
  }
  else if (CR == "CR100") {
    folder_in = "HighMassLFVMuTau/SignalRegion_CR100";
  }
  else if (CR == "CR101") {
    folder_in = "HighMassLFVMuTau/Faketaus_CR101";
  }
  else if (CR == "CR102") {
    folder_in = "HighMassLFVMuTau/WjetsTest_CR102";
  }
  else if (CR == "CR102b") {
    folder_in = "HighMassLFVMuTau/WjetsTest_CR102";
  }
  else if (CR == "CR103") {
    folder_in = "HighMassLFVMuTau/WjetsTest_CR103";
  }
  else if (CR == "prefake") {
    folder_in = "HighMassLFVMuTau/SignalRegion_CR100";
  }    
  else {
    cout << "unrecognised argument!!!" << endl;
  }
  name_out = "histos_highmassmutau_"+CR;

  TFile* file_out = new TFile("Figures/"+name_out+".root", "RECREATE");

  vector<TFile*> DY_files;
  TFile* file_in_DY_lowmass = new TFile(folder_in+"/Arranged_DY/DY.root", "R");            DY_files.push_back(file_in_DY_lowmass);

  TFile* file_in_faketau;
  if (CR == "CR100") {
    file_in_faketau = new TFile("HighMassLFVMuTau/Faketaus_CR0.root", "R");
  }
  else if (CR == "CR102") {
    file_in_faketau = new TFile("HighMassLFVMuTau/Faketaus_CR102.root", "R");
  }


  vector<TFile*> TT_files;
  TT_files.push_back( new TFile(folder_in+"/Arranged_TT/TT_semilep.root", "R") ); //semilep
  TT_files.push_back( new TFile(folder_in+"/Arranged_TT/TT_had.root", "R") ); //had
  TT_files.push_back( new TFile(folder_in+"/Arranged_TT/TT_2l2nu.root", "R") ); //2l2nu

  vector<TFile*> WW_files;
  TFile* file_in_WW_lowmll = new TFile(folder_in+"/Arranged_WW/WW.root", "R");             WW_files.push_back(file_in_WW_lowmll);

  TFile* file_in_WZ = new TFile(folder_in+"/Arranged_WZ/WZ.root", "R");
  TFile* file_in_ZZ = new TFile(folder_in+"/Arranged_ZZ/ZZ.root", "R");

  TFile* file_in_ST = new TFile(folder_in+"/Arranged_ST/ST.root", "R");


  TFile* file_in_data = new TFile(folder_in+"/Arranged_data/data.root", "R");
  

  vector<TString> vars;
  vars.push_back("ev_Mvis");          
  vars.push_back("ev_Mtot");          
  vars.push_back("tau_pt");           
  vars.push_back("tau_eta");          
  vars.push_back("tau_phi");          
  vars.push_back("mu_pt");            
  vars.push_back("mu_eta");           
  vars.push_back("mu_phi");           
  vars.push_back("ev_DRmutau");       
  vars.push_back("ev_Mt");        
  vars.push_back("ev_MET"); 
  vars.push_back("ev_Mcol"); 
  vars.push_back("mu_isolation"); 
  vars.push_back("sign"); 


  vector<TString> taun;
  taun.push_back("realtau");
  if (CR!="CR100") taun.push_back("faketau");

  vector<TString> Mth;
  Mth.push_back("MtLow_OS");
  Mth.push_back("MtLow_SS");
  Mth.push_back("MtLow_TT");
  Mth.push_back("MtHigh");
  Mth.push_back("MtHigh_TT");


  vector<TString> systs;
  systs.push_back("nominal");
  vector<TString> systs_aux = GetSys();
  for (unsigned int iAux=0; iAux<systs_aux.size(); ++iAux) {
    systs.push_back(systs_aux[iAux]+"_up");
    systs.push_back(systs_aux[iAux]+"_down");
  }


  //cross-sections
  vector<double> xs_DY;
  double xs_DY_lowmass = 6225.42;          xs_DY.push_back(xs_DY_lowmass);   


  vector<double> xs_TT;
  xs_TT.push_back(831.76*0.438); //semilep
  xs_TT.push_back(831.76*0.457); //had
  xs_TT.push_back(831.76*0.105); //2l2nu  


  vector<double> xs_WW;
  double xs_WW_lowm = 64.3;       xs_WW.push_back(xs_WW_lowm);

  double xs_ST = 38.09;
  double xs_WZ = 22.82;
  double xs_ZZ = 10.32;
  double xs_signal = 20;

  //Nevents
  vector<double> N_DY;  
  double N_DY_lowmass = 100114403;            N_DY.push_back(N_DY_lowmass);   


  TString var_in, var_out;

  file_out->cd();
  //options = is it the DY Sig?, variable name, which file to get the histo from, process cross-section
  for (unsigned int l = 0; l<systs.size(); ++l) {
    TDirectory* dir = file_out->mkdir( systs[l] );
    dir->cd();
    for (unsigned int i = 0; i<vars.size(); ++i) {
      for (unsigned int j = 0; j<taun.size(); ++j) {
        for (unsigned int k = 0; k<Mth.size(); ++k) {
    
          var_in = vars[i]+"_"+taun[j]+"_"+systs[l]+"_"+Mth[k];
	  if (CR == "CR100") {
	    var_out = vars[i]+"_"+Mth[k];
	  }
	  else {
	    var_out = var_in;
	  }
	  var_in = systs[l]+"/"+var_in;
          
          cout << endl << endl <<var_in << endl;
          
          vector<TH1F*> h_DY_vector;
          for (unsigned int iBin = 0; iBin<DY_files.size(); ++iBin) {
            h_DY_vector.push_back( MC_histo(var_in, DY_files[iBin], file_in_data, xs_DY[iBin], rebin) ); 
          }
          TH1F* h_DY = (TH1F*) h_DY_vector[0]->Clone("DY_"+var_out);
          for (unsigned int iBin = 1; iBin<DY_files.size(); ++iBin) {
    	  //if (iBin > 2) continue;
            h_DY->Add(h_DY_vector[iBin]);
          }
          h_DY->Write();
	  delete h_DY;
          for (unsigned int iBin = 0; iBin<DY_files.size(); ++iBin) delete h_DY_vector[iBin];
    
          vector<TH1F*> h_TT_vector;
          for (unsigned int iBin = 0; iBin<TT_files.size(); ++iBin) {
            h_TT_vector.push_back( MC_histo(var_in, TT_files[iBin], file_in_data, xs_TT[iBin], rebin) ); 
          }
          TH1F* h_TT = (TH1F*) h_TT_vector[0]->Clone("TT_"+var_out);
          for (unsigned int iBin = 1; iBin<h_TT_vector.size(); ++iBin) {
            h_TT->Add(h_TT_vector[iBin]);
          }
          h_TT->Write();
	  delete h_TT;
          for (unsigned int iBin = 0; iBin<TT_files.size(); ++iBin) delete h_TT_vector[iBin];
          
            
          vector<TH1F*> h_WW_vector;
          for (unsigned int iBin = 0; iBin<WW_files.size(); ++iBin) {
    	  //if (iBin > 0) break;
            h_WW_vector.push_back( MC_histo(var_in, WW_files[iBin], file_in_data, xs_WW[iBin], rebin) ); 
          }
          TH1F* h_WW = (TH1F*) h_WW_vector[0]->Clone("WW_"+var_out);
          for (unsigned int iBin = 1; iBin<h_WW_vector.size(); ++iBin) {
            h_WW->Add(h_WW_vector[iBin]);
          }
          
            
          TH1F* h_WZ = MC_histo(var_in, file_in_WZ, file_in_data, xs_WZ, rebin);
          TH1F* h_ZZ = MC_histo(var_in, file_in_ZZ, file_in_data, xs_ZZ, rebin);
          TH1F* h_VV = (TH1F*) h_WW->Clone("VV_"+var_out);
          h_VV->Add(h_WZ);
          h_VV->Add(h_ZZ);
          h_VV->Write();
	  delete h_VV;
	  delete h_WW;
	  delete h_WZ;
	  delete h_ZZ;
          for (unsigned int iBin = 0; iBin<WW_files.size(); ++iBin) delete h_WW_vector[iBin];
          
    
          TH1F* h_ST = MC_histo(var_in, file_in_ST, file_in_data, xs_ST, rebin);
	  h_ST->SetName("ST_"+var_out);
	  h_ST->Write();
	  delete h_ST;
    	
          
          TH1F* h_data = (TH1F*) file_in_data -> Get(var_in);//Data is, by definition, normalized
          h_data -> SetName("data_"+var_out);
          h_data->Rebin(rebin);
          h_data->Write();
	  delete h_data;
        }
      }
      if ((CR == "CR100") || (CR == "CR102")) {
        for (unsigned int k = 0; k<Mth.size(); ++k) {
	  cout << file_in_faketau->GetName() << endl;
	  TH1F* h_faketaus = (TH1F*) file_in_faketau -> Get("faketau_"+vars[i]+"_"+Mth[k]);
	  //h_faketaus->Rebin(rebin);
	  h_faketaus->Write();
	  delete h_faketaus;
        }
      }
    }
  }
  file_out->Close();


  return 0;
}
