#!/usr/bin/env python
import ROOT
import re
from array import array


file=ROOT.TFile("histos_massresolution.root","r")

masspoints=[
"500",   
"600", 
"700", 
"800", 
"900", 
"1000",
"1100",
"1200",
"1300",
"1400",
"1500",
"1600",
"1700",
"1800",
"1900",
"2000",
"2200",
"2400",
"2600",
"2800",
"3000",
"3500",
"4000",
"4500",
"5000",
"6000",
]

file_out=open("signaleff.tex", "w")
header="\\documentclass[11pt]{beamer}\n"
header+="\\usetheme{Copenhagen}\n"
header+="\\usepackage[utf8]{inputenc}\n"
header+="\\usepackage[T1]{fontenc}\n"
header+="\\usepackage{amsmath}\n"
header+="\\usepackage{amsfonts}\n"
header+="\\usepackage{amssymb}\n"
header+="\\usepackage{changepage}\n"
header+="\\usepackage{multirow}\n\n"

header+="\\begin{document}\n"
header+="\\begin{frame}\n"
header+="\\begin{adjustwidth}{-2.5em}{-2em}\n"
#header+="\\tiny\n"
header+="\\fontsize{0.15cm}{0.17cm}\\selectfont\n"
header+="\\begin{tabular}{|l|c|c|c|c|c|c|c|c|c|c|c|}\n"
header+="\\hline\n"

file_out.write(header)
file_out.write("\\multirow{2}{*}{mass} & No discr. & \\multicolumn{2}{c|}{MVA Tight} & \\multicolumn{2}{c|}{VVLoose} & \\multicolumn{2}{c|}{VLoose} & \\multicolumn{2}{c|}{Loose} & \\multicolumn{2}{c|}{Medium} \\\\\n")
#file_out.write("\\hline\n")
file_out.write(" & events & events & ratio & events & ratio & events & ratio & events & ratio & events & ratio \\\\\n")
file_out.write("\\hline\n")

for k in range (0,len(masspoints)):
    header = "ZPrime_"+masspoints[k]
    var_in_total = header+"_weighted_events"
    var_in_nodisc = header+"_Mcol_nodisc"
    var_in_oldtight = header+"_Mcol_oldjettight"
    var_in_jetvvloose = header+"_Mcol_jetvvloose"
    var_in_jetvloose = header+"_Mcol_jetvloose"
    var_in_jetloose = header+"_Mcol_jetloose"
    var_in_jetmedium = header+"_Mcol_jetmedium"
    Data_tot=file.Get(var_in_total)
    Data=file.Get(var_in_nodisc)
    Data_old=file.Get(var_in_oldtight)
    Data_vvl=file.Get(var_in_jetvvloose)
    Data_vl=file.Get(var_in_jetvloose)
    Data_l=file.Get(var_in_jetloose)
    Data_m=file.Get(var_in_jetmedium)
        
    file_out.write("%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s \\\\\n" %(masspoints[k], round(Data.Integral(), 2), round(Data_old.Integral(), 2), round(Data_old.Integral()/Data.Integral(), 2), round(Data_vvl.Integral(), 2), round(Data_vvl.Integral()/Data.Integral(), 2), round(Data_vl.Integral(), 2), round(Data_vl.Integral()/Data.Integral(), 2), round(Data_l.Integral(), 2), round(Data_l.Integral()/Data.Integral(), 2), round(Data_m.Integral(), 2), round(Data_m.Integral()/Data.Integral(), 2) ))

file_out.write("\\hline\n")

closer="\\end{tabular}\n"
closer+="\\end{adjustwidth}\n"
closer+="\\end{frame}\n"
closer+="\\end{document}\n"
file_out.write(closer)
file_out.close()
