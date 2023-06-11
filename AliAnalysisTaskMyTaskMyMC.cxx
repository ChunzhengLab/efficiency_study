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
#include "AliAnalysisTaskMyTaskMyMC.h"
#include "AliPID.h"
#include "AliPIDCombined.h"
#include "AliPIDResponse.h"

using std::cout;
using std::endl;

ClassImp(AliAnalysisTaskMyTaskMyMC);

//---------------------------------------------------
AliAnalysisTaskMyTaskMyMC::AliAnalysisTaskMyTaskMyMC() : AliAnalysisTaskSE() {
  fOutputList = nullptr;
  
  h_pt_pos_hadron_mc = nullptr;
  h_pt_neg_hadron_mc = nullptr;
  h_pt_neg_proton_mc = nullptr;
  h_pt_pos_proton_mc = nullptr;

  h_pt_pos_hadron_rc = nullptr;
  h_pt_neg_hadron_rc = nullptr;
  h_pt_neg_proton_rc = nullptr;
  h_pt_pos_proton_rc = nullptr;

  h_pt_pos_proton_rc_real = nullptr;
  h_pt_neg_proton_rc_real = nullptr;
}

//---------------------------------------------------
AliAnalysisTaskMyTaskMyMC::AliAnalysisTaskMyTaskMyMC(const char *name) : AliAnalysisTaskSE(name) {
  fOutputList = nullptr;

  h_pt_pos_hadron_mc = nullptr;
  h_pt_neg_hadron_mc = nullptr;
  h_pt_neg_proton_mc = nullptr;
  h_pt_pos_proton_mc = nullptr;

  h_pt_pos_hadron_rc = nullptr;
  h_pt_neg_hadron_rc = nullptr;
  h_pt_neg_proton_rc = nullptr;
  h_pt_pos_proton_rc = nullptr;

  h_pt_pos_proton_rc_real = nullptr;
  h_pt_neg_proton_rc_real = nullptr;

  DefineInput(0, TChain::Class());
  DefineOutput(1, TList::Class());
}

//---------------------------------------------------
AliAnalysisTaskMyTaskMyMC::~AliAnalysisTaskMyTaskMyMC() {
}

//---------------------------------------------------
void AliAnalysisTaskMyTaskMyMC::Terminate(Option_t *) {
}

//---------------------------------------------------
void AliAnalysisTaskMyTaskMyMC::UserCreateOutputObjects() {
  fOutputList = new TList();
  fOutputList->SetName(GetName());
  fOutputList->SetOwner(kTRUE);

  h_pt_pos_hadron_mc = new TH1D("h_pt_pos_hadron_mc", "h_pt_pos_hadron_mc", 200, 0, 10);
  h_pt_neg_hadron_mc = new TH1D("h_pt_neg_hadron_mc", "h_pt_neg_hadron_mc", 200, 0, 10);
  h_pt_pos_proton_mc = new TH1D("h_pt_pos_proton_mc", "h_pt_pos_proton_mc", 200, 0, 10);
  h_pt_neg_proton_mc = new TH1D("h_pt_neg_proton_mc", "h_pt_neg_proton_mc", 200, 0, 10);
  fOutputList->Add(h_pt_pos_hadron_mc);
  fOutputList->Add(h_pt_neg_hadron_mc);
  fOutputList->Add(h_pt_pos_proton_mc);
  fOutputList->Add(h_pt_neg_proton_mc);

  h_pt_pos_hadron_rc = new TH1D("h_pt_pos_hadron_rc", "h_pt_pos_hadron_rc", 200, 0, 10);
  h_pt_neg_proton_rc = new TH1D("h_pt_neg_proton_rc", "h_pt_neg_proton_rc", 200, 0, 10);
  h_pt_pos_proton_rc = new TH1D("h_pt_pos_proton_rc", "h_pt_pos_proton_rc", 200, 0, 10);
  h_pt_neg_hadron_rc = new TH1D("h_pt_neg_hadron_rc", "h_pt_neg_hadron_rc", 200, 0, 10);
  fOutputList->Add(h_pt_pos_hadron_rc);
  fOutputList->Add(h_pt_neg_proton_rc);
  fOutputList->Add(h_pt_pos_proton_rc);
  fOutputList->Add(h_pt_neg_hadron_rc);

  h_pt_pos_proton_rc_real = new TH1D("h_pt_pos_proton_rc_real", "h_pt_pos_proton_rc_real", 200, 0, 10);
  h_pt_neg_proton_rc_real = new TH1D("h_pt_neg_proton_rc_real", "h_pt_neg_proton_rc_real", 200, 0, 10);
  fOutputList->Add(h_pt_pos_proton_rc_real);
  fOutputList->Add(h_pt_neg_proton_rc_real);

  PostData(1, fOutputList);
}

//---------------------------------------------------
void AliAnalysisTaskMyTaskMyMC::UserExec(Option_t *) {
  AliAnalysisManager *manager = AliAnalysisManager::GetAnalysisManager();
  if (!manager) {
    AliError(Form("%s: Could not get Analysis Manager", GetName()));
  }
  AliAODInputHandler *handler = (AliAODInputHandler *)manager->GetInputEventHandler();
  if (!handler) {
    AliError(Form("%s: Could not get Input Handler", GetName()));
  }
  AliAODEvent* fAOD = (AliAODEvent *)InputEvent();
  if (!fAOD) {
    AliError(Form("%s: Could not get AOD event", GetName()));
  }
  AliPIDResponse *fPID = handler->GetPIDResponse();
  if (!fPID) {
    AliError(Form("%s: Could not get PIDResponse", GetName()));
  }
  AliMultSelection *fMultSel = (AliMultSelection *)InputEvent()->FindListObject("MultSelection");
  if (!fMultSel) {
    AliError(Form("%s: Could not get AliMultSelection", GetName()));
  }
  AliMCEvent *fMC = (AliMCEvent *)MCEvent();
  if (!fMC) {
    AliError(Form("%s: Could not get AliMCEvent", GetName()));
  }

  if (!manager || !handler || !fAOD || !fMultSel || !fMC) return;

  //------------------
  // event-wise
  //------------------

  // vertex
  AliAODVertex *fVtx = fAOD->GetPrimaryVertex();
  float vx = fVtx->GetX();
  float vy = fVtx->GetY();
  float vz = fVtx->GetZ();
  float vzSPD = fAOD->GetPrimaryVertexSPD()->GetZ();

  if (fabs(vz) > 10) return;
  if (fabs(vz - vzSPD) > 0.5) return;


  double centrality = fMultSel->GetMultiplicityPercentile("V0M");
  if (centrality < 0 || centrality > 80) return;


  //------------------
  // MC reco
  //------------------
  std::vector <int> vec_label_reco;
  int nRCTrack = fAOD->GetNumberOfTracks();
  for (Long_t iRCTrack = 0; iRCTrack < nRCTrack; ++iRCTrack) {
    AliAODTrack *RCTrack = (AliAODTrack *)fAOD->GetTrack(iRCTrack);
    if (!RCTrack) {
      AliError(Form("%s: Could not get Track", GetName()));
      continue;
    }
    if (!RCTrack->TestFilterBit(768)) continue;
    float pt = RCTrack->Pt();
    float eta = RCTrack->Eta();
    float phi = RCTrack->Phi();
    int charge = RCTrack->Charge();
    int nhits = RCTrack->GetTPCNcls();
    float dedx = RCTrack->GetTPCsignal();
    double chi2 = RCTrack->Chi2perNDF();


    if (pt < 0.2 || pt > 5.0) continue;
    if (fabs(eta) > 0.8) continue;
    if (fabs(nhits) < 70) continue;
    if (dedx < 10) continue;
    if (chi2 < 0.1 || chi2 > 4.) continue;

    double r[3];
    RCTrack->GetXYZ(r);
    double dcax = r[0] - fAOD->GetPrimaryVertex()->GetX();
    double dcay = r[1] - fAOD->GetPrimaryVertex()->GetY();
    double dcaz = abs(r[2] - fAOD->GetPrimaryVertex()->GetZ());
    double dcaxy = sqrt(dcax * dcax + dcay * dcay);

    if (fabs(dcaz) > 2.0) continue;
    if (fabs(dcaxy) > 7.0 * (0.0026 + 0.005 / TMath::Power(pt, 1.01))) continue;

    float nSigTPC = fPID->NumberOfSigmasTPC(RCTrack, AliPID::kProton);
    float nSigTOF = fPID->NumberOfSigmasTOF(RCTrack, AliPID::kProton);
    float nSigRMS = TMath::Sqrt(nSigTPC * nSigTPC + nSigTOF * nSigTOF);
    //nsig and special DCA for proton
    bool isProton = (nSigRMS < 3.0) && (fabs(dcaz) < 1.0) && (fabs(dcaxy) < (0.0105 + 0.035 / TMath::Power(pt, 1.1)));

    if (charge > 0) {
      h_pt_pos_hadron_rc->Fill(pt);
      if (isProton) {
        h_pt_pos_proton_rc->Fill(pt);
        //get pdgcode of the track
        int label = abs(RCTrack->GetLabel());
        AliAODMCParticle *MCtrack = (AliAODMCParticle *)fMC->GetTrack(label);
        int pdg = MCtrack->GetPdgCode();
        if (pdg == 2212) {
          h_pt_pos_proton_rc_real->Fill(pt);
        }
      }
    }
    if (charge < 0) {
      h_pt_neg_hadron_rc->Fill(pt);
      if (isProton) {
        h_pt_neg_proton_rc->Fill(pt);
        //get pdgcode of the track
        int label = abs(RCTrack->GetLabel());
        AliAODMCParticle *MCtrack = (AliAODMCParticle *)fMC->GetTrack(label);
        int pdg = MCtrack->GetPdgCode();
        if (pdg == -2212) {
          h_pt_neg_proton_rc_real->Fill(pt);
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
    AliAODMCParticle *MCtrack = static_cast<AliAODMCParticle *>(AODMCTrackArray->At(i));

    if (AliAnalysisUtils::IsParticleFromOutOfBunchPileupCollision(i,fMCEvent)) continue;
    TString generatorName;
    if (!MCtrack) continue;
    if (!MCtrack->IsPhysicalPrimary()) continue;
    if (!MCtrack->IsPrimary()) continue;
    if (MCtrack->Charge() == 0) continue;

    int pdg = MCtrack->GetPdgCode();
    double pt = MCtrack->Pt();
    double eta = MCtrack->Eta();
    int charge = MCtrack->Charge();

    double vzMC = MCtrack->Zv();
    if(fabs(vzMC) > 10) continue;
    if (pt < 0.2 || pt > 5.) continue;
    if (fabs(eta) > 0.8) continue;

    if (charge > 0) {
      h_pt_pos_hadron_mc->Fill(pt);
      if (pdg == 2212) {
        h_pt_pos_proton_mc->Fill(pt);
      }
    }
    if (charge < 0) {
      h_pt_neg_hadron_mc->Fill(pt);
      if (pdg == -2212) {
        h_pt_neg_proton_mc->Fill(pt);
      }
    }
  }

  PostData(1, fOutputList);
}
