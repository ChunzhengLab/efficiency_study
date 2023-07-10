#include <sys/time.h>

#include <cstdlib>
#include <iostream>
// ROOT classes
#include "TChain.h"
#include "TComplex.h"
#include "TExMap.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TList.h"
#include "TMath.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TProfile3D.h"
#include "TRandom3.h"
#include "TTree.h"
// Alice analysis base class
#include "AliAnalysisTaskSE.h"
// Alice analysis additional classes
#include "AliAnalysisManager.h"
#include "AliInputEventHandler.h"
// Alice AOD classes
#include "AliAODEvent.h"
#include "AliAODHandler.h"
#include "AliAODInputHandler.h"
#include "AliAODVZERO.h"
#include "AliAODVertex.h"
// Alice classes
#include "AliAnalysisUtils.h"
#include "AliCentrality.h"
#include "AliEventplane.h"
#include "AliMultSelection.h"
// Alice MC classes
#include "AliAODMCParticle.h"
#include "AliMCEvent.h"
#include "AliMCEventHandler.h"
// Alice "V" classes
#include "AliVEvent.h"
#include "AliVParticle.h"
#include "AliVVZERO.h"
#include "AliVVertex.h"
// Alice PID classes
#include "AliAODPid.h"
#include "AliAODpidUtil.h"
#include "AliAnalysisTaskMyTaskMyMCLambda.h"
#include "AliPID.h"
#include "AliPIDCombined.h"
#include "AliPIDResponse.h"

using std::cout;
using std::endl;

ClassImp(AliAnalysisTaskMyTaskMyMCLambda);

//---------------------------------------------------
AliAnalysisTaskMyTaskMyMCLambda::AliAnalysisTaskMyTaskMyMCLambda():
  AliAnalysisTaskSE(),
  fAOD(nullptr),
  fPID(nullptr),
  fMultSel(nullptr),
  fVtx(nullptr),
  fEventCuts(0)
{
  for (int i = 0; i < 3; i++) fVertex[i] = 0;

  fOutputList = nullptr;
  //hadron
  h_eta_poshadron_mc = nullptr;
  h_eta_neghadron_mc = nullptr;
  h_eta_poshadron_rc = nullptr;
  h_eta_neghadron_rc = nullptr;

  h_pt_poshadron_mc = nullptr;
  h_pt_neghadron_mc = nullptr;
  h_pt_poshadron_rc = nullptr;
  h_pt_neghadron_rc = nullptr;

  //proton
  h_eta_proton_mc = nullptr;
  h_eta_antiproton_mc = nullptr;
  h_eta_proton_rc = nullptr;
  h_eta_antiproton_rc = nullptr;
  h_eta_proton_rc_real = nullptr;
  h_eta_antiproton_rc_real = nullptr;

  h_pt_proton_mc = nullptr;
  h_pt_antiproton_mc = nullptr;
  h_pt_proton_rc = nullptr;
  h_pt_antiproton_rc = nullptr;
  h_pt_proton_rc_real = nullptr;
  h_pt_antiproton_rc_real = nullptr;

  //lambda
  h_rap_lambda_mc = nullptr;
  h_rap_antilambda_mc = nullptr;
  h_rap_lambda_rc = nullptr;
  h_rap_antilambda_rc = nullptr;
  h_rap_lambda_rc_real = nullptr;
  h_rap_antilambda_rc_real = nullptr;

  h_pt_lambda_mc = nullptr;
  h_pt_antilambda_mc = nullptr;
  h_pt_lambda_rc = nullptr;
  h_pt_antilambda_rc = nullptr;
  h_pt_lambda_rc_real = nullptr;
  h_pt_antilambda_rc_real = nullptr;

  h_mass_lambda_rc = nullptr;
  h_mass_antilambda_rc = nullptr;
  h_mass_lambda_rc_real = nullptr;
  h_mass_antilambda_rc_real = nullptr;
}

//---------------------------------------------------
AliAnalysisTaskMyTaskMyMCLambda::AliAnalysisTaskMyTaskMyMCLambda(const char *name) :
  AliAnalysisTaskSE(name),
  fAOD(nullptr),
  fPID(nullptr),
  fMultSel(nullptr),
  fVtx(nullptr),
  fEventCuts(0)
{
  for (int i = 0; i < 3; i++) fVertex[i] = 0;

  fOutputList = nullptr;
  //hadron
  h_eta_poshadron_mc = nullptr;
  h_eta_neghadron_mc = nullptr;
  h_eta_poshadron_rc = nullptr;
  h_eta_neghadron_rc = nullptr;

  h_pt_poshadron_mc = nullptr;
  h_pt_neghadron_mc = nullptr;
  h_pt_poshadron_rc = nullptr;
  h_pt_neghadron_rc = nullptr;

  //proton
  h_eta_proton_mc = nullptr;
  h_eta_antiproton_mc = nullptr;
  h_eta_proton_rc = nullptr;
  h_eta_antiproton_rc = nullptr;
  h_eta_proton_rc_real = nullptr;
  h_eta_antiproton_rc_real = nullptr;

  h_pt_proton_mc = nullptr;
  h_pt_antiproton_mc = nullptr;
  h_pt_proton_rc = nullptr;
  h_pt_antiproton_rc = nullptr;
  h_pt_proton_rc_real = nullptr;
  h_pt_antiproton_rc_real = nullptr;

  //lambda
  h_rap_lambda_mc = nullptr;
  h_rap_antilambda_mc = nullptr;
  h_rap_lambda_rc = nullptr;
  h_rap_antilambda_rc = nullptr;
  h_rap_lambda_rc_real = nullptr;
  h_rap_antilambda_rc_real = nullptr;

  h_pt_lambda_mc = nullptr;
  h_pt_antilambda_mc = nullptr;
  h_pt_lambda_rc = nullptr;
  h_pt_antilambda_rc = nullptr;
  h_pt_lambda_rc_real = nullptr;
  h_pt_antilambda_rc_real = nullptr;

  h_mass_lambda_rc = nullptr;
  h_mass_antilambda_rc = nullptr;
  h_mass_lambda_rc_real = nullptr;
  h_mass_antilambda_rc_real = nullptr;

  DefineInput(0, TChain::Class());
  DefineOutput(1, TList::Class());
}

//---------------------------------------------------
AliAnalysisTaskMyTaskMyMCLambda::~AliAnalysisTaskMyTaskMyMCLambda() {
}

//---------------------------------------------------
void AliAnalysisTaskMyTaskMyMCLambda::Terminate(Option_t *) {
}

//---------------------------------------------------
void AliAnalysisTaskMyTaskMyMCLambda::UserCreateOutputObjects() {
  fOutputList = new TList();
  fOutputList->SetName(GetName());
  fOutputList->SetOwner(kTRUE);

  //hadron pt
  h_pt_poshadron_mc = new TH1D("h_pt_poshadron_mc", "h_pt_poshadron_mc", 400, 0, 20);
  h_pt_neghadron_mc = new TH1D("h_pt_neghadron_mc", "h_pt_neghadron_mc", 400, 0, 20);
  h_pt_poshadron_rc = new TH1D("h_pt_poshadron_rc", "h_pt_poshadron_rc", 400, 0, 20);
  h_pt_neghadron_rc = new TH1D("h_pt_neghadron_rc", "h_pt_neghadron_rc", 400, 0, 20);
  fOutputList->Add(h_pt_poshadron_mc);
  fOutputList->Add(h_pt_neghadron_mc);
  fOutputList->Add(h_pt_poshadron_rc);
  fOutputList->Add(h_pt_neghadron_rc);
  //hadron eta
  h_eta_poshadron_mc = new TH1D("h_eta_poshadron_mc", "h_eta_poshadron_mc", 200, -1, 1);
  h_eta_neghadron_mc = new TH1D("h_eta_neghadron_mc", "h_eta_neghadron_mc", 200, -1, 1);
  h_eta_poshadron_rc = new TH1D("h_eta_poshadron_rc", "h_eta_poshadron_rc", 200, -1, 1);
  h_eta_neghadron_rc = new TH1D("h_eta_neghadron_rc", "h_eta_neghadron_rc", 200, -1, 1);
  fOutputList->Add(h_eta_poshadron_mc);
  fOutputList->Add(h_eta_neghadron_mc);
  fOutputList->Add(h_eta_poshadron_rc);
  fOutputList->Add(h_eta_neghadron_rc);

  //proton pt
  h_pt_proton_mc     = new TH1D("h_pt_proton_mc"    , "h_pt_proton_mc",     400, 0, 20);
  h_pt_antiproton_mc = new TH1D("h_pt_antiproton_mc", "h_pt_antiproton_mc", 400, 0, 20);
  h_pt_proton_rc     = new TH1D("h_pt_proton_rc"    , "h_pt_proton_rc",     400, 0, 20);
  h_pt_antiproton_rc = new TH1D("h_pt_antiproton_rc", "h_pt_antiproton_rc", 400, 0, 20);
  h_pt_proton_rc_real     = new TH1D("h_pt_proton_rc_real"    , "h_pt_proton_rc_real",     400, 0, 20);
  h_pt_antiproton_rc_real = new TH1D("h_pt_antiproton_rc_real", "h_pt_antiproton_rc_real", 400, 0, 20);
  fOutputList->Add(h_pt_proton_mc);
  fOutputList->Add(h_pt_antiproton_mc);
  fOutputList->Add(h_pt_proton_rc);
  fOutputList->Add(h_pt_antiproton_rc);
  fOutputList->Add(h_pt_proton_rc_real);
  fOutputList->Add(h_pt_antiproton_rc_real);
  //proton eta
  h_eta_proton_mc     = new TH1D("h_eta_proton_mc"    , "h_eta_proton_mc",     200, -1, 1);
  h_eta_antiproton_mc = new TH1D("h_eta_antiproton_mc", "h_eta_antiproton_mc", 200, -1, 1);
  h_eta_proton_rc     = new TH1D("h_eta_proton_rc"    , "h_eta_proton_rc",     200, -1, 1);
  h_eta_antiproton_rc = new TH1D("h_eta_antiproton_rc", "h_eta_antiproton_rc", 200, -1, 1);
  h_eta_proton_rc_real     = new TH1D("h_eta_proton_rc_real"    , "h_eta_proton_rc_real",     200, -1, 1);
  h_eta_antiproton_rc_real = new TH1D("h_eta_antiproton_rc_real", "h_eta_antiproton_rc_real", 200, -1, 1);
  fOutputList->Add(h_eta_proton_mc);
  fOutputList->Add(h_eta_antiproton_mc);
  fOutputList->Add(h_eta_proton_rc);
  fOutputList->Add(h_eta_antiproton_rc);
  fOutputList->Add(h_eta_proton_rc_real);
  fOutputList->Add(h_eta_antiproton_rc_real);

  //lambda pt
  h_pt_lambda_mc     = new TH1D("h_pt_lambda_mc"    , "h_pt_lambda_mc",     400, 0, 20);
  h_pt_antilambda_mc = new TH1D("h_pt_antilambda_mc", "h_pt_antilambda_mc", 400, 0, 20);
  h_pt_lambda_rc     = new TH1D("h_pt_lambda_rc"    , "h_pt_lambda_rc",     400, 0, 20);
  h_pt_antilambda_rc = new TH1D("h_pt_antilambda_rc", "h_pt_antilambda_rc", 400, 0, 20);
  h_pt_lambda_rc_real     = new TH1D("h_pt_lambda_rc_real"    , "h_pt_lambda_rc_real",     400, 0, 20);
  h_pt_antilambda_rc_real = new TH1D("h_pt_antilambda_rc_real", "h_pt_antilambda_rc_real", 400, 0, 20);
  fOutputList->Add(h_pt_lambda_mc);
  fOutputList->Add(h_pt_antilambda_mc);
  fOutputList->Add(h_pt_lambda_rc);
  fOutputList->Add(h_pt_antilambda_rc);
  fOutputList->Add(h_pt_lambda_rc_real);
  fOutputList->Add(h_pt_antilambda_rc_real);
  //lambda rap
  h_rap_lambda_mc = new TH1D("h_rap_lambda_mc", "h_rap_lambda_mc", 200, -3, 3);
  h_rap_antilambda_mc = new TH1D("h_rap_antilambda_mc", "h_rap_antilambda_mc", 200, -3, 3);
  h_rap_lambda_rc = new TH1D("h_rap_lambda_rc", "h_rap_lambda_rc", 200, -3, 3);
  h_rap_antilambda_rc = new TH1D("h_rap_antilambda_rc", "h_rap_antilambda_rc", 200, -3, 3);
  h_rap_lambda_rc_real = new TH1D("h_rap_lambda_rc_real", "h_rap_lambda_rc_real", 200, -3, 3);
  h_rap_antilambda_rc_real = new TH1D("h_rap_antilambda_rc_real", "h_rap_antilambda_rc_real", 200, -3, 3);
  fOutputList->Add(h_rap_lambda_mc);
  fOutputList->Add(h_rap_antilambda_mc);
  fOutputList->Add(h_rap_lambda_rc);
  fOutputList->Add(h_rap_antilambda_rc);
  fOutputList->Add(h_rap_lambda_rc_real);
  fOutputList->Add(h_rap_antilambda_rc_real);
  //lambda mass
  h_mass_lambda_rc = new TH1D("h_mass_lambda_rc", "h_mass_lambda_rc", 200, 1.08, 1.16);
  h_mass_antilambda_rc = new TH1D("h_mass_antilambda_rc", "h_mass_antilambda_rc", 200, 1.08, 1.16);
  h_mass_lambda_rc_real = new TH1D("h_mass_lambda_rc_real", "h_mass_lambda_rc_real", 200, 1.08, 1.16);
  h_mass_antilambda_rc_real = new TH1D("h_mass_antilambda_rc_real", "h_mass_antilambda_rc_real", 200, 1.08, 1.16);
  fOutputList->Add(h_mass_lambda_rc);
  fOutputList->Add(h_mass_antilambda_rc);
  fOutputList->Add(h_mass_lambda_rc_real);
  fOutputList->Add(h_mass_antilambda_rc_real);

  PostData(1, fOutputList);
}

//---------------------------------------------------
void AliAnalysisTaskMyTaskMyMCLambda::UserExec(Option_t *) {

  fAOD = dynamic_cast<AliAODEvent *>(InputEvent());
  if (!fAOD) {
    AliError(Form("%s: Could not retrieve AOD or ESD event !!", GetName()));
    return;
  }
  fPID = fInputHandler->GetPIDResponse();
  if (!fPID) {
    AliError(Form("%s: Could not get PIDResponse", GetName()));
    return; 
  }
  fMultSel = (AliMultSelection *)InputEvent()->FindListObject("MultSelection");
  if (!fMultSel) {
    AliError(Form("%s: Could not get AliMultSelection", GetName()));
    return;
  }
  if(!fMCEvent){
    AliError(Form("%s: Could not retrieve MC event !!", GetName()));
    return;
  }

  //------------------
  // event-wise
  //------------------
  fVtx = (AliVVertex *)fInputEvent->GetPrimaryVertex();
  if (!fVtx) return;
  fVtx->GetXYZ(fVertex);
  double vzSPD = fInputEvent->GetPrimaryVertexSPD()->GetZ();
  if (fabs(fVertex[2]) > 10) return;
  if (fabs(fVertex[2] - vzSPD) > 0.5) return;

  double centrality = fMultSel->GetMultiplicityPercentile("V0M");
  if (centrality < 0 || centrality > 80) return;
  if(!fEventCuts.AcceptEvent(fInputEvent)) return;

  //------------------
  // Reco V0
  //------------------
  int nV0s = fAOD->GetNumberOfV0s();
  for (int iV0 = 0; iV0 < nV0s; iV0++) {
    AliAODv0* v0 = fAOD->GetV0(iV0);
    // topological cuts
    if (!v0) continue;
    if (!IsGoodV0(v0)) continue;
    AliAODTrack *pTrack = dynamic_cast<AliAODTrack*>(v0->GetDaughter(0));
    AliAODTrack *nTrack = dynamic_cast<AliAODTrack*>(v0->GetDaughter(1));
    if (!pTrack || !nTrack) continue;
    if (pTrack->Charge() * nTrack->Charge() > 0) continue;
    if (!(IsGoodDaughterTrack(nTrack)) || !(IsGoodDaughterTrack(pTrack))) continue;
    
    //reconstruct lambda and anti-lambda
    int code = GetLambdaCode(pTrack,nTrack);
    double mass = -999;
    if (code == 3122)       mass = v0->MassLambda();
    else if (code == -3122) mass = v0->MassAntiLambda();
    else continue;
    if (mass < 1.115683 - 0.02 || mass > 1.115683 + 0.02) continue;
    double rap = v0->RapLambda();
    if (rap < -0.5 || rap > 0.5) continue;
    double pt = v0->Pt();
    if (pt < 0.5) continue;

    // get pdg code from one-to-one MC matching
    AliMCParticle *pMC = (AliMCParticle*)fMCEvent->GetTrack(abs(pTrack->GetLabel()));
    AliMCParticle *nMC = (AliMCParticle*)fMCEvent->GetTrack(abs(nTrack->GetLabel()));
    if (!pMC || !nMC) continue;
    if (pMC->GetMother() != nMC->GetMother()) continue;
    int v0MotherLabel = pMC->GetMother();
    if (v0MotherLabel <= 0) continue;
    AliAODMCParticle *MCtrack = (AliAODMCParticle *)fMCEvent->GetTrack(abs(v0MotherLabel));
    int pdg = MCtrack->GetPdgCode();


    if (code == 3122) {  
      h_pt_lambda_rc->Fill(pt);
      h_rap_lambda_rc->Fill(rap);
      h_mass_lambda_rc->Fill(mass);
      if (pdg == 3122) {
        h_pt_lambda_rc_real->Fill(pt);
        h_rap_lambda_rc_real->Fill(rap);
        h_mass_lambda_rc_real->Fill(mass);
      }
    } else if (code == -3122) {
      h_pt_antilambda_rc->Fill(pt);
      h_rap_antilambda_rc->Fill(rap);
      h_mass_antilambda_rc->Fill(mass);
      if (pdg == -3122) {
        h_pt_antilambda_rc_real->Fill(pt);
        h_rap_antilambda_rc_real->Fill(rap);
        h_mass_antilambda_rc_real->Fill(mass);
      }
    }
  }

  //------------------
  // Reco Track
  //------------------
  int nTracks = fAOD->GetNumberOfTracks();
  for (int iTrack = 0; iTrack < nTracks; iTrack++) {
    AliAODTrack *track = (AliAODTrack *)fAOD->GetTrack(iTrack);
    if (!track) {
      AliError(Form("%s: Could not get Track", GetName()));
      continue;
    }
    if (!track->TestFilterBit(768)) continue;
    float pt = track->Pt();
    float eta = track->Eta();
    float phi = track->Phi();
    int charge = track->Charge();
    int nhits = track->GetTPCNcls();
    float dedx = track->GetTPCsignal();
    double chi2 = track->Chi2perNDF();

    if (pt < 0.2) continue;
    if (fabs(eta) > 0.8) continue;
    if (fabs(nhits) < 70) continue;
    if (dedx < 10) continue;
    if (chi2 < 0.1 || chi2 > 2.5) continue;

    double r[3];
    track->GetXYZ(r);
    double dcax = r[0] - fVertex[0];
    double dcay = r[1] - fVertex[1];
    double dcaz = abs(r[2] - fVertex[2]);
    double dcaxy = sqrt(dcax * dcax + dcay * dcay);

    if (fabs(dcaz) > 2.0) continue;
    if (fabs(dcaxy) > 7.0 * (0.0026 + 0.005 / TMath::Power(pt, 1.01))) continue;

    float nSigTPC = fPID->NumberOfSigmasTPC(track, AliPID::kProton);
    float nSigTOF = fPID->NumberOfSigmasTOF(track, AliPID::kProton);
    float nSigRMS = TMath::Sqrt(nSigTPC * nSigTPC + nSigTOF * nSigTOF);
    bool isProton = (nSigRMS < 3.0) && (fabs(dcaz) < 1.0) && (fabs(dcaxy) < (0.0105 + 0.035 / TMath::Power(pt, 1.1)));

    if (charge > 0) {
      h_pt_poshadron_rc->Fill(pt);
      h_eta_poshadron_rc->Fill(eta);
      if (isProton) {
        h_pt_proton_rc->Fill(pt);
        h_eta_proton_rc->Fill(eta);
        int label = abs(track->GetLabel());
        AliAODMCParticle *MCtrack = (AliAODMCParticle *)fMCEvent->GetTrack(label);
        int pdg = MCtrack->GetPdgCode();
        if (pdg == 2212) {
          h_pt_proton_rc_real->Fill(pt);
          h_eta_proton_rc_real->Fill(eta);
        }
      }
    }
    if (charge < 0) {
      h_pt_neghadron_rc->Fill(pt);
      h_eta_neghadron_rc->Fill(eta);
      if (isProton) {
        h_pt_antiproton_rc->Fill(pt);
        h_eta_antiproton_rc->Fill(eta);
        int label = abs(track->GetLabel());
        AliAODMCParticle *MCtrack = (AliAODMCParticle *)fMCEvent->GetTrack(label);
        int pdg = MCtrack->GetPdgCode();
        if (pdg == -2212) {
          h_pt_antiproton_rc_real->Fill(pt);
          h_eta_antiproton_rc_real->Fill(eta);
        }
      }
    }
  }
  

  //------------------
  // MC
  //------------------
  // process MC particles
  TClonesArray *AODMCTrackArray = dynamic_cast<TClonesArray *>(fInputEvent->FindListObject(AliAODMCParticle::StdBranchName()));
  if (AODMCTrackArray == nullptr) return;
  // Loop over all primary MC particle
  for (Long_t i = 0; i < AODMCTrackArray->GetEntriesFast(); i++) {
    AliAODMCParticle *trackMC = static_cast<AliAODMCParticle *>(AODMCTrackArray->At(i));
    if (AliAnalysisUtils::IsParticleFromOutOfBunchPileupCollision(i,fMCEvent)) continue;
    if (!trackMC) continue;
    if (!trackMC->IsPhysicalPrimary()) continue;
    if (!trackMC->IsPrimary()) continue;

    double vzMC = trackMC->Zv();
    if(fabs(vzMC) > 10) continue;

    int pdg = trackMC->GetPdgCode();
    double pt = trackMC->Pt();
    double rap = trackMC->Y();
    double eta = trackMC->Eta();
    double charge = trackMC->Charge();

    //hadron and proton
    if (pt > 0.2 && fabs(eta) < 0.8) {
      if (charge > 0) {
        h_pt_poshadron_mc->Fill(pt);
        h_eta_poshadron_mc->Fill(eta);
        if (pdg == 2212) {
          h_pt_proton_mc->Fill(pt);
          h_eta_proton_mc->Fill(eta);
        }
      } else if (charge < 0) {
        h_pt_neghadron_mc->Fill(pt);
        h_eta_neghadron_mc->Fill(eta);
        if (pdg == -2212) {
          h_pt_antiproton_mc->Fill(pt);
          h_eta_antiproton_mc->Fill(eta);
        }
      }
    }

    //lambda
    if (pt > 0.5 && fabs(rap) < 0.5) {
      if (pdg == 3122) {
        h_pt_lambda_mc->Fill(pt);
        h_rap_lambda_mc->Fill(rap);
      } else if (pdg == -3122) {
        h_pt_antilambda_mc->Fill(pt);
        h_rap_antilambda_mc->Fill(rap);
      }
    }
  }
  PostData(1, fOutputList);
}


//---------------------------------------------------
bool AliAnalysisTaskMyTaskMyMCLambda::IsGoodV0(AliAODv0 *thisV0)
{
  // Offline reconstructed V0 only
  if (thisV0->GetOnFlyStatus()) return false;
  // Cosinus of pointing angle < 0.997
  double dCPA = thisV0->CosPointingAngle(fVertex);
  if (dCPA < 0.997) return false;
  // DCA of V0 < 1.5 cm
  double dV0Dca = thisV0->DcaV0ToPrimVertex();
  if (TMath::Abs(dV0Dca) > 1.5) return false;
  // V0 path length before decay 3-100 cm
  double dDecayLength = thisV0->DecayLengthV0(fVertex);
  if (dDecayLength > 100.) return false;
  if (dDecayLength < 3.) return false;
  // DCA between daughters < 0.5cm
  double dDCA = thisV0->DcaV0Daughters();
  if (dDCA > 0.5) return false;
  // DCA of daughters to PV > 0.05 cm
  float nDcaPV = thisV0->DcaNegToPrimVertex();
  float pDcaPV = thisV0->DcaPosToPrimVertex();
  if ( nDcaPV < 0.05 || pDcaPV < 0.05) return false;
  return kTRUE;
}

//---------------------------------------------------
bool AliAnalysisTaskMyTaskMyMCLambda::IsGoodDaughterTrack(const AliAODTrack *track)
{
  // TPC refit
  if (!track->IsOn(AliVTrack::kTPCrefit)) return false;
  // No kinks
  if (int(track->GetProdVertex()->GetType()) == AliAODVertex::kKink) return false;
  // Maximum value of transverse momentum
  double dPt = track->Pt();
  if (dPt > 20) return false;
  // Maximum value of pseudorapidity
  double dEta = track->Eta();
  if (TMath::Abs(dEta) > 0.8) return false;
  // Minimum number of clusters
  float nCrossedRowsTPC = track->GetTPCClusterInfo(2,1);
  if (nCrossedRowsTPC < 70) return false;
  // Findable clusters > 0
  int findable = track->GetTPCNclsF();
  if (findable <= 0) return false;
  // [number of crossed rows]>0.8  [number of findable clusters].
  if (nCrossedRowsTPC/findable < 0.8) return false;
  return true;
}

//---------------------------------------------------
int AliAnalysisTaskMyTaskMyMCLambda::GetLambdaCode(const AliAODTrack *pTrack, const AliAODTrack *nTrack)
{
  bool isLambda     = kFALSE;
  bool isAntiLambda = kFALSE;
  int  code = 0;

  //Λ-->(p+)+(π-)
  float nSigTPCPosProton = TMath::Abs(fPID->NumberOfSigmasTPC(pTrack, AliPID::kProton));//TPC p+
  float nSigTPCNegPion   = TMath::Abs(fPID->NumberOfSigmasTPC(nTrack, AliPID::kPion));//TPC π-
  //(Λ-)-->(p-)+(π+)
  float nSigTPCPosPion   = TMath::Abs(fPID->NumberOfSigmasTPC(pTrack, AliPID::kPion));//TPC π+
  float nSigTPCNegProton = TMath::Abs(fPID->NumberOfSigmasTPC(nTrack, AliPID::kProton));//TPC p-

  isLambda     = (nSigTPCPosProton < 3.) && (nSigTPCNegPion < 3.);
  isAntiLambda = (nSigTPCNegProton < 3.) && (nSigTPCPosPion < 3.);

  if (isLambda)     code =  3122;
  if (isAntiLambda) code = -3122;
  if (isLambda && isAntiLambda) code = 0;
  return code;
}


