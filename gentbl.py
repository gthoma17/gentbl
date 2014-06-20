#COPYRIGHT COMPUWARE CORPORATION
#INTERNAL USE ONLY
#YOU ARE NOT ALLOWED TO USE THIS SCRIPT OR COPY OR DISTRIBUTE OR MODIFIY THIS SCRIPT IF YOU DON'T WORK FOR COMPUWARE
#I would release this under an open source (apache) lisence but compuware owns all the code I write that is 
#directly related to work (also my soul)
#@author SDKELL,GTHOMAS,PNAMBIAR
#
#gentbl.py: Parses a command file of a specific syntax to generate corresponding html and jsrender code to create an html page
#       inputs: An ascii encoded file, with one FNAME and parameter per line, corresponding to one element, in the format as follows:
#               FNAME,LINEPARAMETERS or FNAME,LINEDIRECTIVE
#           
#               where line params can be as follows:
#                   c  = conditional
#                   h  = heading
#                   l  = link
#                   3c = 3 col format. second parm is the fname of date used in col 3
#                   cl = conditional link, sometimes link, sometimes not
#                   ic = inline conditional, first parm is left text, second two are conditional for right field
#                   NO PARAMS = normal element in a table/group 
##seperate multiple parameters with commas
#
#              where line directives can be as follows:
#                    ###NEWGROUP = creates a new group, no parms needed
#                    ###EMPTHEAD = creates new empty header, no parms needed
#                    ###FIXEDPRO = creates new fixed pro field, fname after comma indicates where data comes from
#       outputs: 
#               html.txt: an html file that creates a web page corresponding to a screen def.
#       returns: none.




###################################################################
# link(fname):
#           This function creates html for a link in a group
# inputs:
#           FNAME - the fname corresponding to the data that we 
#                   wanted to display
# outputs:
#           none
# returns:
#           outString: the output string to write to the file 
def link( fname ):
    outString = ""
    outString += " DC C'<a class=\"group-dataTabs\"'\n"
    outString += " DC C' id=\"{{:" + fname + "_ID}}\"'\n"
    outString += " DC C' href=\"#-\">'\n"
    outString += " DC C'{{:" + fname + "_DATA}}'\n"
    outString += " DC C'</a>'\n"
    return outString

###################################################################
# heading(fname):
#           This function creates html for a heading to a group
# inputs:
#           FNAME - the fname corresponding to the data that we 
#                   wanted to display
# outputs:
#           none
# returns:
#           the output string to write to the file 
def heading ( fname ):
    return " DC C'<div class=\"group-heading\">{{:" + fname +"_DATA}}</div>'\n"
 
###################################################################
# threeCol(fname):
#           This function creates html for a row in a group that has
#                   mupltiple collumns in the data section
# inputs:
#           FNAME - the fnames corresponding to the data that we 
#                   wanted to display
# outputs:
#           none
# returns:
#           the output string to write to the file 
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

###################################################################
# condLink(fname):
#           This function creates html for a link that may or may
#                   may not show on the screen depending upon 
#                   a condition
# inputs:
#           FNAME - the fnames corresponding to the data that we 
#                   wanted to display
# outputs:
#           none
# returns:
#           the output string to write to the file 
def condLink ( fname ):
    outString = ""
    outString += " DC C'{{if " + fname +"_ALINK}}'\n"
    outString += link(fname)
    outString += " DC C'{{else}}'\n"
    outString += genCase(fname)
    outString += " DC C'{{/if}}'\n" 
    return outString

###################################################################
# threeCol(fname):
#           This function creates html for a row in a group that has
#                   mupltiple collumns in the data section
# inputs:
#           FNAME - the fnames corresponding to the data that we 
#                   wanted to display
# outputs:
#           none
# returns:
#           the output string to write to the file 
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
###################################################################
# genCase(fname)
#           This function does the general case. It puts the fname
#                   as a descriptor in a table, with the fname's 
#                   data in the second collumn of the table
# inputs:
#           FNAME: - the fname corresponding to the data to be displayed
# outputs:
#           none
# returns:
#           outString: the data to be written out to file in html
def genCase ( fname ):
    outString = ""
    outString += " DC C'<span class=\"group-data\" id=\"{{:" + fname + "_ID}}\">'\n"
    outString += " DC C'{{:" + fname + "_DATA}}</span>'\n"
    return outString
        
###################################################################
# process(fname)
#           handles processing of an output line
# inputs: 
#           line - a string, corresponding to some data to be written out
# outputs:
#           none
# returns:
#           a statement wrapped in DC C statements with appropriate formatting  
#           to actually be written out to file
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
        outString += " DC C'</div>'\n"
    if 'c' in parms:
        outString += " DC C'{{/if}}'\n"
    outString += "*\n"
    return outString

import fileinput
import sys

###################################################################
# MAIN METHOD
#            this main method mainly writes out prefix, post and 
#            calls sub functions to generate html in between header
#            and close of the file
# inputs: see head of file
#
# outputs: see head of file
#
# returns: none. see head of file
#
print sys.argv[1]
f = open("html.txt","w")
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
        f.write("DC C'<div class=\"fixedPro\">{{:" + fname +"_DATA}}</div>'\n")
    if "###NEWGROUP" in line:
        f.write("*****\n")
        f.write(" DC C'</div>'\n")
        f.write(" DC C'<div class=\"group\">'\n")
    elif "###EMPTHEAD" in line:
        f.write(" DC C'<div class=\"group-heading-empty\">{{:" + fname +"_DATA}}</div>'\n")
        f.write("*\n")
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


    
            
