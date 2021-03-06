
#!/usr/bin/env python
import ROOT
import re
from array import array
import os

signal_name = "ZPrime_4000"
#signal_name = "RPV_l001_4000"
#signal_name = "QBH_4500"

def add_lumi():
    lowX=0.58
    #lowX=0.38
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.04)
    lumi.SetTextFont (   42 )
    lumi.AddText("2017 simulation")
    return lumi

def add_CMS():
    lowX=0.21
    lowY=0.70
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.055)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
    return lumi

def add_Preliminary():
    lowX=0.21
    lowY=0.63
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.04)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend(x1,y1,x2,y2):
    output = ROOT.TLegend(x1, y1, x2, y2, "", "brNDC")
    output.SetHeader(signal_name)
    output.SetLineWidth(0)
    output.SetLineStyle(0)
    output.SetFillStyle(0)
    output.SetBorderSize(0)
    output.SetTextFont(62)
    output.SetNColumns(2)
    return output


ROOT.gStyle.SetFrameLineWidth(3)
ROOT.gStyle.SetLineWidth(3)
ROOT.gStyle.SetOptStat(0)

os.system("rm histoStack_systematics.root")

c=ROOT.TCanvas("canvas","",0,0,600,600)
c.cd()

#file=ROOT.TFile("final.root","r")
file=ROOT.TFile("mutauHistos_forLimitSetting_2018.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)


var=[]
#var.append("ev_Mvis")          
#var.append("ev_Mtot")          
#var.append("tau_pt")           
#var.append("tau_eta")          
#var.append("tau_phi")          
#var.append("mu_pt")            
#var.append("mu_eta")           
#var.append("mu_phi")           
#var.append("mu_isolation")           
#var.append("ev_DRmutau")       
#var.append("ev_MET")           
var.append("ev_Mcol")          
#var.append("ev_Mt")            
#var.append("sign")

var_log_dic = {
"ev_Mvis"          : True,           
"ev_Mtot"          : True,      
"tau_pt"           : True,       
"tau_eta"          : False,      
"tau_phi"          : False,     
"mu_pt"            : True,       
"mu_eta"           : False,       
"mu_phi"           : False,       
"mu_isolation"     : True,       
"ev_DRmutau"       : False, 
"ev_DeltaPhimutau" : False,
"ev_DeltaPhiMETtau": False,
"ev_MET"           : True,
"ev_Mcol"          : True,
"ev_Mt"            : True,
"sign"             : False,
}

nvar=len(var)
print nvar

photogenic_var={
"ev_Mvis":              "m_{vis} (GeV)",
"ev_Mtot":              "m_{tot} (GeV)",
"tau_pt":               "#tau p_{T} (GeV)",
"tau_eta":              "#tau #eta",
"tau_phi":              "#tau #phi",
"mu_pt":                "#mu p_{T} (GeV)",
"mu_eta":               "#mu #eta",
"mu_phi":               "#mu #phi",
"mu_isolation":         "#mu iso",
"ev_DRmutau":           "#DeltaR (#mu #tau)",
"ev_DeltaPhimutau":     "#Delta#Phi (#mu #tau)",
"ev_DeltaPhiMETtau":    "#Delta#Phi (E_{T}^{miss} #tau)",
"ev_MET":               "E_{T}^{miss} (GeV)",
"ev_Mcol":              "m_{col}",
"ev_Mt":                "m_{T}",
"sign":                 "OS (left) versus SS (right)",
}

Mth=[
"_MtHigh", 
]

systs_aux=[
"TrueTESdm0",
"TrueTESdm1",
"TrueTESdm10",
"TrueTESdm11",
"FakeEleTESdm0",
"FakeEleTESdm1",
"FakeMuTESdm0",
"FakeMuTESdm1",
"METJetEn",
"METJetRes",
"METUnclustered",
"MES",
"mres",
"minbias",
"muonID",
"muonIso",
"trigger",
"tauID",
"eletauFR",
"mutauFR",
#"FRstat",
#"topQscale",
#"topPDF",
#"WWPDF",
"PDF",
#"prefiring",
#"tracking",
]


systs_mask=[
"FRstat", #always mask, combined with FR syst
"TrueTESdm0",
"TrueTESdm1",
"TrueTESdm10",
"TrueTESdm11",
"FakeEleTESdm0",
"FakeEleTESdm1",
"FakeMuTESdm0",
"FakeMuTESdm1",
"METJetEn",
"METJetRes",
"METUnclustered",
"MES",
"mres",
"muonID",
"muonIso",
"tauID",
"eletauFR",
"mutauFR",
"topQscale",
"topPDF",
"WWPDF",
"trigger",
]


systs_cons={
"Tau":        ["TrueTESdm0","TrueTESdm1","TrueTESdm10","TrueTESdm11","FakeEleTESdm0","FakeEleTESdm1","FakeMuTESdm0","FakeMuTESdm1","tauID","eletauFR","mutauFR"],     
"Muon":       ["MES","muonID","muonIso"],     
#"Top":        ["topQscale","topPDF"],
"MET":        ["METJetEn","METJetRes","METUnclustered"],
"Trigger":    ["trigger"],
}



systs_map={
"Tau":        "#tau systematics",     
"Muon":       "#mu systematics",     
"Top":        "top systematics",     
"TES":        "#tau energy scale",     
"MES":        "#mu energy scale",     
"MET":        "MET systematics",     
"mres":       "#mu p_{T} res.",    
"minbias":    "min bias xs", 
"muonID":     "#mu ID",  
"muonIso":    "#mu isolation", 
"tracking":   "tracking",
"trigger":    "trigger", 
"Trigger":    "trigger", 
"tauID":      "#tau ID",   
"eletauFR":   "e #rightarrow #tau FR",
"mutauFR":    "#mu #rightarrow #tau FR", 
"FRstat":     "jet #rightarrow #tau FF",  
#"FRsys":     #"FRsys",  
"topPt":      "top p_{T} reweighting",   
#"xs":         "cross-sections",
"lumi":       "luminosity",
"fakefactor": "jet #rightarrow #tau FF",
"stat":       "simulation stat.",
"prefiring":  "prefiring",
"WWPDF":      "WW PDF",
"PDF":        "Signal PDF",
}



systs_up=[]
systs_down=[]

variation=[
"up",
"down",
]

for i in range(0,len(systs_aux)):
    systs_up.append(systs_aux[i]+"_up")
    systs_down.append(systs_aux[i]+"_down")

systs={}
systs["up"]=systs_up
systs["down"]=systs_down


for k in range (0,nvar):
    for l in range (0,len(Mth)):
        Signal={}
        MC={}
        MC_rel={}
        sq_combined_error={}
        
        ###########################################
        ###########################################
        #nominal plots
            

        Signal["nominal"]=file.Get(signal_name+"_nominal")

        MC["nominal"]=Signal["nominal"].Clone("MC_nominal")
        MC["nominal"].SetName("MC_nominal")


        
        #end nominal
        ###########################################
        ###########################################

        #systematics
        for iVar in range(0,len(variation)):
            vary=variation[iVar]
            Signal[vary]=[]
            MC[vary]=[]

            sq_combined_error[vary]=MC["nominal"].Clone()
            sq_combined_error[vary].SetName("square_errors_"+vary+"_"+var[k]+Mth[l])
            for iBin in range(1,sq_combined_error[vary].GetNbinsX()+1):
                sq_combined_error[vary].SetBinContent(iBin, 0)
                sq_combined_error[vary].SetBinError(iBin, 0)

        for j in range(0,len(systs_up)):
            for iVar in range(0,len(variation)):
                vary=variation[iVar]

                Signal[vary].append(file.Get(signal_name+"_"+systs[vary][j]))
                print signal_name+"_"+systs[vary][j]
                MC[vary].append(Signal[vary][j].Clone())

                htemp_up = sq_combined_error["up"].Clone()
                htemp_down = sq_combined_error["down"].Clone()
                for iBin in range(1, htemp_up.GetNbinsX()+1):
                    bin_content = MC[vary][j].GetBinContent(iBin)-MC["nominal"].GetBinContent(iBin)
                    if bin_content < 0:
                        htemp_down.SetBinContent(iBin, pow(bin_content,2))
                        htemp_up.SetBinContent(iBin, 0)
                    else:
                        htemp_down.SetBinContent(iBin, 0)
                        htemp_up.SetBinContent(iBin, pow(bin_content,2))
                sq_combined_error["up"].Add(htemp_up)
                sq_combined_error["down"].Add(htemp_down)

                MC[vary][j].Add(MC["nominal"], -1)
                for iBin in range(1, MC[vary][j].GetNbinsX()+1):
                    bin_content = abs(MC[vary][j].GetBinContent(iBin))
                    MC[vary][j].SetBinContent(iBin, bin_content)
            MC_rel[systs_aux[j]] = MC["up"][j].Clone()
            MC_rel[systs_aux[j]].SetName(systs_aux[j]+"_rel")
            #MC_rel[systs_aux[j]].Add(MC["down"][j])
            #MC_rel[systs_aux[j]].Scale(0.5)
            for iBin in range(1,MC_rel[systs_aux[j]].GetNbinsX()+1):
                bin_content = 0
                if MC["nominal"].GetBinContent(iBin) > 0.000001:
                    bin_content = MC_rel[systs_aux[j]].GetBinContent(iBin)/MC["nominal"].GetBinContent(iBin)
                MC_rel[systs_aux[j]].SetBinContent(iBin, bin_content)

        #Consolidation of similar SFs to avoid clutter
        for cons in systs_cons.keys():
            MC_rel[cons]=MC_rel[systs_cons[cons][0]].Clone(cons+"_rel")
            for iBin in range(1,MC_rel[cons].GetNbinsX()+1):
                bin_content = 0
                for iCons in range(0,len(systs_cons[cons])):
                    bin_content += pow(MC_rel[systs_cons[cons][iCons]].GetBinContent(iBin),2)
                MC_rel[cons].SetBinContent(iBin, pow(bin_content,0.5))
        
        #Cross-section, lumi, fakefactor & MC statistics
        MC_rel["lumi"]=MC["nominal"].Clone()
        MC_rel["lumi"].SetName("lumi_rel")

        MC_rel["stat"]=MC["nominal"].Clone()
        MC_rel["stat"].SetName("stat_rel")

        comb_error=sq_combined_error["up"].Clone()
        comb_error.SetName("combined_error")
        for iBin in range(1, MC["nominal"].GetNbinsX()+1):
            bin_content = 0
            #################
            bin_content_sqcomb = 0
            #################

            bin_content = Signal["nominal"].GetBinContent(iBin)*0.025
            #################
            bin_content_sqcomb += pow(bin_content,2)
            #################
            if MC["nominal"].GetBinContent(iBin) > 0.000001:
                bin_content = bin_content/MC["nominal"].GetBinContent(iBin)
            else:
                bin_content = 0
            MC_rel["lumi"].SetBinContent(iBin, bin_content)


            bin_content = MC["nominal"].GetBinError(iBin)
            #################
            bin_content_sqcomb += pow(bin_content,2)
            #################
            if MC["nominal"].GetBinContent(iBin) > 0.000001:
                bin_content = bin_content/MC["nominal"].GetBinContent(iBin)
            else:
                bin_content = 0
            MC_rel["stat"].SetBinContent(iBin, bin_content)

            error_up = pow( sq_combined_error["up"].GetBinContent(iBin) + bin_content_sqcomb, 0.5)
            error_down = pow( sq_combined_error["down"].GetBinContent(iBin) + bin_content_sqcomb, 0.5)
            if MC["nominal"].GetBinContent(iBin) > 0.000001:
                error_av = error_up/MC["nominal"].GetBinContent(iBin)
                if error_up > error_down:
                    error_av = error_up/MC["nominal"].GetBinContent(iBin)
                else:
                    error_av = error_down/MC["nominal"].GetBinContent(iBin)
            else:
                error_av = 0
            comb_error.SetBinContent(iBin, error_av)
            #comb_error.SetBinContent(iBin, error_up)
            for j in range(0,len(systs_up)):
                if MC_rel[systs_aux[j]].GetBinContent(iBin) > error_av or error_av < pow(10,-5):
                    print iBin, systs_aux[j], MC_rel[systs_aux[j]].GetBinContent(iBin), "Total errors:", error_av, error_up, error_down, "MC nominal:", MC["nominal"].GetBinContent(iBin)
        


        pad1 = ROOT.TPad("pad1","pad1",0,0,1,1)
        pad1.Draw()
        pad1.cd()
        pad1.SetFillColor(0)
        pad1.SetBorderMode(0)
        pad1.SetBorderSize(10)
        pad1.SetTickx(1)
        pad1.SetTicky(1)
        pad1.SetLeftMargin(0.18)
        pad1.SetRightMargin(0.05)
        pad1.SetTopMargin(0.122)
        #pad1.SetBottomMargin(0.026)
        pad1.SetBottomMargin(0.16)
        pad1.SetFrameFillStyle(0)
        pad1.SetFrameLineStyle(0)
        pad1.SetFrameLineWidth(3)
        pad1.SetFrameBorderMode(0)
        pad1.SetFrameBorderSize(10)
        if (var_log_dic[var[k]]):
            pad1.SetLogx()
            pad1.SetLogy()

        comb_error.SetLineColor(ROOT.TColor.GetColor("#000000"))
        comb_error.SetLineWidth(2)
        comb_error.SetTitle("")
        comb_error.GetXaxis().SetTitleSize(0.05)
        comb_error.GetXaxis().SetNdivisions(505)
        comb_error.GetYaxis().SetLabelFont(42)
        comb_error.GetYaxis().SetLabelOffset(0.01)
        comb_error.GetYaxis().SetLabelSize(0.04)
        comb_error.GetYaxis().SetTitleSize(0.05)
        comb_error.GetYaxis().SetTitleOffset(1.3)
        comb_error.SetMinimum(pow(10,-5))
        comb_error.GetXaxis().SetTitle("m_{col}")
        comb_error.GetYaxis().SetTitle("Relative uncertainty")
        comb_error.SetMaximum(comb_error.GetMaximum()*pow(10,4))
        comb_error.Draw("hist")

        legende=make_legend(0.5, 0.62, 0.92, 0.85)
        legende.AddEntry(comb_error, "all systematics", "l") 
        color={
            "Tau":        "#de5a6a",
            "Muon":       "#8fccff",
            "Top":        "#006633",
            "TES":        "#d89a6a",
            "MES":        "#9999cc",
            "MET":        "#ffcc66",
            "mres":       "#c338e2",
            "minbias":    "#33cc00",
            "Trigger":    "#fb6781",
            "lumi":       "#ff1493",
            "fakefactor": "#cccc33",
            "stat":       "#ff6600",
            "WWPDF":      "#666699",
            "PDF":        "#0000cc",
        }
                          #"#993333",                 "#66ccff",
        for key in MC_rel.keys():
            bStop = False
            for i in range(0, len(systs_mask)):
                if key == systs_mask[i]:
                    bStop = True
                    break
            if bStop: continue
            color_string = color[key]
            MC_rel[key].SetLineColor(ROOT.TColor.GetColor(color_string))
            MC_rel[key].SetLineWidth(2)
            MC_rel[key].SetTitle("")
            MC_rel[key].Draw("histsame")
            legende.AddEntry(MC_rel[key],systs_map[key],"l")
        legende.Draw()
        comb_error.Draw("histsame")
    
        l1=add_lumi()
        l1.Draw("same")
        l2=add_CMS()
        l2.Draw("same")
        l3=add_Preliminary()
        l3.Draw("same")
        comb_error.Draw("histsame")
    
        pad1.RedrawAxis()
        
        finalstate  = ROOT.TLegend(0.21, 0.52+0.013, 0.43, 0.70+0.155)
        finalstate.SetBorderSize(   0 )
        finalstate.SetFillStyle(    0 )
        finalstate.SetTextAlign(   12 )
        finalstate.SetTextSize ( 0.06 )
        finalstate.SetTextColor(    1 )
        #finalstate.SetTextFont (   41 )
        finalstate.SetHeader("#mu #tau")
        finalstate.Draw("same")


        c.cd()
        pad1.Draw()
    
        ROOT.gPad.RedrawAxis()
        
        c.Modified()
        c.SaveAs("Relative_sys"+"_"+signal_name+".pdf")
        #c.SaveAs("Relative_sys_mask1.pdf")
        #c.SaveAs("Relative_sys_mask2.pdf")


