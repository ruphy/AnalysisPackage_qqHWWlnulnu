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


#include "TSystem.h"



#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif


///
///
///      ___|                       |                     \  |   ___|         /      __ \     \  __ __|   \    
///     |       _ \   |   |  __ \   __|   _ \   __|      |\/ |  |            /       |   |   _ \    |    _ \   
///     |      (   |  |   |  |   |  |     __/  |         |   |  |           /        |   |  ___ \   |   ___ \  
///    \____| \___/  \__,_| _|  _| \__| \___| _|        _|  _| \____|     _/        ____/ _/    _\ _| _/    _\ 
///   
///   
///      ___|                |                            |   _)       
///    \___ \   |   |   __|  __|   _ \  __ `__ \    _` |  __|  |   __|    __| 
///          |  |   | \__ \  |     __/  |   |   |  (   |  |    |  (    \__ \ 
///    _____/  \__, | ____/ \__| \___| _|  _|  _| \__,_| \__| _| \___| ____/  
///            ____/                                                   
///   


// std::vector<double> PUWeight;

int GetNumList(std::vector<int> &list){
 int result = 0;
 for (int it = 0; it<list.size(); it++) result += list.at(it);
 return result;
}


int main(int argc, char** argv)
{ 
 gSystem->Load("libTree");

 TDRStyle();
 
 gStyle->SetPadTopMargin(0.11);
 gStyle->SetPadLeftMargin(0.07);
 gStyle->SetPadRightMargin(0.23);
 gStyle->cd(); 
 
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "      ___|                       |                     \\  |   ___|         /      __ \\     \\  __ __|   \\          " << std::endl;
 std::cout << "     |       _ \\   |   |  __ \\   __|   _ \\   __|      |\\/ |  |            /       |   |   _ \\    |    _ \\       " << std::endl;
 std::cout << "     |      (   |  |   |  |   |  |     __/  |         |   |  |           /        |   |  ___ \\   |   ___ \\          " << std::endl;
 std::cout << "    \\____| \\___/  \\__,_| _|  _| \\__| \\___| _|        _|  _| \\____|     _/        ____/ _/    _\\ _| _/    _\\   " << std::endl; 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl; 
 std::cout << " " << std::endl; 
 std::cout << "      ___|                |                            |   _)                         " << std::endl;
 std::cout << "    \\___ \\   |   |   __|  __|   _ \\  __ `__ \\    _` |  __|  |   __|   __|         " << std::endl;
 std::cout << "          |  |   | \\__ \\  |     __/  |   |   |  (   |  |    |  (    \\__ \\     " << std::endl;
 std::cout << "    _____/  \\__, | ____/ \\__| \\___| _|  _|  _| \\__,_| \\__| _| \\___| ____/       " << std::endl;
 std::cout << "            ____/                                                                     " << std::endl;
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
 
 std::vector<std::string> SignalName;
 SignalName = gConfigParser -> readStringListOption("Input::SignalName");
 
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
 
 
 
 TTree *treeEffVect[300];
 TTree *treeJetLepVect[300];
 
 
 
 //  [iCut] 
 TString* infoString[171];
 TLatex *infoLatex[171]; 
 TCanvas* ccCanvas[171];
 TCanvas* ccCanvasPull[171];
 TH1F* histoSumMC[171];
 //  [iName][iCut]
 TH1F* histo[301][171];
 TH1F* histo_temp[301][171];
 
 //  [iName][iCut]
 double numEvents[301][171];
 double errnumEvents[301][171];
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 char NameNormalization[1000][1000];
 double Normalization[1000];
 double xsection[1000];
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 
 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
 
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
 std::cout << " nCuts   = " << vCut.size() << std::endl;
 
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
 
 ///==== output file ====
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
 
 TFile outFile(OutFileName.c_str(),"RECREATE");
 outFile.cd();
 
 
 ///==== Latinos flag ==== 
 bool  Latinos = false; 
 try {
  Latinos = gConfigParser -> readBoolOption("Input::Latinos");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::Latinos  " << Latinos  << std::endl;  
 
 
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
  toLoad = Form(".L %s",nameptHWeight.c_str());
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
 
 int Entries[301];
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  xsection[iSample] = atof(xsectionName[iSample]);
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
 
 ///==== get number in sample list that correspond to DATA ====
 int numDATA = -1;
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  if (reduced_name_samples.at(iName) == "DATA") {
   numDATA = iName;
  }
 }
 
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){
//   bool isData = false;
//   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
//    if (name_samples.at(iSample) == reduced_name_samples.at(iName)){
//     if (iName == numDATA) {
//      isData = true;
//     }
//    }
//   }
//   if (!isData) {
   char nameFile[20000];
   sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
   if (debug) std::cout << " nameFile = " << nameFile << std::endl;
   
   TFile* f = new TFile(nameFile, "READ");
   
   treeEffVect[iSample] = (TTree*) f->Get(treeNameSelections.c_str());
   if (treeEffVect[iSample] != 0) {
    char nameTreeEff[301];
    sprintf(nameTreeEff,"treeEff_%d",iSample); 
    treeEffVect[iSample]->SetName(nameTreeEff);      
   }
   
   treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
   char nameTreeJetLep[301];
   sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
   treeJetLepVect[iSample]->SetName(nameTreeJetLep);
//   }
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
  if (numEntriesBefore != 0) {
   Normalization[iSample] = LUMI * XSection * preselection_efficiency / numEntriesBefore;
  }
  else {
   Normalization[iSample] = 0; 
  }    
  
  if (Latinos) {
   sprintf (NameNormalization[iSample], "(%s) *  %f / 1000. ", xsectionName[iSample], LUMI);
   Normalization[iSample] = XSection * LUMI / 1000.;   
  }
  
 }
 
 
 
 TLegend* leg = new TLegend(0.8,0.25,0.98,0.78);
 bool LegendBuilt = false;
 
 TString lumiName = Form("#splitline{L = %.1f pb^{-1}}{#splitline{#sqrt{s} = 7}{CMS preliminary}}", LUMI);
 //  TString lumiName = Form("#sqrt{s}=7 TeV   L=%.1f pb^{-1}", LUMI);
 TLatex *latex = new TLatex(0.80, 0.90, lumiName); 
 latex->SetTextAlign(12);
 latex->SetNDC();
 latex->SetTextFont(42);
 latex->SetTextSize(0.03);
 
 
 if (debug) std::cout << " Cut size = " << vCut.size() << " ~~ " << std::endl;
 std::cout.precision (5) ;
//  std::cout.unsetf(std::ios::scientific);
 
 
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
   TString name_histo_temp = Form("%s_%d_temp",nameSample[iSample], iCut);
   histo_temp[iSample][iCut] = new TH1F(name_histo_temp,name_histo_temp,100,-10,10000000000);
   char toDraw[1000];
   sprintf(toDraw,"1 >> %s",name_histo_temp.Data());      
   histo_temp[iSample][iCut] -> Sumw2(); //---- così mette l'errore giusto!
   
   TString CutExtended;
   bool isData = false; //----> in systematic studies it should be always false (never DATA) ... but, let's do it!
   //    if (Normalization[iSample] < 0) isData = true;
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
    //---- normalize here
    CutExtended = Form ("(%s) * (%s)",CutExtended.Data(),NameNormalization[iSample] );    
    //----
   }
   else {
    CutExtended = Form ("(%s)",Cut.Data());    
   }
   
   treeJetLepVect[iSample]->Draw(toDraw,CutExtended,"");
   
//    if (Normalization[iSample]>0) { 
//     histo_temp[iSample][iCut] -> Scale(Normalization[iSample]); 
//    }
   
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    if (name_samples.at(iSample) == reduced_name_samples.at(iName)){
     if (reduced_name_samples_flag.at(iName) == -1){
      TString name_histoTot_temp = Form("%s_%d_Tot_temp",reduced_name_samples.at(iName).c_str(),iCut);
      TString name_HR_histoTot_temp = Form("cut %d",iCut);
      histo[iName][iCut] = new TH1F(name_histoTot_temp,name_HR_histoTot_temp,100,-10,10000000000);
      histo[iName][iCut] -> Sumw2(); //---- così mette l'errore giusto!
      reduced_name_samples_flag.at(iName) = 1;
     }
     histo[iName][iCut] -> Add(histo_temp[iSample][iCut]);
    }
   }
   
   
   std::cout <<"Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% "  << normal <<  " -- " <<  red << (((double) numberOfSamples - iSample)/(numberOfSamples))*100. << "% \r"  << normal << std::flush;   
  } ///==== end cicle on samples ====
 } ///==== end cicle on selections ====
 
 std::cout << " >>> Reprocessing ... " << std::endl;
 std::cout << std::endl;
 
 
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  //   bool isData = false;
  //   if (iName == numDATA) {
   //    isData = true;
   //   }  
   //   if (!isData) {
    for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
     double error = 0;
     numEvents[iName][iCut] = histo[iName][iCut]->IntegralAndError(0,histo[iName][iCut]->GetNbinsX()+1,error);
     errnumEvents[iName][iCut] = error;
    }
    //   }
 }
 
 std::cout << std::endl;
 std::cout << " ****************************************************************** " << std::endl;
 std::cout << " ****************************************************************** " << std::endl;
 std::cout << " *********************** for Lands datacard *********************** " << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
 
 std::string nameOutDataCard = "dataCard.test.txt";
 
 ///==== output - txt file name ====
 try {
  nameOutDataCard = gConfigParser -> readStringOption("Output::DataCard");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 std::ofstream myfile;
 myfile.open (nameOutDataCard.c_str());
 myfile.precision(5);
 std::cout << "Writing to: " << nameOutDataCard << std::endl;
 std::cout << std::endl;
 
//  double totalSig = 0;
//  double totalBkg = 0;
//  for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
//   if (iName != numDATA) {
//    bool isSig = false;
//    for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
//     if (reduced_name_samples.at(iName) == *itSig) isSig = true;
//    }
//    if (isSig) {
//     totalSig += numEvents[iName][vCut.size()-1];   ///---- last cut!
//    }
//    else {
//     totalBkg += numEvents[iName][vCut.size()-1];   ///---- last cut!
//    }
//   }
//  }

 //---- all cuts ----
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
//   if (iName != numDATA) {
   myfile << std::setw (10) << reduced_name_samples.at(iName) << "  ";
//   }
 }
 myfile << std::endl;
 
 for (unsigned int iCut =0; iCut<vCut.size(); iCut++){  
  for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
//    if (iName != numDATA) {
    myfile << std::setw (10) << fabs(numEvents[iName][iCut]) << "  ";
// //     myfile << std::setw (10) << numEvents[iName][iCut] << "  ";
//    }
  }
  myfile << std::endl;
 }
 
 
 for (unsigned int iCut =0; iCut<vCut.size(); iCut++){  
  for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
//    if (iName != numDATA) {
//     myfile << std::setw (10) << (numEvents[iName][iCut] != 0 ? 1. + errnumEvents[iName][iCut] / numEvents[iName][iCut] : -1) << "  ";
    myfile << std::setw (10) << (numEvents[iName][iCut] != 0 ? 1. + fabs(errnumEvents[iName][iCut] / numEvents[iName][iCut]) : -1) << "  ";    
//    }
  }
  myfile << std::endl;
 }
 

 myfile.close(); 
 
 
 std::cerr << " ******************************************* end *******************************************" << std::endl;
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 
 
 ///==== save output ====
 outFile.cd();
 outFile.cd();
 outFile.mkdir("PU");
 outFile.cd("PU");
 
 if (!doWeightFromFile) { 
  hPUMC     -> Write();
  hPUDATA   -> Write();
  hPUWeight -> Write();
 }
 
 leg->Write();

}


















