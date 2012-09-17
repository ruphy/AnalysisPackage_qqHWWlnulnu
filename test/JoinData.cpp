#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "qqHWWlnulnuUtils.h"
#include "../test/Read.cc"

#include "TSystem.h"

/// 
///       |        _)             __ \          |          
///       |   _ \   |  __ \       |   |   _` |  __|   _` | 
///   \   |  (   |  |  |   |      |   |  (   |  |    (   | 
///  \___/  \___/  _| _|  _|     ____/  \__,_| \__| \__,_| 
///                                                        
/// 

int main(int argc, char** argv)
{ 
 
 std::cout << "           " << std::endl;
 std::cout << "           " << std::endl;
 std::cout << "           " << std::endl;
 std::cout << "           |        _)             __ \\          |          " << std::endl;
 std::cout << "           |   _ \\   |  __ \\       |   |   _` |  __|   _` | " << std::endl; 
 std::cout << "       \\   |  (   |  |  |   |      |   |  (   |  |    (   | " << std::endl; 
 std::cout << "      \\___/  \\___/  _| _|  _|     ____/  \\__,_| \\__| \\__,_| " << std::endl; 
 std::cout << "           " << std::endl;                                                            
 std::cout << "           " << std::endl;     
 std::cout << "           " << std::endl;
 std::cout << "           " << std::endl;
 
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
 
 if(argc != 2)
 {
  std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName" << std::endl ;
  return 1;
 }
 
 // Parse the config file                                                                                                                                                          
 parseConfigFile (argv[1]) ;
 
 std::string treeName  = gConfigParser -> readStringOption("Input::treeName");
 std::string fileSamples = gConfigParser -> readStringOption("Input::fileSamples");
 std::string inputDirectory = gConfigParser -> readStringOption("Input::inputDirectory");
 
 std::string inputBeginningFile = "out_NtupleProducer_"; 
 try {
  inputBeginningFile = gConfigParser -> readStringOption("Input::inputBeginningFile");
 }
 catch (char const* exceptionString){
  std::cerr << " exception = " << exceptionString << std::endl;
 }
 std::cout << ">>>>> Input::inputBeginningFile  " << inputBeginningFile  << std::endl;  
 
 
 TTree *treeJetLepVect;
 
 char *nameSample[1000];
 char *nameHumanReadable[1000];
 char* xsectionName[1000];
 
 double Normalization[1000];
 double xsection[1000];
 char nameFileIn[1000];
 sprintf(nameFileIn,"%s",fileSamples.c_str());
 
 int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
 
 ///==== output file ====
 std::string OutFileName    = gConfigParser -> readStringOption("Output::outFileName");
 std::cout << ">>>>> Output::outFileName  " << OutFileName  << std::endl;  
  
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
 
 //==== remove previous output file 
 TString CommandToExec = Form ("rm %s",OutFileName.c_str());
 std::cout << " CommandToExec = " << CommandToExec.Data() << std::endl;
 gSystem->Exec(CommandToExec);  
 CommandToExec = Form ("rm temp_join_data_file.root");
 std::cout << " CommandToExec = " << CommandToExec.Data() << std::endl;
 gSystem->Exec(CommandToExec);  
 
 //==== add files together
 CommandToExec = Form ("hadd temp_join_data_file.root");
 for (int iSample=0; iSample<numberOfSamples; iSample++){
  char nameFile[20000];
  sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
  CommandToExec += " ";
  CommandToExec += nameFile;
  CommandToExec += " ";
 }
 std::cout << " CommandToExec = " << CommandToExec.Data() << std::endl;
 gSystem->Exec(CommandToExec);  
 
 
 TString fakeInputFile = Form ("temp_join_data_file.root");
 TFile* f = new TFile(fakeInputFile.Data(), "READ");  
 treeJetLepVect = (TTree*) f->Get(treeName.c_str());
 
 UInt_t run;
 UInt_t lumi;
 UInt_t event;
 
 treeJetLepVect -> SetBranchAddress("run",  &run);
 treeJetLepVect -> SetBranchAddress("lumi", &lumi);
 treeJetLepVect -> SetBranchAddress("event",&event);
 
 //Create a new file + a clone of old tree in new file
 TFile outFile(OutFileName.c_str(),"RECREATE");
 outFile.cd();
 TTree *newtree = treeJetLepVect -> CloneTree(0);
 
 // define map with events
 std::map<std::pair<uint,std::pair<uint,uint> >,int> eventsMap;  
 
 Long64_t nEvent = treeJetLepVect -> GetEntries();
 
 std::cout << " nEvent = " << nEvent << std::endl;
 std::cout.precision (2) ;
 
 Long64_t counter = 0;
 for (Long64_t iEvent = 0; iEvent<nEvent; iEvent++) {
  treeJetLepVect->GetEntry(iEvent);
  
  std::cout << "Processing: " << blue << (((double) iEvent)/nEvent)*100. << "% \r"  << normal << std::flush;   
  
  std::pair<uint,uint> eventLSandID(lumi, event);
  std::pair<uint,std::pair<uint,uint> > eventRUNandLSandID(run, eventLSandID);   
  if( eventsMap[eventRUNandLSandID] == 1 ) continue;
  else eventsMap[eventRUNandLSandID] = 1;
  
  counter++;
  newtree->Fill();
 }
 newtree->AutoSave();

 //==== remove temporary file
 CommandToExec = Form ("rm temp_join_data_file.root");
 std::cout << " CommandToExec = " << CommandToExec.Data() << std::endl;
 gSystem->Exec(CommandToExec);  
 
 
 std::cout << std::endl;
 std::cout << " counter = " << counter << " / " << nEvent << " = " << (double) counter / nEvent << std::endl;
 std::cout << std::endl;
 std::cout << " **** end **** " << std::endl;
 std::cout << std::endl;
 
}








