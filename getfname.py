#COPYRIGHT COMPUWARE CORPORATION
#INTERNAL USE ONLY
#YOU ARE NOT ALLOWED TO USE THIS SCRIPT OR COPY OR DISTRIBUTE OR MODIFIY THIS SCRIPT IF YOU DON'T WORK FOR COMPUWARE
#I would release this under an open source (apache) lisence but compuware owns all the code I write that is 
#directly related to work (also my soul)
#@author SDKEll, GTHOMAS,PNAMBIAR
#
#getfname.py: Parses a Screen Definition File and strips out fnames with what kind of formatting they require for a template
#       inputs: Screen Definition: this should be an ASCII file specified at the command line for this script to parse
#       outputs: A file OUT.txt with instructions for the gentbl.py script to generate html corresponding to the screen def
#       returns: None

import fileinput
import sys
import re

############################################################################################
# tokenize_line( line ):
# this function, given a string will teokenize this line into a list with each word in the file in the list.
# inputs: 
#           list: string of text expected to be a line of text from a file 
# outputs:
#           none
# returns: 
#           tokenized_list: a tokenized list of the form ['This','is','a','sentence']

def tokenize_line( line ):          #pnambia2
    ''' takes a line and returns a tokenized list '''
    fixedProFound = False
    fixed_pro = '/*->fixedPro<-*/'   #tells us which line the programmer wants to be in fixedPro
    
    if line[0] == ';':               # screen def lines with ; are comments
        return []

    if fixed_pro in line:
        fixedProFound = True
        print "found fixed pro"
        my_list = list(line)
        fp_index = line.find(fixed_pro)
        print fp_index
        my_list[fp_index] = ' '
        my_list[fp_index+1] = ' '
        my_list[fp_index + 14] = ' '        #replace /* and */ with blanks
        my_list[fp_index+15] = ' '
        
        line = ''.join(my_list)
        print line
        

    line = re.sub('/\*.*\*/', '', line) # remove any occurences of /* */
                                        # (greedy, removes largest)    
    line = line.rstrip()            #remove white space
    spaced_line = ' '
    for char in line:
        if char == '{':
            spaced_line += ' { '
        elif char == '}':
            spaced_line += ' } '    #lol, no 80 character line limit
        elif char == '@':
            spaced_line += 'a'
        elif char == '#':          #FNAME's can't have @ or #
            spaced_line += 'n'
        else:                       
            spaced_line += char

    tokenized_list = spaced_line.split(' ')
    tokenized_list = [c for c in tokenized_list if c != '']     #dat list comprehension

    if fixedProFound:
        print tokenized_list

    return tokenized_list

############################################################################################
# doCases( localStack, globalStack, previousStack ):
# This function performs a bunch of if/else logic to determine if a particular object fits
# a list of cases: 
#       GROUP{FNAME} ---> ,h  (Call Information header in MQLOPEN/CLOSE/GET/PUT etc)
#       if FNAME && b4 close parens && I have nested IF && that nested if is an ATTR{TAB} --> ,cl (MQOPTGET) - conditionally sometimes a link sometimes not
#       if Attr(TABS) --> ,l (links)
#       FNAME && no DLOC{} && if/else block following --> ,ic (inline conditional, for exapmple (MQOPTGET) - yes or no with an FDESC whether or not the case is true
#       (ie. USING BLAH BLAH in MQLOPEN), - just plain text that isn't in an HTML table - fixed pro 
#       (Decimal line in MQLGET)  -3 collumn rows 
#       ALL ELSE --> just a newline (normal collumns inside of a group or html table)
# inputs: 
#           localStack: python list type being treated as a stack of local inputs. This will be a parsed string with all data inside of a Group,Hex,Char,Bin,Literal, etc
#           globalStack:  python list being treated as a global stack. will tell you how far indented/how many curly brackets into  the screen definition you are
#           previousStack: python list - keeps ahold of the previous localstack before you. is used for cases such as 3 collum row.
#  outputs:
#           none
# returns: a specially formatted string that is used as a command sequence for html building
def doCases( localStack, globalStack ):
    fieldStart = -1
    #get fname, if no fname return nothing
    outString = ""
    outList = []
    if 'FNAME' in localStack:
        if 'HEX' in localStack:
            fieldStart = localStack.index('HEX')

        elif 'BIN' in localStack:
            fieldStart = localStack.index('BIN')
        elif 'CHAR' in localStack:
            fieldStart = localStack.index('CHAR')
        elif 'LITERAL' in localStack:
            fieldStart = localStack.index('LITERAL')
        elif 'GROUP' in localStack:
            if 'HDR' in localStack:
                hdrStart = localStack.index('HDR') + 2
                hdrEnd = hdrStart + localStack[hdrStart:].index("}")
                if 'NO' not in localStack[hdrStart:hdrEnd]:
                    outString += localStack[localStack.index('FNAME') + 2] + ",h" 
                    return outString

        else:
            return ""
        if fieldStart <0:
            return ""
        else:
            outList.append(localStack[localStack[fieldStart:].index('FNAME') + 2])
            if '->fixedPro<-' in localStack:
                outList.append('###FP')
            if 'ATTR' in localStack:
                attrStart = localStack.index('ATTR') + 2
                attrEnd = attrStart + localStack[attrStart:].index("}")
                if 'TABS' in localStack[attrStart:attrEnd]:
                    outList.append("l")
                    if 'IF' in localStack[fieldStart:]:
                        ifStart = fieldStart + localStack[fieldStart:].index('IF')
                        if localStack[ifStart + 1] == '{':
                            parenCount = 1
                            position = ifStart + 1
                            while parenCount > 0:
                                position += 1 
                                if localStack[position] == '{':
                                    parenCount += 1
                                elif localStack[position] == '}':
                                    parenCount -= 1
                            ifEnd = position
                            if ifStart < attrStart and ifEnd > attrEnd:
                                outList[-1] = "cl"

        if 'IF' in globalStack:
            if globalStack[globalStack.index('IF') + 1] == '{':
                outList.append("c")
    else: 
        return ""
    outString = ",".join(outList)
    return outString


#######################################################################################################################
#  MAIN METHOD
# This is the getfname main method. It will parse a screen template, and using a few stack data structures
# calls various functions to create the command to build appropriate html for a screen.
# inputs:
#           The name of the file to be parsed needs to be passed to this file at the command line.
# outputs:
#           This function writes the command syntax for the gettbl python script into a file called out.txt in the 
#            current directory
# returns:
#           none
f = open("out.txt","w")
#global stack
globalStack = []
#local stack based on function we're in
localStack = []
previousStack = []
#output stack to hold onto output
output = []
###flags
#flag inside local area
local = False
#flag that a group is on the local stack
groupOnStack = False

#output file
#f = open("OUT." + sys.argv[1],"w+")
#for line in xrange(0,1):
for line in fileinput.input():
    #lineList = ['HEX','{','FNAME','{','GMOa','}','POS','{','+2,23,8','}','}']
    lineList = tokenize_line(line)
    #to be replaced, lineList will contain example: ['bin','{','fname','{','thisName','}', etc etc etc]
    #print lineList
    if(len(lineList) != 0):
        for word in xrange(0,len(lineList)):
            #if contains { push to global stack
            #if found a } pop off global stack
            #if pop hex bin char lit, check field stack for conditions, then clear field stack
            if '{' in lineList[word]:
                globalStack.append(lineList[word])
                if local:
                    localStack.append(lineList[word])
            elif '}' in lineList[word]:
                #pop global, check if hex, char, bin lit
                if local:
                    localStack.append(lineList[word])
                while '{' != globalStack.pop():
                    pass
                popped = globalStack.pop()
                if (
                           popped == 'HEX' 
                        or popped == 'CHAR' 
                        or popped == 'BIN' 
                        or popped == 'LITERAL' 
                        or popped == 'GROUP'
                    ):
                    local = False
                    compiledField = doCases(localStack, globalStack)
                    if compiledField != "":
                        output.append(compiledField)
                    previousStack = localStack
                    localStack = []
                    #check parms function

            elif (
                       lineList[word] == 'HEX' 
                    or lineList[word] == 'CHAR' 
                    or lineList[word] == 'BIN' 
                    or lineList[word] == 'LITERAL' 
                ):
                local = True
                if groupOnStack:
                    compiledField = doCases(localStack, globalStack)
                    if compiledField != "":
                        output.append(compiledField)
                    localStack = []
                    groupOnStack = False
                globalStack.append(lineList[word])
                localStack.append(lineList[word])
            elif lineList[word] == 'GROUP':
                local = True
                groupOnStack = True
                globalStack.append(lineList[word])
                localStack.append(lineList[word])
            else:
                globalStack.append(lineList[word])
                if local:
                    localStack.append(lineList[word])
            #print "iteration " + str(word)
            #print "Global stack: " + str(globalStack)
            #print "Local Stack:  " + str(localStack)
for field in output:
    print field
    if ',h' in field:
        print "###NEWGROUP"
        f.write("###NEWGROUP\n")
    f.write(field + "\n")
