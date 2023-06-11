#ifndef AliAnalysisTaskMyTaskMyMC_cxx
#define AliAnalysisTaskMyTaskMyMC_cxx

#include "AliAnalysisTaskSE.h"

//class AliAnalysisUtils;

//#include "AliAnalysisTaskMy.h"

class AliAnalysisTaskMyTaskMyMC : public AliAnalysisTaskSE
{
 public:

  AliAnalysisTaskMyTaskMyMC();
  AliAnalysisTaskMyTaskMyMC(const char *name);
  virtual ~AliAnalysisTaskMyTaskMyMC();

  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t *option);
  virtual void Terminate(Option_t *);

 private:

  TList* fOutputList;
  TH1D* h_pt_pos_hadron_mc;
  TH1D* h_pt_neg_hadron_mc;
  TH1D* h_pt_pos_proton_mc;
  TH1D* h_pt_neg_proton_mc;

  TH1D* h_pt_pos_hadron_rc;
  TH1D* h_pt_neg_hadron_rc;
  TH1D* h_pt_pos_proton_rc;
  TH1D* h_pt_neg_proton_rc;

  TH1D* h_pt_pos_proton_rc_real;
  TH1D* h_pt_neg_proton_rc_real;


  AliAnalysisTaskMyTaskMyMC(const AliAnalysisTaskMyTaskMyMC&);
  AliAnalysisTaskMyTaskMyMC& operator=(const AliAnalysisTaskMyTaskMyMC&);

  ClassDef(AliAnalysisTaskMyTaskMyMC, 1);
};

#endif
