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
# menuopt(fname):
#           This function creates html for a menuopt
# inputs:
#           FNAME - the fname corresponding to the data that we 
#                   wanted to display
# outputs:
#           none
# returns:
#           outString: the output string to write to the file 
def menuopt( fname ):
    outString = ""
    outString += " DC C'<div class=\"fixedLine\">'\n"
    outString += " DC C'<div class=\"fixFloat\">'\n"
    outString += " DC C'<span class=\"spacer\">                  </span></div>'\n"
    outString += " DC C'<div class=\"menuopt-area\">'\n"
    outString += " DC C'<a id=\"{{:" + fname + "_ID}}\" class=\"menuopt-opt\">'\n"
    outString += " DC C'{{:" + fname + "}}</a></div></div>'\n"
    outString += " DC C'<div class=\"clearBoth\"></div>'\n"
    outString += " DC C'<div class=\"fixedLine\"> </div>'\n"
    outString += " DC C'<div class=\"clearBoth\"></div>'\n"
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
# threeColNoTitle( parms ):
#           This function creates html for a three column row
#           where the third column is a single fname, with the 
#           title in front of it         
#
# inputs:
#           parms - list of parameters for the group 
# 
# outputs:
#           none
# returns:
#           the output string to write to the file 
def threeColWithTitle ( parms ):
    outString = ""
    cond = False
    if 'c' in parms:
        cond = True
        parms.remove('c')

    fname1End = parms.index("3cw") - 1
    fname2Start = fname1End + 2

    outString += rightCol(parms[:fname1End+1])
    outString += leftCol(parms[fname2Start])
    outString += rightCol(parms[fname2Start:])

    if cond:
        parms.append('c')
    return outString

###################################################################
# threeColNoTitle( parms ):
#           This function creates html for an three column row
#           where the third column is only one of multiple fnames         
#
# inputs:
#           parms - list of parameters for the group 
# 
# outputs:
#           none
# returns:
#           the output string to write to the file 

def threeColNoTitle( parms ):
    outString = ""
    globalCond = False
    globalParms = []
    theseParms = []
    lastFname = parms.index("3cn") - 1
    if parms[lastFname + 1] != parms[-1]:
        for parm in parms[lastFname+1:]:
            print parm
            globalParms.append(parm)
    outString += rightCol([parms[0]])
    for fname in parms[1:lastFname+1]:
        theseParms.append(fname)
        theseParms.extend(globalParms)
        outString += " DC C'{{if " + fname +"_DATA}}'\n"
        outString += rightCol(theseParms)
        outString += " DC C'{{/if}}'\n"
        theseParms = []
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
# inCond(fname):
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
    if 'm' in parms:
        outString += menuopt(fname)   
    else:
        outString += " DC C'<div class=\"group-row\">'\n"
        outString += leftCol(fname)
        outString += rightCol(parms)
        outString += " DC C'</div>'\n"
    if 'c' in parms:
        outString += " DC C'{{/if}}'\n"
    outString += "*\n"
    return outString

def rightCol( parms ):
    outString = ""
    fname = parms[0]
    if '3cw' in parms:
        outString += threeColWithTitle(parms)
    if '3cn' in parms:
        outString += threeColNoTitle(parms)
    elif 'l' in parms:
        outString += link(fname)
    elif 'cl' in parms:
        outString += condLink (fname)
    elif 'ic' in parms:
        outString += inCond(parms[1], parms[2])
    else:
        outString += genCase(fname)
    return outString

def leftCol( fname ):
    return " DC C'<span class=\"group-desc\">{{:" + fname + "_FDESC}}</span>'\n"

import fileinput
import sys
import os

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
#print sys.argv[1]
screenName = os.path.splitext(os.path.basename(sys.argv[1]))[0]
print "screenName: " + screenName
outFile = open(screenName + ".html","w")
outFile.write("         FDB$HTTO PREFIX,                                              +\n")
outFile.write("               MEMBER=")
outFile.write(screenName + ',')
numSpaces = 48 - len(screenName)
print numSpaces
for i in xrange(0,numSpaces):
    outFile.write(' ')
outFile.write('+\n')
outFile.write("               FORMAT=EBCDIC,                                          +\n")
outFile.write("               MEMTYPE=HTML\n")
outFile.write("*\n")
outFile.write(" DC C'<div id=\"Template_Area\"></div>'\n")
outFile.write(" DC C'<script id=\"Template\" type=\"text/x-jsrender\">'\n")
outFile.write(" DC C'<div id=\"fixedArea\">'\n")
outFile.write("**********\n")
#outFile.write(" DC C'<div id=\"group\">'\n")
for line in fileinput.input():
    if fileinput.isfirstline():
        if "###FIXEDPRO" in line:
            outFile.write(" DC C'<div class=\"fixedPro\">{{:" + fname +"_DATA}}</div>'\n")
            outFile.write(" DC C'<div id=\"group\">'\n") 
        else:
            outFile.write(" DC C'<div id=\"group\">'\n")
    elif "###FIXEDPRO" in line:
        fname = line.split(',')[0]
        outFile.write(" DC C'</div>'")
        outFile.write(" DC C'<div class=\"fixedPro\">{{:" + fname +"_DATA}}</div>'\n")
        outFile.write(" DC C'<div id=\"group\">'\n")
        continue
    if "###NEWGROUP" in line:
        outFile.write("*****\n")
        outFile.write(" DC C'</div>'\n")
        outFile.write(" DC C'<div class=\"group\">'\n")
    elif "###EMPTHEAD" in line:
        outFile.write(" DC C'<div class=\"group-heading-empty\"></div>'\n")
        outFile.write("*\n")
    else:
        thisLine = process(line)
        outFile.write(thisLine)
outFile.write(" DC C'</div>'\n")
outFile.write("**********\n")
outFile.write(" DC C'</div>'                            <!-- END OF FIXED -->\n")
outFile.write(" DC C'</script>'\n")
outFile.write("*\n")
outFile.write("         FDB$HTTO EOM\n")
outFile.close()
fileinput.close()


    
            
