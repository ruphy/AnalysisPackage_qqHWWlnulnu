#include <cmath>
#include <iostream>
#include "TF1.h"
#include "TTree.h"
#include "TCut.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TROOT.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TText.h"
#include <map>
#include <vector>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ConfigParser.h"
#include "ntpleUtils.h"
#include "qqHWWlnulnuUtils.h"

#include "../test/Read.cc"
#include "../test/TDRStyle.cc"

// using namespace std ;

double LUMI = 1000;


struct coll 
{
 coll (std::string name) : m_name (name) {} ;
 void add (const double & XS, std::pair<TTree*,TTree*> al) 
 {
  samples[XS] = al ;
 }
 
 ///=================================================
 double getEqSigma (TCut cut){
  double events = 0. ;
  for (std::map<double, std::pair<TTree*,TTree*> >::iterator it = samples.begin () ;  it != samples.end () ;   ++it){
   it->second.second->SetBranchAddress ("preselection_efficiency", &preselection_efficiency) ;
   it->second.second->SetBranchAddress ("numEntriesBefore", &numEntriesBefore) ;
   it->second.second->GetEntry (0) ;
   
   if (it->second.first->GetEntries () != 0) {
     if (it->first != -1) events += (it->first * (LUMI * it->second.first->GetEntries (cut)) * preselection_efficiency / numEntriesBefore) ;
     else events += (it->second.first->GetEntries (cut));
   }
  }
  return events ;
 } ;
 ///=================================================
 double getAll () {
  double events = 0. ;
  for (std::map<double, std::pair<TTree*,TTree*> >::iterator it = samples.begin () ;  it != samples.end () ;   ++it){
   it->second.second->SetBranchAddress("preselection_efficiency",&preselection_efficiency);
   it->second.second->SetBranchAddress("numEntriesBefore",&numEntriesBefore);
   it->second.second->GetEntry(0);
   if (it->first != -1) events += (it->first * LUMI);
  }
  return events ;
 } ;
 
 ///=================================================
 double getMC (TCut cut){
  double events = 0. ;
  for (std::map<double, std::pair<TTree*,TTree*> >::iterator it = samples.begin () ;  it != samples.end () ;   ++it){
    events += (it->second.first->GetEntries (cut)) ;
  }
  return events ;
 } ;
 
 ///=================================================
 std::map<double, std::pair<TTree*,TTree*> > samples ;
 std::string m_name ; 
 
 double XSection;
 double preselection_efficiency;
 int numEntriesBefore;  
} ;


// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---


///
///
///   ___|                       |                     _ )         _ \   |         |   
///  |       _ \   |   |  __ \   __|   _ \   __|       _ \ \      |   |  |   _ \   __| 
///  |      (   |  |   |  |   |  |     __/  |         ( `  <      ___/   |  (   |  |   
/// \____| \___/  \__,_| _|  _| \__| \___| _|        \___/\/     _|     _| \___/  \__| 
///
///


int main(int argc, char** argv) {
  
  EColor vColor[1000] = {
    kGreen,(EColor) (kGreen+1),
    //kMagenta,(EColor) (kMagenta+1),(EColor) (kMagenta+2),
    kTeal,//(EColor) (kTeal+1),
    kRed,
    kGray,
    kOrange,(EColor) (kOrange+1),
    kBlue,//(EColor)(kBlue+1),(EColor) (kBlue+2),
    (EColor) (kPink+2),//(EColor) (kPink+1),(EColor) (kPink+2),
    kViolet,
    kYellow,
    kGray,(EColor) (kGray+1),(EColor) (kViolet),(EColor) (kYellow),(EColor) (kGray)
  };
   
 //Check if all nedeed arguments to parse are there                                                                                                                               
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");
 std::string treeNameSelections = gConfigParser -> readStringOption("Input::treeNameSelections");
 std::string fileSamples = gConfigParser -> readStringOption("Input::fileSamples");
 std::string inputDirectory = gConfigParser -> readStringOption("Input::inputDirectory");
 
 double LUMI = gConfigParser -> readDoubleOption("Input::Lumi");
 
 
 std::vector<std::string> SignalName = gConfigParser -> readStringListOption("Plot::SignalName");
 
 ///==== list of selections to perform (NOT sequential selections) ====
 std::string CutFile   = gConfigParser -> readStringOption("Selections::CutFile");
 std::string CutHRFile = gConfigParser -> readStringOption("Selections::CutHRFile");
 std::vector<std::string> vCut;
 std::vector<std::string> vCutHR;
 
 std::cout << " nCuts   = " << ReadFileCut(CutFile,     vCut  ) << std::endl;
 std::cout << " nCutsHR = " << ReadFileCutHR(CutHRFile, vCutHR) << std::endl;
 
 
 
 ///==== output file ====
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
 
 TFile outFile(OutFileName.c_str(),"RECREATE");
 outFile.cd();
 
 
 ///==== debug flag ====
 
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 double xsection[1000];
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 
 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
 
  
 std::vector<coll> samples ;
 
 TTree *treeEffVect[100];
 TTree *treeJetLepVect[100];
 
 TH1F* histo[100];
 TH1F* histo_temp[100];
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  xsection[iSample] = atof(xsectionName[iSample]);
 }
 
 
 ///===== create map for joint sample ====
 
 std::vector<int> join_samples;
 std::vector<std::string> name_samples;
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  name_samples.push_back(nameHumanReadable[iSample]);
  join_samples.push_back(-1);
 }
 
 
 std::vector<std::string> reduced_name_samples;
 std::vector<int>         reduced_name_samples_flag;
 //  for (int iSample=0; iSample<numberOfSamples; iSample++){
  for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
   bool flag_name = false;
   for (int iName=0; iName<reduced_name_samples.size(); iName++){
    if (reduced_name_samples.at(iName) == name_samples.at(iSample)) flag_name = true;
   }
   if (flag_name == false) {
    reduced_name_samples.push_back(name_samples.at(iSample));
    reduced_name_samples_flag.push_back(-1);
   }
  }
  
 
 ///===== cicle on reduced sample names and add to counter ====
 
 for (int iName=0; iName<reduced_name_samples.size(); iName++){
//   if (reduced_name_samples.at(iName) != "DATA") {
   bool firstTime = true;
   for (int iSample=0; iSample<numberOfSamples; iSample++){
    if (name_samples.at(iSample) == reduced_name_samples.at(iName)) {
     if (firstTime) {
      firstTime = false;
      samples.push_back (coll (reduced_name_samples.at(iName))) ;
     }
     char nameFile[1000];
     sprintf(nameFile,"%s/out_NtupleProducer_%s.root",inputDirectory.c_str(),nameSample[iSample]);  
     TFile* f = new TFile(nameFile, "READ");     
     std::pair<TTree*, TTree*> pair_vbf_temp ((TTree*) f->Get(treeName.c_str()), (TTree*) f->Get(treeNameSelections.c_str()));
     samples.back ().add (xsection[iSample], pair_vbf_temp) ;
    }
   }
//   }
 } 

std::vector<TCut> selections ;
std::vector<TString> selections_name ;


///==== cut based ====


///==== MH 120 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>20&&q2_pT>20&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>1.5&&M_qq>300") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>30 && l2_pT>10 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DEta_ll<3.8 && DPhi_ll<1.0 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("(M_ll<70&&M_ll>10)") ;
// selections_name.push_back("MET");  selections.push_back ("met>20");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");

///==== MH 130 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>20&&q2_pT>20&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>1.5&&M_qq>300") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>30 && l2_pT>10 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DEta_ll<3.8 && DPhi_ll<1.0 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("(M_ll<70&&M_ll>10)") ;
// selections_name.push_back("MET");  selections.push_back ("met>20");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");

///==== MH 160 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>20&&q2_pT>20&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>2.0&&M_qq>350") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>30 && l2_pT>10 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DEta_ll<3.8 && DPhi_ll<1.5 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("((M_ll<70&&M_ll>20&&l1_flavour==l2_flavour)||(l1_flavour!=l2_flavour))") ;
// selections_name.push_back("MET");  selections.push_back ("met>30");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");

///==== MH 200 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>25&&q2_pT>25&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>2.0&&M_qq>400") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>30 && l2_pT>10 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DPhi_ll>1.5 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("((((M_ll<75&&M_ll>20)||(M_ll>95))&&l1_flavour==l2_flavour)||(l1_flavour!=l2_flavour))") ;
// selections_name.push_back("MET");  selections.push_back ("met>40");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");


///==== MH 400 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>25&&q2_pT>25&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>2.5&&M_qq>500") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>40 && l2_pT>20 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DEta_ll<3.8 && DPhi_ll>1.5 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("((((M_ll<75&&M_ll>20)||(M_ll>95))&&l1_flavour==l2_flavour)||(l1_flavour!=l2_flavour))") ;
// selections_name.push_back("MET");  selections.push_back ("met>30");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");







///=============
///==== MVA ====
///=============

///==== MH 120 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>20&&q2_pT>20&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>1.5&&M_qq>300") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>30 && l2_pT>10 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DEta_ll<3.8 && DPhi_ll<1.0 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("(M_ll<70&&M_ll>10)") ;
// selections_name.push_back("MET");  selections.push_back ("met>20");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");

///==== MH 130 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>20&&q2_pT>20&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>1.5&&M_qq>300") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>30 && l2_pT>10 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DEta_ll<3.8 && DPhi_ll<1.0 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("(M_ll<70&&M_ll>10)") ;
// selections_name.push_back("MET");  selections.push_back ("met>20");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");

///==== MH 160 ====
for (int iCut = 0; iCut<vCut.size(); iCut++){
 TString Cut = Form ("%s",vCut.at(iCut).c_str());
 if (debug) std::cout << " Cut[" << iCut << ":" << vCut.size() << "] = " << Cut.Data() << " ~~ " << std::endl;
 selections_name.push_back(vCutHR.at(iCut).c_str());     selections.push_back (vCut.at(iCut).c_str()) ;
}
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>20&&q2_pT>20") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_charge * l2_charge == -1") ;
// selections_name.push_back("Z_V");  selections.push_back ("((M_ll<70&&M_ll>20&&l1_flavour==l2_flavour)||(l1_flavour!=l2_flavour))") ;
// selections_name.push_back("MET");  selections.push_back ("met>30");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");
// selections_name.push_back("MVAJet");  selections.push_back ("LikelihoodD_JetH160>0");
// selections_name.push_back("MVALep");  selections.push_back ("LikelihoodD_LepH160>0");
// selections_name.push_back("MVALep");  selections.push_back ("MLPBNN_LepH160>0");

///==== MH 200 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>25&&q2_pT>25&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>2.0&&M_qq>400") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>30 && l2_pT>10 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DPhi_ll>1.5 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("((((M_ll<75&&M_ll>20)||(M_ll>95))&&l1_flavour==l2_flavour)||(l1_flavour!=l2_flavour))") ;
// selections_name.push_back("MET");  selections.push_back ("met>40");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");


///==== MH 400 ====
// selections_name.push_back("2j+2l");     selections.push_back ("M_ll>10 && M_qq>200 && DEta_qq>1 && l1_pT>20 && q1_pT>15 && q2_pT>15") ;
// selections_name.push_back("VBF");  selections.push_back ("q1_pT>25&&q2_pT>25&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>2.5&&M_qq>500") ;
// selections_name.push_back("CJV");  selections.push_back ("CJV_30<1") ;
// selections_name.push_back("LEP");  selections.push_back ("l1_pT>40 && l2_pT>20 && abs(l1_Eta)<2.5 && abs(l2_Eta)<2.5 && DEta_ll<3.8 && DPhi_ll>1.5 && l1_charge * l2_charge == -1 && abs(Z_ll)<0.5") ;
// selections_name.push_back("Z_V");  selections.push_back ("((((M_ll<75&&M_ll>20)||(M_ll>95))&&l1_flavour==l2_flavour)||(l1_flavour!=l2_flavour))") ;
// selections_name.push_back("MET");  selections.push_back ("met>30");
// selections_name.push_back("Btag"); selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<0.5&&q1_bTag_trackCountingHighPurBJetTags<0.5&&(q2_bTag_trackCountingHighPurBJetTags+q1_bTag_trackCountingHighPurBJetTags)<0.7");



///==== MVA ====
// /*  -  */ selections.push_back ("") ;
// /* VBF */ selections.push_back ("q1_pT>20&&q2_pT>20&&abs(q1_Eta)>0.1&&abs(q2_Eta)>0.1&&DEta_qq>0.0&&M_qq>300") ;
// /* CJV */ selections.push_back ("CJV_30<1") ;
// /* LEP */ selections.push_back ("l1_pT>30&&l2_pT>10&&(l1_charge*l2_charge)==-1") ;
// /* Z_V */ selections.push_back ("((M_ll<70&&M_ll>20&&l1_flavour==l2_flavour)||(l1_flavour!=l2_flavour))") ;
// /* MET */ selections.push_back ("met>30");
// // // /* Btag */ selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<1.0&&q1_bTag_trackCountingHighPurBJetTags<1.0&&NBjets_trackCountingHighEffBJetTags==0");
// /* Btag */ selections.push_back ("q2_bTag_trackCountingHighPurBJetTags<1.0&&q1_bTag_trackCountingHighPurBJetTags<1.0");
///*MVA Jet*/ selections.push_back ("BDT_Jet>0.1");
///*MVA Lep*/ selections.push_back ("BDT_Lep>-0.2");
 
 std::cout << std::endl;
 std::cout << std::endl;
 
 std::cout.precision (2) ;
 std::cout.unsetf(std::ios::scientific);
 
 std::cout << std::setw (8) << " sample ";
 std::cout << "  |" << std::setw (8) << "  No sel  ";
 for (int iSel = 1 ; iSel < selections.size () ; ++iSel) {
  std::cout << "  |  " << std::setw (8) << vCutHR.at(iSel);
 }
 
 //  std::cout << "  |  " << std::setw (8) << "2j+2l";
 //  std::cout << "  |  " << std::setw (17) << "  VBF ";
 //  std::cout << "  |  " << std::setw (17) << "  CJV ";
 //  std::cout << "  |  " << std::setw (17) << "  LEP ";
 //  std::cout << "  |  " << std::setw (17) << "Z veto ";
 //  std::cout << "  |  " << std::setw (17) << " MET   ";
 //  std::cout << "  |  " << std::setw (17) << " BTag ";
 // std::cout << "  |  " << std::setw (17) << " MVA Jet ";
 // std::cout << "  |  " << std::setw (17) << " MVA Lep";
 
 std::cout << std::endl;
 
 
 std::vector<double> numBackground;
 std::vector<double> numSignal;
 
 
 for (int iSel = 0 ; iSel < selections.size () ; ++iSel) {
  numBackground.push_back(0);
  numSignal.push_back(0);
 }
 
 
 
 for (int iSel = 1 ; iSel < selections.size () ; ++iSel) {
  std::cout << "+------------";
 }
 std::cout << std::endl;
 std::cout << std::endl;
 
 double totalBkg = 0;
 double totalBkgError = 0;
 
 double totalSig = 0;
 double totalSigError = 0;
 
 for (int iSample = 0 ; iSample < samples.size () ; ++iSample)
 {
   std::cout << std::setw (8) << samples.at (iSample).m_name ;
//    std::cout << " | " << std::setw (8) << samples.at (iSample).getAll () ;
//    std::cout << " | " << std::setw (8) << samples.at (iSample).getEqSigma (selections.at (0)) ;
   TCut total_cut = selections.at (0) ;
   
   
   bool isSig = false;
   for (int iSig = 0; iSig < SignalName.size(); iSig++){
    if (reduced_name_samples[iSample] == SignalName.at(iSig)) { isSig = true;}
   }
   
   
   for (int iSel = 0 ; iSel < selections.size () ; ++iSel) 
   {
     total_cut = total_cut && selections.at (iSel) ;
     std::cout << " | " << std::setw (8) << samples.at (iSample).getEqSigma (total_cut) ;
     std::cout << "[" << std::setw (8) <<samples.at (iSample). getMC(total_cut) << "]" ;
     
     if (!isSig && reduced_name_samples[iSample]!="ggH" && reduced_name_samples[iSample]!="DATA") numBackground.at(iSel) = (numBackground.at(iSel) + samples.at (iSample).getEqSigma (total_cut));
     else if (reduced_name_samples[iSample]!="DATA") numSignal.at(iSel)         = (numSignal.at(iSel) + samples.at (iSample).getEqSigma (total_cut));
     
   }
//    std::cout << " | absolute " << endl ;  
   std::cout << std::endl ;  
   
    
   if (!isSig && reduced_name_samples[iSample]!="ggH") totalBkg += samples.at (iSample).getEqSigma (total_cut);
   else totalSig += samples.at (iSample).getEqSigma (total_cut);
      
 } 
 
 for (int iSel = 1 ; iSel < selections.size () ; ++iSel) {
  std::cout << "+------------";
 }
 std::cout << std::endl ;  
 std::cout << std::setw (8) << "tot bkg";
 for (int iSel = 0 ; iSel < selections.size () ; ++iSel) {
  std::cout << " | " << std::setw (8) << numBackground.at(iSel) ;
  std::cout << "[" << std::setw (8) << 0 << "]" ;
 }
 std::cout << std::endl ;  
 std::cout << std::setw (8) << "tot sig";
 for (int iSel = 0 ; iSel < selections.size () ; ++iSel) {
  std::cout << " | " << std::setw (8) << numSignal.at(iSel) ;
  std::cout << "[" << std::setw (8) << 0 << "]" ;
 }
 std::cout << std::endl ;  
 std::cout << std::setw (8) << "S/sq(B)";
 for (int iSel = 0 ; iSel < selections.size () ; ++iSel) {
  std::cout << " | " << std::setw (8) << (sqrt(numBackground.at(iSel)) ? numSignal.at(iSel) / sqrt(numBackground.at(iSel)) : 0) ;
  std::cout << "[" << std::setw (8) << 0 << "]" ;
 }
 std::cout << std::endl ;  
 std::cout << std::endl;
 
 std::cerr << " totalBkg = " << totalBkg << std::endl;
 std::cerr << " totalSig = " << totalSig << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
 ///==== draw ====
 TDRStyle();
 gStyle->SetLabelSize(0.06, "XYZ");
 gStyle->cd(); 
 
 
 TH1F* hDATA = new TH1F("hDATA","DATA",selections.size(), 0, selections.size());
 TH1F* hMC = new TH1F("hMC","hMC",selections.size(), 0, selections.size());
 
 TH1F* v_hMC[100];
 THStack* hsMC = new THStack("stack","MC");
 for (int iName=0; iName<reduced_name_samples.size(); iName++){
   v_hMC[iName] = new TH1F(TString(reduced_name_samples.at(iName)),TString(reduced_name_samples.at(iName)),selections.size(), 0, selections.size());
 }
 
 for (int iSample = 0 ; iSample < samples.size () ; ++iSample){
   TCut total_cut = "1";
   for (int iSel = 0 ; iSel < selections.size () ; ++iSel) {
     total_cut = total_cut && selections.at (iSel) ;
     if (reduced_name_samples[iSample]!="DATA"){
       hMC->Fill(iSel,samples.at (iSample).getEqSigma (total_cut));
       v_hMC[iSample]->Fill(iSel,samples.at (iSample).getEqSigma (total_cut));
     }
     else {
       std::cerr << " samples.at (" << iSample << ").getEqSigma (total_cut) = " << samples.at (iSample).getEqSigma (total_cut) << std::endl;
       hDATA->Fill(iSel,samples.at (iSample).getEqSigma (total_cut));    
     }
   }
 }
 
 for (int iName=0; iName<reduced_name_samples.size(); iName++){
   if (reduced_name_samples[iName]!="DATA"){
     v_hMC[iName]->SetMarkerColor(vColor[iName]);
     v_hMC[iName]->SetLineColor(vColor[iName]);
     v_hMC[iName]->SetFillColor(vColor[iName]);
     v_hMC[iName]->SetLineWidth(2);
     v_hMC[iName]->SetFillStyle(3001);  
     hsMC->Add(v_hMC[iName]);
   }
 }  
 
 TLegend* leg = new TLegend(0.80,0.45,0.90,0.90);
 for (int iName=0; iName<reduced_name_samples.size(); iName++){
   leg->AddEntry(v_hMC[iName],reduced_name_samples.at(iName).c_str(),"pf");    
 }
 
 
 hMC->SetFillColor(kBlue);
 hMC->SetLineColor(kBlue);
 hMC->SetMarkerColor(kBlue);
 hMC->SetFillStyle(3005);

 hDATA->SetLineColor(kBlack);
 hDATA->SetMarkerColor(kBlack);
 hDATA->SetMarkerStyle(20);
 
 for (int iSel = 0 ; iSel < selections_name.size () ; ++iSel) {
   hMC->SetBinError(iSel+1,0);
   hDATA->GetXaxis()->SetBinLabel(iSel+1,selections_name.at(iSel));
   hMC->GetXaxis()->SetBinLabel(iSel+1,selections_name.at(iSel));
   ((TH1*)(hsMC->GetStack()->Last()))->GetXaxis()->SetBinLabel(iSel+1,selections_name.at(iSel));
 }
 
 TString titleY = Form ("# events in %.1f pb-1",LUMI);
 hDATA->GetYaxis()->SetTitle(titleY);
 hMC->GetYaxis()->SetTitle(titleY);
 
 TCanvas * cPullCounter = new TCanvas ("cPullCounter","cPullCounter",800,800);
 PullPlot(cPullCounter,hDATA,hMC);
 cPullCounter->SaveAs("cPullCounter.png");
 cPullCounter->SaveAs("cPullCounter.pdf");
 
 cPullCounter->cd(1);
 hDATA->GetYaxis()->SetRangeUser(hMC->GetMinimum() ? hMC->GetMinimum()/10. : 1e-5 ,std::max(hMC->GetMaximum(),hDATA->GetMaximum()) * 1.1);
 hMC  ->GetYaxis()->SetRangeUser(hMC->GetMinimum() ? hMC->GetMinimum()/10. : 1e-5 ,std::max(hMC->GetMaximum(),hDATA->GetMaximum()) * 1.1); 
 gPad->SetGrid();
 gPad->SetLogy();
 cPullCounter->cd(2);
 cPullCounter->SaveAs("cPullCounter_Log.png");
 cPullCounter->SaveAs("cPullCounter_Log.pdf");
 

 TCanvas * cPullCounterStack = new TCanvas ("cPullCounterStack","cPullCounterStack",800,800);
 PullPlot(cPullCounterStack,hDATA,hsMC);
 cPullCounterStack->cd(1);
 leg->Draw();
 cPullCounterStack->SaveAs("cPullCounterStack.png");
 cPullCounterStack->SaveAs("cPullCounterStack.pdf");
 
 double min_plot = 1e-3 * LUMI;
 cPullCounterStack->cd(1);
 leg->Draw();
 hDATA->GetYaxis()->SetRangeUser(min_plot ,std::max(hMC->GetMaximum(),hDATA->GetMaximum()) * 1.1);
 ((TH1*)(hsMC->GetStack()->Last()))->GetYaxis()->SetRangeUser(min_plot ,std::max(hMC->GetMaximum(),hDATA->GetMaximum()) * 1.1); 
 gPad->SetGrid();
 gPad->SetLogy();
 cPullCounterStack->SaveAs("cPullCounterStack_Log.png");
 cPullCounterStack->SaveAs("cPullCounterStack_Log.pdf");
 
 return 0 ;
 
}
