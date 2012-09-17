// 
// Template from http://root.cern.ch/svn/root/trunk/tmva/test/TMVAClassification.C
// 

#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "../test/Read.cc"

#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

#include "TMVA/Reader.h"


#include "TLorentzVector.h"




int main(int argc, char** argv) {
 
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");
 std::string fileSamples = gConfigParser -> readStringOption("Input::fileSamples");
 std::string inputDirectory = gConfigParser -> readStringOption("Input::inputDirectory");
 
 std::string inputBeginningFile = "out_NtupleProducer_"; 
 try {
  inputBeginningFile = gConfigParser -> readStringOption("Input::inputBeginningFile");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Input::inputBeginningFile  " << inputBeginningFile  << std::endl;  
 
 
 //==== list of methods 
 std::string outputDirectory = gConfigParser -> readStringOption("Output::outputDirectory");
 
 //---- variables 
 float pt1;
 float pt2;
 
 float phi1;
 float phi2;
 
 float jetpt1;
 float jetpt2;
 
 float jetphi1;
 float jetphi2;
 
 float channel;
 
 
 
 
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 TFile* outputRootFile[500];
 TTree* cloneTreeJetLepVect[500];
 
 
 TTree *treeJetLepVect[500];
 TFile* file[500];
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 
 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
 
 double Normalization[1000];
 double xsection[1000];
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
  
  file[iSample] = new TFile(nameFile, "READ");
  
  treeJetLepVect[iSample] = (TTree*) file[iSample]->Get(treeName.c_str());
  char nameTreeJetLep[100];
  sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
  treeJetLepVect[iSample]->SetName(nameTreeJetLep);
  
  treeJetLepVect[iSample] -> SetBranchAddress("jetpt1",  &jetpt1);
  treeJetLepVect[iSample] -> SetBranchAddress("jetpt2",  &jetpt2);
  treeJetLepVect[iSample] -> SetBranchAddress("jetphi1",  &jetphi1);
  treeJetLepVect[iSample] -> SetBranchAddress("jetphi2",  &jetphi2);
  
  treeJetLepVect[iSample] -> SetBranchAddress("pt1",  &pt1);
  treeJetLepVect[iSample] -> SetBranchAddress("pt2",  &pt2);
  treeJetLepVect[iSample] -> SetBranchAddress("phi1",  &phi1);
  treeJetLepVect[iSample] -> SetBranchAddress("phi2",  &phi2);
  
  treeJetLepVect[iSample] -> SetBranchAddress("channel",  &channel);
  
  
  sprintf(nameFile,"%s/%s%s.root",outputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);    
  outputRootFile[iSample] = new TFile ( nameFile, "RECREATE") ;
  outputRootFile[iSample] -> cd () ;
  cloneTreeJetLepVect[iSample] = treeJetLepVect[iSample] -> CloneTree (0) ;
 }
 
 int nInt = 10;
 float MHmin = 120;
 float DMH   = 10;
 float MH;
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  std::cout << " iSample = " << iSample << " :: " << numberOfSamples << std::endl;
  file[iSample] -> cd();
  TBranch *newBranch[1000];
  float Value[1000];
  
  for (int iInt = 0; iInt<nInt; iInt++) {
   MH = MHmin + DMH*iInt;
   TString methodName4Tree = Form ("boostedDphill_%d",static_cast<int>(MH));
   TString methodName4Tree2 = Form ("boostedDphill_%d/F",static_cast<int>(MH));
   newBranch[iInt] = cloneTreeJetLepVect[iSample]->Branch(methodName4Tree,&(Value[iInt]),methodName4Tree2);
   std::cout << " new Branch :: " << methodName4Tree.Data() << std::endl;
  }
  
  ///==== loop ====
  Long64_t nentries = treeJetLepVect[iSample]->GetEntries();
  
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   if ((iEntry%1000) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
   
   treeJetLepVect[iSample]->GetEntry(iEntry);
   
   float pt1X = pt1*cos(phi1);
   float pt1Y = pt1*sin(phi1);
   
   float pt2X = pt2*cos(phi2);
   float pt2Y = pt2*sin(phi2);
   
   float jetpt1X = jetpt1*cos(jetphi1);
   float jetpt1Y = jetpt1*sin(jetphi1);
   
   float jetpt2X = jetpt2*cos(jetphi2);
   float jetpt2Y = jetpt2*sin(jetphi2);
   
   float ptjetjetX = (jetpt1X+jetpt2X);
   float ptjetjetY = (jetpt1Y+jetpt2Y);
   float ptjetjet = sqrt(ptjetjetX*ptjetjetX+ptjetjetY*ptjetjetY);
   float phijetjet = atan2(ptjetjetY,ptjetjetX);
   
   for (int iInt = 0; iInt<nInt; iInt++) {
    MH = MHmin + DMH*iInt;
        
    float m1 = 0.000511*(channel==2||channel==1)+0.106*(channel==3||channel==0);
    float m2 = 0.000511*(channel==3||channel==1)+0.106*(channel==2||channel==0);
    
    float e1 = sqrt(pt1*pt1 + m1*m1);
    float e2 = sqrt(pt2*pt2 + m2*m2);
      
    float EHiggs = sqrt( MH*MH + ptjetjet*ptjetjet );
    TLorentzVector boost_higgs;
    boost_higgs.SetPtEtaPhiE(ptjetjet, 0, phijetjet, EHiggs);

    TVector3 boost;
    boost = boost_higgs.BoostVector(); 
    
    TLorentzVector new_lepton1;
    new_lepton1.SetPtEtaPhiE(pt1, 0, phi1, e1);
    TLorentzVector new_lepton2;
    new_lepton2.SetPtEtaPhiE(pt2, 0, phi2, e2);
    
    //---- now boost
    new_lepton1.Boost(boost);
    new_lepton2.Boost(boost);    
    //---- now the "new_lepton1/2" is boosted!
    
    float vphi1 = new_lepton1.Phi();
    float vphi2 = new_lepton2.Phi();
    
    float boostedDphill = (fabs(vphi1-vphi2)>3.14159265)*(2*3.14159265-fabs(vphi1-vphi2))+(fabs(vphi1-vphi2)<3.14159265)*(fabs(vphi1-vphi2));
    
    Value[iInt] = boostedDphill;
    
   }
   cloneTreeJetLepVect[iSample] -> Fill () ; 
  }
 }
 
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  // save only the new version of the tree
  //   treeJetLepVect[iSample]->Write("", TObject::kOverwrite);
  cloneTreeJetLepVect[iSample] -> SetName (treeName.c_str());
  cloneTreeJetLepVect[iSample] -> AutoSave () ;
  outputRootFile[iSample] -> Close () ;
 }
 
 
}



