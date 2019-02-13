# This file skims the data and saves the output to ./tmp
# Do not combine files across runs, otherwise you may get inconsistent TTree structures!
# Doing things file by file is the safest way to avoid this problem, and comes at almost
# no extra cost.
# You can copy and paste json sources directly from https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/

import os
import ROOT


#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_50_120'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_120_200'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_200_400'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_400_800'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_800_1400'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_1400_2300'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_2300_3500'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_3500_4500'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'

#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_50_120'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_120_200'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_200_400'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_400_800'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_800_1400'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_1400_2300'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIISpring16DR80/ZToEE_NNPDF30_13TeV-powheg_M_2300_3500'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/ZToEE_NNPDF30_13TeV-powheg_M_3500_4500'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/rgoldouz/RunIIFall15MiniAODv2/'
#path = '/pnfs/iihe/cms/store/user/wenxing/SingleElectron/crab_SingleElectron_Run2016B-PromptReco-v2_AOD_golden_0623/160623_122348/0001/'
path = []

#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/crab_ST_tW_top_5f_NoFullyHadronicDecays/170409_113037/0000/")                                      
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1/crab_ST_tW_antitop_5f_NoFullyHadronicDecays/170409_113133/0000/") 

#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-MiniAOD/170408_132740/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-MiniAOD/170408_132740/0001/")
#path.append('/pnfs/iihe/cms/store/user/dbeghin/WW_TuneCUETP8M1_13TeV-pythia8/crab_WW_TuneCUETP8M1_13TeV-pythia8_Nov25B/171125_225941/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/WZ_TuneCUETP8M1_13TeV-pythia8/crab_WZ_TuneCUETP8M1_13TeV-pythia8_Nov25B/171125_234037/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_ZZ_TuneCUETP8M1_13TeV-pythia8_Nov25B/171125_234323/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8_Nov25B/*/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v10ext1v1_Nov25B/171125_234205/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v10v1_Nov25B/171125_234015/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia_v7v1_Nov25B/171125_234252/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_v10ext1v1_Nov25B/171125_233953/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_v10ext1v2_Nov25B/171125_234056/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_v7v1_Nov25B/171125_233933/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Nov25B/171125_234146/')
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-MiniAOD/170408_132740/0000/failed/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8-MiniAOD/170408_132740/0001/failed/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/DYJetsToLL_M-400to500_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-400to500_TuneCUETP8M1_13TeV-amcatnloFXFX/170409_112331/0000/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/DYJetsToLL_M-500to700_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-500to700_TuneCUETP8M1_13TeV-amcatnloFXFX/170409_112133/0000/")                                                    
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/DYJetsToLL_M-700to800_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-700to800_TuneCUETP8M1_13TeV-amcatnloFXFX/170409_113201/0000/")                                                    
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/DYJetsToLL_M-800to1000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-800to1000_TuneCUETP8M1_13TeV-amcatnloFXFX/170409_112757/0000/")                                                  
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/DYJetsToLL_M-1000to1500_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-1000to1500_TuneCUETP8M1_13TeV-amcatnloFXFX/170409_112941/0000/")                                                
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/DYJetsToLL_M-1500to2000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-1500to2000_TuneCUETP8M1_13TeV-amcatnloFXFX/170409_113105/0000/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/DYJetsToLL_M-2000to3000_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-2000to3000_TuneCUETP8M1_13TeV-amcatnloFXFX/170409_113257/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/TTToLL_MLL_1200To1800_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TTToLL_MLL_1200To1800_TuneCUETP8M1_13TeV-powheg-MiniAOD/170408_133520/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/TTToLL_MLL_1800ToInf_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TTToLL_MLL_1800ToInf_TuneCUETP8M1_13TeV-powheg-MiniAOD/170408_132301/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/TTToLL_MLL_500To800_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TTToLL_MLL_500To800_TuneCUETP8M1_13TeV-powheg-MiniAOD/170408_133703/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/TTToLL_MLL_800To1200_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TTToLL_MLL_800To1200_TuneCUETP8M1_13TeV-powheg-MiniAOD/170408_133613/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD/170408_133340/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD_ext1/170408_133104/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD_ext4/170408_132830/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD_ext4/170408_132830/0001/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD/170408_131656/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD_ext1/170408_133247/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD_ext4/170408_132920/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-400To600_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-400To600_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD/170408_132603/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-400To600_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-400To600_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD_ext1/170408_131414/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-600ToInf_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-600ToInf_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD/170408_132651/0000/")
#path.append("/pnfs/iihe/cms/store/user/wenxing/FINAL_sample/MC/WJetsToLNu_Pt-600ToInf_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJetsToLNu_Pt-600ToInf_TuneCUETP8M1_13TeV-amcatnlo-MiniAOD_ext1/170408_133013/0000/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WJets/170408_125645/0000/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/crab_ttbar_2l2nu/170408_130006/0000/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/TTTo2L2Nu_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/crab_ttbar_2l2nu/170408_130006/0001/")


#path.append("/pnfs/iihe/cms/store/user/dbeghin/QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8/crab_QCD_MuEnriched_Pt20toInf/170512_143430/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_15to30/180122_183142/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_30to50/180117_152418/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_50to80/180117_152133/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_80to120/180117_152812/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_80to120ext2/180117_151022/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_120to170/180122_183652/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_120to170ext1/180122_183415/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_170to300/180122_183558/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_170to300ext1/180122_183308/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_300to470/180117_151124/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_300to470ext1/180117_153202/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_470to600/180117_152224/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_600to800/180117_151924/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_600to800ext1/180117_151554/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_800to1000ext1/180117_152920/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_1000to1400/180122_183229/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_1000to1400ext1/180122_183341/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_1400to1800/180122_183510/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/crab_QCD_Pt_1400to1800ext1/180122_183725/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_1800to2400/180117_151451/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_1800to2400ext1/180117_151654/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_2400to3200/180117_151257/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/Moriond17/MuTau_mc_2018Jan22/crab_QCD_Pt_2400to3200ext1/180117_152314/0000/")

#path.append("/pnfs/iihe/cms/store/user/amkalsi/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_TuneCP5_13TeV-/180121_141552/0000/")

#path.append("/pnfs/iihe/cms/store/user/amkalsi/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W1Jet/180208_214528/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W1Jet/180208_214528/0001/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W2Jets/180208_214508/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W3Jets/180208_214633/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W4Jets/180208_214613/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsinc/180208_214548/0000/")

#path.append("/pnfs/iihe/cms/store/user/amkalsi/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJets_madgraph/180203_100002/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJets_madgraph/180203_100002/0001/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJets_madgraph_v1/180203_100014/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJets_madgraph_v1/180203_100014/0001/")

#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/180218_162022/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/180218_162022/0001/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_v1/180218_162040/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_v1/180218_162040/0001/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_v1/180218_162040/0002/")

#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/crab_QCD_Pt20_30/180218_171635/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/crab_QCD_Pt20_30/180218_171635/0001/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/crab_QCD_Pt30_50/180218_171701/0000/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/crab_QCD_Pt30_50/180218_171701/0001/")
#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/crab_QCD_Pt50_80/180218_171722/0000/")

#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134720/0000/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134720/0001/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8/180618_134720/0002/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8ext/180618_134830/0000/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8ext/180618_134830/0001/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-madgraphMLM-pythia8ext/180618_134830/0002/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8/180618_134754/0000/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8/180618_134754/0001/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0000/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0001/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0002/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0003/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0004/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0005/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0006/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0007/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0008/')
#path.append('/pnfs/iihe/cms/store/user/dbeghin/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_TuneCP5_13TeV-amcatnloFXFX-pythia8ext/180618_134736/0009/')

#path.append("/pnfs/iihe/cms/store/user/amkalsi/Moriond2018_Final/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/180619_135246/0000/")

#path.append('/pnfs/iihe/cms/store/user/dbeghin/RPVresonantToMuTau_M-1800_LLE_LQD-001_TuneCUETP8M1_13TeV-calchep-pythia8/crab_RPVresonantToMuTau_M-1800_LLE_LQD-001/170410_134533/0000')


#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/WW_TuneCUETP8M1_13TeV-pythia8/crab_WW/170408_130328/0000/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/WZ_TuneCUETP8M1_13TeV-pythia8/crab_WZ/170408_125550/0000/")
#path.append("/pnfs/iihe/cms/store/user/xgao/2017MC_Moriond/2017-04/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_ZZ/170408_130111/0000/")                   


#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/181029_132920/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/181029_132920/0001/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/181029_132920/0002/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/181029_132853/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/181029_132853/0001/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/crab_TTToHadronic_TuneCP5_13TeV-powheg-pythia8/181029_132853/0002/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/181029_132733/0000/")
path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/181026_160409/0000/")
path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_ext/181026_160251/0000/")
path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_ext/181026_160251/0001/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/181026_160421/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_ext/181026_160308/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/WZ_TuneCP5_13TeV-pythia8/crab_WZ_TuneCP5_13TeV-pythia8/181029_132825/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/WW_TuneCP5_13TeV-pythia8/crab_WW_TuneCP5_13TeV-pythia8/181026_160205/0000/")
#path.append("/pnfs/iihe/cms/store/user/dbeghin/2017METCorrected/MC/ZZ_TuneCP5_13TeV-pythia8/crab_ZZ_TuneCP5_13TeV-pythia8/181029_132759/0000/")



outFile = open("weights.txt" , 'w')
nEventsraw = 0
neventsweight = 0
neventsweight_renorm = 0
nEventsStored = 0
nEventsiihe = 0

for a in path:
    nEventsraw = 0
    neventsweight = 0
    neventsweight_renorm = 0
    nEventsStored = 0
    nEventsiihe = 0
    print a
    filenames=os.popen("ls -t " + a + "*.root")
    for fname in filenames:
        filename = fname[0:-1]
        f = ROOT.TFile.Open(filename)
        tree_in = f.Get('IIHEAnalysis')
        tree_meta = f.Get('meta')
        nEventsiihe += tree_in.GetEntries()
        tree_meta.GetEntry(0)    
        #print tree_meta.nEventsRaw
        nEventsraw += tree_meta.nEventsRaw
        #print nEventsraw
        nEventsStored += tree_meta.nEventsStored
        neventsweight += tree_meta.mc_nEventsWeighted
        f.Close()
    print 'nEventsraw %d   '%(nEventsraw)
    print 'neventsweight %d   '%(neventsweight)
    #print 'neventsweight_renorm %d   '%(neventsweight_renorm)
    print 'nEventsStored %d   '%(nEventsStored)
    print 'nEventsiihe %d   '%(nEventsiihe)
    outFile.write(a+"\n")
    outFile.write('nEventsraw %d   '%(nEventsraw) + "\n")
    outFile.write('neventsweight %d   '%(neventsweight) + "\n")
    #outFile.write('neventsweight_renorm %d   '%(neventsweight_renorm) + "\n")
    outFile.write('nEventsStored %d   '%(nEventsStored) + "\n")
    outFile.write('nEventsiihe %d   '%(nEventsiihe) + "\n\n")

outFile.close()
