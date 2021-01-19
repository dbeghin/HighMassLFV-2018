#! /usr/bin/python
#Code to make a script to submit jobs to the localgrid
#This code doesn't submit directly jobs to localgrid, it just produces a bunch of *.sh files
#In order to submit the jobs, you'll need to type the command "source Submit_*.sh"
#Note : your code needs to be already compiler (with a .exe extension for this to work)

import os
from datasets2018 import * #imports dataset paths: pnfn[], myname[] and myoption[] arrays 
if __name__ == "__main__":
    location=os.getcwd();
    #name of your *compiled* code (omit the .exe extension)
    code_area = "/user/dbeghin/Work/MuTauHighMass_2018/"
    code_name = "FakeRate_mumu"
    region = "CR100"
    folder = "/user/dbeghin/Work/MuTauHighMass_2018/HighMassLFVMuTau/FakeRate_mumu/"
    cms_rel = "/user/dbeghin/2nd/new/CMSSW_10_4_0_patch1/src"
    proxy = "/user/dbeghin/x509up_u$(id -u dbeghin)"
    walltime = "12:18:00"

    for jj in range(0, len(pnfn)):    
        #Main file, which you'll use to submit the jobs
        #To submit the jobs, you'll need to type "source Submit_myname.sh" in your terminal
        submit_File = open("../Submit/Submit_"+myname[jj]+".sh" , 'w')
        f=os.popen("ls -t " + pnfn[jj] + "out* | sort")   #you may want to replace "outfile" with the name of the root files found in the /pnfs folder
        dir = "dcap://maite.iihe.ac.be" +  pnfn[jj]  + "/"
        name_out =  myname[jj] + ".sh"
        outFile = open("../Jobs_to_submit/"+name_out , 'w')
        command1 = "source $VO_CMS_SW_DIR/cmsset_default.sh " + "\n"
        command1 = command1 + "mkdir "+folder+"/Out_"+myname[jj] + "\n"
        command1 = command1 + "cd "+cms_rel + "\n" #go to the top of your CMSSW release
        command1 = command1 + "eval `scram runtime -sh` " + "\n"   #load the cms environment
        command1 = command1 + "export X509_USER_PROXY="+proxy + "\n"
        command1 = command1 + "export scratchdir=$TMPDIR " + "\n"
        command1 = command1 + "cd $scratchdir" + "\n"      
        #command1 = command1 + "mkdir Reweighting" + "\n"
        #command1 = command1 + "cp "+code_area+"/Reweighting/*.root Reweighting/" + "\n"
        #command1 = command1 + "export workdir=/user/dbeghin/Work/MuTauHighMass/ " + "\n"  #Set your working directory, where the code is located
        #command1 = command1 + "cd $workdir"
        outFile.write(command1)
        command3 = "qsub -q localgrid@cream02 -o " + "../out_err/"+myname[jj] +".stdout -e " +"../out_err/"+myname[jj] +".stderr -l walltime="+walltime + "  ../Jobs_to_submit/"+name_out + "\n"  #Command to submit one job to the localgrid
        submit_File.write(command3)
        ligne=0

        files_per_job = int(filesperjob[jj])  #Set the number of root files per job
        con_nbr = 0
        con_name = ""
        scr_name = ""
        for i in f.readlines():   #f contains the root files in the /pnfs directory
            #print ligne
            ligne=ligne+1
            if ligne%files_per_job==0:   
                con_name = "Con"+str(con_nbr)+myname[jj]+".root"
                con_nbr += 1
                outFile.write("hadd -f "+con_name+" Outout*.root\n")
                outFile.write("cp  "+con_name+" \t" + folder+"/Out_"+myname[jj]+"/"+con_name+"\n")
                outFile.write("rm -f *.root\n")
                outFile.close()
                scr_name="test"+str(con_nbr)+myname[jj]
                outFile = open("../Jobs_to_submit/"+scr_name+".sh" , 'w')
                command1 = "mkdir "+folder+"/Out_"+myname[jj] + "\n"
                command1 = command1 + "source $VO_CMS_SW_DIR/cmsset_default.sh " + "\n"
                command1 = command1 + "cd "+cms_rel + "\n"
                command1 = command1 + "eval `scram runtime -sh` " + "\n"
                command1 = command1 + "export X509_USER_PROXY="+proxy + "\n"
                command1 = command1 + "export scratchdir=$TMPDIR " + "\n"
                #command1 = command1 + "export workdir=/user/dbeghin/Work/MuTauHighMass/ " + "\n"
                command1 = command1 + "cd $scratchdir" + "\n"      
                #command1 = command1 + "mkdir Reweighting" + "\n"
                #command1 = command1 + "cp "+code_area+"/Reweighting/*.root Reweighting/" + "\n"
                outFile.write(command1)
                command3 = "qsub -q localgrid@cream02 -o "+ "../out_err/"+scr_name +".stdout -e " +"../out_err/"+scr_name +".stderr -l walltime="+walltime + "  ../Jobs_to_submit/"+scr_name+".sh" + "\n"
                submit_File.write(command3)
            #Below, the command to execute your code, use the correct syntax for your own code, with all arguments (file in, file out, etc.) in the proper order
            #Note that i[0:-1] is just the name of the root file in /pnfs
            command2 = "dccp dcap://maite.iihe.ac.be"+   i[0:-1] + " $scratchdir/" + "\n"
            command2 = command2 + "cp " + code_area + code_name + ".exe $scratchdir/" + "\n"
            bare_fname = i[len(pnfn[jj]):-1]
            command2 = command2 + "\n" + "./" + code_name + ".exe " + "Outout" +str(ligne)+myname[jj]+ ".root " +   bare_fname + " " + region + " " + myoption[jj]
            #command2 = command2 + " \n"+ "cp  Out" +str(ligne)+myname[jj]+ ".root \t" + "/user/dbeghin/Work/MuTauHighMass/"+folder+"/Out_"+myname[jj]+"/Out" +str(ligne)+myname[jj]+ ".root"
            command2 = command2 + "\n rm " + bare_fname
            command2 = command2 + " \n\n\n"
            outFile.write(command2)
            
        con_name = "Con"+str(con_nbr)+myname[jj]+".root"
        outFile.write("hadd -f "+con_name+" Outout*.root\n")
        outFile.write("cp  "+con_name+" \t" + folder+"/Out_"+myname[jj]+"/"+con_name+"\n")
        outFile.write("rm -f *.root\n")
        outFile.close()
        submit_File.close()
