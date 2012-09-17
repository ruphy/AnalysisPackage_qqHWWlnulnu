
##################
# Shape analysis #
##################

rm shapeAnalysisWorkflow.txt
touch shapeAnalysisWorkflow.txt


#  1) create rate (MC expectations)
echo "(1) create rate (MC expectations)" >> shapeAnalysisWorkflow.txt


# create the input for the datacard: rates for each process

./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H110.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H115.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H120.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H125.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H130.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H135.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H140.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H145.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H150.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H155.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H160.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H170.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H180.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H190.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H200.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H250.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H300.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H350.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H400.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H450.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H500.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H550.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H600.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H700.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H800.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H900.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF-Shape/H1000.cfg


./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H110.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H115.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H120.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H125.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H130.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H135.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H140.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H145.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H150.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H155.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H160.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H170.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H180.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H190.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H200.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H250.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H300.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H350.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H400.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H450.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H500.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H550.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H600.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H700.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H800.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H900.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF-Shape/H1000.cfg




# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# 2) create systematics table (see folder "Systematics")
echo "(2) create systematics table (see folder Systematics)" >> shapeAnalysisWorkflow.txt


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Shape analysis - electronResolution

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronResolution/Shape_Systematic_Modified_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronResolution/Shape_Systematic_Normal_of.cfg

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronResolution/Shape_Systematic_Modified_sf.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronResolution/Shape_Systematic_Normal_sf.cfg




# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Shape analysis - electronScale

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronScale/Shape_Systematic_Up_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronScale/Shape_Systematic_Down_of.cfg

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronScale/Shape_Systematic_Up_sf.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/electronScale/Shape_Systematic_Down_sf.cfg





# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Shape analysis - muonScale

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/muonScale/Shape_Systematic_Up_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/muonScale/Shape_Systematic_Down_of.cfg

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/muonScale/Shape_Systematic_Up_sf.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/muonScale/Shape_Systematic_Down_sf.cfg




# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Shape analysis - metResolution

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/metResolution/Shape_Systematic_Modified_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/metResolution/Shape_Systematic_Normal_of.cfg

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/metResolution/Shape_Systematic_Modified_sf.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/metResolution/Shape_Systematic_Normal_sf.cfg




# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Shape analysis - jetEnergyScale

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/jetEnergyScale/Shape_Systematic_Up_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/jetEnergyScale/Shape_Systematic_Down_of.cfg

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/jetEnergyScale/Shape_Systematic_Up_sf.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/jetEnergyScale/Shape_Systematic_Down_sf.cfg



# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Shape analysis - leptonEfficiency

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/leptonEfficiency/Shape_Systematic_Up_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/leptonEfficiency/Shape_Systematic_Down_of.cfg

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/leptonEfficiency/Shape_Systematic_Up_sf.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/leptonEfficiency/Shape_Systematic_Down_sf.cfg


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Shape analysis - PU

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/PU/Shape_Systematic_Up_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/PU/Shape_Systematic_Down_of.cfg

./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/PU/Shape_Systematic_Up_sf.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/PU/Shape_Systematic_Down_sf.cfg






# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# 3) create datadriven estimation (see folder Wjets, DY, ttbar, DYtautau)
echo "(3) create datadriven estimation (see folder Wjets, DY, ttbar, DYtautau)" >> shapeAnalysisWorkflow.txt


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~    Shape analysis  Wjets  ~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# create distributions
./bin/MCDATAComparisonPLOTTool_ManyWP.exe test/Latinos12/WJets/Shape_of.cfg
./bin/MCDATAComparisonPLOTTool_ManyWP.exe test/Latinos12/WJets/Shape_sf.cfg

# split the previous distributions in "up and down" MC statistics fluctuations for each bin
./bin/MCDATAShape_Systematic.exe test/Latinos12/WJets/UpDown_Shape_Systematic_of.cfg
./bin/MCDATAShape_Systematic.exe test/Latinos12/WJets/UpDown_Shape_Systematic_sf.cfg



# now the absolute value for shape analysis
./bin/MCDATACounter_Systematic.exe test/Latinos12/WJets/Systematic_shape_of.cfg

numWP=`cat dataCard.Syst.WJets.shape.of.txt | wc -l | bc`
numWP=`echo "($numWP-1)/2" | bc`
head -1  dataCard.Syst.WJets.shape.of.txt >  tmp.txt
tail -$numWP  dataCard.Syst.WJets.shape.of.txt >>  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-syst-shape-of.txt
numWP=`echo "$numWP+1" | bc`
head -$numWP  dataCard.Syst.WJets.shape.of.txt >  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-value-shape-of.txt
cat test/Latinos12/WJets/result-value-shape-of.txt
cat test/Latinos12/WJets/result-syst-shape-of.txt




./bin/MCDATACounter_Systematic.exe test/Latinos12/WJets/Systematic_shape_sf.cfg

numWP=`cat dataCard.Syst.WJets.shape.sf.txt | wc -l | bc`
numWP=`echo "($numWP-1)/2" | bc`
head -1  dataCard.Syst.WJets.shape.sf.txt >  tmp.txt
tail -$numWP  dataCard.Syst.WJets.shape.sf.txt >>  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-syst-shape-sf.txt
numWP=`echo "$numWP+1" | bc`
head -$numWP  dataCard.Syst.WJets.shape.sf.txt >  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-value-shape-sf.txt
cat test/Latinos12/WJets/result-value-shape-sf.txt
cat test/Latinos12/WJets/result-syst-shape-sf.txt






# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~    Shape analysis  DYee and DYmumu  ~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# create distributions (looser cut)
./bin/MCDATAComparisonPLOTTool_ManyWP.exe test/Latinos12/DYRinout/Shape_sf.cfg

# split the previous distributions in "up and down" MC statistics fluctuations for each bin
./bin/MCDATAShape_Systematic.exe test/Latinos12/DYRinout/UpDown_Shape_Systematic_sf.cfg


# now estimation of number of events
./bin/MCDATAComparisonPLOTTool_ManyWP.exe test/Latinos12/DYRinout/testMCDATAComparisonPLOTTool_DYRinout_AllHiggsMassPoints_shape.cfg


rm test/Latinos12/DYRinout/result-value-shape.txt
rm test/Latinos12/DYRinout/result-value-ee-shape.txt
rm test/Latinos12/DYRinout/result-value-mumu-shape.txt
rm test/Latinos12/DYRinout/result-syst-shape.txt
rm test/Latinos12/DYRinout/result-syst-ee-shape.txt
rm test/Latinos12/DYRinout/result-syst-mumu-shape.txt
rm test/Latinos12/DYRinout/result-syst-stat-shape.txt
rm test/Latinos12/DYRinout/result-syst-stat-ee-shape.txt
rm test/Latinos12/DYRinout/result-syst-stat-mumu-shape.txt
rm test/Latinos12/DYRinout/result-syst-stat-MC-shape.txt
rm test/Latinos12/DYRinout/result-syst-stat-MC-ee-shape.txt
rm test/Latinos12/DYRinout/result-syst-stat-MC-mumu-shape.txt
rm test/Latinos12/DYRinout/result-syst-method-shape.txt
rm test/Latinos12/DYRinout/result-syst-method-ee-shape.txt
rm test/Latinos12/DYRinout/result-syst-method-mumu-shape.txt
rm test/Latinos12/DYRinout/result-syst-method-MC-shape.txt
rm test/Latinos12/DYRinout/result-syst-method-MC-ee-shape.txt
rm test/Latinos12/DYRinout/result-syst-method-MC-mumu-shape.txt
rm test/Latinos12/DYRinout/result-SF-shape.txt
rm test/Latinos12/DYRinout/result-SF-ee-shape.txt
rm test/Latinos12/DYRinout/result-SF-mumu-shape.txt
rm test/Latinos12/DYRinout/result-SF-MC-shape.txt
rm test/Latinos12/DYRinout/result-SF-MC-ee-shape.txt
rm test/Latinos12/DYRinout/result-SF-MC-mumu-shape.txt
rm test/Latinos12/DYRinout/result-R-shape.txt

echo DY     > test/Latinos12/DYRinout/result-value-shape.txt
echo DYee   > test/Latinos12/DYRinout/result-value-ee-shape.txt
echo DYmumu > test/Latinos12/DYRinout/result-value-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-syst-shape.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-ee-shape.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-syst-stat-shape.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-stat-ee-shape.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-stat-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-syst-stat-MC-shape.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-stat-MC-ee-shape.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-stat-MC-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-syst-method-shape.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-method-ee-shape.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-method-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-syst-method-MC-shape.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-method-MC-ee-shape.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-method-MC-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-SF-shape.txt
echo DY     > test/Latinos12/DYRinout/result-SF-ee-shape.txt
echo DY     > test/Latinos12/DYRinout/result-SF-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-SF-MC-shape.txt
echo DY     > test/Latinos12/DYRinout/result-SF-MC-ee-shape.txt
echo DY     > test/Latinos12/DYRinout/result-SF-MC-mumu-shape.txt
echo DY     > test/Latinos12/DYRinout/result-R-shape.txt

for ((i=1; i<28; i++)) do  echo "r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\\\"out_DYRinout_Latinos_2jet_25May1900-ForResult-shape.root\\\",$i,28,\\"-shape\\"\)" ; done
for ((i=1; i<28; i++)) do  r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\"out_DYRinout_Latinos_2jet_25May1900-ForResult-shape.root\",$i,28,\"-shape\"\) ; done






#######################################
#######################################
#######################################
#######################################
############### achtung! ##############
#######################################
#######################################
#######################################
###
### estimation of scale factor @WW level 
### this value (for ee/mumu) has to be plugged in into the ttbar estimation
###
#######################################
#######################################


####################
#### @ WW level ####
for ((i=29; i<30; i++)) do  echo "r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\\\"out_DYRinout_Latinos_2jet_25May1900-ForResult-shape.root\\\",$i,28,\\"-shape\\"\)" ; done
for ((i=29; i<30; i++)) do  r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\"out_DYRinout_Latinos_2jet_25May1900-ForResult-shape.root\",$i,28,\"-shape\"\) ; done

for ((i=29; i<30; i++)) do  echo "r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\\\"out_DYRinout_Latinos_2jet_25May1900-ForResult-shape.root\\\",$i,28,\\"-shape-WW\\"\)" ; done
for ((i=29; i<30; i++)) do  r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\"out_DYRinout_Latinos_2jet_25May1900-ForResult-shape.root\",$i,28,\"-shape-WW\"\) ; done
##################################################
##################################################

more test/Latinos12/DYRinout/result-SF-mumu-shape-WW.txt
more test/Latinos12/DYRinout/result-SF-ee-shape-WW.txt

more test/Latinos12/DYRinout/result-SF-MC-mumu-shape-WW.txt
more test/Latinos12/DYRinout/result-SF-MC-ee-shape-WW.txt









# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~    Shape analysis  ttbar  ~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


ls -r test/Latinos12/ttbar/datacard-shape/H*.cfg | awk '{printf "./bin/MCDATAComparisonPLOTTool.exe "$1"\n"}' | /bin/sh



rm test/Latinos12/ttbar/result-SF-shape-all.txt
rm test/Latinos12/ttbar/result-value-shape-all.txt
rm test/Latinos12/ttbar/result-syst-shape-all.txt
rm test/Latinos12/ttbar/result-syst-stat-shape-all.txt
rm test/Latinos12/ttbar/result-syst-method-shape-all.txt
rm test/Latinos12/ttbar/result-syst-CR-stat-shape-all.txt
rm test/Latinos12/ttbar/result-syst-CJ-FJ-shape-all.txt
rm test/Latinos12/ttbar/result-syst-MCSub-shape-all.txt
echo top > test/Latinos12/ttbar/result-SF-shape-all.txt
echo top > test/Latinos12/ttbar/result-value-shape-all.txt
echo top > test/Latinos12/ttbar/result-syst-shape-all.txt
echo top > test/Latinos12/ttbar/result-syst-stat-shape-all.txt
echo top > test/Latinos12/ttbar/result-syst-method-shape-all.txt
echo top > test/Latinos12/ttbar/result-syst-CR-stat-shape-all.txt
echo top > test/Latinos12/ttbar/result-syst-CJ-FJ-shape-all.txt
echo top > test/Latinos12/ttbar/result-syst-MCSub-shape-all.txt

rm test/Latinos12/ttbar/result-SF-shape-sf.txt
rm test/Latinos12/ttbar/result-value-shape-sf.txt
rm test/Latinos12/ttbar/result-syst-shape-sf.txt
rm test/Latinos12/ttbar/result-syst-stat-shape-sf.txt
rm test/Latinos12/ttbar/result-syst-method-shape-sf.txt
rm test/Latinos12/ttbar/result-syst-CR-stat-shape-sf.txt
rm test/Latinos12/ttbar/result-syst-CJ-FJ-shape-sf.txt
rm test/Latinos12/ttbar/result-syst-MCSub-shape-sf.txt
echo top > test/Latinos12/ttbar/result-SF-shape-sf.txt
echo top > test/Latinos12/ttbar/result-value-shape-sf.txt
echo top > test/Latinos12/ttbar/result-syst-shape-sf.txt
echo top > test/Latinos12/ttbar/result-syst-stat-shape-sf.txt
echo top > test/Latinos12/ttbar/result-syst-method-shape-sf.txt
echo top > test/Latinos12/ttbar/result-syst-CR-stat-shape-sf.txt
echo top > test/Latinos12/ttbar/result-syst-CJ-FJ-shape-sf.txt
echo top > test/Latinos12/ttbar/result-syst-MCSub-shape-sf.txt

rm test/Latinos12/ttbar/result-SF-shape-of.txt
rm test/Latinos12/ttbar/result-value-shape-of.txt
rm test/Latinos12/ttbar/result-syst-shape-of.txt
rm test/Latinos12/ttbar/result-syst-stat-shape-of.txt
rm test/Latinos12/ttbar/result-syst-method-shape-of.txt
rm test/Latinos12/ttbar/result-syst-CR-stat-shape-of.txt
rm test/Latinos12/ttbar/result-syst-CJ-FJ-shape-of.txt
rm test/Latinos12/ttbar/result-syst-MCSub-shape-of.txt
echo top > test/Latinos12/ttbar/result-SF-shape-of.txt
echo top > test/Latinos12/ttbar/result-value-shape-of.txt
echo top > test/Latinos12/ttbar/result-syst-shape-of.txt
echo top > test/Latinos12/ttbar/result-syst-stat-shape-of.txt
echo top > test/Latinos12/ttbar/result-syst-method-shape-of.txt
echo top > test/Latinos12/ttbar/result-syst-CR-stat-shape-of.txt
echo top > test/Latinos12/ttbar/result-syst-CJ-FJ-shape-of.txt
echo top > test/Latinos12/ttbar/result-syst-MCSub-shape-of.txt



for ((i=0; i<27; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_shape_H-WP$i.root\",0,0,$i,\"-shape-all\"\) ;   done
for ((i=0; i<27; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_shape_H-WP$i.root\",0,1,$i,\"-shape-sf\"\) ;   done
for ((i=0; i<27; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_shape_H-WP$i.root\",0,2,$i,\"-shape-of\"\) ;   done


rm test/Latinos12/ttbar/result-*shape*-WW.txt

for ((i=27; i<28; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_shape_H-WP$i.root\",0,0,$i,\"-shape-all-WW\"\) ;   done
for ((i=27; i<28; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_shape_H-WP$i.root\",0,1,$i,\"-shape-sf-WW\"\) ;   done
for ((i=27; i<28; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_shape_H-WP$i.root\",0,2,$i,\"-shape-of-WW\"\) ;   done








# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ~~~~    Shape analysis  DYtautau  ~~~~
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#########################################
# specific datadriven code not needed -> use embedded sample and get shape and normalization automatically (see step 5)
#########################################




# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# 4)  input for datacards
echo "(4)  input for datacards" >> shapeAnalysisWorkflow.txt
# 
# prepare data driven #
r00t test/createForMatt2012Analysis.cxx\(\"-shape\"\)







# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# 5)  input for shapes
echo "(5)  input for shapes" >> shapeAnalysisWorkflow.txt
#

# create distributions for signal, background and DATA
# ./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/MC_statistics/Shape_Systematic.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/MC_statistics/Shape_Systematic_of.cfg
./bin/MCDATAComparisonPLOTTool_ManySamples.exe test/Latinos12/Systematics/MC_statistics/Shape_Systematic_sf.cfg

# split the previous distributions in "up and down" MC statistics fluctuations for each bin
# ./bin/MCDATAShape_Systematic.exe test/Latinos12/Systematics/MC_statistics/UpDown_Shape_Systematic.cfg
./bin/MCDATAShape_Systematic.exe test/Latinos12/Systematics/MC_statistics/UpDown_Shape_Systematic_of.cfg
./bin/MCDATAShape_Systematic.exe test/Latinos12/Systematics/MC_statistics/UpDown_Shape_Systematic_sf.cfg


# create the root file used as input for the shape analysis
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_110.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_115.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_120.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_125.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_130.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_135.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_140.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_145.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_150.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_155.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_160.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_170.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_180.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_190.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_200.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_250.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_300.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_350.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_400.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_450.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_500.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_550.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_600.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_700.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_800.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_900.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/OF-DC/BuildDataCardInput_1000.cfg


./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_110.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_115.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_120.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_125.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_130.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_135.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_140.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_145.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_150.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_155.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_160.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_170.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_180.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_190.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_200.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_250.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_300.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_350.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_400.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_450.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_500.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_550.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_600.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_700.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_800.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_900.cfg
./bin/BuildDataCardInputShape.exe test/Latinos12/BuildDataCard/SF-DC/BuildDataCardInput_1000.cfg


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# 6)  create datacards
#
echo "(6)  create datacards" >> shapeAnalysisWorkflow.txt


# build datacard taking information about rates, systematics, datadriven (it modifies also the root file with distributions in case of gmN data driven)
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Shape/BuildDataCard_1000.cfg


./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Shape/BuildDataCard_1000.cfg







################################
# injection test mH=125,  1x SM


# build datacard taking information about rates, systematics, datadriven (it modifies also the root file with distributions in case of gmN data driven)
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection-Shape/BuildDataCard_1000.cfg


./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection-Shape/BuildDataCard_1000.cfg





### now "combine" and "Brazilian plot"

# where experimentsl systematics are stored
# ls -alrth output_Latinos_tree_2012_Systematics



#### bye bye ####
#################


