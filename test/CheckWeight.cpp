#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "TPie.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMinuit.h"
#include "qqHWWlnulnuUtils.h"
#include "Variables.h"

#include "../test/TDRStyle.cc"
#include "../test/Read.cc"
// #include "../test/DrawTools.h"

#include "PUclass.h"

#include <iomanip>



#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif


///     
///     
///        ___|  |                  |        \ \        /     _)         |      |   
///       |      __ \    _ \   __|  |  /      \ \  \   /  _ \  |   _` |  __ \   __| 
///       |      | | |   __/  (       <        \ \  \ /   __/  |  (   |  | | |  |   
///      \____| _| |_| \___| \___| _|\_\        \_/\_/  \___| _| \__, | _| |_| \__| 
///                                                              |___/              
///     
///     

// std::vector<double> PUWeight;

int GetNumList(std::vector<int> &list){
 int result = 0;
 for (int it = 0; it<list.size(); it++) result += list.at(it);
 return result;
}


int main(int argc, char** argv)
{ 
 TDRStyle();
 
 gStyle->SetPadTopMargin(0.11);
 gStyle->SetPadLeftMargin(0.07);
 gStyle->SetPadRightMargin(0.23);
 gStyle->cd(); 
 
 
 
 std::cout << "          " << std::endl;
 std::cout << "          " << std::endl;
 std::cout << "            ___|  |                  |        \\ \\        /     _)         |      |    " << std::endl;
 std::cout << "           |      __ \\    _ \\   __|  |  /      \\ \\  \\   /  _ \\  |   _` |  __ \\   __|  " << std::endl;
 std::cout << "           |      | | |   __/  (       <        \\ \\  \\ /   __/  |  (   |  | | |  |    " << std::endl;
 std::cout << "          \\____| _| |_| \\___| \\___| _|\\_\\        \\_/\\_/  \\___| _| \\__, | _| |_| \\__|  " << std::endl;
 std::cout << "                                                                  |___/               " << std::endl;
 std::cout << "          " << std::endl;
 std::cout << "          " << std::endl;
 
 
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
 
 std::string inputBeginningFile = "out_NtupleProducer_"; 
 try {
  inputBeginningFile = gConfigParser -> readStringOption("Input::inputBeginningFile");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Input::inputBeginningFile  " << inputBeginningFile  << std::endl;  
 
 float weight;
 std::string nameWeight = "weight"; 
 nameWeight = gConfigParser -> readStringOption("Input::nameWeight");
 
 TTree *treeJetLepVect[1000];
 

 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 double Normalization[1000];
 float xsection[1000];
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());

 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
 
 
 ///==== debug flag ====
 
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  
 
 ///==== program ====
 
 int Entries[100];
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  xsection[iSample] = atof(xsectionName[iSample]);
 }

 for (int iSample=0; iSample<numberOfSamples; iSample++){
  if (debug) std::cout << " iSample = " << iSample << std::endl;
  
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
  if (debug) std::cout << " nameFile = " << nameFile << std::endl;
  
  TFile* f = new TFile(nameFile, "READ");
  
  treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
  char nameTreeJetLep[100];
  sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
  treeJetLepVect[iSample]->SetName(nameTreeJetLep);
  treeJetLepVect[iSample]->SetBranchAddress(nameWeight.c_str(),&weight);
  
  if (treeJetLepVect[iSample]->GetEntries() != 0) {
   treeJetLepVect[iSample]->GetEntry(0);
   if (weight == xsection[iSample]){
    std::cout << " OK ";
   }
   else {
    std::cout << " NO ";
   }
   std::cout << " weight[" << nameWeight.c_str() <<  "][" << iSample << "] = " << weight << " = " << xsection[iSample];
   if (weight != xsection[iSample]){
    std::cout << " ---> " << nameSample[iSample];
   }
   std::cout << std::endl;
  }
  else {
   std::cout << " problem ... 0 entries ! " << std::endl;
   exit(1);
  }
 }
 
 std::cout << std::endl;
 
}





