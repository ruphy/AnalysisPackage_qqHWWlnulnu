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

#include <iomanip>
#include <sstream>

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif


///
///
///       __ \                                |                       _)       _ \                     ____|        |   
///       |   |  |   |  __ `__ \   __ \       |      |   |  __ `__ \   |      |   |  |   |  __ \       __| \ \   /  __| 
///       |   |  |   |  |   |   |  |   |      |      |   |  |   |   |  |      __ <   |   |  |   |      |    \ \ /   |   
///      ____/  \__,_| _|  _|  _|  .__/      _____| \__,_| _|  _|  _| _|     _| \_\ \__,_| _|  _|     _____| \_/   \__| 
///                               _|                                                                                    
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
 std::cout << "          __ \\                                |                       _)       _ \\                     ____|        |    " << std::endl;
 std::cout << "          |   |  |   |  __ `__ \\   __ \\       |      |   |  __ `__ \\   |      |   |  |   |  __ \\       __| \\ \\   /  __|  " << std::endl; 
 std::cout << "          |   |  |   |  |   |   |  |   |      |      |   |  |   |   |  |      __ <   |   |  |   |      |    \\ \\ /   |    " << std::endl;   
 std::cout << "         ____/  \\__,_| _|  _|  _|  .__/      _____| \\__,_| _|  _|  _| _|     _| \\_\\ \\__,_| _|  _|     _____| \\_/   \\__|  " << std::endl; 
 std::cout << "                                  _|                                        " << std::endl;                                             
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
 
 EColor vColor[1000] = {
  (EColor) (kRed+1),
  (EColor) (kRed+3),
  (EColor) (kGray+1),
  (EColor) (kAzure-2),
  (EColor) (kAzure-9),
  (EColor) (kYellow),
  (EColor) (kGreen+2),
//   
  kGreen,
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
 
 std::string inputBeginningFile = "out_NtupleProducer_"; 
 try {
  inputBeginningFile = gConfigParser -> readStringOption("Input::inputBeginningFile");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Input::inputBeginningFile  " << inputBeginningFile  << std::endl;  
 
 TTree *treeEffVect[100];
 TTree *treeJetLepVect[100];
 
 //  <iEvent>[iCut]
 std::vector<int> Run [100];
 std::vector<int> Lumi[100];
 std::vector<int> Evt [100];
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 double Normalization[1000];
 double xsection[1000];
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());

 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);

 ///==== list of selections to perform (NOT sequential additive selections) ====
 std::string CutFile = gConfigParser -> readStringOption("Selections::CutFile");
 std::string CutHRFile = "";
 try {
  CutHRFile = gConfigParser -> readStringOption("Selections::CutHRFile");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 std::vector<std::string> vCut;
 std::vector<std::string> vCutHR;
 
 std::cout << " nCuts   = " << ReadFileCut(CutFile, vCut) << std::endl;
 if (CutHRFile != "") {
  std::cout << " nCutsHR = " << ReadFileCutHR(CutHRFile, vCutHR) << std::endl;
 }
 
 if (vCutHR.size() < vCut.size()) {
  int size1 = vCut.size();
  int size2 = vCutHR.size();
  for (int i=0; i<(size1-size2+2); i++) {
   vCutHR.push_back("test");
  }
 }

 for (unsigned int iCut = 0; iCut<vCutHR.size(); iCut++){ 
  std::cout << " vCutHR[" << iCut << "] = " << vCutHR.at(iCut).c_str() << std::endl;
 }
 
 ///==== Latinos flag ==== 
 bool  Latinos = false; 
 try {
  Latinos = gConfigParser -> readBoolOption("Input::Latinos");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::Latinos  " << Latinos  << std::endl;  
 
 
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
 
 
 double start, end;
 start = clock();
  
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  xsection[iSample] = atof(xsectionName[iSample]);
 }

for (int iSample=0; iSample<numberOfSamples; iSample++){
  
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
  if (debug) std::cout << " nameFile = " << nameFile << std::endl;
  
  TFile* f = new TFile(nameFile, "READ");
  
  treeEffVect[iSample] = (TTree*) f->Get(treeNameSelections.c_str());
  if (treeEffVect[iSample] != 0) {
   char nameTreeEff[100];
   sprintf(nameTreeEff,"treeEff_%d",iSample); 
   treeEffVect[iSample]->SetName(nameTreeEff);      
  }
  
  treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
  char nameTreeJetLep[100];
  sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
  treeJetLepVect[iSample]->SetName(nameTreeJetLep);
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
 for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
  bool flag_name = false;
  for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
   if (reduced_name_samples.at(iName) == name_samples.at(iSample)) flag_name = true;
  }
  if (flag_name == false) {
   reduced_name_samples.push_back(name_samples.at(iSample));
   reduced_name_samples_flag.push_back(-1);
  }

 }

 
 std::cout << " numberOfSamples = " << numberOfSamples << std::endl;
 for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
  double XSection;
  int numEntriesBefore;
  double preselection_efficiency;
  if (treeEffVect[iSample] != 0) {   
   treeEffVect[iSample]->SetBranchAddress("XSection",&XSection);
   treeEffVect[iSample]->SetBranchAddress("numEntriesBefore",&numEntriesBefore);
   treeEffVect[iSample]->SetBranchAddress("preselection_efficiency",&preselection_efficiency);  
   treeEffVect[iSample]->GetEntry(0);
  }
  std::cout << " Xsection = " << XSection << " ~~~> " << xsection[iSample] << std::endl;
  XSection = xsection[iSample];
 }

 
 ///==== get number in sample list that correspond to DATA ====
 int numDATA = -1;
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  if (reduced_name_samples.at(iName) == "DATA") {
   numDATA = iName;
  }
 }

 if (debug) std::cout << " Cut size = " << vCut.size() << " ~~ " << std::endl;
 std::cout.precision (5) ;
 std::cout.unsetf(std::ios::scientific);

 
 ///==== cicle on selections ====
 for (unsigned int iCut =0; iCut<vCut.size(); iCut++){
  TString Cut = Form ("%s",vCut.at(iCut).c_str());
  if (debug) std::cout << " Cut[" << iCut << ":" << vCut.size() << "] = " << Cut.Data() << " ~~ " << std::endl;
  ///==== initialize ====
  for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
   reduced_name_samples_flag.at(iName) = -1;
  }
  
  ///==== cicle on samples ====
  for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
   if (debug) std::cout << " Sample[" << iSample << ":" << numberOfSamples << "] = " << nameSample[iSample] << " ~~ " << std::endl;
  
   bool isData = false;
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    if (name_samples.at(iSample) == reduced_name_samples.at(iName)){
     if (iName == numDATA) {
      isData = true;
     }
    }
   }  
   
   //---- only if DATA it make sense! ----
   if (isData) {
    TString CutExtended  = Cut;
    treeJetLepVect[iSample]->SetEntryList(0); 
    treeJetLepVect[iSample]->Draw(">> myList",CutExtended,"entrylist");
    TEntryList *myList = (TEntryList*)gDirectory->Get("myList");
    treeJetLepVect[iSample]->SetEntryList(myList); 
    
    std::cout << " Dumping ... " << std::endl;
    
    treeJetLepVect[iSample]->SetEstimate(myList->GetN());
    treeJetLepVect[iSample]->Draw("run:lumi:event","","para goff");
    int nEntries = myList->GetN();
    
    std::cout << " nEntries = " << nEntries << std::endl;
    
    Double_t *vTempRun  = treeJetLepVect[iSample]->GetV1();
    Double_t *vTempLumi = treeJetLepVect[iSample]->GetV2();
    Double_t *vTempEvt  = treeJetLepVect[iSample]->GetV3();
    
    std::cout << " got! " << std::endl;
    
    for (int iEntry = 0; iEntry<nEntries; iEntry++){
     if (!(iEntry%(nEntries/10))) std::cout << "iEntry = " << iEntry << " :: " << nEntries << std::endl;
     Run[iCut] .push_back(vTempRun[iEntry]);
     Lumi[iCut].push_back(vTempLumi[iEntry]);
     Evt[iCut] .push_back(vTempEvt[iEntry]);
    }
   }
   
   std::cout <<"Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% "  << normal <<  " -- " <<  red << (((double) numberOfSamples - iSample)/(numberOfSamples))*100. << "% \r"  << normal << std::flush;   
  } ///==== end cicle on samples ====
   //std::cout << "Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% \r"  << normal << std::flush;   
  } ///==== end cicle on selections ====
 
 if (debug) std::cout << " >>> Reprocessing ... " << std::endl;
 
 std::cout << std::endl;
 
 
 
 
 
 
 
 ///==== output - txt file name ====
 
 std::cout.precision (5) ;
 std::cout.unsetf(std::ios::scientific);
 
 std::ofstream myfile;
 std::string ListRunLumiEvt;
 
 try {
  ListRunLumiEvt = gConfigParser -> readStringOption("Output::ListRunLumiEvt");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
  std::cerr << " *** ERROR *** " << std::endl;  
  return 0;
 }
 
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){ 
  std::string nameFile_ListRunLumiEvt = ListRunLumiEvt;
  nameFile_ListRunLumiEvt += "_";
  std::stringstream numberString;
  numberString << iCut;
  nameFile_ListRunLumiEvt += numberString.str();
  nameFile_ListRunLumiEvt += ".txt";
  myfile.open (nameFile_ListRunLumiEvt.c_str());
  std::cout << " preparing :: nameFile_ListRunLumiEvt " << nameFile_ListRunLumiEvt << std::endl;
  
  for (int iEvent=0; iEvent< Run[iCut].size(); iEvent++) {
   myfile << std::setw (15) << Run[iCut] .at(iEvent) << " ";
   myfile << std::setw (15) << Lumi[iCut].at(iEvent) << " ";
   myfile << std::setw (15) << Evt[iCut] .at(iEvent) << " ";
   myfile << std::endl;   
  }
  
  std::cout << " iCut = " << iCut << " :: numSelectedEvents = " << Run[iCut].size() << std::endl;
  
  myfile.close();
 }
//  
//  std::cout << "Writing to: " << nameOutDataCard << std::endl;
//  std::cout << std::endl;
 
 
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
 
 
 
 
 std::cerr << " ******************************************* end *******************************************" << std::endl;
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 
 
}





