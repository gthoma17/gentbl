#COPYRIGHT COMPUWARE CORPORATION
#INTERNAL USE ONLY
#YOU ARE NOT ALLOWED TO USE THIS SCRIPT OR COPY OR DISTRIBUTE OR MODIFIY THIS SCRIPT IF YOU DON'T WORK FOR COMPUWARE
#I would release this under an open source (apache) lisence but compuware owns all the code I write that is 
#directly related to work (also my soul)
#@author SDKEll
#currently merely writes all fnames out to a file
# TODO: 
#       GROUP{FNAME} ---> ,h  (Call Information header in MQLOPEN/CLOSE/GET/PUT etc)
#       if FNAME && b4 close parens && I have nested IF && that nested if is an ATTR{TAB} --> ,cl (MQOPTGET) - conditionally sometimes a link sometimes not
#       if Attr(TABS) --> ,l (links)
#       ALL ELSE --> just a newline (normal collumns inside of a group)
#       FNAME && no DLOC{} && if/else block following --> ,ic (inline conditional, for exapmple (MQOPTGET) - yes or no with an FDESC whether or not the case is true
   
#this leaves fixed pro (ie. USING BLAH BLAH in MQLOPEN), 3 collumn rows (Decimal line in MQLGET)  

import fileinput
import sys
import re

def tokenize_line( line ):          #pnambia2
    ''' takes a line and returns a tokenized list '''

    fixed_pro = '/*->fixedPro<-*/'   #tells us which line the programmer wants to be in fixedPro
    
    if line[0] == ';':               # screen def lines with ; are comments
        return []

    if fixed_pro in line:
        my_list = list(line)
        fp_index = line.find(fixed_pro)
        print fp_index
        my_list[fp_index] = ' '
        my_list[fp_index+1] = ' '
        my_list[fp_index + 14] = ' '        #replace /* and */ with blanks
        my_list[fp_index+15] = ' '
        
        line = ''.join(my_list)
        

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
    
    return tokenized_list

def doCases( localStack, globalStack ):
    #get fname, if no fname return nothing
    outString = ""
    print "Do cases"
    if 'FNAME' in localStack:
        outString = localStack[localStack.index('FNAME') + 2]
        if 'ATTR' in localStack:
            attrStart = localStack.index('ATTR') + 2
            attrEnd = attrStart + localStack[attrStart:].index("}")
            if 'TABS' in localStack[attrStart:attrEnd]:
                outString += ",l"
        if 'GROUP' in localStack:
            if 'HDR' in localStack:
                hdrStart = localStack.index('HDR') + 2
                hdrEnd = hdrStart + localStack[hdrStart:].index("}")
                if 'NO' not in localStack[hdrStart:hdrEnd]:
                    outString += ",h"  

    else: 
        return ""
    return outString


#######################################################################################################################
#                                      MAIN METHOD                                                                    #
#######################################################################################################################
f = open("out.txt","w")
#global stack
globalStack = []
#local stack based on function we're in
localStack = []
#output stack to hold onto output
output = []
###flags
#flag inside local area
local = False

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
                if popped == 'HEX' or popped == 'CHAR' or popped == 'BIN' or popped == 'LITERAL' or popped == 'GROUP':
                    local = False
                    compiledField = doCases(localStack, globalStack)
                    if compiledField != "":
                        output.append(compiledField)
                    localStack = []
                    #check parms function

            elif lineList[word] == 'HEX' or lineList[word] == 'CHAR' or lineList[word] == 'BIN' or lineList[word] == 'LITERAL' or lineList[word] == 'GROUP':
                local = True
                globalStack.append(lineList[word])
                localStack.append(lineList[word])
            else:
                globalStack.append(lineList[word])
                if local:
                    localStack.append(lineList[word])
            #print "iteration " + str(word)
            #print "Global stack: " + str(globalStack)
            #print "Local Stack:  " + str(localStack)
print output
