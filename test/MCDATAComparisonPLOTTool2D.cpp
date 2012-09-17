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
///
///   ___|                                       _)                           \  |   ___|         /      __ \     \  __ __|   \    
///  |       _ \   __ `__ \   __ \    _` |   __|  |   __|   _ \   __ \       |\/ |  |            /       |   |   _ \    |    _ \   
///  |      (   |  |   |   |  |   |  (   |  |     | \__ \  (   |  |   |      |   |  |           /        |   |  ___ \   |   ___ \  
/// \____| \___/  _|  _|  _|  .__/  \__,_| _|    _| ____/ \___/  _|  _|     _|  _| \____|     _/        ____/ _/    _\ _| _/    _\ 
///                          _|                                                                                                    
///
///
///
///     ___ \   __ \  
///        ) |  |   | 
///       __/   |   | 
///     _____| ____/  
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
 std::cout << "   ___|                                       _)                           \\  |   ___|         /      __ \\     \\  __ __|   \\     " << std::endl;
 std::cout << "  |       _ \\   __ `__ \\   __ \\    _` |   __|  |   __|   _ \\   __ \\       |\\/ |  |            /       |   |   _ \\    |    _ \\    " << std::endl;
 std::cout << "  |      (   |  |   |   |  |   |  (   |  |     | \\__ \\  (   |  |   |      |   |  |           /        |   |  ___ \\   |   ___ \\   " << std::endl;
 std::cout << " \\____| \\___/  _|  _|  _|  .__/  \\__,_| _|    _| ____/ \\___/  _|  _|     _|  _| \\____|     _/        ____/ _/    _\\ _| _/    _\\  " << std::endl;
 std::cout << "                          _|                                                                                                     " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "     ___ \\   __ \\        " << std::endl;
 std::cout << "       ) |  |   |          " << std::endl;
 std::cout << "      __/   |   |          " << std::endl;
 std::cout << "    _____| ____/           " << std::endl;
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
 
 double LUMI = gConfigParser -> readDoubleOption("Input::Lumi");
 
 double LumiSyst = gConfigParser -> readDoubleOption("Input::LumiSyst");
 
 double Discovery = gConfigParser -> readDoubleOption("Input::Discovery");
 
 int Normalize = gConfigParser -> readIntOption("Input::Normalize");
 
 std::vector<std::string> SignalName;
 if (Discovery == 1) SignalName = gConfigParser -> readStringListOption("Input::SignalName");
 
 
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
 
 TTree *treeEffVect[100];
 TTree *treeJetLepVect[100];
 

 
  //  [iCut][iVar] 
 TString* infoString[20][30];
 TLatex *infoLatex[20][30]; 
 TCanvas* ccCanvas[20][30];
 TCanvas* ccCanvasPull[20][30];
 TCanvas* ccCanvasPullTrace[20][30];
 TH2F* histoSumMC[20][30];
 //  [iName][iCut][iVar]
 TH2F* histo[100][30][30];
 TH2F* histo_temp[100][20][30];

 //  [iName][iCut]
 double numEvents[100][30];
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 double Normalization[1000];
 double xsection[1000];
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());

 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName); 
 
 ///==== list of variables to plot ====
 std::vector<std::pair<double, double> > vMin;
 std::vector<std::pair<double, double> > vMax;
 std::vector<std::pair<int, int> > vNBin;
 std::vector<std::pair<std::string, std::string> > vVarName;
 std::vector<std::pair<std::string, std::string> > vVarNameHR;
 std::string VarFile = gConfigParser -> readStringOption("Plot::VarFile");
 
 int numVar = ReadFileVar2D(VarFile,vMin,vMax,vNBin,vVarName,vVarNameHR);
  
 
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
  
  if (numEntriesBefore != 0) {
   Normalization[iSample] = LUMI * XSection * preselection_efficiency / numEntriesBefore;
  }
  else {
   Normalization[iSample] = 0; 
  }    
  
  if (Latinos) Normalization[iSample] = XSection * LUMI / 1000.;
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
   if (debug) std::cout << " Var[" << iVar << ":" << vVarName.size() << "] = " << vVarName.at(iVar).first << " && " << vVarName.at(iVar).second << " ~~ " << std::endl;
   ///==== initialize ====
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    reduced_name_samples_flag.at(iName) = -1;
   }
   
   ///==== cicle on samples ====
   for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
    if (debug) std::cout << " Sample[" << iSample << ":" << numberOfSamples << "] = " << nameSample[iSample] << " ~~ " << std::endl;
    TString name_histo_temp = Form("%s_%d_%d_temp",nameSample[iSample], iCut, iVar);
    histo_temp[iSample][iCut][iVar] = new TH2F(name_histo_temp,name_histo_temp,vNBin.at(iVar).first,vMin.at(iVar).first, vMax.at(iVar).first,vNBin.at(iVar).second,vMin.at(iVar).second, vMax.at(iVar).second);
    char toDraw[1000];
    sprintf(toDraw,"%s:%s >> %s",vVarName.at(iVar).second.c_str(),vVarName.at(iVar).first.c_str(),name_histo_temp.Data());      

    histo_temp[iSample][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
    
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
    }
    else {
     CutExtended = Form ("(%s)",Cut.Data());    
    }
    treeJetLepVect[iSample]->Draw(toDraw,CutExtended,"");
    
    if (Normalization[iSample]>0) { 
//      histo_temp[iSample][iCut][iVar] -> Sumw2();
     histo_temp[iSample][iCut][iVar] -> Scale(Normalization[iSample]); 
    }
    
//     std::cout << "Processing: " << blue << (((double) numberOfSamples - iSample)/numberOfSamples) << "% \r"  << normal << std::flush;
   } ///==== end cicle on samples ====
//    std::cout << "###";
  std::cout << "Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% "  << normal <<  " -- " <<  blue << (((double) iVar)/vVarName.size())*100. << "% \r"  << normal << std::flush;   
  } ///==== end cicle on variables to plot ====
  //   std::cout << "***";
 } ///==== end cicle on selections ====
 std::cout << std::endl; 
 
 

 
 ///---- create "big" histos ----
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
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
       TString name_HR_histoTot_temp = Form("%s vs %s @ %s",vVarNameHR.at(iVar).second.c_str(),vVarNameHR.at(iVar).first.c_str(), vCutHR.at(iCut).c_str());
       //        TString name_HR_histoTot_temp = Form("%s %d %s",vVarNameHR.at(iVar).c_str(), iCut, reduced_name_samples.at(iName).c_str());
       histo[iName][iCut][iVar] = new TH2F(name_histoTot_temp,name_HR_histoTot_temp,vNBin.at(iVar).first,vMin.at(iVar).first, vMax.at(iVar).first,vNBin.at(iVar).second,vMin.at(iVar).second, vMax.at(iVar).second);
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
   double data_int = histo[numDATA][iCut][iVar] -> Integral();
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
       TString name_HR_histoTot_temp = Form("%s vs %s @ %s",vVarNameHR.at(iVar).second.c_str(),vVarNameHR.at(iVar).first.c_str(), vCutHR.at(iCut).c_str());
       //        TString name_HR_histoTot_temp = Form("%s %d %s",vVarNameHR.at(iVar).c_str(), iCut, reduced_name_samples.at(iName).c_str());
       histo[iName][iCut][iVar] = new TH2F(name_histoTot_temp,name_HR_histoTot_temp,vNBin.at(iVar).first,vMin.at(iVar).first, vMax.at(iVar).first,vNBin.at(iVar).second,vMin.at(iVar).second, vMax.at(iVar).second);
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
	TString name_HR_histoTot_temp = Form("%s vs %s @ %s",vVarNameHR.at(iVar).second.c_str(),vVarNameHR.at(iVar).first.c_str(), vCutHR.at(iCut).c_str());
	//        TString name_HR_histoTot_temp = Form("%s %d %s",vVarNameHR.at(iVar).c_str(), iCut, reduced_name_samples.at(iName).c_str());
	histo[iName][iCut][iVar] = new TH2F(name_histoTot_temp,name_HR_histoTot_temp,vNBin.at(iVar).first,vMin.at(iVar).first, vMax.at(iVar).first,vNBin.at(iVar).second,vMin.at(iVar).second, vMax.at(iVar).second);
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
 
 
 //  [iCut][iVar]
 THStack* hs[100][100];
 
 std::cout << std::endl;
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   TString nameStack = Form("%d_%d_stack",iCut,iVar);
   hs[iCut][iVar] = new THStack(nameStack,nameStack);
   
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    histo[iName][iCut][iVar]->GetXaxis()->SetTitle(vVarNameHR.at(iVar).first.c_str());
    histo[iName][iCut][iVar]->GetYaxis()->SetTitle(vVarNameHR.at(iVar).second.c_str());
    histo[iName][iCut][iVar]->SetMarkerColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetLineColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetFillColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetLineWidth(2);
    histo[iName][iCut][iVar]->SetFillStyle(3001);
    
    bool isSig = false;
    for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
     if (reduced_name_samples.at(iName) == *itSig) isSig = true;
    }
    
    if (!isSig && reduced_name_samples.at(iName) != "DATA") {
     hs[iCut][iVar]->Add(histo[iName][iCut][iVar]);
    }
    else {
     if (!isSig) {
      histo[iName][iCut][iVar]->SetMarkerStyle(20);
      histo[iName][iCut][iVar]->SetMarkerSize(1);
      histo[iName][iCut][iVar]->SetMarkerColor(kBlack);
      histo[iName][iCut][iVar]->SetLineColor(kBlack);
      histo[iName][iCut][iVar]->SetFillColor(kBlack);
      histo[iName][iCut][iVar]->SetLineWidth(2);
      histo[iName][iCut][iVar]->SetFillStyle(3001);  
     }
     else {
      histo[iName][iCut][iVar]->SetMarkerStyle(21);
      histo[iName][iCut][iVar]->SetMarkerSize(1);
      histo[iName][iCut][iVar]->SetLineWidth(2);
      histo[iName][iCut][iVar]->SetFillStyle(3001);  
     }
    }
   }
   ///==== histo sum MC ====    
   ///==== Add systrematic error ====
//    AddError(hs[iCut][iVar],LumiSyst);
   histoSumMC[iCut][iVar] = ((TH2F*)(hs[iCut][iVar]->GetStack()->Last()));
    
   ///==== legend ====
   if (!LegendBuilt){
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     leg->AddEntry(histo[iName][iCut][iVar],reduced_name_samples.at(iName).c_str(),"pf");    
     LegendBuilt = true;
    }
   }
  }
 }
 std::cout << std::endl << std::endl;
 
 
 
 LumiSyst = 0; ///---- bug fix
 

//  [iName][iCut][iVar]
 TCanvas* cCanvasAll[100][30][30];

 TCanvas* cCompareCut[100];
 TCanvas* cCompareVar[100];
 
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  TString nameCanvas = Form("%d_Cut_Canvas",iCut);
  cCompareCut[iCut] = new TCanvas(nameCanvas,nameCanvas,400 * vVarName.size(),400);
  cCompareCut[iCut] -> Divide (vVarName.size(),1);
 }
 
 for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){ ///==== cicle on variables to plot ====
   TString nameCanvas = Form("%d_Var_Canvas",iVar);
   cCompareVar[iVar] = new TCanvas(nameCanvas,nameCanvas,400,400 * vCut.size());
   cCompareVar[iVar] -> Divide (1,vCut.size());
 }
 
 
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   TString nameCanvas = Form("%d_%d_Canvas",iCut,iVar);
   ccCanvas[iCut][iVar] = new TCanvas(nameCanvas,nameCanvas,400,400);
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    TString nameCanvasName = Form("%d_%d_%d_Canvas",iCut,iVar,iName);
    cCanvasAll[iName][iCut][iVar] = new TCanvas(nameCanvasName,nameCanvasName,400,400);
   }
  }
 } 
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ///==== draw in canvas ====
   
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    cCanvasAll[iName][iCut][iVar]->cd();
    gPad->SetLeftMargin(0.14);
    gPad->SetRightMargin(0.23);
    histo[iName][iCut][iVar]->Draw();
    histo[iName][iCut][iVar]->GetXaxis()->SetTitle(vVarNameHR.at(iVar).first.c_str());
    histo[iName][iCut][iVar]->GetYaxis()->SetTitle(vVarNameHR.at(iVar).second.c_str());
    gPad->SetLogz();
    gPad->SetGrid();
    leg->Draw();
    latex->Draw();
   }
   
   cCompareCut[iCut] -> cd(iVar+1);
   hs[iCut][iVar] ->Draw();
   hs[iCut][iVar]->GetXaxis()->SetTitle(vVarNameHR.at(iVar).first.c_str());
   hs[iCut][iVar]->GetYaxis()->SetTitle(vVarNameHR.at(iVar).second.c_str());
   gPad->SetLogz();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();
   
   cCompareVar[iVar] -> cd(iCut+1);
   hs[iCut][iVar] ->Draw("LEGO");
   hs[iCut][iVar]->GetXaxis()->SetTitle(vVarNameHR.at(iVar).first.c_str());
   hs[iCut][iVar]->GetYaxis()->SetTitle(vVarNameHR.at(iVar).second.c_str());
   gPad->SetLogz();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();

   ccCanvas[iCut][iVar]-> cd();
   hs[iCut][iVar]->Draw("LEGO");
   hs[iCut][iVar]->GetXaxis()->SetTitle(vVarNameHR.at(iVar).first.c_str());
   hs[iCut][iVar]->GetYaxis()->SetTitle(vVarNameHR.at(iVar).second.c_str());
   gPad->SetLogz();
   gPad->SetGrid();
   leg->Draw();
   latex->Draw();

   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    
    bool isSig = false;
    for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
     if (reduced_name_samples.at(iName) == *itSig) isSig = true;
    }
    
    if (isSig || reduced_name_samples.at(iName) == "DATA") {
     cCompareCut[iCut] -> cd(iVar+1);
//      histo[iName][iCut][iVar]->Draw("EsameB");
//      histo[iName][iCut][iVar]->Draw("same");
     
     cCompareVar[iVar] -> cd(iCut+1);
//      histo[iName][iCut][iVar]->Draw("EsameB");
//      histo[iName][iCut][iVar]->Draw("same");
     
     ccCanvas[iCut][iVar]-> cd();
//      histo[iName][iCut][iVar]->Draw("EsameB");
//      histo[iName][iCut][iVar]->Draw("same");
    }
   }
   
   cCompareCut[iCut] -> cd(iVar+1);
   leg->Draw();
   cCompareVar[iVar] -> cd(iCut+1);
   leg->Draw();
   ccCanvas[iCut][iVar]-> cd();
   leg->Draw();
   
  } ///==== end cicle on variables to plot ====
 } ///==== end cicle on selections ====
 
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
 
 outFile.cd();
 outFile.mkdir("Cut");
 outFile.cd("Cut");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  cCompareCut[iCut] -> Write();
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
 }
 
 outFile.cd();
 TDirectory* cdAll = (TDirectory*) outFile.mkdir("All");
 cdAll->mkdir("Var");
 outFile.cd("All/Var");
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ccCanvas[iCut][iVar]-> Write();
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
  }
 }
 
 
 outFile.cd();
 cdAll->mkdir("CutVar");
 outFile.cd("All/CutVar");
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    cCanvasAll[iName][iCut][iVar]->Write();
   }
  }
 }
 outFile.cd();
   
 
 
 
 
 
 
 
 leg->Write();
 
}





