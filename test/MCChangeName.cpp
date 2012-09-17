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
 
 
 //---- now change name of branch ----
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  char nameFile[20000];
  sprintf(nameFile,"%s/out_NtupleProducer_%s.root",inputDirectory.c_str(),nameSample[iSample]);  
  std::cout << " nameFile = " << nameFile << std::endl;
  ///==== GetTree (begin) ==== 
  TFile* newf = new TFile(nameFile, "update");      
  newtreeJetLepVect[iSample] = (TTree*) newf->Get(treeName.c_str());
  ///==== GetTree (end) ====  
  double weight;
  TBranch *newBranch = newtreeJetLepVect[iSample] -> Branch("uffiweight",&weight,"uffiweight/D");  //---- add new weight branch

  double oldweight;
  newtreeJetLepVect[iSample]->SetBranchAddress("newweight",&oldweight); 
  std::cout << " >>>>> GetEntries " << newtreeJetLepVect[iSample]->GetEntries() << std::endl;    
  int nentries = newtreeJetLepVect[iSample]->GetEntries();
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   if((iEntry%((nentries+10)/10)) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
   newtreeJetLepVect[iSample]->GetEntry(iEntry);
   weight = oldweight;
   newBranch->Fill();                       //---- ... and save it!
  }  
  newtreeJetLepVect[iSample]->Write("", TObject::kOverwrite);
  newf->Close();
 }
 
 
 std::cout << " *** end *** " << std::endl;
}









