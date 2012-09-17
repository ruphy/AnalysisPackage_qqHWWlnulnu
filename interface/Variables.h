#include "treeReader.h"
#include "ConfigParser.h"
#include "ntpleUtils.h"
#include "hFactory.h"
#include "h2Factory.h"
#include "stdHisto.h"

#include "TH1F.h"
#include "TProfile.h"
#include "TObject.h"
#include "TTree.h"

struct Variables
{
 //---- tree definition
 TFile* m_outputRootFile;
 TTree* m_reducedTree;
 TTree* m_efficiencyTree;
 
 
 //---- input parameters
 double XSection;
 int dataFlag; 
 int runId; 
 int lumiId; 
 int eventId; 
 int numEntriesBefore;
 double preselection_efficiency;
 
 //---- lepton variables
 
 
 double l1_pX;
 double l1_pY;
 double l1_pZ;
 double l1_pT;
 double l1_E;
 double l1_Eta;
 double l1_Phi;
 
 double l1_charge;
 int          l1_flavour;
 double l1_dxy;
 double l1_dz;
 double l1_3DipSig;
 double l1_tkIso;
 double l1_emIso;
 double l1_hadIso;
 int          l1_isEB;
 double l1_sigmaIetaIeta;
 double l1_DphiIn;
 double l1_DetaIn;
 double l1_HOverE;
 double l1_fbrem;
 double l1_EOverP;
 int          l1_tracker;
 int          l1_standalone;
 int          l1_global;
 double l1_normalizedChi2;
 int          l1_numberOfValidTrackerHits;
 int          l1_numberOfValidMuonHits;
 
 
 
 double l2_pX;
 double l2_pY;
 double l2_pZ;
 double l2_pT;
 double l2_E;
 double l2_Eta;
 double l2_Phi;
 
 double l2_charge;
 int          l2_flavour;
 double l2_dxy;
 double l2_dz;
 double l2_3DipSig;
 double l2_tkIso;
 double l2_emIso;
 double l2_hadIso;
 int          l2_isEB;
 double l2_sigmaIetaIeta;
 double l2_DphiIn;
 double l2_DetaIn;
 double l2_HOverE;
 double l2_fbrem;
 double l2_EOverP;
 int          l2_tracker;
 int          l2_standalone;
 int          l2_global;
 double l2_normalizedChi2;
 int          l2_numberOfValidTrackerHits;
 int          l2_numberOfValidMuonHits;
 
 
 
 double M_ll;
 double DEta_ll;
 double DPhi_ll;
 
 double l1_Z;
 double l2_Z;
 double Z_ll;
 
 int Nleptons_pT5;
 int Nleptons_pT10;
 int Nleptons_pT15;
 int Nleptons_pT20;
 int Nleptons_pT25;
 int Nleptons_pT30;
 
 
 //---- met variables
 double met_X;
 double met_Y;
 double met;
 double pmet; 
 
 //---- jet variables
 
 double q1_pX;
 double q1_pY;
 double q1_pZ;
 double q1_pT;
 double q1_E;
 double q1_Eta;
 double q1_Phi;
 double q1_bTag_trackCountingHighPurBJetTags;
 double q1_bTag_trackCountingHighEffBJetTags;
 
 double q2_pX;
 double q2_pY;
 double q2_pZ;
 double q2_pT;
 double q2_E;
 double q2_Eta;
 double q2_Phi;
 double q2_bTag_trackCountingHighPurBJetTags;
 double q2_bTag_trackCountingHighEffBJetTags;
 
 double M_qq;
 double DEta_qq;
 double DPhi_qq;
 
 int NBjets_trackCountingHighPurBJetTags;
 int NBjets_trackCountingHighEffBJetTags;
 
 int NBjets_trackCountingHighPurBJetTags_m20;
 int NBjets_trackCountingHighPurBJetTags_m15;
 int NBjets_trackCountingHighPurBJetTags_m10;
 int NBjets_trackCountingHighPurBJetTags_m05;
 int NBjets_trackCountingHighPurBJetTags_m04;
 int NBjets_trackCountingHighPurBJetTags_m03;
 int NBjets_trackCountingHighPurBJetTags_m02;
 int NBjets_trackCountingHighPurBJetTags_m01;
 int NBjets_trackCountingHighPurBJetTags_00;
 int NBjets_trackCountingHighPurBJetTags_01;
 int NBjets_trackCountingHighPurBJetTags_02;
 int NBjets_trackCountingHighPurBJetTags_03;
 int NBjets_trackCountingHighPurBJetTags_04;
 int NBjets_trackCountingHighPurBJetTags_05;
 int NBjets_trackCountingHighPurBJetTags_10;
 int NBjets_trackCountingHighPurBJetTags_15;
 int NBjets_trackCountingHighPurBJetTags_20;
 int NBjets_trackCountingHighPurBJetTags_30;
 
 int NBjets_trackCountingHighEffBJetTags_m20;
 int NBjets_trackCountingHighEffBJetTags_m15;
 int NBjets_trackCountingHighEffBJetTags_m10;
 int NBjets_trackCountingHighEffBJetTags_m05;
 int NBjets_trackCountingHighEffBJetTags_m04;
 int NBjets_trackCountingHighEffBJetTags_m03;
 int NBjets_trackCountingHighEffBJetTags_m02;
 int NBjets_trackCountingHighEffBJetTags_m01;
 int NBjets_trackCountingHighEffBJetTags_00;
 int NBjets_trackCountingHighEffBJetTags_01;
 int NBjets_trackCountingHighEffBJetTags_02;
 int NBjets_trackCountingHighEffBJetTags_03;
 int NBjets_trackCountingHighEffBJetTags_04;
 int NBjets_trackCountingHighEffBJetTags_05;
 int NBjets_trackCountingHighEffBJetTags_10;
 int NBjets_trackCountingHighEffBJetTags_15;
 int NBjets_trackCountingHighEffBJetTags_20;
 int NBjets_trackCountingHighEffBJetTags_30;
 
 
 
 int JV_20;
 int JV_30;
 int JV_40;
 int CJV_20;
 int CJV_30;
 int CJV_40;
 
 int q_Z_01_20;
 int q_Z_03_20;
 int q_Z_05_20;
 int q_Z_07_20;
 int q_Z_09_20;
 int q_Z_10_20;
 int q_Z_12_20;
 int q_Z_14_20;
 
 int q_Z_01_30;
 int q_Z_03_30;
 int q_Z_05_30;
 int q_Z_07_30;
 int q_Z_09_30;
 int q_Z_10_30;
 int q_Z_12_30;
 int q_Z_14_30;
 
 int q_Z_01_40;
 int q_Z_03_40;
 int q_Z_05_40;
 int q_Z_07_40;
 int q_Z_09_40;
 int q_Z_10_40;
 int q_Z_12_40;
 int q_Z_14_40;
 
 
 //---- PV info ----
 int nPV;
 
 //---- MC info ----
 int numPUMC;
 
 //---- Trigger info ----
 std::vector<std::string> HLTVector_names_;
 std::vector<int> HLTVector_;
 
};



void InitializeTree(Variables&, const std::string&);
void InitializeTreeTrigger(Variables&, const std::vector<std::string> &);

void FillTree(Variables& vars);
void FillEfficiencyTree(Variables& vars);

void SetEventVariables(Variables& vars, treeReader& reader);

void SetLeptonsVariables(Variables& vars, treeReader& reader,const int& iLep1, const int& iLep2, const int& FlavourLep1, const int& FlavourLep2);

//void SetMetVariables(Variables& vars, treeReader& reader, const std::string& metType);
void SetMetVariables(Variables& vars, treeReader& reader, const std::string& metType, const int& iLep1, const int& iLep2, const int& FlavourLep1, const int& FlavourLep2);

void SetQJetVariables(Variables& vars, treeReader& reader, const int& q1, const int& q2, const std::vector<int>& blacklistJet_forCJV, const std::vector<int>& blacklistJet_forBtag);

void SetPVVariables(Variables& vars, treeReader& reader);

void SetMCVariables(Variables& vars, treeReader& reader);

void SetTriggerVariables(Variables&, treeReader& reader);


void SaveTree(Variables& vars);
