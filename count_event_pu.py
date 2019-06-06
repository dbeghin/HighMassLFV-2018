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
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190506_132620/0000/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190506_132620/0001/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190506_132620/0002/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190506_132620/0003/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/190506_132620/0004/",
]


############################# WW ############################


path_WW=[
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/WW_TuneCP5_13TeV-pythia8/crab_WW_TuneCP5_13TeV-pythia8/190506_132258/0000/",
]


############################## WZ ###########################
path_WZ=[
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/WZ_TuneCP5_13TeV-pythia8/crab_WZ_TuneCP5_13TeV-pythia8/190506_132744/0000/",
]

################################ ZZ #########################
path_ZZ=[
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/ZZ_TuneCP5_13TeV-pythia8/crab_ZZ_TuneCP5_13TeV-pythia8/190506_132359/0000/",
]

################################## ST ###################
path_ST=[
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_v2/190506_132550/0000/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_v3/190506_132522/0000/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_v2/190506_132454/0000/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_v3/190506_132817/0000/",
]




####################################### TTbar ####################
#path_TT_inclusive=['/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext1/171019_161505/0000/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext1/171019_161505/0001/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext2/171019_161445/0000/','/pnfs/iihe/cms/store/user/wenxing/RunIISummer17MiniAOD-92X/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_ext2/171019_161445/0001/']

path_TT_2L2Nu=[
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/190506_132428/0000/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/190506_132428/0001/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/190506_132428/0002/",
]

path_TT_SemiLeptonic=[
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190506_132333/0000/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190506_132333/0001/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190506_132333/0002/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190506_132333/0003/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190506_132333/0004/",
]

path_TT_had = [
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190506_132644/0000/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190506_132644/0001/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190506_132644/0002/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190506_132644/0003/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190506_132644/0004/",
"/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/190506_132644/0005/",
]


####### ZPrime -> mutau #########
path_ZPrime_500  = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_500/crab_20190529_115502/190529_095549/0000/"]
path_ZPrime_600  = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_600/crab_20190529_143228/190529_123301/0000/"]
path_ZPrime_700  = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_700/crab_20190529_142943/190529_123021/0000/"]
path_ZPrime_850  = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_850/crab_20190529_143109/190529_123146/0000/"]
path_ZPrime_1000 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_1000/crab_20190529_143025/190529_123105/0000/"]
path_ZPrime_1300 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_1300/crab_20190529_143418/190529_123449/0000/"]
path_ZPrime_1700 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_1700/crab_20190529_143340/190529_123414/0000/"]
path_ZPrime_2000 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_2000/crab_20190529_143305/190529_123336/0000/"]
path_ZPrime_2500 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_2500/crab_20190529_142800/190529_122849/0000/"]
path_ZPrime_3000 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_3000/crab_20190529_142855/190529_122938/0000/"]
path_ZPrime_4000 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_4000/crab_20190529_143453/190529_123524/0000/"]
path_ZPrime_5000 = ["/pnfs/iihe/cms/store/user/dbeghin/Legacy/2018_v1/Zprime_5000/crab_20190529_143149/190529_123224/0000/"]


################################## 20180220 ################

#sample_path['WW']             =path_WW
#sample_path['WZ']             =path_WZ
#sample_path['ZZ']             =path_ZZ
#sample_path['ST']             =path_ST
#sample_path['DYToLL_mad']     =path_DYToLL_mad
#sample_path['TT_had']        = path_TT_had       
#sample_path['TT_2l2nu']      = path_TT_2L2Nu       
#sample_path['TT_semilep']    = path_TT_SemiLeptonic


sample_path['ZPrime_500']   =  path_ZPrime_500 
sample_path['ZPrime_600']   =  path_ZPrime_600 
sample_path['ZPrime_700']   =  path_ZPrime_700 
sample_path['ZPrime_850']   =  path_ZPrime_850 
sample_path['ZPrime_1000']  =  path_ZPrime_1000
sample_path['ZPrime_1300']  =  path_ZPrime_1300
sample_path['ZPrime_1700']  =  path_ZPrime_1700
sample_path['ZPrime_2000']  =  path_ZPrime_2000
sample_path['ZPrime_2500']  =  path_ZPrime_2500
sample_path['ZPrime_3000']  =  path_ZPrime_3000
sample_path['ZPrime_4000']  =  path_ZPrime_4000
sample_path['ZPrime_5000']  =  path_ZPrime_5000



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
