
///==== Modify Result plot removing one sample              ====
///==== and adding information from data driven estimation ====

#include <iomanip>

void DrawStack(THStack* hs, TString option){ 
 TObjArray* histos = hs->GetStack () ;
 Int_t number = histos->GetEntries();
 TH1F* last = (TH1F*) histos->At (number-1) ;
 TString newoption = Form ("hist%s",option.Data());
 last->Draw (newoption) ;
 for (int i = number-2 ; i >=0 ; --i) {
  TH1F * histo = (TH1F*) histos->At (i) ;
  Style_t origStyle = histo->GetFillStyle ();
  Color_t origColor = histo->GetFillColor ();
  TH1F* dummy = (TH1F*) histo->Clone () ;
  dummy->SetFillStyle (1001) ; 
  dummy->SetFillColor (10) ;    
  TString newoptionIn = Form ("same hist %s",option.Data());
  dummy->Draw (newoptionIn) ;
  histo->Draw (newoptionIn) ;
 }
}

void DrawStackError(THStack* hs, double syst){ 
 TObjArray* histos = hs->GetStack () ;
 Int_t number = histos->GetEntries();
 TH1F* last = (TH1F*) histos->At (number-1) ;
 last->DrawClone ("hist") ;
 for (int i = number-2 ; i >=0 ; --i) {
  TH1F * histo = (TH1F*) histos->At (i) ;
  Style_t origStyle = histo->GetFillStyle ();
  Color_t origColor = histo->GetFillColor ();
  TH1F* dummy = (TH1F*) histo->Clone () ;
  dummy->SetFillStyle (1001) ; 
  dummy->SetFillColor (10) ;        
  dummy->Draw ("same hist") ;
  histo->Draw ("same hist") ;
 }
 Style_t origStyleLast = last->GetFillStyle ();
 Color_t origColorLast = last->GetFillColor ();
 last->SetFillStyle(3335);
 last->SetFillColor(kBlack);
 last->SetMarkerSize(0);
 
 std::vector <double> vErr ;
 for (int iBin = 0 ; iBin < last->GetNbinsX(); iBin++) {
  double additionalError = last->GetBinContent(iBin+1) * syst;
  vErr.push_back(last->GetBinError(iBin+1));
  last->SetBinError(iBin+1,sqrt(additionalError*additionalError + last->GetBinError(iBin+1) * last->GetBinError(iBin+1)) );
 }
 last->DrawClone ("sameE2") ;
 //---- restore hist ----
 last->SetFillStyle(origStyleLast);
 last->SetFillColor(origColorLast);
 for (int iBin = 0 ; iBin < last->GetNbinsX(); iBin++) {
  last->SetBinError(iBin+1, vErr.at(iBin));
 }
}

TGraphErrors*  grPullPlot_grPool(TH1F* hDATA, TH1F* hMC){
 int nbin = hDATA->GetNbinsX();
 double max = hDATA->GetXaxis()->GetXmax();
 double min = hDATA->GetXaxis()->GetXmin();
 std::string name1 = hDATA->GetName();
 std::string name2 = hMC->GetName(); 
 std::string nameNew = name1 + name2; 
 
 TGraphErrors* grPool = new TGraphErrors();
 TGraphErrors* grPoolMC = new TGraphErrors();
 int point = 0; 
 for (int iBin = 0; iBin<nbin; iBin++){
  double X = hDATA->GetBinCenter(iBin+1);
  double DATA = hDATA->GetBinContent(iBin+1);
  double MC = hMC->GetBinContent(iBin+1);
  double errMC = hMC->GetBinError(iBin+1);
  
  grPool->SetPoint      (point, X, (MC ? DATA/MC : 0));
  grPool->SetPointError (point, 0, (MC ? sqrt(DATA)/MC : 0));
  
  grPoolMC->SetPoint      (point, X, 1.);
  grPoolMC->SetPointError (point, 0, (MC ? errMC / MC : 0));
  point++;
 }
 grPool->SetLineColor(kRed);
 grPool->SetLineWidth(2);
 grPool->SetMarkerColor(kRed);
 grPool->SetMarkerStyle(20);
 grPool->SetMarkerSize(1);
 grPool->GetXaxis()->SetTitle(hMC->GetXaxis()->GetTitle()); 
 grPool->GetYaxis()->SetTitle("DATA/MC"); 
 grPool->GetYaxis()->SetRangeUser(0.,3.); 
 
 grPoolMC->SetLineWidth(0);
 grPoolMC->SetMarkerSize(0);
 grPoolMC->SetFillColor(kGreen);
 grPoolMC->GetXaxis()->SetTitle(hMC->GetXaxis()->GetTitle()); 
 grPoolMC->GetYaxis()->SetTitle("DATA/MC"); 
 grPoolMC->GetYaxis()->SetRangeUser(0.,3.); 
 
 return grPool; 
}

TGraphErrors*  grPullPlot_grPoolMC(TH1F* hDATA, TH1F* hMC){
 int nbin = hDATA->GetNbinsX();
 double max = hDATA->GetXaxis()->GetXmax();
 double min = hDATA->GetXaxis()->GetXmin();
 std::string name1 = hDATA->GetName();
 std::string name2 = hMC->GetName(); 
 std::string nameNew = name1 + name2; 
 
 TGraphErrors* grPool = new TGraphErrors();
 TGraphErrors* grPoolMC = new TGraphErrors();
 int point = 0; 
 for (int iBin = 0; iBin<nbin; iBin++){
  double X = hDATA->GetBinCenter(iBin+1);
  double DATA = hDATA->GetBinContent(iBin+1);
  double MC = hMC->GetBinContent(iBin+1);
  double errMC = hMC->GetBinError(iBin+1);
  
  grPool->SetPoint      (point, X, (MC ? DATA/MC : 0));
  grPool->SetPointError (point, 0, (MC ? sqrt(DATA)/MC : 0));
  
  grPoolMC->SetPoint      (point, X, 1.);
  grPoolMC->SetPointError (point, 0, (MC ? errMC / MC : 0));
  point++;
 }
 grPool->SetLineColor(kRed);
 grPool->SetLineWidth(2);
 grPool->SetMarkerColor(kRed);
 grPool->SetMarkerStyle(20);
 grPool->SetMarkerSize(1);
 grPool->GetXaxis()->SetTitle(hMC->GetXaxis()->GetTitle()); 
 grPool->GetYaxis()->SetTitle("DATA/MC"); 
 grPool->GetYaxis()->SetRangeUser(0.,3.); 
 
 grPoolMC->SetLineWidth(0);
 grPoolMC->SetMarkerSize(0);
 grPoolMC->SetFillColor(kGreen);
 grPoolMC->GetXaxis()->SetTitle(hMC->GetXaxis()->GetTitle()); 
 grPoolMC->GetYaxis()->SetTitle("DATA/MC"); 
 grPoolMC->GetYaxis()->SetRangeUser(0.,3.); 
 
 return grPoolMC; 
}


/**
 * Modify Plot with Data Driven results
 */

int ModifyPlot(
 TString StepName       = "0_0",
 TString SampleToChange = "top",
 TString nameFileIn    = "HiggsMass_120.root",
 TString nameFileWithDataDrivenResults = "dd.txt",
 int numSignalSets = 1
) { 
 
 std::string buffer;
 std::ifstream inFileDD(nameFileWithDataDrivenResults);
 std::vector<int> values;
 std::vector<int> errors;
 while(!inFileDD.eof()){
  getline(inFileDD,buffer);
  if (buffer != ""){ ///---> save from empty line at the end!
   if (buffer.at(0) != '#'){ 
    std::stringstream line( buffer );       
    double value, error;
    line >> value; 
    line >> error;
    values.push_back(value);
    errors.push_back(error);
    
    std::cout << " " << value << " +/- " << error << std::endl;
   } 
  }
 }
 
 
 
 TFile* fileIn = new TFile(nameFileIn, "READ");
 
 TString nameTStack       = Form("Data/%s_stack",StepName.Data());
 TString nameTStack_Clone = Form("%s_stack_old",StepName.Data());
 std::cout << " nameTStack = " << nameTStack.Data() << " ::: " << fileIn->Get(nameTStack) << std::endl;
 THStack* hsBackgroundOld = (THStack*) ((THStack*) fileIn->Get(nameTStack))->Clone(nameTStack_Clone.Data());
 THStack* hsBackgroundNew = new THStack("new","new");
 
 THStack* hsSignalOld[100];
 
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  nameTStack       = Form("Data/%s_%d_stack_signal",StepName.Data(),iSignalSet);
  nameTStack_Clone = Form("%s_%d_stack_signal_old",StepName.Data(),iSignalSet);
  std::cout << " nameTStack[iSignalSet:" << iSignalSet << "::" << numSignalSets << "] = " << nameTStack.Data() << " ::: " << fileIn->Get(nameTStack) << std::endl;
  hsSignalOld[iSignalSet] = (THStack*) ((THStack*) fileIn->Get(nameTStack))->Clone(nameTStack_Clone.Data());
 }
 
 TString nameHisto = Form ("Data/DATA_%s_Tot_temp",StepName.Data());
 TString nameHisto_Clone = Form ("DATA_%s_Tot_temp_old",StepName.Data());
 std::cout << " nameHisto = " << nameHisto.Data() << " ::: " << fileIn->Get(nameHisto) << std::endl;
 TH1F* hDATA = (TH1F*) ((TH1F*) fileIn->Get(nameHisto))->Clone(nameHisto_Clone.Data());
 TH1F* histoNoStack[100];
 
 
 ///==== modify background histogram ====
 TObjArray* histos = hsBackgroundOld->GetStack () ;
 Int_t number = histos->GetEntries();
 TH1F* histoModified;
 for (int i = 0; i< number; i++) {
  TH1F * histo = (TH1F*) histos->At (i) ;
  nameHisto       = Form("%s_%s_Tot_temp",SampleToChange.Data(),StepName.Data());
  std::cout << " name = " << setw (25) << histo->GetName() << setw (5) << " :: " << setw (25) << nameHisto.Data() << std::endl;
  std::string string1 = histo->GetName();
  std::string string2 = nameHisto.Data();
  
  nameHisto = Form ("Data/%s",histo->GetName());
  nameHisto_Clone = Form ("%s_old",histo->GetName());
  std::cout << " nameHisto = " << nameHisto.Data() << " ::: " << fileIn->Get(nameHisto) << std::endl;
  histoNoStack[i] = (TH1F*) ((TH1F*) fileIn->Get(nameHisto))->Clone(nameHisto_Clone.Data());
  
  if (string1 == string2) {
   std::cout << " ---> modified " << std::endl;
   histoModified = histoNoStack[i]->Clone("modified");
   for (int ivalues = 0; ivalues < values.size(); ivalues++) {
    if (values.at(ivalues) != -1) {
     std::cout << " histoModified(" << ivalues << ") = " << histoModified->GetBinContent(ivalues+1) << " ~~~> " << values.at(ivalues) << std::endl;     
     histoModified -> SetBinContent(ivalues+1, values.at(ivalues));
     histoModified -> SetBinError  (ivalues+1, errors.at(ivalues));
    }
    else {
     std::cout << " histoModified(" << ivalues << ") = " << histoModified->GetBinContent(ivalues+1) << " ===> " << histoModified->GetBinContent(ivalues+1) << std::endl;
    }
   }
   hsBackgroundNew->Add(histoModified);
  }
  else {
   hsBackgroundNew->Add(histoNoStack[i]);
  }
 }
 
 
 ///==== plot Old ====
 
 std::cout << " ********************************************* " << std::endl;
 
 TCanvas* cResultWODD = new TCanvas("cResultWODD","cResultWODD",500,500);
 TCanvas* cResultWODDPull = new TCanvas("cResultWODDPull","cResultWODDPull",500,500);
 
 TH1F* hResultWODDSumMC = (TH1F*) (hsBackgroundOld->GetStack()->Last());
 TH1F* hResultWODDSignalSumMC[100];
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  std::cerr << " :::: " << hsSignalOld[iSignalSet] << std::endl;
  hResultWODDSignalSumMC[iSignalSet] =  (TH1F*) (hsSignalOld[iSignalSet]->GetStack()->Last());
 }
 
 cResultWODD->cd();
 gPad->SetBottomMargin(0.17);
 
 DrawStackError(hsBackgroundOld,0.00);
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  DrawStack(hsSignalOld[iSignalSet],"Esame");
 }
 
 hDATA -> Draw("EsameP");
 gPad->SetLogy();
 gPad->SetGrid();
 
 cResultWODDPull->cd();
 gPad->SetBottomMargin(0.17);
 
 TGraphErrors* grPullResultWODDSumMC   = grPullPlot_grPool  (hDATA, hResultWODDSumMC);
 TGraphErrors* grPullResultWODDSumMCMC = grPullPlot_grPoolMC(hDATA, hResultWODDSumMC);
 
 if (grPullResultWODDSumMCMC) grPullResultWODDSumMCMC -> Draw("AE3");
 if (grPullResultWODDSumMC)   grPullResultWODDSumMC   -> Draw("PsameE");  
 
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  std::cout << " Higgs [0] " << std::endl; 
  for (int ivalues = 0; ivalues < values.size(); ivalues++) {
   std::cout << "   DATA::MC::MC+Higgs " << setw (10) << hDATA->GetBinContent(ivalues+1) << " :: " << setw (10) << hResultWODDSumMC->GetBinContent(ivalues+1) << " :: " << setw (10) << hResultWODDSumMC->GetBinContent(ivalues+1)+hResultWODDSignalSumMC[iSignalSet]->GetBinContent(ivalues+1) << std::endl;
  }
  std::cout << " *************** " << std::endl;
 }
 
 
 ///==== plot ====
 
 TCanvas* cResult = new TCanvas("cResult","cResult",500,500);
 TCanvas* cResultPull = new TCanvas("cResultPull","cResultPull",500,500);
 
 TH1F* hResultSumMC = (TH1F*) (hsBackgroundNew->GetStack()->Last());
 TH1F* hResultSignalSumMC[100];
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  std::cerr << " :::: " << hsSignalOld[iSignalSet] << std::endl;
  hResultSignalSumMC[iSignalSet] =  (TH1F*) (hsSignalOld[iSignalSet]->GetStack()->Last());
 }
 
 cResult->cd();
 gPad->SetBottomMargin(0.17);
 
 DrawStackError(hsBackgroundNew,0.00);
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  DrawStack(hsSignalOld[iSignalSet],"Esame");
 }
 
 hDATA -> Draw("EsameP");
 gPad->SetLogy();
 gPad->SetGrid();
 
 cResultPull->cd();
 gPad->SetBottomMargin(0.17);
 
 TGraphErrors* grPullResultSumMC   = grPullPlot_grPool  (hDATA, hResultSumMC);
 TGraphErrors* grPullResultSumMCMC = grPullPlot_grPoolMC(hDATA, hResultSumMC);
 
 if (grPullResultSumMCMC) grPullResultSumMCMC -> Draw("AE3");
 if (grPullResultSumMC)   grPullResultSumMC   -> Draw("PsameE");  
 
 for (int iSignalSet = 0; iSignalSet < numSignalSets; iSignalSet++) {
  std::cout << " Higgs [0] " << std::endl; 
  for (int ivalues = 0; ivalues < values.size(); ivalues++) {
   std::cout << "   DATA::MC::MC+Higgs " << setw (10) << hDATA->GetBinContent(ivalues+1) << " :: " << setw (10) << hResultSumMC->GetBinContent(ivalues+1) << " :: " << setw (10) << hResultSumMC->GetBinContent(ivalues+1)+hResultSignalSumMC[iSignalSet]->GetBinContent(ivalues+1) << std::endl;
  }
  std::cout << " *************** " << std::endl;
 }
 
 
 

 
 
 TCanvas* cLegend = (TCanvas*) fileIn->Get("cLegend");
 cLegend->Draw();
 
 
}










