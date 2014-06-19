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




#######################################################################################################################
#                                      MAIN METHOD                                                                    #
#######################################################################################################################
#global stack
globalStack = []
#local stack based on function we're in
localStack = []
###flags
#flag inside local area
local = False

#output file
#f = open("OUT." + sys.argv[1],"w+")



for line in xrange(0,1):
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
                while '{' != globalStack.pop():
                    pass
                popped = globalStack.pop()
                if popped == 'HEX' or popped == 'CHAR' or popped == 'BIN' or popped == 'LITERAL':
                    local = False
                    #check parms function

            elif lineList[word] == 'HEX' or lineList[word] == 'CHAR' or lineList[word] == 'BIN' or lineList[word] == 'LITERAL':
                local = True
                globalStack.append(lineList[word])
                localStack.append(lineList[word])
            else:
                globalStack.append(lineList[word])
                if local:
                    localStack.append(lineList[word])
            #print "iteration " + str(word)
            #print "Global stack: " + str(globalStack)
            #print "Local Stack: " + str(localStack)