#include "treeReader.h"
#include "hFactory.h"
#include "hFunctions.h"
#include "stdHisto.h"
#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "Math/GenVector/VectorUtil.h"
#include "TRandom3.h"
#include <time.h>
#include <sstream>
#include "qqHWWlnulnuUtils.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif



int main(int argc, char** argv)
{ 
 //Check if all nedeed arguments to parse are there                                                                                                                               
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");
 std::string inputFile = gConfigParser -> readStringOption("Input::inputFile");
 
 int entryMOD = gConfigParser -> readIntOption("Input::entryMOD");
 
 double l1_pT;
 double l2_pT;
 double l1_Eta;
 double l2_Eta;
 double DEta_ll;
 double DPhi_ll;
 double M_ll;
 double Z_ll;
 int l1_flavour;
 int l2_flavour;
 
 
 Float_t input_variables_Lep[1000];
 Double_t* MVA_Lep;
 
 TMVA::Reader *TMVAreader_Lep = new TMVA::Reader( "!Color:!Silent" );
 TMVAreader_Lep->AddVariable("log(l1_pT)",&input_variables_Lep[0]);
 TMVAreader_Lep->AddVariable("log(l2_pT)",&input_variables_Lep[1]);
 TMVAreader_Lep->AddVariable("abs(l1_Eta)",&input_variables_Lep[2]);
 TMVAreader_Lep->AddVariable("abs(l2_Eta)",&input_variables_Lep[3]);
 TMVAreader_Lep->AddVariable("l1_Eta*l2_Eta",&input_variables_Lep[4]);
 TMVAreader_Lep->AddVariable("DEta_ll",&input_variables_Lep[5]);
 TMVAreader_Lep->AddVariable("DPhi_ll",&input_variables_Lep[6]);
 TMVAreader_Lep->AddVariable("M_ll",&input_variables_Lep[7]);
 TMVAreader_Lep->AddVariable("abs(Z_ll)",&input_variables_Lep[8]);
 
 TMVAreader_Lep->AddSpectator("l1_flavour",&input_variables_Lep[9]); //==== spectator
 TMVAreader_Lep->AddSpectator("l2_flavour",&input_variables_Lep[10]); //==== spectator
 
  
 
 ///==== book MVA Lep ====
 
 std::vector<std::string> stdstrMethod_Lep;
 try {
  stdstrMethod_Lep = gConfigParser -> readStringListOption ("Lep::Methods");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 std::string OptionalNameSuffix;
 try {
  OptionalNameSuffix = gConfigParser -> readStringOption ("Lep::OptionalNameSuffix");
 }
 catch (char const* exceptionString){
  OptionalNameSuffix = "";
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 std::vector<std::string> stdstrAdditionalInputFile_Lep;
 try {
  stdstrAdditionalInputFile_Lep = gConfigParser -> readStringListOption ("Lep::AdditionalInputFiles");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 if (stdstrMethod_Lep.size() == 0) {
   std::cerr << " ~~~ Attention: no MVA methods selected" << std::endl; 
   return 0;
 }
 
 MVA_Lep = new Double_t [stdstrMethod_Lep.size()];
 TBranch *newBranch[1000];
 
 TFile* file = new TFile(inputFile.c_str(), "update");
 TTree *tree = (TTree*)file->Get("outTreeJetLep");
 tree->SetBranchAddress("l1_pT",&l1_pT);
 tree->SetBranchAddress("l2_pT",&l2_pT);
 tree->SetBranchAddress("l1_Eta",&l1_Eta);
 tree->SetBranchAddress("l2_Eta",&l2_Eta);
 tree->SetBranchAddress("DEta_ll",&DEta_ll);
 tree->SetBranchAddress("DPhi_ll",&DPhi_ll);
 tree->SetBranchAddress("M_qq",&M_ll);
 tree->SetBranchAddress("Z_ll",&Z_ll);
 tree->SetBranchAddress("l1_flavour",&l1_flavour);
 tree->SetBranchAddress("l2_flavour",&l2_flavour);
 
 ///==== add new branches ====
 for (int iMethod=0; iMethod<stdstrMethod_Lep.size(); iMethod++){
  TString methodName = stdstrMethod_Lep.at(iMethod) + "_method_Lep";
  TString weightfile = Form(stdstrAdditionalInputFile_Lep.at(iMethod).c_str());
  TMVAreader_Lep->BookMVA( methodName, weightfile );
  TString methodName4Tree = stdstrMethod_Lep.at(iMethod) + "_Lep" + OptionalNameSuffix;
  TString methodName4Tree2 = stdstrMethod_Lep.at(iMethod) + "_Lep" + OptionalNameSuffix + "/D" ;
  std::cerr << " methodName = " << methodName.Data() << std::endl;
  std::cerr << " methodName4Tree  = " << methodName4Tree.Data() << std::endl;
  std::cerr << " methodName4Tree2 = " << methodName4Tree2.Data() << std::endl;
  newBranch[iMethod] = tree->Branch(methodName4Tree,MVA_Lep+iMethod,methodName4Tree2);
 }
 
 
 ///==== loop ====
 Long64_t nentries = tree->GetEntries();
 
 for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
  if((iEntry%entryMOD) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
  
  tree->GetEntry(iEntry);
  
  input_variables_Lep[0]  = static_cast<Float_t>(log(l1_pT));
  input_variables_Lep[1]  = static_cast<Float_t>(log(l2_pT));
  input_variables_Lep[2]  = static_cast<Float_t>(fabs(l1_Eta));
  input_variables_Lep[3]  = static_cast<Float_t>(fabs(l2_Eta));
  input_variables_Lep[4]  = static_cast<Float_t>(l1_Eta*l2_Eta);
  input_variables_Lep[5]  = static_cast<Float_t>(DEta_ll);
  input_variables_Lep[6]  = static_cast<Float_t>(DPhi_ll);  
  input_variables_Lep[7]  = static_cast<Float_t>(M_ll);
  input_variables_Lep[8]  = static_cast<Float_t>(fabs(Z_ll));
  input_variables_Lep[9]  = static_cast<Float_t>(l1_flavour);  
  input_variables_Lep[10] = static_cast<Float_t>(l2_flavour);  
  
  for (int iMethod=0; iMethod<stdstrMethod_Lep.size(); iMethod++){
   TString methodName = stdstrMethod_Lep.at(iMethod) + "_method_Lep";
   MVA_Lep[iMethod] = TMVAreader_Lep->EvaluateMVA(methodName);
  }  
  for (int iMethod=0; iMethod<stdstrMethod_Lep.size(); iMethod++){
   newBranch[iMethod]->Fill();
  }
 }
 // save only the new version of the tree
 tree->Write("", TObject::kOverwrite);
 
 
 std::cout << " *** end *** " << std::endl;
}

