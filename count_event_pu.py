import os
import ROOT

sample_path = {}

############################ ZToEE #########################
#path_ZToEE_50_120   =["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_50_120/crab_ZToEE_NNPDF31_13TeV-powheg_M_50_120/180218_161630/0000/"]
#path_ZToEE_120_200  =["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_120_200/crab_ZToEE_NNPDF31_13TeV-powheg_M_120_200/180218_161650/0000/"]
#path_ZToEE_200_400  =["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_200_400/crab_ZToEE_NNPDF31_13TeV-powheg_M_200_400/180218_161707/0000/"]
#path_ZToEE_400_800  =["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_400_800/crab_ZToEE_NNPDF31_13TeV-powheg_M_400_800/180218_161727/0000/"]
#path_ZToEE_800_1400 =["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_800_1400/crab_ZToEE_NNPDF31_13TeV-powheg_M_800_1400/180218_161744/0000/"]
#path_ZToEE_1400_2300=["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_1400_2300/crab_ZToEE_NNPDF31_13TeV-powheg_M_1400_2300/180218_161810/0000/"]
#path_ZToEE_2300_3500=["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_2300_3500/crab_ZToEE_NNPDF31_13TeV-powheg_M_2300_3500/180218_161830/0000/"]
#path_ZToEE_3500_4500=["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_3500_4500/crab_ZToEE_NNPDF31_13TeV-powheg_M_3500_4500/180218_161848/0000/"]
#path_ZToEE_4500_6000=["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_4500_6000/crab_ZToEE_NNPDF31_13TeV-powheg_M_4500_6000/180218_161906/0000/"]
#path_ZToEE_6000_Inf =["/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ZToEE_NNPDF31_13TeV-powheg_M_6000_Inf/crab_ZToEE_NNPDF31_13TeV-powheg_M_6000_Inf/180218_161928/0000/"]
########################### DYToEE powheg #####################
#path_DYToEE_pow   =['/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYToEE_M-50_NNPDF31_13TeV-powheg-pythia8/crab_DYToEE_M-50_NNPDF31_13TeV-powheg-pythia8/180218_162058/0000/']

########################### DYJetToLL amc #####################





path_DYToLL_mad=[
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190212_101726/0000/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190212_101726/0001/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190212_101726/0002/',
]

#path_DY1J=[
#'/pnfs/iihe/cms/store/user/dbeghin/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY1JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134813/0000/',
#'/pnfs/iihe/cms/store/user/dbeghin/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY1JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134813/0001/',
#'/pnfs/iihe/cms/store/user/dbeghin/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY1JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8ext/180618_134618/0000/',
#'/pnfs/iihe/cms/store/user/dbeghin/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY1JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8ext/180618_134618/0001/',
#]
#
#path_DY2J=[
#'/pnfs/iihe/cms/store/user/dbeghin/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY2JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134650/0000/',
#'/pnfs/iihe/cms/store/user/dbeghin/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY2JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8ext/180618_134704/0000/',
#]
#
#path_DY3J=[
#'/pnfs/iihe/cms/store/user/dbeghin/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY3JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134635/0000/',
#]
#
#path_DY4J=[
#'/pnfs/iihe/cms/store/user/dbeghin/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY4JetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134848/0000/',
#]


########################### DYJetToLL mad V2 #####################
#path_DYToLL_mad=['/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/180218_162022/0000/','/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/180218_162022/0001/','/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_v1/180218_162040/0000/','/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_v1/180218_162040/0001/','/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_v1/180218_162040/0002/']

########################### WJets ############################

#path_WJet_mad  =[
#'/pnfs/iihe/cms/store/user/amkalsi/2017_MET_Corrected_10Dec2018/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV/181214_095754/0000/',
#'/pnfs/iihe/cms/store/user/amkalsi/2017_MET_Corrected_10Dec2018/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV/181214_095754/0001/',
#]

#path_W1J = [
#'/pnfs/iihe/cms/store/user/amkalsi/Moriond2018_Final/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/180619_135442/0000/',
#'/pnfs/iihe/cms/store/user/amkalsi/Moriond2018_Final/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/180619_135442/0001/',
#]
#
#path_W2J = [
#'/pnfs/iihe/cms/store/user/amkalsi/Moriond2018_Final/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/180619_135552/0000/',
#]
#
#path_W3J = [
#'/pnfs/iihe/cms/store/user/amkalsi/Moriond2018_Final/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/180619_135630/0000/',
#]
#
#path_W4J = [
#'/pnfs/iihe/cms/store/user/amkalsi/Moriond2018_Final/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/180619_135652/0000/',
#]

############################# WW ############################


path_WW=[
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/WW_TuneCP5_13TeV-pythia8/crab_WW_TuneCP5_13TeV-pythia8/190212_101658/0000/',
]

############################# WWTo2L2Nv ############################
#
############################## WZ ###########################
path_WZ=[
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/WZ_TuneCP5_13TeV-pythia8/crab_WZ_TuneCP5_13TeV-pythia8/190212_101744/0000/',
]

################################ ZZ #########################
path_ZZ=[
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/ZZ_TuneCP5_13TeV-pythia8/crab_ZZ_TuneCP5_13TeV-pythia8/190212_101717/0000/',
]

################################## ST ###################
#path_ST=['/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_top_5f_NoFullyHadronicDecays/180218_162306/0000/']
#
#path_ST_anti=['/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_antitop_5f_NoFullyHadronicDecays/180218_162324/0000/']
#
################################# DY mad #####################


##################################### Gamma+Jet ############
#path_GJ  =['/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/GJet_DoubleEMEnriched_13TeV_pythia8/crab_GJet_DoubleEMEnriched_13TeV_pythia8/171019_161408/0000/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/GJet_DoubleEMEnriched_13TeV_pythia8/crab_GJet_DoubleEMEnriched_13TeV_pythia8/171019_161408/0001/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/GJet_DoubleEMEnriched_13TeV_pythia8/crab_GJet_DoubleEMEnriched_13TeV_pythia8/171019_161408/0002/']


####################################### TTbar ####################
#path_TT_inclusive=['/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext1/171019_161505/0000/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext1/171019_161505/0001/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext2/171019_161445/0000/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext2/171019_161445/0001/']

path_TT_2L2Nu=[
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/190212_101756/0000/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/190212_101756/0001/',
]

path_TT_SemiLeptonic=[
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190212_101708/0000/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190212_101708/0001/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190212_101708/0002/',
]

path_TT_had = [
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190212_101735/0000/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190212_101735/0001/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190212_101735/0002/',
'/pnfs/iihe/cms/store/user/dbeghin/2018first/2018Feb11/MC/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190212_101735/0003/',
]


################################## 20180220 ################
#sample_path['ZToEE_50_120'   ]=path_ZToEE_50_120   
#sample_path['ZToEE_120_200'  ]=path_ZToEE_120_200  
#sample_path['ZToEE_200_400'  ]=path_ZToEE_200_400  
#sample_path['ZToEE_400_800'  ]=path_ZToEE_400_800  
#sample_path['ZToEE_800_1400' ]=path_ZToEE_800_1400 
#sample_path['ZToEE_1400_2300']=path_ZToEE_1400_2300
#sample_path['ZToEE_2300_3500']=path_ZToEE_2300_3500
#sample_path['ZToEE_3500_4500']=path_ZToEE_3500_4500
#sample_path['ZToEE_4500_6000']=path_ZToEE_4500_6000
#sample_path['ZToEE_6000_Inf' ]=path_ZToEE_6000_Inf 
#sample_path['DYToEE_pow']     =path_DYToEE_pow
#sample_path['DYToLL_mad']     =path_DYToLL_mad
#sample_path['TT_2L2Nu']       =path_TT_2L2Nu
#sample_path['TT_SemiLeptonic']= path_TT_SemiLeptonic
#sample_path['ST']             =path_ST
#sample_path['ST_anti']        =path_ST_anti
#sample_path['GJet_40_100']    =path_GJ_40_100 
#sample_path['GJet_100_200']   =path_GJ_100_200
#sample_path['GJet_200_400']   =path_GJ_200_400
#sample_path['GJet_400_600']   =path_GJ_400_600
#sample_path['GJet_600_Inf']   =path_GJ_600_Inf


#sample_path['WW']             =path_WW
#sample_path['WZ']             =path_WZ
#sample_path['ZZ']             =path_ZZ
#sample_path['WJetsToLNu']     =path_WJet_mad
#sample_path['W1J']           = path_W1J          
#sample_path['W2J']           = path_W2J          
#sample_path['W3J']           = path_W3J          
#sample_path['W4J']           = path_W4J          
#sample_path['DYToLL_amc']     =path_DYToLL_amc
#sample_path['DYToLL_mad']     =path_DYToLL_mad
#sample_path['DY1J']          = path_DY1J         
#sample_path['DY2J']          = path_DY2J         
#sample_path['DY3J']          = path_DY3J         
#sample_path['DY4J']          = path_DY4J         
sample_path['TT_had']        = path_TT_had       
#sample_path['TT_2l2nu']      = path_TT_2L2Nu       
#sample_path['TT_semilep']    = path_TT_SemiLeptonic
#sample_path['QCD_20_30']     = path_QCD_20_30    
#sample_path['QCD_30_50']     = path_QCD_30_50    
#sample_path['QCD_50_80']     = path_QCD_50_80    
#sample_path['QCD_80_120']    = path_QCD_80_120   
#sample_path['QCD_120_170']   = path_QCD_120_170  
#sample_path['QCD_170_300']   = path_QCD_170_300  
#sample_path['QCD_300_470']   = path_QCD_300_470  
#sample_path['QCD_470_600']   = path_QCD_470_600  
#sample_path['QCD_600_800']   = path_QCD_600_800  
#sample_path['QCD_800_1000']  = path_QCD_800_1000 
#sample_path['QCD_1000_Inf']  = path_QCD_1000_Inf 


for sample_name in sample_path:
    H_pu=ROOT.TH1F("pileup_%s"%(sample_name),"",120,0,120)
    H_pu.Scale(0)
    nEventsraw = 0
    neventsweight = 0
    nEventsStored = 0
    nEventsiihe = 0
    for path in sample_path[sample_name]:
        print path
        filenames = os.listdir(path)
        for fname in filenames:
            filename = path +  fname
            if 'root' not in fname: continue
            f = ROOT.TFile.Open(filename)
            if not f: print 'not exist'+fname
            tree_in = f.Get('IIHEAnalysis')
            tree_meta = f.Get('meta')
            nEventsiihe += tree_in.GetEntries()
            tree_meta.GetEntry(0)
            nEventsraw += tree_meta.nEventsRaw
            nEventsStored += tree_meta.nEventsStored
            neventsweight += tree_meta.mc_nEventsWeighted
            h_tmp=f.Get("pileupDist")
            H_pu.Add(h_tmp,1)
            f.Close()
    fout=ROOT.TFile("./mc_pu/%s.root"%(sample_name),"RECREATE")
    fout.cd()
    H_pu.Write("pileup")
    fout.Close()
    print '#####################'
    print '%s'%(sample_name) 
    print 'nEventsraw %d   '%(nEventsraw)
    print 'neventsweight %d   '%(neventsweight)
    print 'nEventsStored %d   '%(nEventsStored)
    print 'nEventsiihe %d   '%(nEventsiihe)
    print '#####################' 
