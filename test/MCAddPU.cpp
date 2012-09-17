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
///        \  |   ___|         \         |      |       _ \   |   | 
///       |\/ |  |            _ \     _` |   _` |      |   |  |   | 
///       |   |  |           ___ \   (   |  (   |      ___/   |   | 
///      _|  _| \____|     _/    _\ \__,_| \__,_|     _|     \___/  
///                                                                 



int main(int argc, char** argv) {
 
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }


std::cout << "          " << std::endl;  
std::cout << "          " << std::endl;       
std::cout << "              \\  |   ___|         \\         |      |       _ \\   |   |       " << std::endl;
std::cout << "             |\\/ |  |            _ \\     _` |   _` |      |   |  |   |       " << std::endl;
std::cout << "             |   |  |           ___ \\   (   |  (   |      ___/   |   |       " << std::endl;
std::cout << "            _|  _| \\____|     _/    _\\ \\__,_| \\__,_|     _|     \\___/        " << std::endl;
std::cout << "                                                                             " << std::endl;
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
 ///  scale-Up
 ///  scale-Down
 ///
 
 std::vector<double> puScaleDATA = gConfigParser -> readDoubleListOption("Options::puScaleDATA");
 
 ///---- creation +/-8% distributions of PU DATI ----
 std::vector<double> puScaleDATAup;
 std::vector<double> puScaleDATAdown;
 
 TH1F* hpuScaleDATA = new TH1F ("hpuScaleDATA","hpuScaleDATA",puScaleDATA.size(),0,puScaleDATA.size());
 for (int ipu = 0; ipu < puScaleDATA.size(); ipu++) {
  hpuScaleDATA->SetBinContent(ipu+1,puScaleDATA.at(ipu));
 }
 
 for (int ipu = 0; ipu < puScaleDATA.size(); ipu++) {
  double integral_up   = hpuScaleDATA->Integral((ipu+1)*1.08,(ipu+2)*1.08);
  double integral_down = hpuScaleDATA->Integral((ipu+1)*0.92,(ipu+2)*0.92);
  puScaleDATAup.push_back(integral_up);
  puScaleDATAdown.push_back(integral_down);
 }
 
 
 
 
 ///---- trees ----
 TFile* outputRootFile[1001];
 TTree* cloneTreeJetLepVect[1001];
 
 TTree *treeJetLepVect[1001];
 TFile* file[1001];
 
 float itpu;
 float puW;
 float puWup;
 float puWdown;
 
 
 
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
  treeJetLepVect[iSample] -> SetBranchAddress ("itpu",&itpu);
  treeJetLepVect[iSample] -> SetBranchAddress ("puW",&puW);
  
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
  
  TBranch* newBranch_puWup   = cloneTreeJetLepVect[iSample]->Branch("puWup",  &puWup,  "puWup/F"  );
  TBranch* newBranch_puWdown = cloneTreeJetLepVect[iSample]->Branch("puWdown",&puWdown,"puWdown/F");
  
  ///==== loop ====
  
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++) {
   if((iEntry%1000) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;      
   treeJetLepVect[iSample]->GetEntry(iEntry);  
   
   if (itpu<puScaleDATA.size()) {
    puWup   = puScaleDATA.at(itpu) != 0 ? puW * puScaleDATAup.at(itpu)   / puScaleDATA.at(itpu) : puW;
    puWdown = puScaleDATA.at(itpu) != 0 ? puW * puScaleDATAdown.at(itpu) / puScaleDATA.at(itpu) : puW;
   }
   else {
    puWup   = puScaleDATA.at(puScaleDATA.size()-1) != 0 ? puW * puScaleDATAup.at(puScaleDATA.size()-1)   / puScaleDATA.at(puScaleDATA.size()-1) : puW ;
    puWdown = puScaleDATA.at(puScaleDATA.size()-1) != 0 ? puW * puScaleDATAdown.at(puScaleDATA.size()-1) / puScaleDATA.at(puScaleDATA.size()-1) : puW ;
   }
   
   newBranch_puWup   -> Fill();
   newBranch_puWdown -> Fill();
   
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



