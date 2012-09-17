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

#include "../test/LatinoStyle.C"
#include "../test/LatinoStyle2.C"

#include "../test/TDRStyle.cc"
#include "../test/Read.cc"
// #include "../test/DrawTools.h"

#include "PUclass.h"


#include "TProof.h"


#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif

///
///
///   ___|                                       _)                           \  |   ___|         /      __ \     \  __ __|   \    
///  |       _ \   __ `__ \   __ \    _` |   __|  |   __|   _ \   __ \       |\/ |  |            /       |   |   _ \    |    _ \   
///  |      (   |  |   |   |  |   |  (   |  |     | \__ \  (   |  |   |      |   |  |           /        |   |  ___ \   |   ___ \  
/// \____| \___/  _|  _|  _|  .__/  \__,_| _|    _| ____/ \___/  _|  _|     _|  _| \____|     _/        ____/ _/    _\ _| _/    _\ 
///                          _|                                                                                                    
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
 TFormula::SetMaxima(10000);   //---- for too long "draw" instructions ----
  
//  TProof::Open("");
 
//  TDRStyle();
//  LatinoStyle();
 LatinoStyle2();
 
 gStyle->SetPadTopMargin(0.11);
 gStyle->SetPadLeftMargin(0.17);
 gStyle->SetPadRightMargin(0.23);
 gStyle->cd(); 
 
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "   ___|                                       _)                           \\  |   ___|         /      __ \\     \\  __ __|   \\     " << std::endl;
 std::cout << "  |       _ \\   __ `__ \\   __ \\    _` |   __|  |   __|   _ \\   __ \\       |\\/ |  |            /       |   |   _ \\    |    _ \\    " << std::endl;
 std::cout << "  |      (   |  |   |   |  |   |  (   |  |     | \\__ \\  (   |  |   |      |   |  |           /        |   |  ___ \\   |   ___ \\   " << std::endl;
 std::cout << " \\____| \\___/  _|  _|  _|  .__/  \\__,_| _|    _| ____/ \\___/  _|  _|     _|  _| \\____|     _/        ____/ _/    _\\ _| _/    _\\  " << std::endl;
 std::cout << "                          _|                                                                                                     " << std::endl;
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
 
 
 ///==== Latinos colours ====
 
 EColor vColor[300];
 
// // //  = {
// // // //   (EColor) (kRed+1),
// // // //   (EColor) (kBlue+2),
// // // //   (EColor) (kRed+3),
// // //   (EColor) (kGray+1),
// // //   (EColor) (kAzure-2),
// // //   (EColor) (kAzure-9),
// // //   (EColor) (kYellow),
// // //   (EColor) (kGreen+2),
// // //   // 
// // //   // additional backgrounds
// // //   // or additional signals
// // //   //   
// // //   //   
// // //   //   
// // //   (EColor) (kGreen),
// // //   // ----> this can be DY>tautau
// // //   (EColor) (kMagenta),
// // //   (EColor) (kCyan-4),
// // //   (EColor) (kGreen),
// // //   (EColor) (kOrange-3),
// // //   (EColor) (kOrange+7),
// // //   kGreen,
// // //   //kMagenta,(EColor) (kMagenta+1),(EColor) (kMagenta+2),
// // //   kTeal,//(EColor) (kTeal+1),
// // //   kRed,
// // //   kGray,
// // //   kOrange,(EColor) (kOrange+1),
// // //   kBlue,//(EColor)(kBlue+1),(EColor) (kBlue+2),
// // //   (EColor) (kPink+2),//(EColor) (kPink+1),(EColor) (kPink+2),
// // //   kViolet,
// // //   kAzure,
// // // //   kWhite,
// // //   kTeal,
// // //   kYellow,
// // //   kGreen,
// // //   (EColor) (kTeal+1),
// // //   (EColor) (kOrange+2),
// // //   (EColor) (kGreen+2),
// // //   kGray,(EColor) (kGray+1),(EColor) (kViolet),(EColor) (kYellow),(EColor) (kGray)
// // //  };
 
 

 int nCol = 52+6+19+4+12+1+6+2+1+2;
 const std::string sampNames[] = { "Undefined",                            "DY",              "top"  ,               "WZ/ZZ"   ,                "WW",              "Wjets",             "ggH-110",              "qqH-110",                "ggH-115",                 "qqH-115",               "ggH-120",                "qqH-120",               "VH-120",              "ggH-130",               "qqH-130",               "VH-130",              "ggH-140",               "qqH-140",               "VH-140",                "ggH-150",                   "qqH-150",               "VH-150",                "ggH-160",                 "qqH-160",                  "VH-160",             "ggH-170",              "qqH-170",               "VH-170",              "ggH-180",               "qqH-180",               "VH-180",               "ggH-190",                "qqH-190",               "VH-190",                 "ggH-200",                  "qqH-200",              "ggH-250",               "qqH-250",               "ggH-300",                "qqH-300"
,              "ggH-350",               "qqH-350",                "ggH-400",                 "qqH-400",             "ggH-450",              "qqH-450",               "ggH-500",                "qqH-500",             "ggH-550",              "qqH-550",              "ggH-600",             "qqH-600"    ,             "ggH"       ,             "qqH"      ,              "VH"        ,             "VV"         ,             "VV-DY-Fake",             "W"         ,             "DYmumu"     ,             "DYee"       ,             "DYtautau"   ,             "DY#tau#tau"   ,          "DY#tau#tau-MC"   ,             "ZV"           ,             "ZJets"           ,             "WJets"           ,             "t#bar{t}"         ,             "ttbar"                ,             "Top"           ,             "WW"   ,             "VV"        ,             "HWW"       ,             "HWW-110"  ,             "HWW-110x10"  ,             "HWW-115"  ,             "HWW-115x10"  ,             "HWW-118"  ,             "HWW-118x10"  ,    
         "HWW-120" ,             "HWW-120x10"   ,             "HWW-122"  ,             "HWW-122x10"  ,             "HWW-124"  ,             "HWW-124x10"  ,             "HWW-126"  ,             "HWW-126x10"  ,             "HWW-128"  ,             "HWW-128x10"  ,             "HWW-130"  ,             "HWW-130x10"   ,             "HWW-135"  ,             "HWW-135x10"  ,             "HWW-140"  ,             "HWW-150"  ,             "HWW-160"  ,             "HWW-170"  ,             "HWW-180"  ,             "HWW-190"  ,             "HWW-200"  ,             "HWW-250"  ,             "HWW-300"  ,             "HWW-350"  ,             "HWW-400"  ,             "HWW-450"  ,             "HWW-500"  ,             "HWW-550"  ,             "HWW-600"      };
 EColor vColorMap[]            = { (EColor) ( kWhite),(EColor) (      kGreen+2),(EColor) (  kYellow ),(EColor) (   kAzure-2),(EColor) (    kAzure-9),(EColor) (   kGray+1),(EColor) (     kRed+1),(EColor) (      kRed+2),(EColor) (     kOrange+1),(EColor) (      kOrange+2),(EColor) (      kBlue+1),(EColor) (       kBlue+2),(EColor) (     kBlue+3),(EColor) (  kMagenta-7),(EColor) (   kMagenta+0),(EColor) (  kMagenta+2),(EColor) (     kBlue+1),(EColor) (      kBlue+2),(EColor) (     kBlue+3),(EColor) (     kMagenta+1),(EColor) (      kMagenta+2),(EColor) (  kMagenta+3),(EColor) (        kRed+1),(EColor) (         kRed+2),(EColor) (         kRed+3),(EColor) (     kRed+1),(EColor) (      kRed+2),(EColor)     (  kRed+3),(EColor) (     kTeal+1),(EColor) (      kTeal+2),(EColor) (     kTeal+2),(EColor) (     kBlack+1),(EColor) (      kBlack+2),(EColor) (    kBlack+3),(EColor) (     kMagenta+1),(EColor) (      kMagenta+2),(EColor) (     kGray+1),(EColor) (      kGray+2),(EColor) (     kGreen+1),(EColor) (      kGreen+2)
,(EColor) (     kBlue+1),(EColor) (      kBlue+2),(EColor) (     kYellow+1),(EColor) (      kYellow+2),(EColor) (     kRed+1),(EColor) (      kRed+2),(EColor) (     kBlack+1),(EColor) (      kBlack+2),(EColor) (     kRed+1),(EColor) (      kRed+2),(EColor) (     kTeal+1),(EColor) (      kTeal+2 ) ,(EColor) (      kRed+2 ) ,(EColor) (      kRed+4 ),(EColor) (      kRed+3 )  ,(EColor) (      kBlue+0 ) ,(EColor) (      kBlue+0 ),(EColor) (      kGray+2 ),(EColor) (      kGreen+2 ),(EColor) (      kGreen+4 ),(EColor) (      kGreen+6 ),(EColor) (        kMagenta ),(EColor) (        kRed     ),(EColor) (      kMagenta)   ,(EColor) (      kGreen+2)   ,(EColor) (      kGray+1 )   ,(EColor) (      kOrange)        ,(EColor) (      kOrange)            ,(EColor) (      kYellow)    ,(EColor) (      kAzure-9)  ,(EColor) (      kAzure-2),(EColor) (      kRed+1)  ,(EColor) (      kRed+1) ,(EColor) (      kRed+1)    ,(EColor) (     kBlue+1) ,(EColor) (     kBlue+1)    ,(EColor) (     kTeal+1) ,(EColor) (     kTeal+1)    ,(
EColor) (      kRed+2),(EColor) (      kRed+2)     ,(EColor) (  kMagenta+1) ,(EColor) (  kMagenta+1)    ,(EColor) (    kGreen+1) ,(EColor) (    kGreen+1)    ,(EColor) (  kMagenta+4) ,(EColor) (  kMagenta+4)    ,(EColor) (  kMagenta-3) ,(EColor) (  kMagenta-3)    ,(EColor) (     kBlue+2) ,(EColor) (     kBlue+2)     ,(EColor) (     kBlue-1) ,(EColor) (     kBlue-1)    ,(EColor) (      kRed+3) ,(EColor) (     kBlue+3) ,(EColor) (      kRed+4) ,(EColor) (     kBlue+4) ,(EColor) (      kRed+5) ,(EColor) (     kBlue+5) ,(EColor) (      kRed+6) ,(EColor) (     kBlue+6) ,(EColor) (      kRed+7) ,(EColor) (     kBlue+7) ,(EColor) (      kRed-1) ,(EColor) (     kBlue-1) ,(EColor) (      kRed-2) ,(EColor) (     kBlue-2) ,(EColor) (     kRed-3)      };
 
 
//  EColor vColorSig[300] = {
//   (EColor) (kRed+1),
//   (EColor) (kRed+3),
//   (EColor) (kBlue+2),
//   (EColor) (kBlue+4),
//   (EColor) (kGreen),
//   (EColor) (kGreen+2),
//   (EColor) (kOrange-3),
//   (EColor) (kOrange+7),
//   (EColor) (kViolet-3),
//   (EColor) (kViolet+7),
//   (EColor) (kTeal+1),
//   (EColor) (kTeal+3),
//   kGray,(EColor) (kGray+1),(EColor) (kViolet),(EColor) (kYellow),(EColor) (kGray)
//  };
 
 
 
 //Check if all nedeed arguments to parse are there                                                                                                                               
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }


 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");

 std::string treeNameSelections;
 try {
  treeNameSelections = gConfigParser -> readStringOption("Input::treeNameSelections");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
  treeNameSelections = "outTreeSelections";
 }
 
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
 
 
 double LUMI = gConfigParser -> readDoubleOption("Input::Lumi");
 
 double LumiSyst = gConfigParser -> readDoubleOption("Input::LumiSyst");
 
 double Discovery = gConfigParser -> readDoubleOption("Input::Discovery");
 //        # 1 = discovery, 0 = exclusion
 
 int Normalize = gConfigParser -> readIntOption("Input::Normalize");
 
 std::vector<std::vector<std::string> > SignalName;
 int numSignalSets = -1;
 
 try {
  numSignalSets = gConfigParser -> readIntOption("Input::SignalSets");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Input::SignalSets  " << numSignalSets  << std::endl;  
 
 if (numSignalSets == -1) {
  try {
   std::vector<std::string> tempSignalName;
   tempSignalName = gConfigParser -> readStringListOption("Input::SignalName");
   SignalName.push_back(tempSignalName);
   numSignalSets = 1;
  }
  catch (char const* exceptionString){
   std::cerr << " exception = " << exceptionString << std::endl;
  }
 }
 else {
  for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
    TString nameSig;
    nameSig = Form("Input::SignalName%d",iSignalSet);
    std::vector<std::string> tempSignalName = gConfigParser -> readStringListOption(nameSig.Data());
    SignalName.push_back(tempSignalName);
  }
 }
 
 
 
 ///==== PU reweight (begin) ====
 bool doWeightFromFile = false; 
 try {
  doWeightFromFile = gConfigParser -> readStringOption("PU::doWeightFromFile");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> PU::doWeightFromFile  " << doWeightFromFile  << std::endl;  

 std::vector<double> PUMC;
 std::vector<double> PUDATA;
 PUclass PU;
 double sumPUMC = 0;
 double sumPUDATA = 0;
 TH1F* hPUMC;
 TH1F* hPUDATA;
 TH1F* hPUWeight;
 
 std::string nameWeight = "weight"; 
 if (doWeightFromFile) {
  try {
   nameWeight = gConfigParser -> readStringOption("PU::nameWeight");
  }
  catch (char const* exceptionString){
   std::cerr << " exception = " << exceptionString << std::endl;
  }
  std::cout << ">>>>> PU::nameWeight  " << nameWeight  << std::endl;  
 }
   
 if (!doWeightFromFile) {
  
  PUMC   = gConfigParser -> readDoubleListOption("PU::PUMC");
  PUDATA = gConfigParser -> readDoubleListOption("PU::PUDATA");
  
  std::cout << " PUMC.size()   = " << PUMC.size()   << std::endl;
  std::cout << " PUDATA.size() = " << PUDATA.size() << std::endl;
  
  if (PUMC.size() != PUDATA.size()) {
   std::cerr << " ERROR " << std::endl;
   return 1;
  }
  
  for (int itVPU = 0; itVPU < PUMC.size(); itVPU++ ){
   sumPUMC += PUMC.at(itVPU);  
  }
  for (int itVPU = 0; itVPU < PUDATA.size(); itVPU++ ){
   sumPUDATA += PUDATA.at(itVPU);  
  } 
  
  for (int itVPU = 0; itVPU < PUMC.size(); itVPU++ ){
   PU.PUWeight.push_back(PUDATA.at(itVPU) / PUMC.at(itVPU) * sumPUMC / sumPUDATA);
  }
  
  PU.Write("autoWeight.cxx");
  gROOT->ProcessLine(".L autoWeight.cxx");
  
  ///==== save PU distribution in TH1F ====
  hPUMC   = new TH1F("hPUMC","hPUMC",PUMC.size(),0,PUMC.size());
  hPUDATA = new TH1F("hPUDATA","hPUDATA",PUDATA.size(),0,PUDATA.size());
  hPUWeight = new TH1F("hPUWeight","hPUWeight",PUDATA.size(),0,PUDATA.size());
  
  for (int itVPU = 0; itVPU < PUMC.size(); itVPU++ ){
   hPUMC     -> SetBinContent(itVPU+1,PUMC.at(itVPU) / sumPUMC);
   hPUDATA   -> SetBinContent(itVPU+1,PUDATA.at(itVPU) / sumPUDATA);
   hPUWeight -> SetBinContent(itVPU+1,PUDATA.at(itVPU) / PUMC.at(itVPU) * sumPUMC / sumPUDATA);
  }
  
 }
 
 ///==== PU reweight (end) ====
 
 
 ///==== pT Higgs reweight (begin) ====
 std::string nameptHWeight; 
 try {
  nameptHWeight = gConfigParser -> readStringOption("Input::nameptHWeight");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::nameptHWeight  " << nameptHWeight  << std::endl;  
 if (nameptHWeight != ""){
  TString toLoad;
//   toLoad = Form("cp %s ./",nameptHWeight.c_str());
//   gROOT->ProcessLine(toLoad.Data());
  toLoad = Form(".L %s+",nameptHWeight.c_str());
  gROOT->ProcessLine(toLoad.Data());
 }
 
 std::string nameptHWeightSample; 
 try {
  nameptHWeight = gConfigParser -> readStringOption("Input::nameptHWeightSample");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::nameptHWeightSample  " << nameptHWeightSample  << std::endl;  
 
 
 ///==== pT Higgs reweight (end) ====
 
 
 //  [iName]
 TTree *treeEffVect[23];
 TTree *treeJetLepVect[23];
 

 
  //  [iCut][iVar] 
 TString* infoString[347][7];
 TLatex *infoLatex[347][7]; 
 TCanvas* ccCanvas[347][7];
 TCanvas* ccCanvasNormalize[347][7];
 TCanvas* ccCanvasPull[347][7];
 TCanvas* ccCanvasVarAndPull[347][7];
 TCanvas* ccCanvasPullTrace[347][7];
 TH1F* histoSumMC[347][7];
 //  [iName][iCut][iVar]
 TH1F* histo[23][347][7];
 TH1F* histo_temp[23][347][7];
 TH1F* histo_temp_over_under[23][347][7];
 
 //  [iName][iCut]
 double numEvents[23][347];
 
 char *nameSample[300];
 char *nameHumanReadable[300];
 char* xsectionName[300];
 
 char NameNormalization[300][300];
 double Normalization[300];
 double xsection[300];
 char nameFileIn[300];
 sprintf(nameFileIn,"%s",fileSamples.c_str());

 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName); 
 
 ///==== list of variables to plot ====
 std::vector<double> vMin;
 std::vector<double> vMax;
 std::vector<int> vNBin;
 std::vector<std::string> vVarName;
 std::vector<std::string> vVarNameHR;
 std::string VarFile = gConfigParser -> readStringOption("Plot::VarFile");
 
 int numVar = ReadFileVar(VarFile,vMin,vMax,vNBin,vVarName,vVarNameHR);
 
 std::vector<double> vMinBasic;
 std::vector<double> vMaxBasic;
 std::vector<int> vNBinBasic;
 
 for (int iVar = 0; iVar < vNBin.size(); iVar++) {
  vNBinBasic.push_back(vNBin.at(iVar));
  vMinBasic.push_back(vMin.at(iVar));
  vMaxBasic.push_back(vMax.at(iVar));
 }

//  double XSection  = gConfigParser -> readDoubleOption("Plot::XSection");
 
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
 
 std::cout << " nCuts   = " << vCut.size() << std::endl;
 
 
 ///==== output file ====
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
 
 TString toRemove = Form("rm %s",OutFileName.c_str());
 gSystem->Exec(toRemove);  
 
 TFile outFile(OutFileName.c_str(),"RECREATE");
 outFile.cd();
 std::cout << ">>>>> Output::outFileName >> created " << std::endl;  
 
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

 
 ///==== underflow flag ==== 
 bool  underflowFlag = false; 
 try {
  underflowFlag = gConfigParser -> readBoolOption("Input::underflowFlag");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::underflowFlag  " << underflowFlag  << std::endl;  
 
 ///==== overflow flag ==== 
 bool  overflowFlag = false; 
 try {
  overflowFlag = gConfigParser -> readBoolOption("Input::overflowFlag");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::overflowFlag  " << overflowFlag  << std::endl;  
 
 
 
 ///==== program ====
 
 
 double start, end;
 start = clock();
 
 std::cout << " transform names ... " << std::endl;
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  xsection[iSample] = atof(xsectionName[iSample]);
 }
 
 std::cout << " read files ... " << std::endl;
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
  if (debug) std::cout << " nameFile = " << nameFile << std::endl;
  
  TFile* f = new TFile(nameFile, "READ");
  
  treeEffVect[iSample] = (TTree*) f->Get(treeNameSelections.c_str());
  
  if (treeEffVect[iSample] != 0) {
   char nameTreeEff[23];
   sprintf(nameTreeEff,"treeEff_%d",iSample); 
   treeEffVect[iSample]->SetName(nameTreeEff);      
  }
  
  treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
  char nameTreeJetLep[23];
  sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
  treeJetLepVect[iSample]->SetName(nameTreeJetLep);
 }
 
 ///===== create map for joint sample ====
 std::cout << " create map names ... " << std::endl;
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
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  std::cout << ">>> sample[" << iName << "] = " << reduced_name_samples.at(iName) << std::endl;
  bool flag_set = false;
  for (int iCol = 0; iCol < nCol; iCol++) {
   if (reduced_name_samples.at(iName) == sampNames[iCol]) {
    vColor[iName] = vColorMap[iCol];
    flag_set = true;
   }
  }
  if (!flag_set) {
   vColor[iName] = (EColor) (kBlack);
  }
 }
 
 
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
  
//   std::cout << " Xsection = " << XSection << " ~~~> " << xsection[iSample] << std::endl;
  XSection = xsection[iSample];
  
  if (numEntriesBefore != 0) {
   Normalization[iSample] = LUMI * XSection * preselection_efficiency / numEntriesBefore;
  }
  else {
   Normalization[iSample] = 0; 
  }  
  
  if (Latinos) {
   sprintf (NameNormalization[iSample], "(%s) *  %f / 1000. ", xsectionName[iSample], LUMI);
   Normalization[iSample] = XSection * LUMI / 1000.;   
//    std::cout << " NameNormalization[" << iSample << "] = " << NameNormalization[iSample] << " ---  Normalization[" << iSample << "] = " << Normalization[iSample] << std::endl;
  }
 }
 
 
 
 TLegend* legMC = new TLegend(0.8,0.64,0.98,0.103);
 TLegend* leg   = new TLegend(0.8,0.64,0.98,0.103);
 bool LegendBuilt = false;

 TString lumiName = Form("#splitline{L = %.1f pb^{-1}}{#splitline{#sqrt{s} = 7}{CMS preliminary}}", LUMI);
//  TString lumiName = Form("#sqrt{s}=7 TeV   L=%.1f pb^{-1}", LUMI);
 TLatex *latex = new TLatex(0.80, 0.90, lumiName); 
 latex->SetTextAlign(12);
 latex->SetNDC();
 latex->SetTextFont(42);
 latex->SetTextSize(0.03);
  
 ///==== get number in sample list that correspond to DATA ====
 int numDATA = -1;
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  if (reduced_name_samples.at(iName) == "DATA") {
   numDATA = iName;
  }
 }
 
 
 if (debug) std::cout << " Cut size = " << vCut.size() << " ~~ " << std::endl;
 std::cout.precision (2) ;
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  TString Cut = Form ("%s",vCut.at(iCut).c_str());
  if (debug) std::cout << " Cut[" << iCut << ":" << vCut.size() << "] = " << Cut.Data() << " ~~ " << std::endl;
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   if (debug) std::cout << " Var[" << iVar << ":" << vVarName.size() << "] = " << vVarName.at(iVar) << " ~~ " << std::endl;
   
   ///---- check underflow and overflow (begin) ----
   double delta = (vMaxBasic.at(iVar)-vMinBasic.at(iVar)) / vNBinBasic.at(iVar) ; 
   if (underflowFlag && !overflowFlag) {
    vNBin.at(iVar) = vNBinBasic.at(iVar) + 1;
    vMin.at(iVar)  = vMinBasic.at(iVar) - delta;
   }
   else if (!underflowFlag && overflowFlag) {
    vNBin.at(iVar) = vNBinBasic.at(iVar) + 1;
    vMax.at(iVar)  = vMaxBasic.at(iVar) + delta;
   }
   else if (underflowFlag && overflowFlag) {
    vNBin.at(iVar) = vNBinBasic.at(iVar) + 2;
    vMax.at(iVar)  = vMaxBasic.at(iVar) + delta;
    vMin.at(iVar)  = vMinBasic.at(iVar) - delta;
   }
   ///---- check underflow and overflow (end) ----
   
   
   ///==== initialize ====
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    reduced_name_samples_flag.at(iName) = -1;
   }
   
   ///==== cicle on samples ====
   for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
    if (debug) std::cout << " Sample[" << iSample << ":" << numberOfSamples << "] = " << nameSample[iSample] << " ~~ " << std::endl;
    TString name_histo_temp = Form("%s_%d_%d_%d_temp_over_under",nameSample[iSample], iCut, iVar,iSample);
    histo_temp_over_under[iSample][iCut][iVar] = new TH1F(name_histo_temp,name_histo_temp,vNBinBasic.at(iVar),vMinBasic.at(iVar), vMaxBasic.at(iVar));
    char toDraw[100000];
    sprintf(toDraw,"%s >> %s",vVarName.at(iVar).c_str(),name_histo_temp.Data());      

    histo_temp_over_under[iSample][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
    
    TString CutExtended;
    bool isData = false;
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     if (name_samples.at(iSample) == reduced_name_samples.at(iName)){
      if (iName == numDATA) {
       isData = true;
      }
     }
    }  
    if (!isData) {
     if (nameptHWeight != "" && name_samples.at(iSample) == nameptHWeightSample){
      if (!doWeightFromFile) {
      CutExtended = Form ("(%s) * autoWeight(numPUMC) * ptHWeight(ptH)",Cut.Data());    
      }
      else {
       CutExtended = Form ("(%s) * ptHWeight(ptH) * (%s)",Cut.Data(),nameWeight.c_str());    
      }
     }
     else {
      if (!doWeightFromFile) {
       CutExtended = Form ("(%s) * autoWeight(numPUMC)",Cut.Data());    
      }
      else {
       CutExtended = Form ("(%s) * (%s)",Cut.Data(),nameWeight.c_str());    
      }
     }
     //      CutExtended = Form ("(%s) * autoWeight(numPUMC) * ptHWeight(ptH)",Cut.Data());    
     CutExtended = Form ("(%s) * (%s)",CutExtended.Data(),NameNormalization[iSample] );    
    }
    else { //---- if LHC data
     CutExtended = Form ("(%s)",Cut.Data());    
    }
    treeJetLepVect[iSample]->Draw(toDraw,CutExtended,"");
    
    name_histo_temp = Form("%s_%d_%d_%d_temp",nameSample[iSample], iCut, iVar,iSample);
    histo_temp[iSample][iCut][iVar] = new TH1F(name_histo_temp,name_histo_temp,vNBin.at(iVar),vMin.at(iVar), vMax.at(iVar));
    
    histo_temp[iSample][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
    
    for (int iBin = 0; iBin < vNBinBasic.at(iVar); iBin++) {
     if (underflowFlag) {
      histo_temp[iSample][iCut][iVar] -> SetBinContent( iBin+2, histo_temp_over_under[iSample][iCut][iVar] -> GetBinContent(iBin+1) );
      histo_temp[iSample][iCut][iVar] -> SetBinError  ( iBin+2, histo_temp_over_under[iSample][iCut][iVar] -> GetBinError(iBin+1)   ); 
     }
     else {
      histo_temp[iSample][iCut][iVar] -> SetBinContent( iBin+1, histo_temp_over_under[iSample][iCut][iVar] -> GetBinContent(iBin+1) );
      histo_temp[iSample][iCut][iVar] -> SetBinError  ( iBin+1, histo_temp_over_under[iSample][iCut][iVar] -> GetBinError(iBin+1)   );      
     }
    }
    
    if (underflowFlag) {
     histo_temp[iSample][iCut][iVar] -> SetBinContent( 1, histo_temp_over_under[iSample][iCut][iVar] -> GetBinContent(0) );
     histo_temp[iSample][iCut][iVar] -> SetBinError  ( 1, histo_temp_over_under[iSample][iCut][iVar] -> GetBinError(0)   ); 
    }

    if (overflowFlag) {
     histo_temp[iSample][iCut][iVar] -> SetBinContent( vNBin.at(iVar), histo_temp_over_under[iSample][iCut][iVar] -> GetBinContent(vNBinBasic.at(iVar)+1) );
     histo_temp[iSample][iCut][iVar] -> SetBinError  ( vNBin.at(iVar), histo_temp_over_under[iSample][iCut][iVar] -> GetBinError(vNBinBasic.at(iVar)+1)   ); 
//      std::cout << "[" << iSample << "][" << iCut << "][" << iVar << "] = " << histo_temp_over_under[iSample][iCut][iVar] -> GetBinContent(vNBinBasic.at(iVar)+1) << std::endl;
    }

//     std::cout << " CutExtended = " << CutExtended.Data() << std::endl;
//     if (Normalization[iSample]>0) { 
// //      histo_temp[iSample][iCut][iVar] -> Sumw2();
//      histo_temp[iSample][iCut][iVar] -> Scale(Normalization[iSample]); 
//     }
    
//     std::cout << "Processing: " << blue << (((double) numberOfSamples - iSample)/numberOfSamples) << "% \r"  << normal << std::flush;
   } ///==== end cicle on samples ====
//    std::cout << "###";
  std::cout << "Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% "  << normal <<  " -- " <<  blue << (((double) iVar)/vVarName.size())*100. << "% \r"  << normal << std::flush;   
  } ///==== end cicle on variables to plot ====
  //   std::cout << "***";
 } ///==== end cicle on selections ====
 std::cout << std::endl; 
 
 std::cout << " create big histos " << std::endl;

 
 ///---- create "big" histos ----
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  if (debug) std::cout << " Cut[" << iCut << ":" << vCut.size() << "] = " << vCut.at(iCut) << " ~~ " << std::endl;
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ///---- initialize (begin) ----
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    reduced_name_samples_flag.at(iName) = -1;
   }
   ///---- initialize (end) ----
   for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){    
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     if (name_samples.at(iSample) == reduced_name_samples.at(iName) && iName == numDATA){
      if (reduced_name_samples_flag.at(iName) == -1){
       TString name_histoTot_temp = Form("%s_%d_%d_Tot_temp",reduced_name_samples.at(iName).c_str(),iCut, iVar);
       TString name_HR_histoTot_temp = Form("%s %s",vVarNameHR.at(iVar).c_str(), vCutHR.at(iCut).c_str());
       //        TString name_HR_histoTot_temp = Form("%s %d %s",vVarNameHR.at(iVar).c_str(), iCut, reduced_name_samples.at(iName).c_str());
       histo[iName][iCut][iVar] = new TH1F(name_histoTot_temp,name_HR_histoTot_temp,vNBin.at(iVar),vMin.at(iVar), vMax.at(iVar));
       histo[iName][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
       reduced_name_samples_flag.at(iName) = 1;
      }
      histo[iName][iCut][iVar] -> Add(histo_temp[iSample][iCut][iVar]);
     }
    }
   }
  }
 }
 
 
 if (Normalize == 1) { //---- normalize to Data ----
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ///---- initialize (begin) ----
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    reduced_name_samples_flag.at(iName) = -1;
   }
   ///---- initialize (end) ----
   double data_int = 0;
   if (numDATA != -1) data_int = histo[numDATA][iCut][iVar] -> Integral();
   double mc_int = 0;
   
   for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     if (name_samples.at(iSample) == reduced_name_samples.at(iName) && iName != numDATA){
      mc_int += histo_temp[iSample][iCut][iVar] -> Integral();
     }
    }
   }
   
   std::cout << " data_int / mc_int = " << data_int / mc_int << std::endl;
   for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){ 
    histo_temp[iSample][iCut][iVar] -> Scale (data_int / mc_int);
    
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     if (name_samples.at(iSample) == reduced_name_samples.at(iName)  && iName != numDATA){
      if (reduced_name_samples_flag.at(iName) == -1){
       TString name_histoTot_temp = Form("%s_%d_%d_Tot_temp",reduced_name_samples.at(iName).c_str(),iCut, iVar);
       TString name_HR_histoTot_temp = Form("%s %s",vVarNameHR.at(iVar).c_str(), vCutHR.at(iCut).c_str());
       //        TString name_HR_histoTot_temp = Form("%s %d %s",vVarNameHR.at(iVar).c_str(), iCut, reduced_name_samples.at(iName).c_str());
       histo[iName][iCut][iVar] = new TH1F(name_histoTot_temp,name_HR_histoTot_temp,vNBin.at(iVar),vMin.at(iVar), vMax.at(iVar));
       histo[iName][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
       reduced_name_samples_flag.at(iName) = 1;
      }
      histo[iName][iCut][iVar] -> Add(histo_temp[iSample][iCut][iVar]);
     }
    }
   }
  }
 }
 
 }
 else { //---- normalize to Lumi
  
  for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
   if (debug) std::cout << " Cut[" << iCut << ":" << vCut.size() << "] = " << vCut.at(iCut) << " ~~ " << std::endl;
   for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
    ///---- initialize (begin) ----
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     reduced_name_samples_flag.at(iName) = -1;
    }
    ///---- initialize (end) ----
    for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
     
     for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
      if (name_samples.at(iSample) == reduced_name_samples.at(iName) && iName != numDATA ){
       if (reduced_name_samples_flag.at(iName) == -1){
	TString name_histoTot_temp = Form("%s_%d_%d_Tot_temp",reduced_name_samples.at(iName).c_str(),iCut, iVar);
	TString name_HR_histoTot_temp = Form("%s %s",vVarNameHR.at(iVar).c_str(), vCutHR.at(iCut).c_str());
	//        TString name_HR_histoTot_temp = Form("%s %d %s",vVarNameHR.at(iVar).c_str(), iCut, reduced_name_samples.at(iName).c_str());
	histo[iName][iCut][iVar] = new TH1F(name_histoTot_temp,name_HR_histoTot_temp,vNBin.at(iVar),vMin.at(iVar), vMax.at(iVar));
	histo[iName][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
	reduced_name_samples_flag.at(iName) = 1;
       }
       histo[iName][iCut][iVar] -> Add(histo_temp[iSample][iCut][iVar]);
      }
     }
    }
   }
  }
 }
 
 std::cout << " last plot " << std::endl;
 
//  [iName]
 TH1F* hTrend[23];
 THStack* hsTrend;
 //   [iSignalSet]
 THStack* hsSignalTrend[30];
 //  [iCut]
//  TPie* hTrendPie[347];
 
 
 //  [iCut][iVar][iSignalSet]
 THStack* hsSignal[347][23][30];
 THStack* hs[347][23];
 TH1F* hPull[347][23];
 TH1F* hPullTrace[347][23];

 TGraphErrors* grPull[347][23];
 TGraphErrors* grPullMC[347][23];
 
 
 std::cout << std::endl;
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  if (debug) std::cout << " last plot >> iCut = " << iCut << " :: "  << vCut.size() << std::endl;
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   if (debug) std::cout << " last plot >> iVar = " << iVar << " :: " << vVarName.size() << std::endl;
   TString nameStack = Form("%d_%d_stack",iCut,iVar);
   hs[iCut][iVar] = new THStack(nameStack,nameStack);
   
   for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
    nameStack = Form("%d_%d_%d_stack_signal",iCut,iVar,iSignalSet);
    hsSignal[iCut][iVar][iSignalSet] = new THStack(nameStack,nameStack);
   }
   
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    if (debug) std::cout << " last plot >> iName = " << iName << " :: " << reduced_name_samples.size() << std::endl;
    
    bool isSig = false;
    int whichSig = -1;
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     if (debug) std::cout << " iSignalSet = " << iSignalSet << " :: " << numSignalSets << std::endl;
     
     for (std::vector<std::string>::const_iterator itSig = SignalName.at(iSignalSet).begin(); itSig != SignalName.at(iSignalSet).end(); itSig++){
      if (reduced_name_samples.at(iName) == *itSig) {
       whichSig = iSignalSet;
       isSig = true;
      }
     }
    }
    
    histo[iName][iCut][iVar]->GetXaxis()->SetTitle(vVarNameHR.at(iVar).c_str());
    histo[iName][iCut][iVar]->SetMarkerColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetLineColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetFillColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetLineWidth(2);
    histo[iName][iCut][iVar]->SetFillStyle(3001);
    
    if ((!isSig || Discovery==0) && reduced_name_samples.at(iName) != "DATA") {
     hs[iCut][iVar]->Add(histo[iName][iCut][iVar]);
    }
    else {
     if ((!isSig || Discovery==0)) {
      histo[iName][iCut][iVar]->SetMarkerStyle(20);
      histo[iName][iCut][iVar]->SetMarkerSize(1);
      histo[iName][iCut][iVar]->SetMarkerColor(kBlack);
      histo[iName][iCut][iVar]->SetLineColor(kBlack);
      histo[iName][iCut][iVar]->SetFillColor(kBlack);
      histo[iName][iCut][iVar]->SetLineWidth(2);
      histo[iName][iCut][iVar]->SetFillStyle(3001);  
     }
     else {
      histo[iName][iCut][iVar]->SetMarkerStyle(7);
      histo[iName][iCut][iVar]->SetMarkerSize(0.2);
      histo[iName][iCut][iVar]->SetLineWidth(4);
//       histo[iName][iCut][iVar]->SetFillStyle(3001);
      histo[iName][iCut][iVar]->SetFillStyle(0); 
      hsSignal[iCut][iVar][whichSig]->Add(histo[iName][iCut][iVar]);
     }
    }
   }
   ///==== histo sum MC ====    
   ///==== Add systrematic error ====
   AddError(hs[iCut][iVar],LumiSyst);
   histoSumMC[iCut][iVar] = ((TH1F*)(hs[iCut][iVar]->GetStack()->Last()));
   
   //    //---- signal stack
   //    if (Discovery) AddError(hsSignal[iCut][iVar],0);
   
   if (debug) std::cout << " last plot >> pull plot" << std::endl;
   
   ///==== histo with pull plot ====
   if (numDATA != -1) {
    hPull[iCut][iVar] = PullPlot(histo[numDATA][iCut][iVar], histoSumMC[iCut][iVar]);
    hPullTrace[iCut][iVar] = GetTrendInfo(hPull[iCut][iVar],-2.0,2.0);
   }
   
   std::pair<TGraphErrors*, TGraphErrors*> tempPairGrPull;
   if (numDATA != -1) {
    tempPairGrPull = grPullPlot(histo[numDATA][iCut][iVar], histoSumMC[iCut][iVar]);
    grPull  [iCut][iVar] = tempPairGrPull.first;
    grPullMC[iCut][iVar] = tempPairGrPull.second;   
   }
   
   if (numDATA != -1) std::cout << " MC / DATA[" << iCut << "][" << iVar << "] = "<< histoSumMC[iCut][iVar]->Integral() << " / " << histo[numDATA][iCut][iVar]->Integral() << " = " << (histo[numDATA][iCut][iVar]->Integral() ? histoSumMC[iCut][iVar]->Integral()/ histo[numDATA][iCut][iVar]->Integral() : 0) << std::endl;
   
   ///==== legend ====
   if (!LegendBuilt){
    
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     bool isSig = false;
     for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
      for (std::vector<std::string>::const_iterator itSig = SignalName.at(iSignalSet).begin(); itSig != SignalName.at(iSignalSet).end(); itSig++){
       if (reduced_name_samples.at(iName) == *itSig) {
	isSig = true;
       }
      }
     }
     if (!isSig && reduced_name_samples.at(iName) != "DATA") {
      leg->AddEntry(histo[iName][iCut][iVar],reduced_name_samples.at(iName).c_str(),"pf");    
      legMC->AddEntry(histo[iName][iCut][iVar],reduced_name_samples.at(iName).c_str(),"pf");    
     }
    }
    
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     bool isSig = false;
     for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
      for (std::vector<std::string>::const_iterator itSig = SignalName.at(iSignalSet).begin(); itSig != SignalName.at(iSignalSet).end(); itSig++){
       if (reduced_name_samples.at(iName) == *itSig) {
	isSig = true;
       }
      }
     }
     if (isSig) {
      leg->AddEntry(histo[iName][iCut][iVar],reduced_name_samples.at(iName).c_str(),"pf");    
      legMC->AddEntry(histo[iName][iCut][iVar],reduced_name_samples.at(iName).c_str(),"pf");    
     }
    }
    
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     if (reduced_name_samples.at(iName) == "DATA") {
      leg->AddEntry(histo[iName][iCut][iVar],reduced_name_samples.at(iName).c_str(),"pf");    
     }
    }
    leg  -> SetFillColor(kWhite);
    legMC-> SetFillColor(kWhite);
    LegendBuilt = true;
   }
  }
 }
 std::cout << std::endl << std::endl;
 
 ///==== calculate number of events after each step of the analysis ====
 //  [iName][iCut]
 hsTrend = new THStack("Trend","Trend");
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  TString nameSignalTrend = Form("TrendSignal_%d",iSignalSet);
  hsSignalTrend[iSignalSet] = new THStack(nameSignalTrend,nameSignalTrend);
 }
 
//  for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
//   TString nameTHTrendPie = Form("%d_Trend_Pie",iCut);
//   hTrendPie[iCut] = new TPie (nameTHTrendPie,nameTHTrendPie,reduced_name_samples.size());
//  }
 
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  TString nameTHTrend = Form("%s_Trend",reduced_name_samples.at(iName).c_str());
  hTrend[iName] = new TH1F (nameTHTrend,nameTHTrend,vCut.size()+1,0,vCut.size()+1);
  hTrend[iName]->GetXaxis()->SetTitle("Selections");

  if (iName == numDATA) {
   hTrend[iName]->SetMarkerStyle(20);
   hTrend[iName]->SetMarkerSize(1);
   hTrend[iName]->SetMarkerColor(kBlack);
   hTrend[iName]->SetLineColor(kBlack);
   hTrend[iName]->SetFillColor(kBlack);
   hTrend[iName]->SetLineWidth(2);
   hTrend[iName]->SetFillStyle(3001);  
  }
  else {
   hTrend[iName]->SetMarkerColor(vColor[iName]);
   hTrend[iName]->SetLineColor(vColor[iName]);
   hTrend[iName]->SetFillColor(vColor[iName]);
   hTrend[iName]->SetLineWidth(2);
   hTrend[iName]->SetFillStyle(3001);
  }
  for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
   double error = 0;
   numEvents[iName][iCut] = histo[iName][iCut][0]->IntegralAndError(0,histo[iName][iCut][0]->GetNbinsX()+1,error); //--- iVar = 0, it should be the same whatever var you use
//    numEvents[iName][iCut] = histo[iName][iCut][0]->Integral(); //--- iVar = 0, it should be the same whatever var you use
   hTrend[iName]->SetBinContent(iCut+1,numEvents[iName][iCut]);
   hTrend[iName]->SetBinError(iCut+1,error);
   TString nameBin = Form("%d",iCut);
   
   if (vCutHR.size() == 0) {
    hTrend[iName]->GetXaxis()->SetBinLabel(iCut+1,nameBin);
   }
   else {
    hTrend[iName]->GetXaxis()->SetBinLabel(iCut+1,vCutHR.at(iCut).c_str());
   }
   
   
   
//     IntegralAndError
//     Double_t IntegralAndError(Int_t binx1, Int_t binx2, Double_t& err, Option_t* option = "") const
   std::cout << ">>>  numEvents[" << iName << "," << reduced_name_samples.at(iName) << "][" << iCut << "] = " << numEvents[iName][iCut] << " , " << histo[iName][iCut][0]->GetEntries() << " , " << histo[iName][iCut][0]->GetEffectiveEntries() << std::endl;
   
//    if (iName != numDATA) {
//     hTrendPie[iCut]->SetTextSize(0.04);
//     hTrendPie[iCut]->SetTextFont(12);
//     hTrendPie[iCut]->SetEntryFillColor(iName,vColor[iName]);
//     hTrendPie[iCut]->SetEntryFillStyle(iName,3001);
//     hTrendPie[iCut]->SetEntryLabel(iName, reduced_name_samples.at(iName).c_str());
//     hTrendPie[iCut]->SetEntryLineColor(iName, vColor[iName]);
//     hTrendPie[iCut]->SetEntryLineStyle(iName, 2);
//     hTrendPie[iCut]->SetEntryLineWidth(iName, 2);
//     hTrendPie[iCut]->SetEntryRadiusOffset(iName, 0.01);
//     hTrendPie[iCut]->SetEntryVal(iName,numEvents[iName][iCut]);
//    }
//    else {
//     hTrendPie[iCut]->SetEntryLabel(iName, "");
//    }
  }
  
  bool isSig = false;
  int whichSig = -1;
  for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
   for (std::vector<std::string>::const_iterator itSig = SignalName.at(iSignalSet).begin(); itSig != SignalName.at(iSignalSet).end(); itSig++){
    if (reduced_name_samples.at(iName) == *itSig) {
     whichSig = iSignalSet;
     isSig = true;
    }
   }
  }
  if ((!isSig || Discovery==0) && reduced_name_samples.at(iName) != "DATA") {
   hsTrend->Add(hTrend[iName]);
  }
  else if (isSig) {
   hsSignalTrend[whichSig]->Add(hTrend[iName]);
  }   
//   if (iName != numDATA) {
//    hsTrend->Add(hTrend[iName]);
//   }
 }
 AddError(hsTrend,LumiSyst);
//  AddError(hsSignalTrend,0); 
 
 TH1F* hTrendSumMC       = ((TH1F*)(hsTrend->GetStack()->Last()));
//  TH1F* hTrendSignalSumMC;
//  if (Discovery) hTrendSignalSumMC = ((TH1F*)(hsSignalTrend->GetStack()->Last()));
 
 ///==== hTrend with pull plot ====
 TH1F* hPullTrendSumMC;
 if (numDATA != -1) hPullTrendSumMC = PullPlot(hTrend[numDATA], hTrendSumMC);
 TH1F* hPullTrendTraceSumMC;
 if (numDATA != -1) hPullTrendTraceSumMC = GetTrendInfo(hPullTrendSumMC,-2.0,2.0);
 
 std::pair<TGraphErrors*, TGraphErrors*> tempPairGrPullTrend;
 TGraphErrors* grPullTrendSumMC;
 TGraphErrors* grPullTrendSumMCMC;
 if (numDATA != -1) {
  tempPairGrPullTrend = grPullPlot(hTrend[numDATA], hTrendSumMC);
  grPullTrendSumMC   = tempPairGrPullTrend.first;
  grPullTrendSumMCMC = tempPairGrPullTrend.second;
 }
 
 
 ///==== calculate agreement data-MC: Kolmogorov-Smirnov test ==== 
 ///==== cicle on selections ====
 if (numDATA != -1) {
  for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
   ///==== cicle on variables to plot ====
   for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
    double KS = -1;
    double Chi2 = -1;
//     if (histo[numDATA][iCut][iVar]->GetEntries() != 0 && histoSumMC[iCut][iVar]->GetEntries() != 0) {
//      KS = histo[numDATA][iCut][iVar]->KolmogorovTest(histoSumMC[iCut][iVar],"M");
//      Chi2 = histo[numDATA][iCut][iVar]->Chi2Test(histoSumMC[iCut][iVar],"UW");
//     }
//     std::cout << " KS[" << iCut << "][" << iVar << "] = " << KS << std::endl;
    infoString[iCut][iVar] = new TString("");
//     infoString[iCut][iVar] = new TString(Form("#splitline{KS prob = %.4f}{#chi^{2} prob = %.4f}",KS,Chi2));
    infoLatex[iCut][iVar] = new TLatex(0.80, 0.10, *(infoString[iCut][iVar])); 
    infoLatex[iCut][iVar]->SetTextAlign(12);
    infoLatex[iCut][iVar]->SetNDC();
    infoLatex[iCut][iVar]->SetTextFont(42);
    infoLatex[iCut][iVar]->SetTextSize(0.03);
   }
  }
 }
 
 LumiSyst = 0; ///---- bug fix
 
 std::cout << std::endl;
 std::cout << " Plot ... (wait) " << std::endl;
//  TCanvas* cTrendPie[347];
//  TCanvas* cTrendPieAll = new TCanvas("cTrendPieAll","cTrendPieAll",400 * vCut.size(),400);
//  cTrendPieAll -> Divide (vCut.size());
 TCanvas* cTrend = new TCanvas("cTrend","cTrend",400,400);
 TCanvas* cTrendPull = new TCanvas("cTrendPull","cTrendPull",500,670); // 800);
 
 TCanvas* cCompareCutPull[347];
 TCanvas* cCompareVarPull[23];
 
 TCanvas* cCompareCut[347];
 TCanvas* cCompareVar[23];
 
 std::cout << " Plot ... 2 ... (wait) " << std::endl;
 
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  TString titleCanvas = Form("%d_Cut_Canvas %s",iCut,vCutHR.at(iCut).c_str());
  TString nameCanvas = Form("%d_Cut_Canvas",iCut);
  cCompareCut[iCut] = new TCanvas(nameCanvas,titleCanvas,400 * vVarName.size(),400);
  cCompareCut[iCut] -> Divide (vVarName.size(),1);
  TString nameCanvasPull = Form("%d_Cut_Canvas_Pull",iCut);
  cCompareCutPull[iCut] = new TCanvas(nameCanvasPull,titleCanvas,500 * vVarName.size(),670); //400*3);
//   cCompareCutPull[iCut] -> Divide (vVarName.size(),3);
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   //    void DivideCanvas(TPad* cPad, int numberCanvas, double x1, double y1, double x2, double y2 = 0, double yb = 0, double yt = 0, double xl = 0, double xr = 0); 
   DivideCanvas((TPad*) cCompareCutPull[iCut]->cd(), iVar+1,                 iVar * (1. / vVarName.size()) , 0.40, (iVar+1) * (1. / vVarName.size()), 1.00, -99, -99, -99, 0.23);
   DivideCanvas((TPad*) cCompareCutPull[iCut]->cd(), vVarName.size()  +iVar+1, iVar * (1. / vVarName.size()) , 0.20, (iVar+1) * (1. / vVarName.size()), 0.39, -99, -99, -99, 0.23);
   DivideCanvas((TPad*) cCompareCutPull[iCut]->cd(), vVarName.size()*2+iVar+1, iVar * (1. / vVarName.size()) , 0.02, (iVar+1) * (1. / vVarName.size()), 0.15, -99, -99, -99, 0.23);
  }
  
 }
 
 std::cout << " Plot ... 3 ... (wait) " << std::endl;
 
 for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){ ///==== cicle on variables to plot ====
   TString nameCanvas = Form("%d_Var_Canvas",iVar);
   cCompareVar[iVar] = new TCanvas(nameCanvas,nameCanvas,400,400 * vCut.size());
   cCompareVar[iVar] -> Divide (1,vCut.size());
   TString nameCanvasPull = Form("%d_Var_Canvas_Pull",iVar);
   cCompareVarPull[iVar] = new TCanvas(nameCanvasPull,nameCanvasPull,400*3,400 * vCut.size());
   cCompareVarPull[iVar] -> Divide (3,vCut.size());
 }
 
 
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   TString titleCanvas = Form("%d_%d_Canvas %s %s",iCut,iVar,vCutHR.at(iCut).c_str(),vVarNameHR.at(iVar).c_str());
   TString nameCanvas = Form("%d_%d_Canvas",iCut,iVar);
   ccCanvas[iCut][iVar] = new TCanvas(nameCanvas,titleCanvas,400,400);
   TString nameCanvasPull = Form("%d_%d_CanvasPull",iCut,iVar);
   ccCanvasPull[iCut][iVar] = new TCanvas(nameCanvasPull,titleCanvas,400,400);
   TString nameCanvasPullTrace = Form("%d_%d_CanvasPullTrace",iCut,iVar);
   ccCanvasPullTrace[iCut][iVar] = new TCanvas(nameCanvasPullTrace,nameCanvasPullTrace,400,400);
   nameCanvas = Form("%d_%d_Norm_Canvas",iCut,iVar);
   ccCanvasNormalize[iCut][iVar] = new TCanvas(nameCanvas,titleCanvas,400,400);
   nameCanvas = Form("%d_%d_VarPull_Canvas",iCut,iVar);
   ccCanvasVarAndPull[iCut][iVar] = new TCanvas(nameCanvas,titleCanvas,650,600);
// //    void DivideCanvas(TPad* cPad, int numberCanvas, double x1, double y1, double x2, double y2 = 0, double yb = 0, double yt = 0, double xl = 0, double xr = 0); 
   DivideCanvas((TPad*) ccCanvasVarAndPull[iCut][iVar]->cd(), 1, 0.00, 0.30, 0.77, 1.00, -99, -99, -99, 0.10);
   DivideCanvas((TPad*) ccCanvasVarAndPull[iCut][iVar]->cd(), 2, 0.00, 0.02, 0.77, 0.25, -99, -99, -99, 0.10);
//    ccCanvasVarAndPull[iCut][iVar]->Divide(1,2,0.01,0);
  }
 } 
  
  std::cout << " Plot ... 4 ... (wait) " << std::endl;

 ///==== draw trend vs cut (begin)
 cTrend->cd();
 DrawStack(hsTrend,1,LumiSyst);
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
//   std::cout << std::endl << " iSignalSet = " << iSignalSet << " --> pointer = " << hsSignalTrend[iSignalSet] << std::endl;
  if (Discovery) DrawStack(hsSignalTrend[iSignalSet],0,0,"EsameP");
 } 
 
 std::cout << " Plot ... 5 ... (wait) " << std::endl;
 
 if (numDATA != -1) hTrend[numDATA] -> Draw("EsameP");
//  for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
//   bool isSig = false;
//   for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
//    if (reduced_name_samples.at(iName) == *itSig) isSig = true;
//   }
//   if (isSig) {
//    hTrend[iName]->Draw("EsameP");
//   }
//  } 

 gPad->SetLogy();
 gPad->SetGrid();
 leg->Draw();
 latex->Draw();
  
//  cTrendPull->Divide(1,3);
 DivideCanvas((TPad*) cTrendPull->cd(), 1, 0.0, 0.40, 0.77, 1.00, 0.30, -99, -99, 0.10);
 DivideCanvas((TPad*) cTrendPull->cd(), 2, 0.0, 0.20, 0.77, 0.39, 0.30, -99, -99, 0.10);
 DivideCanvas((TPad*) cTrendPull->cd(), 3, 0.0, 0.02, 0.77, 0.15, 0.30, -99, -99, 0.10);
 
 cTrendPull->cd(1);
 DrawStack(hsTrend,1,LumiSyst);
 
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) { 
  if (Discovery) DrawStack(hsSignalTrend[iSignalSet],0,0,"EsameP");
 }
 if (numDATA != -1) hTrend[numDATA] -> Draw("EsameP"); 
//  for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
//   bool isSig = false;
//   for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
//    if (reduced_name_samples.at(iName) == *itSig) isSig = true;
//   }
//   if (isSig) {
//    hTrend[iName]->Draw("EsameP");
//   }
//  }
 gPad->SetLogy();
 gPad->SetGrid();
 cTrendPull->cd();
 leg->Draw();
 latex->Draw();
 cTrendPull->cd(2);
//  hPullTrendSumMC->Draw("EP");
 if (grPullTrendSumMCMC) grPullTrendSumMCMC -> Draw("A2");     //    grPullTrendSumMCMC -> Draw("AE3");
 if (grPullTrendSumMC)   grPullTrendSumMC   -> Draw("PsameE");  
 
 
 gPad->SetGrid();
 cTrendPull->cd(3);
 gPad->SetGrid();
 if (hPullTrendTraceSumMC) hPullTrendTraceSumMC->Draw();
 gPad->SetGrid();
  
 std::cout << " Plot ... 6 ... (wait) " << std::endl;
 
//  for (unsigned int iCut = 0; iCut<vCut.size(); iCut++) {
//   TString nameCanvas = Form("%d_Canvas_Trend",iCut);
//   cTrendPie[iCut] = new TCanvas(nameCanvas,nameCanvas,400,400);
//   cTrendPie[iCut]->cd();
//   hTrendPie[iCut] -> Draw("3d t nol");
//   hTrendPie[iCut]->SetX(.45);
//   hTrendPie[iCut]->SetRadius(.22);
//   leg->Draw();
//   latex->Draw();
//   
//   cTrendPieAll->cd(iCut+1);
//   hTrendPie[iCut] -> Draw("3d t nol");
//   hTrendPie[iCut]->SetX(.45);
//   hTrendPie[iCut]->SetRadius(.22);
//   leg->Draw();
//   latex->Draw();
//  }
 ///==== draw trend vs cut (end)
 
 std::cout << " Plot ... 7 ... (wait) " << std::endl;
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
      
   ///==== draw in canvas ====
   cCompareCut[iCut] -> cd(iVar+1);
   DrawStack(hs[iCut][iVar],1,LumiSyst);
   gPad->SetLogy();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();
   
   if (numDATA != -1 && infoLatex[iCut][iVar]) infoLatex[iCut][iVar]->Draw();
   
   cCompareVar[iVar] -> cd(iCut+1);
   DrawStack(hs[iCut][iVar],1,LumiSyst);
   gPad->SetLogy();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();
   if (numDATA != -1 && infoLatex[iCut][iVar]) infoLatex[iCut][iVar]->Draw();
      
   cCompareCutPull[iCut] -> cd(iVar+1);
   DrawStack(hs[iCut][iVar],1,LumiSyst);
   gPad->SetLogy();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();
   if (numDATA != -1 && infoLatex[iCut][iVar]) infoLatex[iCut][iVar]->Draw();
   
   cCompareVarPull[iVar] -> cd(iCut*3+1);
   DrawStack(hs[iCut][iVar],1,LumiSyst);
   gPad->SetLogy();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();
   if (numDATA != -1 && infoLatex[iCut][iVar]) infoLatex[iCut][iVar]->Draw();
   
   cCompareCutPull[iCut] -> cd(iVar+1+vVarName.size());
//    hPull[iCut][iVar]->Draw("EP");
   if (grPullMC[iCut][iVar]) grPullMC[iCut][iVar] -> Draw("A2"); // if (grPullMC[iCut][iVar]) grPullMC[iCut][iVar] -> Draw("A2");   //    grPullMC[iCut][iVar] -> Draw("AE3");
   if (grPull  [iCut][iVar]) grPull  [iCut][iVar] -> Draw("PsameE");      
   gPad->SetGrid();
//    gPad->SetLeftMargin(0.17);
//    gPad->SetRightMargin(0.07);

   cCompareCutPull[iCut] -> cd(iVar+1+vVarName.size()*2);
   if (hPullTrace[iCut][iVar]) hPullTrace[iCut][iVar]->Draw();
   gPad->SetGrid();
   
   cCompareVarPull[iVar] -> cd(iCut*3+2);
//    hPull[iCut][iVar]->Draw("EP");
   if (grPullMC[iCut][iVar]) grPullMC[iCut][iVar] -> Draw("A2"); // if (grPullMC[iCut][iVar]) grPullMC[iCut][iVar] -> Draw("A2");   //    grPullMC[iCut][iVar] -> Draw("AE3");
   if (grPull  [iCut][iVar]) grPull  [iCut][iVar] -> Draw("PsameE");      
   gPad->SetGrid();
//    gPad->SetLeftMargin(0.17);
//    gPad->SetRightMargin(0.07);
   
   cCompareVarPull[iVar] -> cd(iCut*3+3);
   if (hPullTrace[iCut][iVar]) hPullTrace[iCut][iVar]->Draw("hbar2");
//    gPad->SetRightMargin(0.07);
   gPad->SetGrid();
   
   ccCanvas[iCut][iVar]-> cd();
   DrawStack(hs[iCut][iVar],1,LumiSyst);
   gPad->SetLogy();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();
   if (numDATA != -1 && infoLatex[iCut][iVar]) infoLatex[iCut][iVar]->Draw();
   
   ccCanvasVarAndPull[iCut][iVar]-> cd(1);
   DrawStack(hs[iCut][iVar],1,LumiSyst);
   gPad->SetLogy();
   gPad->SetGrid();
   gPad->SetTickx(2);
   ccCanvasVarAndPull[iCut][iVar]-> cd();
   leg->Draw();
   latex->Draw();
   if (numDATA != -1 && infoLatex[iCut][iVar]) infoLatex[iCut][iVar]->Draw();
   
   
   ccCanvasNormalize[iCut][iVar]-> cd();
   DrawStackNormalized(hs[iCut][iVar]);
   gPad->SetLogy();
   gPad->SetGrid();
   legMC->Draw();
   latex->Draw();
//    infoLatex[iCut][iVar]->Draw();
      
   ccCanvasPull[iCut][iVar]-> cd();
//    hPull[iCut][iVar]->Draw("EP");
   if (grPullMC[iCut][iVar]) grPullMC[iCut][iVar] -> Draw("A2"); // if (grPullMC[iCut][iVar]) grPullMC[iCut][iVar] -> Draw("A2");   //    grPullMC[iCut][iVar] -> Draw("AE3");
   if (grPull  [iCut][iVar]) grPull  [iCut][iVar] -> Draw("PsameE");      
   gPad->SetGrid();
//    gPad->SetLeftMargin(0.17);
//    gPad->SetRightMargin(0.07);
   
   ccCanvasVarAndPull[iCut][iVar]->cd(2);

   if (grPullMC[iCut][iVar]) {
    grPullMC[iCut][iVar] -> Draw("A2");   //    grPullMC[iCut][iVar] -> Draw("AE3");
    grPullMC[iCut][iVar] -> GetXaxis() -> SetRangeUser(vMin.at(iVar),vMax.at(iVar));
//     grPullMC[iCut][iVar] -> GetXaxis() -> SetLabelFont  (   42);
//     grPullMC[iCut][iVar] -> GetXaxis() -> SetLabelOffset(0.010);
//     grPullMC[iCut][iVar] -> GetXaxis() -> SetLabelSize  (0.100);
//     grPullMC[iCut][iVar] -> GetXaxis() -> SetTitleSize  (0.100);
    grPullMC[iCut][iVar] -> GetYaxis() -> CenterTitle();
   }
   if (grPull  [iCut][iVar]) {
    grPull  [iCut][iVar] -> Draw("PsameE");      
    grPull  [iCut][iVar] -> GetXaxis() -> SetRangeUser(vMin.at(iVar),vMax.at(iVar));
//     grPull  [iCut][iVar] -> GetXaxis() -> SetLabelFont  (   42);
//     grPull  [iCut][iVar] -> GetXaxis() -> SetLabelOffset(0.010);
//     grPull  [iCut][iVar] -> GetXaxis() -> SetLabelSize  (0.100);
//     grPull  [iCut][iVar] -> GetXaxis() -> SetTitleSize  (0.100);
    grPull  [iCut][iVar] -> GetYaxis() -> CenterTitle();
   }
   gPad->SetTickx(2);
   gPad->SetGrid();
   
   ccCanvasPullTrace[iCut][iVar]-> cd();
   if (hPullTrace[iCut][iVar]) hPullTrace[iCut][iVar]->Draw();
   gPad->SetGrid();
   
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){    
    bool isSig = false;
    int whichSig = -1;
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     for (std::vector<std::string>::const_iterator itSig = SignalName.at(iSignalSet).begin(); itSig != SignalName.at(iSignalSet).end(); itSig++){
      if (reduced_name_samples.at(iName) == *itSig) {
       whichSig = iSignalSet;
       isSig = true;
      }
     }
    }
    
    if (isSig || reduced_name_samples.at(iName) == "DATA") {
     if ((!isSig || Discovery==0)){
      cCompareCut[iCut] -> cd(iVar+1);
      histo[iName][iCut][iVar]->Draw("EsameB");
      
      cCompareVar[iVar] -> cd(iCut+1);
      histo[iName][iCut][iVar]->Draw("EsameB");
      
      cCompareCutPull[iCut] -> cd(iVar+1);
      histo[iName][iCut][iVar]->Draw("EsameB");
      
      cCompareVarPull[iVar] -> cd(iCut*3+1);
      histo[iName][iCut][iVar]->Draw("EsameB");
      
      ccCanvas[iCut][iVar]-> cd();
      histo[iName][iCut][iVar]->Draw("EsameB");
      
      ccCanvasVarAndPull[iCut][iVar]-> cd(1);
      histo[iName][iCut][iVar]->Draw("EsameB");
     }
     if (isSig){
      ccCanvasNormalize[iCut][iVar]-> cd();
      histo[iName][iCut][iVar]->DrawNormalized("same L");
     }
     
    }
   }
   
   
   cCompareCut[iCut] -> cd(iVar+1);
   if (Discovery) {
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     DrawStack(hsSignal[iCut][iVar][iSignalSet],0,0,"Esame");
    }
   }
   
   cCompareVar[iVar] -> cd(iCut+1);
   if (Discovery) {
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     DrawStack(hsSignal[iCut][iVar][iSignalSet],0,0,"Esame");
    }
   }
   
   cCompareCutPull[iCut] -> cd(iVar+1);
   if (Discovery) {
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     DrawStack(hsSignal[iCut][iVar][iSignalSet],0,0,"Esame");
    }
   }
   
   cCompareVarPull[iVar] -> cd(iCut*3+1);
   if (Discovery) {
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     DrawStack(hsSignal[iCut][iVar][iSignalSet],0,0,"Esame");
    }
   }
   
   ccCanvas[iCut][iVar]-> cd();
   if (Discovery) {
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     DrawStack(hsSignal[iCut][iVar][iSignalSet],0,0,"Esame");
    }
   }
   
   ccCanvasVarAndPull[iCut][iVar]-> cd(1);
   if (Discovery) {
    for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
     DrawStack(hsSignal[iCut][iVar][iSignalSet],0,0,"Esame");
    }
   }
   
      
   cCompareCut[iCut] -> cd(iVar+1);
   leg->Draw();
   cCompareVar[iVar] -> cd(iCut+1);
   leg->Draw();
   cCompareCutPull[iCut] -> cd(iVar+1);
   leg->Draw();
   cCompareVarPull[iVar] -> cd(iCut*3+1);
   leg->Draw();
   ccCanvas[iCut][iVar]-> cd();
   leg->Draw();
   ccCanvasNormalize[iCut][iVar]-> cd();
   legMC->Draw();
   
  } ///==== end cicle on variables to plot ====
 } ///==== end cicle on selections ====
 
 std::cerr << " ******************************************* end *******************************************" << std::endl;
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 
 ///==== save output ====
 outFile.cd();
 cTrend -> Write();
 cTrendPull -> Write();
 
 outFile.mkdir("Trend");
 outFile.cd("Trend");
//  for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
//   cTrendPie[iCut] -> Write();
//  }
//  cTrendPieAll -> Write();
 
 
 outFile.cd();
 outFile.mkdir("PU");
 outFile.cd("PU");
 
 if (!doWeightFromFile) { 
  hPUMC     -> Write();
  hPUDATA   -> Write();
  hPUWeight -> Write();
 }
 
 outFile.cd();
 outFile.mkdir("Cut");
 outFile.cd("Cut");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  cCompareCut[iCut] -> Write();
  cCompareCutPull[iCut] -> Write();
  TString nameCut = Form ("Cut_%d",iCut);
  TString Cut = Form ("%s",vCut.at(iCut).c_str());
  TNamed nameCutNamed (nameCut,Cut);
  nameCutNamed.Write();
 }
 
 outFile.cd();
 outFile.mkdir("Var");
 outFile.cd("Var");
 for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
  cCompareVar[iVar] -> Write();
  cCompareVarPull[iVar] -> Write();
 }
 
 outFile.cd();
 TDirectory* cdAll = (TDirectory*) outFile.mkdir("All");
 cdAll->mkdir("Norm");
 cdAll->mkdir("Var");
 cdAll->mkdir("Pull");
 cdAll->mkdir("PullTrace");
 TDirectory* cdVarPull = (TDirectory*) cdAll->mkdir("VarPull"); 
 
 outFile.cd("All/Var");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ccCanvas[iCut][iVar]-> Write();
  }
 }
 
 outFile.cd();
 outFile.cd("All/Norm");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ccCanvasNormalize[iCut][iVar]-> Write();
  }
 }
 
 outFile.cd();
 outFile.cd("All/Pull");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ccCanvasPull[iCut][iVar]-> Write();
  }
 }
 
 outFile.cd();
 outFile.cd("All/PullTrace");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ccCanvasPullTrace[iCut][iVar]-> Write();
  }
 }
 
 outFile.cd();
 outFile.cd("All/VarPull");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  outFile.cd();
  TString dirName = Form ("cut-%d",iCut);
  cdVarPull->mkdir(dirName.Data());
  outFile.cd();
  TString absoluteDirName = Form ("All/VarPull/cut-%d",iCut);
  outFile.cd(absoluteDirName.Data());
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ccCanvasVarAndPull[iCut][iVar]-> Write();
  }
 }
 
 
 outFile.cd();
 outFile.mkdir("Data");
 outFile.cd("Data");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   hs[iCut][iVar] -> Write() ;
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    histo[iName][iCut][iVar] -> Write();
//     bool isSig = false;
//     for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
//      if (reduced_name_samples.at(iName) == *itSig) isSig = true;
//     }
//     if (isSig || reduced_name_samples.at(iName) == "DATA") {
//      histo[iName][iCut][iVar] -> Write();
//     }
   }
//    ((TH1F*)(hs[iCut][iVar] ->GetStack()->Last()))->Write() ;
   TH1F* tempH =  ((TH1F*)(hs[iCut][iVar] ->GetStack()->Last())) ;
   TString name = Form("All_%d_%d",iCut,iVar);
   tempH -> SetName(name);
   tempH -> Write();
   
   for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
    hsSignal[iCut][iVar][iSignalSet] -> Write();
   }
  }
  
 }
 
 outFile.cd();
 outFile.mkdir("DataTrend");
 outFile.cd("DataTrend");
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  hTrend[iName]->Write();  
 }

 outFile.cd();
 leg->Write();
 TCanvas* cLegend = new TCanvas("cLegend","cLegend",400,400);
 leg->Draw();
 cLegend->Write();
 
 
 outFile.Close();
 
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << ">>>>> Written in File :   " << OutFileName  << std::endl;  
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
}





