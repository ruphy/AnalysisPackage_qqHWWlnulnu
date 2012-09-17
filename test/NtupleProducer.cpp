#include "treeReader.h"
#include "hFactory.h"
#include "hFunctions.h"
#include "stdHisto.h"
#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "Math/GenVector/VectorUtil.h"
#include "TRandom3.h"
#include <time.h>
#include <sstream>
#include "qqHWWlnulnuUtils.h"
#include "Variables.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif

int GetNumList(std::vector<int> &list){
 int result = 0;
 for (int it = 0; it<list.size(); it++) result += list.at(it);
 return result;
}

int main(int argc, char** argv)
{ 
 //Check if all nedeed arguments to parse are there                                                                                                                               
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");
 std::string inputFile = gConfigParser -> readStringOption("Input::inputFile");
 double inputXSection  = gConfigParser -> readDoubleOption("Input::inputXSection");
 
 int entryMAX = gConfigParser -> readIntOption("Input::entryMAX");
 int entryMIN = gConfigParser -> readIntOption("Input::entryMIN");
 int entryMOD = gConfigParser -> readIntOption("Input::entryMOD");
 
 
 std::cout << ">>>>> input::entryMIN  " << entryMIN  << std::endl;  
 std::cout << ">>>>> input::entryMAX  " << entryMAX  << std::endl;  
 std::cout << ">>>>> input::entryMOD  " << entryMOD  << std::endl;  
 
 
 int dataFlag = 0;
 if (inputXSection == -1) dataFlag = 1; //==== it's a data sample!!!
 std::cerr << ">>>>> input:: --- dataFlag  " << dataFlag << std::endl;
// define map with events
  std::map<std::pair<int,std::pair<int,int> >,int> eventsMap;  
 
 
 int nStepToDo = 1000;
 try {
  nStepToDo = gConfigParser -> readIntOption("Input::nStepToDo");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
  nStepToDo = 1000;
 }
 std::cout << ">>>>> input::nStepToDo  " << nStepToDo  << std::endl;  
 
 
 // Open ntple
 TChain* chain = new TChain(treeName.c_str());
 chain->Add(inputFile.c_str());
 treeReader reader((TTree*)(chain));
 
 
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  
 
 
 
 
 
 ///******************
 ///**** Triggers ****
 
 std::vector<std::string> HLTVector;
 try {
  HLTVector = gConfigParser -> readStringListOption("Options::HLTVector");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Options::HLTVector size = " << HLTVector.size() << std::endl;  
 std::cout << ">>>>> >>>>>  "; 
 for (int iHLT = 0; iHLT < HLTVector.size(); iHLT++){
  std::cout << " " << HLTVector.at(iHLT) << ", ";
 }
 std::cout << std::endl; 
  
 ///****************************
 ///**** DATA JSON file ****
 
  std::string inFileNameJSON;
  try {
  inFileNameJSON = gConfigParser -> readStringOption("Input::inFileNameJSON");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Input::inFileNameJSON  " << inFileNameJSON  << std::endl;  
 std::map<int, std::vector<std::pair<int, int> > > jsonMap;
 if( dataFlag == 1 ) {
   jsonMap = readJSONFile(inFileNameJSON);
}

 
 ///---- Efficiency preselections ---- 
 
 std::string histoNameEvents      = gConfigParser -> readStringOption("Input::histoNameEvents"); 
 std::cout << ">>>>> Input::inputFile                 " << inputFile  << std::endl;  
 std::cout << ">>>>> Input::inputXSection             " << inputXSection  << std::endl;  
 std::cout << ">>>>> Input::histoNameEvents      " << histoNameEvents  << std::endl;  
 
 // Open ntples
 TFile File(inputFile.c_str()) ; 
 TH1F* histoEvents = (TH1F*) File.Get(TString(histoNameEvents.c_str()));
 
 
 ///----------------------
 ///---- Preselection ----
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///==== only retrocompatibility ====
 
 ///=================================
 
 double lepton_efficiency = 1;
 double jet_efficiency = 1;
 double eff_Channel_Filter = 1;
 double preselection_efficiency = 1.;

 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 ///-------------------
 ///---- selection ----
 std::string outFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << outFileName  << std::endl;  
 
 int nStep = 10; ///==== number of steps in the analysis
 int numEntriesBefore;
 
 // define variable container
 Variables vars;
 InitializeTree(vars, outFileName);
 InitializeTreeTrigger(vars, HLTVector);
 
 
 vars.XSection = inputXSection;
 vars.dataFlag = dataFlag;  ///~~~~ 0 = MC       1 = DATA
 
 if (entryMAX == -1) entryMAX = reader.GetEntries();
 else if (reader.GetEntries() < entryMAX) entryMAX = reader.GetEntries();
 numEntriesBefore = entryMAX - entryMIN;
 
 if (histoEvents) preselection_efficiency = numEntriesBefore / (1. * histoEvents->GetBinContent(1));
 else preselection_efficiency = 1;
 
 vars.numEntriesBefore = numEntriesBefore;
 vars.preselection_efficiency = preselection_efficiency;
 
 FillEfficiencyTree(vars);
 
 
 ///*************************************
 ///**** definition of electron ID ****
 ///**** https://twiki.cern.ch/twiki/bin/viewauth/CMS/SimpleCutBasedEleID
 ///**** https://twiki.cern.ch/twiki/bin/viewauth/CMS/SimpleCutBasedEleID2011
 
 
 std::vector<double> BarrelSelections;
 std::vector<double> EndcapSelections;
 
 
 
 double eleCombinedIsoBarrel      = gConfigParser -> readDoubleOption("Selection::eleCombinedIsoBarrel");
 double elesigmaIetaIetaBarrel    = gConfigParser -> readDoubleOption("Selection::elesigmaIetaIetaBarrel");
 double eledPhiBarrel             = gConfigParser -> readDoubleOption("Selection::eledPhiBarrel");
 double eledEtaBarrel             = gConfigParser -> readDoubleOption("Selection::eledEtaBarrel");
 
 double eleCombinedIsoEndcap    = gConfigParser -> readDoubleOption("Selection::eleCombinedIsoEndcap");
 double elesigmaIetaIetaEndcap  = gConfigParser -> readDoubleOption("Selection::elesigmaIetaIetaEndcap");
 double eledPhiEndcap           = gConfigParser -> readDoubleOption("Selection::eledPhiEndcap");
 double eledEtaEndcap           = gConfigParser -> readDoubleOption("Selection::eledEtaEndcap");
 
 double elemishits    = gConfigParser -> readDoubleOption("Selection::elemishits");
 double eledist       = gConfigParser -> readDoubleOption("Selection::eledist");
 double eledcot       = gConfigParser -> readDoubleOption("Selection::eledcot");
 
 double eledzPV     = gConfigParser -> readDoubleOption("Selection::eledzPV");
 double eledxyPV    = gConfigParser -> readDoubleOption("Selection::eledxyPV");
 
 
 BarrelSelections.push_back(eleCombinedIsoBarrel);
 BarrelSelections.push_back(elesigmaIetaIetaBarrel);
 BarrelSelections.push_back(eledPhiBarrel);
 BarrelSelections.push_back(eledEtaBarrel);
 BarrelSelections.push_back(elemishits);
 BarrelSelections.push_back(eledist);
 BarrelSelections.push_back(eledcot);
 BarrelSelections.push_back(eledzPV);
 BarrelSelections.push_back(eledxyPV);
 
 EndcapSelections.push_back(eleCombinedIsoEndcap);
 EndcapSelections.push_back(elesigmaIetaIetaEndcap);
 EndcapSelections.push_back(eledPhiEndcap);
 EndcapSelections.push_back(eledEtaEndcap);
 EndcapSelections.push_back(elemishits);
 EndcapSelections.push_back(eledist);
 EndcapSelections.push_back(eledcot);
 EndcapSelections.push_back(eledzPV);
 EndcapSelections.push_back(eledxyPV);
 
 
 ///**** https://twiki.cern.ch/twiki/bin/viewauth/CMS/SimpleCutBasedEleID   --> 2010 Data
 ///**** 95% ****
 
  /*
   BarrelSelections.push_back(0.15); ///==== iso Tk
   BarrelSelections.push_back(2.00); ///==== iso em
   BarrelSelections.push_back(0.12); ///==== iso had
   BarrelSelections.push_back(0.15); ///==== iso combined
   BarrelSelections.push_back(0.015); ///==== hOe
   BarrelSelections.push_back(0.01); ///==== sigmaIetaIeta
   BarrelSelections.push_back(0.8); ///==== dPhi
   BarrelSelections.push_back(0.007); ///==== dEta
   
   EndCapSelections.push_back(0.08); ///==== iso Tk
   EndCapSelections.push_back(0.06); ///==== iso em
   EndCapSelections.push_back(0.05); ///==== iso had
   EndCapSelections.push_back(0.10); ///==== iso combined
   EndCapSelections.push_back(0.07); ///==== hOe
   EndCapSelections.push_back(0.03); ///==== sigmaIetaIeta
   EndCapSelections.push_back(0.7); ///==== dPhi
   EndCapSelections.push_back(0.01); ///==== dEta
   */
  
 
    ///**** 90% ****
   /*
   BarrelSelections.push_back(0.12); ///==== iso Tk
   BarrelSelections.push_back(0.09); ///==== iso em
   BarrelSelections.push_back(0.10); ///==== iso had
   BarrelSelections.push_back(0.10); ///==== iso combined
   BarrelSelections.push_back(0.12); ///==== hOe
   BarrelSelections.push_back(0.01); ///==== sigmaIetaIeta
   BarrelSelections.push_back(0.8); ///==== dPhi
   BarrelSelections.push_back(0.007); ///==== dEta
    
   EndCapSelections.push_back(0.05); ///==== iso Tk
   EndCapSelections.push_back(0.06); ///==== iso em
   EndCapSelections.push_back(0.03); ///==== iso had
   EndCapSelections.push_back(0.07); ///==== iso combined
   EndCapSelections.push_back(0.05); ///==== hOe
   EndCapSelections.push_back(0.03); ///==== sigmaIetaIeta
   EndCapSelections.push_back(0.7); ///==== dPhi
   EndCapSelections.push_back(0.007); ///==== dEta
  */
   
    ///**** 80% ****
    /*
   BarrelSelections.push_back(0.09); ///==== iso Tk
   BarrelSelections.push_back(0.07); ///==== iso em
   BarrelSelections.push_back(0.10); ///==== iso had
   BarrelSelections.push_back(0.07); ///==== iso combined
   BarrelSelections.push_back(0.040); ///==== hOe
   BarrelSelections.push_back(0.01); ///==== sigmaIetaIeta
   BarrelSelections.push_back(0.06); ///==== dPhi
   BarrelSelections.push_back(0.004); ///==== dEta
    
   EndCapSelections.push_back(0.04); ///==== iso Tk
   EndCapSelections.push_back(0.05); ///==== iso em
   EndCapSelections.push_back(0.025); ///==== iso had
   EndCapSelections.push_back(0.06); ///==== iso combined
   EndCapSelections.push_back(0.025); ///==== hOe
   EndCapSelections.push_back(0.03); ///==== sigmaIetaIeta
   EndCapSelections.push_back(0.03); ///==== dPhi
   EndCapSelections.push_back(0.007); ///==== dEta
 */
  
  
  ///**** 70% ****
  /*
  BarrelSelections.push_back(0.05); ///==== iso Tk
  BarrelSelections.push_back(0.06); ///==== iso em
  BarrelSelections.push_back(0.03); ///==== iso had
  BarrelSelections.push_back(0.04); ///==== iso combined
  BarrelSelections.push_back(0.025); ///==== hOe
  BarrelSelections.push_back(0.01); ///==== sigmaIetaIeta
  BarrelSelections.push_back(0.004); ///==== dPhi
  BarrelSelections.push_back(0.004); ///==== dEta
  
  EndCapSelections.push_back(0.025); ///==== iso Tk
  EndCapSelections.push_back(0.025); ///==== iso em
  EndCapSelections.push_back(0.02); ///==== iso had
  EndCapSelections.push_back(0.03); ///==== iso combined
  EndCapSelections.push_back(0.025); ///==== hOe
  EndCapSelections.push_back(0.03); ///==== sigmaIetaIeta
  EndCapSelections.push_back(0.02); ///==== dPhi
  EndCapSelections.push_back(0.005); ///==== dEta
  */
  
  
  
  ///**** https://twiki.cern.ch/twiki/bin/viewauth/CMS/SimpleCutBasedEleID2011   --> 2011 Data
  
  ///**** 95% ****
  /*
  BarrelSelections.push_back(10000.); ///==== iso Tk
  BarrelSelections.push_back(10000.); ///==== iso em
  BarrelSelections.push_back(10000.); ///==== iso had
  BarrelSelections.push_back(0.150); ///==== iso combined
  BarrelSelections.push_back(10000.); ///==== hOe
  BarrelSelections.push_back(0.012); ///==== sigmaIetaIeta
  BarrelSelections.push_back(0.800); ///==== dPhi
  BarrelSelections.push_back(0.007); ///==== dEta
  
  EndCapSelections.push_back(10000.); ///==== iso Tk
  EndCapSelections.push_back(10000.); ///==== iso em
  EndCapSelections.push_back(10000.); ///==== iso had
  EndCapSelections.push_back(0.100); ///==== iso combined
  EndCapSelections.push_back(10000.); ///==== hOe
  EndCapSelections.push_back(0.031); ///==== sigmaIetaIeta
  EndCapSelections.push_back(0.7); ///==== dPhi
  EndCapSelections.push_back(0.011); ///==== dEta
  */
  
  ///**** 90% ****
  /* 
   BarrelSelections.push_back(10000.); ///==== iso Tk
   BarrelSelections.push_back(10000.); ///==== iso em
   BarrelSelections.push_back(10000.); ///==== iso had
   BarrelSelections.push_back(0.085); ///==== iso combined
   BarrelSelections.push_back(10000.); ///==== hOe
   BarrelSelections.push_back(0.01); ///==== sigmaIetaIeta
   BarrelSelections.push_back(0.071); ///==== dPhi
   BarrelSelections.push_back(0.007); ///==== dEta
    
   EndCapSelections.push_back(10000.); ///==== iso Tk
   EndCapSelections.push_back(10000.); ///==== iso em
   EndCapSelections.push_back(10000.); ///==== iso had
   EndCapSelections.push_back(0.051); ///==== iso combined
   EndCapSelections.push_back(10000.); ///==== hOe
   EndCapSelections.push_back(0.031); ///==== sigmaIetaIeta
   EndCapSelections.push_back(0.047); ///==== dPhi
   EndCapSelections.push_back(0.011); ///==== dEta
   */

  ///**** 85% ****
   /*
   BarrelSelections.push_back(10000.); ///==== iso Tk
   BarrelSelections.push_back(10000.); ///==== iso em
   BarrelSelections.push_back(10000.); ///==== iso had
   BarrelSelections.push_back(0.053); ///==== iso combined
   BarrelSelections.push_back(10000.); ///==== hOe
   BarrelSelections.push_back(0.01); ///==== sigmaIetaIeta
   BarrelSelections.push_back(0.039); ///==== dPhi
   BarrelSelections.push_back(0.005); ///==== dEta
   
   EndCapSelections.push_back(10000.); ///==== iso Tk
   EndCapSelections.push_back(10000.); ///==== iso em
   EndCapSelections.push_back(10000.); ///==== iso had
   EndCapSelections.push_back(0.042); ///==== iso combined
   EndCapSelections.push_back(10000.); ///==== hOe
   EndCapSelections.push_back(0.031); ///==== sigmaIetaIeta
   EndCapSelections.push_back(0.028); ///==== dPhi
   EndCapSelections.push_back(0.007); ///==== dEta
   */


 ///**** 80% ****
   /*
   BarrelSelections.push_back(10000.); ///==== iso Tk
   BarrelSelections.push_back(10000.); ///==== iso em
   BarrelSelections.push_back(10000.); ///==== iso had
   BarrelSelections.push_back(0.040); ///==== iso combined
   BarrelSelections.push_back(10000.); ///==== hOe
   BarrelSelections.push_back(0.01); ///==== sigmaIetaIeta
   BarrelSelections.push_back(0.027); ///==== dPhi
   BarrelSelections.push_back(0.005); ///==== dEta
   
   EndCapSelections.push_back(10000.); ///==== iso Tk
   EndCapSelections.push_back(10000.); ///==== iso em
   EndCapSelections.push_back(10000.); ///==== iso had
   EndCapSelections.push_back(0.033); ///==== iso combined
   EndCapSelections.push_back(10000.); ///==== hOe
   EndCapSelections.push_back(0.031); ///==== sigmaIetaIeta
   EndCapSelections.push_back(0.021); ///==== dPhi
   EndCapSelections.push_back(0.006); ///==== dEta
   */
   
  ///***********************************
  ///**** definition of muon ID ****
  std::vector<double> Selections;
  
  double muCombinedIso   = gConfigParser -> readDoubleOption("Selection::muCombinedIso");
  double muChi2Ndof      = gConfigParser -> readDoubleOption("Selection::muChi2Ndof");
  
  
  double muValidTrackerHits = gConfigParser -> readDoubleOption("Selection::muValidTrackerHits");
  double muValidMuonHits    = gConfigParser -> readDoubleOption("Selection::muValidMuonHits");
  
  double mutracker    = gConfigParser -> readDoubleOption("Selection::mutracker");
  double mustandalone = gConfigParser -> readDoubleOption("Selection::mustandalone");
  double muglobal     = gConfigParser -> readDoubleOption("Selection::muglobal");
  
  double mudzPV     = gConfigParser -> readDoubleOption("Selection::mudzPV");
  double mudxyPV    = gConfigParser -> readDoubleOption("Selection::mudxyPV");
  
  
  Selections.push_back(muCombinedIso);
  Selections.push_back(muChi2Ndof);
  Selections.push_back(muValidTrackerHits);
  Selections.push_back(muValidMuonHits);
  Selections.push_back(mutracker);
  Selections.push_back(mustandalone);
  Selections.push_back(muglobal);
  Selections.push_back(mudzPV);
  Selections.push_back(mudxyPV);
  
    
/*  
  Selections.push_back(0.15); ///==== iso Combined
  Selections.push_back(10); ///==== Chi2/ndof
  Selections.push_back(10); ///==== n ValidTrackerHits
  Selections.push_back(0); ///==== n ValidMuonHits
  Selections.push_back(1); ///==== tracker
  Selections.push_back(1); ///==== standalone
  Selections.push_back(1); ///==== global
  //Selections.push_back(1); ///==== goodMuon
  */
  
  
  double start, end;
  std::cout << ">>>>> analysis::entryMIN " << entryMIN << " ==> entryMAX " << entryMAX << ":" << reader.GetEntries() << std::endl;   
  
  int step = 0;
  start = clock();
  for(int iEvent = entryMIN ; iEvent < entryMAX ; ++iEvent) {
   reader.GetEntry(iEvent);
   if((iEvent%entryMOD) == 0) std::cout << ">>>>> analysis::GetEntry " << iEvent << " : " << entryMAX - entryMIN << std::endl;   
   
  ///==== define variables ==== 
  std::vector<ROOT::Math::XYZTVector>* jets = reader.Get4V("jets");
//   std::vector<ROOT::Math::XYZTVector>* muons = reader.Get4V("muons");
//   std::vector<ROOT::Math::XYZTVector>* electrons = reader.Get4V("electrons");
    
  ///*********************************************************************************************
  ///*********************************************************************************************
  
  ///=============================
  ///==== fill MC information ====
  SetMCVariables(vars, reader);
  
  ///=============================
  ///==== fill Primary Vertex ====
  SetPVVariables(vars, reader);
  
  ///================================
  ///==== fill Event information ====
  SetEventVariables(vars, reader);
  
  ///***************************************************
  ///**** STEP -1 - Check no copies in DATA ****
  ///***************************************************
  if (debug) std::cout << " STEP -1 " << std::endl;
  
  if( dataFlag == 1 )
  {
   std::pair<int,int> eventLSandID(reader.GetInt("lumiId")->at(0), reader.GetInt("eventId")->at(0));
   std::pair<int,std::pair<int,int> > eventRUNandLSandID(reader.GetInt("runId")->at(0), eventLSandID);
   
   if( eventsMap[eventRUNandLSandID] == 1 ) continue;
   else eventsMap[eventRUNandLSandID] = 1;
  }

  ///*************************************************
  ///**** Check comparison with JSON file ***
  ///*************************************************


  if( dataFlag == 1 )
    {
      int runId  = reader.GetInt("runId")->at(0);
      int lumiId = reader.GetInt("lumiId")->at(0);
      if(AcceptEventByRunAndLumiSection(runId, lumiId, jsonMap) == false) continue;      
    }


  
  ///****************************
  ///**** STEP 0 - Ntuplizer ****
  ///************* no additional selections applied 

  step = 0;  
  if (step > nStepToDo) {
   FillTree(vars);
   continue;
  }
  if (debug) std::cout << ">>> STEP 0 <<<" << std::endl;
   
   ///*********************************************
  ///**** STEP 1 - Jet cleaning + min pT ****
  ///************* it's performed another time here to make sure that the cleaning worked well
  ///************* Jet - electrons (pT > 5)
  ///************* Jet - muons     (pT > 5)
  ///************ In addition only jets with pT > 15 are considered from now on!
  ///************ No selections are applied here
   
  step = 1;
  if (step > nStepToDo) {
//    FillTree(vars);
   continue;
  }  
  if (debug) std::cout << ">>> STEP 1 <<<" << std::endl;
  
  std::vector<ROOT::Math::XYZTVector> leptons_jetCleaning;   
  // build the collection of electros for jet cleaning
  
  ///==== CLEANING WITH ELECTRONS ====
  for(unsigned int iEle = 0; iEle < (reader.Get4V("electrons")->size()); ++iEle)
  {
   if( reader.Get4V("electrons")->at(iEle).pt() < 5. ) continue;
//    bool flag =  IsEleIsolatedID_VBF(reader,BarrelSelections,EndcapSelections,iEle);
   bool flag =  IsEleIsolatedIDPUCorrected_VBF(reader,BarrelSelections,EndcapSelections,iEle);
   
   if (!flag) continue;
   
   leptons_jetCleaning.push_back( reader.Get4V("electrons")->at(iEle) );
  }
  
  ///==== CLEANING WITH MUONS ====
  for (int iMu = 0; iMu < reader.Get4V("muons")->size(); iMu++){    
   if (reader.Get4V("muons")->at(iMu).pt() < 5.0) continue;
   if (fabs(reader.Get4V("muons")->at(iMu).Eta()) > 2.5) continue;
//    bool flag =  IsMuIsolatedID_VBF(reader,Selections,iMu);
   bool flag =  IsMuIsolatedIDPUCorrected_VBF(reader,Selections,iMu);
   
   if (!flag) continue;

   leptons_jetCleaning.push_back( reader.Get4V("muons")->at(iMu) );
  }
  
  
  ///==== now clean jet collection ====
  
  int nJets = reader.Get4V("jets")->size();
  std::vector<int> whitelistJet; ///~~~~ all jets, 0 if rejected, 1 if accepted
  std::vector<int> blacklistJet; ///~~~~ list of numbers of jets that are "rejected"
  std::vector<int> blacklistJet_forCJV;
  std::vector<int> blacklistJet_forBtag;
  for (int iJet = 0; iJet < nJets; iJet++){
   bool skipJet = false;
   if (reader.Get4V("jets")->at(iJet).Et() < 15.0) skipJet = true;
   for(unsigned int iLep = 0; iLep < leptons_jetCleaning.size(); ++iLep) {
    ROOT::Math::XYZTVector lep = leptons_jetCleaning.at(iLep);
    if (ROOT::Math::VectorUtil::DeltaR(reader.Get4V("jets")->at(iJet),lep) < 0.3 ) skipJet = true;
   }
   if (skipJet) {
    whitelistJet.push_back(0); ///---- reject
    blacklistJet.push_back(iJet); ///---- reject ///== black list is in a different format
    blacklistJet_forCJV.push_back(iJet); ///---- reject ///== black list is in a different format
    blacklistJet_forBtag.push_back(iJet); ///---- reject ///== black list is in a different format
   }
   else {
    whitelistJet.push_back(1); ///---- select
   }
  }
     
   ///**************************************
   ///**** STEP 2 - Super-Preselections ****
   ///************* tighter preselections to start the analysis from the same point
   ///==== construct considered objets
   ///    Objects considered and selections
   
   ///   Muon
   ///   Pt>10GeV, eta<2.5
   ///   MuonId & Iso
   ///
   ///   Electron
   ///   Pt>10GeV & |eta|<2.5
   ///   eleId & Iso
   ///
   ///    At least two leptons 
   
   ///   Jet
   ///   Antikt5, L2L3 correction jets
   ///   At least two calo jets or two pf jets with pt>15 GeV
   
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
  step = 2;
  if (step > nStepToDo) {
//    FillTree(vars);
   continue;
  }  
  if (debug) std::cout << ">>> STEP 2 <<<" << std::endl;
  
   ///   Electron
   ///   Pt>10GeV & |eta|<2.5
   ///   IsoTr / pTele <0.5
  ///   eleId & Iso
  std::vector<int> whitelistEle;
  std::vector<int> blacklistEle;
  int nEles = reader.Get4V("electrons")->size();
  for (int iEle = 0; iEle < nEles; iEle++){    
   bool skipEle = false;
   if (reader.Get4V("electrons")->at(iEle).pt() < 10.0) skipEle = true;
   if (fabs(reader.Get4V("electrons")->at(iEle).Eta()) > 2.5) skipEle = true;
//    bool flag =  IsEleIsolatedID_VBF(reader,BarrelSelections,EndcapSelections,iEle);
   bool flag =  IsEleIsolatedIDPUCorrected_VBF(reader,BarrelSelections,EndcapSelections,iEle);
   if (!flag) skipEle = true;
   
   if (skipEle) {
    whitelistEle.push_back(0); ///---- reject
    blacklistEle.push_back(iEle); ///---- reject ///== black list is in a different format
   }
   else {
    whitelistEle.push_back(1); ///---- select
   }
  }
       
   ///   Muon
   ///   Pt>10GeV, eta<2.5
   ///   MuonId & Iso
   std::vector<int> whitelistMu;
   std::vector<int> blacklistMu;
   int nMus = reader.Get4V("muons")->size();
   for (int iMu = 0; iMu < nMus; iMu++){    
    bool skipMu = false;
    if (reader.Get4V("muons")->at(iMu).pt() < 10.0) skipMu = true;
    if (fabs(reader.Get4V("muons")->at(iMu).Eta()) > 2.5) skipMu = true;    
//     bool flag =  IsMuIsolatedID_VBF(reader,Selections,iMu);
    bool flag =  IsMuIsolatedIDPUCorrected_VBF(reader,Selections,iMu);
    
    if (!flag) skipMu = true;

    if (skipMu) {
     whitelistMu.push_back(0); ///---- reject
     blacklistMu.push_back(iMu); ///---- reject ///== black list is in a different format
    }
    else {
     whitelistMu.push_back(1); ///---- select
    }
   }
      
   ///   At least 2 leptons
   
   int numMus_Accepted = GetNumList(whitelistMu);
   int numEles_Accepted = GetNumList(whitelistEle);
   
   int numLeptons_Accepted = numMus_Accepted + numEles_Accepted;
   if (numLeptons_Accepted < 2) continue;
   
   ///   Jet
   ///   At least two calo jets or two pf jets with pt>20 GeV
   
   int numJets_Accepted = GetNumList(whitelistJet);
   if (numJets_Accepted < 2) continue; ///==== at least 2 jets "isolated"
   
  ///*************************
  ///**** STEP 3 - Jet ID ****
  ///************* Identification of two tag jets

  step = 3;
  if (step > nStepToDo) {
//    FillTree(vars);
   continue;
  }  
  if (debug) std::cout << ">>> STEP 3 <<<" << std::endl;
  
  
  std::vector<int> itSelJet;
  double maxPt_jets_selected = SelectJets(itSelJet,*jets,"maxSumPt",-1.,&blacklistJet);
  
  int q1 = itSelJet.at(0);
  int q2 = itSelJet.at(1);
  ///---- check Pt order ----
  if (jets->at(q1).Pt() < jets->at(q2).Pt()) {
   int tempq = q1;
   q1 = q2;
   q2 = tempq;
  }

if (debug) std::cerr << " q1 = " << q1 << " : q2 = " << q2 << std::endl;


  ///---- update white/black list jets ----
  for (int iJet = 0; iJet < nJets; iJet++){
   if (q1 == iJet || q2 == iJet) {
    whitelistJet.at(iJet) = 1;
    blacklistJet.push_back(iJet); ///===>  blacklistJet used for CJV => no 2 tag jets to be considered!
    blacklistJet_forCJV.push_back(iJet); ///===>  blacklistJet used for CJV => no 2 tag jets to be considered!
   }
   else {
    whitelistJet.at(iJet) = 0;
   }
  }

 SetQJetVariables(vars, reader, q1, q2, blacklistJet_forCJV, blacklistJet_forBtag);

  ///********************************
  ///**** STEP 4 - Lepton ID ****
  ///************* Identification of the two leptons
  step = 4;
  if (step > nStepToDo) {
   FillTree(vars);
   continue;
  }  
  if (debug) std::cout << ">>> STEP 4 <<<" << std::endl;
  

  std::vector<ROOT::Math::XYZTVector> leptons;
  std::vector<int> leptonFlavours;    
  std::vector<int> leptonILep;    
  
  for(unsigned int iEle = 0; iEle < nEles; iEle++){
   if (whitelistEle.at(iEle) == 1){
    leptons.push_back( reader.Get4V("electrons")->at(iEle) );  
    leptonFlavours.push_back(11);
    leptonILep.push_back(iEle);
   }
  }
  
  for(unsigned int iMu = 0; iMu < nMus; iMu++){
   if (whitelistMu.at(iMu) == 1){
    leptons.push_back( reader.Get4V("muons")->at(iMu) );      
    leptonFlavours.push_back(13);
    leptonILep.push_back(iMu);
   }
  }
  
  std::vector<int> itSelLep;
  double maxPt_lept_selected = SelectJets(itSelLep,leptons,"maxSumPt",-1.,0);
  
  int l1 = itSelLep.at(0);
  int l2 = itSelLep.at(1);
  ///---- check Pt order ----
  if (leptons.at(l1).Pt() < leptons.at(l2).Pt()) {
   int templ = l1;
   l1 = l2;
   l2 = templ;
  }
  
  if (debug) std::cerr << " l1 = " << l1 << " : l2 = " << l2 << std::endl;
  
  SetLeptonsVariables(vars, reader, leptonILep.at(l1), leptonILep.at(l2),leptonFlavours.at(l1), leptonFlavours.at(l2));
  
  if (debug) std::cerr << ">> Lepton variables set" << std::endl;
  
  
  SetMetVariables(vars, reader, "PFMet", leptonILep.at(l1), leptonILep.at(l2),leptonFlavours.at(l1), leptonFlavours.at(l2));
  if (debug) std::cerr << ">> MET variables set" << std::endl;
   
   
  //---- lepton veto
  std::vector<int> blacklistLepton;
  blacklistLepton.push_back(l1);
  blacklistLepton.push_back(l2);
  
  vars.Nleptons_pT5  = getNumberPTThreshold(leptons,  5, &blacklistLepton);
  vars.Nleptons_pT10 = getNumberPTThreshold(leptons, 10, &blacklistLepton);
  vars.Nleptons_pT15 = getNumberPTThreshold(leptons, 15, &blacklistLepton);
  vars.Nleptons_pT20 = getNumberPTThreshold(leptons, 20, &blacklistLepton);
  vars.Nleptons_pT25 = getNumberPTThreshold(leptons, 25, &blacklistLepton);
  vars.Nleptons_pT30 = getNumberPTThreshold(leptons, 30, &blacklistLepton);

  if (debug) std::cerr << ">> Lepton multiplicity set" << std::endl;
  
  
  ///*********************************
  ///**** STEP 5 - Jet Selections ****
  ///************* Loose selections of tag jets
  step = 5;
  if (step > nStepToDo) {
   FillTree(vars);
   continue;
  }  
  if (debug) std::cout << ">>> STEP 5 <<<" << std::endl;
  
  ///----  hardcoded fixed preselections ---- VBF (begin) ----
  if (vars.q1_pT < 20.) continue;
  if (vars.q2_pT < 15.) continue;
  if (vars.M_qq <   0.) continue;
  if (vars.DEta_qq < 0.) continue;
  ///----  hardcoded fixed preselections ---- VBF (end) ----

  ///==== save trigger variables ====
  SetTriggerVariables(vars, reader);
  
  ///************************************
  ///**** STEP 6 - Final Production *****
  ///************************************
  ///**** No more selections applied ****

  step = 6;
  if (step > nStepToDo) {
   FillTree(vars);
   continue;
  }  
  if (debug) std::cout << ">>> STEP 6 <<<" << std::endl;

  ///==== if not already filled ... ====
  FillTree(vars);  
  ///=================================================
  
 }
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 SaveTree(vars);
 
 std::cerr << " === end === " << std::endl;
}


