#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TTree.h"
#include "TLeaf.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraphErrors.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include "TLorentzVector.h"

using namespace std;

float norm_F(float x, float y){

  return sqrt(x*x+y*y);

}


double FakeRate_factorised(double taupt, double ratio, TString eta) {
  double SF=0.2;
  if (taupt >= 1000) taupt = 999;
  if (ratio >= 2) ratio = 1.9;

  TFile* fake_file = new TFile("Reweighting/fakerate_MtLow.root","R");

  double reweight = 0;

  TString hname = "eta_"+eta;
  TH1F* h_taupt = (TH1F*) fake_file->Get("FakeRateByTauPt_"+hname);
  int iBin = h_taupt->FindBin(taupt);
  double base_SF = h_taupt->GetBinContent(iBin);

  TH1F* h_corr = (TH1F*) fake_file->Get("RatioCorrectionFactor_"+hname);
  iBin = h_corr->FindBin(ratio);
  double corr_factor = h_corr->GetBinContent(iBin);

  SF = corr_factor*base_SF;
  reweight = SF;

  return reweight;
}



double topPtReweight(double pt) {
  double aa = 1.08872;
  double bb = 0.0119998;
  double cc = 0.895139;

  double w_top = exp(-aa-bb*pt) + cc;

  return w_top;
}


double GetCollinearMass(TLorentzVector tau, TLorentzVector mu,  TLorentzVector MET) {

  double METproj=fabs((MET.Px()*tau.Px()+MET.Py()*tau.Py())/tau.Pt());
  double xth=1;
  if((tau.Pt()+METproj)!=0) xth=tau.Pt()/(tau.Pt()+METproj);
  double mass_vis=(tau+mu).M();
  return mass_vis/sqrt(xth);
}


double GetLepToTauFR(TString lep, double eta) {

  double reweight = 1;
  if (lep == "mu") {
    if (fabs(eta) < 0.4) reweight = 1.17;
    else if (fabs(eta) < 0.8 && fabs(eta) > 0.4) reweight = 1.29;
    else if (fabs(eta) < 1.2 && fabs(eta) > 0.8) reweight = 1.14;
    else if (fabs(eta) < 1.7 && fabs(eta) > 1.2) reweight = 0.93;
    else if (fabs(eta) < 2.3 && fabs(eta) > 1.7) reweight = 1.61;
  }
  else if (lep == "ele") {
    if (fabs(eta) < 1.460) reweight = 1.09;
    else if (fabs(eta) > 1.558) reweight = 1.19;
  }
  return reweight;

}



double FakeRate_SSMtLow(double taupt, double jetpt, TString eta) {
  double SF=0.2;

  TFile* fake_file = new TFile("Reweighting/fakerate_SSMtLow.root","R");

  TString sector_string = "_taupt_";

  if (jetpt >= 1000) jetpt = 999;
  if (taupt >= 1000) taupt = 999;

  if ( (taupt > 0) && (taupt < 300) ) {
    sector_string += "0_300_jetpt_";

    if ( (jetpt > 0) && (jetpt < 150) )          sector_string += "0_150";
    else if ( (jetpt >= 150) && (jetpt < 300) )  sector_string += "150_300";
    else if ( (jetpt >= 300) && (jetpt < 1000) ) sector_string += "300_1000";
  }
  else if ( (taupt > 300) && (taupt < 1000) ) {
    sector_string += "300_1000_jetpt_";

    if ( (jetpt > 0) && (jetpt < 300) )          sector_string += "0_300";
    else if ( (jetpt >= 300) && (jetpt < 1000) ) sector_string += "300_1000";
  }

  double reweight = 0;

  TString hname = "hratio_data_eta_"+eta+"_taupt_jetpt_pass" + sector_string;
  TH2F* h_fake = (TH2F*) fake_file->Get(hname);
  int iBin = h_fake->FindBin(taupt, jetpt);
  SF = h_fake->GetBinContent(iBin);
  if (SF != 1) reweight = SF/(1-SF);

  return reweight;

}



double FakeRate_mumu(double taupt, double jetpt) {
  double SF=0.2;

  TFile* fake_file = new TFile("Reweighting/fakerate.root","R");

  TString sector_string = "_taupt_";

  if (jetpt >= 1000) jetpt = 999;
  if (taupt >= 1000) taupt = 999;

  if ( (taupt > 0) && (taupt < 300) ) {
    if ( (jetpt > 0) && (jetpt < 120) )          sector_string += "0_300_jetpt_0_120";
    else if ( (jetpt >= 120) && (jetpt < 300) )  sector_string += "0_300_jetpt_120_300";
    else if ( (jetpt >= 300) && (jetpt < 1000) ) sector_string += "0_1000_jetpt_300_1000";
  }
  else if ( (taupt > 300) && (taupt < 1000) ) {
    if ( (jetpt > 0) && (jetpt < 300) )          sector_string += "300_1000_jetpt_0_300";
    else if ( (jetpt >= 300) && (jetpt < 1000) ) sector_string += "0_1000_jetpt_300_1000";
  }

  double reweight = 0;

  TString hname = "hratio_data_total_taupt_jetpt_pass" + sector_string;
  TH2F* h_fake = (TH2F*) fake_file->Get(hname);
  int iBin = h_fake->FindBin(taupt, jetpt);
  SF = h_fake->GetBinContent(iBin);
  if (SF != 1) reweight = SF/(1-SF);

  return reweight;

}



pair<double,double> getSF (float mupt, float mueta) {
  //highest pt is 120 GeV
  if (mupt >= 120) mupt = 119;
  TFile* id_file = new TFile("Reweighting/RunBCDEF_SF_ID.root","R");
  TH2F* id_histo = (TH2F*) id_file->Get("NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta");
  int bin_in = id_histo->FindBin(mupt, fabs(mueta));
  double id_sf = id_histo->GetBinContent(bin_in);
  id_file->Close();

  TFile* iso_file = new TFile("Reweighting/RunBCDEF_SF_ISO.root","R");
  TH2F* iso_histo = (TH2F*) iso_file->Get("NUM_LooseRelTkIso_DEN_TrkHighPtID_pair_newTuneP_probe_pt_abseta");
  bin_in = iso_histo->FindBin(mupt, fabs(mueta));
  double iso_sf = iso_histo->GetBinContent(bin_in);
  iso_file->Close();

  if (id_sf == 0) id_sf = 1.0;
  if (iso_sf == 0) iso_sf = 1.0;

  pair<double, double> SF_pair;
  SF_pair.first =  id_sf;  SF_pair.second =iso_sf;
  return  SF_pair;
}


double GetReweight_highmass(float mu_pt, float mu_eta) {
  //highest pt for trigger is 1200 GeV
  if (mu_pt >= 1200) mu_pt = 1199;
  //scale factor files that need to be open
  TFile* tr_file = new TFile("Reweighting/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root","R");
  TH2F* tr_histo = (TH2F*) tr_file->Get("Mu50_PtEtaBins/pt_abseta_ratio");
  int bin_in = tr_histo->FindBin(mu_pt, fabs(mu_eta));
  double tr_sf = tr_histo->GetBinContent(bin_in);
  tr_file->Close();
  if (tr_sf == 0) tr_sf = 1.0;

  float muID_sf = getSF(mu_pt, mu_eta).first, muIso_sf = getSF(mu_pt, mu_eta).second;

  double weight = tr_sf*muID_sf*muIso_sf;

  return weight;
}


double GetReweight_mumu(float mu1_pt, float mu1_eta, float mu2_pt, float mu2_eta) {
  //scale factor files that need to be open                                                                                                                                                                                                   
  TFile* tr_file = new TFile("Reweighting/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root","R");
  TH2F* tr_data = (TH2F*) tr_file->Get("IsoMu27_PtEtaBins/efficienciesDATA/pt_abseta_DATA");
  TH2F* tr_MC = (TH2F*) tr_file->Get("IsoMu27_PtEtaBins/efficienciesMC/pt_abseta_MC");
  //Eff. of the trigger: COMPLEMENTARY of the prob. that NONE of the two muons will trigger                                                                                                                                                   

  int bin_in = tr_data->FindBin(mu1_pt, fabs(mu1_eta));
  double mu1_eff_data = tr_data->GetBinContent(bin_in);
  bin_in = tr_data->FindBin(mu2_pt, fabs(mu2_eta));
  double mu2_eff_data = tr_data->GetBinContent(bin_in);
  double tr_eff_data = 1 - (1 - mu1_eff_data)*(1 - mu2_eff_data);
  if (tr_eff_data == 0) tr_eff_data = 1.0;

  bin_in = tr_MC->FindBin(mu1_pt, fabs(mu1_eta));
  double mu1_eff_MC = tr_MC->GetBinContent(bin_in);
  bin_in = tr_data->FindBin(mu2_pt, fabs(mu2_eta));
  double mu2_eff_MC = tr_MC->GetBinContent(bin_in);
  double tr_eff_MC = 1 - (1 - mu1_eff_MC)*(1 - mu2_eff_MC);
  tr_file->Close();
  if (tr_eff_MC == 0) tr_eff_MC = 1.0;

  double tr_sf = tr_eff_data/tr_eff_MC;

  float mu1ID_sf = getSF(mu1_pt, mu1_eta).first, mu1Iso_sf = getSF(mu1_pt, mu1_eta).second;
  float mu2ID_sf = getSF(mu2_pt, mu2_eta).first, mu2Iso_sf = getSF(mu2_pt, mu2_eta).second;


  double weight=tr_sf*mu1ID_sf*mu1Iso_sf*mu2ID_sf*mu2Iso_sf;

  return weight;
}


