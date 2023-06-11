// include the header of your analysis task here! for classes already compiled by aliBuild,
// precompiled header files (with extension pcm) are available, so that you do not need to
// specify includes for those. for your own task however, you (probably) have not generated a
// pcm file, so we need to include it explicitly
#include "TInterpreter.h"
#include "AliAnalysisManager.h"
#include "AliAODInputHandler.h"
#include "TMacro.h"
#include "AliAnalysisTaskPIDResponse.h"
#include "AliMultSelectionTask.h"
#include "TSystem.h"
#include "TChain.h"
#include "AliAnalysisAlien.h"
#include "AliPhysicsSelectionTask.h"
#include "AliAnalysisTaskMyTaskMyMC.h"
#include <algorithm>
#include <iostream>

void runAnalysis()
{
  // Task Name
  TString taskName = "MCProtonEfficiencyPurity18r";
  // Dataset
  TString dataset = "LHC18r";
  bool isMC = 1;

  // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
  // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
  bool local      = 0;
  bool gridTest   = 0;
  bool gridRun    = 0;
  bool gridMerge  = 0;
  bool localMerge = 1;

  std::vector<bool> boolVector = {local, gridTest, gridRun, gridMerge, localMerge};
  int trueCount = std::count(boolVector.begin(), boolVector.end(), true);
  if (trueCount != 1)
  {
    std::cout << "开关只能开一个!" << std::endl;
    return;
  }
  if (gridMerge || localMerge)
    gridRun = kFALSE;
  if (gridRun)
  {
    gridTest = kFALSE;
    local = kFALSE;
  }

  Int_t groupNumber = 1;

  // since we will compile a class, tell root where to look for headers
#if !defined(__CINT__) || defined(__CLING__)
  gInterpreter->ProcessLine(".include $ROOTSYS/include");
  gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
  gROOT->ProcessLine(".include $ROOTSYS/include");
  gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif

  // create the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
  AliAODInputHandler *aodH = new AliAODInputHandler();
  mgr->SetInputEventHandler(aodH);

  TMacro PIDadd(gSystem->ExpandPathName("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C"));
  AliAnalysisTaskPIDResponse *PIDresponseTask = reinterpret_cast<AliAnalysisTaskPIDResponse *>(PIDadd.Exec());

  if (dataset.EqualTo("LHC15o") || dataset.EqualTo("LHC18q") || dataset.EqualTo("LHC18r"))
  {
    // TMacro physicsSelection(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/macros/AddTaskPhysicsSelection.C"));
    // AliPhysicsSelectionTask* physicsSelectionTask = reinterpret_cast<AliPhysicsSelectionTask*>(physicsSelection.Exec());
    TMacro multSelection(gSystem->ExpandPathName("$ALICE_PHYSICS/OADB/COMMON/MULTIPLICITY/macros/AddTaskMultSelection.C"));
    AliMultSelectionTask *multSelectionTask = reinterpret_cast<AliMultSelectionTask *>(multSelection.Exec());
  }

  // compile the class and load the add task macro
  // here we have to differentiate between using the just-in-time compiler
  // from root6, or the interpreter of root5
#if !defined(__CINT__) || defined(__CLING__)
  gInterpreter->LoadMacro("AliAnalysisTaskMyTaskMyMC.cxx++g");
  AliAnalysisTaskMyTaskMyMC *task = nullptr;
  task = reinterpret_cast<AliAnalysisTaskMyTaskMyMC*>(gInterpreter->ExecuteMacro("AddTaskMyTaskMyMC.C"));
#else
  gROOT->LoadMacro("AliAnalysisTaskMyTaskMyMC.cxx++g");
  gROOT->LoadMacro("AddTaskMyTaskMyMC.C");
  AliAnalysisTaskMyTaskMyMC *task = AddTaskMyTaskMyMC();
#endif

  if (!mgr->InitAnalysis())
    return;
  mgr->SetDebugLevel(2);
  mgr->PrintStatus();
  mgr->SetUseProgressBar(1, 25);

  if (local)
  {
    // if you want to run locally, we need to define some input
    TChain *chain = new TChain("aodTree");
    // add a few files to the chain (change this so that your local files are added)
    // if (dataset.EqualTo("LHC10h"))
    //   chain->Add("/Users/wangchunzheng/alice/data/2010/LHC10h/000139510/ESDs/pass2/AOD160/0247/AliAOD.root");
    // if (dataset.EqualTo("LHC15o"))
    //   chain->Add("/Users/wangchunzheng/alice/data/2015/LHC15o/000245151/pass2/AOD252/0008/AliAOD.root");
    // if (dataset.EqualTo("LHC18q"))
    //   chain->Add("/Users/wangchunzheng/alice/data/2018/LHC18q/000295588/pass3/AOD252/AOD/001/AliAOD.root");
    // if (dataset.EqualTo("LHC18r"))
    //   chain->Add("/Users/wangchunzheng/alice/data/2018/LHC18r/000296691/pass3/AOD252/0001/AliAOD.root");

    chain->Add("AliAOD.root");
    // start the analysis locally, reading the events from the tchain
    mgr->StartAnalysis("local", chain);
  }
  else
  {
    // if we want to run on grid, we create and configure the plugin
    AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
    // also specify the include (header) paths on grid
    alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
    // make sure your source files get copied to grid
    alienHandler->SetAdditionalLibs("AliAnalysisTaskMyTaskMyMC.cxx AliAnalysisTaskMyTaskMyMC.h");
    alienHandler->SetAnalysisSource("AliAnalysisTaskMyTaskMyMC.cxx");
    // select the aliphysics version. all other packages
    // are LOADED AUTOMATICALLY!
    alienHandler->SetAliPhysicsVersion("vAN-20220316_ROOT6-1");
    // set the Alien API version
    alienHandler->SetAPIVersion("V1.1x");

    if (dataset.EqualTo("LHC10h"))
    {
      // 10h
      //  select the input data
      alienHandler->SetGridDataDir("/alice/data/2010/LHC10h");
      alienHandler->SetDataPattern("ESDs/pass2/AOD160/*/AliAOD.root");
      // MC has no prefix, data has prefix 000
      alienHandler->SetRunPrefix("000");
      // runnumber
      // 1
      if (groupNumber == 1)
      {
        alienHandler->AddRunNumber(139510);
        alienHandler->AddRunNumber(139507);
        alienHandler->AddRunNumber(139505);
        alienHandler->AddRunNumber(139503);
        alienHandler->AddRunNumber(139465);
      }
    }
    if (dataset.EqualTo("LHC15o"))
    {
      // select the input data
      alienHandler->SetGridDataDir("/alice/data/2015/LHC15o");
      alienHandler->SetDataPattern("pass2/AOD252/AOD/*/AliAOD.root");
      // MC has no prefix, data has prefix 000
      alienHandler->SetRunPrefix("000");
      if (groupNumber == 1)
      {
        alienHandler->AddRunNumber(246276);
        alienHandler->AddRunNumber(246180);
        alienHandler->AddRunNumber(246053);
        alienHandler->AddRunNumber(245963);
        alienHandler->AddRunNumber(245775);
      }
    }
    if (dataset.EqualTo("LHC18q"))
    {
      // select the input data
      if(isMC) {
        alienHandler->SetGridDataDir("/alice/sim/2020/LHC20e3a");
        alienHandler->SetDataPattern("AOD243/*/AliAOD.root");
        alienHandler->SetRunPrefix("");
      } else {
        alienHandler->SetGridDataDir("/alice/data/2018/LHC18q");
        alienHandler->SetDataPattern("pass3/AOD252/AOD/*/AliAOD.root");
        alienHandler->SetRunPrefix("000");
      }
      // MC has no prefix, data has prefix 000
      if (groupNumber == 1)
      {
        alienHandler->AddRunNumber(296379);
        alienHandler->AddRunNumber(296279);
        alienHandler->AddRunNumber(296135);
        alienHandler->AddRunNumber(296060);
        alienHandler->AddRunNumber(296240);
        alienHandler->AddRunNumber(296198);
        alienHandler->AddRunNumber(296197);
        alienHandler->AddRunNumber(296196);
        alienHandler->AddRunNumber(296195);
        alienHandler->AddRunNumber(296899);
      }
    }
    if (dataset.EqualTo("LHC18r"))
    {
      // select the input data
      if(isMC) {
        alienHandler->SetGridDataDir("/alice/sim/2020/LHC20e3a");
        alienHandler->SetDataPattern("AOD243/*/AliAOD.root");
        alienHandler->SetRunPrefix("");
      } else {
        alienHandler->SetGridDataDir("/alice/data/2018/LHC18r");
        alienHandler->SetDataPattern("pass3/AOD252/AOD/*/AliAOD.root");
        alienHandler->SetRunPrefix("000");
      }
      if (groupNumber == 1)
      {
        alienHandler->AddRunNumber(297406);
        alienHandler->AddRunNumber(297333);
        alienHandler->AddRunNumber(297195);
        alienHandler->AddRunNumber(297117);
        alienHandler->AddRunNumber(296931);
        alienHandler->AddRunNumber(297118);
        alienHandler->AddRunNumber(297085);
        alienHandler->AddRunNumber(297035);
        alienHandler->AddRunNumber(297031);
        alienHandler->AddRunNumber(296966);
      }
    }

    // number of files per subjob
    alienHandler->SetSplitMaxInputFileNumber(40);
    alienHandler->SetExecutable("myTask.sh");
    // specify how many seconds your job may take
    alienHandler->SetTTL(30000);
    alienHandler->SetJDLName("myTask.jdl");

    alienHandler->SetOutputToRunNo(kTRUE);
    alienHandler->SetKeepLogs(kTRUE);
    // merging: run with kTRUE to merge on grid
    // after re-running the jobs in SetRunMode("terminate")
    // (see below) mode, set SetMergeViaJDL(kFALSE)
    // to collect final results
    alienHandler->SetMaxMergeStages(1);
    if (gridRun || gridMerge)
    {
      alienHandler->SetMergeViaJDL(kTRUE);
    }
    if (localMerge)
    {
      alienHandler->SetMergeViaJDL(kFALSE);
    }

    // define the output folders
    if (dataset.EqualTo("LHC10h"))
      alienHandler->SetGridWorkingDir(Form("%s/LHC10h", taskName.Data()));
    if (dataset.EqualTo("LHC15o"))
      alienHandler->SetGridWorkingDir(Form("%s/LHC15o", taskName.Data()));
    if (dataset.EqualTo("LHC18q"))
      alienHandler->SetGridWorkingDir(Form("%s/LHC18q", taskName.Data()));
    if (dataset.EqualTo("LHC18r"))
      alienHandler->SetGridWorkingDir(Form("%s/LHC18r", taskName.Data()));

    alienHandler->SetGridOutputDir("output");

    // connect the alien plugin to the manager
    mgr->SetGridHandler(alienHandler);
    if (gridTest)
    {
      // speficy on how many files you want to run
      alienHandler->SetNtestFiles(1);
      // and launch the analysis
      alienHandler->SetRunMode("test");
      mgr->StartAnalysis("grid");
    }
    else
    {
      // else launch the full grid analysis
      if (gridMerge || localMerge)
        alienHandler->SetRunMode("terminate");
      if (gridRun)
        alienHandler->SetRunMode("full");
      mgr->StartAnalysis("grid");
    }
  }
}

