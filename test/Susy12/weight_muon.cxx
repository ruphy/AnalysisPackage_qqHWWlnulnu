
double weight_muon(double pT1, double eta1, int flavour1, double pT2, double eta2, int flavour2){
 double weight = 1;
 double weight1 = 1;
 double weight2 = 1;
 
 if (flavour1 == 13) {
  if (pT1>=10 && pT1<15  && fabs(eta1)>=0 && fabs(eta1)<1.479) weight1 = 0.962251;
  if (pT1>=15 && pT1<20  && fabs(eta1)>=0 && fabs(eta1)<1.479) weight1 = 0.984605;
  if (pT1>=20 && pT1<50  && fabs(eta1)>=0 && fabs(eta1)<1.479) weight1 = 0.992932;
  if (pT1>=50 && pT1<150 && fabs(eta1)>=0 && fabs(eta1)<1.479) weight1 = 0.993534;

  if (pT1>=10 && pT1<15  && fabs(eta1)>=1.479 && fabs(eta1)<2.4) weight1 = 0.947285;
  if (pT1>=15 && pT1<20  && fabs(eta1)>=1.479 && fabs(eta1)<2.4) weight1 = 0.941377;
  if (pT1>=20 && pT1<50  && fabs(eta1)>=1.479 && fabs(eta1)<2.4) weight1 = 0.976096;
  if (pT1>=50 && pT1<150 && fabs(eta1)>=1.479 && fabs(eta1)<2.4) weight1 = 0.980654;
 }
 
 if (flavour2 == 13) {
  if (pT2>=10 && pT2<15  && fabs(eta2)>=0 && fabs(eta2)<1.479) weight1 = 0.962251;
  if (pT2>=15 && pT2<20  && fabs(eta2)>=0 && fabs(eta2)<1.479) weight1 = 0.984605;
  if (pT2>=20 && pT2<50  && fabs(eta2)>=0 && fabs(eta2)<1.479) weight1 = 0.992932;
  if (pT2>=50 && pT2<150 && fabs(eta2)>=0 && fabs(eta2)<1.479) weight1 = 0.993534;
  
  if (pT2>=10 && pT2<15  && fabs(eta2)>=1.479 && fabs(eta2)<2.4) weight1 = 0.947285;
  if (pT2>=15 && pT2<20  && fabs(eta2)>=1.479 && fabs(eta2)<2.4) weight1 = 0.941377;
  if (pT2>=20 && pT2<50  && fabs(eta2)>=1.479 && fabs(eta2)<2.4) weight1 = 0.976096;
  if (pT2>=50 && pT2<150 && fabs(eta2)>=1.479 && fabs(eta2)<2.4) weight1 = 0.980654;
 }
 
 weight = weight * weight1 * weight2;
 
 return weight;
}



