///==== filter tree for MVA @WW level ====
///==== filter events using the cut defined hardcoded ====

#include <iostream>

#include "TEntryList.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"


int main(int argc, char** argv) {

 gSystem->Load("libTree");
  
 if(argc < 3)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " fileIn fileOut" << std::endl ;
  return 1;
 }
 
 std::string inputFileName  = argv[1];
 std::string outputFileName = argv[2];

 std::cout << " inputFileName  = " << inputFileName  << std::endl;
 std::cout << " outputFileName = " << outputFileName << std::endl;
 
 std::string treeName = "latino";
 
 ///  from http://hepuser.ucsd.edu/twiki2/bin/view/Latinos/FinalFall11Analysis
 //
 std::string Cut = "  trigger && pfmet > 20 && mll > (12 + 8*sameflav) && zveto && mpmet > (20+(17+nvtx/2.)*sameflav) && njet >= 2 && njet <=3 && (dphilljetjet<pi/180.*165. || !sameflav) && bveto_mu && nextra == 0 && bveto_ip && (pt2 > 15||!sameflav) && ptll > 45      && abs(jeteta1)<4.5 && abs(jeteta2)<4.5         && jettche1<2.1 && jettche2<2.1   "; 
 
 //---- only for DY datadriven estimation ----
 std::cout << " argc = " << argc << std::endl;
 
 if (argc == 4) {
  std::string what = argv[3];
  if (what == "DY") {
   std::cout << " DY skim " << std::endl;
   Cut = "             trigger && pfmet > 20 && mll > (12 + 8*sameflav)                                                && njet >= 2 && njet <=3 && (dphilljetjet<pi/180.*165. || !sameflav) && bveto_mu && nextra == 0 && bveto_ip && (pt2 > 15||!sameflav) && ptll > 45      && abs(jeteta1)<4.5 && abs(jeteta2)<4.5                                           "; 
  }
  if (what == "top") {
   std::cout << " top skim " << std::endl;
   Cut = "             trigger && pfmet > 20 && mll > (12 + 8*sameflav) && zveto && mpmet > (20+(17+nvtx/2.)*sameflav) && njet >= 2 && njet <=3 && (dphilljetjet<pi/180.*165. || !sameflav)             && nextra == 0 && bveto_ip && (pt2 > 15||!sameflav) && ptll > 45      && abs(jeteta1)<4.5 && abs(jeteta2)<4.5"; 
  }
  if (what == "4jet") {
   std::cout << " 4jet skim " << std::endl;
   Cut = "             trigger && njet >= 4 && nextra == 0 && bveto_ip && abs(jeteta1)<4.5 && abs(jeteta2)<4.5"; 
  }
  if (what == "3jet") {
   std::cout << " 3jet skim " << std::endl;
   Cut = "             trigger && njet >= 3 && nextra == 0 && bveto_ip && abs(jeteta1)<4.5 && abs(jeteta2)<4.5"; 
  }
  if (what == "2jet") {
   std::cout << " 2jet skim " << std::endl;
   Cut = "             trigger && njet >= 2 && nextra == 0 && bveto_ip && abs(jeteta1)<4.5 && abs(jeteta2)<4.5"; 
  }
  if (what == "0jet") {
   std::cout << " 0jet skim " << std::endl;
   Cut = "              trigger && pfmet > 20 && mll > (12 + 8*sameflav) && zveto && mpmet > (20+(17+nvtx/2.)*sameflav)&& njet==0 && (dphiveto || ! sameflav) && bveto_mu && nextra == 0 && bveto_ip && (pt2 > 15||!sameflav) && ptll > 45 "; 
  }
  if (what == "WHSC") {
   std::cout << " WHSC skim " << std::endl;
   Cut = "            ch1*ch2 == 1"; 
  }
  if (what == "DY2012") {
   std::cout << " DY2012 skim " << std::endl;
   Cut = "trigger==1. && pfmet>20. && mll>12             && mpmet>20.                        && (dphilljetjet<pi/180.*165. || !sameflav )    && bveto_mu==1 && nextra==0 &&   bveto_ip==1 &&  (nbjettche==0 || njet>3)  && ptll>45.                                                                                                                           && (njet>=2 && njet<=3 && (jetpt3<=30 || !(jetpt3 > 30 && (  (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))               "; 
   //     trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20. && (njet==0 || njet==1 || (dphilljetjet<pi/180.*165. || !sameflav )  ) && bveto_mu==1 && nextra==0 &&  (bveto_ip==1 &&  (nbjettche==0 || njet>3)) && ptll>45. &&   ( !sameflav || ( (njet!=0 || dymva1>0.60) && (njet!=1 || dymva1>0.30) && ( njet==0 || njet==1 || (pfmet > 45.0)) ) ) && (njet>=2 && njet<=3 && (jetpt3<=30 || !(jetpt3 > 30 && (  (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))   
  }
  if (what == "Top2012") {
   std::cout << " Top2012 skim " << std::endl;
   Cut = "trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20.                        && (dphilljetjet<pi/180.*165. || !sameflav )                   && nextra==0                                                && ptll>45.                                                                                                    &&  pfmet > 45.0       && (njet>=2 && njet<=3 && (jetpt3<=30 || !(jetpt3 > 30 && (  (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))               "; 
   //     trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20. && (njet==0 || njet==1 || (dphilljetjet<pi/180.*165. || !sameflav )  ) && bveto_mu==1 && nextra==0 &&  (bveto_ip==1 &&  (nbjettche==0 || njet>3)) && ptll>45. &&   ( !sameflav || ( (njet!=0 || dymva1>0.60) && (njet!=1 || dymva1>0.30) && ( njet==0 || njet==1 || (pfmet > 45.0)) ) ) && (njet>=2 && njet<=3 && (jetpt3<=30 || !(jetpt3 > 30 && (  (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))   
  }
  if (what == "2Jet2012") {
   std::cout << " 2Jet2012 skim " << std::endl;
   Cut = "trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20. && (njet==0 || njet==1 || (dphilljetjet<pi/180.*165. || !sameflav )  ) && bveto_mu==1 && nextra==0 &&  (bveto_ip==1 &&  (nbjettche==0 || njet>3)) && ptll>45. &&   ( !sameflav || ( (njet!=0 || dymva1>0.60) && (njet!=1 || dymva1>0.30) && ( njet==0 || njet==1 || (pfmet > 45.0)) ) ) && (njet>=2 && njet<=3 && (jetpt3<=30 || !(jetpt3 > 30 && (  (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))               "; 
   //     trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20. && (njet==0 || njet==1 || (dphilljetjet<pi/180.*165. || !sameflav )  ) && bveto_mu==1 && nextra==0 &&  (bveto_ip==1 &&  (nbjettche==0 || njet>3)) && ptll>45. &&   ( !sameflav || ( (njet!=0 || dymva1>0.60) && (njet!=1 || dymva1>0.30) && ( njet==0 || njet==1 || (pfmet > 45.0)) ) ) && (njet>=2 && njet<=3 && (jetpt3<=30 || !(jetpt3 > 30 && (  (jeteta1-jeteta3 > 0 && jeteta2-jeteta3 < 0) || (jeteta2-jeteta3 > 0 && jeteta1-jeteta3 < 0)))))   
  }
  if (what == "012Jet2012") {
   std::cout << " 012Jet2012 skim " << std::endl;
   Cut = "trigger==1. && pfmet>20. && mll>12             && mpmet>20. && (njet==0 || njet==1 || (dphilljetjet<pi/180.*165. || !sameflav )  ) && bveto_mu==1 && nextra==0 &&  (bveto_ip==1                             )                                                                                                                                            "; 
   //     trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20. && (njet==0 || njet==1 || (dphilljetjet<pi/180.*165. || !sameflav )  ) && bveto_mu==1 && nextra==0 &&  (bveto_ip==1 &&  (nbjettche==0 || njet>3)) && ptll>45. &&   ( !sameflav || ( (njet!=0 || dymva1>0.60) && (njet!=1 || dymva1>0.30) && ( njet==0 || njet==1 || (pfmet > 45.0)) ) )  
  }
  if (what == "DYtautau2012") {
   std::cout << " DYtautau2012 skim " << std::endl;
   Cut = "trigger==1. &&              mll>12                                                                                                 && bveto_mu==1 && nextra==0 &&  (bveto_ip==1 &&  (nbjettche==0 || njet>3))                                                                                                                                            "; 
   //     trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20. && (njet==0 || njet==1 || (dphilljetjet<pi/180.*165. || !sameflav )  ) && bveto_mu==1 && nextra==0 &&  (bveto_ip==1 &&  (nbjettche==0 || njet>3)) && ptll>45. &&   ( !sameflav || ( (njet!=0 || dymva1>0.60) && (njet!=1 || dymva1>0.30) && ( njet==0 || njet==1 || (pfmet > 45.0)) ) )  
  }
  if (what == "MultiJet2012") {
   std::cout << " MultiJet2012 SUSY skim " << std::endl;
   Cut = "trigger==1. && pfmet>80. && mll>12               "; 
  }
  if (what == "Susy2jet2012") {
   std::cout << " Susy2jet2012 skim " << std::endl;
   Cut = "trigger==1. && pfmet>20. && mll>12 && zveto==1 && mpmet>20.                        && (dphilljetjet<pi/180.*165. || !sameflav )                   && nextra==0                                                && ptll>45.                                                                                                    &&  pfmet > 45.0       &&   njet>=2         "; 
  }
 }
 
 std::cout << " Cut = " << Cut.c_str() << std::endl;
 
 TFile* f = new TFile(inputFileName.c_str(), "READ");    
 TTree *treeJetLepVect;
 std::cout << " Get tree ... " << std::endl;
 treeJetLepVect = (TTree*) f->Get(treeName.c_str());

 
 std::cout << " Create new File ... " << std::endl;
 TFile outputRootFile ( outputFileName.c_str(), "RECREATE") ;
 outputRootFile.cd () ;

 int totNumEvents = treeJetLepVect->GetEntries(Cut.c_str());
 std::cout << " totNumEvents   = " << totNumEvents   << std::endl;
 treeJetLepVect->SetEstimate(treeJetLepVect->GetEntries());
 
 treeJetLepVect->SetEntryList(0); 
 treeJetLepVect->Draw(">> myList",Cut.c_str(),"entrylist");
 TEntryList *myList = (TEntryList*) gDirectory->Get("myList");
 treeJetLepVect->SetEntryList(myList); 
 
 std::cout << " tot = " << myList->GetN() << " = " << totNumEvents << " =? " << treeJetLepVect -> GetEntries () << std::endl;
 
 TTree* cloneTree = treeJetLepVect -> CloneTree (0) ;
  
 for ( int iEntry = 0; iEntry < myList -> GetN () ; iEntry++) { 
  treeJetLepVect -> GetEntry (myList->Next());
  cloneTree -> Fill () ;
 }
 cloneTree -> AutoSave () ;
 outputRootFile.Close () ;
  
}





