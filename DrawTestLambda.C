#include "TFile.h"
#include "TDirectoryFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"


void DrawTestLambda() {
  
  gStyle -> SetOptStat(0);

  TFile *f = new TFile("lllll.root");
  TDirectoryFile *dir = (TDirectoryFile*)f->Get("MyTask");
  TList * list = (TList*)dir->Get("ResultsList");

    
  //h_pt_lambda_mc
  //h_pt_antilambda_mc

  //h_pt_lambda_rc
  //h_pt_antilambda_rc

  //h_pt_lambda_rc_real
  //h_pt_antilambda_rc_real

  //h_inv_mass_lambda_rc
  //h_inv_mass_antilambda_rc

  TH1D* h_pt_lambda_mc = (TH1D*)list->FindObject("h_pt_lambda_mc");
  TH1D* h_pt_antilambda_mc = (TH1D*)list->FindObject("h_pt_antilambda_mc");

  TH1D* h_pt_lambda_rc = (TH1D*)list->FindObject("h_pt_lambda_rc");
  TH1D* h_pt_antilambda_rc = (TH1D*)list->FindObject("h_pt_antilambda_rc");

  TH1D* h_pt_lambda_rc_real = (TH1D*)list->FindObject("h_pt_lambda_rc_real");
  TH1D* h_pt_antilambda_rc_real = (TH1D*)list->FindObject("h_pt_antilambda_rc_real");

  TH1D* h_mass_lambda_rc = (TH1D*)list->FindObject("h_inv_mass_lambda_rc");
  TH1D* h_mass_antilambda_rc = (TH1D*)list->FindObject("h_inv_mass_antilambda_rc");
  
  
  //0~0.5, 0.6,0.7,0.8,0.9,1.0,1.1....3.8,3.9,4.0,4.5,5.0,5.5,6.5,8.0,10.0
  //double xbins[] = {0,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9,3.1,3.3,3.5,3.7,3.9,4.0,4.5,5.0,5.5,6.5,8.0,10.0,12,14,16,20};
  //0~0.5, 0.6,0.8,1.0,1.2....3.8,3.9,4.0,6.8.0,10.0
  double xbins[] = {0,0.5,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.4,2.8,3.2,3.6,4.0,6.0,8,10.0,15,20};
  double nBins = sizeof(xbins)/sizeof(double) - 1;


  //double xbins[] = {0,0.4,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.5,5.0,5.5,6.5,8.0,10.0};



  TH1D* h_pt_lambda_mc_rebin =  (TH1D*)h_pt_lambda_mc->Rebin(nBins, "h_pt_lambda_mc_rebin",xbins);
  TH1D* h_pt_antilambda_mc_rebin =  (TH1D*)h_pt_antilambda_mc->Rebin(nBins, "h_pt_antilambda_mc_rebin",xbins);

  TH1D* h_pt_lambda_rc_rebin =  (TH1D*)h_pt_lambda_rc->Rebin(nBins, "h_pt_lambda_rc_rebin",xbins);
  TH1D* h_pt_antilambda_rc_rebin =  (TH1D*)h_pt_antilambda_rc->Rebin(nBins, "h_pt_antilambda_rc_rebin",xbins);

  TH1D* h_pt_lambda_rc_real_rebin =  (TH1D*)h_pt_lambda_rc_real->Rebin(nBins, "h_pt_lambda_rc_real_rebin",xbins);
  TH1D* h_pt_antilambda_rc_real_rebin =  (TH1D*)h_pt_antilambda_rc_real->Rebin(nBins, "h_pt_antilambda_rc_real_rebin",xbins);


  // int nrebin = 8;
  // h_pt_lambda_mc -> Rebin(nrebin);
  // h_pt_antilambda_mc -> Rebin(nrebin);

  // h_pt_lambda_rc -> Rebin(nrebin);
  // h_pt_antilambda_rc -> Rebin(nrebin);

  // h_pt_lambda_rc_real -> Rebin(nrebin);
  // h_pt_antilambda_rc_real -> Rebin(nrebin);

  // h_inv_mass_lambda_rc -> Rebin(nrebin);
  // h_inv_mass_antilambda_rc -> Rebin(nrebin);

  // h_pt_lambda_pos_proton_mc -> Rebin(nrebin);
  // h_pt_lambda_neg_pion_mc -> Rebin(nrebin);

  // h_pt_antilambda_neg_proton_mc -> Rebin(nrebin);
  // h_pt_antilambda_pos_pion_mc -> Rebin(nrebin);

  // h_pt_lambda_pos_proton_rc_real -> Rebin(nrebin);
  // h_pt_lambda_neg_pion_rc_real -> Rebin(nrebin);

  // h_pt_antilambda_neg_proton_rc_real -> Rebin(nrebin);
  // h_pt_antilambda_pos_pion_rc_real -> Rebin(nrebin);


  TH1D* h_eff_pt_lambda = (TH1D*)h_pt_lambda_rc_real->Clone("h_eff_pt_lambda");
  h_eff_pt_lambda->Divide(h_pt_lambda_mc);
  h_eff_pt_lambda->SetLineColor(kRed);

  TH1D* h_eff_pt_antilambda = (TH1D*)h_pt_antilambda_rc_real->Clone("h_eff_pt_antilambda");
  h_eff_pt_antilambda->Divide(h_pt_antilambda_mc);
  h_eff_pt_antilambda->SetLineColor(kBlue);

  TH1D* h_eff_pt_lambda_rebin = (TH1D*)h_pt_lambda_rc_real_rebin->Clone("h_eff_pt_lambda");
  h_eff_pt_lambda_rebin->Divide(h_pt_lambda_mc_rebin);
  h_eff_pt_lambda_rebin->SetLineColor(kRed);

  TH1D* h_eff_pt_antilambda_rebin = (TH1D*)h_pt_antilambda_rc_real_rebin->Clone("h_eff_pt_antilambda");
  h_eff_pt_antilambda_rebin->Divide(h_pt_antilambda_mc_rebin);
  h_eff_pt_antilambda_rebin->SetLineColor(kBlue);


  // TH1D* h_eff_pt_lamhda_pos_proton = (TH1D*)h_pt_lambda_pos_proton_rc_real->Clone("h_eff_pt_lamhda_pos_proton");
  // h_eff_pt_lamhda_pos_proton->Divide(h_pt_lambda_pos_proton_mc);
  // h_eff_pt_lamhda_pos_proton->SetLineColor(kRed);

  // TH1D* h_eff_pt_lamhda_neg_pion = (TH1D*)h_pt_lambda_neg_pion_rc_real->Clone("h_eff_pt_lamhda_neg_pion");
  // h_eff_pt_lamhda_neg_pion->Divide(h_pt_lambda_neg_pion_mc);
  // h_eff_pt_lamhda_neg_pion->SetLineColor(kBlue);

  TH2D* dummy = new TH2D("dummy","LHC15o AOD;#it{p}_{T} (GeV/#it{c});Efficiency of #Lambda",1,0,20,1,0,0.5);

  TCanvas* c1 = new TCanvas("c1","c1",800,600);
  //c1->Divide(2,1);
  c1->cd(1);
  dummy->Draw();
  h_eff_pt_lambda->Draw("same");
  h_eff_pt_antilambda->Draw("same");
  c1->cd(2);
  // h_eff_pt_lamhda_pos_proton->Draw();
  // h_eff_pt_lamhda_neg_pion->Draw("same");

  // TCanvas* c2 = new TCanvas("c2","c2",800,600);
  // c2->SetLogy();
  // h_pt_antilambda_mc->Draw();
  // h_pt_antilambda_rc->SetLineColor(kOrange);
  // h_pt_antilambda_rc->Draw("same");
  // h_pt_antilambda_rc_real->SetLineColor(kRed);
  // h_pt_antilambda_rc_real->Draw("same");


  //TFile* outputfile = new TFile("efficiency18q.root","RECREATE");

}