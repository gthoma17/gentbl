#COPYRIGHT COMPUWARE CORPORATION
#INTERNAL USE ONLY
#YOU ARE NOT ALLOWED TO USE THIS SCRIPT OR COPY OR DISTRIBUTE OR MODIFIY THIS SCRIPT IF YOU DON'T WORK FOR COMPUWARE
#I would release this under an open source (apache) lisence but compuware owns all the code I write that is 
#directly related to work (also my soul)
#currently merely writes all fnames out to a file

##line parms:
##    c  = conditional
##    h  = heading
##    l  = link
##    3c = 3 col format. second parm is the fname of date used in col 3
##    cl = conditional link, sometimes link, sometimes not
##    ic = inline conditional, first parm is left text, second two are conditional for right field
##seperate multiple parameters with commas
##
##line directives:
##    ###NEWGROUP = creates a new group, no parms needed
##    ###EMPTHEAD = creates new empty header, no parms needed
##    ###FIXEDPRO = creates new fixed pro field, fname after comma indicates where data comes from

def link( fname ):
    outString = ""
    outString += " DC C'<a class=\"group-dataTabs\"'\n"
    outString += " DC C' id=\"{{:" + fname + "_ID}}\"'\n"
    outString += " DC C' href=\"#-\">'\n"
    outString += " DC C'{{:" + fname + "_DATA}}'\n"
    outString += " DC C'</a>'\n"
    return outString
def heading ( fname ):
    return " DC C'<div class=\"group-heading\">{{:" + fname +"_DATA}}</div>'\n"
def threeCol ( fname1, fname2 ):
    outString = ""
    outString += " DC C'<span class=\"group-data\" id=\"{{:" + fname1 + "_ID}}\">'\n"
    outString += " DC C'{{:" + fname1 + "_DATA}}'\n"
    outString += " DC C' {{:" + fname2 + "_data}}'\n"
    outString += " DC C'</span>'\n"
    outString += " DC C'<span class=\"group-data\" id=\"{{:" + fname1 + "_ID}}\">'\n"
    outString += " DC C'{{:" + fname2 + "_data}}'\n"
    outString += " DC C'</span>'\n"
    return outString
def condLink ( fname ):
    outString = ""
    outString += " DC C'{{if " + fname +"_ALINK}}'\n"
    outString += link(fname)
    outString += " DC C'{{else}}'\n"
    outString += genCase(fname)
    outString += " DC C'{{/if}}'\n" 
    return outString
def inCond ( data1, data2 ):
    outString = ""
    outString += " DC C'{{if " + data1 + "_DATA}}'\n"
    outString += " DC C'<span class=\"group-data\" id=\"{{:" + data1 + "_ID}}\">'\n"
    outString += " DC C'{{:" + data1 + "_DATA}}</span>'\n"
    outString += " DC C'{{else}}'\n"
    outString += " DC C'<span class=\"group-data\" id=\"{{:" + data2 + "_ID}}\">'\n"
    outString += " DC C'{{:" + data2 + "_DATA}}</span>'\n"
    outString += " DC C'{{/if}}'\n"
    return outString
def genCase ( fname ):
    outString = ""
    outString += " DC C'<span class=\"group-data\" id=\"{{:" + fname + "_ID}}\">'\n"
    outString += " DC C'{{:" + fname + "_DATA}}</span>'\n"
    return outString
        
def process( line ):
    outString = ""
    line = line.rstrip()
    parms = line.split(',')
    fname = parms[0]
    if 'c' in parms:
        outString += " DC C'{{if " + fname +"_DATA}}'\n"
    if 'h' in parms:
        outString += heading(fname)     
    else:
        outString += " DC C'<div class=\"group-row\">'\n"
        outString += " DC C'<span class=\"group-desc\">{{:" + fname + "_FDESC}}</span>'\n"
        if 'l' in parms:
            outString += link(fname)
        elif 'cl' in parms:
            outString += condLink (fname)
        elif 'ic' in parms:
            outString += inCond(parms[1], parms[2])
        elif '3c' in parms:
            outString += inCond(fname, parms[1])
        else:
            outString += genCase(fname)
        outString += " DC C'</div">'\n"
    if 'c' in parms:
        outString += " DC C'{{/if}}'\n"
    outString += "*\n"
    return outString

import fileinput
import sys

print sys.argv[1]
f = open("out\\" + sys.argv[1],"w")
f.write("         FDB$HTTO PREFIX,                                              +\n")
f.write("               MEMBER=!!!!!!,                                          +\n")
f.write("               FORMAT=EBCDIC,                                          +\n")
f.write("               MEMTYPE=HTML\n")
f.write("*\n")
f.write(" DC C'<div id=\"Template_Area\"></div>'\n")
f.write(" DC C'<script id=\"Template\" type=\"text/x-jsrender\">'\n")
f.write(" DC C'<div id=\"fixedArea\">'\n")
f.write("**********\n")
f.write(" DC C'<div id=\"group\">'\n")
for line in fileinput.input():
    if "###FIXEDPRO" in line:
        f.write("DC C'<div class="fixedPro">{{:" + fname +"_DATA}}</div>'\n")
    if "###NEWGROUP" in line:
        f.write("*****\n")
        f.write(" DC C'</div>'\n")
        f.write(" DC C'<div class=\"group\">'\n")
    elif "###EMPTHEAD" in line:
        f.write(" DC C'<div class=\"group-heading-empty\">{{:" + fname +"_DATA}}</div>'\n")
        f.write("*\n"
    else:
        thisLine = process(line)
        f.write(thisLine)
f.write(" DC C'</div>'\n")
f.write("**********\n")
f.write(" DC C'</div>'                            <!-- END OF FIXED -->\n")
f.write(" DC C'</script>'\n")
f.write("*\n")
f.write("         FDB$HTTO EOM\n")
f.close()
fileinput.close()


    
            
