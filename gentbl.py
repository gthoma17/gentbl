##line parms:
##    c = conditional
##    h = heading
##    l = link
##    3c = 3 col format. second parm is the fname of date used in col 3
##    cl = conditional link, sometimes link, sometimes not
##    ic = inline conditional, first parm is left text, second two are conditional for right field
##seperate multiple parameters with commas

def process( line ):
    outString = ""
    line = line.rstrip()
    parms = line.split(',')
    fname = parms[0]
    if 'c' in parms:
        outString += " DC C'{{if " + fname +"_DATA}}'\n"
    if 'h' in parms:
	outString += " DC C'<div class=\"group-heading\">{{:" + fname +"_DATA}}</div>'\n"
     
    else:
        outString += " DC C'<div class=\"group-row\">'\n"
        outString += " DC C'<span class=\"group-desc\">{{:" + fname + "_FDESC}}</span>'\n"
        if 'l' in parms:
            outString += " DC C'<a class=\"group-dataTabs\"'\n"
            outString += " DC C' id=\"{{:" + fname + "_ID}}\"'\n"
            outString += " DC C' href=\"#-\">'\n"
            outString += " DC C'{{:" + fname + "_DATA}}'\n"
            outString += " DC C'</a>'\n"
            outString += " DC C'</div>'\n"
        elif 'cl' in parms:
            outString += " DC C'{{if " + fname +"_ALINK}}'\n"
            process(fname + ",l')
            outString += " DC C'{{else}}'\n"
            process(fname)
            outString += " DC C'{{/if}}'\n" 
        elif 'ic' in parms:
            outString += " DC C'{{if " + parms[1] + "_DATA}}'\n"
            outString += " DC C'<span class=\"group-data\" id=\"{{:" + parms[1] + "_ID}}\">'\n"
            outString += " DC C'{{:" + parms[1] + "_DATA}}</span>'\n"
            outString += " DC C'{{else}}'\n"
            outString += " DC C'<span class=\"group-data\" id=\"{{:" + parms[2] + "_ID}}\">'\n"
            outString += " DC C'{{:" + parms[2] + "_DATA}}</span>'\n"
            outString += " DC C'{{/if}}'\n"
            outString += " DC C'</div>'\n"
        elif '3c' in parms:
            outString += " DC C'<span class=\"group-data\" id=\"{{:" + fname + "_ID}}\">'\n"
            outString += " DC C'{{:" + fname + "_DATA}}'\n"
            outString += " DC C' {{:" + parms[1] + "_data}}'\n"
            outString += " DC C'</span>'\n"
            outString += " DC C'</div>'\n"
        else:
            outString += " DC C'<span class=\"group-data\" id=\"{{:" + fname + "_ID}}\">'\n"
            outString += " DC C'{{:" + fname + "_DATA}}</span>'\n"
            outString += " DC C'</div>'\n"
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
    if "###NEWGROUP" in line:
        f.write("*****\n")
        f.write(" DC C'</div>'\n")
        f.write(" DC C'<div class=\"group\">'\n")
    elif "###EH" in line:
        f.write(" DC C'<div class=\"empty-heading\">{{:" + fname +"_DATA}}</div>'\n")
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


    
            
