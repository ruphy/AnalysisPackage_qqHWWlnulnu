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
///   ___|                                       _)                           \  |   ___|  
///  |       _ \   __ `__ \   __ \    _` |   __|  |   __|   _ \   __ \       |\/ |  |         
///  |      (   |  |   |   |  |   |  (   |  |     | \__ \  (   |  |   |      |   |  |      
/// \____| \___/  _|  _|  _|  .__/  \__,_| _|    _| ____/ \___/  _|  _|     _|  _| \____|  
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
 gSystem->Load("libTree");

 TDRStyle();
  
 gStyle->SetPadTopMargin(0.11);
 gStyle->SetPadLeftMargin(0.10);
 gStyle->SetPadRightMargin(0.23);
 gStyle->cd(); 
 
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "   ___|                                       _)                           \\  |   ___|      " << std::endl;
 std::cout << "  |       _ \\   __ `__ \\   __ \\    _` |   __|  |   __|   _ \\   __ \\       |\\/ |  |     " << std::endl;
 std::cout << "  |      (   |  |   |   |  |   |  (   |  |     | \\__ \\  (   |  |   |      |   |  |         " << std::endl;
 std::cout << " \\____| \\___/  _|  _|  _|  .__/  \\__,_| _|    _| ____/ \\___/  _|  _|     _|  _| \\____|  " << std::endl;
 std::cout << "                          _|                                                                 " << std::endl;
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
//   (EColor) (kRed),
//   (EColor) (kBlue),

  kRed,
  kBlue,//(EColor)(kBlue+1),(EColor) (kBlue+2),
  kGreen,
  //kMagenta,(EColor) (kMagenta+1),(EColor) (kMagenta+2),
  kTeal,//(EColor) (kTeal+1),
  kGray,
  kOrange, //(EColor) (kOrange+1),
  (EColor) (kPink+2),//(EColor) (kPink+1),(EColor) (kPink+2),
  kViolet,
  kYellow,
  kGray,(EColor) (kGray+1),(EColor) (kViolet),(EColor) (kYellow),(EColor) (kGray)

//   (EColor) (kBlue),(EColor) (kBlue+1),
/*  (EColor) (kGreen),
  (EColor) (kYellow),(EColor) (kYellow+1),
  (EColor) (kBlack),(EColor) (kBlack+1),
  //kMagenta,(EColor) (kMagenta+1),(EColor) (kMagenta+2),
  kTeal,//(EColor) (kTeal+1),
  kGray,
  kOrange,
  kViolet,
  kGreen,
  kRed,
  kBlue,//(EColor)(kBlue+1),(EColor) (kBlue+2),
  (EColor) (kPink+2),//(EColor) (kPink+1),(EColor) (kPink+2),
  kYellow,
  (EColor) (kOrange+1),(EColor) (kViolet+1),(EColor) (kYellow+1),(EColor) (kGreen+1),
  (EColor) (kOrange+2),(EColor) (kViolet+2),(EColor) (kYellow+2),(EColor) (kGreen+2),
  (EColor) (kOrange+3),(EColor) (kViolet+3),(EColor) (kYellow+3),(EColor) (kGreen+3),
  (EColor) (kOrange+4),(EColor) (kViolet+4),(EColor) (kYellow+4),(EColor) (kGreen+4),
  (EColor) (kOrange+5),(EColor) (kViolet+5),(EColor) (kYellow+5),(EColor) (kGreen+5)*/
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
 
 
 TTree *treeEffVect[100];
 TTree *treeJetLepVect[100];
 

 
  //  [iCut][iVar] 
 TCanvas* ccCanvas[20][30];
 //  [iName][iCut][iVar]
 TH1F* histo[100][20][30];
 TH1F* histo_temp[100][20][30];

 //  [iName][iCut]
 double numEvents[100][20];
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 char NameNormalization[1000][1000];
 double Normalization[1000];
 double xsection[1000];
 char nameFileIn[1000];
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
 
 ///==== list of selections to perform (NOT sequential additive selections) ====
 std::string CutFile = gConfigParser -> readStringOption("Selections::CutFile");
 std::vector<std::string> vCut;
 std::vector<std::string> vCutHR;
 
 std::string CutHRFile = "";
 try {
  CutHRFile = gConfigParser -> readStringOption("Selections::CutHRFile");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 std::cout << " nCuts = " << ReadFileCut(CutFile, vCut) << std::endl;
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
   Normalization[iSample] = XSection * preselection_efficiency / numEntriesBefore;
  }
  else {
   Normalization[iSample] = 0; 
  }    
  if (Latinos) {
   sprintf (NameNormalization[iSample], "(%s) / 1000. ", xsectionName[iSample]);
   Normalization[iSample] = XSection / 1000.;
  }
 }
 
 
 
 TLegend* leg = new TLegend(0.8,0.25,0.98,0.78);
 bool LegendBuilt = false;
 
 if (debug) std::cout << " Cut size = " << vCut.size() << " ~~ " << std::endl;
 std::cout.precision (2) ;
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  TString Cut = Form ("%s",vCut.at(iCut).c_str());
  if (debug) std::cout << " Cut[" << iCut << ":" << vCut.size() << "] = " << Cut.Data() << " ~~ " << std::endl;
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   if (debug) std::cout << " Var[" << iVar << ":" << vVarName.size() << "] = " << vVarName.at(iVar) << " ~~ " << std::endl;
   ///==== initialize ====
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    reduced_name_samples_flag.at(iName) = -1;
   }
   
   ///==== cicle on samples ====
   for (int iSample = (numberOfSamples-1); iSample>= 0; iSample--){
    if (debug) std::cout << " Sample[" << iSample << ":" << numberOfSamples << "] = " << nameSample[iSample] << " ~~ " << std::endl;
    TString name_histo_temp = Form("%s_%d_%d_temp",nameSample[iSample], iCut, iVar);
    histo_temp[iSample][iCut][iVar] = new TH1F(name_histo_temp,name_histo_temp,vNBin.at(iVar),vMin.at(iVar), vMax.at(iVar));
    char toDraw[1000];
    sprintf(toDraw,"%s >> %s",vVarName.at(iVar).c_str(),name_histo_temp.Data());      

    histo_temp[iSample][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
    
    TString CutExtended;
    
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
    CutExtended = Form ("(%s) * (%s)",CutExtended.Data(),NameNormalization[iSample] );    
    
    treeJetLepVect[iSample]->Draw(toDraw,CutExtended,"");
    
//     if (Normalization[iSample]>0) { 
//      histo_temp[iSample][iCut][iVar] -> Scale(Normalization[iSample]); 
//     }    
    for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
     if (name_samples.at(iSample) == reduced_name_samples.at(iName)){
      if (reduced_name_samples_flag.at(iName) == -1){
       TString name_histoTot_temp = Form("%s_%d_%d_Tot_temp",reduced_name_samples.at(iName).c_str(),iCut, iVar);
       TString name_HR_histoTot_temp = Form("%s %s",vVarNameHR.at(iVar).c_str(),  vCutHR.at(iCut).c_str());
       histo[iName][iCut][iVar] = new TH1F(name_histoTot_temp,name_HR_histoTot_temp,vNBin.at(iVar),vMin.at(iVar), vMax.at(iVar));
       histo[iName][iCut][iVar] -> Sumw2(); //---- così mette l'errore giusto!
       reduced_name_samples_flag.at(iName) = 1;
      }
      histo[iName][iCut][iVar] -> Add(histo_temp[iSample][iCut][iVar]);
     }
    }
   } ///==== end cicle on samples ====
  std::cout << "Processing: " << blue << (((double) iCut)/vCut.size())*100. << "% "  << normal <<  " -- " <<  blue << (((double) iVar)/vVarName.size())*100. << "% \r"  << normal << std::flush;   
  } ///==== end cicle on variables to plot ====
 } ///==== end cicle on selections ====
 std::cout << std::endl; 
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    histo[iName][iCut][iVar]->GetXaxis()->SetTitle(vVarNameHR.at(iVar).c_str());
    histo[iName][iCut][iVar]->SetMarkerColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetLineColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetFillColor(vColor[iName]);
    histo[iName][iCut][iVar]->SetLineWidth(2);
    histo[iName][iCut][iVar]->SetFillStyle(3001);
    
    histo[iName][iCut][iVar]->SetMarkerStyle(21);
    histo[iName][iCut][iVar]->SetMarkerSize(0.5);
    histo[iName][iCut][iVar]->SetLineWidth(2);
    histo[iName][iCut][iVar]->SetFillStyle(3001); 
   }
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
 
 ///==== normalization (begin) ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    double integral = histo[iName][iCut][iVar]->Integral();
    if (integral!=0) integral = 1. / integral;
    histo[iName][iCut][iVar]->Scale(integral);
   }
  }
 }
 
  
 ///==== normalization (end) ====
  
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
  }
 } 
 
 ///==== cicle on selections ====
 for (unsigned int iCut = 0; iCut<vCut.size(); iCut++){
  ///==== cicle on variables to plot ====
  for (unsigned int iVar = 0; iVar<vVarName.size(); iVar++){
   ///==== draw in canvas ====
   cCompareCut[iCut] -> cd(iVar+1);
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    if (iName==0) {histo[iName][iCut][iVar]->Draw("EP");}
    else {histo[iName][iCut][iVar]->Draw("EsameP");}
   }
   gPad->SetLogy();
   gPad->SetGrid();
   leg->Draw();

   cCompareVar[iVar] -> cd(iCut+1);
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    if (iName==0) {histo[iName][iCut][iVar]->Draw("EP");}
    else {histo[iName][iCut][iVar]->Draw("EsameP");}
   }
   gPad->SetLogy();
   gPad->SetGrid();
   leg->Draw();
   
 
   ccCanvas[iCut][iVar]-> cd();
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    if (iName==0) {histo[iName][iCut][iVar]->Draw("EP");}
    else {histo[iName][iCut][iVar]->Draw("EsameP");}
   }
   gPad->SetLogy();
   gPad->SetGrid();
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
   for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
    if (reduced_name_samples.at(iName) == "DATA") {
     histo[iName][iCut][iVar] -> Write();
    }
   }
  }
 }
 
 leg->Write();
 
}





