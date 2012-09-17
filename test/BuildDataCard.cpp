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
///     __ )         _)  |      |      __ \          |            ___|                  | 
///     __ \   |   |  |  |   _` |      |   |   _` |  __|   _` |  |       _` |   __|  _` | 
///     |   |  |   |  |  |  (   |      |   |  (   |  |    (   |  |      (   |  |    (   | 
///    ____/  \__,_| _| _| \__,_|     ____/  \__,_| \__| \__,_| \____| \__,_| _|   \__,_| 
///                                                                                       
///   

// std::vector<double> PUWeight;



void FilterListNames(std::vector<std::string> &nameSamplesSystFromFile, std::vector<std::string> &nameSamplesDump, std::vector<int> &flagSamplesSystDump){
 for (uint iName = 0; iName < nameSamplesSystFromFile.size(); iName++) {
  int flag = -1;
  for (uint iNameDump = 0; iNameDump < nameSamplesDump.size(); iNameDump++) {
   if (nameSamplesDump.at(iNameDump) == nameSamplesSystFromFile.at(iName)) {
//     std::cout << "FilterListNames::  nameSamplesDump.at(" << iNameDump << ") == nameSamplesSystFromFile.at(" << iName << ") --> " << nameSamplesDump.at(iNameDump) << " == " << nameSamplesSystFromFile.at(iName) << std::endl;
    flag = iNameDump;
   }
  }
  if (nameSamplesSystFromFile.at(iName) == "-") {
   flag = -1;
  }
  flagSamplesSystDump.push_back(flag);
 }
}

//----
//---- flagSamplesSystDump tells the number of the long list of files saved in table systematics.
//---- it is ## if a match is found
//---- it is -1 if no match is found OR "-" is provided ---> it will be a data driven sample
//----





int main(int argc, char** argv)
{ 
 TDRStyle();
 
 gStyle->SetPadTopMargin(0.11);
 gStyle->SetPadLeftMargin(0.07);
 gStyle->SetPadRightMargin(0.23);
 gStyle->cd(); 
 
 
 std::cout << "          " << std::endl;
 std::cout << "          " << std::endl;
 std::cout << "           __ )         _)  |      |      __ \\          |            ___|                  |  " << std::endl;
 std::cout << "           __ \\   |   |  |  |   _` |      |   |   _` |  __|   _` |  |       _` |   __|  _` |  " << std::endl; 
 std::cout << "           |   |  |   |  |  |  (   |      |   |  (   |  |    (   |  |      (   |  |    (   |  " << std::endl;
 std::cout << "          ____/  \\__,_| _| _| \\__,_|     ____/  \\__,_| \\__| \\__,_| \\____| \\__,_| _|   \\__,_|  " << std::endl;
 std::cout << "                                                                                              " << std::endl;
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
 
 std::string nameFileRate  = gConfigParser -> readStringOption("Input::nameFileRate");
 std::string nameFileSyst  = gConfigParser -> readStringOption("Input::nameFileSyst");
 std::string nameFileDataDriven = gConfigParser -> readStringOption("Input::nameFileDataDriven");
 int WP                    = gConfigParser -> readIntOption   ("Input::WP");
 std::vector<std::string> nameSamplesSystFromFile   = gConfigParser -> readStringListOption("Input::nameSamplesSystFromFile");
 std::vector<std::string> nameSamplesSystToBeUsed   = gConfigParser -> readStringListOption("Input::nameSamplesSystToBeUsed");
  
 
 for (int iName = 0; iName < nameSamplesSystFromFile.size(); iName++) {
  std::cout << " nameSamplesSystFromFile[" << iName << "] = " << nameSamplesSystFromFile.at(iName) << std::endl;
 }
 for (int iName = 0; iName < nameSamplesSystFromFile.size(); iName++) {
  std::cout << " nameSamplesSystToBeUsed[" << iName << "] = " << nameSamplesSystToBeUsed.at(iName) << std::endl;
 }
 
 std::string nameOutputFile = gConfigParser -> readStringOption ("Output::nameOutputFile");
 
 ///==== debug flag ====
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  
 
 
 ///==== numSig flag ====
 
 int numSig = 2; //---- default qqH + ggH
 try {
  numSig = gConfigParser -> readIntOption("Input::numSig");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::numSig  " << numSig  << std::endl;  
 
 
 ///==== name bin ====
 std::string nameBin = "ll2j"; //---- default ll2j
 try {
  nameBin = gConfigParser -> readStringOption("Input::nameBin");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::nameBin  " << nameBin  << std::endl;  
 
 
 
 ///==== do injection test ====
 int doInjection = 0; //---- default 0 -> no injection test 
 try {
  doInjection = gConfigParser -> readIntOption("Input::doInjection");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::doInjection  " << doInjection  << std::endl;  
 
 std::vector<std::string> samplesToInject;
 try {
  samplesToInject = gConfigParser -> readStringListOption("Input::samplesToInject");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 for (int iInject = 0; iInject < samplesToInject.size(); iInject++) {
  std::cout << " samplesToInject[" << iInject << "::" << samplesToInject.size() << "] = " << samplesToInject.at(iInject) << std::endl;
 }
 
 std::vector<double> scaleSamplesToInject;
 try {
  scaleSamplesToInject = gConfigParser -> readDoubleListOption("Input::scaleSamplesToInject");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 for (int iInject = 0; iInject < scaleSamplesToInject.size(); iInject++) {
  std::cout << " scaleSamplesToInject[" << iInject << "::" << scaleSamplesToInject.size() << "] = " << scaleSamplesToInject.at(iInject) << std::endl;
 }
 
 
 
 
 ///==== do shape ====
 int doShape = 0; //---- default 0 -> no doShape 
 try {
  doShape = gConfigParser -> readIntOption("Input::doShape");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::doShape  " << doShape  << std::endl;  
 
 
 std::string inputFileDistributions;
 try {
  inputFileDistributions = gConfigParser -> readStringOption("Input::inputFileDistributions");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::inputFileDistributions  " << inputFileDistributions  << std::endl;  
 
 
 
  
 //---- for shape analysis, to deal with Wjets negative weights, remove Wjets if integral < 0 (begin) ----        
 for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
  if (doShape) {
   TFile FileDistributionsToModify(inputFileDistributions.c_str(),"UPDATE");
   TString histoName = Form ("histo_%s",nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str());
   TH1F* histoReference = (TH1F*) FileDistributionsToModify.Get(histoName.Data());
   double prev_integral = histoReference->Integral(-1,-1);
   double prev_integral_bis = prev_integral;
   
   bool doneSomething = false;
   for (int iBin = 0; iBin < histoReference->GetNbinsX(); iBin++) {
    double content = histoReference->GetBinContent(iBin+1);
    if (content < 0) {
     histoReference->SetBinContent(iBin+1, -content); //---> patch for Wjets and negative weight! ... but also for negative errors (how on earth is it possible?!?!) Vg ~ 2e-10 ... it 0 !!
     doneSomething = true;
    }
   }
   
   if (doneSomething) {
    prev_integral_bis = histoReference->Integral(-1,-1);
    histoReference->Write();    
   } 

   if (prev_integral >= 0 && doneSomething) {
    std::cout << " to be changed (bin +/-) : " <<     nameSamplesSystToBeUsed.at (iNameToBeUsed);
    std::cout << " :: >>                     " <<     nameSamplesSystFromFile.at (iNameToBeUsed) << std::endl;
   }
   
   if (prev_integral <  10e-9) { // ---- instead of zero, use this number as threshold for "0"
    std::cout << " to be removed : " <<     nameSamplesSystToBeUsed.at (iNameToBeUsed);
    std::cout << " :: >>           " <<     nameSamplesSystFromFile.at (iNameToBeUsed) << std::endl;
    nameSamplesSystToBeUsed.erase (nameSamplesSystToBeUsed.begin() + iNameToBeUsed);
    nameSamplesSystFromFile.erase (nameSamplesSystFromFile.begin() + iNameToBeUsed);
   }
  }
 }
 
 for (int iName = 0; iName < nameSamplesSystFromFile.size(); iName++) {
  std::cout << " nameSamplesSystFromFile[" << iName << "] = " << nameSamplesSystFromFile.at(iName) << std::endl;
 }
 for (int iName = 0; iName < nameSamplesSystFromFile.size(); iName++) {
  std::cout << " nameSamplesSystToBeUsed[" << iName << "] = " << nameSamplesSystToBeUsed.at(iName) << std::endl;
 }
 //---- for shape analysis, to deal with Wjets negative weights, remove Wjets if integral < 0 (end) ----

 
 
 std::cout << " ---> read samples rate <---- " << std::endl;
 std::cout << "      ::: " << nameFileRate.c_str() << std::endl;
 
 
 
 ///==== get Sample names and rate ====
 std::ifstream FileRate (nameFileRate.c_str()); 
 std::vector<double> rate;
 std::vector<std::string> nameSamples;
 double observed;
 
 int nLine = 0;
 std::string buffer; 
 while(!FileRate.eof()) {
  getline(FileRate,buffer);
  if (debug) std::cout << " buffer = " << buffer << std::endl;
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {
   if (nLine == 0) {
    std::string tempString;
    while ( line >> tempString ) {
     nameSamples.push_back(tempString);
    }
    nLine ++;
   }
   else if (nLine == 1) {
    double tempRate;
    while ( line >> tempRate ) {
     rate.push_back(tempRate);
    }
    nLine ++;
   }
   else {
    line >> observed; //---- observed
   }
  }
 }
 
 std::cout << " ---> read systematics <---- " << std::endl;
 
 ///==== get Systematics names and value ====
 std::ifstream FileSyst (nameFileSyst.c_str()); 
 std::vector<std::vector<double> > Syst;
 std::vector<double> SystFlag;
 std::vector<std::string> nameSyst;
 std::vector<std::string> typeSyst;
 
 while(!FileSyst.eof()) {
  getline(FileSyst,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {
   std::string nameSystTemp;
   line >> nameSystTemp;
   nameSyst.push_back(nameSystTemp);
   
   std::string nameFileSystTemp;
   line >> nameFileSystTemp;
   if (debug) std::cout << " nameFileSystTemp = " << nameFileSystTemp << std::endl;

   std::string TypeSystTemp;
   line >> TypeSystTemp;
   typeSyst.push_back(TypeSystTemp);
   if (debug) std::cout << " TypeSystTemp = " << TypeSystTemp << std::endl;
   
   double  SystFlagTemp;
   line >> SystFlagTemp;
   SystFlag.push_back(SystFlagTemp);
   if (debug) std::cout << " SystFlagTemp = " << SystFlagTemp << std::endl;
   
   
   std::ifstream FileSyst_temp (nameFileSystTemp.c_str()); 
   std::string bufferIn;
   std::vector<std::string> nameSamplesSystDumpFile;
   int iWP = -1;
   while(!FileSyst_temp.eof()) {
    getline(FileSyst_temp,bufferIn);
    if (debug) std::cout << " bufferIn = " << bufferIn << std::endl;
    std::stringstream lineIn( bufferIn );     
    if (bufferIn != ""  && bufferIn.at(0) != '#') {
     //---- get list of samples from systematics File ----
     if (debug) std::cout << " iWP = " << iWP << " WP = " << WP << std::endl;
     if (iWP == -1) { 
      std::string tempString;
      while ( lineIn >> tempString ) {
       nameSamplesSystDumpFile.push_back(tempString);
      }
     }

//      for (int iNS = 0; iNS < nameSamplesSystDumpFile.size(); iNS++) {
//       std::cout << " nameSamplesSystDumpFile(" << iNS << "::" << nameSamplesSystDumpFile.size() << ") = " << nameSamplesSystDumpFile.at(iNS) << std::endl;
//      }

     //---- get systematics only if it is the correct WP ----
     if (iWP == WP) {
      std::vector<int> flagSamplesSystDump;
      if (debug) std::cout << " FilterListNames ... " << std::endl;
//    FilterListNames(std::vector<std::string> &nameSamplesSystFromFile, std::vector<std::string> &nameSamplesDump, std::vector<int> &flagSamplesSystDump){
      FilterListNames(nameSamplesSystFromFile, nameSamplesSystDumpFile, flagSamplesSystDump);      
      for (int iName = 0; iName < nameSamplesSystFromFile.size(); iName++) {
       if (debug) std::cout << " nameSamplesSystToBeUsed[" << iName << "] = " << nameSamplesSystToBeUsed.at(iName) << " ";
       if (debug) std::cout << " flagSamplesSystDump    [" << iName << "] = " << flagSamplesSystDump.at(iName) << " ";
       if (debug) std::cout << std::endl;
      }
      if (debug) std::cout << " ... done " << std::endl;
      
      std::vector<double> vSystTempAll;
      double tempSyst;
      while ( lineIn >> tempSyst ) {
       vSystTempAll.push_back(tempSyst);
      }
      
      if (debug) {
       for (int iSystTempAll = 0; iSystTempAll < vSystTempAll.size(); iSystTempAll++ ) {
       std::cout << " vSystTempAll.at(" << iSystTempAll << ") = " << vSystTempAll.at(iSystTempAll) << std::endl;
       }
      }
      
      std::vector<double> vSystTemp;
      for (uint iName = 0; iName < flagSamplesSystDump.size(); iName++) {
//        if (debug && Syst.size() == 0) std::cout << " flagSamplesSystDump[" << iName << "] = " << flagSamplesSystDump.at(iName) << std::endl;
       if (debug) std::cout << " flagSamplesSystDump[" << iName << "::" <<  flagSamplesSystDump.size() << "] = " << flagSamplesSystDump.at(iName) << std::endl;
       if (debug) std::cout << " vSystTempAll.size() = " << vSystTempAll.size() << std::endl;
       
       if (flagSamplesSystDump.at(iName) != -1) {
        vSystTemp.push_back(vSystTempAll.at(flagSamplesSystDump.at(iName)));
       }
       else {
        vSystTemp.push_back(-1);
       }
      }      
      Syst.push_back(vSystTemp);
     }
     iWP++;
    }
   }
  }
 }
 
 

        
//  for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
//   if (doShape) {
//    TFile FileDistributionsToModify(inputFileDistributions.c_str(),"UPDATE");
//    TString histoName = Form ("histo_%s",nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str());
//    TH1F* histoReference = (TH1F*) FileDistributionsToModify.Get(histoName.Data());
//    bool doneSomething = false;
//    for (int iBin = 0; iBin < histoReference->GetNbinsX(); iBin++) {
//     double content = histoReference->GetBinContent(iBin+1);
//     if (content <= 0) {
//       content = 0;
//       histoReference->SetBinContent(iBin+1, content);
//       doneSomething = true;
//     }
//    }
//    if (doneSomething) {
//     histoReference->Write();
//    }
//   } 
//  }  
 
 std::cout << " ---> read Data Driven <---- " << std::endl; 
 
 ///==== get dataDriven Estimation names and value ====
 std::ifstream FileDataDriven (nameFileDataDriven.c_str()); 
 std::vector<std::vector<double> > DataDrivenResult;
 std::vector<std::string> nameDataDriven;
 std::vector<std::vector<int> > flagDataDrivenSample; //---- if a sample has been modified
 
 std::cout << " nameFileDataDriven = " << nameFileDataDriven.c_str() << std::endl;
 while(!FileDataDriven.eof()) {
  getline(FileDataDriven,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {
   std::string nameDataDrivenTemp;
   line >> nameDataDrivenTemp;
   nameDataDriven.push_back(nameDataDrivenTemp);
   
   std::string nameFileDataDriven_temp;
   line >> nameFileDataDriven_temp;
   if (debug) std::cout << " nameDataDrivenTemp = " << nameDataDrivenTemp.c_str() << std::endl;
   if (debug) std::cout << " nameFileDataDriven_temp = " << nameFileDataDriven_temp.c_str() << std::endl;
   
   line >> nameDataDrivenTemp;
//    nameDataDrivenSample.push_back(nameDataDrivenTemp);
   
   std::ifstream FileDataDriven_temp (nameFileDataDriven_temp.c_str()); 
   std::string bufferIn;
   std::vector<std::string> nameSamplesDataDrivenDumpFile;
   int iWP = -1;
   while(!FileDataDriven_temp.eof()) {
    getline(FileDataDriven_temp,bufferIn);
    if (debug) std::cout << " bufferIn = " << bufferIn << std::endl;
    std::stringstream lineIn( bufferIn );     
    if (bufferIn != ""  && bufferIn.at(0) != '#') {
     //---- get list of samples from data driven File ----
     if (debug) std::cout << " iWP = " << iWP << std::endl;
     if (iWP == -1) { 
      std::string tempString;
      while ( lineIn >> tempString ) {
       nameSamplesDataDrivenDumpFile.push_back(tempString);
      }
     }
     //---- get data driven only if it is the correct WP ----
     if (iWP == WP) {
      std::vector<int> flagSamplesDataDrivenDump;
      FilterListNames(nameSamplesSystFromFile, nameSamplesDataDrivenDumpFile, flagSamplesDataDrivenDump);      
      for (int iName = 0; iName < nameSamplesSystFromFile.size(); iName++) {
       if (debug) std::cout << " nameSamplesSystToBeUsed   [" << iName << "] = " << nameSamplesSystToBeUsed.at(iName) << " ";
       if (debug) std::cout << " flagSamplesDataDrivenDump [" << iName << "] = " << flagSamplesDataDrivenDump.at(iName) << " ";
       if (debug) std::cout << std::endl;
      }
      
      flagDataDrivenSample.push_back(flagSamplesDataDrivenDump);
      
      std::vector<double> vDataDrivenTempAll;
      double tempDataDriven;
      while ( lineIn >> tempDataDriven ) {
       vDataDrivenTempAll.push_back(tempDataDriven);
      }
      std::vector<double> vDataDrivenTemp;
      for (uint iName = 0; iName < flagSamplesDataDrivenDump.size(); iName++) {       
       if (flagSamplesDataDrivenDump.at(iName) != -1) {
        vDataDrivenTemp.push_back(vDataDrivenTempAll.at(flagSamplesDataDrivenDump.at(iName)));
       }
       else {
        vDataDrivenTemp.push_back(-1);
       }
      }      
      DataDrivenResult.push_back(vDataDrivenTemp);
     }
     iWP++;
    }
   }
  }
 }
 
 std::cout << " ---> read rate using Data Driven <---- " << std::endl; 
 //---- update rate using DataDriven estimation ----
 for (unsigned int iDataDriven=0; iDataDriven<DataDrivenResult.size(); iDataDriven++){
  if (debug) std::cout << " iDataDriven = " << iDataDriven << " : " << DataDrivenResult.size() << std::endl;
  for (unsigned int iName = 0; iName<nameSamples.size(); iName++) {
   if (debug) std::cout << " iName = " << iName << " : " << nameSamples.size() << std::endl;
   for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
    if (debug) std::cout << " iNameToBeUsed = " << iNameToBeUsed << " : " << nameSamplesSystToBeUsed.size() << " -> " << nameSamplesSystToBeUsed.at(iNameToBeUsed) << std::endl;
    if (debug) std::cout << " nameSamples.at(" << iName << ") = " << nameSamples.at(iName) << " : nameSamplesSystToBeUsed.at("  << iNameToBeUsed << ") = " << nameSamplesSystToBeUsed.at(iNameToBeUsed) << std::endl;
    
    if (nameSamples.at(iName) == nameSamplesSystToBeUsed.at(iNameToBeUsed)) {
     if (DataDrivenResult.at(iDataDriven).at(iNameToBeUsed) == -1) {
//       std::cout << " data Driven [" << iDataDriven << "] not used for this sample :: " << nameSamplesDataDrivenToBeUsed.at(iName) << std::endl;
     }
     else {
      rate.at(iName) = DataDrivenResult.at(iDataDriven).at(iNameToBeUsed);
      
      
      
      //---- modify integral of reference distribution (begin) ----
      
      if (doShape) {
       TFile FileDistributionsToModify(inputFileDistributions.c_str(),"UPDATE");
       TString histoName = Form ("histo_%s",nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str());
       TH1F* histoReference = (TH1F*) FileDistributionsToModify.Get(histoName.Data());
//        std::cout << " histoName = " << histoName.Data() << std::endl;       
//        std::cout << " histoReference = " << histoReference << std::endl;
       double prev_integral = histoReference->Integral(-1,-1);
       double scale_integral;
       if (prev_integral != 0) scale_integral = rate.at(iName) / prev_integral;
       else scale_integral = 1.;
       std::cout << "       >>> scale :: " << nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str() << " = " << scale_integral << std::endl;       
       if (scale_integral != 1.) {
        histoReference->Scale(scale_integral);
        histoReference->Write();
       }
//        std::cout << " ... done. " << std::endl;
      } 
      //---- modify integral of reference distribution (end) ----

      
     }
    }
   }
  }
 }
 
 
 ///==== Injection test (begin) ====
 ///-- change the observed number of events
 ///-- the observed distribution for shape analysis is taken from background
 ///-- data are used only for datadriven estimation
 
 if (doInjection != 0) {
  
  double rateInjection = 0;
  for (int iInject = 0; iInject < samplesToInject.size(); iInject++) {
   for (unsigned int iName=0; iName<nameSamples.size(); iName++){
    if (debug) std::cout << " iName = " << iName << " : " << nameSamples.size() << " : " << rate.size() << std::endl;
    if (nameSamples.at(iName) == samplesToInject.at(iInject)) {
     double scale = 1.;
     if (scaleSamplesToInject.size() > iInject) scale = scaleSamplesToInject.at(iInject);
     rateInjection += (scale*rate.at(iName));
    }
   }
  }

  double rateAllSamplesExceptSignal = 0;
  for (unsigned int iNameToBeUsed=numSig; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
   if (debug) std::cout << " iNameToBeUsed = " << iNameToBeUsed << " : " << nameSamplesSystToBeUsed.size() << " -> " << nameSamplesSystToBeUsed.at(iNameToBeUsed) << std::endl;
   for (unsigned int iName=0; iName<nameSamples.size(); iName++){
    if (debug) std::cout << " iName = " << iName << " : " << nameSamples.size() << " : " << rate.size() << std::endl;
    if (nameSamples.at(iName) == nameSamplesSystToBeUsed.at(iNameToBeUsed)) {
     rateAllSamplesExceptSignal += rate.at(iName);
    }
   }
  }
  
  observed = rateAllSamplesExceptSignal + rateInjection;
  
  if (doShape) {
   //---- for shape analysis, move DATA to sum background (begin) ----        
   TFile FileDistributionsToModify(inputFileDistributions.c_str(),"UPDATE");
   TString histoNameDATA = Form ("histo_DATA");
   TH1F* histoDATA = (TH1F*) FileDistributionsToModify.Get(histoNameDATA.Data());
   histoDATA -> Reset();
   for (unsigned int iNameToBeUsed=numSig; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
    TString histoName = Form ("histo_%s",nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str());
    TH1F* histoReference = (TH1F*) FileDistributionsToModify.Get(histoName.Data());
    histoDATA -> Add (histoReference);
   }
   
   for (int iInject = 0; iInject < samplesToInject.size(); iInject++) {
    TString histoName = Form ("histo_%s",samplesToInject.at(iInject).c_str());
    TH1F* histoReference = (TH1F*) FileDistributionsToModify.Get(histoName.Data());
    double scale = 1.;
    if (scaleSamplesToInject.size() > iInject) scale = scaleSamplesToInject.at(iInject);
    if (histoReference) histoDATA -> Add (histoReference, scale);
   }
   
   histoDATA->Write();
   //---- for shape analysis, move DATA to sum background (end) ----          
  }
 }

 
 ///==== Injection test (end) ====
 
 
 
 ///==== Write to datacard ====
 
 std::cout << " ---> write datacard <---- " << std::endl;
 std::ofstream myfile; 
 myfile.open (nameOutputFile.c_str());
 std::cout << "Writing to: " << nameOutputFile << std::endl;
 std::cout << std::endl;
 
 
 myfile << "Limit" << std::endl;
 myfile << "imax 1 number of channels" << std::endl;
 myfile << "jmax "<< "*" << " number of samples -1" << std::endl;
 myfile << "kmax "<< "*" << " number of nuisance parameters" << std::endl;
//  myfile << "jmax "<< (nameSamplesSystToBeUsed.size() - 1) << " number of samples -1" << std::endl;
//  myfile << "kmax "<< Syst.size() << " number of nuisance parameters" << std::endl;
 
 
 if (!doShape) {
  myfile << "shapes * * FAKE" << std::endl;
 }
 
 myfile << "-------------------------------------------------" << std::endl;
 myfile << "bin             " << nameBin << "   " << std::endl;
 myfile << "observation   " << observed << std::endl;
 
 if (doShape) {
  myfile << "shapes  *           * shapes/" << inputFileDistributions << "   histo_$PROCESS histo_$PROCESS_$SYSTEMATIC " << std::endl;
  myfile << "shapes  data_obs    * shapes/" << inputFileDistributions << "   histo_DATA " << std::endl;  
 }
 
 
 myfile << "-------------------------------------------------" << std::endl;
 
 
 
 
 std::cout.precision (4);
 myfile.precision (4);
 
 myfile << std::setw (22+7+5+1+3+11+5) << "bin                ";
 for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
  myfile << std::setw (10) << nameBin << "  ";
 }
 myfile << std::endl;

 myfile << std::setw (22+7+5+1+3+11+5) << "process                ";
 for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
  myfile << std::setw (10) << nameSamplesSystToBeUsed.at(iNameToBeUsed) << "  ";
 }
 myfile << std::endl;
 
 myfile << std::setw (22+7+5+1+3+11+5) << "process                ";
 for (int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
//   myfile << std::setw (10) << iNameToBeUsed-1 << "  ";
  myfile << std::setw (10) << iNameToBeUsed-numSig+1 << "  ";  
 }
 myfile << std::endl;
 
 myfile << std::setw (29+5+1+3+11+5) << "rate                 " ;
 for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
  if (debug) std::cout << " iNameToBeUsed = " << iNameToBeUsed << " : " << nameSamplesSystToBeUsed.size() << " -> " << nameSamplesSystToBeUsed.at(iNameToBeUsed) << std::endl;
  for (unsigned int iName=0; iName<nameSamples.size(); iName++){
   if (debug) std::cout << " iName = " << iName << " : " << nameSamples.size() << " : " << rate.size() << std::endl;
   if (nameSamples.at(iName) == nameSamplesSystToBeUsed.at(iNameToBeUsed)) {
    myfile << std::setw (10) << rate.at(iName) << "  ";
//     std::cout << nameSamples.at(iName)  << " => " << std::setw (10) << rate.at(iName) << "  " << std::endl;
   }
  }
 }
 myfile << std::endl;
 
 myfile << "-------------------------------------------------" << std::endl;
  
 
 std::cout << " ---> DC: write systematics <---- " << std::endl;
 std::cout << " ---> DC:: Syst.size() = " << Syst.size() << std::endl;
 
 for (unsigned int iSyst=0; iSyst<Syst.size(); iSyst++){
  myfile << std::setw (25+3+11) << nameSyst.at(iSyst); 
  
  if (typeSyst.at(iSyst) == "gmN") {
   myfile << std::setw (5+5)  << typeSyst.at(iSyst);   
   for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
    for (unsigned int iName = 0; iName<nameSamples.size(); iName++) {
     if (nameSamples.at(iName) == nameSamplesSystToBeUsed.at(iNameToBeUsed)) {
      for (unsigned int iDataDriven=0; iDataDriven<nameDataDriven.size(); iDataDriven++){
       if (nameDataDriven.at(iDataDriven) == nameSyst.at(iSyst)) { //---- if it IS the systematics related to data driven         
        if (DataDrivenResult.at(iDataDriven).at(iNameToBeUsed) != -1) {
         if (debug) std::cout << " nameSyst.at(" << iSyst << ") = " << nameSyst.at(iSyst);
         if (debug) std::cout << " == nameSamples.at(" << iName << ") = " << nameSamples.at(iName);
         if (debug) std::cout << " == nameDataDriven.at(" << iDataDriven << ") = " << nameDataDriven.at(iDataDriven);
         if (debug) std::cout << std::endl;
         std::cout.precision(-1);
         myfile << std::setw (5) << round(rate.at(iName) / Syst.at(iSyst).at(iNameToBeUsed));
         std::cout.precision(4);

//          //---- modify integral of reference distribution (begin) ----
//       if (doShape) {
//        TFile FileDistributionsToModify(inputFileDistributions.c_str(),"UPDATE");
//        TString histoName = Form ("histo_%s",nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str());
//        TH1F* histoReference = (TH1F*) FileDistributionsToModify.Get(histoName.Data());
//        
//        double prev_integral = histoReference->Integral(-1,-1);
//        double scale_integral;
//        if (prev_integral) scale_integral = rate.at(iName) / prev_integral;
//        else scale_integral = 1.;
//        histoReference->Scale(scale_integral);
//        histoReference->Write();
//        
//       } 
//       //---- modify integral of reference distribution (end) ----
         
        }
       }
      }
     }
    }
   }
  }
  else {
   myfile << std::setw (10+5)  << typeSyst.at(iSyst);
  }
  
  
  if (debug) std::cout << " iSyst = " << iSyst << " : " << Syst.size() << std::endl;
  for (unsigned int iNameToBeUsed=0; iNameToBeUsed<nameSamplesSystToBeUsed.size(); iNameToBeUsed++){
   if (debug) std::cout << " iNameToBeUsed = " << iNameToBeUsed << " : " << nameSamplesSystToBeUsed.size() << " -> " << nameSamplesSystToBeUsed.at(iNameToBeUsed) << std::endl;
   for (unsigned int iName = 0; iName<nameSamples.size(); iName++) {
    if (debug) std::cout << " iName = " << iName << " : " << nameSamples.size() << std::endl;
    if (debug) std::cout << " nameSamples.at(" << iName << ") = " << nameSamples.at(iName) << " : nameSamplesSystToBeUsed.at("  << iNameToBeUsed << ") = " << nameSamplesSystToBeUsed.at(iNameToBeUsed) << std::endl;
    
    
    if (nameSamples.at(iName) == nameSamplesSystToBeUsed.at(iNameToBeUsed)) {
     if (debug) std::cout << " >> selected ... " << std::endl;
     
     bool setToZero = false;
     for (unsigned int iDataDriven=0; iDataDriven<nameDataDriven.size(); iDataDriven++){
      if (debug)        std::cout << " same name?? >> " << nameDataDriven.at(iDataDriven) << " =? " << nameSyst.at(iSyst) << std::endl;
      if (debug)        std::cout << " iDataDriven = " << iDataDriven << " :: " << nameDataDriven.size() << " == " << flagDataDrivenSample.size() << std::endl;
      if (debug)        std::cout << " iSyst       = " << iSyst       ;
      if (debug)        std::cout << " ::[" << flagDataDrivenSample.size() << "]" << std::endl;
      if (debug)        std::cout << " :: " << flagDataDrivenSample.at(iDataDriven).size() << std::endl;
      
      if (nameDataDriven.at(iDataDriven) != nameSyst.at(iSyst) &&  //---- if it is NOT the systematics related to data driven         
          flagDataDrivenSample.at(iDataDriven).at(iNameToBeUsed) != -1) { //---- if it IS the sample modified by the datadriven         
          setToZero = true;
          if (SystFlag.at(iSyst) == 1) { //---- "annulla palla di fuoco!" leave the systematics as it is passed to the combination device
           setToZero = false;
          }
      }
     }     
     
     if (debug) std::cout << " going to write ..." << std::endl;
     
     if (Syst.at(iSyst).at(iNameToBeUsed) == -1 || setToZero) {
      myfile << std::setw (10) << " - "  << "  ";
     }
     else {
      
      //---- to be performed only for the systematics that are actually used for this sample!
      //---- if negative values of likelihood (1+/-1 --> low edge = 0 or 1e-10 !)
      //---- then binContent -> - binContent (mild solution)
      if (typeSyst.at(iSyst) == "shape") { 
       TFile FileDistributionsToModify(inputFileDistributions.c_str(),"UPDATE");
       TString histoNameUp = Form ("histo_%s_%sUp",nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str(),nameSyst.at(iSyst).c_str());
       if (debug) std::cout << " histoNameUp = " << histoNameUp.Data() << std::endl;   
       TH1F* histoReferenceUp = (TH1F*) FileDistributionsToModify.Get(histoNameUp.Data());
       if (debug) std::cout << " histoReferenceUp = " << histoReferenceUp << std::endl;
       double prev_integral_Up = 0;
       bool doneSomething = false;
       if (histoReferenceUp) {
        double prev_integral_Up = histoReferenceUp->Integral(-1,-1);
        doneSomething = false;
        for (int iBin = 0; iBin < histoReferenceUp->GetNbinsX(); iBin++) {
         double content = histoReferenceUp->GetBinContent(iBin+1);
         if (content < 0) {
          histoReferenceUp->SetBinContent(iBin+1, -content); //---> patch for Wjets and negative weight! ... but also for negative errors (how on earth is it possible?!?!) Vg ~ 2e-10 ... it 0 !!
          doneSomething = true;
         }
        }    
        if (doneSomething) {
         histoReferenceUp->Write();    
         std::cout << " to be changed (bin +/-) : " <<     nameSamplesSystToBeUsed.at (iNameToBeUsed) << " systematics :: " << nameSyst.at(iSyst) << " Up " << std::endl;
         std::cout << " :: >>                     " <<     nameSamplesSystFromFile.at (iNameToBeUsed) << std::endl;
        }
       }
       TString histoNameDown = Form ("histo_%s_%sDown",nameSamplesSystToBeUsed.at(iNameToBeUsed).c_str(),nameSyst.at(iSyst).c_str());
//        std::cout << " histoNameDown = " << histoNameDown.Data() << std::endl;   
       TH1F* histoReferenceDown = (TH1F*) FileDistributionsToModify.Get(histoNameDown.Data());
//        std::cout << " histoReferenceDown = " << histoReferenceDown << std::endl;
       double prev_integral_Down = 0;
       if (histoReferenceDown) {
        prev_integral_Down = histoReferenceDown->Integral(-1,-1);
        doneSomething = false;
        for (int iBin = 0; iBin < histoReferenceDown->GetNbinsX(); iBin++) {
         double content = histoReferenceDown->GetBinContent(iBin+1);
         if (content < 0) {
          histoReferenceDown->SetBinContent(iBin+1, -content); //---> patch for Wjets and negative weight! ... but also for negative errors (how on earth is it possible?!?!) Vg ~ 2e-10 ... it 0 !!
          doneSomething = true;
         }
        }    
        if (doneSomething) {
         histoReferenceDown->Write();    
         std::cout << " to be changed (bin +/-) : " <<     nameSamplesSystToBeUsed.at (iNameToBeUsed) << " systematics :: " << nameSyst.at(iSyst) << " Down " << std::endl;
         std::cout << " :: >>                     " <<     nameSamplesSystFromFile.at (iNameToBeUsed) << std::endl;
        }
       }
       
       if ( prev_integral_Down <= 10e-9 || prev_integral_Up<=10e-9 ) { // ---- instead of zero, use this number as threshold for "0"
        std::cout << "  to be removed (negative integral)  " <<     nameSamplesSystToBeUsed.at (iNameToBeUsed) << " systematics :: " << nameSyst.at(iSyst) << " " << std::endl;
        std::cout << " :: >>                               " <<     nameSamplesSystFromFile.at (iNameToBeUsed) << std::endl;
        myfile << std::setw (10) << " - "  << "  ";
       }
       else {
        myfile << std::setw (10) << Syst.at(iSyst).at(iNameToBeUsed) << "  ";
       }
       
      }
      //---- (end) check for negative bins ----
      else {
       myfile << std::setw (10) << Syst.at(iSyst).at(iNameToBeUsed) << "  ";
      }
      
     }
     
     if (debug) std::cout << " written ..." << std::endl;
     
    }
    
   }
  } 
  myfile << std::endl;
 }
 
 
 
 myfile << std::endl; 
 
 myfile.close(); 
 
 
 
}


















