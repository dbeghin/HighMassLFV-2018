#define IIHEAnalysis_cxx
#include "IIHEAnalysis_2018.h"
#include "aux.h"
#include "PU_reWeighting.cc"
#include "TString.h"
#include <iostream>
#include <vector>
#include "meta.h"
#include "BTagCalibrationStandalone.cc"
#include "BTagCalibrationStandalone.h"

using namespace std;

int main(int argc, char** argv) {
  string out = *(argv + 1);
  string out_name= out;
  string in = *(argv + 2);
  string inname= in;
  string mc_in = *(argv + 3);
  string mc_nickname= mc_in;
  string phase_in = *(argv + 4);
  string phase= phase_in;
  string type_in = *(argv + 5);
  string type= type_in;
  TFile *fIn = TFile::Open(inname.c_str());
  TTree* tree = (TTree*) fIn->Get("IIHEAnalysis");


  TTree* mmeta = (TTree*) fIn->Get("meta");
  meta* m = new meta(mmeta);
  Float_t nEvents = m->Loop(type);


  IIHEAnalysis* a = new IIHEAnalysis(tree);
  a->Loop(phase, type, out_name, mc_nickname, nEvents);
  fIn->Close();
  return 0;
}



//Get weighted events
Float_t meta::Loop(string type_of_data) {
  if (fChain == 0) return -1;

  bool data;
  if (type_of_data == "Data" || type_of_data == "data" || type_of_data == "singlephoton" || type_of_data == "SinglePhoton" || type_of_data == "singlemu" || type_of_data == "SingleMu") {
    data = true;
  }
  else {
    data = false;
  }

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  Float_t nEvents = -1;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    
    if (data) {
      nEvents = nEventsRaw;
    }
    else {
      nEvents = mc_nEventsWeighted;
    }
  }
  return nEvents;
}



//main analysis loop
void IIHEAnalysis::Loop(string controlregion, string type_of_data, string out_name, string mc_nickname, Float_t nEvents) {
   if (fChain == 0) return;

   
   BTagCalibration calib("DeepCSV", "Reweighting/DeepCSV_102XSF_WP_V1.csv");
   BTagCalibrationReader reader(BTagEntry::OP_MEDIUM,  // operating point
				"central",             // central sys type
				{"up", "down"});      // other sys types
   reader.load(calib,                // calibration instance
	       BTagEntry::FLAV_B,    // btag flavour
	       "comb") ;              // measurement type
   reader.load(calib,                // calibration instance
	       BTagEntry::FLAV_C,    // btag flavour
	       "comb") ;              // measurement type
   reader.load(calib,                // calibration instance
	       BTagEntry::FLAV_UDSG,  // btag flavour
	       "incl") ; // measurement type


   bool Signal, data, singlephoton, singlemu, DYinc, WJetsinc, TTinc, WWinc, TT;
   if (type_of_data == "Signal" || type_of_data == "signal") {
     Signal = true;
     data = false;
     DYinc = false;
     WJetsinc = false;
     TTinc = false;
     TT = false;
     WWinc = false;
   }
   else if (type_of_data == "Data" || type_of_data == "data" || type_of_data == "singlephoton" || type_of_data == "SinglePhoton" || type_of_data == "singlemu" || type_of_data == "SingleMu") {
     Signal = false;
     data = true;
     DYinc = false;
     WJetsinc = false;
     TTinc = false;
     TT = false;
     WWinc = false;
   }
   else if (type_of_data == "DYinc") {
     Signal = false;
     data = false;
     DYinc = true;
     WJetsinc = false;
     TTinc = false;
     TT = false;
     WWinc = false;
   }
   else if (type_of_data == "WJetsinc") {
     Signal = false;
     data = false;
     DYinc = false;
     WJetsinc = true;
     TTinc = false;
     TT = false;
     WWinc = false;
   }
   else if (type_of_data == "TTinc") {
     Signal = false;
     data = false;
     DYinc = false;
     WJetsinc = false;
     TTinc = true;
     TT = true;
     WWinc = false;
   }
   else if (type_of_data == "TT") {
     Signal = false;
     data = false;
     DYinc = false;
     WJetsinc = false;
     TTinc = false;
     TT = true;
     WWinc = false;
   }
   else if (type_of_data == "WWinc") {
     Signal = false;
     data = false;
     DYinc = false;
     WJetsinc = false;
     TTinc = false;
     TT = false;
     WWinc = true;
   }
   else {
     Signal = false;
     data = false;
     DYinc = false;
     WJetsinc = false;
     TTinc = false;
     TT = false;
     WWinc = false;
   }

   if (type_of_data == "singlephoton" || type_of_data == "SinglePhoton") singlephoton = true;
   if (type_of_data == "singlemu" || type_of_data == "SingleMu") singlemu = true;



   int CR_number = -1;
   if (controlregion == "CR0") {
     //OS, iso mu, iso tau = signal region
     CR_number = 0;
   }
   else if (controlregion == "CR1") {
     //SS, iso mu, iso tau
     CR_number = 1;
   }
   else if (controlregion == "CR2") {
     //OS, iso mu, anti-iso tau
     CR_number = 2;
   }
   else if (controlregion == "CR3") {
     //SS, iso mu, anti-iso tau
     CR_number = 3;
   }
   else if (controlregion == "CR4") {
     //OS, anti-iso mu, anti-iso tau
     CR_number = 4;
   }
   else if (controlregion == "CR5") {
     //SS, anti-iso mu, anti-iso tau
     CR_number = 5;
   }
   else if (controlregion == "CR7") {
     //SS, iso mu, anti-iso tau, mt restricted
     CR_number = 7;
   }
   else if (controlregion == "CR9") {
     //SS, iso mu, iso tau, mt restricted
     CR_number = 9;
   }
   else if (controlregion == "CR100") {
     //no sign requirement, iso mu, anti-iso tau, estimate fake tau bg
     CR_number = 100;
   }
   else if (controlregion == "CR101") {
     //no sign requirement, iso mu, anti-iso tau, estimate fake tau bg
     CR_number = 101;
   }
   else if (controlregion == "CR102") {
     //no sign requirement, iso mu, iso tau, Mt>80 GeV, W+Jets enriched CR
     CR_number = 102;
   }
   else if (controlregion == "CR103") {
     //no sign requirement, iso mu, anti-iso tau, Mt>80 GeV, W+Jets enriched CR
     CR_number = 103;
   }

   //string out_name = "out_"+type_of_data+".root";
   TFile* file_out = new TFile(out_name.c_str(),"RECREATE");

   const float mu_mass = 0.10565837;
   const float pi = 3.14159;

   //list here the names and x-axis ranges of all gen-level histos we wish to create :
   vector<TString> histo_gen_names;                vector<int> nBins_gen;     vector<float> x_min_gen,    x_max_gen; 
   histo_gen_names.push_back("gen_tau_pt");       nBins_gen.push_back(100);  x_min_gen.push_back(0);     x_max_gen.push_back(100);
   histo_gen_names.push_back("gen_tau_eta");      nBins_gen.push_back(50);   x_min_gen.push_back(-2.5);  x_max_gen.push_back(2.5);
   histo_gen_names.push_back("gen_tau_phi");      nBins_gen.push_back(64);   x_min_gen.push_back(-3.2);  x_max_gen.push_back(3.2);
   histo_gen_names.push_back("gen_ev_DR2l");       nBins_gen.push_back(100);  x_min_gen.push_back(0);     x_max_gen.push_back(10);
   histo_gen_names.push_back("gen_ev_M");          nBins_gen.push_back(100);  x_min_gen.push_back(995);   x_max_gen.push_back(1005);
   histo_gen_names.push_back("gen_ev_visDR2l");    nBins_gen.push_back(100);  x_min_gen.push_back(0);     x_max_gen.push_back(10);
   histo_gen_names.push_back("gen_ev_Mvis");       nBins_gen.push_back(200);  x_min_gen.push_back(700);   x_max_gen.push_back(1100);
   histo_gen_names.push_back("gen_ev_ntaus");      nBins_gen.push_back(10);  x_min_gen.push_back(0);   x_max_gen.push_back(10);
   histo_gen_names.push_back("gen_tau_decaymode");    nBins_gen.push_back(3);  x_min_gen.push_back(-0.5); x_max_gen.push_back(2.5);
   histo_gen_names.push_back("gen_tautau_decaymode"); nBins_gen.push_back(9);  x_min_gen.push_back(-0.5); x_max_gen.push_back(8.5);

   vector<TH1F*> hgen;
   for (unsigned int i = 0; i<histo_gen_names.size(); ++i) hgen.push_back( new TH1F(histo_gen_names[i], histo_gen_names[i], nBins_gen[i], x_min_gen[i], x_max_gen[i]) ); 


   //list here the names and x-axis ranges of all reco-level histos we wish to create :
   vector<TString> histo_names;               vector<int> nBins;     vector<float> x_min,   x_max; 
   histo_names.push_back("ev_Mvis");          nBins.push_back(4000); x_min.push_back(0);    x_max.push_back(4000);
   histo_names.push_back("ev_Mtot");          nBins.push_back(4000); x_min.push_back(0);    x_max.push_back(4000);
   histo_names.push_back("tau_pt");           nBins.push_back(1000); x_min.push_back(0);    x_max.push_back(1000);
   histo_names.push_back("tau_eta");          nBins.push_back(50);  x_min.push_back(-2.5); x_max.push_back(2.5);
   histo_names.push_back("tau_phi");          nBins.push_back(64);  x_min.push_back(-3.2); x_max.push_back(3.2);
   histo_names.push_back("mu_pt");            nBins.push_back(1000); x_min.push_back(0);    x_max.push_back(1000);
   histo_names.push_back("mu_eta");           nBins.push_back(50);   x_min.push_back(-2.5); x_max.push_back(2.5);
   histo_names.push_back("mu_phi");           nBins.push_back(64);   x_min.push_back(-3.2); x_max.push_back(3.2);
   histo_names.push_back("ev_DRmutau");       nBins.push_back(100);  x_min.push_back(0);    x_max.push_back(10);
   histo_names.push_back("ev_DeltaPhimutau"); nBins.push_back(64);   x_min.push_back(0);    x_max.push_back(3.2);
   histo_names.push_back("ev_DeltaPhiMETtau");nBins.push_back(64);   x_min.push_back(0);    x_max.push_back(3.2);
   histo_names.push_back("ev_MET");           nBins.push_back(1000); x_min.push_back(0);    x_max.push_back(1000);
   histo_names.push_back("ev_weight");        nBins.push_back(400);  x_min.push_back(-2);   x_max.push_back(2);
   histo_names.push_back("ev_deltaMET");      nBins.push_back(200);  x_min.push_back(-100); x_max.push_back(100);
   histo_names.push_back("ev_Mcol");          nBins.push_back(4000); x_min.push_back(0);    x_max.push_back(4000);
   histo_names.push_back("ev_Mt");            nBins.push_back(4000); x_min.push_back(0);    x_max.push_back(4000);
   histo_names.push_back("mu_isolation");     nBins.push_back(200);  x_min.push_back(0);    x_max.push_back(0.2);
   histo_names.push_back("sign");             nBins.push_back(5);    x_min.push_back(0);    x_max.push_back(5);
   int OS_number = 1;
   int SS_number = 3;

   vector<TString> taun;
   taun.push_back("realtau"); int j_real = taun.size()-1;
   taun.push_back("faketau"); int j_fake = taun.size()-1;

   vector<TString> Mth;
   Mth.push_back("MtLow_OS");  int k_low_OS = Mth.size()-1;
   Mth.push_back("MtLow_SS");  int k_low_SS = Mth.size()-1;
   Mth.push_back("MtHigh");    int k_high   = Mth.size()-1;
   Mth.push_back("MtLow_TT");  int k_low_TT= Mth.size()-1;
   Mth.push_back("MtHigh_TT"); int k_high_TT= Mth.size()-1;


   vector<TH1F*> h[Mth.size()][taun.size()];
   for (unsigned int i = 0; i<histo_names.size(); ++i) {
     for (unsigned int j = 0; j<taun.size(); ++j) {
       for (unsigned int k = 0; k<Mth.size(); ++k) {
	 h[k][j].push_back( new TH1F(histo_names[i]+"_"+taun[j]+"_"+Mth[k], histo_names[i]+"_"+taun[j]+"_"+Mth[k], nBins[i], x_min[i], x_max[i]) ); 
	 h[k][j][i]->Sumw2();
       }
     }
   }


   vector<TString> h_names;
   //h_names.push_back("taupt_jetpt_pass"); int iJetPtPass = h_names.size()-1;
   //h_names.push_back("taupt_jetpt_fail"); int iJetPtFail = h_names.size()-1;
   h_names.push_back("taupt_ratio_pass");  int iRatioPass  = h_names.size()-1;
   h_names.push_back("taupt_ratio_fail");  int iRatioFail  = h_names.size()-1;

   vector<TString> dms;
   dms.push_back("DM0");  int k_DM0  = dms.size()-1;
   dms.push_back("DM1");  int k_DM1  = dms.size()-1;
   dms.push_back("DM10"); int k_DM10 = dms.size()-1;

   vector<TString> eta;
   eta.push_back("barrel"); int l_barrel = eta.size()-1;
   eta.push_back("endcap"); int l_endcap = eta.size()-1;

   vector<TH2F*> hh[h_names.size()][Mth.size()][dms.size()][eta.size()];

   for (unsigned int i = 0; i<h_names.size(); ++i) {
     for (unsigned int j = 0; j<Mth.size(); ++j) {
       for (unsigned int k = 0; k<dms.size(); ++k) {
	 for (unsigned int l = 0; l<eta.size(); ++l) {
	   for (unsigned int m = 0; m<taun.size(); ++m) {
	     TString nname = h_names[i]+"_"+Mth[j]+"_"+dms[k]+"_"+eta[l]+"_"+taun[m];
	     hh[i][j][k][l].push_back( new TH2F(nname, nname, 1000, 0, 1000, 1000, 0, 10) );
	     hh[i][j][k][l][m]->Sumw2();
	   }
	 }
       }
     }
   }
   



   Long64_t nEntries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   long n1=0, n2=0;
   int print_count = 0;
   //start loop over all events
   cout << nEntries << endl;
   for (Long64_t jEntry = 0; jEntry < nEntries; ++jEntry) {
      Long64_t iEntry = LoadTree(jEntry);
      if (iEntry < 0) break;
      if (jEntry % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", jEntry, nEntries);


      nb = fChain->GetEntry(jEntry);
      nbytes += nb;

      float first_weight = 1;
      double final_weight = first_weight;
      float pu_weight = 1;
      if (!data) {
	pu_weight = PU_2018_Rereco::MC_pileup_weight(mc_trueNumInteractions, mc_nickname, "Data_2018AtoD");
      }
      

      //Do not consider events which should be rejected
      bool reject_event = false, Zmumu = false;
      if (DYinc) {
        TLorentzVector l1_p4, l2_p4, ll_p4;
      	l1_p4.SetPxPyPzE(0, 0, 0, 0);
      	l2_p4.SetPxPyPzE(0, 0, 0, 0);
      	ll_p4.SetPxPyPzE(0, 0, 0, 0);
        int l1_pdgid = 0, l2_pdgid = 0;
        if (print_count < 20) {
          ++print_count;
          //cout << endl << "LHE info" << endl;
        }

	bool found_1 = false, found_2 = false;
        for (unsigned int iLHE = 0; iLHE < LHE_Pt->size(); ++iLHE) {
          if (print_count < 20) {
            //cout << LHE_pdgid->at(iLHE) << "  " << LHE_Pt->at(iLHE) << "  " << LHE_Eta->at(iLHE) << "  " << LHE_Phi->at(iLHE) << "  " << LHE_E->at(iLHE) << endl;
          }
      	  if (LHE_Pt->at(iLHE) <= 0) continue; 
          if (LHE_pdgid->at(iLHE) == 11 || LHE_pdgid->at(iLHE) == 13 || LHE_pdgid->at(iLHE) == 15) {
            l1_p4.SetPtEtaPhiE(LHE_Pt->at(iLHE),LHE_Eta->at(iLHE),LHE_Phi->at(iLHE),LHE_E->at(iLHE));
            l1_pdgid = LHE_pdgid->at(iLHE);
	    found_1 = true;
          }
          else if (LHE_pdgid->at(iLHE) == -11 || LHE_pdgid->at(iLHE) == -13 || LHE_pdgid->at(iLHE) == -15) {
            l2_p4.SetPtEtaPhiE(LHE_Pt->at(iLHE),LHE_Eta->at(iLHE),LHE_Phi->at(iLHE),LHE_E->at(iLHE));
            l2_pdgid = LHE_pdgid->at(iLHE); 
	    found_2 = true;
         }
      	  if (abs(LHE_pdgid->at(iLHE)) == 13) Zmumu = true;
        }
	if (!found_1 || !found_2) continue;
        if (l1_pdgid == -l2_pdgid) {
          ll_p4 = l1_p4 + l2_p4;
          if (ll_p4.M() > 400) reject_event = true;
        }
        else {
          cout << "??" << LHE_pdgid->size() << endl;
        }
      }//close is this DY inclusive question
      else if (WJetsinc) {
        TLorentzVector l_p4, nu_p4, lnu_p4;
      	l_p4.SetPxPyPzE(0, 0, 0, 0);
      	nu_p4.SetPxPyPzE(0, 0, 0, 0);
      	lnu_p4.SetPxPyPzE(0, 0, 0, 0);
        int l_pdgid = 0, nu_pdgid = 0;
        if (print_count < 20) {
          ++print_count;
          //cout << endl << "LHE info" << endl;
        }

	bool found_1 = false, found_2 = false;
        for (unsigned int iLHE = 0; iLHE < LHE_Pt->size(); ++iLHE) {
          if (print_count < 20) {
      	    // cout << LHE_pdgid->at(iLHE) << "  " << LHE_Pt->at(iLHE) << "  " << LHE_Eta->at(iLHE) << "  " << LHE_Phi->at(iLHE) << "  " << LHE_E->at(iLHE) << endl;
          }
          if (abs(LHE_pdgid->at(iLHE)) == 11 || abs(LHE_pdgid->at(iLHE)) == 13 || abs(LHE_pdgid->at(iLHE)) == 15) {
            l_p4.SetPtEtaPhiE(LHE_Pt->at(iLHE),LHE_Eta->at(iLHE),LHE_Phi->at(iLHE),LHE_E->at(iLHE));
            l_pdgid = LHE_pdgid->at(iLHE);
	    found_1 = true;
          }
          else if (abs(LHE_pdgid->at(iLHE)) == 12 || abs(LHE_pdgid->at(iLHE)) == 14 || abs(LHE_pdgid->at(iLHE)) == 16) {
            nu_p4.SetPtEtaPhiE(LHE_Pt->at(iLHE),LHE_Eta->at(iLHE),LHE_Phi->at(iLHE),LHE_E->at(iLHE));
            nu_pdgid = LHE_pdgid->at(iLHE);
	    found_2 = true;
          }
        }
	if (!found_1 || !found_2) continue;
        if (abs(l_pdgid) == abs(nu_pdgid)-1) {
          lnu_p4 = l_p4 + nu_p4;
          if (lnu_p4.Pt() > 100) reject_event = true;
        }
        else {
          cout << "??" << endl;
        }
      }//close the is this WJets inclusive question
      else if (TTinc || WWinc) {
        TLorentzVector l1_p4, l2_p4, ll_p4;
      	l1_p4.SetPxPyPzE(0, 0, 0, 0);
      	l2_p4.SetPxPyPzE(0, 0, 0, 0);
      	ll_p4.SetPxPyPzE(0, 0, 0, 0);
        int l1_pdgid = 0, l2_pdgid = 0;
        if (print_count < 20) {
          ++print_count;
          //cout << endl << jEntry << endl << "LHE info" << endl;
        }

	bool found_1 = false, found_2 = false;
        for (unsigned int iLHE = 0; iLHE < LHE_Pt->size(); ++iLHE) {
          if (print_count < 20) {
            //cout << LHE_pdgid->at(iLHE) << "  " << LHE_Pt->at(iLHE) << "  " << LHE_Eta->at(iLHE) << "  " << LHE_Phi->at(iLHE) << "  " << LHE_E->at(iLHE) << endl;
          }
          if (abs(LHE_pdgid->at(iLHE)) == 11 || abs(LHE_pdgid->at(iLHE)) == 13 || abs(LHE_pdgid->at(iLHE)) == 15) {
            l1_p4.SetPtEtaPhiE(LHE_Pt->at(iLHE),LHE_Eta->at(iLHE),LHE_Phi->at(iLHE),LHE_E->at(iLHE));
            l1_pdgid = LHE_pdgid->at(iLHE);
	    found_1 = true;
          }
      
          for (unsigned int jLHE = 0; jLHE < iLHE; ++jLHE) {
            if (abs(LHE_pdgid->at(iLHE)) == 11 || abs(LHE_pdgid->at(iLHE)) == 13 || abs(LHE_pdgid->at(iLHE)) == 15) {
              l2_p4.SetPtEtaPhiE(LHE_Pt->at(jLHE),LHE_Eta->at(jLHE),LHE_Phi->at(iLHE),LHE_E->at(jLHE));
              l2_pdgid = LHE_pdgid->at(jLHE);
	      found_2 = true;
            }
            ll_p4 = l1_p4 + l2_p4;
	    if (!found_1 || !found_2) continue;
      	    if (TTinc) {
      	      if (ll_p4.M() > 500) reject_event = true;
      	    }
      	    else if (WWinc) {
      	      if (ll_p4.M() > 200) reject_event = true;
      	    }	      
      	    if (reject_event) break;
          }
      	  if (reject_event) break;
        }
      }
      //close the is this TT inclusive question
      //if (reject_event) continue;
      //FIXME when there are high mass samples
      
      double TT_ptreweight = 1, w_top_up = 1, w_top_down = 1;
      if(TT) {
	bool find_t1 = false;
	bool find_t2 = false;
	TLorentzVector MC_p4_1(1,0,0,0);
	TLorentzVector MC_p4_2(1,0,0,0);
	for(unsigned iMC=0 ; iMC<LHE_Pt->size() ; ++iMC) {
	  if( (LHE_pdgid->at(iMC) == 6) ) {
	    MC_p4_1.SetPtEtaPhiE(LHE_Pt->at(iMC),LHE_Eta->at(iMC),LHE_Phi->at(iMC),LHE_E->at(iMC)) ;
	    find_t1 = true;
	  }
	  else if( (LHE_pdgid->at(iMC) == -6) ) {
	    MC_p4_2.SetPtEtaPhiE(LHE_Pt->at(iMC),LHE_Eta->at(iMC),LHE_Phi->at(iMC),LHE_E->at(iMC)) ;
	    find_t2 = true;
	  }
	  if(find_t1 && find_t2) {
	    float tmp_t1 = exp(0.0615-0.0005*MC_p4_1.Pt());
	    float tmp_t2 = exp(0.0615-0.0005*MC_p4_2.Pt());
	    float tmp_t1_uncer = top_reweighting_uncertainty(MC_p4_1.Pt());
	    float tmp_t2_uncer = top_reweighting_uncertainty(MC_p4_2.Pt());

	    w_top_up = sqrt(tmp_t1*(1.0 + tmp_t1_uncer)*tmp_t2*(1.0 + tmp_t2_uncer) );
	    w_top_down = sqrt(tmp_t1*(1.0 - tmp_t1_uncer)*tmp_t2*(1.0 - tmp_t2_uncer) );
	    TT_ptreweight = sqrt(tmp_t1 * tmp_t2);
	    break;
	  }
	}
      }

      vector<TLorentzVector> tauhp4;
      tauhp4.clear();
      vector<TLorentzVector> anyleptonp4, genmup4, genelep4;
      anyleptonp4.clear();
      genmup4.clear();
      genelep4.clear();
      vector<int> tau_ind, tau_dm;
      tau_ind.clear(), tau_dm.clear();
      if (!data) {
	//start loop over all simulated particules
	TLorentzVector mup4, totalvisp4, p4;
	for (unsigned int iMC = 0; iMC < mc_pt->size(); ++iMC) {
	  if (abs(mc_pdgId->at(iMC)) == 11 || abs(mc_pdgId->at(iMC)) == 13) {
	    if (mc_pt->at(iMC) < 10) continue;
	    p4.SetPxPyPzE(mc_px->at(iMC), mc_py->at(iMC), mc_pz->at(iMC), mc_energy->at(iMC));
	    if (p4.Pt() < 10) continue;
	    if (p4.Pt() > 10000) continue;
	    anyleptonp4.push_back(p4);
	    if (abs(mc_pdgId->at(iMC)) == 13) genmup4.push_back(p4);
	    if (abs(mc_pdgId->at(iMC)) == 11) genelep4.push_back(p4);
	  }
	}//end MC loop
	for (unsigned int iMC = 0; iMC < mc_tau_had_pt->size(); ++iMC) {
	  if (mc_tau_had_pt->at(iMC) < 10) continue;
	  p4.SetPtEtaPhiE(mc_tau_had_pt->at(iMC), mc_tau_had_eta->at(iMC), mc_tau_had_phi->at(iMC), mc_tau_had_energy->at(iMC)); 
	  if (p4.Pt() < 10) continue;
	  if (p4.Pt() > 10000) continue;
	  tauhp4.push_back( p4 );
	  anyleptonp4.push_back( p4 );
	}

      }//end is this not-data? condition


      //Is one of the triggers fired?
      //FIXME
      bool PassTrigger = false;
      if (trig_HLT_Mu50_accept || trig_HLT_OldMu100_accept || trig_HLT_TkMu100_accept) PassTrigger = true;
      if (!PassTrigger) continue;

      if(!trig_Flag_goodVertices_accept) continue;
      if(!trig_Flag_globalSuperTightHalo2016Filter_accept) continue;
      if(!trig_Flag_HBHENoiseFilter_accept) continue;
      if(!trig_Flag_HBHENoiseIsoFilter_accept) continue;
      if(!trig_Flag_EcalDeadCellTriggerPrimitiveFilter_accept) continue;
      if(!trig_Flag_BadPFMuonFilter_accept) continue;
      
      bool ECALBadCalib = false;
      if (data) ECALBadCalib = trig_Flag_ecalBadCalibReduced;
      else ECALBadCalib = MET_ecalBadCalibFilterUpdate_2018;
      if (!ECALBadCalib) continue;




      //bjet pair finding (medium WP for the bjet)                                                                                                                           
      //add SF when available
      int nbjet = 0;
      float bjetMedium2018 =  0.4184;
      float bjet_weight = 1;
      for (unsigned int iJet = 0; iJet < jet_pt->size(); ++iJet) {
	TLorentzVector bjet_p4;
	bool looseJet = false;
	if (data) {
	  looseJet = jet_isJetID_2018->at(iJet);
	}
	else {
	  looseJet = jet_isJetIDLoose->at(iJet);
	}
	if (jet_DeepCSV->at(iJet) > bjetMedium2018 && jet_pt->at(iJet) > 30 && fabs(jet_eta->at(iJet)) < 2.4 && looseJet) {
	  bjet_p4.SetPxPyPzE(jet_px->at(iJet), jet_py->at(iJet), jet_pz->at(iJet), jet_energy->at(iJet));

	  //bjet should match neither a tau nor a muon
	  bool btau = false;
	  for (unsigned int iTau = 0; iTau < tau_pt->size(); ++iTau) {
	    TLorentzVector tau_temp_p4;
	    tau_temp_p4.SetPtEtaPhiE(tau_pt->at(iTau), tau_eta->at(iTau), tau_phi->at(iTau), tau_energy->at(iTau));
	    if (tau_temp_p4.Pt() < 30.0) continue;
	    if (fabs(tau_eta->at(iTau)) > 2.3) continue;
	    if (tau_decayModeFinding->at(iTau) < 0.5) continue;
	    if (tau_againstMuonTight3->at(iTau) < 0.5) continue;
	    if (tau_againstElectronVLooseMVA6->at(iTau) < 0.5) continue;
	    if (fabs(tau_charge->at(iTau)) != 1) continue;
	    if (tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	          
	    if (bjet_p4.DeltaR(tau_temp_p4) < 0.5) btau = true;
	    if (btau) break;
	  }
	  if (btau) continue;
	      
	  bool bmu = false;
	  for (unsigned int iMu = 0; iMu < mu_ibt_pt->size(); ++iMu) {
	    TLorentzVector mu_temp_p4;
	    mu_temp_p4.SetPtEtaPhiM(mu_ibt_pt->at(iMu), mu_ibt_eta->at(iMu), mu_ibt_phi->at(iMu), mu_mass);
	    if (mu_ibt_pt->at(iMu) < 53.0) continue;
	    if (!mu_isHighPtMuon->at(iMu)) continue;
	    if (fabs(mu_ibt_eta->at(iMu)) > 2.4) continue;
	    if (mu_isoTrackerBased03->at(iMu) > 0.1) continue;
	          
	    if (bjet_p4.DeltaR(mu_temp_p4) < 0.5) bmu = true;
	    if (bmu) break;
	  }
	  if (bmu) continue;
	  double jet_scalefactor = 1;
	  if (!data) {
	    if (fabs(jet_partonFlavour->at(iJet)) == 5) {
	      jet_scalefactor = reader.eval_auto_bounds(
							"central",
							BTagEntry::FLAV_B,
							fabs(bjet_p4.Eta()), // absolute value of eta
							bjet_p4.Pt()
							);
	    }
	    else if (fabs(jet_partonFlavour->at(iJet)) == 4) {
	      jet_scalefactor = reader.eval_auto_bounds(
							"central",
							BTagEntry::FLAV_C,
							fabs(bjet_p4.Eta()), // absolute value of eta
							bjet_p4.Pt()
							);
	    }
	    else {
	      jet_scalefactor = reader.eval_auto_bounds(
							"central",
							BTagEntry::FLAV_UDSG,
							fabs(bjet_p4.Eta()), // absolute value of eta
							bjet_p4.Pt()
							);
	    }

	    cout<<"jet_scalefactor:"<<jet_scalefactor<<endl;
	    if (jet_scalefactor == 0) jet_scalefactor = 1;
	    bjet_weight *= jet_scalefactor;

	  }
	  ++nbjet;
	}
	if (nbjet >= 2) break;
      }



      //classify mu-tau pairs by their collinear mass
      map<vector<int>, float> Mcol_map;
      vector<vector<int>> mutau_ind_temp;
      for (unsigned int ii = 0; ii < mu_ibt_pt->size(); ++ii) {
        TLorentzVector mu_p4;
        mu_p4.SetPtEtaPhiM(mu_ibt_pt->at(ii), mu_ibt_eta->at(ii), mu_ibt_phi->at(ii), mu_mass);
        for (unsigned int jj = 0; jj < tau_pt->size(); ++jj) {
	  float met_px = MET_nominal_Px;
	  float met_py = MET_nominal_Py;
	  float met_pt = MET_nominal_Pt;
          TLorentzVector tau_p4, met_p4;
          tau_p4.SetPtEtaPhiE(tau_pt->at(jj), tau_eta->at(jj), tau_phi->at(jj), tau_energy->at(jj));
          met_p4.SetPxPyPzE(met_px, met_py, 0, met_pt);

          //MET recalculation because we're using the high-pt muon ID
          TLorentzVector mu_gt_p4, mu_gt_transp4;
          mu_gt_p4.SetPxPyPzE(0, 0, 0, 0);
          mu_gt_transp4.SetPxPyPzE(0, 0, 0, 0);

          float min_dR = 0.2;
          for (unsigned int kk=0; kk<mu_gt_pt->size(); ++kk) {
            if (!mu_isPFMuon->at(kk)) continue;
            mu_gt_p4.SetPtEtaPhiM(mu_gt_pt->at(kk), mu_gt_eta->at(kk), mu_gt_phi->at(kk), mu_mass);
            if ( (abs(mu_gt_p4.Pt()) >= 998.99) && (abs(mu_gt_p4.Pt()) <= 999.01) )continue;
            if (mu_gt_p4.DeltaR(mu_p4) > min_dR) continue;
            min_dR = mu_gt_p4.DeltaR(mu_p4);
            mu_gt_transp4.SetPtEtaPhiM(mu_gt_pt->at(kk), 0, mu_gt_phi->at(kk), mu_mass);
          }
          met_p4 = met_p4 + mu_gt_transp4 - mu_p4;

          float Mcol = GetCollinearMass(tau_p4, mu_p4, met_p4);
          vector<int> index;
          index.push_back(ii); //mu index
          index.push_back(jj); //tau index
          Mcol_map[index] = Mcol;
          mutau_ind_temp.push_back(index);
        }
      }


      vector<vector<int>> rest, mutau_ind;
      mutau_ind.clear();
      while (mutau_ind_temp.size()>0) {
        rest.clear();
        float max_mcol = -1;
        vector<int> highest_ind;
        highest_ind.clear();
        for (unsigned int iInd = 0; iInd < mutau_ind_temp.size(); ++iInd) {
          if (Mcol_map[mutau_ind_temp[iInd]] > max_mcol) {
            max_mcol = Mcol_map[mutau_ind_temp[iInd]];
            if (highest_ind.size() > 0) rest.push_back(highest_ind);
            highest_ind = mutau_ind_temp[iInd];
          }
          else {
            rest.push_back(mutau_ind_temp[iInd]);
          }
        }
        mutau_ind.push_back(highest_ind);
        mutau_ind_temp = rest;
      }


      //start loop over reconstructed mu-tau pairs
      bool filled_histos = false;
      for (unsigned int ii = 0; ii < mutau_ind.size(); ++ii) {
        if (filled_histos) break;
        int iMu = mutau_ind[ii][0];
        int iTau = mutau_ind[ii][1];

	if (mu_ibt_pt->at(iMu) < 53.0) continue;
	if (!mu_isHighPtMuon->at(iMu)) continue;
	if (fabs(mu_ibt_eta->at(iMu)) > 2.4) continue;


	TLorentzVector mu_p4, mu_ibt_transp4;
	mu_p4.SetPtEtaPhiM(mu_ibt_pt->at(iMu), mu_ibt_eta->at(iMu), mu_ibt_phi->at(iMu), mu_mass);
	mu_ibt_transp4.SetPxPyPzE(mu_ibt_px->at(iMu), mu_ibt_py->at(iMu), 0, mu_ibt_pt->at(iMu));

	TLorentzVector tau_p4, tau_TES_p4, vis_p4, met_p4, metmu_p4, total_p4;
	float met_px = MET_nominal_Px;
	float met_py = MET_nominal_Py;
	float met_pt = MET_nominal_Pt;
	tau_p4.SetPtEtaPhiE(tau_pt->at(iTau), tau_eta->at(iTau), tau_phi->at(iTau), tau_energy->at(iTau));
	met_p4.SetPxPyPzE(met_px, met_py, 0, met_pt);
	
	vis_p4 = tau_p4 + mu_p4;
	total_p4 = vis_p4 + met_p4;
	metmu_p4 = met_p4 + mu_p4;
	
	if (tau_pt->at(iTau) < 0) continue;
	if (tau_p4.Pt() < 30.0) continue;
	if (fabs(tau_eta->at(iTau)) > 2.3) continue;
	if (tau_decayModeFinding->at(iTau) < 0.5) continue;
	if (tau_againstMuonTight3->at(iTau) < 0.5) continue;
	if (tau_againstElectronVLooseMVA6->at(iTau) < 0.5) continue;
	//if (fabs(tau_dz->at(iTau)) > 0.2) continue;
	if (fabs(tau_charge->at(iTau)) != 1) continue;


	//control regions : sign selection, muon isolation and tau ID
	if (CR_number == -1) {
	  cout << "Error: Control region not recognized" << endl;
	  break;
	}
	
	float reliso = mu_isoTrackerBased03->at(iMu); //use instead sumofpts divided by muon ibt pt


	//MET recalculation because we're using the high-pt muon ID
	TLorentzVector mu_gt_p4, mu_gt_transp4;
	mu_gt_p4.SetPxPyPzE(0, 0, 0, 0);
	mu_gt_transp4.SetPxPyPzE(0, 0, 0, 0);

	float min_dR = 0.2;
	for (unsigned int kk=0; kk<mu_gt_pt->size(); ++kk) {
	  if (!mu_isPFMuon->at(kk)) continue;
	  mu_gt_p4.SetPtEtaPhiM(mu_gt_pt->at(kk), mu_gt_eta->at(kk), mu_gt_phi->at(kk), mu_mass);
	  if ( (abs(mu_gt_p4.Pt()) >= 998.99) && (abs(mu_gt_p4.Pt()) <= 999.01) )continue;
	  if (mu_gt_p4.DeltaR(mu_p4) > min_dR) continue;
	  min_dR = mu_gt_p4.DeltaR(mu_p4);
	  mu_gt_transp4.SetPtEtaPhiM(mu_gt_pt->at(kk), 0, mu_gt_phi->at(kk), mu_mass);
	}
	met_p4 = met_p4 + mu_gt_transp4 - mu_ibt_transp4;


	
	float Mt = -1;
	if (2 * ( mu_p4.Pt() * met_p4.Pt()  - mu_p4.Px()*met_p4.Px() - mu_p4.Py()*met_p4.Py() ) < 0) {
	  Mt = 0;
	}
	else {
	  Mt = sqrt(2 * ( mu_p4.Pt() * met_p4.Pt()  - mu_p4.Px()*met_p4.Px() - mu_p4.Py()*met_p4.Py() ) );
	}

	if (CR_number<100) {
	  //sign selection
	  if (CR_number%2 == 0) {
	    if (tau_charge->at(iTau) * mu_ibt_charge->at(iMu) > 0) continue; //OS selection
	  }
	  else {
	    if (tau_charge->at(iTau) * mu_ibt_charge->at(iMu) < 0) continue; //SS selection
	  }
	  
	  //muon isolation
	  if (CR_number < 4 || CR_number >= 7) {
	    if (reliso > 0.1) continue;
	  }
	  else {
	    if (reliso < 0.1) continue;
	  }
	    
	  //tau isolation
	  if (CR_number < 2 || CR_number == 9) {
	    if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	  }
	  else {
	    if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) > 0.5) continue;
	    if (tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	  }
	}
	else {
	  if (CR_number == 100) {
	    if (reliso > 0.1) continue;
	    //if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	    if (tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	  }	      
	  if (CR_number == 101) {
	    if (reliso > 0.1) continue;
	    if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) > 0.5) continue;
	    if (tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	  }	      
	  if (CR_number == 102) {
	    if (reliso > 0.1) continue;
	    if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	    if (Mt<80) continue;
	  }	      
	  if (CR_number == 103) {
	    if (reliso > 0.1) continue;
	    if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) > 0.5) continue;
	    if (tau_byVVLooseIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	    if (Mt<80) continue;
	  }	      
	}


	int kMth = -1;
	bool isLowTTCR = false, isHighTTCR = false;
	int sign_number = -1;
	if (Mt < 120) {
	  if (nbjet >= 2) isLowTTCR = true;
	  if ( tau_charge->at(iTau)*mu_ibt_charge->at(iMu) < 0) {
	    kMth = k_low_OS;
	    sign_number = OS_number;
	  }
	  else {
	    kMth = k_low_SS;
	    sign_number = SS_number;
	  }
	}
	else {
	  kMth = k_high;
	  if (nbjet >= 2) isHighTTCR = true;
	  if ( tau_charge->at(iTau)*mu_ibt_charge->at(iMu) < 0) {
	    sign_number = OS_number;
	  }
	  else {
	    sign_number = SS_number;
	  }
	}

	double lepToTauFR = 1;

	//separate histos by tau realness
	int jTauN=j_real;
	bool tau_match = false;
	if (!data && !Signal) {
	  //fill gen histos to understand wth is going on
	  hgen[7]->Fill(tauhp4.size(), mc_w_sign);
	  for (unsigned int iGen = 0; iGen<tauhp4.size(); ++iGen) {
	    hgen[0]->Fill(tauhp4[iGen].Pt(), mc_w_sign);
	    hgen[1]->Fill(tauhp4[iGen].Eta(), mc_w_sign);
	    hgen[2]->Fill(tauhp4[iGen].Phi(), mc_w_sign);
	  }

	  bool ele_match = false;
	  if (genelep4.size() != 0) {
	    for (unsigned int iGen = 0; iGen < genelep4.size(); ++iGen) {
		if (tau_p4.DeltaR(genelep4[iGen]) < 0.2) ele_match = true;
	    }
	  }
	  bool mu_match = false;
	  if (genmup4.size() != 0) {
	    for (unsigned int iGen = 0; iGen < genmup4.size(); ++iGen) {
		if (tau_p4.DeltaR(genmup4[iGen]) < 0.2) mu_match = true;
	    }
	  }
	  if (ele_match && mu_match) {
	    cout << "gen electron AND muon both match to same tau !!!" << endl << endl << endl;
	    continue;
	  }
	  if (ele_match) lepToTauFR = GetLepToTauFR("ele", tau_p4.Eta());
	  if (mu_match)  lepToTauFR = GetLepToTauFR("mu", tau_p4.Eta());


	  bool is_not_jet = false;
	  if (anyleptonp4.size() != 0) {
	    for (unsigned int iGen = 0; iGen < anyleptonp4.size(); ++iGen) {
		if (tau_p4.DeltaR(anyleptonp4[iGen]) < 0.2) {
		  is_not_jet = true;
		  break;
		}
	    }
	  }
	  if (tauhp4.size() != 0) {
	    for (unsigned int iGen = 0; iGen < tauhp4.size(); ++iGen) {
		if (tau_p4.DeltaR(tauhp4[iGen]) < 0.2) {
		  tau_match = true;
		  break;
		}
	    }
	  }
	  if (is_not_jet) {
	    jTauN=j_real;
	  }
	  else {
	    jTauN=j_fake;
	  }

	  float reweight = GetReweight_highmass(mu_p4.Pt(), mu_p4.Eta());
	  h[kMth][jTauN][13]->Fill(reweight);
	}
	//FIXME
	first_weight = 1;
	if (!data) first_weight = pu_weight * GetReweight_highmass(mu_p4.Pt(), mu_p4.Eta()) * 1.0 * mc_w_sign * TT_ptreweight * lepToTauFR;
	final_weight = first_weight;

	if (CR_number == 7 || CR_number == 9) {
	  h[kMth][jTauN][16]->Fill(Mt, final_weight);
	  if (Mt < 80 || Mt > 120) continue;
	}



	if (final_weight != final_weight) {
	  cout << "Not a number!!!!!!!" << endl;
	  continue;
	}

	


	// MATCH TAUS TO AK4 jets
        bool matched_to_reco_jet=false;
        TLorentzVector jet_p4(0.,0.,0.,0.);
        for (unsigned int ijet = 0; ijet < jet_pt->size(); ijet++){
	  bool looseJet = false;
	  if (data) {
	    looseJet = jet_isJetID_2018->at(ijet);
	  }
	  else {
	    looseJet = jet_isJetIDLoose->at(ijet);
	  }
          if(!(fabs(jet_eta->at(ijet)) < 2.3)) continue;
          if(!looseJet) continue;
          TLorentzVector jet_p4_tmp;
          jet_p4_tmp.SetPxPyPzE(jet_px->at(ijet), jet_py->at(ijet), jet_pz->at(ijet), jet_energy->at(ijet));
          if(!(tau_p4.DeltaR(jet_p4_tmp) < 0.2)) continue;
          matched_to_reco_jet=true;
          jet_p4=jet_p4_tmp;
          break;

        }

	if(!(matched_to_reco_jet)) continue;



	float Mcol = GetCollinearMass(tau_p4, mu_p4, met_p4);
	TString eta_string = "";
	int l_eta = -1;
	if (fabs(tau_eta->at(iTau)) < 1.46) {
	  eta_string = "barrel";
	  l_eta = l_barrel;
	}
	else if (fabs(tau_eta->at(iTau)) > 1.56) {
	  eta_string = "endcap";
	  l_eta = l_endcap;
	}
	else {
	  continue;
	}

	double ratio = 1;
	if (jet_p4.Pt() != 0) ratio = tau_p4.Pt()/jet_p4.Pt();

	//if ((CR_number == 101) || (CR_number == 103)) final_weight = first_weight*FakeRate_SSMtLow(tau_p4.Pt(), jet_p4.Pt(), eta_string);
	if ((CR_number == 101) || (CR_number == 103)) final_weight = first_weight*FakeRate_unfactorised(tau_p4.Pt(), ratio, eta_string);


	//TH2's for the fake rate
	int iJetPt = -1, iRatio = -1;
	//Tau histos
	if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) > 0.5) {
	  //iJetPt = iJetPtPass;
	  iRatio  = iRatioPass;
	}
	else {
	  //iJetPt = iJetPtFail;
	  iRatio  = iRatioFail;
	}

	//decay mode
	int k_dm = -1;
	if (tau_decayMode->at(iTau) == 0) {
	  k_dm = k_DM0;
	}
	else if (tau_decayMode->at(iTau) == 1 || tau_decayMode->at(iTau) == 2) {
	  k_dm = k_DM1;
	}
	else if (tau_decayMode->at(iTau) == 10 || tau_decayMode->at(iTau) == 11) {
	  k_dm = k_DM10;
	}

	//electron veto
	bool electron = false;
	for (unsigned int iEle = 0; iEle < gsf_pt->size(); ++iEle) {
	  bool heepID = false;
	  if (data) {
	    heepID = gsf_VID_heepElectronID_HEEPV70->at(iEle);
	  }
	  else {
	    heepID = gsf_isHeepV7->at(iEle);
	  }
	  if (heepID && gsf_pt->at(iEle) > 40) electron = true;
	  if (electron) break;
	}
	if (electron) continue;

	float dR = tau_p4.DeltaR(mu_p4);

	if (dR < 0.5) continue;
	filled_histos = true;
	if (CR_number == 100) {
	  //hh[iJetPt][kMth][k_dm][l_eta][jTauN]->Fill(tau_p4.Pt(), jet_p4.Pt(), final_weight);
	  hh[iRatio][kMth][k_dm][l_eta][jTauN]->Fill(tau_p4.Pt(), ratio, final_weight);
	  if (tau_byTightIsolationMVArun2017v2DBoldDMwLT2017->at(iTau) < 0.5) continue;
	}


	bool stopFilling = false;
	int k_value = kMth;
	int n_fuel = 0;
	while (!stopFilling && n_fuel<2) {
	  ++n_fuel;

	  h[k_value][jTauN][0]->Fill(vis_p4.M(), final_weight);
	  h[k_value][jTauN][1]->Fill(total_p4.M(), final_weight);
	  h[k_value][jTauN][2]->Fill(tau_p4.Pt(), final_weight);
	  h[k_value][jTauN][3]->Fill(tau_p4.Eta(), final_weight);
	  h[k_value][jTauN][4]->Fill(tau_p4.Phi(), final_weight);
	  h[k_value][jTauN][5]->Fill(mu_p4.Pt(), final_weight);
	  h[k_value][jTauN][6]->Fill(mu_p4.Eta(), final_weight);
	  h[k_value][jTauN][7]->Fill(mu_p4.Phi(), final_weight);
	  h[k_value][jTauN][8]->Fill(dR, final_weight);
	  h[k_value][jTauN][11]->Fill(met_p4.Pt(), final_weight);
	  //h[k_value][jTauN][12]->Fill(mc_w_sign);
	  h[k_value][jTauN][13]->Fill(met_p4.Px()-met_px, final_weight);
	  h[k_value][jTauN][14]->Fill(Mcol, final_weight);
	  h[k_value][jTauN][15]->Fill(Mt, final_weight);
	  h[k_value][jTauN][16]->Fill(reliso, final_weight);
	  h[k_value][jTauN][17]->Fill(sign_number, final_weight);
	  if (k_value == k_high_TT || k_value == k_low_TT) stopFilling = true;
	  if (k_value == kMth) {
	    if (isHighTTCR) {
	      k_value = k_high_TT;
	      final_weight *= bjet_weight;
	    }
	    else if (isLowTTCR) {
	      k_value = k_low_TT;
	      final_weight *= bjet_weight;
	    } 
	    else {
	      stopFilling = true;
	    }
	  }
	}
      }//loop over muons
   }//loop over events


   TH1F* h_total_events =  new TH1F("weighted_events", "weighted_events", 1, 0, 1);
   h_total_events->Fill(0.5, nEvents);
   file_out->cd();
   h_total_events->Write();
   for (unsigned int i = 0; i<histo_names.size(); ++i) for (unsigned int j = 0; j<taun.size(); ++j) for (unsigned int k = 0; k<Mth.size(); ++k) h[k][j][i]->Write();
   for (unsigned int i = 0; i<h_names.size(); ++i) for (unsigned int j = 0; j<Mth.size(); ++j) for (unsigned int k = 0; k<dms.size(); ++k) for (unsigned int l = 0; l<eta.size(); ++l) for (unsigned int m = 0; m<taun.size(); ++m) hh[i][j][k][l][m]->Write();
   for (unsigned int i = 0; i<hgen.size(); ++i) hgen[i]->Write();
   file_out->Close();
}
