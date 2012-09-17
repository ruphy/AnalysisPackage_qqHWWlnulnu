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
 
 double q1_pT;
 double q2_pT;
 double q1_Eta;
 double q2_Eta;
 double DEta_qq;
 double DPhi_qq;
 double M_qq;
 int CJV_30;
 double q1_bTag_trackCountingHighPurBJetTags;
 double q2_bTag_trackCountingHighPurBJetTags;

 
 
 Float_t input_variables_Jet[1000];
 Double_t* MVA_Jet;
 
 TMVA::Reader *TMVAreader_Jet = new TMVA::Reader( "!Color:!Silent" );
 TMVAreader_Jet->AddVariable("log(q1_pT)",&input_variables_Jet[0]);
 TMVAreader_Jet->AddVariable("log(q2_pT)",&input_variables_Jet[1]);
 TMVAreader_Jet->AddVariable("abs(q1_Eta)",&input_variables_Jet[2]);
 TMVAreader_Jet->AddVariable("abs(q2_Eta)",&input_variables_Jet[3]);
 TMVAreader_Jet->AddVariable("q1_Eta*q2_Eta",&input_variables_Jet[4]);
 TMVAreader_Jet->AddVariable("DEta_qq",&input_variables_Jet[5]);
 TMVAreader_Jet->AddVariable("DPhi_qq",&input_variables_Jet[6]);
 TMVAreader_Jet->AddVariable("log(M_qq)",&input_variables_Jet[7]);
 TMVAreader_Jet->AddSpectator("q1_bTag_trackCountingHighPurBJetTags",&input_variables_Jet[8]); //==== spectator
 TMVAreader_Jet->AddSpectator("q2_bTag_trackCountingHighPurBJetTags",&input_variables_Jet[9]); //==== spectator
 TMVAreader_Jet->AddSpectator("CJV_30",&input_variables_Jet[10]);
 
  
 
 ///==== book MVA Jet ====
 
 std::vector<std::string> stdstrMethod_Jet;
 try {
  stdstrMethod_Jet = gConfigParser -> readStringListOption ("Jet::Methods");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 std::string OptionalNameSuffix;
 try {
  OptionalNameSuffix = gConfigParser -> readStringOption ("Jet::OptionalNameSuffix");
 }
 catch (char const* exceptionString){
  OptionalNameSuffix = "";
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 std::vector<std::string> stdstrAdditionalInputFile_Jet;
 try {
  stdstrAdditionalInputFile_Jet = gConfigParser -> readStringListOption ("Jet::AdditionalInputFiles");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 
 if (stdstrMethod_Jet.size() == 0) {
   std::cerr << " ~~~ Attention: no MVA methods selected" << std::endl; 
   return 0;
 }
 
 MVA_Jet = new Double_t [stdstrMethod_Jet.size()];
 TBranch *newBranch[1000];
 
 TFile* file = new TFile(inputFile.c_str(), "update");
 TTree *tree = (TTree*)file->Get("outTreeJetLep");
 tree->SetBranchAddress("q1_pT",&q1_pT);
 tree->SetBranchAddress("q2_pT",&q2_pT);
 tree->SetBranchAddress("q1_Eta",&q1_Eta);
 tree->SetBranchAddress("q2_Eta",&q2_Eta);
 tree->SetBranchAddress("DEta_qq",&DEta_qq);
 tree->SetBranchAddress("DPhi_qq",&DPhi_qq);
 tree->SetBranchAddress("M_qq",&M_qq);
 tree->SetBranchAddress("CJV_30",&CJV_30);
 tree->SetBranchAddress("q1_bTag_trackCountingHighPurBJetTags",&q1_bTag_trackCountingHighPurBJetTags);
 tree->SetBranchAddress("q2_bTag_trackCountingHighPurBJetTags",&q2_bTag_trackCountingHighPurBJetTags);
 
 
 ///==== add new branches ====
 for (int iMethod=0; iMethod<stdstrMethod_Jet.size(); iMethod++){
  TString methodName = stdstrMethod_Jet.at(iMethod) + "_method_Jet";
  TString weightfile = Form(stdstrAdditionalInputFile_Jet.at(iMethod).c_str());
  TMVAreader_Jet->BookMVA( methodName, weightfile );
  TString methodName4Tree = stdstrMethod_Jet.at(iMethod) + "_Jet" + OptionalNameSuffix;
  TString methodName4Tree2 = stdstrMethod_Jet.at(iMethod) + "_Jet" + OptionalNameSuffix + "/D" ;
  std::cerr << " methodName = " << methodName.Data() << std::endl;
  std::cerr << " methodName4Tree  = " << methodName4Tree.Data() << std::endl;
  std::cerr << " methodName4Tree2 = " << methodName4Tree2.Data() << std::endl;
  newBranch[iMethod] = tree->Branch(methodName4Tree,MVA_Jet+iMethod,methodName4Tree2);
 }
 
 
 ///==== loop ====
 Long64_t nentries = tree->GetEntries();
 
 for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
  if((iEntry%entryMOD) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
  
  tree->GetEntry(iEntry);
  
  input_variables_Jet[0] = static_cast<Float_t>(log(q1_pT));
  input_variables_Jet[1] = static_cast<Float_t>(log(q2_pT));
  input_variables_Jet[2] = static_cast<Float_t>(fabs(q1_Eta));
  input_variables_Jet[3] = static_cast<Float_t>(fabs(q2_Eta));
  input_variables_Jet[4] = static_cast<Float_t>(q1_Eta*q2_Eta);
  input_variables_Jet[5] = static_cast<Float_t>(DEta_qq);
  input_variables_Jet[6] = static_cast<Float_t>(DPhi_qq);  
  input_variables_Jet[7] = static_cast<Float_t>(log(M_qq));
  input_variables_Jet[8] = static_cast<Float_t>(q1_bTag_trackCountingHighPurBJetTags);
  input_variables_Jet[9] = static_cast<Float_t>(q2_bTag_trackCountingHighPurBJetTags);
  input_variables_Jet[10] = static_cast<Float_t>(CJV_30);
  
  for (int iMethod=0; iMethod<stdstrMethod_Jet.size(); iMethod++){
   TString methodName = stdstrMethod_Jet.at(iMethod) + "_method_Jet";
   MVA_Jet[iMethod] = TMVAreader_Jet->EvaluateMVA(methodName);
  }  
  for (int iMethod=0; iMethod<stdstrMethod_Jet.size(); iMethod++){
   newBranch[iMethod]->Fill();
  }
 }
 // save only the new version of the tree
 tree->Write("", TObject::kOverwrite);
 
 
 std::cout << " *** end *** " << std::endl;
}

