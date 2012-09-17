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





#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif


///    
///      __ \     \  __ __|   \         |   |  |   __ __| 
///      |   |   _ \    |    _ \        |   |  |      |   
///      |   |  ___ \   |   ___ \       ___ |  |      |   
///     ____/ _/    _\ _| _/    _\     _|  _| _____| _|   
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
 
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "          __ \\     \\  __ __|   \\         |   |  |   __ __| " << std::endl;
 std::cout << "          |   |   _ \\    |    _ \\        |   |  |      |" << std::endl;   
 std::cout << "          |   |  ___ \\   |   ___ \\       ___ |  |      |" << std::endl;   
 std::cout << "         ____/ _/    _\\ _| _/    _\\     _|  _| _____| _|" << std::endl;   
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
  
 TTree *treeEffVect[100];
 TTree *treeJetLepVect[100];
 
 //  [iSample][iCut]
 double numEvents[100][200];
 
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
 std::vector<std::string> vCut;
 std::cout << " nCuts = " << ReadFileCut(CutFile, vCut) << std::endl;
 
 ///==== output file ====
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
 
 TFile outFile(OutFileName.c_str(),"RECREATE");
 outFile.cd();
 
 
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
  sprintf(nameFile,"%s/out_NtupleProducer_%s.root",inputDirectory.c_str(),nameSample[iSample]);  
  TFile* f = new TFile(nameFile, "READ");
  
  treeEffVect[iSample] = (TTree*) f->Get(treeNameSelections.c_str());
  char nameTreeEff[100];
  sprintf(nameTreeEff,"treeEff_%d",iSample); 
  treeEffVect[iSample]->SetName(nameTreeEff);      
  
  treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
  char nameTreeJetLep[100];
  sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
  treeJetLepVect[iSample]->SetName(nameTreeJetLep);
 }
 
 
 for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
  double XSection;
  int numEntriesBefore;
  double preselection_efficiency;
  treeEffVect[iSample]->SetBranchAddress("XSection",&XSection);
  treeEffVect[iSample]->SetBranchAddress("numEntriesBefore",&numEntriesBefore);
  treeEffVect[iSample]->SetBranchAddress("preselection_efficiency",&preselection_efficiency);  
  treeEffVect[iSample]->GetEntry(0);
  
  std::cout << " Xsection = " << XSection << " ~~~> " << xsection[iSample] << std::endl;
  XSection = xsection[iSample];
 }
 
 
 if (debug) std::cout << " Cut size = " << vCut.size() << " ~~ " << std::endl;
 
 std::cout.precision (3) ;
 ///==== cicle on selections ====
 for (uint iCut = 0; iCut<vCut.size(); iCut++){
  TString Cut = Form ("%s",vCut.at(iCut).c_str());
  if (debug) std::cout << " Cut[" << iCut << ":" << vCut.size() << "] = " << Cut.Data() << " ~~ " << std::endl;
  
  ///==== cicle on samples ====
  for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
   if (debug) std::cout << " Sample[" << iSample << ":" << numberOfSamples << "] = " << nameSample[iSample] << " ~~ " << std::endl;
   TString CutExtended;
   CutExtended = Form ("(%s)",Cut.Data());    
   numEvents[iSample][iCut] = treeJetLepVect[iSample]->GetEntries(CutExtended);
   std::cout << "Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% "  << normal <<  " -- " <<  red << (((double) numberOfSamples - iSample)/(numberOfSamples))*100. << "% \r"  << normal << std::flush;   
  } ///==== end cicle on samples ====
  //   std::cout << "Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% \r"  << normal << std::flush;   
 } ///==== end cicle on selections ====
 
 
 
 std::cout.precision (5) ;
 std::cout.unsetf(std::ios::scientific);
 
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << " *********************************** " << std::endl;
 for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
  std::cout << " | " << std::setw (8) << nameSample[iSample];
  std::cout << " ";
 }
 std::cout << std::endl;
 for (uint iCut = 0; iCut<vCut.size(); iCut++){
  std::cout << " | " << std::setw (8) <<  iCut;
  std::cout << " ";
  for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
   std::cout << " | " << cyan << std::setw (8) <<  numEvents[iSample][iCut];
   std::cout << normal << " " ;
  }
  std::cout << std::endl;
 }
 
 std::cerr << " ******************************************* end *******************************************" << std::endl;
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 
 
 ///==== save output ====
 outFile.cd();
 
}





