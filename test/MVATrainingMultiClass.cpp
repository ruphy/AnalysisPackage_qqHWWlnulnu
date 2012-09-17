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

#include "TMVAMultiClassGui.C"
#include "TMVA/MethodCategory.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif



int main(int argc, char** argv) { 
  
  if(argc != 2)
  {
   std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName      MVAconfigFileName" << std::endl ;
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
  
  
  
  double LUMI = gConfigParser -> readDoubleOption("Options::Lumi");
  
  std::vector<std::string> SignalName;
  SignalName = gConfigParser -> readStringListOption("Options::SignalName");
  
  for (int iSignalSample=0; iSignalSample<SignalName.size(); iSignalSample++){ 
   std::cout << " Signal[" << iSignalSample << "] = " << SignalName.at(iSignalSample) << std::endl;
  }
  
  std::string nameWeight = "1"; 
  try {
   nameWeight = gConfigParser -> readStringOption("Options::nameWeight");
  }
  catch (char const* exceptionString){
   std::cerr << " exception = " << exceptionString << std::endl;
  }
  std::cout << ">>>>> Input::nameWeight  " << nameWeight  << std::endl;  
  
  
  
  TTree *treeJetLepVect[200];
  
  char *nameSample[1000];
  char *nameHumanReadable[1000];
  char* xsectionName[1000];
  
  char nameFileIn[1000];
  sprintf(nameFileIn,"%s",fileSamples.c_str());
  
  int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
  
  double Normalization[1000];
  double xsection[1000];
  
  for (int iSample=0; iSample<numberOfSamples; iSample++){
   xsection[iSample] = atof(xsectionName[iSample]);
  }
  
  for (int iSample=0; iSample<numberOfSamples; iSample++){ 
   char nameFile[20000];
   sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
   
   TFile* f = new TFile(nameFile, "READ");
   
   treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
   char nameTreeJetLep[100];
   sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
   treeJetLepVect[iSample]->SetName(nameTreeJetLep);

   double XSection;
   XSection = xsection[iSample];
   Normalization[iSample] = XSection * LUMI / 1000.; 
  }
  
  //==== cut
  std::string CutFile = gConfigParser -> readStringOption("Selections::CutFile");
  std::vector<std::string> vCut;
  std::cout << " nCuts   = " << ReadFileCut(CutFile, vCut) << std::endl;
  
  std::string Cut;
  if (vCut.size() != 0) {
   Cut = vCut.at(0);
  }
  else {
   Cut = "1";
  }
  
  //==== HiggsMass
  std::string HiggsMass = gConfigParser -> readStringOption("Options::HiggsMass");

  //==== list of methods
  std::vector<std::string> vectorMyMethodList = gConfigParser -> readStringListOption("Options::MVAmethods");
  TString myMethodList;
  for (int iMVA = 0; iMVA < vectorMyMethodList.size(); iMVA++) {
   if (iMVA == 0) myMethodList = Form ("%s",vectorMyMethodList.at(iMVA).c_str());
   else           myMethodList = Form ("%s,%s",myMethodList.Data(),vectorMyMethodList.at(iMVA).c_str());
  }
  
  //==== output
  TString outfileName = gConfigParser -> readStringOption("Output::outFileName");
  
  
  // This loads the library
  TMVA::Tools::Instance();
  
  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;
  
  Use["MLP"]             = 1;
  Use["BDTG"]            = 1;
  Use["FDA_GA"]          = 0;
  Use["PDEFoam"]         = 0;
  
     
  std::cout << std::endl;
  std::cout << "==> Start TMVAClassification" << std::endl;
  
  // Select methods (don't look at this code - not of interest)
  if (myMethodList != "") {
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
      
      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
   for (UInt_t i=0; i<mlist.size(); i++) {
    std::string regMethod(mlist[i]);
    
    if (Use.find(regMethod) == Use.end()) {
     std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
     for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
      std::cout << std::endl;
     return 0;
    }
    Use[regMethod] = 1;
   }
  }
  
  // --------------------------------------------------------------------------------------------------
  // --- Here the preparation phase begins
  
  // Create a new root output file
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
    
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAMulticlass",     outputFile, "AnalysisType=multiclass:!V:!Silent:!V:Transformations=I;D" );
  TMVA::Factory *factory = new TMVA::Factory( "TMVAMulticlass",     outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=multiclass" );
  
  factory->AddVariable( "jetpt1" , 'F');
  factory->AddVariable( "jetpt2" , 'F');
  factory->AddVariable( "mjj" , 'F');
  factory->AddVariable( "detajj" , 'F');
  factory->AddVariable( "dphilljetjet" , 'F');
  
  factory->AddVariable( "pt1" , 'F');
  factory->AddVariable( "pt2" , 'F');
  factory->AddVariable( "mll" , 'F');
  factory->AddVariable( "dphill" , 'F');
  factory->AddVariable( "mth" , 'F');
  
  factory->AddVariable( "dphillmet" , 'F');
  factory->AddVariable( "mpmet" , 'F');
  
  factory->AddSpectator( "channel" , 'F');
    
  for (int iSample=0; iSample<numberOfSamples; iSample++){ 
   int numEnt = treeJetLepVect[iSample]->GetEntries(Cut.c_str());
   std::cout << " Sample = " << nameSample[iSample] << " ~ " << nameHumanReadable[iSample] << " --> " << numEnt << std::endl;
   if (numEnt != 0) { 
    if (iSample == 0) factory->AddTree( treeJetLepVect[iSample], "Signal", Normalization[iSample] );
    else if (iSample == 1) factory->AddTree( treeJetLepVect[iSample], "Background", Normalization[iSample] );
    else factory->AddTree( treeJetLepVect[iSample], TString(nameHumanReadable[iSample]), Normalization[iSample] );
 
//     factory->AddTree( treeJetLepVect[iSample], TString(nameHumanReadable[iSample]), Normalization[iSample] );
//     factory->AddTree( treeJetLepVect[iSample], TString(nameHumanReadable[iSample]), Normalization[iSample] , nameWeight.c_str());
    //     factory->AddTree( treeJetLepVect[iSample], TString(nameHumanReadable[iSample]));
   }
  }
  
//   for (int iSample=0; iSample<numberOfSamples; iSample++){ 
//    int numEnt = treeJetLepVect[iSample]->GetEntries(Cut.c_str());
//    std::cout << " Sample = " << nameSample[iSample] << " ~ " << nameHumanReadable[iSample] << " --> " << numEnt << std::endl;
//    if (numEnt != 0) { 
//     bool isSig = false;
//     for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
//      if (nameHumanReadable[iSample] == *itSig) isSig = true;
//     }
//     if (isSig) {
//      factory->AddTree( treeJetLepVect[iSample], TString("Signal"), Normalization[iSample] ); //---> ci deve essere uno chiamato Signal!
//     }
//     else {
//      factory->AddTree( treeJetLepVect[iSample], TString(nameHumanReadable[iSample]), Normalization[iSample] );
//     }
//    }
//   }
//   
//   for (int iSample=0; iSample<numberOfSamples; iSample++){ 
//    int numEnt = treeJetLepVect[iSample]->GetEntries(Cut.c_str());
//    std::cout << " Sample = " << nameSample[iSample] << " ~ " << nameHumanReadable[iSample] << " --> " << numEnt << std::endl;
//    if (numEnt != 0) { 
//     bool isSig = false;
//     for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
//      if (nameHumanReadable[iSample] == *itSig) isSig = true;
//     }
//     if (isSig) {
// //      factory->AddTree( treeJetLepVect[iSample], TString("Signal"), Normalization[iSample] ); //---> ci deve essere uno chiamato Signal!
//     }
//     else {
//      factory->AddTree( treeJetLepVect[iSample], TString(nameHumanReadable[iSample]), Normalization[iSample] );
//     }
//    }
//   }
  
  
  std::cerr << " AAAAAAAAAAAAAAAAAAAAAAAAAAAAA " << std::endl; 
  
  TCut mycuts = Cut.c_str();
  
//   factory->SetWeightExpression( nameWeight.c_str() );
//   factory->SetBackgroundWeightExpression( nameWeight.c_str() );
//   factory->SetSignalWeightExpression    ( nameWeight.c_str() );
  
  std::cerr << " BBBBBBBBBBBBBBBBBBBBBBBBBBBBB " << std::endl;
  
  factory->PrepareTrainingAndTestTree( mycuts ,"SplitMode=Random:NormMode=None:!V");
//   factory->PrepareTrainingAndTestTree( "" ,"SplitMode=Random:NormMode=None:!V");
  
  std::cerr << " CCCCCCCCCCCCCCCCCCCCCCCCCCCCC " << std::endl; 
  
  
  
  // gradient boosted decision trees
//   if (Use["BDTG"])    factory->BookMethod( TMVA::Types::kBDT, "BDTG", "!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.50:nCuts=20:NNodesMax=8");
  if (Use["BDTG"])    factory->BookMethod( TMVA::Types::kBDT, "BDTG", "!H:!V:NTrees=600:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.50:nCuts=20:NNodesMax=8");
  // neural network
  if (Use["MLP"])     factory->BookMethod( TMVA::Types::kMLP, "MLP", "!H:!V:NeuronType=tanh:NCycles=1000:HiddenLayers=N+5,5:TestRate=5:EstimatorType=MSE");
  // functional discriminant with GA minimizer
  if (Use["FDA_GA"])  factory->BookMethod( TMVA::Types::kFDA, "FDA_GA", "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );
  // PDE-Foam approach
  if (Use["PDEFoam"]) factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoam", "!H:!V:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );
  
  
  
  //==== Optimize parameters in MVA methods
//   factory->OptimizeAllMethods();
//   factory->OptimizeAllMethods("ROCIntegral","Scan");
  //==== Train MVAs using the set of training events ====
  factory->TrainAllMethods();
  
  //==== Evaluate all MVAs using the set of test events ====
  factory->TestAllMethods();
  
  //==== Evaluate and compare performance of all configured MVAs ====
  factory->EvaluateAllMethods();    
  
  // --------------------------------------------------------------
  
  // Save the output
  outputFile->Close();
  
  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAnalysis is done!" << std::endl;      
  
  delete factory;
  
  //==== change position of weights file
  std::string toDo;
  
  toDo = "rm -r Weights-MVA-MultiClass/weights_" + HiggsMass + "_testVariables";
  std::cerr << "toDo = " << toDo << std::endl;
  system (toDo.c_str()); 
  
  toDo = "mv weights Weights-MVA-MultiClass/weights_" + HiggsMass + "_testVariables";
  std::cerr << "toDo = " << toDo << std::endl;
  system (toDo.c_str()); 
  
  // Launch the GUI for the root macros
  //   if (!gROOT->IsBatch()) TMVAGui( outfileName );
}



