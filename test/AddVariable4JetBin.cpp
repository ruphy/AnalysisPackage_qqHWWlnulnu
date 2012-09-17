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
 float jetpt1;
 float jetpt2;
 float jetpt3;
 float jetpt4;
 
 float jetphi1;
 float jetphi2;
 float jetphi3;
 float jetphi4;
 
 float jeteta1;
 float jeteta2;
 float jeteta3;
 float jeteta4;
 
 
 
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
  treeJetLepVect[iSample] -> SetBranchAddress("jetpt3",  &jetpt3);
  treeJetLepVect[iSample] -> SetBranchAddress("jetpt4",  &jetpt4);
  treeJetLepVect[iSample] -> SetBranchAddress("jetphi1",  &jetphi1);
  treeJetLepVect[iSample] -> SetBranchAddress("jetphi2",  &jetphi2);
  treeJetLepVect[iSample] -> SetBranchAddress("jetphi3",  &jetphi3);
  treeJetLepVect[iSample] -> SetBranchAddress("jetphi4",  &jetphi4);
  treeJetLepVect[iSample] -> SetBranchAddress("jeteta1",  &jeteta1);
  treeJetLepVect[iSample] -> SetBranchAddress("jeteta2",  &jeteta2);
  treeJetLepVect[iSample] -> SetBranchAddress("jeteta3",  &jeteta3);
  treeJetLepVect[iSample] -> SetBranchAddress("jeteta4",  &jeteta4);
  
  sprintf(nameFile,"%s/%s%s.root",outputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);    
  outputRootFile[iSample] = new TFile ( nameFile, "RECREATE") ;
  outputRootFile[iSample] -> cd () ;
  cloneTreeJetLepVect[iSample] = treeJetLepVect[iSample] -> CloneTree (0) ;
 }
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  std::cout << " iSample = " << iSample << " :: " << numberOfSamples << std::endl;
  file[iSample] -> cd();
  TBranch *newBranch[100];
  float mjjjj; 
  float ptjjjj; 
  float mjjj; 
  float ptjjj; 
  
  TString methodName4Tree = Form ("mjjjj");
  TString methodName4Tree2 = Form ("mjjjj/F");
  newBranch[0] = cloneTreeJetLepVect[iSample]->Branch(methodName4Tree,&mjjjj,methodName4Tree2);

  methodName4Tree = Form ("ptjjjj");
  methodName4Tree2 = Form ("ptjjjj/F");
  newBranch[1] = cloneTreeJetLepVect[iSample]->Branch(methodName4Tree,&ptjjjj,methodName4Tree2);

  methodName4Tree = Form ("mjjj");
  methodName4Tree2 = Form ("mjjj/F");
  newBranch[2] = cloneTreeJetLepVect[iSample]->Branch(methodName4Tree,&mjjj,methodName4Tree2);
  
  methodName4Tree = Form ("ptjjj");
  methodName4Tree2 = Form ("ptjjj/F");
  newBranch[3] = cloneTreeJetLepVect[iSample]->Branch(methodName4Tree,&ptjjj,methodName4Tree2);
  
  ///==== loop ====
  Long64_t nentries = treeJetLepVect[iSample]->GetEntries();
  
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   if ((iEntry%1000) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
   
   treeJetLepVect[iSample]->GetEntry(iEntry);
   
   TLorentzVector jet1;
   jet1.SetPtEtaPhiE(jetpt1, jeteta1, jetphi1, jetpt1/sin(2*atan(exp(-jeteta1))));
   
   TLorentzVector jet2;
   jet2.SetPtEtaPhiE(jetpt2, jeteta2, jetphi2, jetpt2/sin(2*atan(exp(-jeteta2))));
   
   TLorentzVector jet3;
   jet3.SetPtEtaPhiE(jetpt3, jeteta3, jetphi3, jetpt3/sin(2*atan(exp(-jeteta3))));
   
   TLorentzVector jet4;
   jet4.SetPtEtaPhiE(jetpt4, jeteta4, jetphi4, jetpt4/sin(2*atan(exp(-jeteta4))));
   
   TLorentzVector jetSum4 = jet1 + jet2 + jet3 + jet4;
   TLorentzVector jetSum3 = jet1 + jet2 + jet3;
   
   if (jetpt4 != 0) {
   mjjjj = jetSum4.M();
   ptjjjj = jetSum4.Pt();
   }
   else {
    mjjjj = -1;
    ptjjjj = -1;
   }
   
   mjjj = jetSum3.M();
   ptjjj = jetSum3.Pt();
   
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



