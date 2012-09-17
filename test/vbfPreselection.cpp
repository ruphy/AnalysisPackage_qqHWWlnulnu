/**
   vbfPreselection
   require minimum number of leptons and jets (with Deta and Mjj requirements)
*/

#include "treeReader.h"
#include "ConfigParser.h"
#include "ntpleUtils.h"

#include <iomanip>
#include <sstream>

#include "TH1F.h"



int main (int argc, char** argv)
{
  //Check if all nedeed arguments to parse are there                                                                                                                               
  if (argc != 2)
  {
    std::cerr << ">>>>> vbfPreselection::usage: " << argv[0] << " configFileName" << std::endl ;
    return 1 ;
  }
  
  
  
  // Parse the config file                                                                                                                                                          
  parseConfigFile (argv[1]) ;
  
  std::string inputFileList = gConfigParser -> readStringOption ("Input::inputFileList") ;
  std::string jetAlgorithm  = gConfigParser -> readStringOption ("Input::jetAlgorithm") ;
  
  std::string outputRootFilePath = gConfigParser -> readStringOption ("Output::outputRootFilePath") ;
  std::string outputRootFileName = gConfigParser -> readStringOption ("Output::outputRootFileName") ;  
  
  int entryMODULO = gConfigParser -> readIntOption ("Options::entryMODULO") ;
  
  int nJetMIN = gConfigParser -> readIntOption ("Cuts::nJetMIN") ;
  float jetEtMIN = gConfigParser -> readFloatOption ("Cuts::jetEtMIN") ;
  
  int nLepMIN = gConfigParser -> readIntOption ("Cuts::nLepMIN") ;
  float lepPtMIN = gConfigParser -> readFloatOption ("Cuts::lepPtMIN") ;
  float lepTkIsoOverPtMAX = gConfigParser -> readFloatOption ("Cuts::lepTkIsoOverPtMAX") ;
 
 
 float VBFDetaMIN = gConfigParser -> readFloatOption ("Cuts::VBFDetaMIN") ;
 float VBFMjjMIN = gConfigParser -> readFloatOption ("Cuts::VBFMjjMIN") ;
 
 
  //PG this is before any preselections, and gets propagated to the new ntuples... cool!!!
  std::map<int,int> totalEvents = GetTotalEvents ("AllEvents/totalEvents", inputFileList.c_str ()) ;  

  std::string VBFPreselectionName = "AllEvents/passedEvents" ; 
  std::map<int,int> VBFPreselectionEvents = GetTotalEvents (VBFPreselectionName.c_str (), inputFileList.c_str ()) ;  
  
  // Open old tree
  std::string treeName = "" + jetAlgorithm + "/SimpleNtuple" ;
  TChain* chain = new TChain (treeName.c_str ()) ;
  if (!FillChain (*chain, inputFileList.c_str ())) return 1 ;
  treeReader reader ( (TTree*) (chain)) ;
  
  // Open output root file for clone tree
  outputRootFileName += "_" + jetAlgorithm + ".root" ;
  TFile outputRootFile ( (outputRootFilePath+"/"+outputRootFileName).c_str (), "RECREATE") ;
  outputRootFile.cd () ;
  
  TTree* cloneTree = chain -> CloneTree (0) ;
  
  // define histograms
  int nStep = 5 ;
  TH1F* events = new TH1F ("events", "events", nStep, 0., 1.*nStep) ;
  std::map<int, int> stepEvents ;
  std::map<int, std::string> stepName ;

  int step = 0 ;
  stepEvents[step] = totalEvents[1] ;
  stepName[step] = "total events" ;

  step = 1 ;
  stepEvents[step] = VBFPreselectionEvents[1] ;
  stepName[step] = "useless" ;

  std::stringstream step_name ; 
  step = 2 ;
  step_name << nLepMIN << " leptons" ;
//      std::cout << step_name.str () << std::endl ;
  stepName[step] = step_name.str () ;

  step = 3 ;
  step_name.str (std::string ()) ;
  step_name << nJetMIN << " jets" ;
//      std::cout << step_name.str () << std::endl ;
  stepName[step] = step_name.str () ;

  // Loop over events
  std::cout << ">>>>> vbfPreselection::Read " << chain -> GetEntries () << " entries" << std::endl ;  
  for (int entry = 0 ; entry < chain -> GetEntries () ; ++entry)
    {
      reader.GetEntry (entry) ;
      if ( (entry%entryMODULO) == 0) std::cout << ">>>>> vbfPreselection::GetEntry " << entry << std::endl ;   
      
      //***************
      // cut on leptons
      step = 2 ;
      
      int nLep = 0 ;
      std::vector<ROOT::Math::XYZTVector> electrons ;
      std::vector<ROOT::Math::XYZTVector> muons ;
      std::vector<ROOT::Math::XYZTVector> leptons ;
  
      for (unsigned int eleIt = 0 ; eleIt < (reader.Get4V ("electrons")->size ()) ; ++eleIt)
        {
          if ( reader.Get4V ("electrons")->at (eleIt).pt () < lepPtMIN ) continue ;
          if ( (reader.GetFloat ("electrons_tkIsoR03")->at (eleIt)) / reader.Get4V ("electrons")->at (eleIt).pt () > lepTkIsoOverPtMAX ) continue ;
          ++nLep ;
          
          electrons.push_back ( reader.Get4V ("electrons")->at (eleIt) ) ;
          leptons.push_back ( reader.Get4V ("electrons")->at (eleIt) ) ;      
        }
      
      for (unsigned int muIt = 0 ; muIt < (reader.Get4V ("muons")->size ()) ; ++muIt)
        {
          if ( reader.Get4V ("muons")->at (muIt).pt () < lepPtMIN ) continue ;
          if ( (reader.GetFloat ("muons_tkIsoR03")->at (muIt)) / reader.Get4V ("muons")->at (muIt).pt () > lepTkIsoOverPtMAX ) continue ;
          ++nLep ;
          
          muons.push_back ( reader.Get4V ("muons")->at (muIt) ) ;
          leptons.push_back ( reader.Get4V ("muons")->at (muIt) ) ;      
        }
      
      if ( nLep < nLepMIN ) continue ;
      stepEvents[step] += 1 ;
      
      //************
      // cut on jets
      step = step + 1 ;
      
      int nJet = 0 ;
      std::vector<ROOT::Math::XYZTVector> jets ;
      for (unsigned int jetIt = 0 ; jetIt < (reader.Get4V ("jets")->size ()) ; ++jetIt)
        {
          ROOT::Math::XYZTVector jet = reader.Get4V ("jets")->at (jetIt) ;
          if ( jet.Et () < jetEtMIN ) continue ;
          
          bool skipJet = false ;
          for (unsigned int eleIt = 0 ; eleIt < electrons.size () ; ++eleIt)
            {
              ROOT::Math::XYZTVector ele = electrons.at (eleIt) ;
              if ( deltaR (jet.eta (), jet.phi (), ele.eta (), ele.phi ()) < 0.3 )
                skipJet = true ;
            }
          if (skipJet == true) continue ;
          
          ++nJet ;
          jets.push_back ( reader.Get4V ("jets")->at (jetIt) ) ;
        }
        
      if ( nJet < nJetMIN ) continue ;
      stepEvents[step] += 1 ;
      
      //*********
      // VBF cuts: at least one pair of jets with minima requirements
      step =step+1 ;
      stepName[step] = "VBF" ;
      
       bool isVBFCutsOk = false ;
       
       for (unsigned int jetIt1 = 0 ; jetIt1 < jets.size () ; ++jetIt1) {
         for (unsigned int jetIt2 = jetIt1+1 ; jetIt2 < jets.size () ; ++jetIt2) {
             ROOT::Math::XYZTVector jet1 = jets.at (jetIt1) ;
             ROOT::Math::XYZTVector jet2 = jets.at (jetIt2) ;
             ROOT::Math::XYZTVector jet12 = jet1 + jet2 ;
             
             if ((fabs (jet1.eta () - jet2.eta ()) > VBFDetaMIN) &&
                 (jet12.mass () > VBFMjjMIN) )
               isVBFCutsOk = true ;
           }    
       }
      if (isVBFCutsOk == false) continue ;
      stepEvents[step] += 1 ;
      
      cloneTree -> Fill () ;
      
    } // loop over the events
 
  
  for (step = 0 ; step < nStep ; ++step)
    {
      events -> SetBinContent (step+1, stepEvents[step]) ;
      events -> GetXaxis () -> SetBinLabel (step+1, stepName[step].c_str ()) ;
    }
  
  events -> Write () ;
  
  cloneTree -> AutoSave () ;
  std::cout << cloneTree->GetEntries () << " events selected out of " << chain -> GetEntries () << std::endl ;
  outputRootFile.Close () ;
  
  return 0 ;
}
