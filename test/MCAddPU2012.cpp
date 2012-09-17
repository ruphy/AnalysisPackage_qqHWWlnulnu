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




///     
///        \  |   ___|         \         |      |       _ \   |   |     ___ \    _ \ _ | ___ \  
///       |\/ |  |            _ \     _` |   _` |      |   |  |   |        ) |  |   |  |    ) | 
///       |   |  |           ___ \   (   |  (   |      ___/   |   |       __/   |   |  |   __/  
///      _|  _| \____|     _/    _\ \__,_| \__,_|     _|     \___/      _____| \___/  _| _____| 
///                                                                                             

int main(int argc, char** argv) {
 
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 
 std::cout << "          " << std::endl;  
 std::cout << "          " << std::endl;       
 
 std::cout << "                         " << std::endl;  
 std::cout << "                  \\  |   ___|         \\         |      |       _ \\   |   |     ___ \\    _ \\ _ | ___ \\            " << std::endl;  
 std::cout << "                 |\\/ |  |            _ \\     _` |   _` |      |   |  |   |        ) |  |   |  |    ) |           " << std::endl;   
 std::cout << "                 |   |  |           ___ \\   (   |  (   |      ___/   |   |       __/   |   |  |   __/            " << std::endl;    
 std::cout << "                _|  _| \\____|     _/    _\\ \\__,_| \\__,_|     _|     \\___/      _____| \\___/  _| _____|           " << std::endl;   
 std::cout << "          " << std::endl;                                                                                                       
 std::cout << "          " << std::endl;
 std::cout << "          " << std::endl;

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
 

 std::string outputDirectory = gConfigParser -> readStringOption("Output::outputDirectory");
 
 
 
 
 
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
 
 
 ///==== weight file ==== 
 
 std::vector<double> puScaleDATA = gConfigParser -> readDoubleListOption("Options::puScaleDATA");
 std::vector<double> puScaleMC   = gConfigParser -> readDoubleListOption("Options::puScaleMC");
 
 double integralDATA = 0;
 double integralMC   = 0;
 
//  puScaleMC.pop_back();
//  puScaleDATA.pop_back();
 
 for (int ibin = 0; ibin < puScaleDATA.size(); ibin++) {
  integralDATA += puScaleDATA.at(ibin);
  integralMC   += puScaleMC.at(ibin);
 }
 std::cout << " integralDATA = " << integralDATA << std::endl;
 std::cout << " integralMC   = " << integralMC   << std::endl;
 
 for (int ibin = 0; ibin < puScaleDATA.size(); ibin++) {
//   puScaleDATA.at(ibin) = puScaleDATA.at(ibin) * integralMC / integralDATA;
  puScaleMC.at(ibin)   = puScaleMC.at(ibin)   * integralDATA / integralMC;
 }
 
 
 
 ///---- trees ----
 TFile* outputRootFile[1001];
 TTree* cloneTreeJetLepVect[1001];
 
 TTree *treeJetLepVect[1001];
 TFile* file[1001];
 
 float trpu;
 float puW2012;
 
 
 char *nameSample[1001];
 char *nameHumanReadable[1001];
 char* xsectionName[1001];
 
 char nameFileIn[1001];
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 
 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
  
  file[iSample] = new TFile(nameFile, "READ");
  
  treeJetLepVect[iSample] = (TTree*) file[iSample]->Get(treeName.c_str());
  char nameTreeJetLep[100];
  treeJetLepVect[iSample] -> SetName(nameTreeJetLep);  
  treeJetLepVect[iSample] -> SetBranchAddress ("trpu",&trpu);
  
  sprintf(nameFile,"%s/%s%s.root",outputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);    
  outputRootFile[iSample] = new TFile ( nameFile, "RECREATE") ;
  outputRootFile[iSample] -> cd () ;
  cloneTreeJetLepVect[iSample] = treeJetLepVect[iSample] -> CloneTree (0) ;

  ///---- dump in new trees in new root file ----
  file[iSample] -> cd();
  ///==== loop ====
  Long64_t nentries = treeJetLepVect[iSample]->GetEntries();
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   treeJetLepVect[iSample]->GetEntry(iEntry);
   cloneTreeJetLepVect[iSample] -> Fill () ; 
  }

  ///---- add new weights ----
  std::cout << " iSample = " << iSample << " :: " << numberOfSamples << std::endl;
  file[iSample] -> cd();
  
  std::cout << " >>>>> GetEntries " << treeJetLepVect[iSample]->GetEntries() << std::endl;  
  
  TBranch* newBranch_puW2012  = cloneTreeJetLepVect[iSample]->Branch("puW2012",  &puW2012,  "puW2012/F"  );
  
  ///==== loop ====
  
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++) {
   if((iEntry%10000) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;      
   treeJetLepVect[iSample]->GetEntry(iEntry);  
   
//    if (round(trpu)<puScaleDATA.size()) {
//     puW2012   = puScaleMC.at(round(trpu)) != 0 ? 1. * puScaleDATA.at(round(trpu)) / puScaleMC.at(round(trpu)) : 1.;
   if (trpu<puScaleDATA.size()) {
     puW2012   = puScaleMC.at((int) trpu) != 0 ? 1. * puScaleDATA.at((int) trpu) / puScaleMC.at((int) trpu) : 1.;
   }
   else {
    puW2012 = puScaleMC.at(puScaleDATA.size()-1) != 0 ? 1. * puScaleDATA.at(puScaleDATA.size()-1) / puScaleMC.at(puScaleDATA.size()-1) : 1.;
   }
   
   newBranch_puW2012   -> Fill();   
  }
 }
 
 
 ///---- save in output files ---- 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  outputRootFile[iSample]->cd();
  cloneTreeJetLepVect[iSample] -> SetName (treeName.c_str());
  cloneTreeJetLepVect[iSample]->Write(treeName.c_str(),TObject::kOverwrite);
  outputRootFile[iSample] -> Close () ;
 }
 
 
}



