#include "TFile.h"
#include "TDirectoryFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStyle.h"

void GetEfficiency(TFile* f) {
  TDirectoryFile *dir = (TDirectoryFile*)f->Get("MyTask");
  TList * list = (TList*)dir->Get("ResultsList");

  TH1D* h_pt_pos_hadron_mc = (TH1D*)list->FindObject("h_pt_pos_hadron_mc");
  TH1D* h_pt_neg_hadron_mc = (TH1D*)list->FindObject("h_pt_neg_hadron_mc");

  TH1D* h_pt_pos_proton_mc = (TH1D*)list->FindObject("h_pt_pos_proton_mc");
  TH1D* h_pt_neg_proton_mc = (TH1D*)list->FindObject("h_pt_neg_proton_mc");

  TH1D* h_pt_pos_hadron_rc = (TH1D*)list->FindObject("h_pt_pos_hadron_rc");
  TH1D* h_pt_neg_hadron_rc = (TH1D*)list->FindObject("h_pt_neg_hadron_rc");

  TH1D* h_pt_pos_proton_rc = (TH1D*)list->FindObject("h_pt_pos_proton_rc");
  TH1D* h_pt_neg_proton_rc = (TH1D*)list->FindObject("h_pt_neg_proton_rc");

  TH1D* h_pt_pos_proton_rc_real = (TH1D*)list->FindObject("h_pt_pos_proton_rc_real");
  TH1D* h_pt_neg_proton_rc_real = (TH1D*)list->FindObject("h_pt_neg_proton_rc_real");

  double xbins[] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,
                    1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,
                    2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,
                    3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,
                    4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,
                    5.0};

  TH1D* h_pt_pos_hadron_mc_rebin = (TH1D*)h_pt_pos_hadron_mc->Rebin(50,"h_pt_pos_hadron_mc_rebin",xbins);
  TH1D* h_pt_neg_hadron_mc_rebin = (TH1D*)h_pt_neg_hadron_mc->Rebin(50,"h_pt_neg_hadron_mc_rebin",xbins);
  TH1D* h_pt_pos_proton_mc_rebin = (TH1D*)h_pt_pos_proton_mc->Rebin(50,"h_pt_pos_proton_mc_rebin",xbins);
  TH1D* h_pt_neg_proton_mc_rebin = (TH1D*)h_pt_neg_proton_mc->Rebin(50,"h_pt_neg_proton_mc_rebin",xbins);

  TH1D* h_pt_pos_hadron_rc_rebin = (TH1D*)h_pt_pos_hadron_rc->Rebin(50,"h_pt_pos_hadron_rc_rebin",xbins);
  TH1D* h_pt_neg_hadron_rc_rebin = (TH1D*)h_pt_neg_hadron_rc->Rebin(50,"h_pt_neg_hadron_rc_rebin",xbins);
  TH1D* h_pt_pos_proton_rc_rebin = (TH1D*)h_pt_pos_proton_rc->Rebin(50,"h_pt_pos_proton_rc_rebin",xbins);
  TH1D* h_pt_neg_proton_rc_rebin = (TH1D*)h_pt_neg_proton_rc->Rebin(50,"h_pt_neg_proton_rc_rebin",xbins);


  TH1D* h_pt_pos_proton_rc_real_rebin = (TH1D*) h_pt_pos_proton_rc_real->Rebin(50,"h_pt_pos_proton_rc_real_rebin",xbins);
  TH1D* h_pt_neg_proton_rc_real_rebin = (TH1D*) h_pt_neg_proton_rc_real->Rebin(50,"h_pt_neg_proton_rc_real_rebin",xbins);

  TH1D* h_eff_pos_hadron_rebin = (TH1D*)h_pt_pos_hadron_rc_rebin->Clone("h_eff_pos_hadron");
  h_eff_pos_hadron_rebin->Divide(h_pt_pos_hadron_mc_rebin);
  TH1D* h_eff_neg_hadron_rebin = (TH1D*)h_pt_neg_hadron_rc_rebin->Clone("h_eff_neg_hadron");
  h_eff_neg_hadron_rebin->Divide(h_pt_neg_hadron_mc_rebin);
  TH1D* h_eff_pos_proton_rebin = (TH1D*)h_pt_pos_proton_rc_real_rebin->Clone("h_eff_pos_proton");
  h_eff_pos_proton_rebin->Divide(h_pt_pos_proton_mc_rebin);
  TH1D* h_eff_neg_proton_rebin = (TH1D*)h_pt_neg_proton_rc_real_rebin->Clone("h_eff_neg_proton");
  h_eff_neg_proton_rebin->Divide(h_pt_neg_proton_mc_rebin);
  TH1D* h_pur_pos_proton_rebin = (TH1D*)h_pt_pos_proton_rc_real_rebin->Clone("h_eff_pos_proton_real");
  h_pur_pos_proton_rebin->Divide(h_pt_pos_proton_rc_rebin);
  TH1D* h_pur_neg_proton_rebin = (TH1D*)h_pt_neg_proton_rc_real_rebin->Clone("h_eff_neg_proton_real");
  h_pur_neg_proton_rebin->Divide(h_pt_neg_proton_rc_rebin);

  h_eff_pos_hadron_rebin->SetLineColor(kRed);
  h_eff_neg_hadron_rebin->SetLineColor(kBlue);
  h_eff_pos_proton_rebin->SetLineColor(kRed);
  h_eff_neg_proton_rebin->SetLineColor(kBlue);
  h_pur_pos_proton_rebin->SetLineColor(kRed);
  h_pur_neg_proton_rebin->SetLineColor(kBlue);

  h_eff_pos_hadron_rebin->SetMarkerColor(kRed);
  h_eff_neg_hadron_rebin->SetMarkerColor(kBlue);
  h_eff_pos_proton_rebin->SetMarkerColor(kRed);
  h_eff_neg_proton_rebin->SetMarkerColor(kBlue);
  h_pur_pos_proton_rebin->SetMarkerColor(kRed);
  h_pur_neg_proton_rebin->SetMarkerColor(kBlue);

  h_eff_pos_hadron_rebin->SetMarkerStyle(kOpenCircle);
  h_eff_neg_hadron_rebin->SetMarkerStyle(kOpenCircle);
  h_eff_pos_proton_rebin->SetMarkerStyle(kOpenCircle);
  h_eff_neg_proton_rebin->SetMarkerStyle(kOpenCircle);
  h_pur_pos_proton_rebin->SetMarkerStyle(kOpenCircle);
  h_pur_neg_proton_rebin->SetMarkerStyle(kOpenCircle);

  h_eff_pos_hadron_rebin->SetMarkerSize(1);
  h_eff_neg_hadron_rebin->SetMarkerSize(1);
  h_eff_pos_proton_rebin->SetMarkerSize(1);
  h_eff_neg_proton_rebin->SetMarkerSize(1);
  h_pur_pos_proton_rebin->SetMarkerSize(1);
  h_pur_neg_proton_rebin->SetMarkerSize(1);


  TCanvas *c = new TCanvas("c", "c", 1000, 600);
  c->Divide(2,1);
  c->cd(1);
  h_eff_pos_hadron_rebin->SetTitle("Efficiency");
  h_eff_pos_hadron_rebin->Draw("same");
  h_eff_neg_hadron_rebin->Draw("same");
  h_eff_pos_proton_rebin->Draw("same");
  h_eff_neg_proton_rebin->Draw("same");
  c->cd(2);
  h_pur_pos_proton_rebin->SetTitle("Purity");
  h_pur_pos_proton_rebin->GetYaxis()->SetRangeUser(0.4,1.1);
  h_pur_pos_proton_rebin->Draw("same");
  h_pur_neg_proton_rebin->Draw("same");

  TList* outlist = new TList();
  outlist->Add(h_eff_pos_hadron_rebin);
  outlist->Add(h_eff_neg_hadron_rebin);
  outlist->Add(h_eff_pos_proton_rebin);
  outlist->Add(h_eff_neg_proton_rebin);


  TFile* outputfile = new TFile("efficiency18r.root","RECREATE");
  outputfile->cd();
  outlist->Write("fListNUE",TObject::kSingleKey);
}


void MakeEffFileHadronProton() {
  gStyle->SetOptStat(0);
  TFile* file18r = TFile::Open("18r_AnalysisResults.root");
  TFile* file18q = TFile::Open("18q_AnalysisResults.root");

  GetEfficiency(file18r);
  //GetEfficiency(file18q);
}