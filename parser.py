#!/c/Python27/python
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
    three_col_withFound = False
    three_col_with = '/*->3ColWithFDesc<-*/'
    three_col_withoutFound = False
    three_col_without = '/*->3ColWithoutFDesc<-*/'
    
    if line[0] == ';' or line[0] == '*':    # screen def lines with ; are comments
        return []                           # ignoring lines starting with * for now

    line = line[:72]                           #remove elements after col 72
    
    if fixed_pro in line:
        fixedProFound = True
        #print "found fixed pro"
        my_list = list(line)
        fp_index = line.find(fixed_pro)
        #print fp_index
        my_list[fp_index] = ' '
        my_list[fp_index+1] = ' '
        my_list[fp_index + 14] = ' '        #replace /* and */ with blanks
        my_list[fp_index+15] = ' '
        
        line = ''.join(my_list)
        #print line

    if three_col_with in line:
        three_col_withFound = True
        #print "found fixed pro"
        my_list = list(line)
        col_index = line.find(three_col_with)
        #print fp_index
        my_list[col_index] = ' '
        my_list[col_index+1] = ' '
        my_list[col_index + 19] = ' '        #replace /* and */ with blanks
        my_list[col_index+20] = ' '
        
        line = ''.join(my_list)
        #print line


    if three_col_without in line:
        three_col_withoutFound = True
        #print "found fixed pro"
        my_list = list(line)
        col_index = line.find(three_col_without)
        #print fp_index
        my_list[col_index] = ' '
        my_list[col_index+1] = ' '
        my_list[col_index + 22] = ' '        #replace /* and */ with blanks
        my_list[col_index+23] = ' '
        
        line = ''.join(my_list)
        #print line


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

    #if fixedProFound or three_col_withFound or three_col_withoutFound:
    #    print tokenized_list

    return tokenized_list

############################################################################################
# doCases( localStack, globalStack, prevPos, prevPrevPos ):
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
#           outputStack: python list containing all out the parsed output to this point
#           prevPos: the position data from the last displayable field
#           prevPrevPos: the position data from the second to last field
#  outputs:
#           none
# returns: a specially formatted string that is used as a command sequence for html building
def doCases( localStack, globalStack, outputStack, prevPos, prevPrevPos ):
    fieldStart = -1
    #get fname, if no fname return nothing
    outString = ""
    outList = []
    if (
            'FNAME' in localStack                #only do stuff if theres an fname
            and not hasTag(globalStack, 'TABLE') #which isn't in a table 
            and not hasTag(globalStack, 'DP')    #and isn't in a DP
        ):
        if 'HEX' in localStack:
            fieldStart = localStack.index('HEX')
        elif 'BIN' in localStack:
            fieldStart = localStack.index('BIN')
        elif 'CHAR' in localStack:
            fieldStart = localStack.index('CHAR')
        elif 'LITERAL' in localStack:
            fieldStart = localStack.index('LITERAL')
        elif 'CHOICE' in localStack:
            fieldStart = localStack.index('CHOICE')
        elif 'PACK' in localStack:
            fieldStart = localStack.index('PACK')
        elif 'TM' in localStack:
            fieldStart = localStack.index('TM')

        #HEADER CASE
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
            fname = localStack[localStack[fieldStart:].index('FNAME') + 2]
            #print fname
            outList.append(fname)
            #FIXED PRO  CASE
            if '->fixedPro<-' in localStack:
                outList.append('###FIXEDPRO')
            if (getPos(localStack) == "+0" or getPos(localStack) == prevPos) and (prevPos != None):
                #print "found suspicious prevPos"
                #INLINE CONDITIONAL CASE
                if prevPos == "+0" or prevPos == prevPrevPos:
                    if 'IF' in globalStack:
                        if globalStack[globalStack.index('IF') + 1] == '{':
                            if len(outputStack) != 0:
                                if ',c' in outputStack[-1] or ',l' in outputStack[-1]:
                                    sisterFname = outputStack.pop().split(',')[0]
                                    parent = outputStack.pop()
                                    parentFname = parent.split(',')[0]
                                    appendString = parentFname + ',' + sisterFname + ',' + fname + ',ic'
                                    if ',c' in parent:
                                        appendString += ",c"
                                    outputStack.append(appendString)
                                    return ""
                #3 Column Conditional where you want to show the FDesc (eg. |VALUE| 0xF | Decimal: 15|)
                elif '->3ColWithFDesc<-' in localStack:
                    #print "HIT! " + fname + " " + getPos(localStack) + " " + prevPos
                    #print outputStack
                    if len(outputStack) != 0:
                        last = outputStack.pop().split(',')
                        #print last
                        newStr = last[0]
                        if ',l' in last:
                            newStr += ',l'
                        if ',c' in last:
                            newStr += ',l'
                        newStr += ",3cw," + fname
                        outputStack.append(newStr)
                        return ""

                #3 Column Conditional where you don't want to show the FDesc (eg. |REASONCODE x234| CC_YOU_SUCK|) 
                # Typically in  these cases the data is the CC type usually in a vlist
                if 'CHOICE' in localStack:
                    #you have more than 1024 options in your vlist
                    if prevPos == "+0" or prevPos == prevPrevPos:
                        last = outputStack.pop().split(',')
                        last.insert(-1,(fname ))
                        strOut =  ','.join(last)
                        outputStack.append(strOut)
                        return ""
                    #only one vlist... so only 2 fnames to deal with
                    else:
                        last = outputStack.pop().split(',')
                        newStr = last[0]
                        if ',l' in last:
                            newStr += ',l'
                        if ',c' in last:
                            newStr += ',c'
                        newStr += "," + fname + ",3cn"
                        outputStack.append(newStr)
                        return ""
            #all kinds of link logic
            if 'ATTR' in localStack:
                attrStart = localStack.index('ATTR') + 2
                attrEnd = attrStart + localStack[attrStart:].index("}")
                if 'TABS' in localStack[attrStart:attrEnd]:
                    outList.append("l")
                    #Data fnames can sometimes be conditionally links.
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

        #is my element in general a conditional, and is it possible I won't be shown on the screen a all?
        if 'IF' in globalStack:
            if globalStack[globalStack.index('IF') + 1] == '{':
                outList.append("c")

    elif 'MENUOPT' in localStack:
        fieldStart = localStack.index('MENUOPT')
        
        if not 'SEL' in localStack:
            return ""
        else:
            new_string = 'MOPT'
            selector = localStack[localStack.index('SEL')+2]
            if int(selector) < 10:
                new_string += '0'
            new_string += selector
            outList.append(new_string)
            outList.append('m')
                
    else: 
        return ""
    outString = ",".join(outList)
    return outString

#######################################################################################################################
#  getPos( localStack )
# This is the get position method. Gets the position data from the local stack and then returns it.
#
# inputs:
#           The stack whos position data is to be returned
# outputs:
#           None
# returns:
#           The position data contained in the input stack
def getPos( localStack ):
    if 'POS' in localStack:
        posData = localStack[localStack.index('POS') + 2]
        posRow = posData.split(',')[0]
        return posRow
    else:
        return None

#######################################################################################################################
#  hasTag( stack, tag )
# This is the get position method. Gets the position data from the local stack and then returns it.
#
# inputs:
#           The stack to check
#           The tag to look for
# outputs:
#           None
# returns:
#           Boolean, whether or not the tag is in the stack
def hasTag( stack, tag):
    #print "looking for: " + tag
    #print "inside: " + str(stack)
    if tag in stack and stack[stack.index(tag)+1] == '{':
        #print "returning true"
        return True
    else:
        return False
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
#global stack
globalStack = []
#local stack based on function we're in
localStack = []
prevPos = None
prevPrevPos = None
#output for the current group
groupOutput = []
#output for current screen
screenOutput = []
#output list for all screens
allOutput = []
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
    #print lineList
    if ':SCREEN' in lineList:
        if lineList[lineList.index(':SCREEN') + 2] == 'NAME':
            #print lineList[lineList.index(':SCREEN') + 4]
            if len(screenOutput) != 0:
                allOutput.append(screenOutput)
                screenOutput = []
            thisScreen = lineList[lineList.index(':SCREEN') + 4]
            screenOutput.insert(0,thisScreen)
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
                        or popped == 'CHOICE'
                        or popped == 'MENUOPT'
                        or popped == 'PACK'
                        or popped == 'TM'
                    ):
                    local = False
                    compiledField = doCases(localStack, globalStack, screenOutput, prevPos, prevPrevPos)
                    if compiledField != "":
                        screenOutput.append(compiledField)
                    prevPrevPos = prevPos
                    prevPos = getPos(localStack)
                    localStack = []
                    #check parms function

            elif (
                       lineList[word] == 'HEX' 
                    or lineList[word] == 'CHAR' 
                    or lineList[word] == 'BIN' 
                    or lineList[word] == 'LITERAL' 
                    or lineList[word] == 'CHOICE'
                    or lineList[word] == 'MENUOPT'
                    or lineList[word] == 'PACK'
                    or lineList[word] == 'TM'
                ):
                local = True
                if groupOnStack:
                    prevPos = None
                    compiledField = doCases(localStack, globalStack, screenOutput, prevPos, prevPrevPos)
                    if compiledField != "":
                        screenOutput.append(compiledField)
                    localStack = []
                    groupOnStack = False
                globalStack.append(lineList[word])
                localStack.append(lineList[word])
            elif lineList[word] == 'GROUP':
                local = True
                groupOnStack = True
                #print "found group on line: "
                #print line
                #print "pre concat: " + str(screenOutput)
                screenOutput += ["###NEWGROUP"]
                #print "post concat: " + str(screenOutput)
                globalStack.append(lineList[word])
                localStack.append(lineList[word])
            else:
                globalStack.append(lineList[word])
                if local:
                    localStack.append(lineList[word])
            #print
            #print "iteration " + str(word)
            #print "Global stack: " + str(globalStack)
            #print "Local Stack:  " + str(localStack)
            #raw_input()


if len(screenOutput) != 0:
    allOutput.append(screenOutput)
    screenOutput = []
for output in allOutput:
    thisScreen = output.pop(0)
    f = open(thisScreen + ".cmdlist","w")
    print "OPENING FILE: " + thisScreen
    for field in output:
        f.write(field + "\n")
        print field
