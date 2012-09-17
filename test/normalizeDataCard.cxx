void normalizeDataCard(TString nameIn, TString nameOut, double xsectionScale, int numSample){
 
 std::ifstream file (nameIn.Data());
 std::string buffer;

 ofstream myfile;
 myfile.open (nameOut.Data());

std::string tempString;
double rate;

 while(!file.eof())
{
  getline(file,buffer);
  std::cout << "buffer = " << buffer << std::endl;
  std::stringstream line( buffer );      
   line >> tempString; 
//   std::cout << "tempString = " << tempString << std::endl;
   if (tempString.at(0) != 'r') {
     myfile << buffer;
   }
   else {
     myfile << tempString << "  ";
     for (int i=0; i<numSample; i++) {
       line >> rate;
       myfile << (rate * xsectionScale) << "  ";
     }
   }
   myfile << std::endl;
 }
  myfile.close(); 
 }
