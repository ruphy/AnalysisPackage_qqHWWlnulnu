#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "TPie.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMinuit.h"
#include "qqHWWlnulnuUtils.h"
#include "Variables.h"

#include "../test/LatinoStyle.C"
#include "../test/LatinoStyle2.C"

#include "../test/TDRStyle.cc"
#include "../test/Read.cc"
// #include "../test/DrawTools.h"

#include "PUclass.h"


#include "TProof.h"


#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#endif

///    
///
///       ___|         |         _ \          |   _)            _)              |   _)               
///      |      |   |  __|      |   |  __ \   __|  |  __ `__ \   | _  /   _` |  __|  |   _ \   __ \  
///      |      |   |  |        |   |  |   |  |    |  |   |   |  |   /   (   |  |    |  (   |  |   | 
///     \____| \__,_| \__|     \___/   .__/  \__| _| _|  _|  _| _| ___| \__,_| \__| _| \___/  _|  _| 
///                                   _|                                                             
///    



///---- int (-inf, x) ----
void IntegralSx(TH1F* histo,TH1F* histo_IntSx) { 
 histo->ComputeIntegral();
 Double_t *integral = histo->GetIntegral();
 Double_t totIntegral = integral [histo->GetNbinsX()+1];
 for (int iBin = 0; iBin < histo->GetNbinsX()+1; iBin++) {
  integral[iBin] = totIntegral * integral[iBin];
 }
 histo_IntSx->SetContent(integral);
 histo_IntSx->SetLineColor(histo->GetLineColor());
 histo_IntSx->SetLineWidth(histo->GetLineWidth());
 histo_IntSx->GetXaxis()->SetTitle(histo->GetXaxis()->GetTitle()); 
 histo_IntSx->GetYaxis()->SetTitle("Cumulative SX"); 
}

///---- int (x, +inf) ----
void IntegralDx(TH1F* histo,TH1F* histo_IntDx) { 
 histo->ComputeIntegral();
 Double_t *integral = histo->GetIntegral();
 Double_t totIntegral = integral [histo->GetNbinsX()+1];
 Double_t *integralDX = new Double_t [histo->GetNbinsX()+2];
 for (int iBin = 0; iBin < histo->GetNbinsX()+2; iBin++) {
  integralDX[iBin] = totIntegral - integral[iBin]*totIntegral;
 }
 histo_IntDx->SetContent(integralDX);
 histo_IntDx->SetLineColor(histo->GetLineColor());
 histo_IntDx->SetLineWidth(histo->GetLineWidth());
 histo_IntDx->GetXaxis()->SetTitle(histo->GetXaxis()->GetTitle()); 
 histo_IntDx->GetYaxis()->SetTitle("Cumulative DX"); 
}

///---- A/B and A/sqrt(B) ----
void Ratio(TH1F* histo_Int_Sig, TH1F* histo_Int_Bkg, TH1F* histo_Int_Sig_over_Bkg, TH1F* histo_Int_Sig_over_sqrtBkg) {
 int nbin = histo_Int_Sig->GetNbinsX()+2;
 for (int iBin = 0; iBin < nbin; iBin++) {
  double Sig = histo_Int_Sig -> GetBinContent(iBin);
  double Bkg = histo_Int_Bkg -> GetBinContent(iBin);
  double Sig_over_Bkg = Bkg!=0 ? Sig / Bkg : 0;
  double Sig_over_sqrtBkg = Bkg!=0 ? Sig / sqrt(Bkg) : 0;
  
  histo_Int_Sig_over_Bkg     -> SetBinContent(iBin, Sig_over_Bkg);
  histo_Int_Sig_over_sqrtBkg -> SetBinContent(iBin, Sig_over_sqrtBkg);
 }
 
 histo_Int_Sig_over_Bkg->SetLineColor(kGreen);
 histo_Int_Sig_over_Bkg->SetLineWidth(histo_Int_Sig->GetLineWidth());
 histo_Int_Sig_over_Bkg->GetXaxis()->SetTitle(histo_Int_Sig->GetXaxis()->GetTitle()); 
 histo_Int_Sig_over_Bkg->GetYaxis()->SetTitle("S/B"); 
 
 histo_Int_Sig_over_sqrtBkg->SetLineColor(kMagenta);
 histo_Int_Sig_over_sqrtBkg->SetLineWidth(histo_Int_Sig->GetLineWidth());
 histo_Int_Sig_over_sqrtBkg->GetXaxis()->SetTitle(histo_Int_Sig->GetXaxis()->GetTitle()); 
 histo_Int_Sig_over_sqrtBkg->GetYaxis()->SetTitle("S/#sqrt{B}"); 
 
}



///---- main program ----

int main(int argc, char** argv)
{ 
 TFormula::SetMaxima(10000);   //---- for too long "draw" instructions ----
  
//  TProof::Open("");
 
 LatinoStyle2();
 
 gStyle->SetPadTopMargin(0.11);
 gStyle->SetPadLeftMargin(0.17);
 gStyle->SetPadRightMargin(0.23);
 gStyle->cd(); 
 
 
 std::cout << " " << std::endl;
 std::cout << " " << std::endl;
 ///    
 ///
 std::cout << "        ___|         |         _ \\          |   _)            _)              |   _)                        " << std::endl;
 std::cout << "       |      |   |  __|      |   |  __ \\   __|  |  __ `__ \\   | _  /   _` |  __|  |   _ \\   __ \\        " << std::endl;
 std::cout << "       |      |   |  |        |   |  |   |  |    |  |   |   |  |   /   (   |  |    |  (   |  |   |           " << std::endl;
 std::cout << "      \\____| \\__,_| \\__|     \\___/   .__/  \\__| _| _|  _|  _| _| ___| \\__,_| \\__| _| \\___/  _|  _|   " << std::endl;
 std::cout << "                                    _|                                                                       " << std::endl;
 std::cout << "      " << std::endl;
 
 char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
 char black[] = { 0x1b, '[', '0', ';', '3', '0', 'm', 0 };
 char red[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
 char green[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
 char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
 char blue[] = { 0x1b, '[', '0', ';', '3', '4', 'm', 0 };
 char purple[] = { 0x1b, '[', '0', ';', '3', '5', 'm', 0 };
 char cyan[] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
 char Lgray[] = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
 char Dgray[] = { 0x1b, '[', '0', ';', '3', '8', 'm', 0 };
 char Bred[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
 //for bold colors, just change the 0 after the [ to a 1
 
 
 ///==== Latinos colours ====
 
 //Check if all nedeed arguments to parse are there                                                                                                                               
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }


 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::vector<std::string> vecSignalName     = gConfigParser -> readStringListOption("Input::SignalNames");
 std::vector<std::string> vecBackgroundName = gConfigParser -> readStringListOption("Input::BackgroundNames");
 
 std::cout << " >>>>> vecSignalName.size()     = " << vecSignalName.size()     << std::endl;
 std::cout << " >>>>> vecBackgroundName.size() = " << vecBackgroundName.size() << std::endl;
 
 
 std::string inputHistoFile  = gConfigParser -> readStringOption("Input::HistoFile"); 
 
 TFile* inFile = new TFile (inputHistoFile.c_str(),"READ");
 
 
 ///==== output file ====
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
 
 TString toRemove = Form("rm %s",OutFileName.c_str());
 gSystem->Exec(toRemove);  
 
 TFile* outFile = new TFile(OutFileName.c_str(),"RECREATE");
 outFile->cd();
 std::cout << ">>>>> Output::outFileName >> created " << std::endl;  
 
 //  [iName][iCut][iVar]
 TH1F* histo[56][191][21];
 TH1F* histo_IntSx[56][191][21];
 TH1F* histo_IntDx[56][191][21];
 
 //  [iCut][iVar]
 TH1F* histo_Sig[191][21];
 TH1F* histo_Bkg[191][21];

 THStack* hstack_Sig[191][21];
 THStack* hstack_Bkg[191][21];
 
 TH1F* histo_IntSx_Sig[191][21];
 TH1F* histo_IntSx_Bkg[191][21];
 TH1F* histo_IntDx_Sig[191][21];
 TH1F* histo_IntDx_Bkg[191][21];

 THStack* hstack_IntSx_Sig[191][21];
 THStack* hstack_IntSx_Bkg[191][21];
 THStack* hstack_IntDx_Sig[191][21];
 THStack* hstack_IntDx_Bkg[191][21];
 
 
 TH1F* histo_IntSx_Sig_over_Bkg[191][21];
 TH1F* histo_IntDx_Sig_over_Bkg[191][21];
 
 TH1F* histo_IntSx_Sig_over_sqrtBkg[191][21];
 TH1F* histo_IntDx_Sig_over_sqrtBkg[191][21];
 
 
 ///==== debug flag ==== 
 bool  debug = false; 
 try {
  debug = gConfigParser -> readBoolOption("Input::debug");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> input::debug  " << debug  << std::endl;  

 ///==== program ====
 
 double start, end;
 start = clock();
 
 TLegend* leg      = new TLegend(0.8,0.64,0.98,0.103);
 TLegend* legStack = new TLegend(0.8,0.64,0.98,0.103);
 bool LegendBuilt = false;


 
 int MAXCUT = 191;
 int MAXVAR = 21;

 int REALMAXCUT = 0;
 int REALMAXVAR = 0;
 
 std::cout << " cycling ... " << std::endl;
 ///==== cycle on selections ====
 for (unsigned int iCut = 0; iCut<MAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<MAXVAR; iVar++){
   unsigned int iSample = 0;
   for (iSample = 0; iSample<vecBackgroundName.size(); iSample++){
    TString nameHisto = Form ("Data/%s_%d_%d_Tot_temp",vecBackgroundName.at(iSample).c_str(),iCut,iVar);
    if (debug) std::cout << " Bkg::nameHisto[" << iSample << "][" << iCut << "][" << iVar << "] = " << nameHisto.Data() << std::endl;
    histo[iSample][iCut][iVar] = (TH1F*) inFile->Get(nameHisto);
    
    if (histo[iSample][iCut][iVar] != 0) {
     if (REALMAXCUT < iCut+1) {
      REALMAXCUT = iCut+1;
     }
     if (REALMAXVAR < iVar+1) {
      REALMAXVAR = iVar+1;
     }
    }
    else {
//      continue;
    }
   }
   
   iSample = vecBackgroundName.size();
   for (; iSample<(vecBackgroundName.size()+vecSignalName.size()); iSample++){
    TString nameHisto = Form ("Data/%s_%d_%d_Tot_temp",vecSignalName.at(iSample-vecBackgroundName.size()).c_str(),iCut,iVar);
    if (debug) std::cout << " Sig::nameHisto[" << iSample << "][" << iCut << "][" << iVar << "] = " << nameHisto.Data() << std::endl;
    histo[iSample][iCut][iVar] = (TH1F*) inFile->Get(nameHisto);
    
    if (histo[iSample][iCut][iVar] != 0) {
     //
    }
    else {
     //      continue;
    }
   }
   
  } //---- iCut
 } //----iVar
 
 std::cout << " cycling: Sig and Bkg ... " << std::endl;
 ///---- create Signal and Background distributions ----
 for (unsigned int iCut = 0; iCut<REALMAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<REALMAXVAR; iVar++){
   
   int nbin = histo[0][iCut][iVar] -> GetNbinsX();
   double max = histo[0][iCut][iVar] ->GetXaxis() -> GetBinUpEdge (nbin);
   double min = histo[0][iCut][iVar] ->GetXaxis() -> GetBinLowEdge(1);   
   TString nameHisto;
   
   nameHisto = Form ("Sig_%d_%d",iCut,iVar);
   histo_Sig[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_Sig[iCut][iVar] -> Sumw2();
   histo_Sig[iCut][iVar] -> GetXaxis() -> SetTitle(histo[0][iCut][iVar]->GetXaxis()->GetTitle());
   histo_Sig[iCut][iVar] -> SetLineColor(kBlue);
   histo_Sig[iCut][iVar] -> SetLineWidth(2);
   
   nameHisto = Form ("Bkg_%d_%d",iCut,iVar);
   histo_Bkg[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_Bkg[iCut][iVar] -> Sumw2();
   histo_Bkg[iCut][iVar] -> GetXaxis() -> SetTitle(histo[0][iCut][iVar]->GetXaxis()->GetTitle());
   histo_Bkg[iCut][iVar] -> SetLineColor(kRed);
   histo_Bkg[iCut][iVar] -> SetLineWidth(2);
      
   
   nameHisto = Form ("hs_Sig_%d_%d",iCut,iVar);
   hstack_Sig[iCut][iVar] = new THStack(nameHisto, nameHisto);
   
   nameHisto = Form ("hs_Bkg_%d_%d",iCut,iVar);
   hstack_Bkg[iCut][iVar] = new THStack(nameHisto, nameHisto);
   
   
   unsigned int iSample = 0;
   for (iSample = 0; iSample<vecBackgroundName.size(); iSample++){
    histo[iSample][iCut][iVar] -> SetFillStyle(3001);
    histo[iSample][iCut][iVar] -> SetFillColor(histo[iSample][iCut][iVar] -> GetLineColor());
    
    histo_Bkg[iCut][iVar] -> Add (histo[iSample][iCut][iVar]);   
    hstack_Bkg[iCut][iVar]-> Add (histo[iSample][iCut][iVar]);   
   }
   
   iSample = vecBackgroundName.size();
   for (; iSample<(vecBackgroundName.size()+vecSignalName.size()); iSample++){
    histo[iSample][iCut][iVar] -> SetFillStyle(0);
    histo[iSample][iCut][iVar] -> SetFillColor(histo[iSample][iCut][iVar] -> GetLineColor());
    
    histo_Sig[iCut][iVar] -> Add (histo[iSample][iCut][iVar]);
    hstack_Sig[iCut][iVar]-> Add (histo[iSample][iCut][iVar]);   
   }
   
   if (!LegendBuilt){
    leg->AddEntry(histo_Sig[iCut][iVar],"signal","pf");    
    leg->AddEntry(histo_Bkg[iCut][iVar],"background","pf");    
    leg->SetFillColor(0);
    
    for (iSample = 0; iSample<vecBackgroundName.size(); iSample++){
     legStack->AddEntry(histo[iSample][iCut][iVar],vecBackgroundName.at(iSample).c_str(),"pf");    
    }
    iSample = vecBackgroundName.size();
    for (; iSample<(vecBackgroundName.size()+vecSignalName.size()); iSample++){
     legStack->AddEntry(histo[iSample][iCut][iVar],vecSignalName.at(iSample - vecBackgroundName.size()).c_str(),"pf");    
    }
    legStack->SetFillColor(0);    
    LegendBuilt = true;
   }
   
     
   
  }
 }
 
 
 
 std::cout << " cycling: Sig and Bkg : Integral ... " << std::endl;
 ///---- create Signal and Background integrated Sx and Dx distributions ----
 for (unsigned int iCut = 0; iCut<REALMAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<REALMAXVAR; iVar++){
   
   int nbin = histo[0][iCut][iVar] -> GetNbinsX();
   double max = histo[0][iCut][iVar] ->GetXaxis() -> GetBinUpEdge (nbin);
   double min = histo[0][iCut][iVar] ->GetXaxis() -> GetBinLowEdge(1);   
   TString nameHisto;
   
   nameHisto = Form ("IntDx_Sig_%d_%d",iCut,iVar);
   histo_IntDx_Sig[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntDx_Sig[iCut][iVar] -> Sumw2();
   
   nameHisto = Form ("IntSx_Sig_%d_%d",iCut,iVar);
   histo_IntSx_Sig[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntSx_Sig[iCut][iVar] -> Sumw2();
   
   nameHisto = Form ("IntDx_Bkg_%d_%d",iCut,iVar);
   histo_IntDx_Bkg[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntDx_Bkg[iCut][iVar] -> Sumw2();
   
   nameHisto = Form ("IntSx_Bkg_%d_%d",iCut,iVar);
   histo_IntSx_Bkg[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntSx_Bkg[iCut][iVar] -> Sumw2();
   
   ///---- do integral ----
   IntegralSx(histo_Sig[iCut][iVar],histo_IntSx_Sig[iCut][iVar]);
   IntegralDx(histo_Sig[iCut][iVar],histo_IntDx_Sig[iCut][iVar]);
   
   IntegralSx(histo_Bkg[iCut][iVar],histo_IntSx_Bkg[iCut][iVar]);
   IntegralDx(histo_Bkg[iCut][iVar],histo_IntDx_Bkg[iCut][iVar]);
   
   
   
   
   ///---- same but for single contribution ----
   
   nameHisto = Form ("hs_IntDx_Bkg_%d_%d",iCut,iVar);
   hstack_IntDx_Bkg[iCut][iVar] = new THStack(nameHisto, nameHisto);
   nameHisto = Form ("hs_IntDx_Sig_%d_%d",iCut,iVar);
   hstack_IntDx_Sig[iCut][iVar] = new THStack(nameHisto, nameHisto);
   nameHisto = Form ("hs_IntSx_Bkg_%d_%d",iCut,iVar);
   hstack_IntSx_Bkg[iCut][iVar] = new THStack(nameHisto, nameHisto);
   nameHisto = Form ("hs_IntSx_Sig_%d_%d",iCut,iVar);
   hstack_IntSx_Sig[iCut][iVar] = new THStack(nameHisto, nameHisto);
   
   unsigned int iSample = 0;
   for (iSample = 0; iSample<vecBackgroundName.size(); iSample++){
    nameHisto = Form ("IntDx_Bkg_%d_%d_%d",iSample,iCut,iVar);
    histo_IntDx[iSample][iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
    histo_IntDx[iSample][iCut][iVar] -> Sumw2();
    histo_IntDx[iSample][iCut][iVar] -> SetFillStyle(3001);
    histo_IntDx[iSample][iCut][iVar] -> SetFillColor(histo[iSample][iCut][iVar] -> GetLineColor());
    
    nameHisto = Form ("IntSx_Bkg_%d_%d_%d",iSample,iCut,iVar);
    histo_IntSx[iSample][iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
    histo_IntSx[iSample][iCut][iVar] -> Sumw2();
    histo_IntSx[iSample][iCut][iVar] -> SetFillStyle(3001);
    histo_IntSx[iSample][iCut][iVar] -> SetFillColor(histo[iSample][iCut][iVar] -> GetLineColor());
    
    IntegralSx(histo[iSample][iCut][iVar],histo_IntSx[iSample][iCut][iVar]);
    IntegralDx(histo[iSample][iCut][iVar],histo_IntDx[iSample][iCut][iVar]);
    
    hstack_IntSx_Bkg[iCut][iVar] -> Add (histo_IntSx[iSample][iCut][iVar]);
    hstack_IntDx_Bkg[iCut][iVar] -> Add (histo_IntDx[iSample][iCut][iVar]);
   }
   
   iSample = vecBackgroundName.size();
   for (; iSample<(vecBackgroundName.size()+vecSignalName.size()); iSample++){
    nameHisto = Form ("IntDx_Sig_%d_%d_%d",iSample,iCut,iVar);
    histo_IntDx[iSample][iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
    histo_IntDx[iSample][iCut][iVar] -> Sumw2();
    histo_IntDx[iSample][iCut][iVar] -> SetFillStyle(3001);
    histo_IntDx[iSample][iCut][iVar] -> SetFillColor(histo[iSample][iCut][iVar] -> GetLineColor());
    
    nameHisto = Form ("IntSx_Sig_%d_%d_%d",iSample,iCut,iVar);
    histo_IntSx[iSample][iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
    histo_IntSx[iSample][iCut][iVar] -> Sumw2();
    histo_IntSx[iSample][iCut][iVar] -> SetFillStyle(3001);
    histo_IntSx[iSample][iCut][iVar] -> SetFillColor(histo[iSample][iCut][iVar] -> GetLineColor());
    
    IntegralSx(histo[iSample][iCut][iVar],histo_IntSx[iSample][iCut][iVar]);
    IntegralDx(histo[iSample][iCut][iVar],histo_IntDx[iSample][iCut][iVar]);

    hstack_IntSx_Sig[iCut][iVar] -> Add (histo_IntSx[iSample][iCut][iVar]);
    hstack_IntDx_Sig[iCut][iVar] -> Add (histo_IntDx[iSample][iCut][iVar]);
   }
  
   
  }
 }
 
 
 std::cout << " cycling: Sig and Bkg : Integral : S/B ... " << std::endl;
 ///---- create S over B and S over sqrtB integrated Sx and Dx distributions ----
 for (unsigned int iCut = 0; iCut<REALMAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<REALMAXVAR; iVar++){
   
   int nbin = histo[0][iCut][iVar] -> GetNbinsX();
   double max = histo[0][iCut][iVar] ->GetXaxis() -> GetBinUpEdge (nbin);
   double min = histo[0][iCut][iVar] ->GetXaxis() -> GetBinLowEdge(1);   
   TString nameHisto;
   
   nameHisto = Form ("IntSx_Sig_over_Bkg_%d_%d",iCut,iVar);
   histo_IntSx_Sig_over_Bkg[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntSx_Sig_over_Bkg[iCut][iVar] -> Sumw2();
   
   nameHisto = Form ("IntDx_Sig_over_Bkg_%d_%d",iCut,iVar);
   histo_IntDx_Sig_over_Bkg[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntDx_Sig_over_Bkg[iCut][iVar] -> Sumw2();
   
   nameHisto = Form ("IntSx_Sig_over_sqrtBkg_%d_%d",iCut,iVar);
   histo_IntSx_Sig_over_sqrtBkg[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntSx_Sig_over_sqrtBkg[iCut][iVar] -> Sumw2();
   
   nameHisto = Form ("IntDx_Sig_over_sqrtBkg_%d_%d",iCut,iVar);
   histo_IntDx_Sig_over_sqrtBkg[iCut][iVar] = new TH1F(nameHisto, nameHisto, nbin, min, max);
   histo_IntDx_Sig_over_sqrtBkg[iCut][iVar] -> Sumw2();
   
   ///---- do ratio plot ----
   Ratio(histo_IntSx_Sig[iCut][iVar],histo_IntSx_Bkg[iCut][iVar],histo_IntSx_Sig_over_Bkg[iCut][iVar],histo_IntSx_Sig_over_sqrtBkg[iCut][iVar]);
   Ratio(histo_IntDx_Sig[iCut][iVar],histo_IntDx_Bkg[iCut][iVar],histo_IntDx_Sig_over_Bkg[iCut][iVar],histo_IntDx_Sig_over_sqrtBkg[iCut][iVar]);
   
  }
 }
 
 
 std::cerr << " ******************************************* end *******************************************" << std::endl;
 end = clock();
 std::cout <<"Time = " <<  ((double) (end - start)) << " (a.u.)" << std::endl;  
 
 
 
 std::cout << std::endl;
 std::cout << " Plot ... (wait) " << std::endl;
 
 TCanvas* canvas[191][21];
 TCanvas* canvas_stack[191][21];

 TCanvas* canvas_stack_2plot[191][21];
 
 
 for (unsigned int iCut = 0; iCut<REALMAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<REALMAXVAR; iVar++){
   TString nameCanvas;
   
   nameCanvas = Form ("SigBkg_%d_%d",iCut,iVar);
   canvas[iCut][iVar] = new TCanvas (nameCanvas,nameCanvas,800,900);
   canvas[iCut][iVar] -> Divide(2,4);
   
   canvas[iCut][iVar] -> cd (1);
   histo_Bkg[iCut][iVar] -> Draw();
   histo_Sig[iCut][iVar] -> Draw("same");
   leg->Draw();
   
   canvas[iCut][iVar] -> cd (2);
   histo_Bkg[iCut][iVar] -> Draw();
   histo_Sig[iCut][iVar] -> Draw("same");
   leg->Draw();
   
   canvas[iCut][iVar] -> cd (3);
   histo_IntSx_Bkg[iCut][iVar] -> Draw();
   histo_IntSx_Sig[iCut][iVar] -> Draw("same");
   
   canvas[iCut][iVar] -> cd (4);
   histo_IntDx_Bkg[iCut][iVar] -> Draw();
   histo_IntDx_Sig[iCut][iVar] -> Draw("same");
   
   canvas[iCut][iVar] -> cd (5);
   histo_IntSx_Sig_over_Bkg[iCut][iVar] -> Draw();
   
   canvas[iCut][iVar] -> cd (6);
   histo_IntDx_Sig_over_Bkg[iCut][iVar] -> Draw();
   
   canvas[iCut][iVar] -> cd (7);
   histo_IntSx_Sig_over_sqrtBkg[iCut][iVar] -> Draw();
   
   canvas[iCut][iVar] -> cd (8);
   histo_IntDx_Sig_over_sqrtBkg[iCut][iVar] -> Draw();
   
   
   
   
   
   
   
   
   
   
   
   
   nameCanvas = Form ("hs_SigBkg_%d_%d",iCut,iVar);
   canvas_stack[iCut][iVar] = new TCanvas (nameCanvas,nameCanvas,800,900);
   canvas_stack[iCut][iVar] -> Divide(2,4);
   
   canvas_stack[iCut][iVar] -> cd (1);
   hstack_Bkg[iCut][iVar] -> Draw();
   hstack_Sig[iCut][iVar] -> Draw("same");
   legStack->Draw();
   
   canvas_stack[iCut][iVar] -> cd (2);
   hstack_Bkg[iCut][iVar] -> Draw();
   hstack_Sig[iCut][iVar] -> Draw("same");
   legStack->Draw();
   
   canvas_stack[iCut][iVar] -> cd (3);
   hstack_IntSx_Bkg[iCut][iVar] -> Draw();
   hstack_IntSx_Sig[iCut][iVar] -> Draw("same");
   
   canvas_stack[iCut][iVar] -> cd (4);
   hstack_IntDx_Bkg[iCut][iVar] -> Draw();
   hstack_IntDx_Sig[iCut][iVar] -> Draw("same");
   
   canvas_stack[iCut][iVar] -> cd (5);
   histo_IntSx_Sig_over_Bkg[iCut][iVar] -> Draw();
   
   canvas_stack[iCut][iVar] -> cd (6);
   histo_IntDx_Sig_over_Bkg[iCut][iVar] -> Draw();
   
   canvas_stack[iCut][iVar] -> cd (7);
   histo_IntSx_Sig_over_sqrtBkg[iCut][iVar] -> Draw();
   
   canvas_stack[iCut][iVar] -> cd (8);
   histo_IntDx_Sig_over_sqrtBkg[iCut][iVar] -> Draw();
   
   
   
   
   
   
   
   
   
   
   nameCanvas = Form ("hs_SB_SigBkg_%d_%d",iCut,iVar);
   canvas_stack_2plot[iCut][iVar] = new TCanvas (nameCanvas,nameCanvas,800,900);
   canvas_stack_2plot[iCut][iVar] -> Divide(2,2);
      
   canvas_stack_2plot[iCut][iVar] -> cd (1);
   hstack_IntSx_Bkg[iCut][iVar] -> Draw();
   hstack_IntSx_Sig[iCut][iVar] -> Draw("same");
   legStack->Draw();
   gPad->SetGrid();
   
   canvas_stack_2plot[iCut][iVar] -> cd (2);
   hstack_IntDx_Bkg[iCut][iVar] -> Draw();
   hstack_IntDx_Sig[iCut][iVar] -> Draw("same");
   legStack->Draw();
   gPad->SetGrid();
   
   canvas_stack_2plot[iCut][iVar] -> cd (3);
   histo_IntSx_Sig_over_sqrtBkg[iCut][iVar] -> Draw();
   gPad->SetGrid();
   
   canvas_stack_2plot[iCut][iVar] -> cd (4);
   histo_IntDx_Sig_over_sqrtBkg[iCut][iVar] -> Draw();
   gPad->SetGrid();
   
   
  }
 }
 
 
 
 
 ///==== save output ====
 outFile->cd();
 
 outFile->mkdir("Canvas");
 outFile->cd("Canvas");
 
 for (unsigned int iCut = 0; iCut<REALMAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<REALMAXVAR; iVar++){
   canvas[iCut][iVar] -> Write();
   canvas_stack[iCut][iVar] -> Write();
  }
 }
 
 outFile->cd();
 outFile->mkdir("SelectedCanvas");
 outFile->cd("SelectedCanvas");
 for (unsigned int iCut = 0; iCut<REALMAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<REALMAXVAR; iVar++){
   canvas_stack_2plot[iCut][iVar] -> Write();
  }
 }
 
 outFile->cd();
 outFile->mkdir("Histo");
 outFile->cd("Histo");

 for (unsigned int iCut = 0; iCut<REALMAXCUT; iCut++){
  for (unsigned int iVar = 0; iVar<REALMAXVAR; iVar++){
   
   histo_Sig[iCut][iVar]-> Write();
   histo_Bkg[iCut][iVar]-> Write();
   
   histo_IntSx_Sig[iCut][iVar]-> Write();
   histo_IntSx_Bkg[iCut][iVar]-> Write();
   histo_IntDx_Sig[iCut][iVar]-> Write();
   histo_IntDx_Bkg[iCut][iVar]-> Write();
   
   histo_IntSx_Sig_over_Bkg[iCut][iVar]-> Write();
   histo_IntDx_Sig_over_Bkg[iCut][iVar]-> Write();
   
   histo_IntSx_Sig_over_sqrtBkg[iCut][iVar]-> Write();
   histo_IntDx_Sig_over_sqrtBkg[iCut][iVar]-> Write();
   
  }
 }
 
 leg->Write();
 outFile->Close();
 
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << ">>>>> Written in File :   " << OutFileName  << std::endl;  
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
}





