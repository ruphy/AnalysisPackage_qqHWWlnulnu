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

#include "TSystem.h"



#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif


///     
///        ___|   |                               \  |   ___|         /      __ \     \  __ __|   \    
///      \___ \   __ \    _` |  __ \    _ \      |\/ |  |            /       |   |   _ \    |    _ \   
///            |  | | |  (   |  |   |   __/      |   |  |           /        |   |  ___ \   |   ___ \  
///      _____/  _| |_| \__,_|  .__/  \___|     _|  _| \____|     _/        ____/ _/    _\ _| _/    _\ 
///                            _|                                                                      
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
 TDRStyle();
 
 gStyle->SetPadTopMargin(0.11);
 gStyle->SetPadLeftMargin(0.07);
 gStyle->SetPadRightMargin(0.23);
 gStyle->cd(); 
 
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "         " << std::endl;
 std::cout << "           ___|   |                               \\  |   ___|         /      __ \\     \\  __ __|   \\          " << std::endl;
 std::cout << "         \\___ \\   __ \\    _` |  __ \\    _ \\      |\\/ |  |            /       |   |   _ \\    |    _ \\         " << std::endl;   
 std::cout << "               |  | | |  (   |  |   |   __/      |   |  |           /        |   |  ___ \\   |   ___ \\        " << std::endl;  
 std::cout << "         _____/  _| |_| \\__,_|  .__/  \\___|     _|  _| \\____|     _/        ____/ _/    _\\ _| _/    _\\       " << std::endl; 
 std::cout << "                               _|                                                                            " << std::endl;                                                                      
 std::cout << " " << std::endl;        
 std::cout << " " << std::endl;      
 std::cout << "         ___|                |                            |   _)                       " << std::endl;
 std::cout << "       \\___ \\   |   |   __|  __|   _ \\  __ `__ \\    _` |  __|  |   __|    __|          " << std::endl; 
 std::cout << "             |  |   | \\__ \\  |     __/  |   |   |  (   |  |    |  (    \\__ \\           " << std::endl; 
 std::cout << "       _____/  \\__, | ____/ \\__| \\___| _|  _|  _| \\__,_| \\__| _| \\___| ____/           " << std::endl;  
 std::cout << "               ____/                                                                   " << std::endl;                                                   
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
 
 int NumShapes  = gConfigParser -> readIntOption("Input::NumShapes");
 int NumCuts    = gConfigParser -> readIntOption("Input::NumCuts");
 
 std::vector<std::string> nameSamples   = gConfigParser -> readStringListOption("Input::nameSamples"); 

 std::string fileInput   = gConfigParser -> readStringOption("Input::fileInput");
 
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  

 
 //  [iName][iCut][iVar]
 TH1F* histo      [131][40][5];
 //  [iName][iCut][iVar][iBin]
 TH1F* histo_up   [131][40][5][10];
 TH1F* histo_down [131][40][5][10];
 
 
 TFile inFile(fileInput.c_str(),"READ");
 
 

 TString toRemove = Form("rm %s",OutFileName.c_str());
 gSystem->Exec(toRemove);  
 
 TFile outFile(OutFileName.c_str(),"RECREATE");
 outFile.cd();
 outFile.mkdir("Data");
 outFile.cd("Data"); 
 
 TFile tempOutFile("temporaneo.root","RECREATE");
 
 for (unsigned int iVar = 0; iVar<NumShapes; iVar++){
  double min = -999;
  double max = -999;
  int   nbin = -999;
  for (unsigned int iName=0; iName<nameSamples.size(); iName++){ 
   for (unsigned int iCut = 0; iCut<NumCuts; iCut++){
    
    TString nameHisto = Form("Data/%s_%d_%d_Tot_temp",nameSamples.at(iName).c_str(),iCut, iVar);
    
//     std::cout << "nameHisto[" << iName << "][" << iCut << "][" << iVar << "] = " << nameHisto.Data() << std::endl;
    
    tempOutFile.cd();  
    histo[iName][iCut][iVar] = (TH1F*) inFile.Get(nameHisto.Data());

    if (min  == -999) min = histo[iName][iCut][iVar] -> GetBinLowEdge(1);
    if (max  == -999) max = histo[iName][iCut][iVar] -> GetBinLowEdge(histo[iName][iCut][iVar]->GetNbinsX()+1);
    if (nbin == -999) nbin = histo[iName][iCut][iVar] -> GetNbinsX();
    
    for (int iBin = 0; iBin<nbin; iBin++){
     
     TString nameHisto_up = Form("%s_%d_%d_%d_up",nameSamples.at(iName).c_str(),iCut,iVar,iBin);
     TString nameHisto_down = Form("%s_%d_%d_%d_down",nameSamples.at(iName).c_str(),iCut,iVar,iBin);
     
     histo_down [iName][iCut][iVar][iBin] = new TH1F(nameHisto_down.Data(),nameHisto_down.Data(),nbin,min,max);
     histo_up   [iName][iCut][iVar][iBin] = new TH1F(nameHisto_up.Data()  ,nameHisto_up.Data()  ,nbin,min,max);
     
     for (int iBin2 = 0; iBin2<nbin; iBin2++){
      if (histo[iName][iCut][iVar]) {
       double mean = histo[iName][iCut][iVar] -> GetBinContent (iBin2+1);
       double err  = histo[iName][iCut][iVar] -> GetBinError (iBin2+1);
       double up = mean;
       if (iBin == iBin2) up = mean + err;
       double down = mean;
       if (iBin == iBin2) down = mean - err;
       histo_down[iName][iCut][iVar][iBin] -> SetBinContent(iBin2+1,down);
       histo_up  [iName][iCut][iVar][iBin] -> SetBinContent(iBin2+1,up);
      }
     }
    }
    
   }
  }
 }
 
 
 std::cout << " ... writing ... " << std::endl;
 
 
 outFile.cd();
 outFile.cd("Data");  
 for (unsigned int iName=0; iName<nameSamples.size(); iName++){ 
  std::cout << " name[" << iName << "] = " << nameSamples.at(iName) << std::endl;
  for (unsigned int iCut = 0; iCut<NumCuts; iCut++){
//    std::cout << ">>  Cut[" << iCut << "]" << std::endl;
   for (unsigned int iVar = 0; iVar<NumShapes; iVar++){
//     std::cout << ">> >>  Var[" << iVar << "]" << std::endl;
    if (histo[iName][iCut][iVar]) {
     int nbin = histo[iName][iCut][iVar] -> GetNbinsX();
     for (int iBin = 0; iBin<nbin; iBin++){     
      histo_down [iName][iCut][iVar][iBin] -> Write();
      histo_up   [iName][iCut][iVar][iBin] -> Write();
     }
     TString nameHisto = Form("%s_%d_%d",nameSamples.at(iName).c_str(),iCut, iVar);
     histo      [iName][iCut][iVar] -> SetName(nameHisto.Data());
     histo      [iName][iCut][iVar] -> Write();
    }
   }
  }
 }
 
 std::cout << " ... writing (end) ... " << std::endl;

 outFile.Close();
 

 toRemove = Form("rm temporaneo.root");
 gSystem->Exec(toRemove);  
 
 
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << ">>>>> Written in File :   " << OutFileName  << std::endl;  
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
    
 
}


















