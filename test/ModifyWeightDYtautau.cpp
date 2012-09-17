///==== filter tree for MVA @WW level ====
///==== filter events using the cut defined hardcoded ====

#include <iostream>

#include "TEntryList.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include <cstdlib> 

///       
///          \  |             | _)   _|            \ \        /     _)         |      |        __ \ \ \   /      |                  |                 
///         |\/ |   _ \    _` |  |  |    |   |      \ \  \   /  _ \  |   _` |  __ \   __|      |   | \   /       __|   _` |  |   |  __|   _` |  |   | 
///         |   |  (   |  (   |  |  __|  |   |       \ \  \ /   __/  |  (   |  | | |  |        |   |    |        |    (   |  |   |  |    (   |  |   | 
///        _|  _| \___/  \__,_| _| _|   \__, |        \_/\_/  \___| _| \__, | _| |_| \__|     ____/    _|       \__| \__,_| \__,_| \__| \__,_| \__,_| 
///                                     ____/                          |___/                                                                          
///       


int main(int argc, char** argv) {

 if(argc != 4)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " fileIn fileOut Events" << std::endl ;
  return 1;
 }
 
 std::cout << "      " << std::endl;
 std::cout << "      " << std::endl;             
 std::cout << "                \\  |             | _)   _|            \\ \\        /     _)         |      |        __ \\ \\ \\   /      |                  |                      " << std::endl;
 std::cout << "               |\\/ |   _ \\    _` |  |  |    |   |      \\ \\  \\   /  _ \\  |   _` |  __ \\   __|      |   | \\   /       __|   _` |  |   |  __|   _` |  |   |      " << std::endl; 
 std::cout << "               |   |  (   |  (   |  |  __|  |   |       \\ \\  \\ /   __/  |  (   |  | | |  |        |   |    |        |    (   |  |   |  |    (   |  |   |      " << std::endl; 
 std::cout << "              _|  _| \\___/  \\__,_| _| _|   \\__, |        \\_/\\_/  \\___| _| \\__, | _| |_| \\__|     ____/    _|       \\__| \\__,_| \\__,_| \\__| \\__,_| \\__,_|      " << std::endl; 
 std::cout << "                                           ____/                          |___/                                                                               " << std::endl;
 std::cout << "      " << std::endl;
 std::cout << "      " << std::endl;
 
 
 
 std::string inputFileName  = argv[1];
 std::string outputFileName = argv[2];

//  double events = atof(argv[3]);
//  std::cout << " events = " << events << std::endl;
//  double xsection = 975; // pb
 
 double scaleFactor = atof(argv[3]);
 std::cout << " scaleFactor = " << scaleFactor << std::endl;
 
 
 
 
 std::string treeName = "latino";
 
 ///  from http://hepuser.ucsd.edu/twiki2/bin/view/Latinos/FinalFall11Analysis
 
 TFile* f = new TFile(inputFileName.c_str(), "READ");    
 TTree *treeJetLepVect;
 treeJetLepVect = (TTree*) f->Get(treeName.c_str());
 float mcGenWeight;
 
 treeJetLepVect->SetBranchAddress("mcGenWeight",&mcGenWeight);
 //---- do not store the old baseW
 treeJetLepVect->SetBranchStatus ("baseW",  0);
 treeJetLepVect->SetBranchStatus ("trigger",0);
 
 int totNumEvents = treeJetLepVect->GetEntries();
 std::cout << " totNumEvents   = " << totNumEvents   << std::endl;
 
 //---- new tree
 TFile outputRootFile ( outputFileName.c_str(), "RECREATE") ;
 outputRootFile.cd () ;
 TTree* cloneTree = treeJetLepVect -> CloneTree (0) ;
 float baseW;
 float trigger;
 
 //---- add a "new" baseW
 cloneTree->Branch("baseW",&baseW,"baseW/F");
 cloneTree->Branch("trigger",&trigger,"trigger/F");
 
 for ( int iEntry = 0; iEntry < totNumEvents ; iEntry++) { 
  treeJetLepVect -> GetEntry (iEntry);
//   baseW = ( mcGenWeight * xsection / events );
  baseW = ( mcGenWeight * scaleFactor );
  trigger = 1.;
  cloneTree -> Fill () ;
 }
 
 cloneTree -> AutoSave () ;
 outputRootFile.Close () ;
 
}





