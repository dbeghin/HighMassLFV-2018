mkdir -p Arranged_DY
hadd -f Arranged_DY/DY.root Out_DYamc*/Con*DY*.root 
#hadd -f Arranged_DY/DY.root Out_DYmad*/Con*DY*.root 


mkdir -p Arranged_TT
hadd -f Arranged_TT/TT_had.root Out_TT_had*/Con*TT*.root 
hadd -f Arranged_TT/TT_semilep.root Out_TT_semilep*/Con*TT*.root 
hadd -f Arranged_TT/TT_2l2nu.root Out_TT_2l*/Con*TT*.root 


mkdir -p Arranged_WJets
hadd -f Arranged_WJets/WJets.root Out_WJets*/Con*WJets*.root 


#mkdir -p Arranged_QCD
#hadd -f Arranged_QCD/QCD_20to30.root Out_QCD_*20to30*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_30to50.root Out_QCD_*30to50*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_50to80.root Out_QCD_*50to80*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_80to120.root Out_QCD_*80to120*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_120to170.root Out_QCD_*120to170*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_170to300.root Out_QCD_*170to300*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_300to470.root Out_QCD_*300to470*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_470to600.root Out_QCD_*470to600*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_600to800.root Out_QCD_*600to800*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_800to1000.root Out_QCD_*800to1000*/Con*QCD*.root
#hadd -f Arranged_QCD/QCD_1000toInf.root Out_QCD_*1000toInf*/Con*QCD*.root

mkdir -p Arranged_WW
hadd -f Arranged_WW/WW.root Out_WW/Con*WW*.root 


mkdir -p Arranged_ZZ
hadd -f Arranged_ZZ/ZZ.root Out_ZZ/Con*ZZ*.root 


mkdir -p Arranged_WZ
hadd -f Arranged_WZ/WZ.root Out_WZ/Con*WZ*.root 


#mkdir -p Arranged_ST_top
#hadd -f Arranged_ST_top/ST_top.root Out_ST_top/Con*ST_top*.root 
#
#
#mkdir -p Arranged_ST_antitop
#hadd -f Arranged_ST_antitop/ST_antitop.root Out_ST_antitop/Con*ST_antitop*.root 


mkdir -p Arranged_data
hadd -f Arranged_data/data.root Out_SMu_*/Con*.root