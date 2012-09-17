
######################
# Cut&Count analysis #
######################

# *********************************
#  de-comment if not already performed
#
# *********************************
#
# rm -r output_Latinos_tree_2012_012jet
# mkdir output_Latinos_tree_2012_012jet
# ls output_Latinos_tree_2012/ |  awk '{print "./bin/FilterCut.exe output_Latinos_tree_2012/"$1" output_Latinos_tree_2012_012jet/"$1" 012Jet2012"}' 
# ls output_Latinos_tree_2012/ |  awk '{print "./bin/FilterCut.exe output_Latinos_tree_2012/"$1" output_Latinos_tree_2012_012jet/"$1" 012Jet2012"}'   &> skim2j.sh
# chmod +x skim2j.sh
# ./skim2j.sh
# 
# *********************************



#  1) create rate (MC expectations)

# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H110.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H115.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H120.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H125.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H130.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H135.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H140.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H145.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H150.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H155.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H160.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H170.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H180.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H190.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H200.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H250.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H300.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H350.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H400.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H450.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H500.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H550.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H600.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H700.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H800.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H900.cfg
# ./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/H1000.cfg


# OF #

./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H110.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H115.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H120.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H125.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H130.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H135.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H140.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H145.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H150.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H155.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H160.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H170.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H180.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H190.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H200.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H250.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H300.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H350.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H400.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H450.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H500.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H550.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H600.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H700.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H800.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H900.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/OF/H1000.cfg



# SF #

./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H110.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H115.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H120.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H125.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H130.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H135.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H140.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H145.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H150.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H155.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H160.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H170.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H180.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H190.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H200.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H250.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H300.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H350.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H400.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H450.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H500.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H550.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H600.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H700.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H800.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H900.cfg
./bin/MCDATACounter.exe test/Latinos12/HiggsMasses/SF/H1000.cfg


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# 2) create systematics table (see folder "Systematics")



# Uncertanty due to Electron Resolution
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronResolution/Systematic_Modified.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronResolution/Systematic_Normal.cfg
# 
# r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.electronResolution.Normal.110.txt\",\"dataCard.Syst.electronResolution.Modified.110.txt\",\"test/Latinos12/Systematics/electronResolution/result.txt\"\)



./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronResolution/Systematic_Modified_of.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronResolution/Systematic_Normal_of.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.electronResolution.Normal.OF.110.txt\",\"dataCard.Syst.electronResolution.Modified.OF.110.txt\",\"test/Latinos12/Systematics/electronResolution/result_of.txt\"\)



./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronResolution/Systematic_Modified_sf.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronResolution/Systematic_Normal_sf.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.electronResolution.Normal.SF.110.txt\",\"dataCard.Syst.electronResolution.Modified.SF.110.txt\",\"test/Latinos12/Systematics/electronResolution/result_sf.txt\"\)






# Uncertanty due to Electron Scale
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronScale/Systematic_Minus.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronScale/Systematic_Plus.cfg
# 
# r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.electronScale.Plus.110.txt\",\"dataCard.Syst.electronScale.Minus.110.txt\",\"test/Latinos12/Systematics/electronScale/result.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronScale/Systematic_Minus_of.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronScale/Systematic_Plus_of.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.electronScale.Plus.OF.110.txt\",\"dataCard.Syst.electronScale.Minus.OF.110.txt\",\"test/Latinos12/Systematics/electronScale/result_of.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronScale/Systematic_Minus_sf.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/electronScale/Systematic_Plus_sf.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.electronScale.Plus.SF.110.txt\",\"dataCard.Syst.electronScale.Minus.SF.110.txt\",\"test/Latinos12/Systematics/electronScale/result_sf.txt\"\)






# Uncertanty due to Muon Scale
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/muonScale/Systematic_Minus.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/muonScale/Systematic_Plus.cfg
# 
# r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.muonScale.Plus.110.txt\",\"dataCard.Syst.muonScale.Minus.110.txt\",\"test/Latinos12/Systematics/muonScale/result.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/muonScale/Systematic_Minus_of.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/muonScale/Systematic_Plus_of.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.muonScale.Plus.OF.110.txt\",\"dataCard.Syst.muonScale.Minus.OF.110.txt\",\"test/Latinos12/Systematics/muonScale/result_of.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/muonScale/Systematic_Minus_sf.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/muonScale/Systematic_Plus_sf.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.muonScale.Plus.SF.110.txt\",\"dataCard.Syst.muonScale.Minus.SF.110.txt\",\"test/Latinos12/Systematics/muonScale/result_sf.txt\"\)




# Uncertanty due to met Resolution
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/metResolution/Systematic_Modified.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/metResolution/Systematic_Normal.cfg
# 
# r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.metResolution.Normal.110.txt\",\"dataCard.Syst.metResolution.Modified.110.txt\",\"test/Latinos12/Systematics/metResolution/result.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/metResolution/Systematic_Modified_of.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/metResolution/Systematic_Normal_of.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.metResolution.Normal.OF.110.txt\",\"dataCard.Syst.metResolution.Modified.OF.110.txt\",\"test/Latinos12/Systematics/metResolution/result_of.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/metResolution/Systematic_Modified_sf.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/metResolution/Systematic_Normal_sf.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.metResolution.Normal.SF.110.txt\",\"dataCard.Syst.metResolution.Modified.SF.110.txt\",\"test/Latinos12/Systematics/metResolution/result_sf.txt\"\)





# Uncertanty due to Jet Energy Scale
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/jetEnergyScale/Systematic_Minus.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/jetEnergyScale/Systematic_Plus.cfg
# 
# r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.jetEnergyScale.Plus.110.txt\",\"dataCard.Syst.jetEnergyScale.Minus.110.txt\",\"test/Latinos12/Systematics/jetEnergyScale/result.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/jetEnergyScale/Systematic_Minus_of.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/jetEnergyScale/Systematic_Plus_of.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.jetEnergyScale.Plus.OF.110.txt\",\"dataCard.Syst.jetEnergyScale.Minus.OF.110.txt\",\"test/Latinos12/Systematics/jetEnergyScale/result_of.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/jetEnergyScale/Systematic_Minus_sf.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/jetEnergyScale/Systematic_Plus_sf.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.jetEnergyScale.Plus.SF.110.txt\",\"dataCard.Syst.jetEnergyScale.Minus.SF.110.txt\",\"test/Latinos12/Systematics/jetEnergyScale/result_sf.txt\"\)






# Uncertanty due to Lepton efficiency
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/leptonEfficiency/Systematic_Minus.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/leptonEfficiency/Systematic_Plus.cfg
# r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.leptonEfficiency.Plus.110.txt\",\"dataCard.Syst.leptonEfficiency.Minus.110.txt\",\"test/Latinos12/Systematics/leptonEfficiency/result.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/leptonEfficiency/Systematic_Minus_of.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/leptonEfficiency/Systematic_Plus_of.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.leptonEfficiency.Plus.OF.110.txt\",\"dataCard.Syst.leptonEfficiency.Minus.OF.110.txt\",\"test/Latinos12/Systematics/leptonEfficiency/result_of.txt\"\)


./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/leptonEfficiency/Systematic_Minus_sf.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/leptonEfficiency/Systematic_Plus_sf.cfg

r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.leptonEfficiency.Plus.SF.110.txt\",\"dataCard.Syst.leptonEfficiency.Minus.SF.110.txt\",\"test/Latinos12/Systematics/leptonEfficiency/result_sf.txt\"\)




# Uncertanty due to PU rescaling
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# 
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/PU/Systematic_wPU.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/PU/Systematic_wPUup.cfg
# ./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/PU/Systematic_wPUdown.cfg
# r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.PUdown.110.txt\",\"dataCard.Syst.PUup.110.txt\",\"test/Latinos12/Systematics/PU/result.txt\"\)

./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/PU/Systematic_wPUup_OF.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/PU/Systematic_wPUdown_OF.cfg
r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.PUdown.110.OF.txt\",\"dataCard.Syst.PUup.110.OF.txt\",\"test/Latinos12/Systematics/PU/result-of.txt\"\)

./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/PU/Systematic_wPUup_SF.cfg
./bin/MCDATACounter_Systematic.exe test/Latinos12/Systematics/PU/Systematic_wPUdown_SF.cfg
r00t test/Latinos12/Systematics/Diff.cxx\(\"dataCard.Syst.PUdown.110.SF.txt\",\"dataCard.Syst.PUup.110.SF.txt\",\"test/Latinos12/Systematics/PU/result-sf.txt\"\)







# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# 3) create datadriven estimation (see folder "###", DY, ttbar, DYtautau)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# DYtautau already embedded
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

./bin/MCDATACounter_Systematic.exe test/Latinos12/DYtautau/Systematic.cfg

numWP=`cat dataCard.Syst.Dytautau.110.txt | wc -l | bc`
numWP=`echo "($numWP-1)/2" | bc`
head -1  dataCard.Syst.Dytautau.110.txt >  tmp.txt
tail -$numWP  dataCard.Syst.Dytautau.110.txt >>  tmp.txt
mv tmp.txt test/Latinos12/DYtautau/result-syst.txt
numWP=`echo "$numWP+1" | bc`
head -$numWP  dataCard.Syst.Dytautau.110.txt >  tmp.txt
mv tmp.txt test/Latinos12/DYtautau/result-value.txt
cat test/Latinos12/DYtautau/result-value.txt
cat test/Latinos12/DYtautau/result-syst.txt




# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# DY ee/mumu Rinout method
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


./bin/MCDATAComparisonPLOTTool.exe test/Latinos12/DYRinout/testMCDATAComparisonPLOTTool_DYRinout_AllHiggsMassPoints.cfg


rm test/Latinos12/DYRinout/result-value.txt
rm test/Latinos12/DYRinout/result-value-ee.txt
rm test/Latinos12/DYRinout/result-value-mumu.txt
rm test/Latinos12/DYRinout/result-syst.txt
rm test/Latinos12/DYRinout/result-syst-ee.txt
rm test/Latinos12/DYRinout/result-syst-mumu.txt
rm test/Latinos12/DYRinout/result-syst-stat.txt
rm test/Latinos12/DYRinout/result-syst-stat-ee.txt
rm test/Latinos12/DYRinout/result-syst-stat-mumu.txt
rm test/Latinos12/DYRinout/result-syst-stat-MC.txt
rm test/Latinos12/DYRinout/result-syst-stat-MC-ee.txt
rm test/Latinos12/DYRinout/result-syst-stat-MC-mumu.txt
rm test/Latinos12/DYRinout/result-syst-method.txt
rm test/Latinos12/DYRinout/result-syst-method-ee.txt
rm test/Latinos12/DYRinout/result-syst-method-mumu.txt
rm test/Latinos12/DYRinout/result-syst-method-MC.txt
rm test/Latinos12/DYRinout/result-syst-method-MC-ee.txt
rm test/Latinos12/DYRinout/result-syst-method-MC-mumu.txt
rm test/Latinos12/DYRinout/result-SF.txt
rm test/Latinos12/DYRinout/result-SF-ee.txt
rm test/Latinos12/DYRinout/result-SF-mumu.txt
rm test/Latinos12/DYRinout/result-SF-MC.txt
rm test/Latinos12/DYRinout/result-SF-MC-ee.txt
rm test/Latinos12/DYRinout/result-SF-MC-mumu.txt
rm test/Latinos12/DYRinout/result-R.txt

echo DY     > test/Latinos12/DYRinout/result-value.txt
echo DYee   > test/Latinos12/DYRinout/result-value-ee.txt
echo DYmumu > test/Latinos12/DYRinout/result-value-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-syst.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-ee.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-syst-stat.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-stat-ee.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-stat-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-syst-stat-MC.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-stat-MC-ee.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-stat-MC-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-syst-method.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-method-ee.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-method-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-syst-method-MC.txt
echo DYee   > test/Latinos12/DYRinout/result-syst-method-MC-ee.txt
echo DYmumu > test/Latinos12/DYRinout/result-syst-method-MC-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-SF.txt
echo DY     > test/Latinos12/DYRinout/result-SF-ee.txt
echo DY     > test/Latinos12/DYRinout/result-SF-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-SF-MC.txt
echo DY     > test/Latinos12/DYRinout/result-SF-MC-ee.txt
echo DY     > test/Latinos12/DYRinout/result-SF-MC-mumu.txt
echo DY     > test/Latinos12/DYRinout/result-R.txt

for ((i=1; i<28; i++)) do  echo "r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\\\"out_DYRinout_Latinos_2jet_25May1900-ForResult.root\\\",$i,28\)" ; done
for ((i=1; i<28; i++)) do  r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\"out_DYRinout_Latinos_2jet_25May1900-ForResult.root\",$i,28\) ; done

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


cat result-value.txt
cat result-value-ee.txt
cat result-value-mumu.txt
rm result-syst.txt
rm result-syst-ee.txt
rm result-syst-mumu.txt
cat result-syst-stat.txt
cat result-syst-stat-ee.txt
cat result-syst-stat-mumu.txt
rm result-syst-stat-MC.txt
rm result-syst-stat-MC-ee.txt
rm result-syst-stat-MC-mumu.txt
cat result-syst-method.txt
cat result-syst-method-ee.txt
cat result-syst-method-mumu.txt
rm result-syst-method-MC.txt
rm result-syst-method-MC-ee.txt
rm result-syst-method-MC-mumu.txt
rm result-SF.txt
rm result-SF-ee.txt
rm result-SF-mumu.txt
rm result-SF-MC.txt
rm result-SF-MC-ee.txt
rm result-SF-MC-mumu.txt
rm result-R.txt




####################
#### @ WW level ####
for ((i=29; i<30; i++)) do  echo "r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\\\"out_DYRinout_Latinos_2jet_25May1900-ForResult.root\\\",$i,28\)" ; done
for ((i=29; i<30; i++)) do  r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\"out_DYRinout_Latinos_2jet_25May1900-ForResult.root\",$i,28\) ; done

for ((i=29; i<30; i++)) do  echo "r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\\\"out_DYRinout_Latinos_2jet_25May1900-ForResult.root\\\",$i,28\)" ; done
for ((i=29; i<30; i++)) do  r00t test/Latinos12/DYRinout/GetDY-Result-forDataCard.cxx\(\"out_DYRinout_Latinos_2jet_25May1900-ForResult.root\",$i,28,\"-WW\"\) ; done
##################################################
##################################################

more test/Latinos12/DYRinout/result-SF-mumu-WW.txt
more test/Latinos12/DYRinout/result-SF-ee-WW.txt

more test/Latinos12/DYRinout/result-SF-MC-mumu-WW.txt
more test/Latinos12/DYRinout/result-SF-MC-ee-WW.txt





#######################################
#######################################
############ stop here ################
#######################################
#######################################
#######################################



# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ttbar (SF and OF)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


ls -r test/Latinos12/ttbar/datacard/H*.cfg | awk '{printf "./bin/MCDATAComparisonPLOTTool.exe "$1"\n"}' | /bin/sh

## //
## //   input => root file input
## //   iVar =>  binning-definition and CF=0, FJ=1, name of the variable!
## //   PlusCut => 0=CJ all, 1=CJ sameflav, 2=CJ !sameflav  :: bunch of 6 cuts
## //   iWP => output name  "test/Latinos12/ttbar/result-forNote-%d%s.txt",iWP,suffix.Data()
## //   suffix = "", "-sf", "-of" (sameflav or opposite flav)
## //
## //    int GetTop_Result_forDataCard(TString input, int iVar = 0, int PlusCut = 0, int iWP = 0, TString suffix = "") {
## //


rm test/Latinos12/ttbar/result-SF.txt
rm test/Latinos12/ttbar/result-value.txt
rm test/Latinos12/ttbar/result-syst.txt
rm test/Latinos12/ttbar/result-syst-stat.txt
rm test/Latinos12/ttbar/result-syst-method.txt
rm test/Latinos12/ttbar/result-syst-CR-stat.txt
rm test/Latinos12/ttbar/result-syst-CJ-FJ.txt
rm test/Latinos12/ttbar/result-syst-MCSub.txt
echo top > test/Latinos12/ttbar/result-SF.txt
echo top > test/Latinos12/ttbar/result-value.txt
echo top > test/Latinos12/ttbar/result-syst.txt
echo top > test/Latinos12/ttbar/result-syst-stat.txt
echo top > test/Latinos12/ttbar/result-syst-method.txt
echo top > test/Latinos12/ttbar/result-syst-CR-stat.txt
echo top > test/Latinos12/ttbar/result-syst-CJ-FJ.txt
echo top > test/Latinos12/ttbar/result-syst-MCSub.txt

rm test/Latinos12/ttbar/result-SF-all.txt
rm test/Latinos12/ttbar/result-value-all.txt
rm test/Latinos12/ttbar/result-syst-all.txt
rm test/Latinos12/ttbar/result-syst-stat-all.txt
rm test/Latinos12/ttbar/result-syst-method-all.txt
rm test/Latinos12/ttbar/result-syst-CR-stat-all.txt
rm test/Latinos12/ttbar/result-syst-CJ-FJ-all.txt
rm test/Latinos12/ttbar/result-syst-MCSub-all.txt
echo top > test/Latinos12/ttbar/result-SF-all.txt
echo top > test/Latinos12/ttbar/result-value-all.txt
echo top > test/Latinos12/ttbar/result-syst-all.txt
echo top > test/Latinos12/ttbar/result-syst-stat-all.txt
echo top > test/Latinos12/ttbar/result-syst-method-all.txt
echo top > test/Latinos12/ttbar/result-syst-CR-stat-all.txt
echo top > test/Latinos12/ttbar/result-syst-CJ-FJ-all.txt
echo top > test/Latinos12/ttbar/result-syst-MCSub-all.txt

rm test/Latinos12/ttbar/result-SF-sf.txt
rm test/Latinos12/ttbar/result-value-sf.txt
rm test/Latinos12/ttbar/result-syst-sf.txt
rm test/Latinos12/ttbar/result-syst-stat-sf.txt
rm test/Latinos12/ttbar/result-syst-method-sf.txt
rm test/Latinos12/ttbar/result-syst-CR-stat-sf.txt
rm test/Latinos12/ttbar/result-syst-CJ-FJ-sf.txt
rm test/Latinos12/ttbar/result-syst-MCSub-sf.txt
echo top > test/Latinos12/ttbar/result-SF-sf.txt
echo top > test/Latinos12/ttbar/result-value-sf.txt
echo top > test/Latinos12/ttbar/result-syst-sf.txt
echo top > test/Latinos12/ttbar/result-syst-stat-sf.txt
echo top > test/Latinos12/ttbar/result-syst-method-sf.txt
echo top > test/Latinos12/ttbar/result-syst-CR-stat-sf.txt
echo top > test/Latinos12/ttbar/result-syst-CJ-FJ-sf.txt
echo top > test/Latinos12/ttbar/result-syst-MCSub-sf.txt

rm test/Latinos12/ttbar/result-SF-of.txt
rm test/Latinos12/ttbar/result-value-of.txt
rm test/Latinos12/ttbar/result-syst-of.txt
rm test/Latinos12/ttbar/result-syst-stat-of.txt
rm test/Latinos12/ttbar/result-syst-method-of.txt
rm test/Latinos12/ttbar/result-syst-CR-stat-of.txt
rm test/Latinos12/ttbar/result-syst-CJ-FJ-of.txt
rm test/Latinos12/ttbar/result-syst-MCSub-of.txt
echo top > test/Latinos12/ttbar/result-SF-of.txt
echo top > test/Latinos12/ttbar/result-value-of.txt
echo top > test/Latinos12/ttbar/result-syst-of.txt
echo top > test/Latinos12/ttbar/result-syst-stat-of.txt
echo top > test/Latinos12/ttbar/result-syst-method-of.txt
echo top > test/Latinos12/ttbar/result-syst-CR-stat-of.txt
echo top > test/Latinos12/ttbar/result-syst-CJ-FJ-of.txt
echo top > test/Latinos12/ttbar/result-syst-MCSub-of.txt


for ((i=0; i<27; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_H-WP$i.root\",0,0,$i,\"-all\"\) ;   done
for ((i=0; i<27; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_H-WP$i.root\",0,1,$i,\"-sf\"\) ;   done
for ((i=0; i<27; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_H-WP$i.root\",0,2,$i,\"-of\"\) ;   done



ls test/Latinos12/ttbar/result-*-WW.txt | grep -v shape | awk '{print "rm "$1}' | /bin/sh

for ((i=27; i<28; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_H-WP$i.root\",0,0,$i,\"-all-WW\"\) ;   done
for ((i=27; i<28; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_H-WP$i.root\",0,1,$i,\"-sf-WW\"\) ;   done
for ((i=27; i<28; i++)) do  root -l test/Latinos12/ttbar/GetTop-Result-forDataCard.cxx\(\"output/out_ComparisonPLOTT_H-WP$i.root\",0,2,$i,\"-of-WW\"\) ;   done









# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# WJets already "embedded"
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


# ./bin/MCDATACounter_Systematic.exe test/Latinos12/WJets/Systematic.cfg
# 
# numWP=`cat dataCard.Syst.WJets.110.txt | wc -l | bc`
# numWP=`echo "($numWP-1)/2" | bc`
# head -1  dataCard.Syst.WJets.110.txt >  tmp.txt
# tail -$numWP  dataCard.Syst.WJets.110.txt >>  tmp.txt
# mv tmp.txt test/Latinos12/WJets/result-syst.txt
# numWP=`echo "$numWP+1" | bc`
# head -$numWP  dataCard.Syst.WJets.110.txt >  tmp.txt
# mv tmp.txt test/Latinos12/WJets/result-value.txt
# cat test/Latinos12/WJets/result-value.txt
# cat test/Latinos12/WJets/result-syst.txt





./bin/MCDATACounter_Systematic.exe test/Latinos12/WJets/Systematic_of.cfg

numWP=`cat dataCard.Syst.WJets.110.of.txt | wc -l | bc`
numWP=`echo "($numWP-1)/2" | bc`
head -1  dataCard.Syst.WJets.110.of.txt >  tmp.txt
tail -$numWP  dataCard.Syst.WJets.110.of.txt >>  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-syst-of.txt
numWP=`echo "$numWP+1" | bc`
head -$numWP  dataCard.Syst.WJets.110.of.txt >  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-value-of.txt
cat test/Latinos12/WJets/result-value-of.txt
cat test/Latinos12/WJets/result-syst-of.txt







./bin/MCDATACounter_Systematic.exe test/Latinos12/WJets/Systematic_sf.cfg

numWP=`cat dataCard.Syst.WJets.110.sf.txt | wc -l | bc`
numWP=`echo "($numWP-1)/2" | bc`
head -1  dataCard.Syst.WJets.110.sf.txt >  tmp.txt
tail -$numWP  dataCard.Syst.WJets.110.sf.txt >>  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-syst-sf.txt
numWP=`echo "$numWP+1" | bc`
head -$numWP  dataCard.Syst.WJets.110.sf.txt >  tmp.txt
mv tmp.txt test/Latinos12/WJets/result-value-sf.txt
cat test/Latinos12/WJets/result-value-sf.txt
cat test/Latinos12/WJets/result-syst-sf.txt






# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# 4)  input for datacards
# 
# prepare data driven #
r00t test/createForMatt2012Analysis.cxx

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 
# 5) build datacard (MC expectation)
# TEST :::    ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard.cfg
# 


# rm dataCard.Result.???.txt 
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_110.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_115.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_120.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_125.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_130.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_135.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_140.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_145.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_150.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_155.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_160.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_170.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_180.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_190.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_200.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_250.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_300.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_350.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_400.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_450.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_500.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_550.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_600.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_700.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_800.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_900.cfg
# ./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/BuildDataCard_1000.cfg


rm dataCard.Result.???.??.txt 
rm dataCard.Result.????.??.txt 

./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF/BuildDataCard_1000.cfg


./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF/BuildDataCard_1000.cfg




################################
# injection test mH=125,   1x SM


rm dataCard.Result.???.??.txt 
rm dataCard.Result.????.??.txt 

./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/OF-Injection/BuildDataCard_1000.cfg


./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_110.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_115.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_120.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_125.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_130.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_135.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_140.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_145.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_150.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_155.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_160.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_170.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_180.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_190.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_200.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_250.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_300.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_350.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_400.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_450.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_500.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_550.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_600.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_700.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_800.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_900.cfg
./bin/BuildDataCard.exe test/Latinos12/BuildDataCard/SF-Injection/BuildDataCard_1000.cfg





### now "combine" and "Brazilian plot"

#### bye bye ####
#################


