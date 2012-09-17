

void createForMatt(){
 //  
 
 int nMass = 19;
 Double_t x_vals[40] = {110, 115, 120, 130, 140, 150, 160, 170, 180, 190, 200, 250, 300, 350, 400, 450, 500, 550, 600};
//  int nMass = 25;
//  Double_t x_vals[40] = {110, 115, 118, 120, 122, 124, 126, 128, 130, 135, 140, 150, 160, 170, 180, 190, 200, 250, 300, 350, 400, 450, 500, 550, 600};
 
 
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
  
  //  if (iMass < 11) myfileTop << x_vals[iMass] << "   " << ValueTop.at(0) << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
  //  else myfileTop << x_vals[iMass] << "   " << ValueTop.at(1) << "   " << ValueTop.at(1)*(SystTop.at(1)-1) << std::endl;
  
  if (iMass == 0)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(0)  << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
  if (iMass == 1)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(0)  << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
  if (iMass == 2)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(0)  << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
  if (iMass == 3)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(0)  << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
  if (iMass == 4)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(0)  << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
  if (iMass == 5)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(0)  << "   " << ValueTop.at(0)*(SystTop.at(0)-1) << std::endl;
  if (iMass == 6)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(1)  << "   " << ValueTop.at(1)*(SystTop.at(1)-1) << std::endl;
  if (iMass == 7)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(1)  << "   " << ValueTop.at(1)*(SystTop.at(1)-1) << std::endl;
  if (iMass == 8)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(1)  << "   " << ValueTop.at(1)*(SystTop.at(1)-1) << std::endl;
  if (iMass == 9)  myfileTop << x_vals[iMass] << "   " << ValueTop.at(2)  << "   " << ValueTop.at(2)*(SystTop.at(2)-1) << std::endl;
  if (iMass == 10) myfileTop << x_vals[iMass] << "   " << ValueTop.at(2)  << "   " << ValueTop.at(2)*(SystTop.at(2)-1) << std::endl;
  if (iMass == 11) myfileTop << x_vals[iMass] << "   " << ValueTop.at(3)  << "   " << ValueTop.at(3)*(SystTop.at(3)-1) << std::endl;
  if (iMass == 12) myfileTop << x_vals[iMass] << "   " << ValueTop.at(3)  << "   " << ValueTop.at(3)*(SystTop.at(3)-1) << std::endl;
  if (iMass == 13) myfileTop << x_vals[iMass] << "   " << ValueTop.at(3)  << "   " << ValueTop.at(3)*(SystTop.at(3)-1) << std::endl;
  if (iMass == 14) myfileTop << x_vals[iMass] << "   " << ValueTop.at(4)  << "   " << ValueTop.at(4)*(SystTop.at(4)-1) << std::endl;
  if (iMass == 15) myfileTop << x_vals[iMass] << "   " << ValueTop.at(5)  << "   " << ValueTop.at(5)*(SystTop.at(5)-1) << std::endl;
  if (iMass == 16) myfileTop << x_vals[iMass] << "   " << ValueTop.at(6)  << "   " << ValueTop.at(6)*(SystTop.at(6)-1) << std::endl;
  if (iMass == 17) myfileTop << x_vals[iMass] << "   " << ValueTop.at(10) << "   " << ValueTop.at(10)*(SystTop.at(10)-1) << std::endl;
  if (iMass == 18) myfileTop << x_vals[iMass] << "   " << ValueTop.at(11) << "   " << ValueTop.at(11)*(SystTop.at(11)-1) << std::endl;
  if (iMass == 19) myfileTop << x_vals[iMass] << "   " << ValueTop.at(12) << "   " << ValueTop.at(12)*(SystTop.at(12)-1) << std::endl;
  if (iMass == 20) myfileTop << x_vals[iMass] << "   " << ValueTop.at(13) << "   " << ValueTop.at(13)*(SystTop.at(13)-1) << std::endl;
  if (iMass == 21) myfileTop << x_vals[iMass] << "   " << ValueTop.at(14) << "   " << ValueTop.at(14)*(SystTop.at(14)-1) << std::endl;
  if (iMass == 22) myfileTop << x_vals[iMass] << "   " << ValueTop.at(15) << "   " << ValueTop.at(15)*(SystTop.at(15)-1) << std::endl;
  if (iMass == 23) myfileTop << x_vals[iMass] << "   " << ValueTop.at(16) << "   " << ValueTop.at(16)*(SystTop.at(16)-1) << std::endl;
  if (iMass == 24) myfileTop << x_vals[iMass] << "   " << ValueTop.at(17) << "   " << ValueTop.at(17)*(SystTop.at(17)-1) << std::endl;
  
  
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
  
  if (iMass == 0)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(0)  << "   " << ValueDY.at(0)*(SystDY.at(0)-1) << std::endl;
  if (iMass == 1)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(0)  << "   " << ValueDY.at(0)*(SystDY.at(0)-1) << std::endl;
  if (iMass == 2)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(0)  << "   " << ValueDY.at(0)*(SystDY.at(0)-1) << std::endl;
  if (iMass == 3)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(0)  << "   " << ValueDY.at(0)*(SystDY.at(0)-1) << std::endl;
  if (iMass == 4)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(0)  << "   " << ValueDY.at(0)*(SystDY.at(0)-1) << std::endl;
  if (iMass == 5)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(0)  << "   " << ValueDY.at(0)*(SystDY.at(0)-1) << std::endl;
  if (iMass == 6)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(1)  << "   " << ValueDY.at(1)*(SystDY.at(1)-1) << std::endl;
  if (iMass == 7)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(1)  << "   " << ValueDY.at(1)*(SystDY.at(1)-1) << std::endl;
  if (iMass == 8)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(1)  << "   " << ValueDY.at(1)*(SystDY.at(1)-1) << std::endl;
  if (iMass == 9)  myfileDY << x_vals[iMass] << "   " << ValueDY.at(2)  << "   " << ValueDY.at(2)*(SystDY.at(2)-1) << std::endl;
  if (iMass == 10) myfileDY << x_vals[iMass] << "   " << ValueDY.at(2)  << "   " << ValueDY.at(2)*(SystDY.at(2)-1) << std::endl;
  if (iMass == 11) myfileDY << x_vals[iMass] << "   " << ValueDY.at(3)  << "   " << ValueDY.at(3)*(SystDY.at(3)-1) << std::endl;
  if (iMass == 12) myfileDY << x_vals[iMass] << "   " << ValueDY.at(3)  << "   " << ValueDY.at(3)*(SystDY.at(3)-1) << std::endl;
  if (iMass == 13) myfileDY << x_vals[iMass] << "   " << ValueDY.at(3)  << "   " << ValueDY.at(3)*(SystDY.at(3)-1) << std::endl;
  if (iMass == 14) myfileDY << x_vals[iMass] << "   " << ValueDY.at(4)  << "   " << ValueDY.at(4)*(SystDY.at(4)-1) << std::endl;
  if (iMass == 15) myfileDY << x_vals[iMass] << "   " << ValueDY.at(5)  << "   " << ValueDY.at(5)*(SystDY.at(5)-1) << std::endl;
  if (iMass == 16) myfileDY << x_vals[iMass] << "   " << ValueDY.at(6)  << "   " << ValueDY.at(6)*(SystDY.at(6)-1) << std::endl;
  if (iMass == 17) myfileDY << x_vals[iMass] << "   " << ValueDY.at(10) << "   " << ValueDY.at(10)*(SystDY.at(10)-1) << std::endl;
  if (iMass == 18) myfileDY << x_vals[iMass] << "   " << ValueDY.at(11) << "   " << ValueDY.at(11)*(SystDY.at(11)-1) << std::endl;
  if (iMass == 19) myfileDY << x_vals[iMass] << "   " << ValueDY.at(12) << "   " << ValueDY.at(12)*(SystDY.at(12)-1) << std::endl;
  if (iMass == 20) myfileDY << x_vals[iMass] << "   " << ValueDY.at(13) << "   " << ValueDY.at(13)*(SystDY.at(13)-1) << std::endl;
  if (iMass == 21) myfileDY << x_vals[iMass] << "   " << ValueDY.at(14) << "   " << ValueDY.at(14)*(SystDY.at(14)-1) << std::endl;
  if (iMass == 22) myfileDY << x_vals[iMass] << "   " << ValueDY.at(15) << "   " << ValueDY.at(15)*(SystDY.at(15)-1) << std::endl;
  if (iMass == 23) myfileDY << x_vals[iMass] << "   " << ValueDY.at(16) << "   " << ValueDY.at(16)*(SystDY.at(16)-1) << std::endl;
  if (iMass == 24) myfileDY << x_vals[iMass] << "   " << ValueDY.at(17) << "   " << ValueDY.at(17)*(SystDY.at(17)-1) << std::endl;
  
 }
 myfileDY.close();
 
 
 
 
 std::cout << std::endl;
 std::cout << "more TopCard_2j.txt" << std::endl; 
 std::cout << "more DYCard_2j.txt" << std::endl;
 std::cout << std::endl;
 
//  std::cout << "mkdir  ~/Dropbox/Public/VBF/2011Dec05" << std::endl; 
//  std::cout << std::endl;
//  std::cout << "cp TopCard_2j.txt  ~/Dropbox/Public/VBF/2011Dec05" << std::endl; 
//  std::cout << "cp DYCard_2j.txt   ~/Dropbox/Public/VBF/2011Dec05" << std::endl;
 

 std::cout << "mkdir  ~/Dropbox/Public/VBF/2012Apr04-bis" << std::endl; 
 std::cout << std::endl;
 std::cout << "cp TopCard_2j.txt  ~/Dropbox/Public/VBF/2012Apr04-bis/" << std::endl; 
 std::cout << "cp DYCard_2j.txt   ~/Dropbox/Public/VBF/2012Apr04-bis/" << std::endl;
 
 std::cout << std::endl;
 std::cout << std::endl;
 
 gApplication->Terminate(0);
 
}


