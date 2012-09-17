#include <iostream>
#include <fstream>


void AMPlotMacroCreator_Susy() {
 
 TString fileVar = Form("var07Sep.txt");
 TString date    = Form("07Sep_Susy");
 
 TString file    = Form("out_test_Latinos_07Sep2012_2000_Run2012AB_8TeV_SUSY.root");
 
 TString lumi    = Form("5.063");
 
 
 for (int iCut = 0; iCut < 7; iCut++) {
  
  TString CommandToExec = Form("rm -r %s_%d",date.Data(),iCut);
  gSystem->Exec(CommandToExec);  
  
  CommandToExec = Form("mkdir %s_%d",date.Data(),iCut);
  gSystem->Exec(CommandToExec);  
  
  CommandToExec = Form("cp index.php %s_%d",date.Data(),iCut);
  gSystem->Exec(CommandToExec);  
  
  
  
  
  //---- red file "var" ----
  std::vector<std::string> vVar_simple;
  std::vector<std::string> vVar;
  std::vector<int>         vVar_num;
  std::vector<int>         vBlindBinSx;
  std::vector<int>         vBlindBinDx;
  std::vector<double>      vCutValueSx;
  std::vector<double>      vCutValueDx;
  std::ifstream indata;
  
  indata.open(fileVar.Data());
  if(!indata) {
   std::cerr << "Error: file " << fileVar.Data() << " could not be opened" << std::endl;
   return 1;
  }
  
  std::string variable_simple;
  std::string variable;
  int variable_num;
  int blind_num_sx;
  int blind_num_dx;
  double cut_value_sx;
  double cut_value_dx;
  std::string buffer;
  
  while ( !indata.eof() ) { // keep reading until end-of-file
  getline(indata,buffer);
  if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end!
   std::stringstream line( buffer );      
   line >> variable_simple; 
   line >> variable; 
   line >> variable_num; 
   line >> blind_num_sx;
   line >> blind_num_dx;
   line >> cut_value_sx;
   line >> cut_value_dx;
   vVar_simple.push_back(variable_simple);
   vVar.push_back(variable);
   vVar_num.push_back(variable_num);
   vBlindBinSx.push_back(blind_num_sx);
   vBlindBinDx.push_back(blind_num_dx);
   vCutValueSx.push_back(cut_value_sx);
   vCutValueDx.push_back(cut_value_dx);
  }
  }
  indata.close();
  
  
  std::cout << std::endl;
  
  for (int iVar=0; iVar<vVar_simple.size(); iVar++) {
   TString name = Form ("Plot-AM-%s-%s-%d-auto.C",vVar_simple.at(iVar).c_str(), date.Data(), iCut);
   ofstream myfile;
   myfile.open (name.Data());
   
   myfile << "#include \"TString.h\"" << std::endl;
   myfile << "#include \"TH1F.h\"" << std::endl;
   myfile << "#include \"TSystem.h\"" << std::endl;
   myfile << "#include \"TInterpreter.h\"" << std::endl;
   myfile << "#include \"TFile.h\"" << std::endl;
   myfile << std::endl;
   myfile << "  #include \"PlotVHqqHggH.C\"" << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   myfile << "void Plot_AM_" << vVar_simple.at(iVar).c_str() << "_" << date.Data() << "_" << iCut << "_auto() {" << std::endl;
   myfile << " TString cutNameBefore = Form(\"Data/\");" << std::endl;
   myfile << std::endl;
   myfile << " //                            cut_variable " << std::endl;
   myfile << " TString cutNameAfter  = Form(\"_" << iCut << "_" << vVar_num.at(iVar) << "_Tot_temp\");" << std::endl;
   myfile << std::endl;  
   myfile << " gROOT->LoadMacro(\"PlotVHqqHggH.C+\");" << std::endl;   
   myfile << " gInterpreter->ExecuteMacro(\"LatinoStyle2.C\");" << std::endl;
   myfile << std::endl;  
   myfile << " TCanvas* c1 = new TCanvas(\"" <<  vVar_simple.at(iVar).c_str() << "\",\"" <<  vVar_simple.at(iVar).c_str() << "\",500,600);" << std::endl;
   myfile << " TFile* f = new TFile(\"~/Cern/Code/VBF/qqHWW/AnalysisPackage_qqHWWlnulnu/" << file.Data() << "\");" << std::endl;
   myfile << std::endl;  
   myfile << std::endl;  
   myfile << " PlotVHqqHggH* hs = new PlotVHqqHggH();" << std::endl;
   myfile << std::endl;
   myfile << " hs->setLumi(" << lumi.Data() << ");" << std::endl;
   myfile << " hs->setLabel(\""<<  vVar.at(iVar).c_str() <<"\");" << std::endl;
   myfile << " hs->addLabel(\"    #sqrt{s} = 8 TeV\");" << std::endl;
   myfile << std::endl;
   myfile << " TString name;" << std::endl;
   myfile << std::endl;
   myfile << " std::vector<int> vectColourBkg;        " << std::endl;
   myfile << " std::vector<double> vectSystBkg;       " << std::endl;
   myfile << " std::vector<std::string> vectNameBkg;  " << std::endl;
   myfile << " std::vector<TH1F*> vectTHBkg;          " << std::endl;
   myfile << std::endl;
   myfile << " std::vector<int> vectColourSig;      " << std::endl;
   myfile << " std::vector<double> vectSystSig;       " << std::endl;
   myfile << " std::vector<std::string> vectNameSig;  " << std::endl;
   myfile << " std::vector<TH1F*> vectTHSig;          " << std::endl;
   
   myfile << std::endl;
   myfile << " ///==== signal (begin) ====" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sT2tt-350-70%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHSig.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameSig.push_back (\"T2tt-stop350-lsp70\");" << std::endl;
   myfile << " vectColourSig.push_back(6);" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sT2tt-500-70%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHSig.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameSig.push_back (\"T2tt-stop500-lsp70\");" << std::endl;
   myfile << " vectColourSig.push_back(97);" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sT2tt-350-100%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHSig.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameSig.push_back (\"T2tt-stop350-lsp100\");" << std::endl;
   myfile << " vectColourSig.push_back(70);" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sT2tt-500-100%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHSig.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameSig.push_back (\"T2tt-stop500-lsp100\");" << std::endl;
   myfile << " vectColourSig.push_back(65);" << std::endl;
   myfile << std::endl;

   myfile << " name = Form(\"%sT2tt-500-200%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHSig.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameSig.push_back (\"T2tt-stop500-lsp200\");" << std::endl;
   myfile << " vectColourSig.push_back(5);" << std::endl;
   myfile << std::endl;
   
   myfile << " name = Form(\"%sT2tt-200-0%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHSig.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameSig.push_back (\"T2tt-stop200-lsp0\");" << std::endl;
   myfile << " vectColourSig.push_back(7);" << std::endl;
   myfile << std::endl;
   
   
      
//    
//    myfile << " name = Form(\"%sT2bw%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
//    myfile << " vectTHSig.push_back ( (TH1F*) f->Get(name) );" << std::endl;
//    myfile << " vectNameSig.push_back (\"T2bw\");" << std::endl;
//    myfile << " vectColourSig.push_back(639);" << std::endl;
//    myfile << std::endl;
   myfile << " ///==== signal (end)  ====" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sDATA%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " hs->setDataHist ((TH1F*)f->Get(name));" << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   myfile << " hs->setBlindBinSx("<< vBlindBinSx.at(iVar) << ");" << std::endl;
   myfile << " hs->setBlindBinDx("<< vBlindBinDx.at(iVar) << ");" << std::endl;
   myfile << std::endl;
   myfile << " hs->setCutSx("<< vCutValueSx.at(iVar) << ",\">\");" << std::endl;
   myfile << " hs->setCutDx("<< vCutValueDx.at(iVar) << ",\"<\");" << std::endl;
   myfile << std::endl;  
   myfile << std::endl;
   myfile << " ///==== background (begin)  ====" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sH-125%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHBkg.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameBkg.push_back (\"H-125\");" << std::endl;
   myfile << " vectColourBkg.push_back(633);" << std::endl;
   myfile << " vectSystBkg.push_back(0.00);" << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sVV%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHBkg.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameBkg.push_back (\"WZ/ZZ\");" << std::endl;
   myfile << " vectColourBkg.push_back(858);" << std::endl;
   myfile << " vectSystBkg.push_back(0.00);" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sWJets%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHBkg.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameBkg.push_back (\"W+jets\");" << std::endl;
   myfile << " vectColourBkg.push_back(921);" << std::endl;
   myfile << " vectSystBkg.push_back(0.36);" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sTop%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHBkg.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameBkg.push_back (\"top\");" << std::endl;
   myfile << " vectColourBkg.push_back(400);" << std::endl;
   //   myfile << " vectSystBkg.push_back(0.20);" << std::endl;
   myfile << " vectSystBkg.push_back(0.00);" << std::endl;
   myfile << std::endl;
   myfile << " name = Form(\"%sZJets%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHBkg.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameBkg.push_back (\"DY+jets\");" << std::endl;
   myfile << " vectColourBkg.push_back(418);" << std::endl;
   //   myfile << " vectSystBkg.push_back(0.20);" << std::endl;
   myfile << " vectSystBkg.push_back(0.00);" << std::endl;
   
   myfile << " name = Form(\"%sWW%s\",cutNameBefore.Data(),cutNameAfter.Data());" << std::endl;
   myfile << " vectTHBkg.push_back ( (TH1F*) f->Get(name) );" << std::endl;
   myfile << " vectNameBkg.push_back (\"WW\");" << std::endl;
   myfile << " vectColourBkg.push_back(851);" << std::endl;
   myfile << " vectSystBkg.push_back(0.00);" << std::endl;
   myfile << std::endl;
   
   myfile << std::endl;
   myfile << std::endl;
   
   
   myfile << std::endl;
   myfile << " ///==== background (end)  ====" << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   myfile << " hs->set_vectTHBkg     (vectTHBkg);      " << std::endl; 
   myfile << " hs->set_vectNameBkg   (vectNameBkg);    " << std::endl;
   myfile << " hs->set_vectColourBkg (vectColourBkg);  " << std::endl;
   myfile << " hs->set_vectSystBkg   (vectSystBkg);    " << std::endl;
   myfile << std::endl;  
   myfile << " hs->set_vectTHSig     (vectTHSig);      " << std::endl;
   myfile << " hs->set_vectNameSig   (vectNameSig);    " << std::endl;
   myfile << " hs->set_vectColourSig (vectColourSig);  " << std::endl;
   myfile << " //  hs->set_vectSystSig   (vectSystSig);" << std::endl;
   myfile << std::endl;
   
   myfile << std::endl;
   myfile << std::endl;
   myfile << " hs->set_addSignal (0); //---- stack signal = 1, no stack signal = 0  " << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   
   
   myfile << " hs->prepare();" << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   myfile << " ///==== draw ====" << std::endl;
   myfile << std::endl;   
   //    myfile << " hs->addLabel(\""<< date.Data() <<"\");" << std::endl; // ---- add folder name on plot! to combine later!
   myfile << std::endl;
   myfile << std::endl;
   myfile << " hs->Draw(c1,1,true);" << std::endl;
   myfile << std::endl;
   myfile << " c1->Print(\"" << date.Data() << "_" << iCut << "/" <<  vVar_simple.at(iVar).c_str() << ".pdf\");" << std::endl;
   myfile << " c1->Print(\"" << date.Data() << "_" << iCut << "/" <<  vVar_simple.at(iVar).c_str() << ".png\");" << std::endl;
   //   myfile << " c1->Print(\"" << date.Data() << "_" << iCut << "/" <<  vVar_simple.at(iVar).c_str() << ".gif\");" << std::endl;
   myfile << std::endl;
   
   myfile << " c1->SetLogy();" << std::endl;
   myfile << " hs->Draw(c1,1,true);" << std::endl;
   myfile << " c1->Print(\"" << date.Data() << "_" << iCut << "/" <<  vVar_simple.at(iVar).c_str() << "_logy.pdf\");" << std::endl;
   myfile << " c1->Print(\"" << date.Data() << "_" << iCut << "/" <<  vVar_simple.at(iVar).c_str() << "_logy.png\");" << std::endl;
   //   myfile << " c1->Print(\"" << date.Data() << "_" << iCut << "/" <<  vVar_simple.at(iVar).c_str() << "_logy.gif\");" << std::endl;
   
   myfile << "}" << std::endl;
   myfile << std::endl;
   myfile << std::endl;
   
   
   myfile.close(); 
   
   CommandToExec = Form("root -l -q -b %s+",name.Data());
   gSystem->Exec(CommandToExec);  
   
  }
  
  
  
  for (int iVar=0; iVar<vVar_simple.size(); iVar++) {
   TString name = Form ("Plot-AM-%s-%s-%d-auto.C",vVar_simple.at(iVar).c_str(), date.Data(), iCut);
   std::cout << "r00t " << name.Data() << "+" << std::endl;
  }
  
  std::cout << std::endl;
  std::cout << std::endl;
  
  std::cout << "scp -r " << date.Data() << "_" << iCut << "/ amassiro@lxplus.cern.ch:/afs/cern.ch/user/a/amassiro/www/HWW/Plot/ICHEP2012/plot/07Sep2012/" << std::endl;
  
  std::cout << std::endl;
  std::cout << std::endl;
  
 }
 
 gApplication->Terminate(0);
 
}













