

void createForMatt2012Analysis(std::string additional = ""){ // -shape for shape analysis
 //  
 
 int nMass = 27;
 Double_t x_vals[40] = {110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 170, 180, 190, 200, 250, 300, 350, 400, 450, 500, 550, 600, 700, 800, 900, 1000};
 

 
 std::string buffer;
 int iLine =0; 
 
 TString fileInName;
 
 ///---- 
 ///---- __ __|  _ \    _ \  
 ///----    |   |   |  |   | 
 ///----    |   |   |  ___/  
 ///----   _|  \___/  _|     
 ///----                     
 
 
 ///----   
 ///----       ___|   ____| 
 ///----    \___ \   |     
 ///----          |  __|   
 ///----    _____/  _|     
 ///----   
 
 std::cout << " Top sf " << std::endl;
 
 std::vector<double> SystTop_sf;
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-MCSub%s-sf.txt",additional.c_str());
 std::ifstream FileSystTop_MCSub_sf (fileInName.Data()); 
 std::vector<double> SystTop_MCSub_sf;
 
 iLine =0; 
 while(!FileSystTop_MCSub_sf.eof()) {
  getline(FileSystTop_MCSub_sf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_MCSub_sf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-CR-stat%s-sf.txt",additional.c_str());
 std::ifstream FileSystTop_CR_stat_sf (fileInName.Data()); 
 std::vector<double> SystTop_CR_stat_sf;
 
 iLine =0; 
 while(!FileSystTop_CR_stat_sf.eof()) {
  getline(FileSystTop_CR_stat_sf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_CR_stat_sf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-method%s-sf.txt",additional.c_str());
 std::ifstream FileSystTop_method_sf (fileInName.Data()); 
 std::vector<double> SystTop_method_sf;
 
 iLine =0; 
 while(!FileSystTop_method_sf.eof()) {
  getline(FileSystTop_method_sf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_method_sf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-stat%s-sf.txt",additional.c_str());
 std::ifstream FileSystTop_stat_sf (fileInName.Data()); 
 std::vector<double> SystTop_stat_sf;
 
 iLine =0; 
 while(!FileSystTop_stat_sf.eof()) {
  getline(FileSystTop_stat_sf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_stat_sf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-value%s-sf.txt",additional.c_str());
 std::ifstream FileSystTop_value_sf (fileInName.Data()); 
 std::vector<double> ValueTop_sf;
 
 iLine =0; 
 while(!FileSystTop_value_sf.eof()) {
  getline(FileSystTop_value_sf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    ValueTop_sf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for (int iMass = 0; iMass<nMass; iMass++) {
  SystTop_sf.push_back(1.000);
 }
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  double value = ValueTop_sf.at(iMass);
  
  double prev = SystTop_sf.at(iMass) - 1.000;
  double syst_MCSub = SystTop_MCSub_sf.at(iMass) - 1.000;
  double syst_CR_stat = SystTop_CR_stat_sf.at(iMass) - 1.000;
  double syst_method = SystTop_method_sf.at(iMass) - 1.000;
  
  SystTop_sf.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat + syst_method*syst_method);
//   SystTop_sf.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat);
  
 }
 
 
 std::ofstream myfileTop_sf; 
 fileInName = Form ("TopCard_2j%s-sf.txt",additional.c_str());
 myfileTop_sf.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number sf events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueTop_sf.at(iMass) / SystTop_stat_sf.at(iMass) ;
  double alpha = SystTop_stat_sf.at(iMass);
  myfileTop_sf << x_vals[iMass] << "   " <<  int(SR_B+0.1) << "   " << alpha << "   " << alpha * SystTop_sf.at(iMass) << std::endl;
 }
 myfileTop_sf.close();
 
 
 
 
 
 
 
 
    

 ///----   
 ///----      _ \   ____| 
 ///----     |   |  |     
 ///----     |   |  __|   
 ///----    \___/  _|    
 ///----   
 
 
 std::cout << " Top of " << std::endl;
 
 std::vector<double> SystTop_of;
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-MCSub%s-of.txt",additional.c_str());
 std::ifstream FileSystTop_MCSub_of (fileInName.Data()); 
 std::vector<double> SystTop_MCSub_of;
 
 iLine =0; 
 while(!FileSystTop_MCSub_of.eof()) {
  getline(FileSystTop_MCSub_of,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_MCSub_of.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-CR-stat%s-of.txt",additional.c_str());
 std::ifstream FileSystTop_CR_stat_of (fileInName.Data()); 
 std::vector<double> SystTop_CR_stat_of;
 
 iLine =0; 
 while(!FileSystTop_CR_stat_of.eof()) {
  getline(FileSystTop_CR_stat_of,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_CR_stat_of.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-method%s-of.txt",additional.c_str());
 std::ifstream FileSystTop_method_of (fileInName.Data()); 
 std::vector<double> SystTop_method_of;
 
 iLine =0; 
 while(!FileSystTop_method_of.eof()) {
  getline(FileSystTop_method_of,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_method_of.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-stat%s-of.txt",additional.c_str());
 std::ifstream FileSystTop_stat_of (fileInName.Data()); 
 std::vector<double> SystTop_stat_of;
 
 iLine =0; 
 while(!FileSystTop_stat_of.eof()) {
  getline(FileSystTop_stat_of,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_stat_of.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-value%s-of.txt",additional.c_str());
 std::ifstream FileSystTop_value_of (fileInName.Data()); 
 std::vector<double> ValueTop_of;
 
 iLine =0; 
 while(!FileSystTop_value_of.eof()) {
  getline(FileSystTop_value_of,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    ValueTop_of.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for (int iMass = 0; iMass<nMass; iMass++) {
  SystTop_of.push_back(1.000);
 }
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  double value = ValueTop_of.at(iMass);
  
  double prev = SystTop_of.at(iMass) - 1.000;
  double syst_MCSub = SystTop_MCSub_of.at(iMass) - 1.000;
  double syst_CR_stat = SystTop_CR_stat_of.at(iMass) - 1.000;
  double syst_method = SystTop_method_of.at(iMass) - 1.000;
  
  SystTop_of.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat + syst_method*syst_method);
//   SystTop_of.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat);
  
 }
 
 
 std::ofstream myfileTop_of; 
 fileInName = Form ("TopCard_2j%s-of.txt",additional.c_str());
 myfileTop_of.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number of events in control region
  //   col3: extrapolation factor to get the yield in signal regi" + additional + "on (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueTop_of.at(iMass) / SystTop_stat_of.at(iMass) ;
  double alpha = SystTop_stat_of.at(iMass);
  myfileTop_of << x_vals[iMass] << "   " << int(SR_B+0.1)  << "   " << alpha << "   " << alpha * SystTop_of.at(iMass) << std::endl;
 }
 myfileTop_of.close();
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 ///----    
 ///----       _ \   ____|                  ___|   ____| 
 ///----     |   |  |            |       \___ \   |     
 ///----     |   |  __|       _   _|           |  __|   
 ///----    \___/  _|           _|       _____/  _|     
 ///----                                               
 ///----   
 
 std::cout << " Top of+sf " << std::endl;
 
 std::vector<double> SystTop_ofsf;
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-MCSub%s-all.txt",additional.c_str());
 std::ifstream FileSystTop_MCSub_ofsf (fileInName.Data()); 
 std::vector<double> SystTop_MCSub_ofsf;
 
 iLine =0; 
 while(!FileSystTop_MCSub_ofsf.eof()) {
  getline(FileSystTop_MCSub_ofsf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    double tempValueTop;
    line >> tempValueTop;
    SystTop_MCSub_ofsf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-CR-stat%s-all.txt",additional.c_str());
 std::ifstream FileSystTop_CR_stat_ofsf (fileInName.Data()); 
 std::vector<double> SystTop_CR_stat_ofsf;
 
 iLine =0; 
 while(!FileSystTop_CR_stat_ofsf.eof()) {
  getline(FileSystTop_CR_stat_ofsf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_CR_stat_ofsf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-method%s-all.txt",additional.c_str());
 std::ifstream FileSystTop_method_ofsf (fileInName.Data()); 
 std::vector<double> SystTop_method_ofsf;
 
 iLine =0; 
 while(!FileSystTop_method_ofsf.eof()) {
  getline(FileSystTop_method_ofsf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_method_ofsf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-stat%s-all.txt",additional.c_str());
 std::ifstream FileSystTop_stat_ofsf (fileInName.Data()); 
 std::vector<double> SystTop_stat_ofsf;
 
 iLine =0; 
 while(!FileSystTop_stat_ofsf.eof()) {
  getline(FileSystTop_stat_ofsf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop_stat_ofsf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-value%s-all.txt",additional.c_str());
 std::ifstream FileSystTop_value_ofsf (fileInName.Data()); 
 std::vector<double> ValueTop_ofsf;
 
 iLine =0; 
 while(!FileSystTop_value_ofsf.eof()) {
  getline(FileSystTop_value_ofsf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    ValueTop_ofsf.push_back(tempValueTop);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for (int iMass = 0; iMass<nMass; iMass++) {
  SystTop_ofsf.push_back(1.000);
 }
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  double value = ValueTop_ofsf.at(iMass);
  
  double prev = SystTop_ofsf.at(iMass) - 1.000;
  double syst_MCSub = SystTop_MCSub_ofsf.at(iMass) - 1.000;
  double syst_CR_stat = SystTop_CR_stat_ofsf.at(iMass) - 1.000;
  double syst_method = SystTop_method_ofsf.at(iMass) - 1.000;
  
  SystTop_ofsf.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat + syst_method*syst_method);
//   SystTop_ofsf.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat);
  
 }
 
 
 std::ofstream myfileTop_ofsf; 
 fileInName = Form ("TopCard_2j%s_ofsf.txt",additional.c_str());
 myfileTop_ofsf.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number of events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueTop_ofsf.at(iMass) / SystTop_stat_ofsf.at(iMass) ;
  double alpha = SystTop_stat_ofsf.at(iMass);
  myfileTop_ofsf << x_vals[iMass] << "   " << int(SR_B+0.1) << "   " << alpha << "   " << alpha * SystTop_ofsf.at(iMass) << std::endl;
 }
 myfileTop_ofsf.close();
 
 
 
 
 
 
 
 ///----    
 ///----       ___|   ____|         /       _ \   ____|                   | _)  |   
 ///----    \___ \   |            /       |   |  |           __|  __ \   |  |  __| 
 ///----          |  __|         /        |   |  __|       \__ \  |   |  |  |  |   
 ///----    _____/  _|         _/        \___/  _|         ____/  .__/  _| _| \__| 
 ///----                                                         _|                
 ///----    
 
 
 
 ///----   
 ///----       ___|   ____| 
 ///----    \___ \   |     
 ///----          |  __|   
 ///----    _____/  _|     
 ///----   
 
 std::cout << " Top sf @WW level " << std::endl;
 
 std::vector<double> SystTopAtWW_sf;
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-MCSub%s-sf-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_MCSub_sf (fileInName.Data()); 
 std::vector<double> SystTopAtWW_MCSub_sf;
 
 iLine =0; 
 while(!FileSystTopAtWW_MCSub_sf.eof()) {
  getline(FileSystTopAtWW_MCSub_sf,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {   
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_MCSub_sf.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-CR-stat%s-sf-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_CR_stat_sf (fileInName.Data()); 
 std::vector<double> SystTopAtWW_CR_stat_sf;
 
 iLine =0; 
 while(!FileSystTopAtWW_CR_stat_sf.eof()) {
  getline(FileSystTopAtWW_CR_stat_sf,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {  
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_CR_stat_sf.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-method%s-sf-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_method_sf (fileInName.Data()); 
 std::vector<double> SystTopAtWW_method_sf;
 
 iLine =0; 
 while(!FileSystTopAtWW_method_sf.eof()) {
  getline(FileSystTopAtWW_method_sf,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {
   
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_method_sf.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-stat%s-sf-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_stat_sf (fileInName.Data()); 
 std::vector<double> SystTopAtWW_stat_sf;
 
 iLine =0; 
 while(!FileSystTopAtWW_stat_sf.eof()) {
  getline(FileSystTopAtWW_stat_sf,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_stat_sf.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-value%s-sf-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_value_sf (fileInName.Data()); 
 std::vector<double> ValueTopAtWW_sf;
 
 iLine =0; 
 while(!FileSystTopAtWW_value_sf.eof()) {
  getline(FileSystTopAtWW_value_sf,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {  
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   ValueTopAtWW_sf.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for (int iMass = 0; iMass<1; iMass++) {
  SystTopAtWW_sf.push_back(1.000);
 }
 
 for (int iMass = 0; iMass<1; iMass++) {
  double value = ValueTopAtWW_sf.at(iMass);
  
  double prev = SystTopAtWW_sf.at(iMass) - 1.000;
  double syst_MCSub = SystTopAtWW_MCSub_sf.at(iMass) - 1.000;
  double syst_CR_stat = SystTopAtWW_CR_stat_sf.at(iMass) - 1.000;
  double syst_method = SystTopAtWW_method_sf.at(iMass) - 1.000;
  
    SystTopAtWW_sf.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat + syst_method*syst_method);
//   SystTopAtWW_sf.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat);
  
 }
 
 
 std::ofstream myfileTopAtWW_sf; 
 fileInName = Form ("TopCard_2j%s_sf_WW.txt",additional.c_str());
 myfileTopAtWW_sf.open (fileInName.Data());
 
 for (int iMass = 0; iMass<1; iMass++) {
  //   col2: number sf events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueTopAtWW_sf.at(iMass) / SystTopAtWW_stat_sf.at(iMass) ;
  double alpha = SystTopAtWW_stat_sf.at(iMass);
  myfileTopAtWW_sf << " WW " << "   " <<  int(SR_B+0.1) << "   " << alpha << "   " << alpha * SystTopAtWW_sf.at(iMass) << std::endl;
 }
 myfileTopAtWW_sf.close();
 
 
 
 
 
 
 
 
 
 
 ///----   
 ///----      _ \   ____| 
 ///----     |   |  |     
 ///----     |   |  __|   
 ///----    \___/  _|    
 ///----   
 
 
 std::cout << " Top of @WW level" << std::endl;
 
 std::vector<double> SystTopAtWW_of;
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-MCSub%s-of-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_MCSub_of (fileInName.Data()); 
 std::vector<double> SystTopAtWW_MCSub_of;
 
 iLine =0; 
 while(!FileSystTopAtWW_MCSub_of.eof()) {
  getline(FileSystTopAtWW_MCSub_of,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') { 
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_MCSub_of.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-CR-stat%s-of-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_CR_stat_of (fileInName.Data()); 
 std::vector<double> SystTopAtWW_CR_stat_of;
 
 iLine =0; 
 while(!FileSystTopAtWW_CR_stat_of.eof()) {
  getline(FileSystTopAtWW_CR_stat_of,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {    
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_CR_stat_of.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-MCSub%s-of-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_method_of (fileInName.Data()); 
 std::vector<double> SystTopAtWW_method_of;
 
 iLine =0; 
 while(!FileSystTopAtWW_method_of.eof()) {
  getline(FileSystTopAtWW_method_of,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') { 
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_method_of.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-syst-stat%s-of-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_stat_of (fileInName.Data()); 
 std::vector<double> SystTopAtWW_stat_of;
 
 iLine =0; 
 while(!FileSystTopAtWW_stat_of.eof()) {
  getline(FileSystTopAtWW_stat_of,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') {
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   SystTopAtWW_stat_of.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/ttbar/result-value%s-of-WW.txt",additional.c_str());
 std::ifstream FileSystTopAtWW_value_of (fileInName.Data()); 
 std::vector<double> ValueTopAtWW_of;
 
 iLine =0; 
 while(!FileSystTopAtWW_value_of.eof()) {
  getline(FileSystTopAtWW_value_of,buffer);
  std::stringstream line( buffer );      
  if (buffer != ""  && buffer.at(0) != '#') { 
   double tempValueTopAtWW;
   line >> tempValueTopAtWW;
   ValueTopAtWW_of.push_back(tempValueTopAtWW);
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 for (int iMass = 0; iMass<1; iMass++) {
  SystTopAtWW_of.push_back(1.000);
 }
 
 for (int iMass = 0; iMass<1; iMass++) {
  double value = ValueTopAtWW_of.at(iMass);
  
  double prev = SystTopAtWW_of.at(iMass) - 1.000;
  double syst_MCSub = SystTopAtWW_MCSub_of.at(iMass) - 1.000;
  double syst_CR_stat = SystTopAtWW_CR_stat_of.at(iMass) - 1.000;
  double syst_method = SystTopAtWW_method_of.at(iMass) - 1.000;
  
  SystTopAtWW_of.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat + syst_method*syst_method);
//   SystTopAtWW_of.at(iMass) = sqrt( prev*prev + syst_MCSub*syst_MCSub + syst_CR_stat*syst_CR_stat);
  
 }
  
 std::ofstream myfileTopAtWW_of; 
 fileInName = Form ("TopCard_2j%s_of_WW.txt",additional.c_str());
 myfileTopAtWW_of.open (fileInName.Data());
 
 for (int iMass = 0; iMass<1; iMass++) {
  //   col2: number of events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueTopAtWW_of.at(iMass) / SystTopAtWW_stat_of.at(iMass) ;
  double alpha = SystTopAtWW_stat_of.at(iMass);
  myfileTopAtWW_of << " WW " << "   " << int(SR_B+0.1)  << "   " << alpha << "   " << alpha * SystTopAtWW_of.at(iMass) << std::endl;
 }
 myfileTopAtWW_of.close();
 
 
 std::cout << " Top of @Higgs level" << std::endl;
 
 
 double TopSF = ValueTopAtWW_sf.at(0);
 double TopOF = ValueTopAtWW_of.at(0);
 
 double errTopSF = sqrt(SystTopAtWW_sf.at(0) * TopSF * SystTopAtWW_sf.at(0) * TopSF +  SystTopAtWW_stat_sf.at(0) * TopSF);
 double errTopOF = sqrt(SystTopAtWW_of.at(0) * TopOF * SystTopAtWW_of.at(0) * TopOF +  SystTopAtWW_stat_of.at(0) * TopOF);
 
 std::cout << std::endl;
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << std::endl;
 std::cout << " TopSF = " << TopSF << " +/- " << errTopSF << std::endl;
 std::cout << " TopOF = " << TopOF << " +/- " << errTopOF << std::endl;
 std::cout << std::endl;
 std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
 std::cout << std::endl;
 
 double Rof    = TopOF / (TopSF+TopOF);
 double errRof = sqrt ( TopOF / (TopSF+TopOF) / (TopSF+TopOF) * errTopSF   * TopOF / (TopSF+TopOF) / (TopSF+TopOF) * errTopSF +     TopSF / (TopSF+TopOF) / (TopSF+TopOF) * errTopOF   * TopSF / (TopSF+TopOF) / (TopSF+TopOF) * errTopOF );
 
 double Rsf    = TopSF / (TopOF+TopSF);
 double errRsf = sqrt ( TopSF / (TopOF+TopSF) / (TopOF+TopSF) * errTopOF   * TopSF / (TopOF+TopSF) / (TopOF+TopSF) * errTopOF +     TopOF / (TopOF+TopSF) / (TopOF+TopSF) * errTopSF   * TopOF / (TopOF+TopSF) / (TopOF+TopSF) * errTopSF );
 
 double Rofsf    = TopOF / TopSF;
 double errRofsf = sqrt(errTopOF / TopSF * errTopOF / TopSF +  errTopSF * TopOF / TopSF  / TopSF * errTopSF * TopOF / TopSF / TopSF);
 
 
 
 
 std::ofstream myfileTop_of_withR; 
 fileInName = Form ("TopCard_2j%s_of_withR.txt",additional.c_str());
 myfileTop_of_withR.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number of events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueTop_ofsf.at(iMass) / SystTop_stat_ofsf.at(iMass) ;
  double alpha = SystTop_stat_ofsf.at(iMass) * Rof;
  double err_alpha = alpha * sqrt(SystTop_ofsf.at(iMass) * SystTop_ofsf.at(iMass) + errRof/Rof * errRof/Rof);
  myfileTop_of_withR << x_vals[iMass] << "   " << int(SR_B+0.1) << "   " << alpha << "   " << err_alpha << std::endl;
 }
 myfileTop_of_withR.close();
 
 
 std::ofstream myfileTop_sf_withR; 
 fileInName = Form ("TopCard_2j%s_sf_withR.txt",additional.c_str());
 myfileTop_sf_withR.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number sf events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueTop_ofsf.at(iMass) / SystTop_stat_ofsf.at(iMass) ;
  double alpha = SystTop_stat_ofsf.at(iMass) * Rsf;
  double err_alpha = alpha * sqrt(SystTop_ofsf.at(iMass) * SystTop_ofsf.at(iMass) + errRsf/Rsf * errRsf/Rsf);
  myfileTop_sf_withR << x_vals[iMass] << "   " << int(SR_B+0.1) << "   " << alpha << "   " << err_alpha << std::endl;
 }
 myfileTop_sf_withR.close();
 
 
 
 
 ///---- for my datacard ----
 std::ofstream myfileTop_of_withR_forMyDataCard_syst_stat; 
 fileInName = Form ("test/Latinos12/ttbar/result-syst-stat-withR%s-of.txt",additional.c_str());
 myfileTop_of_withR_forMyDataCard_syst_stat.open (fileInName.Data());
 myfileTop_of_withR_forMyDataCard_syst_stat << " top " << std::endl;
 for (int iMass = 0; iMass<nMass; iMass++) {
  double alpha = SystTop_stat_ofsf.at(iMass) * Rof;
  myfileTop_of_withR_forMyDataCard_syst_stat << alpha << "   " << std::endl;
 }
 myfileTop_of_withR_forMyDataCard_syst_stat.close();
 

 std::ofstream myfileTop_of_withR_forMyDataCard_syst_onR; 
 fileInName = Form ("test/Latinos12/ttbar/result-syst-onR-withR%s-of.txt",additional.c_str());
 myfileTop_of_withR_forMyDataCard_syst_onR.open (fileInName.Data());
 myfileTop_of_withR_forMyDataCard_syst_onR << " top " << std::endl;
 for (int iMass = 0; iMass<nMass; iMass++) {
  double alpha = SystTop_stat_ofsf.at(iMass) * Rof;
  double err_relative_alpha = errRof/Rof;
  myfileTop_of_withR_forMyDataCard_syst_onR << (1.000 + err_relative_alpha) << "   " << std::endl;
 }
 myfileTop_of_withR_forMyDataCard_syst_onR.close();
 
 
 std::ofstream myfileTop_withR_forMyDataCard_value_of; 
 fileInName = Form ("test/Latinos12/ttbar/result-value-R%s-of.txt",additional.c_str());
 myfileTop_withR_forMyDataCard_value_of.open (fileInName.Data());
 myfileTop_withR_forMyDataCard_value_of << " top " << std::endl; 
 for (int iMass = 0; iMass<nMass; iMass++) {
  double SR_B  = ValueTop_ofsf.at(iMass) / SystTop_stat_ofsf.at(iMass) ;
  double alpha = SystTop_stat_ofsf.at(iMass) * Rof;
  double value = alpha * SR_B;
  myfileTop_withR_forMyDataCard_value_of << value << "   " << std::endl;
 }
 myfileTop_withR_forMyDataCard_value_of.close();
 
 
 
 
 
 
 
 std::ofstream myfileTop_sf_withR_forMyDataCard_syst_stat; 
 fileInName = Form ("test/Latinos12/ttbar/result-syst-stat-withR%s-sf.txt",additional.c_str());
 myfileTop_sf_withR_forMyDataCard_syst_stat.open (fileInName.Data());
 myfileTop_sf_withR_forMyDataCard_syst_stat << " top " << std::endl;
 for (int iMass = 0; iMass<nMass; iMass++) {
  double alpha = SystTop_stat_ofsf.at(iMass) * Rsf;
  myfileTop_sf_withR_forMyDataCard_syst_stat << alpha << "   " << std::endl;
 }
 myfileTop_sf_withR_forMyDataCard_syst_stat.close();
 
 
 std::ofstream myfileTop_sf_withR_forMyDataCard_syst_onR; 
 fileInName = Form ("test/Latinos12/ttbar/result-syst-onR-withR%s-sf.txt",additional.c_str());
 myfileTop_sf_withR_forMyDataCard_syst_onR.open (fileInName.Data());
 myfileTop_sf_withR_forMyDataCard_syst_onR << " top " << std::endl;
 for (int iMass = 0; iMass<nMass; iMass++) {
  double alpha = SystTop_stat_ofsf.at(iMass) * Rsf;
  double err_relative_alpha = errRsf/Rsf;
  myfileTop_sf_withR_forMyDataCard_syst_onR << (1.000 - err_relative_alpha) << "   " << std::endl;  //---- opposite w.r.t. of
 }
 myfileTop_sf_withR_forMyDataCard_syst_onR.close();


 std::ofstream myfileTop_withR_forMyDataCard_value_sf; 
 fileInName = Form ("test/Latinos12/ttbar/result-value-R%s-sf.txt",additional.c_str());
 myfileTop_withR_forMyDataCard_value_sf.open (fileInName.Data());
 myfileTop_withR_forMyDataCard_value_sf << " top " << std::endl; 
 for (int iMass = 0; iMass<nMass; iMass++) {
  double SR_B  = ValueTop_ofsf.at(iMass) / SystTop_stat_ofsf.at(iMass) ;
  double alpha = SystTop_stat_ofsf.at(iMass) * Rsf;
  double value = alpha * SR_B;
  myfileTop_withR_forMyDataCard_value_sf << value << "   " << std::endl;
 }
 myfileTop_withR_forMyDataCard_value_sf.close();
 
 
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
 
 
 
 ///----  
 ///----     __ \ \ \   / 
 ///----    |   | \   /  
 ///----    |   |    |   
 ///----   ____/    _|   
 ///----                 
 
 
 std::vector<double> SystDY;
 
 std::cout << " DY mm " << std::endl;
 
 ///----                          
 ///----     __ `__ \   __ `__ \  
 ///----     |   |   |  |   |   | 
 ///----    _|  _|  _| _|  _|  _| 
 ///----                         
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/DYRinout/result-syst-method-mumu%s.txt",additional.c_str());
 std::ifstream FileSystDY_method_mumu (fileInName.Data()); 
 std::vector<double> SystDY_method_mumu;
 
 iLine =0; 
 while(!FileSystDY_method_mumu.eof()) {
  getline(FileSystDY_method_mumu,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    SystDY_method_mumu.push_back(tempValueDY);
   }
  }
  iLine++;
 } 
 

 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/DYRinout/result-syst-stat-mumu%s.txt",additional.c_str());
 std::ifstream FileSystDY_stat_mumu (fileInName.Data()); 
 std::vector<double> SystDY_stat_mumu;
 
 iLine =0; 
 while(!FileSystDY_stat_mumu.eof()) {
  getline(FileSystDY_stat_mumu,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    SystDY_stat_mumu.push_back(tempValueDY);
   }
  }
  iLine++;
 } 
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/DYRinout/result-value-mumu%s.txt",additional.c_str());
 std::ifstream FileSystDYValueDY_mumu (fileInName.Data()); 
 std::vector<double> ValueDY_mumu;
 
 iLine =0; 
 while(!FileSystDYValueDY_mumu.eof()) {
  getline(FileSystDYValueDY_mumu,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    ValueDY_mumu.push_back(tempValueDY);
   }
  }
  iLine++;
 }
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ofstream myfileDY_mumu; 
 fileInName = Form ("DYCard_mumu_2j%s.txt",additional.c_str());
 myfileDY_mumu.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number of events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueDY_mumu.at(iMass) / SystDY_stat_mumu.at(iMass) ;
  double alpha = SystDY_stat_mumu.at(iMass);
  double err_alpha = (SystDY_method_mumu.at(iMass) - 1.000) * alpha;
  myfileDY_mumu << x_vals[iMass] << "   " <<  int(SR_B+0.1) << "   " << alpha << "   " << err_alpha << std::endl;
 }
 myfileDY_mumu.close();
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 ///----                   
 ///----        _ \   _ \ 
 ///----        __/   __/ 
 ///----      \___| \___| 
 ///----                  
 
 
 std::cout << " DY ee " << std::endl;
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/DYRinout/result-syst-method-ee%s.txt",additional.c_str());
 std::ifstream FileSystDY_method_ee (fileInName.Data()); 
 std::vector<double> SystDY_method_ee;
 
 iLine =0; 
 while(!FileSystDY_method_ee.eof()) {
  getline(FileSystDY_method_ee,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    SystDY_method_ee.push_back(tempValueDY);
   }
  }
  iLine++;
 } 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/DYRinout/result-syst-stat-ee%s.txt",additional.c_str());
 std::ifstream FileSystDY_stat_ee (fileInName.Data()); 
 std::vector<double> SystDY_stat_ee;
 
 iLine =0; 
 while(!FileSystDY_stat_ee.eof()) {
  getline(FileSystDY_stat_ee,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    SystDY_stat_ee.push_back(tempValueDY);
   }
  }
  iLine++;
 } 
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 fileInName = Form ("test/Latinos12/DYRinout/result-value-ee%s.txt",additional.c_str());
 std::ifstream FileSystDYValueDY_ee (fileInName.Data()); 
 std::vector<double> ValueDY_ee;
 
 iLine =0; 
 while(!FileSystDYValueDY_ee.eof()) {
  getline(FileSystDYValueDY_ee,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    ValueDY_ee.push_back(tempValueDY);
   }
  }
  iLine++;
 }
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ofstream myfileDY_ee; 
 fileInName = Form ("DYCard_ee_2j%s.txt",additional.c_str());
 myfileDY_ee.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number of events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueDY_ee.at(iMass) / SystDY_stat_ee.at(iMass) ;
  double alpha = SystDY_stat_ee.at(iMass);
  double err_alpha = (SystDY_method_ee.at(iMass) - 1.000) * alpha;
  myfileDY_ee << x_vals[iMass] << "   " <<  int(SR_B+0.1) << "   " << alpha << "   " << err_alpha << std::endl;
 }
 myfileDY_ee.close();
 
 
 
 
 
 
 ///----                                                        
 ///----       __ `__ \   __ `__ \         |         _ \   _ \ 
 ///----       |   |   |  |   |   |     _   _|       __/   __/ 
 ///----      _|  _|  _| _|  _|  _|       _|       \___| \___| 
 ///----                                        

 std::ofstream myfileDY; 
 fileInName = Form ("DYCard_2j%s.txt",additional.c_str());
 myfileDY.open (fileInName.Data());
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col2: number of events in control region
  //   col3: extrapolation factor to get the yield in signal region (final yield = col2 * col3)
  //   col4: uncertainty on col3 in fraction (excluding the stat error on col2)
  double SR_B  = ValueDY_ee.at(iMass) / SystDY_stat_ee.at(iMass) + ValueDY_mumu.at(iMass) / SystDY_stat_mumu.at(iMass);
  double SR_A  = ValueDY_ee.at(iMass) + ValueDY_mumu.at(iMass);
  double alpha = SR_A / SR_B;
  
  double alpha_ee   = SystDY_stat_ee.at(iMass);
  double alpha_mumu = SystDY_stat_mumu.at(iMass);  
  double err_alpha_ee   = (SystDY_method_ee.at(iMass)   - 1.000) * alpha_ee;
  double err_alpha_mumu = (SystDY_method_mumu.at(iMass) - 1.000) * alpha_mumu;
  
  
  double err_alpha = sqrt( err_alpha_ee*err_alpha_ee + err_alpha_mumu*err_alpha_mumu ); 
  myfileDY << x_vals[iMass] << "   " << int(SR_B+0.1)  << "   " << alpha << "   " << err_alpha << std::endl;
 }
 myfileDY.close();
 
 
 
 
 
 
 ///----      
 ///----      \ \        /      _)        |         
 ///----       \ \  \   /   |    |   _ \  __|   __| 
 ///----        \ \  \ / _   _|  |   __/  |   \__ \ 
 ///----         \_/\_/    _|    | \___| \__| ____/ 
 ///----                     ___/                   
 ///----     

 
 
 
 std::cout << " W+jets " << std::endl;
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileValue_Wjets ("test/Latinos12/WJets/result-value.txt"); 
 std::vector<double> ValueWjets;
 
 iLine =0; 
 while(!FileValue_Wjets.eof()) {
  getline(FileValue_Wjets,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueWjets;
    line >> tempValueWjets;
    ValueWjets.push_back(tempValueWjets);
   }
  }
  iLine++;
 } 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileSyst_Wjets ("test/Latinos12/WJets/result-syst.txt"); 
 std::vector<double> SystWjets;
 
 iLine =0; 
 while(!FileSyst_Wjets.eof()) {
  getline(FileSyst_Wjets,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueWjets;
    line >> tempValueWjets;
    SystWjets.push_back(tempValueWjets);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ofstream myfileWjets; 
 myfileWjets.open ("WjetsCard_2j_ofsf.txt");
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col1: value
  //   col2: error
  double value = ValueWjets.at(iMass);
  double error = (SystWjets.at(iMass) - 1.000) * value;
  myfileWjets << x_vals[iMass] << "   " << value << "   " << error << std::endl;
 }
 myfileWjets.close();
 
 
 
 
 
 
 ///----      
 ///----      \ \        / _)        |               _ \   ____| 
 ///----       \ \  \   /   |   _ \  __|   __|      |   |  |     
 ///----        \ \  \ /    |   __/  |   \__ \      |   |  __|   
 ///----         \_/\_/     | \___| \__| ____/     \___/  _|     
 ///----                ___/                              
 ///----      
 
 
 
 
 
 std::cout << " W+jets OF " << std::endl;
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileValue_Wjets_of ("test/Latinos12/WJets/result-value-of.txt"); 
 std::vector<double> ValueWjets_of;
 
 iLine =0; 
 while(!FileValue_Wjets_of.eof()) {
  getline(FileValue_Wjets_of,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueWjets;
    line >> tempValueWjets;
    ValueWjets_of.push_back(tempValueWjets);
   }
  }
  iLine++;
 } 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileSyst_Wjets_of ("test/Latinos12/WJets/result-syst-of.txt"); 
 std::vector<double> SystWjets_of;
 
 iLine =0; 
 while(!FileSyst_Wjets_of.eof()) {
  getline(FileSyst_Wjets_of,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueWjets;
    line >> tempValueWjets;
    SystWjets_of.push_back(tempValueWjets);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ofstream myfileWjets_of; 
 myfileWjets_of.open ("WjetsCard_2j_of.txt");
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col1: value
  //   col2: error
  double value = ValueWjets_of.at(iMass);
  double error = (SystWjets_of.at(iMass) - 1.000) * value;
  myfileWjets_of << x_vals[iMass] << "   " << value << "   " << error << std::endl;
 }
 myfileWjets_of.close();
 
 
 
 
 
 
 ///----       
 ///----       \ \        / _)        |               ___|   ____| 
 ///----        \ \  \   /   |   _ \  __|   __|     \___ \   |     
 ///----         \ \  \ /    |   __/  |   \__ \           |  __|   
 ///----          \_/\_/     | \___| \__| ____/     _____/  _|     
 ///----                 ___/               
 ///----       
 
 
 
 
 std::cout << " W+jets SF " << std::endl;
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileValue_Wjets_sf ("test/Latinos12/WJets/result-value-sf.txt"); 
 std::vector<double> ValueWjets_sf;
 
 iLine =0; 
 while(!FileValue_Wjets_sf.eof()) {
  getline(FileValue_Wjets_sf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueWjets;
    line >> tempValueWjets;
    ValueWjets_sf.push_back(tempValueWjets);
   }
  }
  iLine++;
 } 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileSyst_Wjets_sf ("test/Latinos12/WJets/result-syst-sf.txt"); 
 std::vector<double> SystWjets_sf;
 
 iLine =0; 
 while(!FileSyst_Wjets_sf.eof()) {
  getline(FileSyst_Wjets_sf,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueWjets;
    line >> tempValueWjets;
    SystWjets_sf.push_back(tempValueWjets);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ofstream myfileWjets_sf; 
 myfileWjets_sf.open ("WjetsCard_2j_sf.txt");
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col1: value
  //   col2: error
  double value = ValueWjets_sf.at(iMass);
  double error = (SystWjets_sf.at(iMass) - 1.000) * value;
  myfileWjets_sf << x_vals[iMass] << "   " << value << "   " << error << std::endl;
 }
 myfileWjets_sf.close();
 
 
 
 
 
 
 
 ///----     
 ///----      __ \ \ \   /  |                  |                 
 ///----      |   | \   /   __|   _` |  |   |  __|   _` |  |   | 
 ///----      |   |    |    |    (   |  |   |  |    (   |  |   | 
 ///----     ____/    _|   \__| \__,_| \__,_| \__| \__,_| \__,_| 
 ///----                                                         

 
 
 
 
 std::cout << " DYtautau " << std::endl;
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileValue_DYtautau ("test/Latinos12/DYtautau/result-value.txt"); 
 std::vector<double> ValueDYtautau;
 
 iLine =0; 
 while(!FileValue_DYtautau.eof()) {
  getline(FileValue_DYtautau,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDYtautau;
    line >> tempValueDYtautau;
    ValueDYtautau.push_back(tempValueDYtautau);
   }
  }
  iLine++;
 } 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ifstream FileSyst_DYtautau ("test/Latinos12/DYtautau/result-syst.txt"); 
 std::vector<double> SystDYtautau;
 
 iLine =0; 
 while(!FileSyst_DYtautau.eof()) {
  getline(FileSyst_DYtautau,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDYtautau;
    line >> tempValueDYtautau;
    SystDYtautau.push_back(tempValueDYtautau);
   }
  }
  iLine++;
 }
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 std::ofstream myfileDYtautau; 
 myfileDYtautau.open ("DYtautauCard_2j.txt");
 
 for (int iMass = 0; iMass<nMass; iMass++) {
  //   col1: value
  //   col2: error
  double value = ValueDYtautau.at(iMass);
  double error = (SystDYtautau.at(iMass) - 1.000) * value;
  myfileDYtautau << x_vals[iMass] << "   " << value << "   " << error << std::endl;
 }
 myfileDYtautau.close();
 
 
 
 
 
 
 
 
 
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
 std::cout << std::endl;
 std::cout << "more TopCard_2j" << additional << "_sf.txt"   << std::endl; 
 std::cout << "more TopCard_2j" << additional << "_of.txt"   << std::endl; 
 std::cout << "more TopCard_2j" << additional << "_ofsf.txt" << std::endl; 
 std::cout << std::endl;
 std::cout << "more DYCard_mumu_2j" << additional << ".txt" << std::endl;
 std::cout << "more DYCard_ee_2j" << additional << ".txt" << std::endl;
 std::cout << "more DYCard_2j" << additional << ".txt" << std::endl;
 std::cout << std::endl;
 std::cout << "more DYtautauCard_2j.txt" << std::endl;
 std::cout << std::endl;
 std::cout << "more WjetsCard_2j_sf.txt" << std::endl;
 std::cout << "more WjetsCard_2j_of.txt" << std::endl;
 std::cout << "more WjetsCard_2j_ofsf.txt" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "more TopCard_2j" << additional << "_sf_WW.txt"   << std::endl; 
 std::cout << "more TopCard_2j" << additional << "_of_WW.txt"   << std::endl; 
 std::cout << std::endl;
 std::cout << "more TopCard_2j" << additional << "_sf_withR.txt"   << std::endl; 
 std::cout << "more TopCard_2j" << additional << "_of_withR.txt"   << std::endl;  
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << " Rof   = " << Rof   << " +/- " << errRof   << std::endl;
 std::cout << " Rsf   = " << Rsf   << " +/- " << errRsf   << std::endl;
 std::cout << " Rofsf = " << Rofsf << " +/- " << errRofsf << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
//  std::cout << "mkdir  ~/Dropbox/Public/VBF/2012Jun10" << std::endl; 
//  std::cout << std::endl;
//  std::cout << "cp TopCard_2j_sf.txt  ~/Dropbox/Public/VBF/2012Jun10/" << std::endl; 
//  std::cout << "cp TopCard_2j_of.txt   ~/Dropbox/Public/VBF/2012Jun10/" << std::endl;
//  std::cout << "cp TopCard_2j_ofsf.txt   ~/Dropbox/Public/VBF/2012Jun10/" << std::endl;
//  std::cout << std::endl;
//  std::cout << "cp DYCard_mumu_2j.txt   ~/Dropbox/Public/VBF/2012Jun10/" << std::endl;
//  std::cout << "cp DYCard_ee_2j.txt   ~/Dropbox/Public/VBF/2012Jun10/" << std::endl;
//  std::cout << "cp DYCard_2j.txt   ~/Dropbox/Public/VBF/2012Jun10/" << std::endl;
//  std::cout << std::endl;
//  std::cout << std::endl;
 
//  std::cout << "mkdir  ~/Dropbox/Public/VBF/2012Jun14-Result" << std::endl; 
//  std::cout << std::endl;
//  std::cout << "cp TopCard_2j_sf.txt  ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl; 
//  std::cout << "cp TopCard_2j_of.txt   ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << "cp TopCard_2j_ofsf.txt   ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << std::endl;
//  std::cout << "cp TopCard_2j_sf_withR.txt  ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl; 
//  std::cout << "cp TopCard_2j_of_withR.txt  ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << std::endl;
//  std::cout << "cp DYCard_mumu_2j.txt   ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << "cp DYCard_ee_2j.txt   ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << "cp DYCard_2j.txt   ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << std::endl;
//  std::cout << "cp DYtautauCard_2j.txt   ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << std::endl;
//  std::cout << "cp WjetsCard_2j_sf.txt     ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << "cp WjetsCard_2j_of.txt     ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << "cp WjetsCard_2j_ofsf.txt   ~/Dropbox/Public/VBF/2012Jun14-Result/" << std::endl;
//  std::cout << std::endl;
//  std::cout << std::endl;
 
 

 std::cout << "mkdir  ~/Dropbox/Public/VBF/2012Jun27-Result" << std::endl; 
 std::cout << std::endl;
//  std::cout << "cp TopCard_2j" << additional << "_sf.txt  ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl; 
//  std::cout << "cp TopCard_2j" << additional << "_of.txt   ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << "cp TopCard_2j" << additional << "_ofsf.txt   ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << std::endl;
 std::cout << "cp TopCard_2j" << additional << "_sf_withR.txt  ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl; 
 std::cout << "cp TopCard_2j" << additional << "_of_withR.txt  ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << std::endl;
 std::cout << "cp DYCard_mumu_2j" << additional << ".txt   ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << "cp DYCard_ee_2j" << additional << ".txt   ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << "cp DYCard_2j" << additional << ".txt   ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << std::endl;
 std::cout << "cp DYtautauCard_2j.txt   ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << std::endl;
 std::cout << "cp WjetsCard_2j_sf.txt     ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << "cp WjetsCard_2j_of.txt     ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << "cp WjetsCard_2j_ofsf.txt   ~/Dropbox/Public/VBF/2012Jun27-Result/" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
 
 
 gApplication->Terminate(0);
 
}


