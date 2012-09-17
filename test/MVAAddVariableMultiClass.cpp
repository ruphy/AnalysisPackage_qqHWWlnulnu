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


int main(int argc, char** argv) {
 
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
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
 float jetpt1;
 float jetpt2;
 float mjj;
 float detajj;
 float dphilljetjet;
 
 float pt1;
 float pt2;
 float mll;
 float dphill;
 float mth;
 
 float dphillmet;
 float mpmet;
 
 float channel;
 
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
  
  treeJetLepVect[iSample] -> SetBranchAddress("jetpt1",  &jetpt1);
  treeJetLepVect[iSample] -> SetBranchAddress("jetpt2",  &jetpt2);
  treeJetLepVect[iSample] -> SetBranchAddress("mjj",   &mjj);
  treeJetLepVect[iSample] -> SetBranchAddress("detajj", &detajj);
  treeJetLepVect[iSample] -> SetBranchAddress("dphilljetjet", &dphilljetjet);
  treeJetLepVect[iSample] -> SetBranchAddress("pt1", &pt1);
  treeJetLepVect[iSample] -> SetBranchAddress("pt2", &pt2);
  treeJetLepVect[iSample] -> SetBranchAddress("mll", &mll);
  treeJetLepVect[iSample] -> SetBranchAddress("dphill", &dphill);
  treeJetLepVect[iSample] -> SetBranchAddress("mth", &mth);
  treeJetLepVect[iSample] -> SetBranchAddress("dphillmet", &dphillmet);
  treeJetLepVect[iSample] -> SetBranchAddress("mpmet", &mpmet);
  treeJetLepVect[iSample] -> SetBranchAddress("channel", &channel);
  
  
  sprintf(nameFile,"%s/%s%s.root",outputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);    
  outputRootFile[iSample] = new TFile ( nameFile, "RECREATE") ;
  outputRootFile[iSample] -> cd () ;
  cloneTreeJetLepVect[iSample] = treeJetLepVect[iSample] -> CloneTree (0) ;
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
   
//    TMVAreader->AddVariable("jetpt1",       &jetpt1);
//    TMVAreader->AddVariable("jetpt2",       &jetpt2);
//    TMVAreader->AddVariable("mjj",          &mjj);
//    TMVAreader->AddVariable("detajj",       &detajj);
//    TMVAreader->AddVariable("dphilljetjet", &dphilljetjet);
//    TMVAreader->AddVariable("pt1",          &pt1);
//    TMVAreader->AddVariable("pt2",          &pt2);
//    TMVAreader->AddVariable("mll",          &mll);
//    TMVAreader->AddVariable("dphill",       &dphill);
//    TMVAreader->AddVariable("mth",          &mth);
//    TMVAreader->AddVariable("dphillmet",    &dphillmet);
//    TMVAreader->AddVariable("mpmet",        &mpmet);

   Float_t input_variables[1000];
//    float input_variables[1000];
   
//    TMVAreader->AddVariable("jetpt1",       &(input_variables[0]));
//    TMVAreader->AddVariable("jetpt2",       &(input_variables[1]));
//    TMVAreader->AddVariable("mjj",          &(input_variables[2]));
//    TMVAreader->AddVariable("detajj",       &(input_variables[3]));
//    TMVAreader->AddVariable("dphilljetjet", &(input_variables[4]));
//    TMVAreader->AddVariable("pt1",          &(input_variables[5]));
//    TMVAreader->AddVariable("pt2",          &(input_variables[6]));
//    TMVAreader->AddVariable("mll",          &(input_variables[7]));
//    TMVAreader->AddVariable("dphill",       &(input_variables[8]));
//    TMVAreader->AddVariable("mth",          &(input_variables[9]));
//    TMVAreader->AddVariable("dphillmet",    &(input_variables[10]));
//    TMVAreader->AddVariable("mpmet",        &(input_variables[11]));
   
   TMVAreader->AddVariable("jetpt1",       &input_variables[0]);
   TMVAreader->AddVariable("jetpt2",       &input_variables[1]);
   TMVAreader->AddVariable("mjj",          &input_variables[2]);
   TMVAreader->AddVariable("detajj",       &input_variables[3]);
   TMVAreader->AddVariable("dphilljetjet", &input_variables[4]);
   TMVAreader->AddVariable("pt1",          &input_variables[5]);
   TMVAreader->AddVariable("pt2",          &input_variables[6]);
   TMVAreader->AddVariable("mll",          &input_variables[7]);
   TMVAreader->AddVariable("dphill",       &input_variables[8]);
   TMVAreader->AddVariable("mth",          &input_variables[9]);
   TMVAreader->AddVariable("dphillmet",    &input_variables[10]);
   TMVAreader->AddVariable("mpmet",        &input_variables[11]);
   TMVAreader->AddSpectator("channel",     &input_variables[12]);
   
 
   TString myMethodMassList = Form ("%s",vectorMyMethodMassList.at(iMVAMass).c_str());
   TString weightfile = Form ("%s/weights_%s_testVariables/TMVAMulticlass_%s.weights.xml",MVADirectory.c_str(),myMethodMassList.Data(),myMethodList.Data());
   
   std::cout << " myMethodList = " << myMethodList.Data() << std::endl;
   std::cout << " weightfile   = " << weightfile.Data()   << std::endl;
   
//    TString myMethodListBook = Form ("%s",vectorMyMethodList.at(iMVA).c_str());
   
//    TMVAreader->BookMVA( myMethodListBook, weightfile );
   TMVAreader->BookMVA( myMethodList, weightfile );
   
   
   for (int iSample=0; iSample<numberOfSamples; iSample++){ 
    std::cout << " iSample = " << iSample << " :: " << numberOfSamples << std::endl;
    file[iSample] -> cd();
    Double_t MVA_Value;
    TBranch *newBranch;
    
    TString methodName4Tree = Form ("%s_%s_MVAHiggs",myMethodList.Data(),myMethodMassList.Data());
    TString methodName4Tree2 =  Form ("%s_%s_MVAHiggs/D",myMethodList.Data(),myMethodMassList.Data());
    newBranch = cloneTreeJetLepVect[iSample]->Branch(methodName4Tree,&MVA_Value,methodName4Tree2);
//     newBranch = treeJetLepVect[iSample]->Branch(methodName4Tree,&MVA_Value,methodName4Tree2);
    
    
    ///==== loop ====
    Long64_t nentries = treeJetLepVect[iSample]->GetEntries();
    
    for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
     if((iEntry%1000) == 0) std::cout << ">>>>> analysis::GetEntry " << iEntry << " : " << nentries << std::endl;   
     
     treeJetLepVect[iSample]->GetEntry(iEntry);
     
     input_variables[0]  = static_cast<Float_t>(jetpt1);
     input_variables[1]  = static_cast<Float_t>(jetpt2);
     input_variables[2]  = static_cast<Float_t>(mjj);
     input_variables[3]  = static_cast<Float_t>(detajj);
     input_variables[4]  = static_cast<Float_t>(dphilljetjet);
     input_variables[5]  = static_cast<Float_t>(pt1);
     input_variables[6]  = static_cast<Float_t>(pt2);
     input_variables[7]  = static_cast<Float_t>(mll);
     input_variables[8]  = static_cast<Float_t>(dphill);
     input_variables[9]  = static_cast<Float_t>(mth);
     input_variables[10] = static_cast<Float_t>(dphillmet);
     input_variables[11] = static_cast<Float_t>(mpmet);
     input_variables[12] = static_cast<Float_t>(channel);
     
     int num = TMVAreader->EvaluateMulticlass(myMethodList).size();
     double max = -1e9;
     double tempmax;
     int numsel = -1;
     for (int inum = 0; inum<(num-2); inum++) { // il -2 è dovuto a Sig e Bkg che mi salva il training! Uffi!
      tempmax = (TMVAreader->EvaluateMulticlass(myMethodList))[inum];
      if (tempmax > max) {
       max = tempmax;
       numsel = inum;
      }
     }
     MVA_Value = max + 3*numsel;
     
     //      newBranch -> Fill();
     cloneTreeJetLepVect[iSample] -> Fill () ; 
    }
   }
  }
 }
 
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  // save only the new version of the tree
  //   treeJetLepVect[iSample]->Write("", TObject::kOverwrite);
  cloneTreeJetLepVect[iSample] -> SetName (treeName.c_str());
  cloneTreeJetLepVect[iSample] -> AutoSave () ;
  outputRootFile[iSample] -> Close () ;
 }
     
  
}



