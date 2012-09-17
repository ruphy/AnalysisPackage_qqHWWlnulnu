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
///   
///    _ _|                       |   
///      |   __ \   __ \   |   |  __| 
///      |   |   |  |   |  |   |  |   
///    ___| _|  _|  .__/  \__,_| \__| 
///                _|                
///   
///   

// std::vector<double> PUWeight;


///                                                                            fileROOT                      name-systematics                        name-suffix-input-file                                                 name-suffix
int readInputShapesFiles(std::string fileInputTrees, std::vector<std::string> & vec_file_root, std::vector<std::string> & vec_name_systematics, std::vector<std::string> & vec_name_suffix_input_file, std::vector<std::string> & vec_name_suffix) {
 std::ifstream inFile(fileInputTrees.c_str());
 std::string buffer;
 char temp[10000];
 std::string tempString;
 while(!inFile.eof()){
  getline(inFile,buffer);
  if (buffer != ""){ ///---> save from empty line at the end!
   if (buffer.at(0) != '#'){   
    std::stringstream line( buffer );
    line >> temp; tempString = temp;
    vec_file_root.push_back(tempString);
    
    line >> temp; tempString = temp;
    if (tempString == "@") tempString = "";
    vec_name_systematics.push_back(tempString);
    
    line >> temp; tempString = temp;
    if (tempString == "@") tempString = "";
    vec_name_suffix_input_file.push_back(tempString);
    
    line >> temp; tempString = temp;    
    if (tempString == "@") tempString = "";
    vec_name_suffix.push_back(tempString);
   } 
  }
 }
 return vec_file_root.size();
 
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
 std::cout << "           __ )         _)  |      |      __ \\          |            ___|                  |  " << std::endl;
 std::cout << "           __ \\   |   |  |  |   _` |      |   |   _` |  __|   _` |  |       _` |   __|  _` |  " << std::endl; 
 std::cout << "           |   |  |   |  |  |  (   |      |   |  (   |  |    (   |  |      (   |  |    (   |  " << std::endl;
 std::cout << "          ____/  \\__,_| _| _| \\__,_|     ____/  \\__,_| \\__| \\__,_| \\____| \\__,_| _|   \\__,_|  " << std::endl;
 std::cout << "                                                                                              " << std::endl;
 std::cout << "          " << std::endl;
 std::cout << "          " << std::endl;
 std::cout << "                                                     " << std::endl;             
 std::cout << "                                                     " << std::endl;             
 std::cout << "              _ _|                       |           " << std::endl;
 std::cout << "                |   __ \\   __ \\   |   |  __|         " << std::endl; 
 std::cout << "                |   |   |  |   |  |   |  |           " << std::endl;   
 std::cout << "              ___| _|  _|  .__/  \\__,_| \\__|         " << std::endl; 
 std::cout << "                          _|                         " << std::endl;                
 std::cout << "                                                     " << std::endl;             
 std::cout << "                                                     " << std::endl;
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
 
 std::string fileInputTrees  = gConfigParser -> readStringOption("Input::fileInputTrees");
 
 int iVar  = gConfigParser -> readIntOption("Input::iVar");
 int iCut  = gConfigParser -> readIntOption("Input::iCut");
 
 std::vector<std::string> nameSamples   = gConfigParser -> readStringListOption("Input::nameSamples"); 
 
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
 
 
 ///==== debug flag ====
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  
 
 
 
 
 TString toRemove = Form("rm %s",OutFileName.c_str());
 gSystem->Exec(toRemove);  
 
 TFile outFile(OutFileName.c_str(),"RECREATE");
 outFile.cd(); 

 TFile tempOutFile("temporaneo.root","RECREATE");
 
 //  [iName][iSyst]
 TH1F* histo      [131][101];
 
 
 
 ///      fileROOT         name-systematics    name-suffix
 std::vector<std::string> vec_file_root;
 std::vector<std::string> vec_name_systematics;
 std::vector<std::string> vec_name_suffix_input_file;
 std::vector<std::string> vec_name_suffix;
 
 readInputShapesFiles(fileInputTrees, vec_file_root, vec_name_systematics, vec_name_suffix_input_file, vec_name_suffix);
 
 if (debug) std::cout << " nameSamples.size()   = " << nameSamples.size()   << std::endl;
 if (debug) std::cout << " vec_file_root.size() = " << vec_file_root.size() << std::endl;
  
 for (unsigned int iName=0; iName<nameSamples.size(); iName++){ 
  for (unsigned int iSyst=0; iSyst<vec_file_root.size(); iSyst++){ 
   if (debug) std::cout << " vec_file_root.at(" << iSyst << ").c_str() = " << vec_file_root.at(iSyst).c_str() << std::endl;
   TFile inFile(vec_file_root.at(iSyst).c_str(),"READ");
//    TString nameHisto = Form("Data/%s_%d_%d_Tot_temp",nameSamples.at(iName).c_str(),iCut, iVar);
   TString nameHisto = Form("Data/%s_%d_%d%s",nameSamples.at(iName).c_str(),iCut, iVar, vec_name_suffix_input_file.at(iSyst).c_str());
   if (debug) std::cout << " nameHisto[" << iName << "][" << iSyst << "] = " << nameHisto.Data() << std::endl;
   tempOutFile.cd();  
   histo[iName][iSyst] = 0;
   if (inFile.Get(nameHisto.Data())) {
    histo[iName][iSyst] = (TH1F*) ((TH1F*) inFile.Get(nameHisto.Data()))->Clone();
   
   //---- check if histogram is present
   if (debug) std::cout << " histo[" << iName << "][" << iSyst << "] = " << histo[iName][iSyst] << std::endl;
   if (debug) std::cout << " -> Got nameHisto[" << iName << "][" << iSyst << "] = " << nameHisto.Data() << " = " << histo[iName][iSyst] << std::endl;
   TString newNameHisto;
   
   if (vec_name_suffix.at(iSyst) != "")  {
    newNameHisto = Form("histo_%s%s_%s_%s",nameSamples.at(iName).c_str(),vec_name_systematics.at(iSyst).c_str(),nameSamples.at(iName).c_str(),vec_name_suffix.at(iSyst).c_str());
   
    size_t found;
    found = nameSamples.at(iName).find("VH-");   
    if ( found != std::string::npos )   newNameHisto = Form("histo_%s%s_VH_%s",nameSamples.at(iName).c_str(),vec_name_systematics.at(iSyst).c_str(),vec_name_suffix.at(iSyst).c_str());
    found = nameSamples.at(iName).find("ggH-");   
    if ( found != std::string::npos )   newNameHisto = Form("histo_%s%s_ggH_%s",nameSamples.at(iName).c_str(),vec_name_systematics.at(iSyst).c_str(),vec_name_suffix.at(iSyst).c_str());  
    found = nameSamples.at(iName).find("qqH-");   
    if ( found != std::string::npos )   newNameHisto = Form("histo_%s%s_qqH_%s",nameSamples.at(iName).c_str(),vec_name_systematics.at(iSyst).c_str(),vec_name_suffix.at(iSyst).c_str());

   }
   else  {
    newNameHisto = Form("histo_%s%s",   nameSamples.at(iName).c_str(),vec_name_systematics.at(iSyst).c_str());
   }
   
   //    histo_$PROCESS histo_$PROCESS_$SYSTEMATIC
   histo[iName][iSyst] -> SetName  (newNameHisto.Data());
   histo[iName][iSyst] -> SetTitle (newNameHisto.Data());
   if (debug) std::cout << " -> new name nameHisto[" << iName << "][" << iSyst << "] = " << newNameHisto.Data() << " = " << histo[iName][iSyst] -> GetName() << std::endl;
   }
  }
 }
 
 if (debug) std::cout << " writing ... " << std::endl;
 if (debug) std::cout << " file = " << outFile.GetName() << std::endl;
 
 outFile.cd(); 
 for (unsigned int iName=0; iName<nameSamples.size(); iName++){ 
  for (unsigned int iSyst=0; iSyst<vec_file_root.size(); iSyst++){ 
   if (debug) std::cout << "    write [" << iName << "][" << iSyst << "]" ;
   if (debug) std::cout << "    --> " << histo[iName][iSyst] << std::endl ;
   if (histo[iName][iSyst] ) if (debug) std::cout << " = " << histo[iName][iSyst] -> GetTitle() << std::endl;
   if (histo[iName][iSyst] ) if (debug) std::cout << " = " << histo[iName][iSyst] -> GetName() << std::endl;
   if (histo[iName][iSyst] ) histo[iName][iSyst] -> Write ();
  }
 }
 
 std::cout << std::endl;
 if (debug) std::cout << " writing (end) " << std::endl;
 
 outFile.Close();
 
 
 toRemove = Form("rm temporaneo.root");
 gSystem->Exec(toRemove);  
 
 
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << ">>>>> Written in File :   " << OutFileName  << std::endl;  
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
 
 
}





