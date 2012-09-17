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

#include "TEntryList.h"
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


#include "TLorentzVector.h"


///     
///        \  |         |          |           _ \   __ \   ____| 
///       |\/ |   _` |  __|   __|  __ \       |   |  |   |  |     
///       |   |  (   |  |    (     | | |      ___/   |   |  __|   
///      _|  _| \__,_| \__| \___| _| |_|     _|     ____/  _|     
///                                                               


int ReadFilePDF(char cfgFile[1000], char* nameFileNormal[1000],char* nameFilePDF[1000], char* nameFileCut[1000]){
 
 int numberOfSamples = 0;
 std::ifstream inFile(cfgFile);
 std::string buffer; 
 while(!inFile.eof()){
  getline(inFile,buffer);
  if (buffer != ""){ ///---> save from empty line at the end!
   if (buffer.at(0) != '#'){ 
    std::stringstream line( buffer );       
    nameFileNormal[numberOfSamples] = new char [10000];
    line >> nameFileNormal[numberOfSamples]; 
    std::cout << nameFileNormal[numberOfSamples] << " ";
    
    nameFilePDF[numberOfSamples] = new char [10000];
    line >> nameFilePDF[numberOfSamples]; 
    std::cout << nameFilePDF[numberOfSamples] << " ";
    
    nameFileCut[numberOfSamples] = new char [10000];
    line >> nameFileCut[numberOfSamples]; 
    std::cout << nameFileCut[numberOfSamples] << " ";
    
    std::cout << std::endl;
    numberOfSamples++;
   } 
  }
 }
 
 return numberOfSamples;
}


int main(int argc, char** argv) {
 
 
 
 std::cout << "  " << std::endl;
 std::cout << "  " << std::endl;
 std::cout << "     " << std::endl;
 std::cout << "               " << std::endl;
 std::cout << "             \\  |         |          |           _ \\   __ \\   ____|      " << std::endl;
 std::cout << "            |\\/ |   _` |  __|   __|  __ \\       |   |  |   |  |          " << std::endl;     
 std::cout << "            |   |  (   |  |    (     | | |      ___/   |   |  __|        " << std::endl;
 std::cout << "           _|  _| \\__,_| \\__| \\___| _| |_|     _|     ____/  _|          " << std::endl;
 std::cout << "                                                                         " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 
 
 
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeNameNormal  = gConfigParser -> readStringOption("Input::treeNameNormal");
 std::string treeNamePDF     = gConfigParser -> readStringOption("Input::treeNamePDF");
 
 std::string cfgFile = gConfigParser -> readStringOption("Input::cfgFile");
 
 std::string outputFile = gConfigParser -> readStringOption("Output::outputFile");

 //---- variables 
 UInt_t event;   //---- in normal trees
 int eventId; //---- in pdf trees

 float baseW;
 float puW;
 float kfW;
 float effW;
 float triggW;
 
 std::vector<float> *weightAup = new std::vector<float>;
 std::vector<float> *weightBup = new std::vector<float>;
 std::vector<float> *weightCup = new std::vector<float>;
 
 std::vector<float> *weightAdo = new std::vector<float>;
 std::vector<float> *weightBdo = new std::vector<float>;
 std::vector<float> *weightCdo = new std::vector<float>;
 
 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 TTree *treeJetLepVect[500];
 TFile* fileNormal[500];

 TTree *treePDF[500];
 TFile* filePDF[500];
 
 char *nameFileNormal[1000];
 char *nameFilePDF[1000];
 char* nameFileCut[1000];
  
 
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",cfgFile.c_str());
 
 int numberOfSamples = ReadFilePDF (nameFileIn, nameFileNormal, nameFilePDF, nameFileCut);
 
 TFile* outputRootFile;
 outputRootFile = new TFile (outputFile.c_str(),"RECREATE");
 
 TH1F* histo[1000];
 
 TH1F* histoA[1000];
 TH1F* histoAup[1000];
 TH1F* histoAdo[1000];
 TH1F* histoB[1000];
 TH1F* histoBup[1000];
 TH1F* histoBdo[1000];
 TH1F* histoC[1000];
 TH1F* histoCup[1000];
 TH1F* histoCdo[1000];
 
 double Normalization[1000];
 double xsection[1000];
 
 for (int iSample=0; iSample<numberOfSamples; iSample++){ 
  
  std::string CutFile = nameFileCut[iSample];
  std::vector<std::string> vCut;
  std::cout << " nCuts   = " << ReadFileCut(CutFile, vCut) << std::endl;
  TString Cut = Form ("%s",vCut.at(0).c_str()); ///---- only cut == 0 considered so far
  
  char nameFile[200000];
   
  //---- pdf file ----
  sprintf(nameFile,"%s",nameFilePDF[iSample]);   
  filePDF[iSample] = new TFile(nameFile, "READ");
//   std::cout << " nameFile = " << nameFile << std::endl;
  treePDF[iSample] = (TTree*) filePDF[iSample]->Get(treeNamePDF.c_str());
//   std::cout << " treeNamePDF = " << treeNamePDF << std::endl;
  char nameTreePDF[100];
  sprintf(nameTreePDF,"treePDF_%d",iSample); 
  treePDF[iSample]->SetName(nameTreePDF);
    
  std::cout << " treePDF[iSample] = " << treePDF[iSample] << std::endl;
  std::cout << " treePDF[" << iSample << "]->GetEntries() = " << treePDF[iSample]->GetEntries() << std::endl;
  
  treePDF[iSample] -> SetBranchAddress("weightAup",&weightAup);
  treePDF[iSample] -> SetBranchAddress("weightBup",&weightBup);
  treePDF[iSample] -> SetBranchAddress("weightCup",&weightCup);  
  treePDF[iSample] -> SetBranchAddress("weightAdo",&weightAdo);
  treePDF[iSample] -> SetBranchAddress("weightBdo",&weightBdo);
  treePDF[iSample] -> SetBranchAddress("weightCdo",&weightCdo);
  
  std::cout << " BuildIndex " << std::endl;
  
  treePDF[iSample] -> BuildIndex("eventId");
  
  
  
  
  //---- normal file ----
  sprintf(nameFile,"%s",nameFileNormal[iSample]);   
  fileNormal[iSample] = new TFile(nameFile, "READ");
  
  treeJetLepVect[iSample] = (TTree*) fileNormal[iSample]->Get(treeNameNormal.c_str());
  char nameTreeJetLep[100];
  sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
  treeJetLepVect[iSample]->SetName(nameTreeJetLep);
  
  
  std::cout << " Normal :: SetBranchAddress " << std::endl;
  
  treeJetLepVect[iSample] -> SetBranchAddress("event",  &event);
  treeJetLepVect[iSample] -> SetBranchAddress("baseW",  &baseW);
  treeJetLepVect[iSample] -> SetBranchAddress("puW",  &puW);
  treeJetLepVect[iSample] -> SetBranchAddress("kfW",  &kfW);
  treeJetLepVect[iSample] -> SetBranchAddress("effW",  &effW);
  treeJetLepVect[iSample] -> SetBranchAddress("triggW",  &triggW);
  
  
  treeJetLepVect[iSample] -> SetEntryList(0); 
  treeJetLepVect[iSample] ->Draw (">> myList",Cut.Data(),"entrylist");
  TEntryList *myList = (TEntryList*) gDirectory -> Get("myList");
  treeJetLepVect[iSample] -> SetEntryList(myList); 
  
  
  
  
  
  outputRootFile -> cd();
  TString name;
  name = Form ("sample_%d",iSample);
  outputRootFile -> mkdir(name);
  outputRootFile -> cd(name);

  name = Form ("histo_%d",iSample);
  histo[iSample] = new TH1F(name,name,2000,0,2);  
  
  name = Form ("histo_A_%d",iSample);
  histoA[iSample] = new TH1F(name,name,2000,0,2);  
  name = Form ("histo_A_up_%d",iSample);
  histoAup[iSample] = new TH1F(name,name,2000,0,2);  
  name = Form ("histo_A_do_%d",iSample);
  histoAdo[iSample] = new TH1F(name,name,2000,0,2);
  
  name = Form ("histo_B_%d",iSample);
  histoB[iSample] = new TH1F(name,name,2000,0,2);  
  name = Form ("histo_B_up_%d",iSample);
  histoBup[iSample] = new TH1F(name,name,2000,0,2);  
  name = Form ("histo_B_do_%d",iSample);
  histoBdo[iSample] = new TH1F(name,name,2000,0,2);
  
  name = Form ("histo_C_%d",iSample);
  histoC[iSample] = new TH1F(name,name,2000,0,2);  
  name = Form ("histo_C_up_%d",iSample);
  histoCup[iSample] = new TH1F(name,name,2000,0,2);  
  name = Form ("histo_C_do_%d",iSample);
  histoCdo[iSample] = new TH1F(name,name,2000,0,2);
  
  ///==== loop ====
//   Long64_t nentries = treeJetLepVect[iSample]->GetEntries();  
  Long64_t nentries = myList->GetN();  
     
  std::vector<double> events_A_up;
  std::vector<double> events_A_do;
  std::vector<double> events_B_up;
  std::vector<double> events_B_do;
  std::vector<double> events_C_up;
  std::vector<double> events_C_do;

  std::vector<double> all_A_up;
  std::vector<double> all_A_do;
  std::vector<double> all_B_up;
  std::vector<double> all_B_do;
  std::vector<double> all_C_up;
  std::vector<double> all_C_do;
  
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   if ((iEntry%1000) == 0) std::cout << ">>>>> analysis Normal::GetEntry " << iEntry << " : " << nentries << std::endl;   

   Long64_t entry = myList->GetEntry(iEntry);  
   treeJetLepVect[iSample]->GetEntry(entry);
   
   treePDF[iSample] -> GetEntryWithIndex(event);
   
   
   if (iEntry == 0) {
    
    for (int iWei = 0; iWei < weightAup->size(); iWei++) {   
     events_A_up.push_back(0);
    }
    for (int iWei = 0; iWei < weightAdo->size(); iWei++) {   
     events_A_do.push_back(0);
    }

    for (int iWei = 0; iWei < weightBup->size(); iWei++) {   
     events_B_up.push_back(0);
    }
    for (int iWei = 0; iWei < weightBdo->size(); iWei++) {   
     events_B_do.push_back(0);
    }
    
    for (int iWei = 0; iWei < weightCup->size(); iWei++) {   
     events_C_up.push_back(0);
    }
    for (int iWei = 0; iWei < weightCdo->size(); iWei++) {   
     events_C_do.push_back(0);
    }
   }
   
   
   
   for (int iWei = 0; iWei < weightAup->size(); iWei++) {   
    events_A_up.at(iWei) = events_A_up.at(iWei) + weightAup->at(iWei);
   }
   for (int iWei = 0; iWei < weightAdo->size(); iWei++) {   
    events_A_do.at(iWei) = events_A_do.at(iWei) + weightAdo->at(iWei);
   }

   for (int iWei = 0; iWei < weightBup->size(); iWei++) {   
    events_B_up.at(iWei) = events_B_up.at(iWei) + weightBup->at(iWei);
   }
   for (int iWei = 0; iWei < weightBdo->size(); iWei++) {   
    events_B_do.at(iWei) = events_B_do.at(iWei) + weightBdo->at(iWei);
   }
   
   for (int iWei = 0; iWei < weightCup->size(); iWei++) {   
    events_C_up.at(iWei) = events_C_up.at(iWei) + weightCup->at(iWei);
   }
   for (int iWei = 0; iWei < weightCdo->size(); iWei++) {   
    events_C_do.at(iWei) = events_C_do.at(iWei) + weightCdo->at(iWei);
   }
   
  }
  
  
  nentries =  treePDF[iSample] -> GetEntries();
  for (Long64_t iEntry = 0; iEntry < nentries; iEntry++){
   if ((iEntry%10000) == 0) std::cout << ">>>>> analysis PDF ::GetEntry " << iEntry << " : " << nentries << std::endl;   
   
   treePDF[iSample] -> GetEntry(iEntry);
   
   if (iEntry == 0) {
    for (int iWei = 0; iWei < weightAup->size(); iWei++) {   
     all_A_up.push_back(0);
    }
    for (int iWei = 0; iWei < weightAdo->size(); iWei++) {   
     all_A_do.push_back(0);
    }
    
    for (int iWei = 0; iWei < weightBup->size(); iWei++) {   
     all_B_up.push_back(0);
    }
    for (int iWei = 0; iWei < weightBdo->size(); iWei++) {   
     all_B_do.push_back(0);
    }
    
    for (int iWei = 0; iWei < weightCup->size(); iWei++) {   
     all_C_up.push_back(0);
    }
    for (int iWei = 0; iWei < weightCdo->size(); iWei++) {   
     all_C_do.push_back(0);
    }
   }
   
   for (int iWei = 0; iWei < weightAup->size(); iWei++) {   
    all_A_up.at(iWei) = all_A_up.at(iWei) + weightAup->at(iWei);
   }
   for (int iWei = 0; iWei < weightAdo->size(); iWei++) {   
    all_A_do.at(iWei) = all_A_do.at(iWei) + weightAdo->at(iWei);
   }
   
   for (int iWei = 0; iWei < weightBup->size(); iWei++) {   
    all_B_up.at(iWei) = all_B_up.at(iWei) + weightBup->at(iWei);
   }
   for (int iWei = 0; iWei < weightBdo->size(); iWei++) {   
    all_B_do.at(iWei) = all_B_do.at(iWei) + weightBdo->at(iWei);
   }

   for (int iWei = 0; iWei < weightCup->size(); iWei++) {   
    all_C_up.at(iWei) = all_C_up.at(iWei) + weightCup->at(iWei);
   }
   for (int iWei = 0; iWei < weightCdo->size(); iWei++) {   
    all_C_do.at(iWei) = all_C_do.at(iWei) + weightCdo->at(iWei);
   }

  }
  
  for (int iWei = 0; iWei < weightAup->size(); iWei++) {      
   histoAup[iSample] -> Fill(events_A_up.at(iWei) / all_A_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoAdo[iSample] -> Fill(events_A_do.at(iWei) / all_A_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoA[iSample] -> Fill(events_A_up.at(iWei) / all_A_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoA[iSample] -> Fill(events_A_do.at(iWei) / all_A_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0))); 
   histo[iSample] -> Fill(events_A_up.at(iWei) / all_A_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histo[iSample] -> Fill(events_A_do.at(iWei) / all_A_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
  }
  for (int iWei = 0; iWei < weightBup->size(); iWei++) {      
   histoBup[iSample] -> Fill(events_B_up.at(iWei) / all_B_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoBdo[iSample] -> Fill(events_B_do.at(iWei) / all_B_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoB[iSample] -> Fill(events_B_up.at(iWei) / all_B_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoB[iSample] -> Fill(events_B_do.at(iWei) / all_B_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histo[iSample] -> Fill(events_B_up.at(iWei) / all_B_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histo[iSample] -> Fill(events_B_do.at(iWei) / all_B_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
  }
  for (int iWei = 0; iWei < weightCup->size(); iWei++) {      
   histoCup[iSample] -> Fill(events_C_up.at(iWei) / all_C_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoCdo[iSample] -> Fill(events_C_do.at(iWei) / all_C_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoC[iSample] -> Fill(events_C_up.at(iWei) / all_C_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histoC[iSample] -> Fill(events_C_do.at(iWei) / all_C_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histo[iSample] -> Fill(events_C_up.at(iWei) / all_C_up.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
   histo[iSample] -> Fill(events_C_do.at(iWei) / all_C_do.at(iWei) / (events_A_up.at(0) / all_A_up.at(0)));
  }
  
//   for (int iWei = 0; iWei < weightAup->size(); iWei++) {      
//    histoAup[iSample] -> Fill(events_A_up.at(iWei) / all_A_up.at(iWei));
//    histoAdo[iSample] -> Fill(events_A_do.at(iWei) / all_A_do.at(iWei));
//    histoA[iSample] -> Fill(events_A_up.at(iWei) / all_A_up.at(iWei));
//    histoA[iSample] -> Fill(events_A_do.at(iWei) / all_A_do.at(iWei));
//   }
//   for (int iWei = 0; iWei < weightBup->size(); iWei++) {      
//    histoBup[iSample] -> Fill(events_B_up.at(iWei) / all_B_up.at(iWei));
//    histoBdo[iSample] -> Fill(events_B_do.at(iWei) / all_B_do.at(iWei));
//    histoB[iSample] -> Fill(events_B_up.at(iWei) / all_B_up.at(iWei));
//    histoB[iSample] -> Fill(events_B_do.at(iWei) / all_B_do.at(iWei));
//   }
//   for (int iWei = 0; iWei < weightCup->size(); iWei++) {      
//    histoCup[iSample] -> Fill(events_C_up.at(iWei) / all_C_up.at(iWei));
//    histoCdo[iSample] -> Fill(events_C_do.at(iWei) / all_C_do.at(iWei));
//    histoC[iSample] -> Fill(events_C_up.at(iWei) / all_C_up.at(iWei));
//    histoC[iSample] -> Fill(events_C_do.at(iWei) / all_C_do.at(iWei));
//   }
   
  
  name = Form ("sample_%d",iSample);
  outputRootFile -> cd(name);  
  histo[iSample] -> Write();  
  
  histoA[iSample] -> Write();  
  histoAup[iSample] -> Write();  
  histoAdo[iSample] -> Write();  
  
  histoB[iSample] -> Write();  
  histoBup[iSample] -> Write();  
  histoBdo[iSample] -> Write();  
  
  histoC[iSample] -> Write();  
  histoCup[iSample] -> Write();  
  histoCdo[iSample] -> Write();  
    
 }
 
}



