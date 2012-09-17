// 
// Template from http://root.cern.ch/svn/root/trunk/tmva/test/TMVAClassification.C
// 

#include "ConfigParser.h"
#include "ntpleUtils.h"

#include "../test/Read.cc"

#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"

#include "TMVAGui.C"
#include "TMVA/MethodCategory.h"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif



int main(int argc, char** argv) { 
  
  if(argc != 2)
  {
   std::cerr << ">>>>> analysis.cpp::usage: " << argv[0] << " configFileName      MVAconfigFileName" << std::endl ;
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
  
  
  
  double LUMI = gConfigParser -> readDoubleOption("Options::Lumi");
  
  std::vector<std::string> SignalName;
  SignalName = gConfigParser -> readStringListOption("Options::SignalName");
  
  for (int iSignalSample=0; iSignalSample<SignalName.size(); iSignalSample++){ 
   std::cout << " Signal[" << iSignalSample << "] = " << SignalName.at(iSignalSample) << std::endl;
  }
  
  std::string nameWeight = "1"; 
  try {
   nameWeight = gConfigParser -> readStringOption("Options::nameWeight");
  }
  catch (char const* exceptionString){
   std::cerr << " exception = " << exceptionString << std::endl;
  }
  std::cout << ">>>>> Input::nameWeight  " << nameWeight  << std::endl;  
  
  
  
  TTree *treeJetLepVect[200];
  
  char *nameSample[1000];
  char *nameHumanReadable[1000];
  char* xsectionName[1000];
  
  char nameFileIn[1000];
  sprintf(nameFileIn,"%s",fileSamples.c_str());
  
  int numberOfSamples = ReadFile(nameFileIn, nameSample, nameHumanReadable, xsectionName);
  
  double Normalization[1000];
  double xsection[1000];
  
  for (int iSample=0; iSample<numberOfSamples; iSample++){
   xsection[iSample] = atof(xsectionName[iSample]);
  }
  
  for (int iSample=0; iSample<numberOfSamples; iSample++){ 
   char nameFile[20000];
   sprintf(nameFile,"%s/%s%s.root",inputDirectory.c_str(),inputBeginningFile.c_str(),nameSample[iSample]);  
   
   TFile* f = new TFile(nameFile, "READ");
   
   treeJetLepVect[iSample] = (TTree*) f->Get(treeName.c_str());
   char nameTreeJetLep[100];
   sprintf(nameTreeJetLep,"treeJetLep_%d",iSample); 
   treeJetLepVect[iSample]->SetName(nameTreeJetLep);

   double XSection;
   XSection = xsection[iSample];
   Normalization[iSample] = XSection * LUMI / 1000.; 
  }
  
  //==== cut
  std::string CutFile = gConfigParser -> readStringOption("Selections::CutFile");
  std::vector<std::string> vCut;
  std::cout << " nCuts   = " << ReadFileCut(CutFile, vCut) << std::endl;
  
  std::string Cut;
  if (vCut.size() != 0) {
   Cut = vCut.at(0);
  }
  else {
   Cut = "1";
  }
  
  //==== HiggsMass
  std::string HiggsMass = gConfigParser -> readStringOption("Options::HiggsMass");

  //==== list of methods
  std::vector<std::string> vectorMyMethodList = gConfigParser -> readStringListOption("Options::MVAmethods");
  TString myMethodList;
  for (int iMVA = 0; iMVA < vectorMyMethodList.size(); iMVA++) {
   if (iMVA == 0) myMethodList = Form ("%s",vectorMyMethodList.at(iMVA).c_str());
   else           myMethodList = Form ("%s,%s",myMethodList.Data(),vectorMyMethodList.at(iMVA).c_str());
  }
  
  //==== output
  TString outfileName = gConfigParser -> readStringOption("Output::outFileName");
  
  
  // This loads the library
  TMVA::Tools::Instance();
  
  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;
  
  // --- Cut optimisation
  Use["Cuts"]            = 1;
  Use["CutsD"]           = 1;
  Use["CutsPCA"]         = 0;
  Use["CutsGA"]          = 0;
  Use["CutsSA"]          = 0;
  // 
  // --- 1-dimensional likelihood ("naive Bayes estimator")
  Use["Likelihood"]      = 1;
  Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
  Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
  Use["LikelihoodKDE"]   = 0;
  Use["LikelihoodMIX"]   = 0;
  //
  // --- Mutidimensional likelihood and Nearest-Neighbour methods
  Use["PDERS"]           = 1;
  Use["PDERSD"]          = 0;
  Use["PDERSPCA"]        = 0;
  Use["PDEFoam"]         = 1;
  Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
  Use["KNN"]             = 1; // k-nearest neighbour method
  //
  // --- Linear Discriminant Analysis
  Use["LD"]              = 1; // Linear Discriminant identical to Fisher
  Use["Fisher"]          = 0;
  Use["FisherG"]         = 0;
  Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
  Use["HMatrix"]         = 0;
  //
  // --- Function Discriminant analysis
  Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
  Use["FDA_SA"]          = 0;
  Use["FDA_MC"]          = 0;
  Use["FDA_MT"]          = 0;
  Use["FDA_GAMT"]        = 0;
  Use["FDA_MCMT"]        = 0;
  //
  // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
  Use["MLP"]             = 0; // Recommended ANN
  Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
  Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
  Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
  Use["TMlpANN"]         = 0; // ROOT's own ANN
  //
  // --- Support Vector Machine 
  Use["SVM"]             = 1;
  // 
  // --- Boosted Decision Trees
  Use["BDT"]             = 1; // uses Adaptive Boost
  Use["BDTG"]            = 0; // uses Gradient Boost
  Use["BDTB"]            = 0; // uses Bagging
  Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
  Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
  // 
  // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
  Use["RuleFit"]         = 1;
  // ---------------------------------------------------------------
  Use["MLPCat"]          = 0;
  Use["BDTCat"]          = 0;
     
  std::cout << std::endl;
  std::cout << "==> Start TMVAClassification" << std::endl;
  
  // Select methods (don't look at this code - not of interest)
  if (myMethodList != "") {
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
      
      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
   for (UInt_t i=0; i<mlist.size(); i++) {
    std::string regMethod(mlist[i]);
    
    if (Use.find(regMethod) == Use.end()) {
     std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
     for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
      std::cout << std::endl;
     return 0;
    }
    Use[regMethod] = 1;
   }
  }
  
  // --------------------------------------------------------------------------------------------------
  // --- Here the preparation phase begins
  
  // Create a new root output file
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
    
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
  
  factory->AddVariable( "jetpt1" , 'F');
  factory->AddVariable( "jetpt2" , 'F');
  factory->AddVariable( "mjj" , 'F');
  factory->AddVariable( "detajj" , 'F');
  factory->AddVariable( "dphilljetjet" , 'F');
  
  factory->AddVariable( "pt1" , 'F');
  factory->AddVariable( "pt2" , 'F');
  factory->AddVariable( "mll" , 'F');
  factory->AddVariable( "dphill" , 'F');
  factory->AddVariable( "mth" , 'F');
  
  factory->AddVariable( "dphillmet" , 'F');
  factory->AddVariable( "mpmet" , 'F');
  
  factory->AddSpectator( "channel" , 'F');
  
  
  for (int iSample=0; iSample<numberOfSamples; iSample++){ 
   int numEnt = treeJetLepVect[iSample]->GetEntries(Cut.c_str());
   std::cout << " Sample = " << nameSample[iSample] << " ~ " << nameHumanReadable[iSample] << " --> " << numEnt << std::endl;
   if (numEnt != 0) { 
    bool isSig = false;
    for (std::vector<std::string>::const_iterator itSig = SignalName.begin(); itSig != SignalName.end(); itSig++){
     if (nameHumanReadable[iSample] == *itSig) isSig = true;
    }
    if (isSig) {
     factory->AddSignalTree(     treeJetLepVect[iSample], Normalization[iSample] );
    }
    else {
     factory->AddBackgroundTree( treeJetLepVect[iSample], Normalization[iSample] );
    }
   }
  }
  
  
  TCut mycuts = Cut.c_str();
  TCut mycutb = Cut.c_str();
  
  
  
  factory->SetWeightExpression( nameWeight.c_str() );
//   factory->SetBackgroundWeightExpression( nameWeight.c_str() );
//   factory->SetSignalWeightExpression    ( nameWeight.c_str() );
  
  factory->PrepareTrainingAndTestTree( mycuts, mycutb,"SplitMode=Random:NormMode=None:!V");
  
  // Cut optimisation
  if (Use["Cuts"]) factory->BookMethod( TMVA::Types::kCuts, "Cuts","!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
  
  if (Use["CutsD"]) factory->BookMethod( TMVA::Types::kCuts, "CutsD","!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );
  
  if (Use["CutsPCA"]) factory->BookMethod( TMVA::Types::kCuts, "CutsPCA","!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

  if (Use["CutsGA"])   factory->BookMethod( TMVA::Types::kCuts, "CutsGA","H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

  if (Use["CutsSA"]) factory->BookMethod( TMVA::Types::kCuts, "CutsSA","!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

  // Likelihood ("naive Bayes estimator")
  if (Use["Likelihood"]) factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood","H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

  // Decorrelated likelihood
  if (Use["LikelihoodD"]) factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD","!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );
 
  // PCA-transformed likelihood
  if (Use["LikelihoodPCA"]) factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodPCA","!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 
  
  // Use a kernel density estimator to approximate the PDFs
  if (Use["LikelihoodKDE"]) factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE","!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 
   
  // Use a variable-dependent mix of splines and kernel density estimator
  if (Use["LikelihoodMIX"]) factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodMIX","!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 
    
  // Test the multi-dimensional probability density estimator
  // here are the options strings for the MinMax and RMS methods, respectively:
  //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
  //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
  if (Use["PDERS"]) factory->BookMethod( TMVA::Types::kPDERS, "PDERS","!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );
     
  if (Use["PDERSD"]) factory->BookMethod( TMVA::Types::kPDERS, "PDERSD","!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );
      
  if (Use["PDERSPCA"]) factory->BookMethod( TMVA::Types::kPDERS, "PDERSPCA","!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );
      
  // Multi-dimensional likelihood estimator using self-adapting phase-space binning
  if (Use["PDEFoam"]) factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoam","!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );
       
  if (Use["PDEFoamBoost"]) factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoamBoost","!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );
       
  // K-Nearest Neighbour classifier (KNN)
  if (Use["KNN"]) factory->BookMethod( TMVA::Types::kKNN, "KNN","H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
       
  // H-Matrix (chi2-squared) method
  if (Use["HMatrix"]) factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );
       
  // Linear discriminant (same as Fisher discriminant)
  if (Use["LD"]) factory->BookMethod( TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
     
  // Fisher discriminant (same as LD)
  if (Use["Fisher"]) factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
     
  // Fisher with Gauss-transformed input variables
  if (Use["FisherG"]) factory->BookMethod( TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );
      
  // Composite classifier: ensemble (tree) of boosted Fisher classifiers
  if (Use["BoostedFisher"]) factory->BookMethod( TMVA::Types::kFisher, "BoostedFisher","H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );
  
  // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
  if (Use["FDA_MC"]) factory->BookMethod( TMVA::Types::kFDA, "FDA_MC","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );
   
  // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
  if (Use["FDA_GA"]) factory->BookMethod( TMVA::Types::kFDA, "FDA_GA","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );
   
  // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
  if (Use["FDA_SA"]) factory->BookMethod( TMVA::Types::kFDA, "FDA_SA","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
   
  if (Use["FDA_MT"]) factory->BookMethod( TMVA::Types::kFDA, "FDA_MT","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );
    
  if (Use["FDA_GAMT"]) factory->BookMethod( TMVA::Types::kFDA, "FDA_GAMT","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );
     
  if (Use["FDA_MCMT"]) factory->BookMethod( TMVA::Types::kFDA, "FDA_MCMT","H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );
   
  // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
//   if (Use["MLP"]) factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
  if (Use["MLP"]) factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=G,N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
  
  if (Use["MLPBFGS"]) factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );
   
  if (Use["MLPBNN"]) factory->BookMethod( TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators
    
  // CF(Clermont-Ferrand)ANN
  if (Use["CFMlpANN"]) factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  
      
  // Tmlp(Root)ANN
  if (Use["TMlpANN"]) factory->BookMethod( TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
       
  // Support Vector Machine
  if (Use["SVM"]) factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );
    
  // Boosted Decision Trees
  // Gradient Boost
  if (Use["BDTG"]) factory->BookMethod( TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:NNodesMax=5" );
  
  // Adaptive Boost
//   if (Use["BDT"]) factory->BookMethod( TMVA::Types::kBDT, "BDT","!H:!V:NTrees=850:nEventsMin=150:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
//   if (Use["BDT"]) factory->BookMethod( TMVA::Types::kBDT, "BDT","!H:!V:NTrees=500:nEventsMin=150:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
  if (Use["BDT"]) factory->BookMethod( TMVA::Types::kBDT, "BDT","!H:!V:VarTransform=G,N:NTrees=500:nEventsMin=150:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
  
  // Bagging
  if (Use["BDTB"]) factory->BookMethod( TMVA::Types::kBDT, "BDTB","!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
      
  // Decorrelation + Adaptive Boost
  if (Use["BDTD"]) factory->BookMethod( TMVA::Types::kBDT, "BDTD","!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
      
  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
  if (Use["BDTF"]) factory->BookMethod( TMVA::Types::kBDT, "BDTMitFisher","!H:!V:NTrees=50:nEventsMin=150:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
      
  // RuleFit -- TMVA implementation of Friedman's method
  if (Use["RuleFit"]) factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit","H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
       
  // ---------------------------
  // ---- define categories ----
  if (Use["MLPCat"]) {
   TMVA::MethodCategory* mcat = 0;
   TMVA::MethodBase* liCat = factory->BookMethod( TMVA::Types::kCategory, "MLPCat","" );
   mcat = dynamic_cast<TMVA::MethodCategory*>(liCat);
   
   TString theCatVars = "jetpt1:jetpt2:mjj:detajj:dphilljetjet:pt1:pt2:mll:dphill:mth:dphillmet:mpmet";      
   mcat->AddMethod( "abs(channel-0)<0.5",theCatVars, TMVA::Types::kMLP, "Category_MLP_mm","H:!V:NeuronType=tanh:VarTransform=G,N:NCycles=500:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
   mcat->AddMethod( "abs(channel-3)<0.5",theCatVars, TMVA::Types::kMLP, "Category_MLP_me","H:!V:NeuronType=tanh:VarTransform=G,N:NCycles=500:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
   mcat->AddMethod( "abs(channel-2)<0.5",theCatVars, TMVA::Types::kMLP, "Category_MLP_em","H:!V:NeuronType=tanh:VarTransform=G,N:NCycles=500:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
   mcat->AddMethod( "abs(channel-1)<0.5",theCatVars, TMVA::Types::kMLP, "Category_MLP_ee","H:!V:NeuronType=tanh:VarTransform=G,N:NCycles=500:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
   //    # mumu 
   //    channel == 0
   //    # mue
   //    channel == 3
   //    # emu 
   //    channel == 2
   //    # ee
   //    channel == 1
  }

  
  if (Use["BDTCat"]) {
   TMVA::MethodCategory* mcat = 0;
   TMVA::MethodBase* liCat = factory->BookMethod( TMVA::Types::kCategory, "BDTCat","" );
   mcat = dynamic_cast<TMVA::MethodCategory*>(liCat);
   
   TString theCatVars = "jetpt1:jetpt2:mjj:detajj:dphilljetjet:pt1:pt2:mll:dphill:mth:dphillmet:mpmet";      
   mcat->AddMethod( "abs(channel-0)<0.5",theCatVars, TMVA::Types::kBDT, "Category_BDT_mm","!H:!V:VarTransform=G,N:NTrees=700:nEventsMin=150:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=50:PruneMethod=NoPruning" );
   mcat->AddMethod( "abs(channel-3)<0.5",theCatVars, TMVA::Types::kBDT, "Category_BDT_me","!H:!V:VarTransform=G,N:NTrees=700:nEventsMin=150:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=50:PruneMethod=NoPruning" );
   mcat->AddMethod( "abs(channel-2)<0.5",theCatVars, TMVA::Types::kBDT, "Category_BDT_em","!H:!V:VarTransform=G,N:NTrees=700:nEventsMin=150:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=50:PruneMethod=NoPruning" );
   mcat->AddMethod( "abs(channel-1)<0.5",theCatVars, TMVA::Types::kBDT, "Category_BDT_ee","!H:!V:VarTransform=G,N:NTrees=700:nEventsMin=150:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=50:PruneMethod=NoPruning" );
  }
  
  
  
  //==== Optimize parameters in MVA methods
//   factory->OptimizeAllMethods();
//   factory->OptimizeAllMethods("ROCIntegral","Scan");
  //==== Train MVAs using the set of training events ====
  factory->TrainAllMethods();
  
  //==== Evaluate all MVAs using the set of test events ====
  factory->TestAllMethods();
  
  //==== Evaluate and compare performance of all configured MVAs ====
  factory->EvaluateAllMethods();    
  
  // --------------------------------------------------------------
  
  // Save the output
  outputFile->Close();
  
  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAnalysis is done!" << std::endl;      
  
  delete factory;
  
  //==== change position of weights file
  std::string toDo;
  
  toDo = "rm -r Weights-MVA/weights_" + HiggsMass + "_testVariables";
  std::cerr << "toDo = " << toDo << std::endl;
  system (toDo.c_str()); 
  
  toDo = "mv weights Weights-MVA/weights_" + HiggsMass + "_testVariables";
  std::cerr << "toDo = " << toDo << std::endl;
  system (toDo.c_str()); 
  
  // Launch the GUI for the root macros
  //   if (!gROOT->IsBatch()) TMVAGui( outfileName );
}



