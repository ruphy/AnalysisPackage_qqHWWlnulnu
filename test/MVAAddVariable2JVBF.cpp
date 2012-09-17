// 
// Template from http://root.cern.ch/svn/root/trunk/tmva/test/TMVAClassification.C
// 

#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "../test/Read.cc"

#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"

#include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

#include "TMVA/Reader.h"


///     
///     
///        \  | \ \     /  \            \         |      |     \ \     /            _)         |      |           ___ \       |     \ \     /  __ )   ____| 
///       |\/ |  \ \   /  _ \          _ \     _` |   _` |      \ \   /  _` |   __|  |   _` |  __ \   |   _ \        ) |      |      \ \   /   __ \   |     
///       |   |   \ \ /  ___ \        ___ \   (   |  (   |       \ \ /  (   |  |     |  (   |  |   |  |   __/       __/   \   |       \ \ /    |   |  __|   
///      _|  _|    \_/ _/    _\     _/    _\ \__,_| \__,_|        \_/  \__,_| _|    _| \__,_| _.__/  _| \___|     _____| \___/         \_/    ____/  _|     
///                                                                                                                                                         
///     




int main(int argc, char** argv) {
 
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << "      " << std::endl;
 std::cout << "        \\  | \\ \\     /  \\            \\         |      |     \\ \\     /            _)         |      |           ___ \\       |     \\ \\     /  __ )   ____|  " << std::endl;
 std::cout << "       |\\/ |  \\ \\   /  _ \\          _ \\     _` |   _` |      \\ \\   /  _` |   __|  |   _` |  __ \\   |   _ \\        ) |      |      \\ \\   /   __ \\   |      " << std::endl;     
 std::cout << "       |   |   \\ \\ /  ___ \\        ___ \\   (   |  (   |       \\ \\ /  (   |  |     |  (   |  |   |  |   __/       __/   \\   |       \\ \\ /    |   |  __|    " << std::endl;
 std::cout << "      _|  _|    \\_/ _/    _\\     _/    _\\ \\__,_| \\__,_|        \\_/  \\__,_| _|    _| \\__,_| _.__/  _| \\___|     _____| \\___/         \\_/    ____/  _|      " << std::endl;
 std::cout << "                                                                                                                                                          " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 
 
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");
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
 
 
 //==== list of methods
 std::string              MVADirectory           = gConfigParser -> readStringOption    ("Options::MVADirectory");
 std::vector<std::string> vectorMyMethodList     = gConfigParser -> readStringListOption("Options::MVAmethods");
 std::vector<std::string> vectorMyMethodMassList = gConfigParser -> readStringListOption("Options::MVAmethodsMass");
 
 std::string outputDirectory = gConfigParser -> readStringOption("Output::outputDirectory");
 
 //---- variables 
 
 //-- by YY --
 float pt1;
 float pt2;
 float dphill;
 float drll;
 float mll;
 float channel;
 float mth;
 float mjj;
 float detajj;
 float jeteta1;
 
 
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 TFile* outputRootFile[500];
 TTree* cloneTreeJetLepVect[500];
 
 
 TTree *treeJetLepVect[500];
 TFile* file[500];
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 
 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
 
 double Normalization[1000];
 double xsection[1000];
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
  
  file[iSample] = new TFile(nameFile, "READ");
  
  treeJetLepVect[iSample] = (TTree*) file[iSample]->Get(treeName.c_str());
  char nameTreeJetLep[100];
  sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
  treeJetLepVect[iSample]->SetName(nameTreeJetLep);
  
  
  
  treeJetLepVect[iSample] -> SetBranchAddress("pt1",  &pt1);
  treeJetLepVect[iSample] -> SetBranchAddress("pt2",  &pt2);
  treeJetLepVect[iSample] -> SetBranchAddress("dphill",   &dphill);
  treeJetLepVect[iSample] -> SetBranchAddress("drll", &drll);
  treeJetLepVect[iSample] -> SetBranchAddress("mll", &mll);
  treeJetLepVect[iSample] -> SetBranchAddress("channel", &channel);
  treeJetLepVect[iSample] -> SetBranchAddress("mth", &mth);
  treeJetLepVect[iSample] -> SetBranchAddress("mjj", &mjj);
  treeJetLepVect[iSample] -> SetBranchAddress("detajj", &detajj);
  treeJetLepVect[iSample] -> SetBranchAddress("jeteta1", &jeteta1);
  
  
  sprintf(nameFile,"%s/%s%s.root",outputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);    
  outputRootFile[iSample] = new TFile ( nameFile, "RECREATE") ;
  outputRootFile[iSample] -> cd () ;
  cloneTreeJetLepVect[iSample] = treeJetLepVect[iSample] -> CloneTree (0) ;
 }
 
 
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  file[iSample] -> cd();
  ///==== loop ====
  Long64_t nentries = treeJetLepVect[iSample]->GetEntries();
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   treeJetLepVect[iSample]->GetEntry(iEntry);
   cloneTreeJetLepVect[iSample] -> Fill () ; 
  }
 }
 
 
 /**
  * cycle on MVA (method-mass)
  * * cycle on samples
  * * * cycle on events
  */
 
 for (int iMVA = 0; iMVA < vectorMyMethodList.size(); iMVA++) {
  std::cout << " vectorMyMethodList[" << iMVA << "] = " << vectorMyMethodList.at(iMVA) << std::endl;
  TString myMethodList = Form ("%s",vectorMyMethodList.at(iMVA).c_str());
  for (int iMVAMass = 0; iMVAMass < vectorMyMethodMassList.size(); iMVAMass++) {
   std::cout << " vectorMyMethodMassList[" << iMVAMass << "] = " << vectorMyMethodMassList.at(iMVAMass) << std::endl;
   
   TMVA::Reader *TMVAreader = new TMVA::Reader( "!Color:!Silent" );
   Float_t input_variables[1000];
      
   TMVAreader->AddVariable("lep1pt",    &input_variables[0]);
   TMVAreader->AddVariable("lep2pt",    &input_variables[1]);
   TMVAreader->AddVariable("dPhi",      &input_variables[2]);
   TMVAreader->AddVariable("dR",        &input_variables[3]);
   TMVAreader->AddVariable("dilmass",   &input_variables[4]);
   TMVAreader->AddVariable("type",      &input_variables[5]);
   TMVAreader->AddVariable("mt",        &input_variables[6]);
   TMVAreader->AddVariable("mjj",       &input_variables[7]);
   TMVAreader->AddVariable("detajj",    &input_variables[8]);   
   TMVAreader->AddVariable("jet1eta",   &input_variables[9]);
   
   TString myMethodMassList = Form ("%s",vectorMyMethodMassList.at(iMVAMass).c_str());
   TString weightfile = Form ("%s/weights_%s_testVariables/TMVAClassification_%s.weights.xml",MVADirectory.c_str(),myMethodMassList.Data(),myMethodList.Data());
   
   std::cout << " myMethodList = " << myMethodList.Data() << std::endl;
   std::cout << " weightfile   = " << weightfile.Data()   << std::endl;
   TMVAreader->BookMVA( myMethodList, weightfile );
   
   
   for (int iSample=0; iSample<numberOfSamples; iSample++){ 
    std::cout << " iSample = " << iSample << " :: " << numberOfSamples << std::endl;
    file[iSample] -> cd();
    Double_t MVA_Value;
    TBranch *newBranch;
    
    TString methodName4Tree = Form ("%s_%s_MVAHiggs",myMethodList.Data(),myMethodMassList.Data());
    TString methodName4Tree2 =  Form ("%s_%s_MVAHiggs_2JVBF/D",myMethodList.Data(),myMethodMassList.Data());
    newBranch = cloneTreeJetLepVect[iSample]->Branch(methodName4Tree,&MVA_Value,methodName4Tree2);
    
    
    ///==== loop ====
    Long64_t nentries = treeJetLepVect[iSample]->GetEntries();
    
    for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
     if((iEntry%1000) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
     
     treeJetLepVect[iSample]->GetEntry(iEntry);
     
     input_variables[0]  = static_cast<Float_t>(pt1);
     input_variables[1]  = static_cast<Float_t>(pt2);
     input_variables[2]  = static_cast<Float_t>(dphill);
     input_variables[3]  = static_cast<Float_t>(drll);
     input_variables[4]  = static_cast<Float_t>(mll);
     
     float smurfChannel = -1;
     if ( channel == 0 ) smurfChannel = 0 ;
     if ( channel == 1 ) smurfChannel = 3 ;
     if ( channel == 2 ) smurfChannel = 2 ;
     if ( channel == 3 ) smurfChannel = 1 ;
     input_variables[5]  = static_cast<Float_t>(smurfChannel);
     
     input_variables[6]  = static_cast<Float_t>(mth);
     input_variables[7]  = static_cast<Float_t>(mjj);
     input_variables[8]  = static_cast<Float_t>(detajj);
     input_variables[9]  = static_cast<Float_t>(jeteta1);
     
     MVA_Value = TMVAreader->EvaluateMVA(myMethodList);
     
     newBranch -> Fill();
     
    }
   }
  }
 }
 
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  outputRootFile[iSample]->cd();
  
  // save only the new version of the tree
  //   treeJetLepVect[iSample]->Write("", TObject::kOverwrite);
  cloneTreeJetLepVect[iSample] -> SetName (treeName.c_str());
  //   cloneTreeJetLepVect[iSample] -> AutoSave () ;
  
  cloneTreeJetLepVect[iSample]->Write(treeName.c_str(),TObject::kOverwrite);
  
  outputRootFile[iSample] -> Close () ;
 }
 
 
}



