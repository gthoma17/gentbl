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

def tokenize_line( line ):          #pnambia2
    ''' takes a line and returns a tokenized list '''
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


#output files
f = open("OUT." + sys.argv[1],"w+")

for line in fileinput.input():
    lineList = line.split();
    #print lineList
    if(len(lineList) != 0):
        for word in lineList:
            #does my word = FNAME{blahbla}
            if(word[0] == 'F' and word[1] == 'N' and word[2] == 'A' and word[3] == 'M' and word[4] == 'E'):
                for char in range(6,(len(word)-1)):
                    #sys.stdout.write(word[char])
                    f.write(word[char])
                #print
                # if the line contaning the FNAME also has the text HDR{YES}, then you've got a header
                for word2 in lineList:
                    if (word2 == 'HDR{YES}'):
                        f.write(",h")
                f.write("\n");

