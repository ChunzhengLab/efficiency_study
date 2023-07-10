#include "TFile.h"
#include "TDirectoryFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <iostream>

void DrawTest() {
  TString dataset = "18q";
  TFile *f = new TFile(dataset+"_AnalysisResults.root");
  if (!f) {
    printf("ERROR: file not found\n");
    return;
  }
  TDirectoryFile *dir = (TDirectoryFile*)f->Get("MyTask");
  if (!dir) {
    printf("ERROR: directory not found\n");
    return;
  }
  TList * list = (TList*)dir->Get("ResultsList");
  if (!list) {
    printf("ERROR: list not found\n");
    return;
  }

  //hadron
  TH1D* h_eta_poshadron_mc = (TH1D*)list->FindObject("h_eta_poshadron_mc");
  if (!h_eta_poshadron_mc) {
    printf("ERROR: h_eta_poshadron_mc not found\n");
    return;
  }
  TH1D* h_eta_neghadron_mc = (TH1D*)list->FindObject("h_eta_neghadron_mc");
  if (!h_eta_neghadron_mc) {
    printf("ERROR: h_eta_neghadron_mc not found\n");
    return;
  }
  TH1D* h_eta_poshadron_rc = (TH1D*)list->FindObject("h_eta_poshadron_rc");
  if (!h_eta_poshadron_rc) {
    printf("ERROR: h_eta_poshadron_rc not found\n");
    return;
  }
  TH1D* h_eta_neghadron_rc = (TH1D*)list->FindObject("h_eta_neghadron_rc");
  if (!h_eta_neghadron_rc) {
    printf("ERROR: h_eta_neghadron_rc not found\n");
    return;
  }

  TH1D* h_pt_poshadron_mc = (TH1D*)list->FindObject("h_pt_poshadron_mc");
  if (!h_pt_poshadron_mc) {
    printf("ERROR: h_pt_poshadron_mc not found\n");
    return;
  }
  TH1D* h_pt_neghadron_mc = (TH1D*)list->FindObject("h_pt_neghadron_mc");
  if (!h_pt_neghadron_mc) {
    printf("ERROR: h_pt_neghadron_mc not found\n");
    return;
  }
  TH1D* h_pt_poshadron_rc = (TH1D*)list->FindObject("h_pt_poshadron_rc");
  if (!h_pt_poshadron_rc) {
    printf("ERROR: h_pt_poshadron_rc not found\n");
    return;
  }
  TH1D* h_pt_neghadron_rc = (TH1D*)list->FindObject("h_pt_neghadron_rc");
  if (!h_pt_neghadron_rc) {
    printf("ERROR: h_pt_neghadron_rc not found\n");
    return;
  }

  //proton
  TH1D* h_eta_proton_mc = (TH1D*)list->FindObject("h_eta_proton_mc");
  if (!h_eta_proton_mc) {
    printf("ERROR: h_eta_proton_mc not found\n");
    return;
  }
  TH1D* h_eta_antiproton_mc = (TH1D*)list->FindObject("h_eta_antiproton_mc");
  if (!h_eta_antiproton_mc) {
    printf("ERROR: h_eta_antiproton_mc not found\n");
    return;
  }
  TH1D* h_eta_proton_rc = (TH1D*)list->FindObject("h_eta_proton_rc");
  if (!h_eta_proton_rc) {
    printf("ERROR: h_eta_proton_rc not found\n");
    return;
  }
  TH1D* h_eta_antiproton_rc = (TH1D*)list->FindObject("h_eta_antiproton_rc");
  if (!h_eta_antiproton_rc) {
    printf("ERROR: h_eta_antiproton_rc not found\n");
    return;
  }
  TH1D* h_eta_proton_rc_real = (TH1D*)list->FindObject("h_eta_proton_rc_real");
  if (!h_eta_proton_rc_real) {
    printf("ERROR: h_eta_proton_rc_real not found\n");
    return;
  }
  TH1D* h_eta_antiproton_rc_real = (TH1D*)list->FindObject("h_eta_antiproton_rc_real");
  if (!h_eta_antiproton_rc_real) {
    printf("ERROR: h_eta_antiproton_rc_real not found\n");
    return;
  }

  TH1D* h_pt_proton_mc = (TH1D*)list->FindObject("h_pt_proton_mc");
  if (!h_pt_proton_mc) {
    printf("ERROR: h_pt_proton_mc not found\n");
    return;
  }
  TH1D* h_pt_antiproton_mc = (TH1D*)list->FindObject("h_pt_antiproton_mc");
  if (!h_pt_antiproton_mc) {
    printf("ERROR: h_pt_antiproton_mc not found\n");
    return;
  }
  TH1D* h_pt_proton_rc = (TH1D*)list->FindObject("h_pt_proton_rc");
  if (!h_pt_proton_rc) {
    printf("ERROR: h_pt_proton_rc not found\n");
    return;
  }
  TH1D* h_pt_antiproton_rc = (TH1D*)list->FindObject("h_pt_antiproton_rc");
  if (!h_pt_antiproton_rc) {
    printf("ERROR: h_pt_antiproton_rc not found\n");
    return;
  }
  TH1D* h_pt_proton_rc_real = (TH1D*)list->FindObject("h_pt_proton_rc_real");
  if (!h_pt_proton_rc_real) {
    printf("ERROR: h_pt_proton_rc_real not found\n");
    return;
  }
  TH1D* h_pt_antiproton_rc_real = (TH1D*)list->FindObject("h_pt_antiproton_rc_real");
  if (!h_pt_antiproton_rc_real) {
    printf("ERROR: h_pt_antiproton_rc_real not found\n");
    return;
  }

  TH1D* h_pt_lambda_mc = (TH1D*)list->FindObject("h_pt_lambda_mc");
  if (!h_pt_lambda_mc) {
    printf("ERROR: h_pt_lambda_mc not found\n");
    return;
  }
  TH1D* h_pt_antilambda_mc = (TH1D*)list->FindObject("h_pt_antilambda_mc");
  if (!h_pt_antilambda_mc) {
    printf("ERROR: h_pt_antilambda_mc not found\n");
    return;
  }

  TH1D* h_pt_lambda_rc = (TH1D*)list->FindObject("h_pt_lambda_rc");
  if (!h_pt_lambda_rc) {
    printf("ERROR: h_pt_lambda_rc not found\n");
    return;
  }
  TH1D* h_pt_antilambda_rc = (TH1D*)list->FindObject("h_pt_antilambda_rc");
  if (!h_pt_antilambda_rc) {
    printf("ERROR: h_pt_antilambda_rc not found\n");
    return;
  }

  TH1D* h_pt_lambda_rc_real = (TH1D*)list->FindObject("h_pt_lambda_rc_real");
  if (!h_pt_lambda_rc_real) {
    printf("ERROR: h_pt_lambda_rc_real not found\n");
    return;
  }
  TH1D* h_pt_antilambda_rc_real = (TH1D*)list->FindObject("h_pt_antilambda_rc_real");
  if (!h_pt_antilambda_rc_real) {
    printf("ERROR: h_pt_antilambda_rc_real not found\n");
    return;
  }
  cout<<"load data done"<<endl;

  double xbins_hadron[] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,
                           1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,
                           2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,
                           3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,
                           4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,
                           5.0};
  double nBins_hadron = sizeof(xbins_hadron)/sizeof(double) - 1;

  double xbins_lambda[] = {0,0.5,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.4,2.8,3.2,3.6,4.0,4.5,5.0,5.5,6.0,6.5,7.0,8.0,10.0};
  double nBins_lambda = sizeof(xbins_lambda)/sizeof(double) - 1;

  //hadron
  TH1D* h_pt_poshadron_mc_rebin = (TH1D*)h_pt_poshadron_mc -> Rebin(nBins_hadron,"h_pt_poshadron_mc_rebin",xbins_hadron);
  TH1D* h_pt_neghadron_mc_rebin = (TH1D*)h_pt_neghadron_mc -> Rebin(nBins_hadron,"h_pt_neghadron_mc_rebin",xbins_hadron);
  TH1D* h_pt_poshadron_rc_rebin = (TH1D*)h_pt_poshadron_rc -> Rebin(nBins_hadron,"h_pt_poshadron_rc_rebin",xbins_hadron);
  TH1D* h_pt_neghadron_rc_rebin = (TH1D*)h_pt_neghadron_rc -> Rebin(nBins_hadron,"h_pt_neghadron_rc_rebin",xbins_hadron);
  TH1D* h_eff_pt_poshadron_rebin = (TH1D*)h_pt_poshadron_rc_rebin->Clone("h_eff_pt_poshadron_rebin");
  h_eff_pt_poshadron_rebin->Divide(h_pt_poshadron_mc_rebin);
  TH1D* h_eff_pt_neghadron_rebin = (TH1D*)h_pt_neghadron_rc_rebin->Clone("h_eff_pt_neghadron_rebin");
  h_eff_pt_neghadron_rebin->Divide(h_pt_neghadron_mc_rebin);
  cout<<"hadron efficiency done"<<endl;

  //proton
  TH1D* h_pt_proton_mc_rebin = (TH1D*)h_pt_proton_mc -> Rebin(nBins_hadron,"h_pt_proton_mc_rebin",xbins_hadron);
  TH1D* h_pt_antiproton_mc_rebin = (TH1D*)h_pt_antiproton_mc -> Rebin(nBins_hadron,"h_pt_antiproton_mc_rebin",xbins_hadron);
  TH1D* h_pt_proton_rc_real_rebin = (TH1D*)h_pt_proton_rc_real -> Rebin(nBins_hadron,"h_pt_proton_rc_real_rebin",xbins_hadron);
  TH1D* h_pt_antiproton_rc_real_rebin = (TH1D*)h_pt_antiproton_rc_real -> Rebin(nBins_hadron,"h_pt_antiproton_rc_real_rebin",xbins_hadron);
  TH1D* h_eff_pt_proton_rebin = (TH1D*)h_pt_proton_rc_real_rebin->Clone("h_eff_pt_proton_rebin");
  h_eff_pt_proton_rebin->Divide(h_pt_proton_mc_rebin);
  TH1D* h_eff_pt_antiproton_rebin = (TH1D*)h_pt_antiproton_rc_real_rebin->Clone("h_eff_pt_antiproton_rebin");
  h_eff_pt_antiproton_rebin->Divide(h_pt_antiproton_mc_rebin);
  cout<<"proton efficiency done"<<endl;

  //lambda
  TH1D* h_pt_lambda_mc_rebin =  (TH1D*)h_pt_lambda_mc->Rebin(nBins_lambda, "h_pt_lambda_mc_rebin",xbins_lambda);
  TH1D* h_pt_antilambda_mc_rebin =  (TH1D*)h_pt_antilambda_mc->Rebin(nBins_lambda, "h_pt_antilambda_mc_rebin",xbins_lambda);
  TH1D* h_pt_lambda_rc_real_rebin =  (TH1D*)h_pt_lambda_rc_real->Rebin(nBins_lambda, "h_pt_lambda_rc_real_rebin",xbins_lambda);
  TH1D* h_pt_antilambda_rc_real_rebin =  (TH1D*)h_pt_antilambda_rc_real->Rebin(nBins_lambda, "h_pt_antilambda_rc_real_rebin",xbins_lambda);
  TH1D* h_eff_pt_lambda_rebin = (TH1D*)h_pt_lambda_rc_real_rebin->Clone("h_eff_pt_lambda");
  h_eff_pt_lambda_rebin->Divide(h_pt_lambda_mc_rebin);
  TH1D* h_eff_pt_antilambda_rebin = (TH1D*)h_pt_antilambda_rc_real_rebin->Clone("h_eff_pt_antilambda");
  h_eff_pt_antilambda_rebin->Divide(h_pt_antilambda_mc_rebin);
  cout<<"lambda efficiency done"<<endl;


  // TH1D* h_pur_pt_proton_rebin = (TH1D*)h_pt_proton_rc_real_rebin->Clone("h_pur_pt_proton_rebin");
  // h_pur_pt_proton_rebin->Divide(h_pt_proton_rc_rebin);
  // TH1D* h_pur_pt_antiproton_rebin = (TH1D*)h_pt_antiproton_rc_real_rebin->Clone("h_pur_pt_antiproton_rebin");
  // h_pur_pt_antiproton_rebin->Divide(h_pt_antiproton_rc_rebin);
  //set color
  h_eff_pt_poshadron_rebin->SetLineColor(kRed);
  h_eff_pt_neghadron_rebin->SetLineColor(kBlue);
  h_eff_pt_proton_rebin->SetLineColor(kRed);
  h_eff_pt_antiproton_rebin->SetLineColor(kBlue);
  h_eff_pt_lambda_rebin->SetLineColor(kRed);
  h_eff_pt_antilambda_rebin->SetLineColor(kBlue);
  // h_pur_pt_proton_rebin->SetLineColor(kRed);
  // h_pur_pt_antiproton_rebin->SetLineColor(kBlue);

  TCanvas *c = new TCanvas("c", "c", 1000, 1000);
  c->Divide(2,1);
  c->cd(1);
  h_eff_pt_poshadron_rebin->Draw("same");
  h_eff_pt_neghadron_rebin->Draw("same");
  h_eff_pt_proton_rebin->Draw("same");
  h_eff_pt_antiproton_rebin->Draw("same");
  h_eff_pt_lambda_rebin->Draw("same");
  h_eff_pt_antilambda_rebin->Draw("same");

  c->cd(2);
  //h_pur_pt_proton_rebin->Draw("same");
  //h_pur_pt_antiproton_rebin->Draw("same");

  TFile* f_out = new TFile(Form("efficiency%s.root",dataset.Data()),"recreate");
  TList* list_out = new TList();
  h_eff_pt_poshadron_rebin->SetName("h_eff_pos_hadron");
  h_eff_pt_poshadron_rebin->SetXTitle("p_{T} (GeV/c)");
  h_eff_pt_poshadron_rebin->SetYTitle("efficiency h^{+}");

  h_eff_pt_neghadron_rebin->SetName("h_eff_neg_hadron");
  h_eff_pt_neghadron_rebin->SetXTitle("p_{T} (GeV/c)");
  h_eff_pt_neghadron_rebin->SetYTitle("efficiency h^{-}");

  h_eff_pt_proton_rebin->SetName("h_eff_pos_proton");
  h_eff_pt_proton_rebin->SetXTitle("p_{T} (GeV/c)");
  h_eff_pt_proton_rebin->SetYTitle("efficiency p");

  h_eff_pt_antiproton_rebin->SetName("h_eff_neg_proton");
  h_eff_pt_antiproton_rebin->SetXTitle("p_{T} (GeV/c)");
  h_eff_pt_antiproton_rebin->SetYTitle("efficiency #bar{p}");

  h_eff_pt_lambda_rebin->SetName("h_eff_lambda");
  h_eff_pt_antilambda_rebin->SetXTitle("p_{T} (GeV/c)");
  h_eff_pt_antilambda_rebin->SetYTitle("efficiency #bar{#Lambda}");


  h_eff_pt_antilambda_rebin->SetName("h_eff_antilambda");
  h_eff_pt_antilambda_rebin->SetXTitle("p_{T} (GeV/c)");
  h_eff_pt_antilambda_rebin->SetYTitle("efficiency #bar{#Lambda}");


  list_out->Add(h_eff_pt_poshadron_rebin);
  list_out->Add(h_eff_pt_neghadron_rebin);
  list_out->Add(h_eff_pt_proton_rebin);
  list_out->Add(h_eff_pt_antiproton_rebin);
  list_out->Add(h_eff_pt_lambda_rebin);
  list_out->Add(h_eff_pt_antilambda_rebin);
  list_out->Write("fListNUE",TObject::kSingleKey);
  f_out->Close();
}