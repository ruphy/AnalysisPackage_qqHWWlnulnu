// r00t test/ExtractPlot.cxx\(\"out_test_Latinos_26July2011_1100.root\",\"All/Norm/0_2_Norm_Canvas\"\)

void ExtractPlot(TString nameRootFile, TString nameCanvas){
 
 TFile* fileDATA = new TFile(nameRootFile,"READ");
 
 TCanvas* Canvas = (TCanvas*) fileDATA->Get(nameCanvas);
 
 Canvas->Draw();

 
 TCanvas* myCC = new TCanvas("myCC","myCC",800,800);
 TList* list = (TList*) Canvas->GetListOfPrimitives();
 bool firstTime = true;
 TObject* obj;
 TIter next(Canvas->GetListOfPrimitives());
 while ((obj = next.Next())){
//   std::cout << "obj->ClassName() = " << obj->ClassName() << std::endl;
  std::string name(obj->ClassName());
  if (name == "TH1F") {
//    std::cout << " ciao!" << std::endl;
   if (firstTime) {
    obj->Draw();
    firstTime = false;
   }
   else {
    obj->Draw("same");
   }
  }
 }
  
 
//  list->Print();
 
//  cc = (TCanvas*) fileIn->Get("All/Var/10_7_Canvas");
//  nameHisto = Form ("%s_10_7_Tot_temp",nameDATA.Data());
//  h = (TH1F*) cc->GetPrimitive(nameHisto);
//  hMC = (TH1F*) cc->GetPrimitive("W_10_7_Tot_temp");
//  cJoint->cd();
//  h->Draw();
//  hMC->Draw("HISTsame");
//  cJoint->SetGrid();
//  TLegend* leg = cJoint->BuildLegend(0.8,0.55,0.98,0.75);
//  leg->SetFillColor(kWhite);
//  cJoint->SetGrid(); 
 
 
}


