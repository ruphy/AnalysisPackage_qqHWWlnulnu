///==== filter tree for MVA @WW level ====
///==== filter events using the cut defined hardcoded ====

#include <iostream>

#include "TEntryList.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include <cstdlib> 

// 
//  add those variables that a usually datadriven, such as triggerWeight and lepton efficiency weight
//  set to 1
// 

///    
///         \         |      | \ \     /            _)         |      |        ____|                       __ \          |          
///        _ \     _` |   _` |  \ \   /  _` |   __|  |   _` |  __ \   |   _ \  |     __|  _ \   __ `__ \   |   |   _` |  __|   _` | 
///       ___ \   (   |  (   |   \ \ /  (   |  |     |  (   |  |   |  |   __/  __|  |    (   |  |   |   |  |   |  (   |  |    (   | 
///     _/    _\ \__,_| \__,_|    \_/  \__,_| _|    _| \__,_| _.__/  _| \___| _|   _|   \___/  _|  _|  _| ____/  \__,_| \__| \__,_| 
///                                                                                                                                 


int main(int argc, char** argv) {

 if(argc != 4)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " fileIn fileOut Events" << std::endl ;
  return 1;
 }
 
 std::cout << "      " << std::endl;
 std::cout << "      " << std::endl;             
 std::cout << "            " << std::endl;                 
 std::cout << "               \\         |      | \\ \\     /            _)         |      |        ____|                       __ \\          |                " << std::endl;             
 std::cout << "              _ \\     _` |   _` |  \\ \\   /  _` |   __|  |   _` |  __ \\   |   _ \\  |     __|  _ \\   __ `__ \\   |   |   _` |  __|   _` |       " << std::endl;             
 std::cout << "             ___ \\   (   |  (   |   \\ \\ /  (   |  |     |  (   |  |   |  |   __/  __|  |    (   |  |   |   |  |   |  (   |  |    (   |       " << std::endl;             
 std::cout << "           _/    _\\ \\__,_| \\__,_|    \\_/  \\__,_| _|    _| \\__,_| _.__/  _| \\___| _|   _|   \\___/  _|  _|  _| ____/  \\__,_| \\__| \\__,_|       " << std::endl;             
 std::cout << "                                                                                                                                             " << std::endl;             
 std::cout << "      " << std::endl;
 std::cout << "      " << std::endl;
 
 
 
 std::string inputFileName  = argv[1];
 std::string outputFileName = argv[2];

 std::string treeName = "latino";
 
 ///  from http://hepuser.ucsd.edu/twiki2/bin/view/Latinos/FinalFall11Analysis
 
 TFile* f = new TFile(inputFileName.c_str(), "READ");    
 TTree *treeJetLepVect;
 treeJetLepVect = (TTree*) f->Get(treeName.c_str());
 float mcGenWeight;
 
 int totNumEvents = treeJetLepVect->GetEntries();
 std::cout << " totNumEvents   = " << totNumEvents   << std::endl;
 
 //---- new tree
 TFile outputRootFile ( outputFileName.c_str(), "RECREATE") ;
 outputRootFile.cd () ;
 TTree* cloneTree = treeJetLepVect -> CloneTree (0) ;
 float triggW;
 
 //---- add a "new" baseW
 cloneTree->Branch("triggW",&triggW,"triggW/F");
 
 for ( int iEntry = 0; iEntry < totNumEvents ; iEntry++) { 
  treeJetLepVect -> GetEntry (iEntry);
  triggW = 1. ;
  cloneTree -> Fill () ;
 }
 
 cloneTree -> AutoSave () ;
 outputRootFile.Close () ;
 
}





