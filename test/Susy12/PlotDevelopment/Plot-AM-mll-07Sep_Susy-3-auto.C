#include "TString.h"
#include "TH1F.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "TFile.h"

  #include "PlotVHqqHggH.C"


void Plot_AM_mll_07Sep_Susy_3_auto() {
 TString cutNameBefore = Form("Data/");

 //                            cut_variable 
 TString cutNameAfter  = Form("_3_2_Tot_temp");

 gROOT->LoadMacro("PlotVHqqHggH.C+");
 gInterpreter->ExecuteMacro("LatinoStyle2.C");

 TCanvas* c1 = new TCanvas("mll","mll",500,600);
 TFile* f = new TFile("~/Cern/Code/VBF/qqHWW/AnalysisPackage_qqHWWlnulnu/out_test_Latinos_07Sep2012_2000_Run2012AB_8TeV_SUSY.root");


 PlotVHqqHggH* hs = new PlotVHqqHggH();

 hs->setLumi(5.063);
 hs->setLabel("m_{ll}");
 hs->addLabel("    #sqrt{s} = 8 TeV");

 TString name;

 std::vector<int> vectColourBkg;        
 std::vector<double> vectSystBkg;       
 std::vector<std::string> vectNameBkg;  
 std::vector<TH1F*> vectTHBkg;          

 std::vector<int> vectColourSig;      
 std::vector<double> vectSystSig;       
 std::vector<std::string> vectNameSig;  
 std::vector<TH1F*> vectTHSig;          

 ///==== signal (begin) ====

 name = Form("%sT2tt-350-70%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHSig.push_back ( (TH1F*) f->Get(name) );
 vectNameSig.push_back ("T2tt-stop350-lsp70");
 vectColourSig.push_back(6);

 name = Form("%sT2tt-500-70%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHSig.push_back ( (TH1F*) f->Get(name) );
 vectNameSig.push_back ("T2tt-stop500-lsp70");
 vectColourSig.push_back(97);

 name = Form("%sT2tt-350-100%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHSig.push_back ( (TH1F*) f->Get(name) );
 vectNameSig.push_back ("T2tt-stop350-lsp100");
 vectColourSig.push_back(70);

 name = Form("%sT2tt-500-100%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHSig.push_back ( (TH1F*) f->Get(name) );
 vectNameSig.push_back ("T2tt-stop500-lsp100");
 vectColourSig.push_back(65);

 name = Form("%sT2tt-500-200%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHSig.push_back ( (TH1F*) f->Get(name) );
 vectNameSig.push_back ("T2tt-stop500-lsp200");
 vectColourSig.push_back(5);

 name = Form("%sT2tt-200-0%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHSig.push_back ( (TH1F*) f->Get(name) );
 vectNameSig.push_back ("T2tt-stop200-lsp0");
 vectColourSig.push_back(7);

 ///==== signal (end)  ====

 name = Form("%sDATA%s",cutNameBefore.Data(),cutNameAfter.Data());
 hs->setDataHist ((TH1F*)f->Get(name));



 hs->setBlindBinSx(0);
 hs->setBlindBinDx(0);

 hs->setCutSx(-999,">");
 hs->setCutDx(-999,"<");


 ///==== background (begin)  ====

 name = Form("%sH-125%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHBkg.push_back ( (TH1F*) f->Get(name) );
 vectNameBkg.push_back ("H-125");
 vectColourBkg.push_back(633);
 vectSystBkg.push_back(0.00);


 name = Form("%sVV%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHBkg.push_back ( (TH1F*) f->Get(name) );
 vectNameBkg.push_back ("WZ/ZZ");
 vectColourBkg.push_back(858);
 vectSystBkg.push_back(0.00);

 name = Form("%sWJets%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHBkg.push_back ( (TH1F*) f->Get(name) );
 vectNameBkg.push_back ("W+jets");
 vectColourBkg.push_back(921);
 vectSystBkg.push_back(0.36);

 name = Form("%sTop%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHBkg.push_back ( (TH1F*) f->Get(name) );
 vectNameBkg.push_back ("top");
 vectColourBkg.push_back(400);
 vectSystBkg.push_back(0.00);

 name = Form("%sZJets%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHBkg.push_back ( (TH1F*) f->Get(name) );
 vectNameBkg.push_back ("DY+jets");
 vectColourBkg.push_back(418);
 vectSystBkg.push_back(0.00);
 name = Form("%sWW%s",cutNameBefore.Data(),cutNameAfter.Data());
 vectTHBkg.push_back ( (TH1F*) f->Get(name) );
 vectNameBkg.push_back ("WW");
 vectColourBkg.push_back(851);
 vectSystBkg.push_back(0.00);




 ///==== background (end)  ====


 hs->set_vectTHBkg     (vectTHBkg);      
 hs->set_vectNameBkg   (vectNameBkg);    
 hs->set_vectColourBkg (vectColourBkg);  
 hs->set_vectSystBkg   (vectSystBkg);    

 hs->set_vectTHSig     (vectTHSig);      
 hs->set_vectNameSig   (vectNameSig);    
 hs->set_vectColourSig (vectColourSig);  
 //  hs->set_vectSystSig   (vectSystSig);



 hs->set_addSignal (0); //---- stack signal = 1, no stack signal = 0  


 hs->prepare();


 ///==== draw ====



 hs->Draw(c1,1,true);

 c1->Print("07Sep_Susy_3/mll.pdf");
 c1->Print("07Sep_Susy_3/mll.png");

 c1->SetLogy();
 hs->Draw(c1,1,true);
 c1->Print("07Sep_Susy_3/mll_logy.pdf");
 c1->Print("07Sep_Susy_3/mll_logy.png");
}


