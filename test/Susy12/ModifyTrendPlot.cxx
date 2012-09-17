
///==== Modify Trend plot removing one sample              ====
///==== and adding information from data driven estimation ====

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
 for (int i = number-2 ; i >=0 ; --i) 
 {
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


//  r00t test/Latinos/ModifyTrendPlot.cxx\(\"cTrend\",\"test/Latinos/sample_change.txt\",\"top\",\"out_test_Latinos_6Oct.root\",\"DDresult.txt\",\"out.root\"\)

int ModifyTrendPlot(
 TString CanvasName     = "cTrend",
 TString ListSamples    = "sample_change.txt",
 TString SampleToChange = "top",
 TString nameFileIn    = "HiggsMass_120.root",
 TString nameFileWithDataDrivenResults = "dd.txt",
 TString nameFileOut   = "HiggsMass_120.root"
){ 
 
 char *nameSample[1000];
 int numberOfSamples = 0;
 std::ifstream inFileSamples(ListSamples);
 std::string buffer; 
 std::vector<std::string> reduced_name_samples;
 std::vector<int> reduced_name_samples_signal_background;
 
 while(!inFileSamples.eof()){
  getline(inFileSamples,buffer);
  if (buffer != ""){ ///---> save from empty line at the end!
   if (buffer.at(0) != '#'){ 
    std::stringstream line( buffer );       
    nameSample[numberOfSamples] = new char [1000];
    line >> nameSample[numberOfSamples]; 
    std::cout << nameSample[numberOfSamples] << " ";
    int temp_flag;
    line >> temp_flag; 
    std::cout << " --> " << temp_flag << std::endl;
    reduced_name_samples.push_back(std::string(nameSample[numberOfSamples]));
    reduced_name_samples_signal_background.push_back(temp_flag);
    numberOfSamples++;
   } 
  }
 }
 
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
   } 
  }
 }
 
 
 
 
 
 
 TFile* fileIn = new TFile(nameFileIn, "READ");
 
 TH1F* hTrendModified;
 THStack* hsTrendModified;
 
 TH1F* hTrend[100];
 THStack* hsTrend;
 THStack* hsSignalTrend;
 
 hsTrendModified = new THStack("TrendModified","TrendModified");
 hsTrend = new THStack("Trend","Trend");
 hsSignalTrend = new THStack("TrendSignal","TrendSignal");
 
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  TString nameTHTrend = Form("DataTrend/%s_Trend",reduced_name_samples.at(iName).c_str());
  std::cout << " nameTHTrend[" << iName << "] = " << nameTHTrend.Data() << std::endl;
  TString nameTHTrend_Clone = Form("DataTrend/%s_Trend_Clone",reduced_name_samples.at(iName).c_str());
  hTrend[iName] = (TH1F*) ((TH1F*) fileIn->Get(nameTHTrend))->Clone(nameTHTrend_Clone.Data());
 } 
 
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  if (reduced_name_samples.at(iName) != SampleToChange.Data()) {
   if (reduced_name_samples_signal_background.at(iName) == 0) { //---- background
    hsTrend->Add(hTrend[iName]);
    hsTrendModified->Add(hTrend[iName]);
   }
   else if (reduced_name_samples_signal_background.at(iName) == 1){ //---- signal
    hsSignalTrend->Add(hTrend[iName]);
   }
  }
  else {
   hTrendModified = hTrend[iName]->Clone("modified");
   for (int ivalues = 0; ivalues < values.size(); ivalues++) {
    if (values.at(ivalues) != -1) {
     std::cout << " hTrend[" << iName << "](" << ivalues << ") = " << hTrend[iName]->GetBinContent(ivalues+1) << " ~~~> " << values.at(ivalues) << std::endl;     
     hTrend[iName] -> SetBinContent(ivalues+1, values.at(ivalues));
     hTrend[iName] -> SetBinError  (ivalues+1, values.at(ivalues));
    }
    else {
     std::cout << " hTrend[" << iName << "](" << ivalues << ") = " << hTrend[iName]->GetBinContent(ivalues+1) << " ===> " << hTrend[iName]->GetBinContent(ivalues+1) << std::endl;
    }
   }
   hsTrend->Add(hTrend[iName]);
   hsTrendModified->Add(hTrendModified);
  }
 }
 
 
 
 TCanvas* cTrend = new TCanvas("cTrend","cTrend",400,400);
 TCanvas* cTrendPull = new TCanvas("cTrendPull","cTrendPull",400,400);
 
 TH1F* hTrendSumMC       = ((TH1F*)(hsTrend->GetStack()->Last()));
 TH1F* hTrendSignalSumMC = ((TH1F*)(hsSignalTrend->GetStack()->Last()));
 
 
 cTrend->cd();
 gPad->SetBottomMargin(0.17);
 
 DrawStackError(hsTrend,0.00);
 DrawStack(hsSignalTrend,"EsameP");
 
 int numDATA = -1;
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
   if (reduced_name_samples_signal_background.at(iName) == -1) { //---- data
     hTrend[iName] -> Draw("EsameP");
     numDATA = iName;
   }
 }
 gPad->SetLogy();
 gPad->SetGrid();
 

 
 cTrendPull->cd();
 gPad->SetBottomMargin(0.17);
 
 TGraphErrors* grPullTrendSumMC   = grPullPlot_grPool  (hTrend[numDATA], hTrendSumMC);
 TGraphErrors* grPullTrendSumMCMC = grPullPlot_grPoolMC(hTrend[numDATA], hTrendSumMC);

 if (grPullTrendSumMCMC) grPullTrendSumMCMC -> Draw("AE3");
 if (grPullTrendSumMC)   grPullTrendSumMC   -> Draw("PsameE");  

 
 for (int ivalues = 0; ivalues < values.size(); ivalues++) {
  std::cout << " DATA::MC::MC+Higgs " << hTrend[numDATA]->GetBinContent(ivalues+1) << " :: " << hTrendSumMC->GetBinContent(ivalues+1) << " :: " << hTrendSumMC->GetBinContent(ivalues+1)+hTrendSignalSumMC->GetBinContent(ivalues+1) << std::endl;
 }
 
 
 
 
 
 
 //==== previous trend ====
 TCanvas* cTrendModified = new TCanvas("cTrendModified","cTrendModified",400,400);
 TCanvas* cTrendPullModified = new TCanvas("cTrendPullModified","cTrendPullModified",400,400);
 
 TH1F* hTrendSumMCModified       = ((TH1F*)(hsTrendModified->GetStack()->Last()));
 
 cTrendModified->cd();
 gPad->SetBottomMargin(0.17);
 
 DrawStack(hsTrendModified,"");
 DrawStack(hsSignalTrend,"EsameP");
 
 int numDATA = -1;
 for (unsigned int iName=0; iName<reduced_name_samples.size(); iName++){
  if (reduced_name_samples_signal_background.at(iName) == -1) { //---- data
     hTrend[iName] -> Draw("EsameP");
     numDATA = iName;
  }
 }
 gPad->SetLogy();
 gPad->SetGrid();
 
 
 cTrendPullModified->cd();
 gPad->SetBottomMargin(0.17);
 
 TGraphErrors* grPullTrendSumMCModified   = grPullPlot_grPool  (hTrend[numDATA], hTrendSumMCModified);
 TGraphErrors* grPullTrendSumMCMCModified = grPullPlot_grPoolMC(hTrend[numDATA], hTrendSumMCModified);
 
 if (grPullTrendSumMCMCModified) grPullTrendSumMCMCModified -> Draw("AE3");
 if (grPullTrendSumMCModified)   grPullTrendSumMCModified   -> Draw("PsameE");  
 
 
 
 
//  
//  TCanvas* canvas = (TCanvas*) file->Get(CanvasName);
//  THStack* stack  = (THStack*) file->Get(StackName);
//  
// 
//  TFile* fileOut = new TFile(nameFileOut, "RECREATE");
//  fileOut.cd();
//  canvas->Write();
//  stack->Write();
 
//  gApplication->Terminate(0);
}





