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
 
 ///---- Efficiency preselections ---- 
 
 std::string treeNameLeptonFilter      = gConfigParser -> readStringOption("Input::treeNameLeptonFilter");
 std::string treeNameJetCounterFilter  = gConfigParser -> readStringOption("Input::treeNameJetCounterFilter");
 
 std::cout << ">>>>> Input::inputFile                 " << inputFile  << std::endl;  
 std::cout << ">>>>> Input::treeNameLeptonFilter      " << treeNameLeptonFilter  << std::endl;  
 std::cout << ">>>>> Input::treeNameJetCounterFilter  " << treeNameJetCounterFilter  << std::endl;  
 
 // Open ntples
 TFile File(inputFile.c_str()) ;
 TH1F* hLeptonFilterTotal = (TH1F*) File.Get(TString(treeNameLeptonFilter.c_str()) + "/totalEvents");
 TH1F* hLeptonFilterPassed = (TH1F*) File.Get(TString(treeNameLeptonFilter.c_str()) + "/passedEvents"); 
 
 TH1F* hJetCounterFilterTotal = (TH1F*) File.Get(TString(treeNameJetCounterFilter.c_str()) + "/totalEvents");
 TH1F* hJetCounterFilterPassed = (TH1F*) File.Get(TString(treeNameJetCounterFilter.c_str()) + "/passedEvents"); 
 
 ///----------------------
 ///---- LeptonFilter ----
 
 int nLeptonFilterTotal = hLeptonFilterTotal->GetEntries();
 int nLeptonFilterPassed = hLeptonFilterPassed->GetEntries();
 double lepton_efficiency = static_cast<double>(nLeptonFilterPassed) / static_cast<double>(nLeptonFilterTotal);
 std::cout << " Lepton Filter = " << nLeptonFilterPassed << " / " << nLeptonFilterTotal << " = " << static_cast<double>(nLeptonFilterPassed) / static_cast<double>(nLeptonFilterTotal) << std::endl;
 
 
 ///--------------------------
 ///---- JetCounterFilter ----
 
 int nJetCounterFilterTotal = hJetCounterFilterTotal->GetEntries();
 int nJetCounterFilterPassed = hJetCounterFilterPassed->GetEntries();
 double jet_efficiency = static_cast<double>(nJetCounterFilterPassed) / static_cast<double>(nJetCounterFilterTotal);
 std::cout << " JetCounter Filter = " << nJetCounterFilterPassed << " / " << nJetCounterFilterTotal << " = " << static_cast<double>(nJetCounterFilterPassed) / static_cast<double>(nJetCounterFilterTotal) << std::endl;
 
 
 ///-----------------------------------
 ///---- additional channel filter ----
 
 double eff_Channel_Filter = 1.;
 if ((TH1F*) File.Get(TString("eff_ee"))) {
  TH1F* hChannelFilter = (TH1F*) File.Get(TString("eff_ee"));
  eff_Channel_Filter = hChannelFilter->GetBinContent(1);
 }
 if ((TH1F*) File.Get(TString("eff_emu"))) {
  TH1F* hChannelFilter = (TH1F*) File.Get(TString("eff_emu"));
  eff_Channel_Filter = hChannelFilter->GetBinContent(1);
 }
 if ((TH1F*) File.Get(TString("eff_mumu"))) {
  TH1F* hChannelFilter = (TH1F*) File.Get(TString("eff_mumu"));
  eff_Channel_Filter = hChannelFilter->GetBinContent(1);
 }
 if ((TH1F*) File.Get(TString("eff_other"))) {
  TH1F* hChannelFilter = (TH1F*) File.Get(TString("eff_other"));
  eff_Channel_Filter = hChannelFilter->GetBinContent(1);
 }
 
 ///----------------------
 ///---- Preselection ----
 
 double preselection_efficiency = lepton_efficiency * jet_efficiency * eff_Channel_Filter;
 std::cout << " Preselection efficiency = " << preselection_efficiency << std::endl;
 
 
 
 ///-------------------
 ///---- selection ----
 std::string OutFileNameEfficiencies    = gConfigParser -> readStringOption("Output::OutFileNameEfficiencies");
 std::cout << ">>>>> Output::OutFileNameEfficiencies  " << OutFileNameEfficiencies  << std::endl;  
 
 TFile outFile(OutFileNameEfficiencies.c_str(),"RECREATE");
 
 int nStep = 10; ///==== number of steps in the analysis
 TH1F* events = new TH1F("events", "events", nStep+1, 0., 1.*(nStep+1));
 std::map<int, int> stepEvents;
 std::map<int, std::string> stepName;
 
 outFile.mkdir("histos");
 outFile.cd("histos");
 
 stdHisto* stdHistograms = new stdHisto(nStep, "no",&reader);
 stdHistograms -> Add1("jets", nStep);
 stdHistograms -> Add1("muons", nStep);
 stdHistograms -> Add1Float("muIso", nStep,2000,0,2);
 stdHistograms -> Add1("electrons", nStep);
 stdHistograms -> Add1Float("eleIso", nStep,2000,0,2);
 stdHistograms -> Add1("met", nStep);
 stdHistograms -> Add2("JJ", nStep);
 stdHistograms -> Add2("ll", nStep);
 
 outFile.cd();
 
 double analysisEfficiency; 
 double XSection = inputXSection;
 int numEntriesBefore;
  
 TTree outTreeSelections("outTreeSelections","outTreeSelections");
 outTreeSelections.Branch("XSection",&XSection,"XSection/D");
 outTreeSelections.Branch("lepton_efficiency",&lepton_efficiency,"lepton_efficiency/D");
 outTreeSelections.Branch("jet_efficiency",&jet_efficiency,"jet_efficiency/D");
 outTreeSelections.Branch("preselection_efficiency",&preselection_efficiency,"preselection_efficiency/D");
 outTreeSelections.Branch("eff_Channel_Filter",&eff_Channel_Filter,"eff_Channel_Filter/D");
 outTreeSelections.Branch("numEntriesBefore",&numEntriesBefore,"numEntriesBefore/I");
 outTreeSelections.Branch("analysisEfficiency",&analysisEfficiency,"analysisEfficiency/D");
 
 
 ///==============
 ///==== Jets ====
 
 TTree outTreeJetLep("outTreeJetLep","outTreeJetLep");
 
 double bTag_trackCountingHighPurBJetTags_q1;
 double bTag_trackCountingHighEffBJetTags_q1;
 double bTag_combinedSecondaryVertexBJetTags_q1;
 double bTag_combinedSecondaryVertexMVABJetTags_q1;
 
 double bTag_trackCountingHighPurBJetTags_q2;
 double bTag_trackCountingHighEffBJetTags_q2;
 double bTag_combinedSecondaryVertexBJetTags_q2;
 double bTag_combinedSecondaryVertexMVABJetTags_q2; 
 
 double tkIso_l1;
 double emIso_l1;
 double hadIso_l1;

 double tkIso_l2;
 double emIso_l2;
 double hadIso_l2;
  
 double pT_RECO_q1;
 double pT_RECO_q2;
 double phi_RECO_q1;
 double phi_RECO_q2;
 double eta_RECO_q1;
 double eta_RECO_q2;
 double eta_RECO_q1_eta_RECO_q2;
 double Deta_RECO_q12;
 double Mjj;
 int NBjets_trackCountingHighPurBJetTags;
 int NBjets_trackCountingHighEffBJetTags;
 int NBjets_combinedSecondaryVertexBJetTags;
 int NBjets_combinedSecondaryVertexMVABJetTags;
 int NBjets_simpleSecondaryVertexBJetTags;
 int JV_20;
 int JV_30;
 int CJV_20;
 int CJV_30;
 int Z_01_30;
 int Z_03_30;
 int Z_05_30;
 int Z_07_30;
 int Z_09_30;
 int Z_10_30;
 int Z_12_30;
 int Z_14_30;
 int Z_01_20;
 int Z_03_20;
 int Z_05_20;
 int Z_07_20;
 int Z_09_20;
 int Z_10_20;
 int Z_12_20;
 int Z_14_20;
 
 double MET;
 
 int AnalysisStep; 
  

 outTreeJetLep.Branch("bTag_trackCountingHighPurBJetTags_q1",&bTag_trackCountingHighPurBJetTags_q1,"bTag_trackCountingHighPurBJetTags_q1/D");
 outTreeJetLep.Branch("bTag_trackCountingHighEffBJetTags_q1",&bTag_trackCountingHighEffBJetTags_q1,"bTag_trackCountingHighEffBJetTags_q1/D");
 outTreeJetLep.Branch("bTag_combinedSecondaryVertexBJetTags_q1",&bTag_combinedSecondaryVertexBJetTags_q1,"bTag_combinedSecondaryVertexBJetTags_q1/D");
 outTreeJetLep.Branch("bTag_combinedSecondaryVertexMVABJetTags_q1",&bTag_combinedSecondaryVertexMVABJetTags_q1,"bTag_combinedSecondaryVertexMVABJetTags_q1/D");
 
 outTreeJetLep.Branch("bTag_trackCountingHighPurBJetTags_q2",&bTag_trackCountingHighPurBJetTags_q2,"bTag_trackCountingHighPurBJetTags_q2/D");
 outTreeJetLep.Branch("bTag_trackCountingHighEffBJetTags_q2",&bTag_trackCountingHighEffBJetTags_q2,"bTag_trackCountingHighEffBJetTags_q2/D");
 outTreeJetLep.Branch("bTag_combinedSecondaryVertexBJetTags_q2",&bTag_combinedSecondaryVertexBJetTags_q2,"bTag_combinedSecondaryVertexBJetTags_q2/D");
 outTreeJetLep.Branch("bTag_combinedSecondaryVertexMVABJetTags_q2",&bTag_combinedSecondaryVertexMVABJetTags_q2,"bTag_combinedSecondaryVertexMVABJetTags_q2/D");
 
 
 outTreeJetLep.Branch("tkIso_l1",&tkIso_l1,"tkIso_l1/D");
 outTreeJetLep.Branch("emIso_l1",&emIso_l1,"emIso_l1/D");
 outTreeJetLep.Branch("hadIso_l1",&hadIso_l1,"hadIso_l1/D");
 outTreeJetLep.Branch("tkIso_l2",&tkIso_l2,"tkIso_l2/D");
 outTreeJetLep.Branch("emIso_l2",&emIso_l2,"emIso_l2/D");
 outTreeJetLep.Branch("hadIso_l2",&hadIso_l2,"hadIso_l2/D");
 
 
 outTreeJetLep.Branch("pT_RECO_q1",&pT_RECO_q1,"pT_RECO_q1/D");
 outTreeJetLep.Branch("pT_RECO_q2",&pT_RECO_q2,"pT_RECO_q2/D");
 outTreeJetLep.Branch("phi_RECO_q1",&phi_RECO_q1,"phi_RECO_q1/D");
 outTreeJetLep.Branch("phi_RECO_q2",&phi_RECO_q2,"phi_RECO_q2/D");
 outTreeJetLep.Branch("eta_RECO_q1",&eta_RECO_q1,"eta_RECO_q1/D");
 outTreeJetLep.Branch("eta_RECO_q2",&eta_RECO_q2,"eta_RECO_q2/D");
 outTreeJetLep.Branch("eta_RECO_q1_eta_RECO_q2",&eta_RECO_q1_eta_RECO_q2,"eta_RECO_q1_eta_RECO_q2/D");
 outTreeJetLep.Branch("Deta_RECO_q12",&Deta_RECO_q12,"Deta_RECO_q12/D");
 outTreeJetLep.Branch("Mjj",&Mjj,"Mjj/D");
 outTreeJetLep.Branch("JV_20",&JV_20,"JV_20/I");
 outTreeJetLep.Branch("JV_30",&JV_30,"JV_30/I");
 outTreeJetLep.Branch("CJV_20",&CJV_20,"CJV_20/I");
 outTreeJetLep.Branch("CJV_30",&CJV_30,"CJV_30/I");
 outTreeJetLep.Branch("AnalysisStep",&AnalysisStep,"AnalysisStep/I");
 
 outTreeJetLep.Branch("Z_01_30",&Z_01_30,"Z_01_30/I");
 outTreeJetLep.Branch("Z_03_30",&Z_03_30,"Z_03_30/I");
 outTreeJetLep.Branch("Z_05_30",&Z_05_30,"Z_05_30/I");
 outTreeJetLep.Branch("Z_07_30",&Z_07_30,"Z_07_30/I");
 outTreeJetLep.Branch("Z_09_30",&Z_09_30,"Z_09_30/I");
 outTreeJetLep.Branch("Z_10_30",&Z_10_30,"Z_10_30/I");
 outTreeJetLep.Branch("Z_12_30",&Z_12_30,"Z_12_30/I");
 outTreeJetLep.Branch("Z_14_30",&Z_14_30,"Z_14_30/I");

 outTreeJetLep.Branch("Z_01_20",&Z_01_20,"Z_01_20/I");
 outTreeJetLep.Branch("Z_03_20",&Z_03_20,"Z_03_20/I");
 outTreeJetLep.Branch("Z_05_20",&Z_05_20,"Z_05_20/I");
 outTreeJetLep.Branch("Z_07_20",&Z_07_20,"Z_07_20/I");
 outTreeJetLep.Branch("Z_09_20",&Z_09_20,"Z_09_20/I");
 outTreeJetLep.Branch("Z_10_20",&Z_10_20,"Z_10_20/I");
 outTreeJetLep.Branch("Z_12_20",&Z_12_20,"Z_12_20/I");
 outTreeJetLep.Branch("Z_14_20",&Z_14_20,"Z_14_20/I");
 
 outTreeJetLep.Branch("MET",&MET,"MET/D");
 
 outTreeJetLep.Branch("NBjets_trackCountingHighPurBJetTags",&NBjets_trackCountingHighPurBJetTags,"NBjets_trackCountingHighPurBJetTags/I");
 outTreeJetLep.Branch("NBjets_trackCountingHighEffBJetTags",&NBjets_trackCountingHighEffBJetTags,"NBjets_trackCountingHighEffBJetTags/I");
 outTreeJetLep.Branch("NBjets_combinedSecondaryVertexBJetTags",&NBjets_combinedSecondaryVertexBJetTags,"NBjets_combinedSecondaryVertexBJetTags/I");
 outTreeJetLep.Branch("NBjets_combinedSecondaryVertexMVABJetTags",&NBjets_combinedSecondaryVertexMVABJetTags,"NBjets_combinedSecondaryVertexMVABJetTags/I");
 
 outTreeJetLep.Branch("NBjets_simpleSecondaryVertexBJetTags",&NBjets_simpleSecondaryVertexBJetTags,"NBjets_simpleSecondaryVertexBJetTags/I");
 

  
  ///=================
  ///==== leptons ====
  
 
//  TTree outTreeJetLep("outTreeJetLep","outTreeJetLep");
 int pdgId_RECO_l1;
 int pdgId_RECO_l2;
 double pT_RECO_l1;
 double pT_RECO_l2;
 double eta_RECO_l1;
 double eta_RECO_l2;
 double eta_RECO_l1_eta_RECO_l2;
 double Deta_RECO_l12;
 double Dphi_RECO_l12;
 double Mll;
 double charge_RECO_l1_charge_RECO_l2;
 
 double Z_l1;
 double Z_l2;
 
 
 outTreeJetLep.Branch("pdgId_RECO_l1",&pdgId_RECO_l1,"pdgId_RECO_l1/I");
 outTreeJetLep.Branch("pdgId_RECO_l2",&pdgId_RECO_l2,"pdgId_RECO_l2/I");
 outTreeJetLep.Branch("pT_RECO_l1",&pT_RECO_l1,"pT_RECO_l1/D");
 outTreeJetLep.Branch("pT_RECO_l2",&pT_RECO_l2,"pT_RECO_l2/D");
 outTreeJetLep.Branch("eta_RECO_l1",&eta_RECO_l1,"eta_RECO_l1/D");
 outTreeJetLep.Branch("eta_RECO_l2",&eta_RECO_l2,"eta_RECO_l2/D");
 outTreeJetLep.Branch("eta_RECO_l1_eta_RECO_l2",&eta_RECO_l1_eta_RECO_l2,"eta_RECO_l1_eta_RECO_l2/D");
 outTreeJetLep.Branch("Deta_RECO_l12",&Deta_RECO_l12,"Deta_RECO_l12/D");
 outTreeJetLep.Branch("Dphi_RECO_l12",&Dphi_RECO_l12,"Dphi_RECO_l12/D");
 outTreeJetLep.Branch("Mll",&Mll,"Mll/D");
 outTreeJetLep.Branch("charge_RECO_l1_charge_RECO_l2",&charge_RECO_l1_charge_RECO_l2,"charge_RECO_l1_charge_RECO_l2/D");
 outTreeJetLep.Branch("AnalysisStep",&AnalysisStep,"AnalysisStep/I");
 outTreeJetLep.Branch("Z_l1",&Z_l1,"Z_l1/D");
 outTreeJetLep.Branch("Z_l2",&Z_l2,"Z_l2/D");
 
 double start, end;
 
 if (entryMAX == -1) entryMAX = reader.GetEntries();
 else if (reader.GetEntries() < entryMAX) entryMAX = reader.GetEntries();
 numEntriesBefore = entryMAX - entryMIN;
 
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
  ///*********************************************************************************************
  ///*********************************************************************************************
  
  ///****************************
  ///**** STEP 0 - Ntuplizer ****
  ///************* no additional selections applied
  
  step = 0;  
  if (step > nStepToDo) {
   outTreeJetLep.Fill();
   continue;
  }  
  stepName[step] = "Jet cleaning";
  stepEvents[step] += 1;
  
  ///==== filling ====
  stdHistograms -> Fill1("muons","muons",step,0);
  stdHistograms -> Fill1("electrons","electrons",step,0);
  stdHistograms -> Fill1("jets","jets",step,0);
  stdHistograms -> Fill1("met","met",step,0); 
  
  
  ///*******************************
  ///**** STEP 1 - Jet cleaning ****
  ///************* it's performed another time here to make sure that the cleaning worked well
  ///************* possible problems with electron ID
    
  step = 1;
  if (step > nStepToDo) {
   outTreeJetLep.Fill();
   continue;
  }  
    
  std::vector<ROOT::Math::XYZTVector> electrons_jetCleaning;   
  // build the collection of electros for jet cleaning
  for(unsigned int eleIt = 0; eleIt < (reader.Get4V("electrons")->size()); ++eleIt)
  {
   if( reader.Get4V("electrons")->at(eleIt).pt() < 5. ) continue;
   if( (reader.GetFloat("electrons_tkIso")->at(eleIt)) / reader.Get4V("electrons")->at(eleIt).pt() > 0.5 ) continue;
   if( (reader.GetFloat("electrons_IdRobustLoose")->at(eleIt)) < 1. ) continue; 
   electrons_jetCleaning.push_back( reader.Get4V("electrons")->at(eleIt) );
  }
  
  int nJets = jets->size();
  std::vector<int> whitelistJet;
  std::vector<int> blacklistJet;
  std::vector<int> blacklistJet_forCJV;
  std::vector<int> blacklistJet_forBtag;
  for (int iJet = 0; iJet < nJets; iJet++){
   bool skipJet = false;
   if (jets->at(iJet).Et() < 10.0) skipJet = true;
   for(unsigned int eleIt = 0; eleIt < electrons_jetCleaning.size(); eleIt++) {
    ROOT::Math::XYZTVector ele = electrons_jetCleaning.at(eleIt);
    if (ROOT::Math::VectorUtil::DeltaR(jets->at(iJet),ele) < 0.3 ) skipJet = true;
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
  
  if (GetNumList(whitelistJet) < 2) continue; ///==== at least 2 jets "isolated"
 
   
  stepName[step] = "Jet cleaning";
  stepEvents[step] += 1;
  
  ///==== filling ====
  stdHistograms -> Fill1("muons","muons",step,0);
  stdHistograms -> Fill1("electrons","electrons",step,0);
  stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
  stdHistograms -> Fill1("met","met",step,0); 
  
   
  
   ///**************************************
   ///**** STEP 2 - Super-Preselections ****
   ///************* tighter preselections to start the analysis from the same point

   ///==== construct considered objets
   ///    Objects considered
   
   ///   Muon
   ///   PromptTightMuonID
   ///   Pt>10GeV, eta<2.5
   ///   IsoTr / pTmu <0.5
   
   ///   Electron
   ///   Pt>10GeV & |eta|<2.5
   ///   IsoTr / pTele <0.5
   ///   eidRobustLoose   
   
   ///   Jet
   ///   Antikt5, L2L3 correction, Pt>30GeV & |eta|<5
   
   ///   Remove jet with
   ///   a lepton(e/mu) with pt>10GeV in cone=0.3
   ///   or
   ///   an electron (the ones defined above) in cone=0.1
   
   
   
   ///   Preselections
   
   ///   At least 2 leptons
   ///   Muon (from the collections defined above)
   ///   Pt > 15 GeV
   
   ///   Electron (from the collection defined above)
   ///   Pt>15 GeV
   
   ///   At least two calo jets or two pf jets with pt>30GeV
   ///   Jets (from the collection defined above)
   
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
  step = 2;
  if (step > nStepToDo) {
   outTreeJetLep.Fill();
   continue;
  }  
  
   ///   Electron
   ///   Pt>10GeV & |eta|<2.5
   ///   IsoTr / pTele <0.5
   ///   eidRobustLoose   
   std::vector<int> whitelistEle;
   std::vector<int> blacklistEle;
   int nEles = reader.Get4V("electrons")->size();
   for (int iEle = 0; iEle < nEles; iEle++){    
    bool skipEle = false;
    if (reader.Get4V("electrons")->at(iEle).pt() < 10.0) skipEle = true;
    if (fabs(reader.Get4V("electrons")->at(iEle).Eta()) > 2.5) skipEle = true;
    if ( (reader.GetFloat("electrons_tkIso")->at(iEle)) / reader.Get4V("electrons")->at(iEle).pt() > 0.5 ) skipEle = true;
    if ( (reader.GetFloat("electrons_IdRobustLoose")->at(iEle)) < 1. )  skipEle = true;    
    
    if ( (reader.GetFloat("electrons_tkIso")->at(iEle)) / reader.Get4V("electrons")->at(iEle).pt() > 0.1 ) skipEle = true;
    if ( (reader.GetFloat("electrons_emIso03")->at(iEle)) / reader.Get4V("electrons")->at(iEle).pt() > 0.1 ) skipEle = true;
    if ( (reader.GetFloat("electrons_hadIso03_1")->at(iEle) + reader.GetFloat("electrons_hadIso03_2")->at(iEle)) / reader.Get4V("electrons")->at(iEle).pt() > 0.1 ) skipEle = true;
    
    if (skipEle) {
     whitelistEle.push_back(0); ///---- reject
     blacklistEle.push_back(iEle); ///---- reject ///== black list is in a different format
    }
    else {
     whitelistEle.push_back(1); ///---- select
    }
   }
   
//    std::cerr << "ciao!!!" << std::endl;
   
   
   ///   Muon
   ///   PromptTightMuonID
   ///   Pt>10GeV, eta<2.5
   ///   IsoTr / pTmu <0.5   
   std::vector<int> whitelistMu;
   std::vector<int> blacklistMu;
   int nMus = reader.Get4V("muons")->size();
//    std::cerr << "mu = " << nMus << std::endl;
   
   for (int iMu = 0; iMu < nMus; iMu++){    
    bool skipMu = false;
    if (reader.Get4V("muons")->at(iMu).pt() < 10.0) skipMu = true;
//     std::cerr << "mu = " << nMus << std::endl;
    
    if (fabs(reader.Get4V("muons")->at(iMu).Eta()) > 2.5) skipMu = true;
//     std::cerr << "mu = " << nMus << " " << reader.GetFloat("muons_tkIsoR03")->at(iMu) << std::endl;
    
    if ( (reader.GetFloat("muons_tkIsoR03")->at(iMu)) / reader.Get4V("muons")->at(iMu).pt() > 0.5 ) skipMu = true;
//     std::cerr << "mu = " << nMus << std::endl;
    
    if ( (reader.GetFloat("muons_tkIsoR03")->at(iMu)) / reader.Get4V("muons")->at(iMu).pt() > 0.1 ) skipMu = true;
    if ( (reader.GetFloat("muons_emIsoR03")->at(iMu)) / reader.Get4V("muons")->at(iMu).pt() > 0.1 ) skipMu = true;
    if ( (reader.GetFloat("muons_hadIsoR03")->at(iMu)) / reader.Get4V("muons")->at(iMu).pt() > 0.1 ) skipMu = true;
    
    if( (reader.GetInt("muons_goodMuon")->at(iMu)) < 1. )  skipMu = true;    
    if (skipMu) {
     whitelistMu.push_back(0); ///---- reject
     blacklistMu.push_back(iMu); ///---- reject ///== black list is in a different format
    }
    else {
     whitelistMu.push_back(1); ///---- select
    }
   }
   
//    std::cerr << "ele = " << nEles << std::endl;
   
   ///   Jet
   ///   Antikt5, L2L3 correction, Pt>30GeV & |eta|<5  
   ///   Remove jet with
   ///   a lepton(e/mu) with pt>10GeV in cone=0.3
   ///   or
   ///   an electron (the ones defined above) in cone=0.1
   electrons_jetCleaning.clear();
   // build the collection of electros for jet cleaning
   
//    std::cerr << "ele = " << nEles << std::endl;
   
   for(unsigned int iEle = 0; iEle < nEles; ++iEle)
   {
    if (whitelistEle.at(iEle) == 0) continue;
    electrons_jetCleaning.push_back( reader.Get4V("electrons")->at(iEle) );
   }
   for (int iJet = 0; iJet < nJets; iJet++){
    bool skipJet = false;
    if (whitelistJet.at(iJet) == 0) {
//      skipJet = true;
     continue; //---- otherwise blacklistJet.push_back(iJet) and blacklistJet becomes too long
     //-------------- and then it's faster!
    }   
    if (jets->at(iJet).Et() < 30.0) skipJet = true;
    if (jets->at(iJet).Eta() > 5.0) skipJet = true;
    for(unsigned int eleIt = 0; eleIt < electrons_jetCleaning.size(); eleIt++) {
     ROOT::Math::XYZTVector ele = electrons_jetCleaning.at(eleIt);
     if (ROOT::Math::VectorUtil::DeltaR(jets->at(iJet),ele) < 0.3 ) skipJet = true;
    }
    if (skipJet) {
     whitelistJet.at(iJet) = 0; ///---- reject
     blacklistJet.push_back(iJet); ///---- reject ///== black list is in a different format
    }
    else {
     whitelistJet.at(iJet) = 1; ///---- select
    }
   }
//    std::cerr << "ciao!!!" << std::endl;
   
   ///   At least 2 leptons
   ///   Muon (from the collections defined above)
   ///   Pt > 15 GeV
   int numLeptons_Accepted = 0;
   for (int iMu = 0; iMu < nMus; iMu++){  
    if (whitelistMu.at(iMu) == 1 && reader.Get4V("muons")->at(iMu).pt() > 15.0) numLeptons_Accepted++;
   }
   ///   Electron (from the collection defined above)
   ///   Pt>15 GeV
   for (int iEle = 0; iEle < nEles; iEle++){  
    if (whitelistEle.at(iEle) == 1 && reader.Get4V("electrons")->at(iEle).pt() > 15.0) numLeptons_Accepted++;
   }
   
//    std::cerr << "numLeptons_Accepted = " << numLeptons_Accepted << std::endl;
   
   if (numLeptons_Accepted < 2) continue;
   
   ///   At least two calo jets or two pf jets with pt>30GeV
   ///   Jets (from the collection defined above)
   int numJets_Accepted = 0;
   for (int iJet = 0; iJet < nJets; iJet++){  
    if (whitelistJet.at(iJet) == 1) numJets_Accepted++;
   }

// std::cerr << "numJets_Accepted = " << numJets_Accepted << " = " << GetNumList(whitelistJet) << " = " << nJets << " - " << blacklistJet.size() << std::endl;

   if (numJets_Accepted < 2) continue;
   
  
   ///==== filling ====
   stepName[step] = "Super Pre-Selections";
   stepEvents[step] += 1;
  
   stdHistograms -> Fill1("muons","muons",step,&whitelistMu);
   stdHistograms -> Fill1("electrons","electrons",step,&whitelistEle);
   stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
   stdHistograms -> Fill1("met","met",step,0); 
   
   
  ///*************************
  ///**** STEP 3 - Jet ID ****
  ///************* Identification of two tag jets
  step = 3;
  if (step > nStepToDo) {
   outTreeJetLep.Fill();
   continue;
  }  
  
  std::vector<int> itSelJet;
  double maxPt_jets_selected = SelectJets(itSelJet,*jets,"maxSumPt",-1.,&blacklistJet);
  
//   std::cerr << "itSelJet.at(0) = " << itSelJet.at(0) << " : " << nJets << std::endl;
//   std::cerr << "itSelJet.at(1) = " << itSelJet.at(1) << " : " << nJets << std::endl;
  
  
  int q1 = itSelJet.at(0);
  int q2 = itSelJet.at(1);
  ///---- check Pt order ----
  if (jets->at(q1).Pt() < jets->at(q2).Pt()) {
   int tempq = q1;
   q1 = q2;
   q2 = tempq;
  }
  
//   std::cerr << "here is ok" <<  std::endl;
  
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
  
  MET = reader.Get4V("met")->at(0).Et();
  
  
  bTag_trackCountingHighPurBJetTags_q1 = reader.GetFloat("jets_trackCountingHighPurBJetTags")->at(q1);
  bTag_trackCountingHighEffBJetTags_q1 = reader.GetFloat("jets_trackCountingHighEffBJetTags")->at(q1);
  bTag_combinedSecondaryVertexBJetTags_q1 = reader.GetFloat("jets_combinedSecondaryVertexBJetTags")->at(q1);
  bTag_combinedSecondaryVertexMVABJetTags_q1 = reader.GetFloat("jets_combinedSecondaryVertexMVABJetTags")->at(q1); 
  
  bTag_trackCountingHighPurBJetTags_q2 = reader.GetFloat("jets_trackCountingHighPurBJetTags")->at(q2);
  bTag_trackCountingHighEffBJetTags_q2 = reader.GetFloat("jets_trackCountingHighEffBJetTags")->at(q2);
  bTag_combinedSecondaryVertexBJetTags_q2 = reader.GetFloat("jets_combinedSecondaryVertexBJetTags")->at(q2);
  bTag_combinedSecondaryVertexMVABJetTags_q2 = reader.GetFloat("jets_combinedSecondaryVertexMVABJetTags")->at(q2); 
  
  pT_RECO_q1 = jets->at(q1).Pt();
  pT_RECO_q2 = jets->at(q2).Pt();
  phi_RECO_q1 = jets->at(q1).Phi();
  phi_RECO_q2 = jets->at(q2).Phi();
  eta_RECO_q1 = jets->at(q1).Eta();
  eta_RECO_q2 = jets->at(q2).Eta();
  eta_RECO_q1_eta_RECO_q2 = eta_RECO_q1 * eta_RECO_q2;
  Deta_RECO_q12 = fabs(eta_RECO_q1-eta_RECO_q2); 
  Mjj = (jets->at(q1) + jets->at(q2)).M();
  CJV_20 = getCJV(*jets,q1,q2,20.,&blacklistJet_forCJV);
  CJV_30 = getCJV(*jets,q1,q2,30.,&blacklistJet_forCJV);

  JV_20 = getJV(*jets,20.,&blacklistJet_forCJV);
  JV_30 = getJV(*jets,30.,&blacklistJet_forCJV);

  
  JV_20 = getJV(*jets,20.,&blacklistJet_forCJV);
  JV_30 = getJV(*jets,30.,&blacklistJet_forCJV);
   
  Z_01_30 = getZepp(*jets,q1,q2,30.,0.1,&blacklistJet_forCJV);
  Z_03_30 = getZepp(*jets,q1,q2,30.,0.3,&blacklistJet_forCJV);
  Z_05_30 = getZepp(*jets,q1,q2,30.,0.5,&blacklistJet_forCJV);
  Z_07_30 = getZepp(*jets,q1,q2,30.,0.7,&blacklistJet_forCJV);
  Z_09_30 = getZepp(*jets,q1,q2,30.,0.9,&blacklistJet_forCJV);
  Z_10_30 = getZepp(*jets,q1,q2,30.,1.0,&blacklistJet_forCJV);
  Z_12_30 = getZepp(*jets,q1,q2,30.,1.2,&blacklistJet_forCJV);
  Z_14_30 = getZepp(*jets,q1,q2,30.,1.4,&blacklistJet_forCJV);

  Z_01_20 = getZepp(*jets,q1,q2,20.,0.1,&blacklistJet_forCJV);
  Z_03_20 = getZepp(*jets,q1,q2,20.,0.3,&blacklistJet_forCJV);
  Z_05_20 = getZepp(*jets,q1,q2,20.,0.5,&blacklistJet_forCJV);
  Z_07_20 = getZepp(*jets,q1,q2,20.,0.7,&blacklistJet_forCJV);
  Z_09_20 = getZepp(*jets,q1,q2,20.,0.9,&blacklistJet_forCJV);
  Z_10_20 = getZepp(*jets,q1,q2,20.,1.0,&blacklistJet_forCJV);
  Z_12_20 = getZepp(*jets,q1,q2,20.,1.2,&blacklistJet_forCJV);
  Z_14_20 = getZepp(*jets,q1,q2,20.,1.4,&blacklistJet_forCJV);
   
  NBjets_trackCountingHighPurBJetTags = 0;
  NBjets_trackCountingHighEffBJetTags = 0;
  NBjets_combinedSecondaryVertexBJetTags = 0;
  NBjets_combinedSecondaryVertexMVABJetTags = 0;
  NBjets_simpleSecondaryVertexBJetTags = 0;
  
  for (int iJet = 0; iJet < nJets; iJet++){
   bool skipJet = false;
   for(unsigned int kk = 0; kk < blacklistJet_forBtag.size(); ++kk) {
    if(blacklistJet_forBtag.at(kk) == static_cast<int>(iJet)) skipJet = true;
   }
   if (reader.Get4V("jets")->at(iJet).pt() < 10.0) skipJet = true;
   if (skipJet) continue;
   if (reader.GetFloat("jets_trackCountingHighPurBJetTags")->at(iJet) > -50.0) NBjets_trackCountingHighPurBJetTags++;
   if (reader.GetFloat("jets_trackCountingHighEffBJetTags")->at(iJet) > -50.0) NBjets_trackCountingHighEffBJetTags++;
   if (reader.GetFloat("jets_combinedSecondaryVertexBJetTags")->at(iJet) > -5.0) NBjets_combinedSecondaryVertexBJetTags++;
   if (reader.GetFloat("jets_combinedSecondaryVertexMVABJetTags")->at(iJet) > -5.0) NBjets_combinedSecondaryVertexMVABJetTags++;
   if (reader.GetFloat("jets_simpleSecondaryVertexBJetTags")->at(iJet) > 2.5) NBjets_simpleSecondaryVertexBJetTags++;
  }
  
  
  AnalysisStep = step;
  
//   std::cerr << "here is ok" <<  std::endl;
  
  
  ///==== filling ====
  stepName[step] = "Jet ID";
  stepEvents[step] += 1;
  
  stdHistograms -> Fill1("muons","muons",step,&whitelistMu);
  stdHistograms -> Fill1("electrons","electrons",step,&whitelistEle);
  stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
  stdHistograms -> Fill1("met","met",step,0); 
  stdHistograms -> Fill2(jets->at(q1),jets->at(q2), "JJ", step);
  
  
 
  
  ///********************************
  ///**** STEP 4 - Lepton ID ****
  ///************* Identification of the two leptons
  step = 5;
  if (step > nStepToDo) {
   outTreeJetLep.Fill();
   continue;
  }  
  
  std::vector<ROOT::Math::XYZTVector> electrons;
  std::vector<ROOT::Math::XYZTVector> muons;
  std::vector<ROOT::Math::XYZTVector> leptons;
  std::vector<std::string> leptonFlavours;    
  std::vector<int> leptonFlavours_pdgId;    
  std::vector<float> leptons_charge;
  std::vector<float> leptons_tkIso;
  std::vector<float> leptons_emIso;
  std::vector<float> leptons_hadIso;
  std::vector<float> leptons_lipSig;
  std::vector<float> leptons_tipSig;
  std::vector<float> leptons_3DipSig;
  
//   std::cerr << "here is ok 3" <<  std::endl;
  
  for(unsigned int iEle = 0; iEle < nEles; iEle++){
   if (whitelistEle.at(iEle) == 1){
    leptons.push_back( reader.Get4V("electrons")->at(iEle) );  
    leptonFlavours.push_back("electron");
    leptonFlavours_pdgId.push_back(11);
    leptons_charge.push_back(reader.GetFloat("electrons_charge")->at(iEle));
    leptons_tkIso.push_back(reader.GetFloat("electrons_tkIso")->at(iEle));
    leptons_emIso.push_back(reader.GetFloat("electrons_emIso03")->at(iEle));
    leptons_hadIso.push_back(reader.GetFloat("electrons_hadIso03_1")->at(iEle)+reader.GetFloat("electrons_hadIso03_2")->at(iEle));
    leptons_lipSig.push_back(reader.GetFloat("electrons_lipSignificance")->at(iEle));
    leptons_tipSig.push_back(reader.GetFloat("electrons_tipSignificance")->at(iEle));
    leptons_3DipSig.push_back(reader.GetFloat("electrons_3DipSignificance")->at(iEle));
   }
  }
  
//   std::cerr << "here is ok 4" <<  std::endl;
  
  
  for(unsigned int iMu = 0; iMu < nMus; iMu++){
   if (whitelistMu.at(iMu) == 1){
//     muons.push_back( reader.Get4V("muons")->at(iMu) );
    leptons.push_back( reader.Get4V("muons")->at(iMu) );      
    leptonFlavours.push_back("muon");
    leptonFlavours_pdgId.push_back(13);
    leptons_charge.push_back(reader.GetFloat("muons_charge")->at(iMu));
    leptons_tkIso.push_back(reader.GetFloat("muons_tkIsoR03")->at(iMu));
    leptons_emIso.push_back(reader.GetFloat("muons_emIsoR03")->at(iMu));
    leptons_hadIso.push_back(reader.GetFloat("muons_hadIsoR03")->at(iMu));
    leptons_lipSig.push_back(reader.GetFloat("muons_lipSignificance")->at(iMu));
    leptons_tipSig.push_back(reader.GetFloat("muons_tipSignificance")->at(iMu));
    leptons_3DipSig.push_back(reader.GetFloat("muons_3DipSignificance")->at(iMu));
   }
  }
  
//   std::cerr << "leptons.size() = " << leptons.size() << std::endl;
  
  if (leptons.size() < 2) continue; ///=== I want at least 2 leptons!!!
  
  
   
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
  
  pdgId_RECO_l1 = leptonFlavours_pdgId.at(l1);
  pdgId_RECO_l2 = leptonFlavours_pdgId.at(l2);
  pT_RECO_l1 = leptons.at(l1).Pt();
  pT_RECO_l2 = leptons.at(l2).Pt();
  eta_RECO_l1 = leptons.at(l1).Eta();
  eta_RECO_l2 = leptons.at(l2).Eta();
  eta_RECO_l1_eta_RECO_l2 = eta_RECO_l1 * eta_RECO_l2;
  Deta_RECO_l12 = fabs(eta_RECO_l1-eta_RECO_l2); 
  Dphi_RECO_l12 = deltaPhi(leptons.at(l1).Phi(),leptons.at(l2).Phi());
  Mll = (leptons.at(l1) + leptons.at(l2)).M();
  charge_RECO_l1_charge_RECO_l2 = leptons_charge.at(l1) * leptons_charge.at(l2);  
  
  
  tkIso_l1 = leptons_tkIso.at(l1);
  emIso_l1 = leptons_emIso.at(l1);
  hadIso_l1 = leptons_hadIso.at(l1);

  tkIso_l2 = leptons_tkIso.at(l2);
  emIso_l2 = leptons_emIso.at(l2);
  hadIso_l2 = leptons_hadIso.at(l2);
  
  
  
  
  ///==== Zepp for lepton ====
  double etaMin = jets->at(q1).Eta();
  double etaMax = jets->at(q2).Eta();
  if (etaMax < etaMin) std::swap(etaMin,etaMax);
  double etaMean = (etaMax + etaMin) / 2.;
  double dEta = (etaMax - etaMin);
  Z_l1 = (leptons.at(l1).Eta() - etaMean)/dEta;
  Z_l2 = (leptons.at(l2).Eta() - etaMean)/dEta;
  ///=========================  
  
  
  stdHistograms -> Fill1("muons","muons",step,&whitelistMu);
  stdHistograms -> Fill1("electrons","electrons",step,&whitelistEle);
  stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
  stdHistograms -> Fill1("met","met",step,0);  
  stdHistograms -> Fill2(jets->at(q1),jets->at(q2), "JJ", step);
  stdHistograms -> Fill2(leptons.at(l1),leptons.at(l2), "ll", step);
  
  stepName[step] = "Lepton ID";
  stepEvents[step] += 1;
  
  
  ///*********************************
  ///**** STEP 5 - Jet Selections ****
  ///************* Loose selections of tag jets
  step = 4;
  if (step > nStepToDo) {
   outTreeJetLep.Fill();
   continue;
  }  
  
  if (pT_RECO_q1 < 30.) continue;
  if (pT_RECO_q2 < 30.) continue;
  if (Mjj < 200.) continue;
  if (Deta_RECO_q12 < 1.) continue;
  if (eta_RECO_q1_eta_RECO_q2 > 0.) continue;
  
  ///==== filling ====
  stepName[step] = "Jet Selections";
  stepEvents[step] += 1;
  
  stdHistograms -> Fill1("muons","muons",step,&whitelistMu);
  stdHistograms -> Fill1("electrons","electrons",step,&whitelistEle);
  stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
  stdHistograms -> Fill1("met","met",step,0); 
  stdHistograms -> Fill2(jets->at(q1),jets->at(q2), "JJ", step);
  
  
  
 
  ///************************************
  ///**** STEP 6 - Final Production *****
  ///************************************
  ///**** No more selections applied ****


  step = 6;
  if (step > nStepToDo) {
   outTreeJetLep.Fill();
   continue;
  }  
  
  ///=== Jets ===
  
  AnalysisStep = step;
  
 
  outTreeJetLep.Fill();
//   outTreeJetLep.Fill();
//   std::cerr << "======================================= end " << std::endl;
  
  
  ///==== ... to be continued in next program ... ====
  ///=================================================
  
 }
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 //  outFile.Write();   
 
 
 
 
 ///==== save additional information ====
 //  TFile* outputRootFile = new TFile(OutFileNameEfficiencies.c_str(), "recreate");
 //  outputRootFile -> cd();
 for(step = 0; step < nStep; ++step)
 {
  events -> SetBinContent(step+2, stepEvents[step]);
  events -> GetXaxis() -> SetBinLabel(step+2, stepName[step].c_str());
  
  if (step != 0){
   analysisEfficiency = static_cast<double>(stepEvents[step]) / static_cast<double>(stepEvents[0]); ///---- fractio => efficiency
   outTreeSelections.Fill();
  }
 } 
 events -> Write(); 
 outFile.Write();
 
 std::cerr << " === end === " << std::endl;
 delete stdHistograms;
 
}


