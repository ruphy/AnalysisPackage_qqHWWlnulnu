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
 //  std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 //  std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
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

 TTree outTreeJet("outTreeJet","outTreeJet");
 
 double pT_RECO_q1;
 double pT_RECO_q2;
 double eta_RECO_q1;
 double eta_RECO_q2;
 double eta_RECO_q1_eta_RECO_q2;
 double Deta_RECO_q12;
 double Mjj;
 int CJV_20;
 int CJV_30;
 int AnalysisStep;
 
 outTreeJet.Branch("pT_RECO_q1",&pT_RECO_q1,"pT_RECO_q1/D");
 outTreeJet.Branch("pT_RECO_q2",&pT_RECO_q2,"pT_RECO_q2/D");
 outTreeJet.Branch("eta_RECO_q1",&eta_RECO_q1,"eta_RECO_q1/D");
 outTreeJet.Branch("eta_RECO_q2",&eta_RECO_q2,"eta_RECO_q2/D");
 outTreeJet.Branch("eta_RECO_q1_eta_RECO_q2",&eta_RECO_q1_eta_RECO_q2,"eta_RECO_q1_eta_RECO_q2/D");
 outTreeJet.Branch("Deta_RECO_q12",&Deta_RECO_q12,"Deta_RECO_q12/D");
 outTreeJet.Branch("Mjj",&Mjj,"Mjj/D");
 outTreeJet.Branch("CJV_20",&CJV_20,"CJV_20/I");
 outTreeJet.Branch("CJV_30",&CJV_30,"CJV_30/I");
 outTreeJet.Branch("AnalysisStep",&AnalysisStep,"AnalysisStep/I");
  
 
 TTree outTreeLep("outTreeLep","outTreeLep");
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
 
 outTreeLep.Branch("pdgId_RECO_l1",&pdgId_RECO_l1,"pdgId_RECO_l1/I");
 outTreeLep.Branch("pdgId_RECO_l2",&pdgId_RECO_l2,"pdgId_RECO_l2/I");
 outTreeLep.Branch("pT_RECO_l1",&pT_RECO_l1,"pT_RECO_l1/D");
 outTreeLep.Branch("pT_RECO_l2",&pT_RECO_l2,"pT_RECO_l2/D");
 outTreeLep.Branch("eta_RECO_l1",&eta_RECO_l1,"eta_RECO_l1/D");
 outTreeLep.Branch("eta_RECO_l2",&eta_RECO_l2,"eta_RECO_l2/D");
 outTreeLep.Branch("eta_RECO_l1_eta_RECO_l2",&eta_RECO_l1_eta_RECO_l2,"eta_RECO_l1_eta_RECO_l2/D");
 outTreeLep.Branch("Deta_RECO_l12",&Deta_RECO_l12,"Deta_RECO_l12/D");
 outTreeLep.Branch("Dphi_RECO_l12",&Dphi_RECO_l12,"Dphi_RECO_l12/D");
 outTreeLep.Branch("Mll",&Mll,"Mll/D");
 outTreeLep.Branch("charge_RECO_l1_charge_RECO_l2",&charge_RECO_l1_charge_RECO_l2,"charge_RECO_l1_charge_RECO_l2/D");
 
 double start, end;
 
 if (entryMAX == -1) entryMAX = reader.GetEntries();
 else if (reader.GetEntries() < entryMAX) entryMAX = reader.GetEntries();
 numEntriesBefore = entryMAX - entryMIN;
 
 std::cout << ">>>>> analysis::entryMIN " << entryMIN << " ==> entryMAX " << entryMAX << std::endl;   
 
 int step = 0;
 start = clock();
 for(int iEvent = entryMIN ; iEvent < entryMAX ; ++iEvent) {
  reader.GetEntry(iEvent);
  if((iEvent%entryMOD) == 0) std::cout << ">>>>> analysis::GetEntry " << iEvent << std::endl;   
  
  ///==== define variables ==== 
  std::vector<ROOT::Math::XYZTVector>* jets = reader.Get4V("jets");
//   std::vector<ROOT::Math::XYZTVector>* muons = reader.Get4V("muons");
//   std::vector<ROOT::Math::XYZTVector>* electrons = reader.Get4V("electrons");
  
  ///*******************************
  ///**** STEP 0 - Preselection ****
  step = 0;
  stepName[step] = "preselection";
  stepEvents[step] += 1;
  
  stdHistograms -> Fill1("muons","muons",step,0);
  stdHistograms -> Fill1("electrons","electrons",step,0);
  stdHistograms -> Fill1("jets","jets",step,0);
  stdHistograms -> Fill1("met","met",step,0); 
  
  
  ///==== Jet cleaning ====
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
   }
   else {
    whitelistJet.push_back(1); ///---- select
   }
  }
  
  ///*******************************
  ///**** STEP 1 - Jet cleaning ****
  if (GetNumList(whitelistJet) < 2) continue; ///==== at least 2 jets "isolated"
   
   step = 1;
  stepName[step] = "Jet cleaning";
  stepEvents[step] += 1;
  
  stdHistograms -> Fill1("muons","muons",step,0);
  stdHistograms -> Fill1("electrons","electrons",step,0);
  stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
  stdHistograms -> Fill1("met","met",step,0);  
  
  
  ///*************************
  ///**** STEP 2 - Jet ID ****
  
  step = 2;
  stepName[step] = "Jet ID";
  stepEvents[step] += 1;
  
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
  
  ///---- update white/black list jets ----
  blacklistJet.clear();
  for (int iList = 0; iList < whitelistJet.size(); iList++){
   if (q1 == iList || q2 == iList) {
    whitelistJet.at(iList) = 1;
   }
   else {
    whitelistJet.at(iList) = 0;
    blacklistJet.push_back(iList);
   }
  }
  
  stdHistograms -> Fill1("muons","muons",step,0);
  stdHistograms -> Fill1("electrons","electrons",step,0);
  stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
  stdHistograms -> Fill1("met","met",step,0);  
  stdHistograms -> Fill2(jets->at(q1),jets->at(q2), "JJ", step);
  
  pT_RECO_q1 = jets->at(q1).Pt();
  pT_RECO_q2 = jets->at(q2).Pt();
  eta_RECO_q1 = jets->at(q1).Eta();
  eta_RECO_q2 = jets->at(q2).Eta();
  eta_RECO_q1_eta_RECO_q2 = eta_RECO_q1 * eta_RECO_q2;
  Deta_RECO_q12 = fabs(eta_RECO_q1-eta_RECO_q2); 
  Mjj = (jets->at(q1) + jets->at(q2)).M();
  CJV_20 = getCJV(*jets,q1,q2,20.,&blacklistJet);
  CJV_30 = getCJV(*jets,q1,q2,30.,&blacklistJet);
  
  AnalysisStep = step;
  outTreeJet.Fill();
  
  ///*********************************
  ///**** STEP 3 - Jet Selections ****
  
  if (pT_RECO_q1 < 30.) continue;
  if (pT_RECO_q2 < 20.) continue;
  if (Mjj < 200.) continue;
  if (Deta_RECO_q12 < 1.) continue;
  if (eta_RECO_q1_eta_RECO_q2 > 0.) continue;
  
  step = 3;
  stepName[step] = "Jet Selections";
  stepEvents[step] += 1;
  
  
  ///*************************************
  ///**** STEP 4 - Jet Selections MVA ****
  
  step = 4;
  stepName[step] = "Jet MVA";
  stepEvents[step] += 1;
 
 
  ///********************************
  ///**** STEP 5 - Lepton Number ****
  
  step = 5;
  stepName[step] = "Lepton Number";
  stepEvents[step] += 1;
  
  std::vector<ROOT::Math::XYZTVector> electrons;
  std::vector<ROOT::Math::XYZTVector> muons;
  std::vector<ROOT::Math::XYZTVector> leptons;
  std::vector<std::string> leptonFlavours;    
  std::vector<int> leptonFlavours_pdgId;    
  std::vector<float> leptons_charge;
  std::vector<float> leptons_tkIso;
  std::vector<float> leptons_lipSig;
  std::vector<float> leptons_tipSig;
  std::vector<float> leptons_3DipSig;
  
  double eleIdValueMIN = 1;
  double lepNMIN = 2;
  
  for(unsigned int eleIt = 0; eleIt < (reader.Get4V("electrons")->size()); ++eleIt)
  {
   if( reader.Get4V("electrons")->at(eleIt).pt() < 10. ) continue;
   if( (reader.GetFloat("electrons_tkIso")->at(eleIt)) / reader.Get4V("electrons")->at(eleIt).pt() > 0.5 ) continue;
   if( (reader.GetFloat("electrons_IdRobustTight")->at(eleIt)) < eleIdValueMIN ) continue;
   
   electrons.push_back( reader.Get4V("electrons")->at(eleIt) );
   leptons.push_back( reader.Get4V("electrons")->at(eleIt) );      
   leptonFlavours.push_back("electron");
   leptonFlavours_pdgId.push_back(11);
   leptons_charge.push_back(reader.GetFloat("electrons_charge")->at(eleIt));
   leptons_tkIso.push_back(reader.GetFloat("electrons_tkIso")->at(eleIt));
   leptons_lipSig.push_back(reader.GetFloat("electrons_lipSignificance")->at(eleIt));
   leptons_tipSig.push_back(reader.GetFloat("electrons_tipSignificance")->at(eleIt));
   leptons_3DipSig.push_back(reader.GetFloat("electrons_3DipSignificance")->at(eleIt));
  }
  
  for(unsigned int muIt = 0; muIt < (reader.Get4V("muons")->size()); ++muIt)
  {
   if( reader.Get4V("muons")->at(muIt).pt() < 10. ) continue;
   if( (reader.GetFloat("muons_tkIsoR03")->at(muIt)) / reader.Get4V("muons")->at(muIt).pt() > 0.5 ) continue;
   
   muons.push_back( reader.Get4V("muons")->at(muIt) );
   leptons.push_back( reader.Get4V("muons")->at(muIt) );      
   leptonFlavours.push_back("muon");
   leptonFlavours_pdgId.push_back(13);
   leptons_charge.push_back(reader.GetFloat("muons_charge")->at(muIt));
   leptons_tkIso.push_back(reader.GetFloat("muons_tkIsoR03")->at(muIt));
   leptons_lipSig.push_back(reader.GetFloat("muons_lipSignificance")->at(muIt));
   leptons_tipSig.push_back(reader.GetFloat("muons_tipSignificance")->at(muIt));
   leptons_3DipSig.push_back(reader.GetFloat("muons_3DipSignificance")->at(muIt));
  }
  
  if( (int)(leptons.size()) < lepNMIN ) continue;
  
  
  ///****************************
  ///**** STEP 6 - Lepton ID ****
  
  step = 6;
  stepName[step] = "Lepton ID";
  stepEvents[step] += 1;
  
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
  outTreeLep.Fill();
  
  stdHistograms -> Fill1("muons","muons",step,0);
  stdHistograms -> Fill1("electrons","electrons",step,0);
  stdHistograms -> Fill1("jets","jets",step,&whitelistJet);
  stdHistograms -> Fill1("met","met",step,0);  
  stdHistograms -> Fill2(jets->at(q1),jets->at(q2), "JJ", step);
  stdHistograms -> Fill2(leptons.at(l1),leptons.at(l2), "ll", step);
  
  
  ///************************************
  ///**** STEP 7 - Lepton Selections ****
  
//   step = 7;
//   stepName[step] = "Lepton selections";
//   stepEvents[step] += 1;
  
 
  ///****************************************
  ///**** STEP 8 - Lepton Selections MVA ****
  
//   step = 8;
//   stepName[step] = "Lepton Selections MVA";
//   stepEvents[step] += 1;
  
  
  
  
  
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
 
 delete stdHistograms;
 
 
 
}


