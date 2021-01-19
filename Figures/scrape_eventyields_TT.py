#!/usr/bin/env python
import ROOT
import re
from array import array


file_2016=ROOT.TFile("../../MuTauHighMass/Figures/histos_highmassmutau_CR100.root","r")
file_2017=ROOT.TFile("../../MuTauHighMass_2017/Figures/histos_highmassmutau_CR100.root","r")
file_2018=ROOT.TFile("../../MuTauHighMass_2018/Figures/histos_highmassmutau_CR100.root","r")


process=[
"data",
"TT",
"ST",
"DY",
"VV",
"faketau",
]

process_map={
"data"    : "Obs.",
"TT"      : "\\ttbar",
"ST"      : "ST",
"DY"      : "DY",
"VV"      : "Diboson",
"faketau" : "Jet BG",
}

years=[
"2016",
"2017",
"2018",
]

years_map={
"2016" : file_2016,
"2017" : file_2017,
"2018" : file_2018,
}


file_out=open("eventyields_TT.tex", "w")
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
header+="\\begin{tabular}{|l|l|l|l|l|l|l|}\n"
header+="\\hline\n"

file_out.write(header)
file_out.write("\\multirow{2}{*}{Process} & \\multicolumn{2}{c|}{2016} & \\multicolumn{2}{c|}{2017} & \\multicolumn{2}{c|}{2018} \\\\\n")
#file_out.write("\\hline\n")
file_out.write(" & \\mT $>$ 120 GeV & \\mT $<$ 120 GeV & \\mT $>$ 120 GeV & \\mT $<$ 120 GeV & \\mT $>$ 120 GeV & \\mT $<$ 120 GeV \\\\\n")
file_out.write("\\hline\n")

total_MtLow = {}
total_MtHigh = {}

for l in range (0,len(years)):
    total_MtHigh[years[l]] = 0
    total_MtLow[years[l]] = 0

for k in range (0,len(process)):
    file_out.write(process_map[process[k]]+" ")
    for l in range (0,len(years)):
        header = "nominal/"+process[k]+"_nominal_sign_"
        if years[l] == "2018": header = "nominal/"+process[k]+"_sign_"
        Data_MtHigh=years_map[years[l]].Get(header+"MtHigh_TT")
        Data_MtLow=years_map[years[l]].Get(header+"MtLow_TT")

        int_MtHigh=Data_MtHigh.Integral()
        if int_MtHigh<0: int_MtHigh = 0
        int_MtLow=Data_MtLow.Integral()
        if int_MtLow<0: int_MtLow = 0

        if k>0:
            total_MtHigh[years[l]] += int_MtHigh
            total_MtLow[years[l]] += int_MtLow
        file_out.write("& %s & %s " %(round(int_MtHigh, 2), round(int_MtLow, 2) ) )
    file_out.write("\\\\\n")
    if (k==0): file_out.write("\\hline\n")

file_out.write("\\hline\n")

file_out.write("Total BG ")
for l in range (0,len(years)):
    file_out.write("& %s & %s " %(round(total_MtHigh[years[l]], 2), round(total_MtLow[years[l]], 2) ) )

file_out.write("\\\\\n \\hline\n")

closer="\\end{tabular}\n"
closer+="\\end{adjustwidth}\n"
closer+="\\end{frame}\n"
closer+="\\end{document}\n"
file_out.write(closer)
file_out.close()
