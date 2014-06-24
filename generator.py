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
#           outList: the output string to write to the file 
def link( fname ):
    outList = []
    outList.append(" DC C'<a class=\"group-dataTabs\"'\n")
    outList.append(" DC C' id=\"{{:" + fname + "_ID}}\"'\n")
    outList.append(" DC C' href=\"#-\">'\n")
    outList.append(" DC C'{{:" + fname + "_DATA}}'\n")
    outList.append(" DC C'</a>'\n")
    return outList

###################################################################
# menuopt(fname):
#           This function creates html for a menuopt
# inputs:
#           FNAME - the fname corresponding to the data that we 
#                   wanted to display
# outputs:
#           none
# returns:
#           outList: the output string to write to the file 
def menuopt( fname ):
    outList = []
    outList.append(" DC C'<div class=\"fixedLine\">'\n")
    outList.append(" DC C'<div class=\"fixFloat\">'\n")
    outList.append(" DC C'<span class=\"spacer\">                  </span></div>'\n")
    outList.append(" DC C'<div class=\"menuopt-area\">'\n")
    outList.append(" DC C'<a id=\"{{:" + fname + "_ID}}\" class=\"menuopt-opt\">'\n")
    outList.append(" DC C'{{:" + fname + "}}</a></div></div>'\n")
    outList.append(" DC C'<div class=\"clearBoth\"></div>'\n")
    outList.append(" DC C'<div class=\"fixedLine\"> </div>'\n")
    outList.append(" DC C'<div class=\"clearBoth\"></div>'\n")
    return outList

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
    outList = []
    cond = False
    if 'c' in parms:
        cond = True
        parms.remove('c')

    fname1End = parms.index("3cw") - 1
    fname2Start = fname1End + 2

    outList += rightCol(parms[:fname1End+1])
    outList += leftCol(parms[fname2Start])
    outList += rightCol(parms[fname2Start:])

    if cond:
        parms.append('c')
    return outList

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
    outList = []
    globalCond = False
    globalParms = []
    theseParms = []
    lastFname = parms.index("3cn") - 1
    if parms[lastFname + 1] != parms[-1]:
        for parm in parms[lastFname+1:]:
            print parm
            globalParms.append(parm)
    outList += rightCol([parms[0]])
    for fname in parms[1:lastFname+1]:
        theseParms.append(fname)
        theseParms.extend(globalParms)
        outList.append(" DC C'{{if " + fname +"_DATA}}'\n")
        outList += rightCol(theseParms)
        outList.append(" DC C'{{/if}}'\n")
        theseParms = []
    return outList

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
    outList = []
    outList.append(" DC C'{{if " + fname +"_ALINK}}'\n")
    outList += link(fname)
    outList.append(" DC C'{{else}}'\n")
    outList += genCase(fname)
    outList.append(" DC C'{{/if}}'\n" )
    return outList

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
    outList = []
    outList.append(" DC C'{{if " + data1 + "_DATA}}'\n")
    outList.append(" DC C'<span class=\"group-data\" id=\"{{:" + data1 + "_ID}}\">'\n")
    outList.append(" DC C'{{:" + data1 + "_DATA}}</span>'\n")
    outList.append(" DC C'{{else}}'\n")
    outList.append(" DC C'<span class=\"group-data\" id=\"{{:" + data2 + "_ID}}\">'\n")
    outList.append(" DC C'{{:" + data2 + "_DATA}}</span>'\n")
    outList.append(" DC C'{{/if}}'\n")
    return outList
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
#           outList: the data to be written out to file in html
def genCase ( fname ):
    outList = []
    outList.append(" DC C'<span class=\"group-data\" id=\"{{:" + fname + "_ID}}\">'\n")
    outList.append(" DC C'{{:" + fname + "_DATA}}</span>'\n")
    return outList
        
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
    outList = []
    line = line.rstrip()
    parms = line.split(',')
    fname = parms[0]
    if 'c' in parms:
        outList.append(" DC C'{{if " + fname +"_DATA}}'\n")
    if 'h' in parms:
        outList += heading(fname)
    if 'm' in parms:
        outList += menuopt(fname)
    else:
        outList.append(" DC C'<div class=\"group-row\">'\n")
        outList += leftCol(fname)
        outList += rightCol(parms)
        outList.append(" DC C'</div>'\n")
    if 'c' in parms:
        outList.append(" DC C'{{/if}}'\n")
    outList.append("*\n")
    return outList

def rightCol( parms ):
    outList = []
    fname = parms[0]
    if '3cw' in parms:
        outList += threeColWithTitle(parms)
    if '3cn' in parms:
        outList += threeColNoTitle(parms)
    elif 'l' in parms:
        outList += link(fname)
    elif 'cl' in parms:
        outList += condLink (fname)
    elif 'ic' in parms:
        outList += inCond(parms[1], parms[2])
    else:
        outList += genCase(fname)
    return outList

def leftCol( fname ):
    return [" DC C'<span class=\"group-desc\">{{:" + fname + "_FDESC}}</span>'\n"]

def fileEnd():
    outList = []
    outList.append("**********\n")
    outList.append(" DC C'</div>'                            <!-- END OF FIXED -->\n")
    outList.append(" DC C'</script>'\n")
    outList.append("*\n")
    outList.append("         FDB$HTTO EOM\n")
    return outList

def fileSetup( screenName ):
    outList = []
    outList.append("         FDB$HTTO PREFIX,                                              +\n")
    memString = "               MEMBER="
    memString += (screenName.upper() + ',')
    numSpaces = 48 - len(screenName)
    for i in xrange(0,numSpaces):
        memString += ' '
    outList.append(memString + '+\n')
    outList.append("               FORMAT=EBCDIC,                                          +\n")
    outList.append("               MEMTYPE=HTML\n")
    outList.append("*\n")
    outList.append(" DC C'<div id=\"Template_Area\"></div>'\n")
    outList.append(" DC C'<script id=\"Template\" type=\"text/x-jsrender\">'\n")
    outList.append(" DC C'<div id=\"fixedArea\">'\n")
    outList.append("**********\n")
    return outList

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

#list containing all groups
allGroups = []
#list containing the info for the current group
thisGroup = []
#list containing all lines to be written to the file
outList = []


screenName = os.path.splitext(os.path.basename(sys.argv[1]))[0]

#read in whole file, allGroups is a list of lists. each list is a group, each node is a row
for line in fileinput.input():
    line = line.rstrip()
    if line == '###NEWGROUP':
        #if starting a new group, check if we need to bring a fixed pro along
        if '###FIXEDPRO' in thisGroup[-1]:
            oldFixedPro = thisGroup.pop()
            allGroups.append(thisGroup)
            thisGroup = []
            thisGroup[0] = oldFixedPro
        else:
            allGroups.append(thisGroup)
            thisGroup = []
    else:
        thisGroup.append(line)
allGroups.append(thisGroup)
fileinput.close()

print allGroups

outList += fileSetup(screenName)

for group in allGroups:
    if "###FIXEDPRO" in group[0]:
        fname = group[0].split(',')[0]
        outList.append(" DC C'<div class=\"fixedPro\">{{:" + fname +"_DATA}}</div>'\n")
        outList.append(" DC C'<div id=\"group\">'\n") 
        outList.append("*\n") 
        outList.pop(0)
    elif ",h" not in group[0]:
        outList.append(" DC C'<div id=\"group\">'\n") 
        outList.append(" DC C'<div class=\"group-heading-empty\"></div>'\n")
        outList.append("*\n") 
    else:
        outList.append(" DC C'<div id=\"group\">'\n") 
        outList.append("*\n") 

    for row in group:
        thisRow = process(row)
        outList += thisRow
    outList.append("*\n") 
    outList.append(" DC C'</div>'\n")

outList += fileEnd()
outFile = open(screenName + ".html","w")
print "outList contains " + str(len(outList)) + " lines"
for line in outList:
    outFile.write(line)
outFile.close()