
double weight_electron(double pT1, double eta1, int flavour1, double pT2, double eta2, int flavour2){
 double weight = 1;
 double weight1 = 1;
 double weight2 = 1;
 if (flavour1 == 11) {
  if (pT1>=10 && pT1<15  && fabs(eta1)>=0 && fabs(eta1)<1) weight1 = 0.910407;
  if (pT1>=15 && pT1<20  && fabs(eta1)>=0 && fabs(eta1)<1) weight1 = 0.885822;
  if (pT1>=20 && pT1<25  && fabs(eta1)>=0 && fabs(eta1)<1) weight1 = 0.916496;
  if (pT1>=25 && pT1<50  && fabs(eta1)>=0 && fabs(eta1)<1) weight1 = 0.978818;
  if (pT1>=50 && pT1<200 && fabs(eta1)>=0 && fabs(eta1)<1) weight1 = 0.972301;

  if (pT1>=10 && pT1<15  && fabs(eta1)>=1.0 && fabs(eta1)<1.4442) weight1 = 1.01616;
  if (pT1>=15 && pT1<20  && fabs(eta1)>=1.0 && fabs(eta1)<1.4442) weight1 = 0.964906;
  if (pT1>=20 && pT1<25  && fabs(eta1)>=1.0 && fabs(eta1)<1.4442) weight1 = 0.903574;
  if (pT1>=25 && pT1<50  && fabs(eta1)>=1.0 && fabs(eta1)<1.4442) weight1 = 0.982828;
  if (pT1>=50 && pT1<200 && fabs(eta1)>=1.0 && fabs(eta1)<1.4442) weight1 = 0.976071;
  
  if (pT1>=10 && pT1<15  && fabs(eta1)>=1.4442 && fabs(eta1)<1.566) weight1 = 0.40595;
  if (pT1>=15 && pT1<20  && fabs(eta1)>=1.4442 && fabs(eta1)<1.566) weight1 = 1.03679;
  if (pT1>=20 && pT1<25  && fabs(eta1)>=1.4442 && fabs(eta1)<1.566) weight1 = 1.09654;
  if (pT1>=25 && pT1<50  && fabs(eta1)>=1.4442 && fabs(eta1)<1.566) weight1 = 1.06289;
  if (pT1>=50 && pT1<200 && fabs(eta1)>=1.4442 && fabs(eta1)<1.566) weight1 = 1.03299;
  
  if (pT1>=10 && pT1<15  && fabs(eta1)>=1.566 && fabs(eta1)<2.0) weight1 = 1.17042;
  if (pT1>=15 && pT1<20  && fabs(eta1)>=1.566 && fabs(eta1)<2.0) weight1 = 1.05732;
  if (pT1>=20 && pT1<25  && fabs(eta1)>=1.566 && fabs(eta1)<2.0) weight1 = 0.9605;
  if (pT1>=25 && pT1<50  && fabs(eta1)>=1.566 && fabs(eta1)<2.0) weight1 = 1.01426;
  if (pT1>=50 && pT1<200 && fabs(eta1)>=1.566 && fabs(eta1)<2.0) weight1 = 1.00178;

  if (pT1>=10 && pT1<15  && fabs(eta1)>=2.0 && fabs(eta1)<2.5) weight1 = 0.848856;
  if (pT1>=15 && pT1<20  && fabs(eta1)>=2.0 && fabs(eta1)<2.5) weight1 = 1.02422;
  if (pT1>=20 && pT1<25  && fabs(eta1)>=2.0 && fabs(eta1)<2.5) weight1 = 0.956629;
  if (pT1>=25 && pT1<50  && fabs(eta1)>=2.0 && fabs(eta1)<2.5) weight1 = 0.997448;
  if (pT1>=50 && pT1<200 && fabs(eta1)>=2.0 && fabs(eta1)<2.5) weight1 = 1.01248;
 }
 
 if (flavour2 == 11) {
  if (pT2>=10 && pT2<15  && fabs(eta2)>=0 && fabs(eta2)<1) weight2 = 0.910407;
  if (pT2>=15 && pT2<20  && fabs(eta2)>=0 && fabs(eta2)<1) weight2 = 0.885822;
  if (pT2>=20 && pT2<25  && fabs(eta2)>=0 && fabs(eta2)<1) weight2 = 0.916496;
  if (pT2>=25 && pT2<50  && fabs(eta2)>=0 && fabs(eta2)<1) weight2 = 0.978818;
  if (pT2>=50 && pT2<200 && fabs(eta2)>=0 && fabs(eta2)<1) weight2 = 0.972301;
  
  if (pT2>=10 && pT2<15  && fabs(eta2)>=1.0 && fabs(eta2)<1.4442) weight2 = 1.01616;
  if (pT2>=15 && pT2<20  && fabs(eta2)>=1.0 && fabs(eta2)<1.4442) weight2 = 0.964906;
  if (pT2>=20 && pT2<25  && fabs(eta2)>=1.0 && fabs(eta2)<1.4442) weight2 = 0.903574;
  if (pT2>=25 && pT2<50  && fabs(eta2)>=1.0 && fabs(eta2)<1.4442) weight2 = 0.982828;
  if (pT2>=50 && pT2<200 && fabs(eta2)>=1.0 && fabs(eta2)<1.4442) weight2 = 0.976071;
  
  if (pT2>=10 && pT2<15  && fabs(eta2)>=1.4442 && fabs(eta2)<1.566) weight2 = 0.40595;
  if (pT2>=15 && pT2<20  && fabs(eta2)>=1.4442 && fabs(eta2)<1.566) weight2 = 1.03679;
  if (pT2>=20 && pT2<25  && fabs(eta2)>=1.4442 && fabs(eta2)<1.566) weight2 = 1.09654;
  if (pT2>=25 && pT2<50  && fabs(eta2)>=1.4442 && fabs(eta2)<1.566) weight2 = 1.06289;
  if (pT2>=50 && pT2<200 && fabs(eta2)>=1.4442 && fabs(eta2)<1.566) weight2 = 1.03299;
  
  if (pT2>=10 && pT2<15  && fabs(eta2)>=1.566 && fabs(eta2)<2.0) weight2 = 1.17042;
  if (pT2>=15 && pT2<20  && fabs(eta2)>=1.566 && fabs(eta2)<2.0) weight2 = 1.05732;
  if (pT2>=20 && pT2<25  && fabs(eta2)>=1.566 && fabs(eta2)<2.0) weight2 = 0.9605;
  if (pT2>=25 && pT2<50  && fabs(eta2)>=1.566 && fabs(eta2)<2.0) weight2 = 1.01426;
  if (pT2>=50 && pT2<200 && fabs(eta2)>=1.566 && fabs(eta2)<2.0) weight2 = 1.00178;
  
  if (pT2>=10 && pT2<15  && fabs(eta2)>=2.0 && fabs(eta2)<2.5) weight2 = 0.848856;
  if (pT2>=15 && pT2<20  && fabs(eta2)>=2.0 && fabs(eta2)<2.5) weight2 = 1.02422;
  if (pT2>=20 && pT2<25  && fabs(eta2)>=2.0 && fabs(eta2)<2.5) weight2 = 0.956629;
  if (pT2>=25 && pT2<50  && fabs(eta2)>=2.0 && fabs(eta2)<2.5) weight2 = 0.997448;
  if (pT2>=50 && pT2<200 && fabs(eta2)>=2.0 && fabs(eta2)<2.5) weight2 = 1.01248;
 }
 
 weight = weight * weight1 * weight2;
 
 return weight;
}



