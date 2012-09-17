#include <iostream>
//#include "ntupleReader.h"
#include "TFile.h"
#include "TTree.h"

int main ()
{
  TFile f ("output_Spring11_90_NoPU_Run2011/out_NtupleProducer_DATA.root") ;
  TTree * fChain = (TTree*) f.Get ("outTreeJetLep") ;

  Int_t           runId;
  Int_t           lumiId;
  Int_t           eventId;
  Double_t        l1_pX;

  TBranch        *b_runId;   //!
  TBranch        *b_lumiId;   //!
  TBranch        *b_eventId;   //!
  TBranch        *b_l1_pX;   //!

  fChain->SetBranchAddress ("runId", &runId, &b_runId);
  fChain->SetBranchAddress ("lumiId", &lumiId, &b_lumiId);
  fChain->SetBranchAddress ("eventId", &eventId, &b_eventId);
  fChain->SetBranchAddress ("l1_pX", &l1_pX, &b_l1_pX);

  for (int iEntry = 0 ; iEntry < fChain->GetEntries () ; ++iEntry)
    {
      fChain->GetEntry (iEntry) ;
      std::cout << runId   << "\t" ;
      std::cout << lumiId  << "\t" ;
      std::cout << eventId << "\t" ;
      std::cout << l1_pX << "\n" ;

    }

  return 0 ; 
}