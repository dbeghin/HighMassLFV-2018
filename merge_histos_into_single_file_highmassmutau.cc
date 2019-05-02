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
  //TFile* file_in_DY_400to500 = new TFile(folder_in+"/Arranged_DY/DY_400to500.root", "R");            DY_files.push_back(file_in_DY_400to500);
  //TFile* file_in_DY_500to700 = new TFile(folder_in+"/Arranged_DY/DY_500to700.root", "R");	     DY_files.push_back(file_in_DY_500to700);
  //TFile* file_in_DY_700to800 = new TFile(folder_in+"/Arranged_DY/DY_700to800.root", "R");	     DY_files.push_back(file_in_DY_700to800);
  //TFile* file_in_DY_800to1000 = new TFile(folder_in+"/Arranged_DY/DY_800to1000.root", "R");	     DY_files.push_back(file_in_DY_800to1000);
  //TFile* file_in_DY_1000to1500 = new TFile(folder_in+"/Arranged_DY/DY_1000to1500.root", "R");	     DY_files.push_back(file_in_DY_1000to1500);
  //TFile* file_in_DY_1500to2000 = new TFile(folder_in+"/Arranged_DY/DY_1500to2000.root", "R");	     DY_files.push_back(file_in_DY_1500to2000);
  //TFile* file_in_DY_2000to3000 = new TFile(folder_in+"/Arranged_DY/DY_2000to3000.root", "R");        DY_files.push_back(file_in_DY_2000to3000);

  TFile* file_in_faketau;
  if (CR == "CR100") {
    file_in_faketau = new TFile("HighMassLFVMuTau/Faketaus_CR0.root", "R");
  }
  else if (CR == "CR102") {
    file_in_faketau = new TFile("HighMassLFVMuTau/Faketaus_CR102.root", "R");
  }


  TFile* file_in_WJets = new TFile(folder_in+"/Arranged_WJets/WJets.root", "R");
  vector<TFile*> WJets_files;
  TFile* file_in_WJets_lowpt = new TFile(folder_in+"/Arranged_WJets/WJets_inclusive.root", "R");     WJets_files.push_back(file_in_WJets_lowpt);
  TFile* file_in_WJets_100to250 = new TFile(folder_in+"/Arranged_WJets/WJets_100to250.root", "R");   WJets_files.push_back(file_in_WJets_100to250);
  TFile* file_in_WJets_250to400 = new TFile(folder_in+"/Arranged_WJets/WJets_250to400.root", "R");   WJets_files.push_back(file_in_WJets_250to400);
  TFile* file_in_WJets_400to600 = new TFile(folder_in+"/Arranged_WJets/WJets_400to600.root", "R");   WJets_files.push_back(file_in_WJets_400to600);
  TFile* file_in_WJets_600toInf = new TFile(folder_in+"/Arranged_WJets/WJets_600toInf.root", "R");   WJets_files.push_back(file_in_WJets_600toInf);

  vector<TFile*> TT_files;
  TT_files.push_back( new TFile(folder_in+"/Arranged_TT/TT_semilep.root", "R") ); //semilep
  TT_files.push_back( new TFile(folder_in+"/Arranged_TT/TT_had.root", "R") ); //had
  TT_files.push_back( new TFile(folder_in+"/Arranged_TT/TT_2l2nu.root", "R") ); //2l2nu

  vector<TFile*> WW_files;
  TFile* file_in_WW_lowmll = new TFile(folder_in+"/Arranged_WW/WW.root", "R");             WW_files.push_back(file_in_WW_lowmll);
  //TFile* file_in_WW_200to600 = new TFile(folder_in+"/Arranged_WW/WW_200to600.root", "R");	     WW_files.push_back(file_in_WW_200to600);
  //TFile* file_in_WW_600to1200 = new TFile(folder_in+"/Arranged_WW/WW_600to1200.root", "R");	     WW_files.push_back(file_in_WW_600to1200);
  //TFile* file_in_WW_1200to2500 = new TFile(folder_in+"/Arranged_WW/WW_1200to2500.root", "R");	     WW_files.push_back(file_in_WW_1200to2500);
  //TFile* file_in_WW_2500toInf = new TFile(folder_in+"/Arranged_WW/WW_2500toInf.root", "R");          WW_files.push_back(file_in_WW_2500toInf);

  TFile* file_in_WZ = new TFile(folder_in+"/Arranged_WZ/WZ.root", "R");
  TFile* file_in_ZZ = new TFile(folder_in+"/Arranged_ZZ/ZZ.root", "R");

  //TFile* file_in_ST_top = new TFile(folder_in+"/Arranged_ST_top/ST_top.root", "R");
  //TFile* file_in_ST_antitop = new TFile(folder_in+"/Arranged_ST_antitop/ST_antitop.root", "R");


  TFile* file_in_signal = new TFile(folder_in+"/Arranged_RPV/RPV.root", "R");
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
  //if (CR == "CR7") vars.push_back("ev_Mt"); 
  //if (CR == "CR9") vars.push_back("ev_Mt"); 


  vector<TString> taun;
  taun.push_back("realtau");
  if (CR!="CR100") taun.push_back("faketau");

  vector<TString> Mth;
  Mth.push_back("MtLow_OS");
  Mth.push_back("MtLow_SS");
  Mth.push_back("MtLow_TT");
  Mth.push_back("MtHigh");
  Mth.push_back("MtHigh_TT");


  //cross-sections
  vector<double> xs_DY;
  double xs_DY_lowmass = 6225.42;          xs_DY.push_back(xs_DY_lowmass);   
  //double xs_DY_400to500 = 0.4064;	   xs_DY.push_back(xs_DY_400to500);  
  //double xs_DY_500to700 = 0.241;	   xs_DY.push_back(xs_DY_500to700);  
  //double xs_DY_700to800 = 0.03606;	   xs_DY.push_back(xs_DY_700to800);  
  //double xs_DY_800to1000 = 0.03032;	   xs_DY.push_back(xs_DY_800to1000); 
  //double xs_DY_1000to1500 = 0.01924;	   xs_DY.push_back(xs_DY_1000to1500);
  //double xs_DY_1500to2000 = 0.002181;	   xs_DY.push_back(xs_DY_1500to2000);
  //double xs_DY_2000to3000 = 0.0005129;     xs_DY.push_back(xs_DY_2000to3000);

  vector<double> xs_WJets;
  double xs_WJets_lowpt = 61526.7;         xs_WJets.push_back(xs_WJets_lowpt);	 
  double xs_WJets_100to250 = 627.1;        xs_WJets.push_back(xs_WJets_100to250);
  double xs_WJets_250to400 = 21.8;	   xs_WJets.push_back(xs_WJets_250to400);
  double xs_WJets_400to600 = 2.635;	   xs_WJets.push_back(xs_WJets_400to600);
  double xs_WJets_600toInf = 0.4102;       xs_WJets.push_back(xs_WJets_600toInf);


  vector<double> xs_TT;
  xs_TT.push_back(831.76*0.438); //semilep
  xs_TT.push_back(831.76*0.457); //had
  xs_TT.push_back(831.76*0.105); //2l2nu  


  vector<double> xs_WW;
  double xs_WW_lowm = 64.3;       xs_WW.push_back(xs_WW_lowm);
  //double xs_WW_200to600 = 1.39;              xs_WW.push_back(xs_WW_200to600); 
  //double xs_WW_600to1200 = 5.7e-2;	     xs_WW.push_back(xs_WW_600to1200); 
  //double xs_WW_1200to2500 = 3.6e-3;	     xs_WW.push_back(xs_WW_1200to2500); 
  //double xs_WW_2500toInf = 5.4e-5;           xs_WW.push_back(xs_WW_2500toInf); 

  double xs_ST = 38.09;
  double xs_WZ = 22.82;
  double xs_ZZ = 10.32;
  double xs_signal = 20;

  //Nevents
  vector<double> N_DY;  
  double N_DY_lowmass = 100114403;            N_DY.push_back(N_DY_lowmass);   
  //double N_DY_400to500 = 151168;	      N_DY.push_back(N_DY_400to500);  
  //double N_DY_500to700 = 144087;	      N_DY.push_back(N_DY_500to700);  
  //double N_DY_700to800 = 136874;	      N_DY.push_back(N_DY_700to800);  
  //double N_DY_800to1000 = 131568;	      N_DY.push_back(N_DY_800to1000); 
  //double N_DY_1000to1500 = 119990;	      N_DY.push_back(N_DY_1000to1500);
  //double N_DY_1500to2000 = 111668;	      N_DY.push_back(N_DY_1500to2000);
  //double N_DY_2000to3000 = 101266;	      N_DY.push_back(N_DY_2000to3000);



  vector<double> N_TT;
  N_TT.push_back(100728756); //semilep
  N_TT.push_back(132566902); //had
  N_TT.push_back(63751842); //2l2nu

  vector<double> N_WW;
  double N_WW_lowm = 7850000;                N_WW.push_back(N_WW_lowm);
  //double N_WW_200to600 = 199991;             N_WW.push_back(N_WW_200to600); 
  //double N_WW_600to1200 = 74997;             N_WW.push_back(N_WW_600to1200); 
  //double N_WW_1200to2500 = 99992;            N_WW.push_back(N_WW_1200to2500); 
  //double N_WW_2500toInf = 13968;             N_WW.push_back(N_WW_2500toInf); 

  double N_ST_top = 3256548;
  double N_ST_antitop = 3256309;

  double N_WZ = 3885000;
  double N_ZZ = 1979000;


  double N_signal = 14994;
  TString var_in, var_out;

  file_out->cd();
  //options = is it the DY Sig?, variable name, which file to get the histo from, process cross-section
  for (unsigned int i = 0; i<vars.size(); ++i) {
    for (unsigned int j = 0; j<taun.size(); ++j) {
      for (unsigned int k = 0; k<Mth.size(); ++k) {

        var_in = vars[i]+"_"+taun[j]+"_"+Mth[k];
	if (CR == "CR100") {
	  var_out = vars[i]+"_"+Mth[k];
	}
	else {
	  var_out = var_in;
	}
        
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
        
        vector<TH1F*> h_TT_vector;
        for (unsigned int iBin = 0; iBin<TT_files.size(); ++iBin) {
          h_TT_vector.push_back( MC_histo(var_in, TT_files[iBin], file_in_data, xs_TT[iBin], rebin) ); 
        }
        TH1F* h_TT = (TH1F*) h_TT_vector[0]->Clone("TT_"+var_out);
        for (unsigned int iBin = 1; iBin<h_TT_vector.size(); ++iBin) {
          h_TT->Add(h_TT_vector[iBin]);
        }
        h_TT->Write();
        
          
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
        //h_VV -> SetName("VV_"+var_in);
        h_VV->Write();
        
        //TH1F* h_ST_top = MC_histo(var_in, file_in_ST_top, xs_ST, N_ST_top, rebin);
        //TH1F* h_ST_antitop = MC_histo(var_in, file_in_ST_antitop, xs_ST, N_ST_antitop, rebin);
        //TH1F* h_ST = (TH1F*) h_ST_top->Clone("ST_"+var_out);
        //h_ST->Add(h_ST_antitop);
        //h_ST->Write();
	
	if (CR != "CR101") {
	  //TH1F* h_signal = MC_histo(var_in, file_in_signal, xs_signal, N_signal, rebin);
	  //h_signal->SetName("Signal_"+var_out);
	  //h_signal->Write();
	  //FIXME
	}
        
        TH1F* h_data = (TH1F*) file_in_data -> Get(var_in);//Data is, by definition, normalized
        h_data -> SetName("data_"+var_out);
        h_data->Rebin(rebin);
        h_data->Write();
      }
    }
    if ((CR == "CR100") || (CR == "CR102")) {
      for (unsigned int k = 0; k<Mth.size(); ++k) {
      	cout << file_in_faketau->GetName() << endl;
      	TH1F* h_faketaus = (TH1F*) file_in_faketau -> Get("faketau_"+vars[i]+"_"+Mth[k]);
      	//h_faketaus->Rebin(rebin);
      	h_faketaus->Write();
      }
    }
  }
  file_out->Close();


  return 0;
}
