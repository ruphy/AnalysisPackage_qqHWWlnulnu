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
 
 std::string puScaleDATAhisto = gConfigParser -> readStringOption("Options::puScaleDATAhisto");
 std::string puScaleMChisto   = gConfigParser -> readStringOption("Options::puScaleMChisto");
 
 TString nameHistoDATA = Form ("pileup");
 TString nameHistoMC   = Form ("pileup");
 
 TFile* fileDATA = new TFile (puScaleDATAhisto.c_str(),"READ");
 TFile* fileMC   = new TFile (puScaleMChisto.c_str(),  "READ");
 
 TH1F* histoDATA = (TH1F*) fileDATA->Get(nameHistoDATA.Data()); 
 TH1F* histoMC   = (TH1F*) fileMC  ->Get(nameHistoMC.Data()); 
 
 int mc_nBin = histoMC->GetNbinsX();
 float mc_minValue = histoMC->GetXaxis()->GetXmin();
 float mc_maxValue = histoMC->GetXaxis()->GetXmax();
 float mc_dValue = (mc_maxValue - mc_minValue) / mc_nBin;
 
 
 int data_nBin = histoDATA->GetNbinsX();
 float data_minValue = histoDATA->GetXaxis()->GetXmin();
 float data_maxValue = histoDATA->GetXaxis()->GetXmax();
 float data_dValue = (data_maxValue - data_minValue) / data_nBin;
 
 int ratio = mc_dValue/data_dValue;
 int nBin = data_nBin;
 float minValue = data_minValue;
 float maxValue = data_maxValue;
 float dValue = data_dValue;
 
 std::cout << " ratio = " << ratio << std::endl;
 
//  if (data_dValue != dValue || data_maxValue!= maxValue || data_minValue!= minValue) {
 if ((mc_dValue/data_dValue - (int) (mc_dValue/data_dValue)) != 0) {
  std::cerr << " ERROR:: incompatible intervals!" << std::endl;
  exit(0);
 }
 
 std::vector<float> puScaleDATA;
 std::vector<float> puScaleMC;

 for (int iBin = 0; iBin < nBin; iBin++) {
  puScaleDATA.push_back (histoDATA->GetBinContent(iBin+1));
  int mcbin = iBin / ratio;
  puScaleMC.push_back   (histoMC->GetBinContent(mcbin+1));
 }
 
 float integralDATA = 0;
 float integralMC   = 0;
 
 for (int iBin = 0; iBin < nBin; iBin++) {
  integralDATA += puScaleDATA.at(iBin);
  integralMC   += puScaleMC.at(iBin);
 }
 std::cout << " integralDATA = " << integralDATA << std::endl;
 std::cout << " integralMC   = " << integralMC   << std::endl;
 
 for (int iBin = 0; iBin < puScaleDATA.size(); iBin++) {
  puScaleMC.at(iBin)   = puScaleMC.at(iBin)   * integralDATA / integralMC;
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
   if((iEntry%100000) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;      
   treeJetLepVect[iSample]->GetEntry(iEntry);  
   
   if (((int) (trpu/dValue))<puScaleDATA.size()) {
    puW2012   = puScaleMC.at(((int) (trpu/dValue))) != 0 ? 1. * puScaleDATA.at(((int) (trpu/dValue))) / puScaleMC.at(((int) (trpu/dValue))) : 1.;
//    if ((round(trpu/dValue))<puScaleDATA.size()) {
//     puW2012   = puScaleMC.at(round(trpu/dValue)) != 0 ? 1. * puScaleDATA.at(round(trpu/dValue)) / puScaleMC.at(round(trpu/dValue)) : 1.;
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



