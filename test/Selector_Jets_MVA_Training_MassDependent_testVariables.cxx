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
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

#include "test/Winter10/Read.cc"

Bool_t ReadDataFromAsciiIFormat = kFALSE;


void Selector_Jets_MVA_Training_MassDependent_testVariables( std::string HiggsMass = "qqH160") {

 TMVA::Tools::Instance();
 
 std::cout << "Start TMVAnalysis" << std::endl << "=================" << std::endl << std::endl;
 
 // Create a new root output file.
 TString outfileName = Form( "output/Selector_Jets_trained_%s_testVariables_BDT.root", HiggsMass.c_str() );
 TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
 
 //==== Create the factory ====
 TMVA::Factory *factory = new TMVA::Factory( "TMVAnalysis", outputFile, Form("!V:!Silent:%sColor:!V:Transformations=I;D;P;G", gROOT->IsBatch()?"!":"") );
 
 
 //==== Add the input variable names to be used to train the MVAs to the factory ====
 
 int Match4;

 factory->AddVariable( "log(q1_pT)" , 'F');
 factory->AddVariable( "log(q2_pT)" , 'F');
 factory->AddVariable( "abs(q1_Eta)" , 'F');
 factory->AddVariable( "abs(q2_Eta)" , 'F');
 factory->AddVariable( "q1_Eta*q2_Eta" , 'F');
 factory->AddVariable( "DEta_qq" , 'F');
 factory->AddVariable( "DPhi_qq" , 'F');
 factory->AddVariable( "log(M_qq)" , 'F');
 factory->AddSpectator( "q1_bTag_trackCountingHighPurBJetTags" , 'F');
 factory->AddSpectator( "q2_bTag_trackCountingHighPurBJetTags" , 'F');
 factory->AddSpectator( "CJV_30" , 'I');
 
 //==== Define the input samples ====
 
 TTree *signal_background[100]; 
 double weights[100];

 TTree *treeEffVect[100];
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 double xsection[1000];
 
 char nameFileIn[1000] = {"test/Winter10/samples_skimmed_training_AllHiggsMasses.txt"};
 int totalSamples =  ReadFile(nameFileIn,nameSample,nameHumanReadable, xsectionName);
 
 for (int iSample=0; iSample<totalSamples; iSample++){
  xsection[iSample] = atof(xsectionName[iSample]);
 }
 
 for (int iSample=0; iSample<totalSamples; iSample++){
  std::cout << " Sample[" << iSample << " : " << totalSamples << "] = " << nameSample[iSample] << std::endl;
  char nameFile[1000];
  sprintf(nameFile,"output_Fall10_AK5PF/out_NtupleProducer_%s.root",nameSample[iSample]);  
  TFile* f = new TFile(nameFile, "READ");
  
  treeEffVect[iSample] = (TTree) f->Get("outTreeSelections");
  char nameTreeEff[100];
  sprintf(nameTreeEff,"treeEff_%d",iSample); 
  treeEffVect[iSample]->SetName(nameTreeEff);      
  
  double XSection;
  double eff_Channel_Filter;
  double preselection_efficiency;
  int numEntriesBefore;
  treeEffVect[iSample]->SetBranchAddress("XSection",&XSection);
  treeEffVect[iSample]->SetBranchAddress("preselection_efficiency",&preselection_efficiency);
  treeEffVect[iSample]->SetBranchAddress("numEntriesBefore",&numEntriesBefore);
  treeEffVect[iSample]->GetEntry(0);
  
  ///**********************************************************************
  XSection = xsection[iSample];
  weights[iSample] = XSection * preselection_efficiency / numEntriesBefore;
  signal_background[iSample] = (TTree) f->Get("outTreeJetLep");
  ///**********************************************************************
  std::cout << std::endl;
 } 
 
 std::cout << " Signal = " << HiggsMass << std::endl;
 for (int iSample=0; iSample<totalSamples; iSample++){
  std::string tempName = nameHumanReadable[iSample];
  std::cout << " ~~ Name = " << tempName << std::endl;
  if (tempName.find(HiggsMass) != string::npos ){ /// ---- the way signal is defined!
   factory->AddSignalTree( signal_background[iSample], weights[iSample] );
   std::cerr << " *** adding sample " << tempName << " as signal" << std::endl;
  }
  else {
   int found = tempName.find("qqH");
   if (found == string::npos) { /// ---- add only background, other Higgs masses not considered
    factory->AddBackgroundTree( signal_background[iSample], weights[iSample] );
    std::cerr << " *** adding sample " << tempName << " as background" << std::endl;
   }
  }
 }
 
 std::cerr << "==== exec ==== " << std::endl;
 
 TString mycuts_s = Form("1");
 TString mycuts_b = Form("1");
 
 TCut mycuts = mycuts_s;
 TCut mycutb = mycuts_b;
 
 factory->PrepareTrainingAndTestTree( mycuts, mycutb,"SplitMode=Random:NormMode=NumEvents:!V");
 
 
   //==== Book the MVA methods ====
/*
 TMVA::MethodBase* liCat_1 = factory->BookMethod( TMVA::Types::kCategory, "All_1","" );
 TMVA::MethodCategory* mcat_1 = 0;
 mcat_1 = dynamic_cast<TMVA::MethodCategory*>(liCat_1);       
 TString theCatVars_1 = "log(q1_pT):log(q2_pT):abs(q1_Eta):abs(q2_Eta):q1_Eta*q2_Eta:DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_1->AddMethod( "1",theCatVars_1, TMVA::Types::kMLP,"All_1","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_2 = factory->BookMethod( TMVA::Types::kCategory, "All_2","" );
 TMVA::MethodCategory* mcat_2 = 0;
 mcat_2 = dynamic_cast<TMVA::MethodCategory*>(liCat_2);       
 TString theCatVars_2 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_2->AddMethod( "1",theCatVars_2, TMVA::Types::kMLP,"All_2","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_3 = factory->BookMethod( TMVA::Types::kCategory, "All_3","" );
 TMVA::MethodCategory* mcat_3 = 0;
 mcat_3 = dynamic_cast<TMVA::MethodCategory*>(liCat_3);       
 TString theCatVars_3 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DEta_qq:log(M_qq)"; 
 mcat_3->AddMethod( "1",theCatVars_3, TMVA::Types::kMLP,"All_3","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_4 = factory->BookMethod( TMVA::Types::kCategory, "All_4","" );
 TMVA::MethodCategory* mcat_4 = 0;
 mcat_4 = dynamic_cast<TMVA::MethodCategory*>(liCat_4);       
 TString theCatVars_4 = "log(q1_pT):log(q2_pT):DEta_qq:log(M_qq)"; 
 mcat_4->AddMethod( "1",theCatVars_4, TMVA::Types::kMLP,"All_4","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_5 = factory->BookMethod( TMVA::Types::kCategory, "All_5","" );
 TMVA::MethodCategory* mcat_5 = 0;
 mcat_5 = dynamic_cast<TMVA::MethodCategory*>(liCat_5);       
 TString theCatVars_5 = "DEta_qq:log(M_qq)"; 
 mcat_5->AddMethod( "1",theCatVars_5, TMVA::Types::kMLP,"All_5","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );

 TMVA::MethodBase* liCat_6 = factory->BookMethod( TMVA::Types::kCategory, "All_6","" );
 TMVA::MethodCategory* mcat_6 = 0;
 mcat_6 = dynamic_cast<TMVA::MethodCategory*>(liCat_6);       
 TString theCatVars_6 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DEta_qq:DPhi_qq"; 
 mcat_6->AddMethod( "1",theCatVars_6, TMVA::Types::kMLP,"All_6","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_7 = factory->BookMethod( TMVA::Types::kCategory, "All_7","" );
 TMVA::MethodCategory* mcat_7 = 0;
 mcat_7 = dynamic_cast<TMVA::MethodCategory*>(liCat_7);       
 TString theCatVars_7 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DPhi_qq:log(M_qq)"; 
 mcat_7->AddMethod( "1",theCatVars_7, TMVA::Types::kMLP,"All_7","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_8 = factory->BookMethod( TMVA::Types::kCategory, "All_8","" );
 TMVA::MethodCategory* mcat_8 = 0;
 mcat_8 = dynamic_cast<TMVA::MethodCategory*>(liCat_8);       
 TString theCatVars_8 = "log(q1_pT):log(q2_pT):DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_8->AddMethod( "1",theCatVars_8, TMVA::Types::kMLP,"All_8","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_9 = factory->BookMethod( TMVA::Types::kCategory, "All_9","" );
 TMVA::MethodCategory* mcat_9 = 0;
 mcat_9 = dynamic_cast<TMVA::MethodCategory*>(liCat_9);       
 TString theCatVars_9 = "q1_Eta*q2_Eta:DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_9->AddMethod( "1",theCatVars_9, TMVA::Types::kMLP,"All_9","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 
 TMVA::MethodBase* liCat_10 = factory->BookMethod( TMVA::Types::kCategory, "All_10","" );
 TMVA::MethodCategory* mcat_10 = 0;
 mcat_10 = dynamic_cast<TMVA::MethodCategory*>(liCat_10);       
 TString theCatVars_10 = "log(q2_pT):q1_Eta*q2_Eta:DEta_qq:log(M_qq)"; 
 mcat_10->AddMethod( "1",theCatVars_10, TMVA::Types::kMLP,"All_10","H:!V:NeuronType=tanh:VarTransform=N,D,G:NCycles=300:HiddenLayers=N+2:TestRate=5" );
 */
 
 



 TMVA::MethodBase* liCat_1 = factory->BookMethod( TMVA::Types::kCategory, "All_1","" );
 TMVA::MethodCategory* mcat_1 = 0;
 mcat_1 = dynamic_cast<TMVA::MethodCategory*>(liCat_1);       
 TString theCatVars_1 = "log(q1_pT):log(q2_pT):abs(q1_Eta):abs(q2_Eta):q1_Eta*q2_Eta:DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_1->AddMethod( "1",theCatVars_1, TMVA::Types::kBDT,"All_1","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_2 = factory->BookMethod( TMVA::Types::kCategory, "All_2","" );
 TMVA::MethodCategory* mcat_2 = 0;
 mcat_2 = dynamic_cast<TMVA::MethodCategory*>(liCat_2);       
 TString theCatVars_2 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_2->AddMethod( "1",theCatVars_2, TMVA::Types::kBDT,"All_2","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_3 = factory->BookMethod( TMVA::Types::kCategory, "All_3","" );
 TMVA::MethodCategory* mcat_3 = 0;
 mcat_3 = dynamic_cast<TMVA::MethodCategory*>(liCat_3);       
 TString theCatVars_3 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DEta_qq:log(M_qq)"; 
 mcat_3->AddMethod( "1",theCatVars_3, TMVA::Types::kBDT,"All_3","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_4 = factory->BookMethod( TMVA::Types::kCategory, "All_4","" );
 TMVA::MethodCategory* mcat_4 = 0;
 mcat_4 = dynamic_cast<TMVA::MethodCategory*>(liCat_4);       
 TString theCatVars_4 = "log(q1_pT):log(q2_pT):DEta_qq:log(M_qq)"; 
 mcat_4->AddMethod( "1",theCatVars_4, TMVA::Types::kBDT,"All_4","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_5 = factory->BookMethod( TMVA::Types::kCategory, "All_5","" );
 TMVA::MethodCategory* mcat_5 = 0;
 mcat_5 = dynamic_cast<TMVA::MethodCategory*>(liCat_5);       
 TString theCatVars_5 = "DEta_qq:log(M_qq)"; 
 mcat_5->AddMethod( "1",theCatVars_5, TMVA::Types::kBDT,"All_5","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );

 TMVA::MethodBase* liCat_6 = factory->BookMethod( TMVA::Types::kCategory, "All_6","" );
 TMVA::MethodCategory* mcat_6 = 0;
 mcat_6 = dynamic_cast<TMVA::MethodCategory*>(liCat_6);       
 TString theCatVars_6 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DEta_qq:DPhi_qq"; 
 mcat_6->AddMethod( "1",theCatVars_6, TMVA::Types::kBDT,"All_6","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_7 = factory->BookMethod( TMVA::Types::kCategory, "All_7","" );
 TMVA::MethodCategory* mcat_7 = 0;
 mcat_7 = dynamic_cast<TMVA::MethodCategory*>(liCat_7);       
 TString theCatVars_7 = "log(q1_pT):log(q2_pT):q1_Eta*q2_Eta:DPhi_qq:log(M_qq)"; 
 mcat_7->AddMethod( "1",theCatVars_7, TMVA::Types::kBDT,"All_7","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_8 = factory->BookMethod( TMVA::Types::kCategory, "All_8","" );
 TMVA::MethodCategory* mcat_8 = 0;
 mcat_8 = dynamic_cast<TMVA::MethodCategory*>(liCat_8);       
 TString theCatVars_8 = "log(q1_pT):log(q2_pT):DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_8->AddMethod( "1",theCatVars_8, TMVA::Types::kBDT,"All_8","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_9 = factory->BookMethod( TMVA::Types::kCategory, "All_9","" );
 TMVA::MethodCategory* mcat_9 = 0;
 mcat_9 = dynamic_cast<TMVA::MethodCategory*>(liCat_9);       
 TString theCatVars_9 = "q1_Eta*q2_Eta:DEta_qq:DPhi_qq:log(M_qq)"; 
 mcat_9->AddMethod( "1",theCatVars_9, TMVA::Types::kBDT,"All_9","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
 TMVA::MethodBase* liCat_10 = factory->BookMethod( TMVA::Types::kCategory, "All_10","" );
 TMVA::MethodCategory* mcat_10 = 0;
 mcat_10 = dynamic_cast<TMVA::MethodCategory*>(liCat_10);       
 TString theCatVars_10 = "log(q2_pT):q1_Eta*q2_Eta:DEta_qq:log(M_qq)"; 
 mcat_10->AddMethod( "1",theCatVars_10, TMVA::Types::kBDT,"All_10","!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=2.5" );
 
   // --------------------------------------------------------------------------------------------------
   // ---- Now you can tell the factory to train, test, and evaluate the MVAs


   
   //==== Optimize parameters in MVA methods
   factory->OptimizeAllMethods()
//    factory->OptimizeAllMethods("ROCIntegral","Scan");
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
   std::string toDo = "mv weights Weights/weights_jet_" + HiggsMass + "_testVariables";
   std::cerr << "toDo = " << toDo << std::endl;
   system (toDo.c_str()); 
   
   
   // Launch the GUI for the root macros
//    if (!gROOT->IsBatch()) TMVAGui( outfileName );
}



