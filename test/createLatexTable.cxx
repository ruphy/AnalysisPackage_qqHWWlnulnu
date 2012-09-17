

void createLatexTable(){
 //  
 
 int nMass = 19;
 Double_t x_vals[40] = {110, 115, 120, 130, 140, 150, 160, 170, 180, 190, 200, 250, 300, 350, 400, 450, 500, 550, 600};
 
 
 std::ifstream FileSystTop ("test/Latinos/ttbar/result-syst.txt"); 
 std::vector<double> SystTop;
 
 std::string buffer;
 int iLine =0; 
 while(!FileSystTop.eof()) {
  getline(FileSystTop,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    SystTop.push_back(tempValueTop);
   }
  }
  iLine++;
 } 
 
 std::ifstream FileSystTopValueTop ("test/Latinos/ttbar/result-value.txt"); 
 std::vector<double> ValueTop;
 
 iLine =0; 
 while(!FileSystTopValueTop.eof()) {
  getline(FileSystTopValueTop,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueTop;
    line >> tempValueTop;
    ValueTop.push_back(tempValueTop);
   }
  }
  iLine++;
 } 
 
 std::ofstream myfileTop; 
 myfileTop.open ("TopCard_2j.txt");
 
 for (int iMass = 0; iMass<nMass; iMass++) {
//   if (iMass < 11) myfileTop << x_vals[iMass] << "   " << ValueTop.at(0) << "   " << SystTop.at(0) << std::endl;
//   else myfileTop << x_vals[iMass] << "   " << ValueTop.at(1) << "   " << SystTop.at(1) << std::endl;

 if (iMass < 11) myfileTop << x_vals[iMass] << "   " << ValueTop.at(0) << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
 else myfileTop << x_vals[iMass] << "   " << ValueTop.at(1) << "   " << ValueTop.at(1)*(SystTop.at(1)-1) << std::endl;
  
 }
 myfileTop.close();
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 std::ifstream FileSystDY ("test/Latinos/DYRinout/result-syst.txt"); 
 std::vector<double> SystDY;
 
 iLine =0; 
 while(!FileSystDY.eof()) {
  getline(FileSystDY,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    SystDY.push_back(tempValueDY);
   }
  }
  iLine++;
 } 
 
 std::ifstream FileSystDYValueDY ("test/Latinos/DYRinout/result-value.txt"); 
 std::vector<double> ValueDY;
 
 iLine =0; 
 while(!FileSystDYValueDY.eof()) {
  getline(FileSystDYValueDY,buffer);
  std::stringstream line( buffer );      
  if (iLine != 0){
   if (buffer != ""  && buffer.at(0) != '#') {
    
    double tempValueDY;
    line >> tempValueDY;
    ValueDY.push_back(tempValueDY);
   }
  }
  iLine++;
 } 
 
 std::ofstream myfileDY; 
 myfileDY.open ("DYCard_2j.txt");
 
 for (int iMass = 0; iMass<nMass; iMass++) {
//   if (iMass < 11) myfileDY << x_vals[iMass] << "   " << ValueDY.at(0) << "   " << SystDY.at(0) << std::endl;
//   else myfileDY << x_vals[iMass] << "   " << ValueDY.at(1) << "   " << SystDY.at(1) << std::endl;

 if (iMass < 11) myfileDY << x_vals[iMass] << "   " << ValueDY.at(0) << "   " << ValueDY.at(0)*(SystDY.at(0)-1) << std::endl;
 else myfileDY << x_vals[iMass] << "   " << ValueDY.at(1) << "   " << ValueDY.at(1)*(SystDY.at(1)-1) << std::endl;

 }
 myfileDY.close();
 
 
 
 
 std::cout << std::endl;
 std::cout << "more TopCard_2j.txt" << std::endl; 
 std::cout << "more DYCard_2j.txt" << std::endl;
 std::cout << std::endl;
 std::cout << "cp TopCard_2j.txt  ~/Dropbox/Public/VBF/2011Nov19" << std::endl; 
 std::cout << "cp DYCard_2j.txt   ~/Dropbox/Public/VBF/2011Nov19" << std::endl;
 std::cout << std::endl;
 
 
 gApplication->Terminate(0);
 
}


