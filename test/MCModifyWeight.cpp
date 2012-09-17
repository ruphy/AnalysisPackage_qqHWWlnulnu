#include "treeReader.h"
#include "hFactory.h"
#include "hFunctions.h"
#include "stdHisto.h"
#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "TLeaf.h"
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

#include "../test/Read.cc"
#include "PUclass.h"



///   
///      \  |             | _)   _|            \ \        /     _)         |      |   
///     |\/ |   _ \    _` |  |  |    |   |      \ \  \   /  _ \  |   _` |  __ \   __| 
///     |   |  (   |  (   |  |  __|  |   |       \ \  \ /   __/  |  (   |  | | |  |   
///    _|  _| \___/  \__,_| _| _|   \__, |        \_/\_/  \___| _| \__, | _| |_| \__| 
///                                 ____/                          |___/              
///   



int main(int argc, char** argv){ 
 //Check if all nedeed arguments to parse are there                                                                                                                               
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 
 std::cout << "  " << std::endl;
 std::cout << "  " << std::endl;
 std::cout << "     " << std::endl;
 std::cout << "        \\  |             | _)   _|            \\ \\        /     _)         |      |   " << std::endl;
 std::cout << "       |\\/ |   _ \\    _` |  |  |    |   |      \\ \\  \\   /  _ \\  |   _` |  __ \\   __| " << std::endl; 
 std::cout << "       |   |  (   |  (   |  |  __|  |   |       \\ \\  \\ /   __/  |  (   |  | | |  |   " << std::endl;
 std::cout << "      _|  _| \\___/  \\__,_| _| _|   \\__, |        \\_/\\_/  \\___| _| \\__, | _| |_| \\__| " << std::endl;
 std::cout << "                                   ____/                          |___/              " << std::endl;
 std::cout << "     " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");
 std::string fileSamples = gConfigParser -> readStringOption("Input::fileSamples");
 std::string inputDirectory = gConfigParser -> readStringOption("Input::inputDirectory");
 
 TTree *treeJetLepVect[1000];
 TTree *newtreeJetLepVect[1000];
 
 char nameFileIn[1000];
 char *nameSample[1000];
 int PUScenarioIndex[1000]; //---- not used, but to reuse code and simplicity
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 int numberOfSamples = ReadFileWeight(nameFileIn, nameSample, PUScenarioIndex); 
 
 std::cout << std::endl;
 std::cout << " numberOfSamples = " << numberOfSamples << std::endl;
 std::cout << std::endl;
 
 ///==== debug flag (begin) ==== 
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  
 ///==== debug flag (end) ==== 
 
 
 ///==== reweighting function (begin) ====
 std::string nameReweightingFunction; 
 try {
  nameReweightingFunction = gConfigParser -> readStringOption("Rewight::nameReweightingFunction");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Rewight::nameReweightingFunction  " << nameReweightingFunction  << std::endl;  
 ///==== reweighting function (end) ====

 ///==== reweighting function file (begin) ====
 std::string nameReweightingFunctionFile; 
 std::string nameReweightingFunctionFileFormula; 
 std::string nameReweightingFunctionFileWithFormula; 
 bool fromFile = false;
 try {
  nameReweightingFunctionFile = gConfigParser -> readStringOption("Rewight::nameReweightingFunctionFile");
  nameReweightingFunctionFileWithFormula = gConfigParser -> readStringOption("Rewight::nameReweightingFunctionFileFormula");
  std::ifstream indata;
  indata.open(nameReweightingFunctionFileWithFormula.c_str()); // opens the file
  indata >> nameReweightingFunctionFileFormula;
  indata.close();
 
  TString toLoad = Form (".L %s+",nameReweightingFunctionFile.c_str());
  std::cout << " to Load = " << toLoad.Data() << std::endl;
  gROOT->ProcessLine(toLoad);
  fromFile = true;
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Rewight::nameReweightingFunctionFile             " << nameReweightingFunctionFile         << std::endl;  
 std::cout << ">>>>> Rewight::nameReweightingFunctionFileWithFormula  " << nameReweightingFunctionFileWithFormula  << std::endl;  
 std::cout << ">>>>> Rewight::nameReweightingFunctionFileFormula      " << nameReweightingFunctionFileFormula  << std::endl;  
 
 ///==== reweighting function (end) ====
 
 
 std::string nameNewWeight; 
 nameNewWeight = gConfigParser -> readStringOption("Rewight::nameNewWeight");
 std::cout << ">>>>> Rewight::nameNewWeight  " << nameNewWeight  << std::endl;  
 
 std::string nameOldWeight; 
 nameOldWeight = gConfigParser -> readStringOption("Rewight::nameOldWeight");
 std::cout << ">>>>> Rewight::nameOldWeight  " << nameOldWeight  << std::endl;  
 
 
//  TString toDo;
//  if (!fromFile) {
//   toDo = Form ("nuovoWeight = %s ; \n",nameReweightingFunction.c_str());
//  }
//  else {
//   toDo   = Form ("nuovoWeight = %s ; \n",nameReweightingFunctionFileFormula.c_str());
//  }  
//  std::cout << " to Do = " << toDo.Data() << std::endl;
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  char nameFile[20000];
  sprintf(nameFile,"%s/out_NtupleProducer_%s.root",inputDirectory.c_str(),nameSample[iSample]);  
  std::cout << " nameFile = " << nameFile << std::endl;
  std::cout << " nameSample[" << iSample << ":" << numberOfSamples << "] = " << nameSample[iSample] << std::endl;
  ///==== GetTree (begin) ==== 
  TFile* f = new TFile(nameFile, "update");      
  treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
  ///==== GetTree (end) ====
  
  std::cout << " >>>>> GetEntries " << treeJetLepVect[iSample]->GetEntries() << std::endl;    

  Long64_t nentries = treeJetLepVect[iSample]->GetEntries();
  treeJetLepVect[iSample]->SetEstimate(nentries);
  
//   treeJetLepVect[iSample]->Draw(nameOldWeight.c_str(),"","para goff"); //---- save "weights" ----
//   weightBefore = treeJetLepVect[iSample]->GetV1(); //---- get them ----
//   std::cout << " >>>> previous weights got" << std::endl;
  double newweight;
  TString newBranchName = Form ("%s/D",nameNewWeight.c_str());
  TBranch *newBranch = treeJetLepVect[iSample] -> Branch(nameNewWeight.c_str(),&newweight,newBranchName);  //---- add new weight branch
  
  TString toDraw;
  if (!fromFile) {
   toDraw = Form ("%s:%s",nameOldWeight.c_str(),nameReweightingFunction.c_str());
  }
  else {
   toDraw = Form ("%s:%s",nameOldWeight.c_str(),nameReweightingFunctionFileFormula.c_str());
  }  
  std::cout << " toDraw = " << toDraw.Data() << std::endl;
  treeJetLepVect[iSample]->Draw(toDraw,"","para goff");
  
  Double_t *weightBefore = treeJetLepVect[iSample]->GetV1();
  Double_t *weightTemp = treeJetLepVect[iSample]->GetV2();
  
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   if((iEntry%((nentries+10)/10)) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
   treeJetLepVect[iSample]->GetEntry(iEntry);
   
//    double nuovoWeight = 0;
//    gROOT->ProcessLine(toDo);
//    std::cout << " nuovoWeight = " << nuovoWeight << std::endl;
//    newweight = nuovoWeight; //---- update weight ...
   
//    newweight = weightBefore[iEntry] * weightTemp[iEntry]; //---- update weight ...
   
//    std::cout << " value = " << treeJetLepVect[iSample]->GetLeaf("weight_PU")->GetValue() << std::endl;
      
   newweight = weightBefore[iEntry] * weightTemp[iEntry]; //---- update weight ...
   
//    std::cout << " newweight = " << newweight << " =  weightBefore[iEntry]{" << weightBefore[iEntry] << "} * weightTemp[iEntry]{" << weightTemp[iEntry] << "} " << std::endl;
   
   
   newBranch->Fill();                       //---- ... and save it!
  }
  // save only the new version of the tree
  treeJetLepVect[iSample]->Write("", TObject::kOverwrite);
  f->Close();
 }
 
 std::cout << " *** end *** " << std::endl;
}

