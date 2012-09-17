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

#include "TEntryList.h"
#include "PUclass.h"

#include <iomanip>
#include <sstream>

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif


///
///
///      ____| _)  |  |                     _ \                     |                       _)      ____|        |   
///      |      |  |  __|   _ \   __|      |   |  |   |  __ \       |      |   |  __ `__ \   |      __| \ \   /  __| 
///      __|    |  |  |     __/  |         __ <   |   |  |   |      |      |   |  |   |   |  |      |    \ \ /   |   
///     _|     _| _| \__| \___| _|        _| \_\ \__,_| _|  _|     _____| \__,_| _|  _|  _| _|     _____| \_/   \__| 
///                                                                                                                  
///    
///     
///   
///   


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
 
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "       ____| _)  |  |                     _ \\                     |                       _)      ____|        |   " << std::endl;
 std::cout << "       |      |  |  __|   _ \\   __|      |   |  |   |  __ \\       |      |   |  __ `__ \\   |      __| \\ \\   /  __| " << std::endl;
 std::cout << "       __|    |  |  |     __/  |         __ <   |   |  |   |      |      |   |  |   |   |  |      |    \\ \\ /   |   " << std::endl;
 std::cout << "      _|     _| _| \\__| \\___| _|        _| \\_\\ \\__,_| _|  _|     _____| \\__,_| _|  _|  _| _|     _____| \\_/   \\__| " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl; 

 char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
 char black[] = { 0x1b, '[', '0', ';', '3', '0', 'm', 0 };
 char red[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
 char green[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
 char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
 char blue[] = { 0x1b, '[', '0', ';', '3', '4', 'm', 0 };
 char purple[] = { 0x1b, '[', '0', ';', '3', '5', 'm', 0 };
 char cyan[] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
 char Lgray[] = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
 char Dgray[] = { 0x1b, '[', '0', ';', '3', '8', 'm', 0 };
 char Bred[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
 //for bold colors, just change the 0 after the [ to a 1
 
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

 std::string outputDirectory = gConfigParser -> readStringOption("Output::outputDirectory");
 
 
 
 UInt_t run;
 UInt_t lumi;
 UInt_t event;
 
 TTree *treeEffVect[100];
 TTree *treeJetLepVect[100];
  
 char *nameSampleIn  [1000];
 char *nameSampleOut [1000];
 
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 int numberOfSamples = ReadFileInOut(nameFileIn, nameSampleIn, nameSampleOut);

 ///==== debug flag ====
 
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  
 
 
 ///==== input RunLumiEvt list ====

 
 std::string buffer;
 char temp[10000];
 
 
 
 
 
 
 std::vector<int> RunSkip ;
 
 std::string ListRunSkip;
 
 try {
  ListRunSkip = gConfigParser -> readStringOption("Input::ListRunSkip");
  std::cout << " ListRunSkip = " << ListRunSkip.c_str() << std::endl;

  std::ifstream inFileListRunSkip(ListRunSkip.c_str());
  
  while(!inFileListRunSkip.eof()){
   getline(inFileListRunSkip,buffer);
   if (buffer != ""){ ///---> save from empty line at the end!
   if (buffer.at(0) != '#'){   
    std::stringstream line( buffer );
    line >> temp;  RunSkip.push_back(atoi(temp));
   } 
   }
  }
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 
 
 
 
 //  <iEvent>
 std::vector<int> Run ;
 std::vector<int> Lumi;
 std::vector<int> Evt ;
 
 std::string ListRun;
 
 try {
  ListRun = gConfigParser -> readStringOption("Input::ListRun");
  std::cout << " ListRun = " << ListRun.c_str() << std::endl;
 
  std::ifstream inFileListRun(ListRun.c_str());
  
  while(!inFileListRun.eof()){
   getline(inFileListRun,buffer);
   if (buffer != ""){ ///---> save from empty line at the end!
   if (buffer.at(0) != '#'){   
    std::stringstream line( buffer );
    line >> temp;  Run.push_back(atoi(temp));
    Lumi.push_back(-1);
    Evt.push_back(-1);
   } 
   }
  }
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 
 
 std::string ListRunLumiEvt;
 
 try {
  ListRunLumiEvt = gConfigParser -> readStringOption("Input::ListRunLumiEvt");
  std::cout << " ListRunLumiEvt = " << ListRunLumiEvt.c_str() << std::endl;

  std::ifstream inFileList(ListRunLumiEvt.c_str());
  while(!inFileList.eof()){
   getline(inFileList,buffer);
   if (buffer != ""){ ///---> save from empty line at the end!
   if (buffer.at(0) != '#'){   
    std::stringstream line( buffer );
    line >> temp;  Run.push_back(atoi(temp));
    line >> temp; Lumi.push_back(atoi(temp));
    line >> temp;  Evt.push_back(atoi(temp));
   } 
   }
  }
  
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
//   std::cerr << " *** ERROR *** " << std::endl;  
//   return 0;
 }
 
 
 
 ///==== program ====
 
 double start, end;
 start = clock();
 
 ///==== cicle on samples ====
 for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSampleIn[iSample]);  
  if (debug) std::cout << " nameFile = " << nameFile << std::endl;
  std::cout << " Sample[" << iSample << ":" << numberOfSamples << "] = " << nameSampleIn[iSample] << " ~~ nameFile = " << nameFile << std::endl;
  
  
  TFile* f = new TFile(nameFile, "READ");
  
  treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
  
  treeJetLepVect[iSample] -> SetBranchAddress("run",  &run);
  treeJetLepVect[iSample] -> SetBranchAddress("lumi", &lumi);
  treeJetLepVect[iSample] -> SetBranchAddress("event",&event);
  
  sprintf(nameFile,"%s/%s%s.root",outputDirectory.c_str(),inputBeginningFile.c_str(),nameSampleOut[iSample]);  
  if (debug) std::cout << " nameFile = " << nameFile << std::endl;
  
  TFile *newfile = new TFile(nameFile,"recreate");
  TTree *newtree = treeJetLepVect[iSample]->CloneTree(0);
    
  int nEvent = treeJetLepVect[iSample]->GetEntries();
  for (int iEvent = 0; iEvent<nEvent; iEvent++){   
   if (!(iEvent%(nEvent/10))) std::cout << " iEvent = " << iEvent << " :: " << nEvent << std::endl;
   treeJetLepVect[iSample]->GetEntry(iEvent);
  
   bool isSelected = false;
 
   for (int iRun = 0; iRun < Run.size(); iRun++) {
    if (run == Run.at(iRun) && lumi == Lumi.at(iRun) && event == Evt.at(iRun)) isSelected = true;
    if (run == Run.at(iRun) && lumi == Lumi.at(iRun) && Evt.at(iRun) == -1   ) isSelected = true;
    if (run == Run.at(iRun) && Lumi.at(iRun) == -1   && event == Evt.at(iRun)) isSelected = true;
    if (run == Run.at(iRun) && Lumi.at(iRun) == -1   && Evt.at(iRun) == -1   ) isSelected = true;
   }

   //---- skip has priority w.r.t selection!
   if (Run.size() == 0) isSelected = true;
   for (int iRun = 0; iRun < RunSkip.size(); iRun++) {
    if (run == RunSkip.at(iRun)) isSelected = false;
   }


   if (isSelected) {
    newtree->Fill();
   }
  }
  
  newtree->AutoSave();
  
 } ///==== end cicle on samples ====
 
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
 
 
 
 
 std::cerr << " ******************************************* end *******************************************" << std::endl;
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 
 
}





