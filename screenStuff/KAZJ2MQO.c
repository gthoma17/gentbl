 KAZJ2MQO @GENMOD                                                       00030000
         SPACE                                                          00040000
KAZJ2MQO TITLE '- OPEN QUEUES / MQ OPTION SCREENS '                     00050000
*--------------------------------------------------------------------*  00060000
*                                                                    *  00070000
*                    COMPUWARE CONFIDENTIAL                          *  00080000
*                                                                    *  00090000
*--------------------------------------------------------------------*  00100000
*                                                                    *  00110000
*                       MAINTENANCE LOG                              *  00120000
*                                                                    *  00130000
*--------------------------------------------------------------------*  00140000
*               DESCRIPTION                  |   DATE   | WHO | CHG  *  00150000
*--------------------------------------------------------------------*  00160000
*--------------------------------------------------------------------*
* COPIED FROM MTVJ2MQO FOR AA/BATCH          | 07/23/04 | RHH |      *
*--------------------------------------------------------------------*
* AA.V11R2.5.B - WEBSPHERE MQ 2033   #181582 | 12/19/08 | DFS | @03  *  00161000
*--------------------------------------------------------------------*
* ADD VER2 MQMD FIELDS               #186182 | 01/30/09 | DFS | @04  *
*--------------------------------------------------------------------*
* AA.V11R2     - WEBSPHERE MQ 2033   #188635 | 03/27/09 | DFS | @05  *  00161000
*--------------------------------------------------------------------*
* CORRECTIONS TO MQ SCREEN DISPLAY.  #190517 | 09/15/09 | BJS | @06  *  00161000
*--------------------------------------------------------------------*
* ADD MISSING AND CORRECT EXISTING   #186109 | 12/03/09 | BJS | @07  *
*  GET MESSAGE OPTIONS (GMO).                |          |     |      *
*                                            |          |     |      *
*                                            |          |     |      *
*--------------------------------------------------------------------*
* ADDED TEMPLATE DEFINITIONS AFTER    #092616| 06/06/14 | SDK | @08  *
* SCREEN DEFINITIONS. MFD-10545              |          |     |      *
* ALSO CONFIRMED ALL CHAR,BIN,HEX,LITERAL    |          |     |      *
*--------------------------------------------------------------------*
         EJECT                                                          00220000
*--------------------------------------------------------------------*  00230000
*                                                                    *  00240000
*                    COMPUWARE CONFIDENTIAL                          *  00250000
*                                                                    *  00260000
*--------------------------------------------------------------------*  00270000
*                                                                    *  00280000
*                        PROGRAM PROLOG                              *  00290000
*                                                                    *  00300000
*--------------------------------------------------------------------*  00310000
*                                                                    *  00320000
*      PROGRAM NAME: KAZJ2MQO                                        *  00330000
*                                                                    *  00340000
*    DISTRIBUTED BY: COMPUWARE CORPORATION                           *  00370000
*                                                                    *  00380000
*          FUNCTION: DEFINE THE SCREEN DEFINITIONS FOR               *  00390000
*                         MQOGMO   - GMO DETAIL                  @01 *
*                         MQOPMO   - PMO DETAIL                  @01 *
*                         MQOPTMSG - REPORT MSG OPTIONS          @01 *
*                         MQOPTOPN - OPEN OPTIONS                @01 *
*                         MQOPTPUT - PUT MSG OPTIONS             @01 *
*                         MQOPTGET - GET MSG OPTIONS             @01 *
*                         MQOPTMAT - MATCH OPTIONS               @01 *
*                                                                    *
*        ATTRIBUTES: (Y) REENTRANT                                   *  00420000
*                    (N) AUTHORIZED                                  *  00430000
*                                                                    *  00440000
*         ARGUMENTS: N/A                                             *  00450000
*                                                                    *  00460000
*           RESULTS: N/A                                             *  00470000
*                                                                    *  00480000
*      RETURN CODES: N/A                                             *  00490000
*                                                                    *  00500000
*       ABEND CODES: N/A                                             *  00510000
*                                                                    *  00520000
*--------------------------------------------------------------------*  00530000
         EJECT                                                          00540000
*
         COPY  KAZ#MQOQ                                          @03    00560000
*
*
KAZJ2MQO FDB$CSCT                                                       00550000
*

:STREAM{ NAME{MQOPT.STRUCT} TEXT{                             /* @06 */
This is the structure identifier for the block.  It is        /* @06 */
an eyecatcher to identify the block.\P\P                      /* @06 */
This field is validated by Abend-aid for CICS and if          /* @06 */
invalid there will be a # symbol alongside it.                /* @06 */
}}                                                            /* @06 */
:END                                                          /* @06 */

:STREAM{ NAME{MQOPT.STRUCT2} TEXT{                            /* @06 */
The structure identifier for the block was                    /* @06 */
validated by Abend-AID for CICS found to be invalid.  This    /* @06 */
# symbol alongside it is used to indicate the field contains  /* @06 */
an invalid value.                                             /* @06 */
}}                                                            /* @06 */
:END                                                          /* @06 */

:STREAM{ NAME{MQOPT.VER} TEXT{                                /* @06 */
This is the version identifier for the block.\P\P             /* @06 */
The version identifier is a binary number starting            /* @06 */
at 1, and incremented each time fields are added to           /* @06 */
the structure.  This allows the version identifier            /* @06 */
to be programmatically interogated to determine if            /* @06 */
potential fields exist in the structure before                /* @06 */
that field is referenced.\P\P                                 /* @06 */
This field is validated by Abend-AID for CICS and if          /* @06 */
invalid there will be a # symbol alongside it.                /* @06 */
}}                                                            /* @06 */
:END                                                          /* @06 */

:STREAM{ NAME{MQOPT.VER2} TEXT{                               /* @06 */
The version identifier for the block was                      /* @06 */
validated by Abend-AID for CICS found to be invalid.  This    /* @06 */
# symbol alongside it is used to indicate the field contains  /* @06 */
an invalid value.                                             /* @06 */
}}                                                            /* @06 */
:END                                                          /* @06 */

:STREAM{ NAME{MQOPT.RESERVED} TEXT{                           /* @06 */
This is a reserved field. \P\P                                /* @06 */
It is not used for OS/390.                                    /* @06 */
}}                                                            /* @06 */
:END                                                          /* @06 */

:SCREEN{ NAME{MQOPQS} TITLE{Opened Queues at Dump Time}       /* @03 */ 00600000
 TEMPLATE{KAZHDTMP.MQOPQS}                                    /* @08 */
  ORG{KAZ#MQOQ}                                               /* @03 */ 00610000
  FIXED{                                                      /* @03 */ 00620000
    DP{ FNAME{F006}  DLOC{OPQSQREL} }           /* MQ RELEASE    @06 */
    CHAR{ FNAME{QMGR}  POS{1,31,4}                            /* @03 */ 01100000
      DLOC{OPQSQMGR}                                          /* @03 */ 01110000
      XNAME{QUEUE MGR NAME}                                   /* @03 */ 01120000
      FDESC{ COL{1} FILL{.}                                   /* @03 */
        TEXT{QMgr Name} }                                     /* @06 */
      HELP{The name of the queue manager that this job was    /* @03 */
           connected to at the time of the dump. \P           /* @03 */
      }                                                       /* @03 */
    }                                                         /* @03 */ 01170000
    BIN{ FNAME{QPNCNT}  POS{2,31,8}                           /* @03 */ 01100000
      DLOC{OPQSOPQ#}                                          /* @03 */ 01110000
      XNAME{OPEN QUEUES}                                      /* @03 */ 01120000
      FDESC{ COL{1} FILL{.}                                   /* @03 */
        TEXT{Number of Opened Queues} }                       /* @03 */
      HELP{The number of queues that were still open at dump time. \P   01140000
      }                                                       /* @03 */ 01160000
    }                                                         /* @03 */ 01170000
  }    /* end fixed                                              @03 */ 00630000
  TABLE{                                                      /* @03 */ 00640000
    LPE{1}  TABORG{OPQSENT} SCROLL{SYS} LOCK{2}               /* @03 */ 00650000
    ELEN{OPQSENTL}  CTR{OPQSENT#} SKIP{1}                     /* @03 */ 00660000
;                                                             /* @03 */ 00661300
    DP{ FNAME{F001}  DLOC{OPQSHNDL} }           /* HANDLE        @03 */ 00662000
    DP{ FNAME{F002}  DLOC{OPQSOPEN} }           /* OPEN OPTIONS  @03 */ 00662000
    DP{ FNAME{F003}  DLOC{OPQSGET} }            /* GET OPTIONS   @03 */ 00662000
    DP{ FNAME{F004}  DLOC{OPQSPUT} }            /* PUT OPTIONS   @03 */ 00662000
    DP{ FNAME{F005}  DLOC{OPQSQDEF} }           /* QDEF TYPE     @03 */ 00662000
;                                                             /* @03 */ 00661300
    COND{ FNAME{CURRHNDL} DLOC{OPQSFLAG}                      /* @03 */
      COMPOP{TM,OPQSCURH,O} }                                 /* @03 */
;                                                             /* @03 */ 00666000
    LCMD{ SEL{D}                                              /* @03 */ 00670000
      CMD{CPR MQCB @FF005 @FF001}                             /* @03 */ 00680000
      POS{1,12} TEXT{Queue Definition}                        /* @03 */ 00690000
      HELP{To display the queue defintions. \P                /* @03 */ 00700000
      }                                                       /* @03 */ 00730000
    }                                                         /* @03 */ 00740000
    LCMD{ SEL{*}                                              /* @03 */ 00750000
      CMD{CPR MQCB @FF005 @FF001}                             /* @03 */ 00760000
      POS{1,17} TEXT{Queue Definition}                        /* @03 */ 00770000
    }                                                         /* @03 */ 00780000
    LCMD{ SEL{H}                                              /* @03 */ 00790000
      CMD{CPR MQHI @FF001 C @FF006}                           /* @06 */ 00800000
      POS{1,40} TEXT{Handle Information}                      /* @03 */ 00810000
      HELP{To display the Handle information. \P              /* @03 */ 00820000
      }                                                       /* @03 */ 00850000
    }                                                         /* @03 */ 00860000
;                                                             /* @03 */ 00950000
;                                                             /* @03 */ 00960000
    COLUMN{ LOS{8} SKIP{1}                                    /* @03 */ 00980000
      TEXT{Handle}                                            /* @03 */ 00990000
      HEX{ FNAME{HANDLE}  POS{1,1,8}                          /* @03 */ 01000000
        IF { COND{CURRHNDL}                                   /* @03 */
           THEN { ATTR{ TABS CURR } }                         /* @03 */
           ELSE { ATTR{TABS} } }                              /* @03 */
        DLOC{OPQSHNDL}                                        /* @03 */ 01010000
        XNAME{HANDLE}                                         /* @03 */ 01020000
        COMMAND{ NAME{.DFLT}  CMD{CPR MQHI @FF001 C @FF006}   /* @06 */ 01022000
          DESC{Display Handle Information}                    /* @03 */ 01023000
          HELP{                                               /* @03 */ 01024000
          }                                                   /* @03 */ 01026000
        }                                                     /* @03 */ 01027000
        HELP{The object handle value that was returned to the program   01030000
             when the queue was opened. \P
        }                                                     /* @03 */ 01050000
      }                                                       /* @03 */ 01060000
    }                                                         /* @03 */ 01070000
    COLUMN{ SKIP{2}  LOS{8}                                   /* @03 */ 01080000
      TEXT{Queue Type}                                        /* @03 */ 01090000
      CHOICE{ FNAME{QTYPE}  POS{1,1,8}                        /* @03 */ 01100000
        IF { COND{CURRHNDL}                                   /* @03 */
           THEN { ATTR{ CURR }} }                             /* @03 */
        DLOC{OPQSQDEF}                                        /* @03 */ 01110000
        XNAME{QUEUE TYPE}                                     /* @03 */ 01120000
        LISTV{                                                /* @03 */
              VALUE{X'01','QLOCAL  '}                         /* @03 */
              VALUE{X'03','QALIAS  '}                         /* @03 */
              VALUE{X'06','QREMOTE '}                         /* @03 */
             }                                                /* @03 */
        HELP{The type of queue that was opened. \P            /* @03 */ 01140000
        }                                                     /* @03 */ 01160000
      }                                                       /* @03 */ 01170000
    }                                                         /* @03 */ 01180000
    COLUMN{ LOS{8} SKIP{1}                                    /* @03 */ 01181000
      TEXT{Open Options}                                      /* @03 */ 01182000
      HEX{ FNAME{OPENOPTS}  POS{1,1,8}                        /* @03 */ 01184000
        IF { COND{CURRHNDL}                                   /* @03 */
           THEN { ATTR{ TABS CURR } }                         /* @03 */
           ELSE { ATTR{TABS} } }                              /* @03 */
        DLOC{OPQSOPEN}                                        /* @03 */ 01186000
        XNAME{OPEN OPTIONS}                                   /* @03 */ 01187000
        COMMAND{ NAME{.DFLT}  CMD{CPR MQM2 OPN @FF002}        /* @03 */ 01189000
          DESC{Display Open Options}                          /* @03 */ 01189100
          HELP{                                               /* @03 */ 01189200
          }                                                   /* @03 */ 01189500
        }                                                     /* @03 */ 01189600
        HELP{The options that the queue manager used when the /* @03 */ 01189700
             queue was opened. \P                             /* @03 */
        }                                                     /* @03 */ 01189900
      }                                                       /* @03 */ 01190000
    }                                                         /* @03 */ 01190100
    COLUMN{ LOS{8} SKIP{1}                                    /* @03 */ 01181000
      TEXT{Get Options}                                       /* @03 */ 01182000
      HEX{ FNAME{GETOPTS}  POS{1,1,8}                         /* @03 */ 01184000
        IF { COND{CURRHNDL}                                   /* @03 */
           THEN { ATTR{ TABS CURR } }                         /* @03 */
           ELSE { ATTR{TABS} } }                              /* @03 */
        DLOC{OPQSGET}                                         /* @03 */ 01186000
        XNAME{GET OPTIONS}                                    /* @03 */ 01187000
        COMMAND{ NAME{.DFLT}  CMD{CPR MQM2 GET @FF003}        /* @03 */ 01189000
          DESC{Displays Get Options}                          /* @03 */ 01189100
        }                                                     /* @03 */ 01189600
        HELP{The options that the queue manager used for the last       01189700
             MQGET call using this queue. If there were not any MQGET
             calls using this queue, the options will be all zeros.\P
        }                                                     /* @03 */ 01189900
      }                                                       /* @03 */ 01190000
    }                                                         /* @03 */ 01190100
    COLUMN{ LOS{8} SKIP{1}                                    /* @03 */ 01181000
      TEXT{Put Options}                                       /* @03 */ 01182000
      HEX{ FNAME{PUTOPTS}  POS{1,1,8}                         /* @03 */ 01184000
        IF { COND{CURRHNDL}                                   /* @03 */
           THEN { ATTR{ TABS CURR } }                         /* @03 */
           ELSE { ATTR{TABS} } }                              /* @03 */
        DLOC{OPQSPUT}                                         /* @03 */ 01186000
        XNAME{PUT OPTIONS}                                    /* @03 */ 01187000
        COMMAND{ NAME{.DFLT}  CMD{CPR MQM2 PUT @FF004}        /* @03 */ 01189000
          DESC{Display Put Options}                           /* @03 */ 01189100
        }                                                     /* @03 */ 01189600
        HELP{The options that the queue manager used for the last       01189700
             MQPUT call using this queue. If there were not any MQPUT
             calls using this queue, the options will be all zeros.\P
        }                                                               01189900
      }                                                       /* @03 */ 01190000
    }                                                         /* @03 */ 01190100
    COLUMN{ LOS{48} SKIP{2}                                   /* @03 */ 01181000
      TEXT{Queue Name}                                        /* @03 */ 01182000
      CHAR{ FNAME{QNAME}  POS{1,1,48}                         /* @03 */ 01184000
        IF { COND{CURRHNDL}                                   /* @03 */
           THEN { ATTR{ CURR }} }                             /* @03 */
        DLOC{OPQSQNME}                                        /* @03 */ 01186000
        XNAME{QUEUE NAME}                                     /* @03 */ 01187000
        HELP{The name of the queue that was used at open time. \P       01189700
        }                                                     /* @03 */ 01189900
      }                                                       /* @03 */ 01190000
    }                                                         /* @03 */ 01190100
  } /* end-of-table                                           /* @03 */ 03090000
  TRAIL{                                                      /* @03 */ 03100000
    INSTEXTS{ POS{1,1,,1}                                     /* @03 */ 03110000
TEXT{Type a line command and press \EM(ON)Enter\EM(OFF) to process it}} 03120000
  }                                                           /* @03 */ 03130000
  HELP{This screen displays the queues that were still open when the    03140000
       dump occurred. It also allows the option to get more detailed    03150000
       information on the queues. \P\P                        /* @03 */
  }                                                           /* @03 */ 03160000
} /* end-of-screen                                               @03 */ 03170000
:END                                                          /* @03 */
:SCREEN{ NAME{MQOGMO} TITLE{GMO Detail}                       /* @03 */
 TEMPLATE{KAZHDTMP.MQOGMO}                                    /* @08 */
  ORG{KAZ#MQOQ}                                               /* @03 */
  FIXED{
    DP{ FNAME{F001}  DLOC{GPMOGMO@} }                         /* @03 */
    DP{ FNAME{F002}  DLOC{GPMOOPTN} }
    DP{ FNAME{F003}  DLOC{GPMOTYPE} }
    DP{ FNAME{F004}  DLOC{GPMOOPTM} }                         /* @03 */
    COND{ FNAME{WAITNEG1} DLOC{GPMOWAIT}                      /* @03 */
         COMPOP{CLC,X'FFFFFFFF',E} }                          /* @03 */
    COND{ FNAME{NEWFMT} DLOC{BUFFMT}                          /* @03 */
         COMPOP{CLI,'2',E} }                                  /* @03 */
;
    COND{ FNAME{VALSTRUC} DLOC{GPMOFLAG}
         COMPOP{TM,SW_IDOK,O} }
    COND{ FNAME{VALVER} DLOC{GPMOFLAG}
         COMPOP{TM,SW_VEROK,O} }
;
    COND{ FNAME{VALVER2} DLOC{GPMOFLAG}                       /* @03 */
         COMPOP{TM,SW_V2OK,O} }                               /* @03 */
    COND{ FNAME{VALVER3} DLOC{GPMOFLAG}                       /* @03 */
         COMPOP{TM,SW_V3OK,O} }                               /* @03 */
;                                                             /* @03 */
    IF { COND{NEWFMT}                                         /* @03 */
    THEN {                                                    /* @03 */
    HEX{ FNAME{GMO@}  POS{+2,25,8}                            /* @03 */
      DLOC{GPMOGMO@}                                          /* @03 */
      XNAME{GMO Address}                                      /* @03 */
      ATTR{ TABS }                                            /* @03 */
      HEXD{A,'GMO'}                                           /* @03 */
      FDESC{ COL{1} FILL{.}                                   /* @03 */
        TEXT{GMO Address}                                     /* @03 */
      }                                                       /* @03 */
      HELP{                                                   /* @03 */
The address of the Get Message Options storage block.         /* @03 */
      }                                                       /* @03 */
    } } }                                                     /* @03 */
; -----------------------------------
; FOLLOWING FIELD ADDED BY CHANGE @02
; -----------------------------------
    IF { COND{VALSTRUC}
    THEN {
       CHAR { FNAME{STRUCTID} POS{+2,25,04}
         DLOC{GPMOID}
         XNAME{Structure ID}
         FDESC{ COL{1} FILL{.}
           TEXT{Structure ID}
         }
         HELP{\IM('MQOPT.STRUCT')}
       }
    }
    ELSE {
       HEX { FNAME{STRUCTID} POS{+2,25,08}
         DLOC{GPMOID}
         XNAME{Structure ID}
         FDESC{ COL{1} FILL{.}
           TEXT{Structure ID}
         }
         HELP{\IM('MQOPT.STRUCT')}
       }
       LITERAL { FNAME{STRUCT#} POS{+0,34,01}                 /* @03 */
         TEXT{#}                                              /* @03 */
         XNAME{Structure #}
         HELP{\IM('MQOPT.STRUCT2')}
       }
    }}
; -----------------------------------
; FOLLOWING FIELD ADDED BY CHANGE @02
; -----------------------------------
    HEX { FNAME{VERSION} POS{+1,25,08}
      DLOC{GPMOVER}
      XNAME{Version Number}
      FDESC{ COL{1} FILL{.}
        TEXT{Version}
      }
      HELP{\IM('MQOPT.VER')}
    }
    IF { COND{NOT.VALVER}
    THEN {
       LITERAL { FNAME{VERSION#} POS{+0,34,01}                /* @03 */
         TEXT{#}                                              /* @03 */
         XNAME{Version Number}
         HELP{\IM('MQOPT.VER2')}
       }
    }}
; -----------------------------------
; FOLLOWING FIELD ADDED BY CHANGE @02
; -----------------------------------
    HEX{ FNAME{GMOOPT}  POS{+1,25,8}
      DLOC{GPMOOPTN}
      XNAME{GMOopt}
      ATTR{ TABS }
      COMMAND{ NAME{.DFLT} CMD{CPR MQM2 GET @FF002}
              DESC{Display GMO options} }
      FDESC{ COL{1} FILL{.}
        TEXT{Options}
      }
      HELP{
These GMO options control processing
to be used for the MQGET call. Each bit represents
a different setting which can be specified by the
application programmer.\P\P
For further information place the cursor on this field
and press <enter>.  The GMO options screen will be
displayed showing a breakdown of all the options.
      }
    }
; -------------------------------------
; FOLLOWING FIELD CHANGED BY CHANGE @02
; ------------------------------------
    BIN{ FNAME{WAITINT}  POS{+1,25,8}
      DLOC{GPMOWAIT}
      XNAME{Wait Interval}
      FDESC{ COL{1} FILL{.}
        TEXT{Wait Interval}
      }
      HELP{
This is the approximate time, expressed in milliseconds, that the MQGET
call waits for a message to arrive.  If the value is 'FFFFFFFF' then the
wait interval is unlimited and the MQGET will wait forever.
      }
    }
    IF { COND{WAITNEG1}
    THEN {
       LITERAL { FNAME{NOWAIT} POS{+0,41,14}
        TEXT{MQWI_UNLIMITED}
         XNAME{Wait Interval}
         FDESC{ COL{1} FILL{.}
           TEXT{Wait Interval}
         }
         HELP{
This indicates that the
wait interval is unlimited and the MQGET will wait forever.
         }
       }
    }
    ELSE {
        CHAR{ FNAME{WAITINT2} POS{+0,36,20}
          XNAME{Wait Interval2}
          DLOC{GPMOWAI2}
      HELP{
This is the approximate time, expressed in seconds, that the MQGET
call waits for a message to arrive.
          }
        }
    }}
    HEX{ FNAME{SIGNAL}  POS{+1,25,8}
      DLOC{GPMOSIG@}
      XNAME{Signal}
      ATTR{ TABS }
      HEXD{A,'SIGNAL'}
      FDESC{ COL{1} FILL{.}
        TEXT{Signal1}
      }
      HELP{
This is an input field that is used only in conjunction with the
MQGMO_SET_SIGNAL option; it identifies a signal that is to be
delivered when a message is available.\P\P
This field can contain the address of an Event Control Block (ECB).
      }
    }
; -----------------------------------
; FOLLOWING FIELD ADDED BY CHANGE @02
; -----------------------------------
    LITERAL { FNAME{SIGNAL2} POS{+1,25,03}
     TEXT{N/A}
      XNAME{Signal2}
      FDESC{ COL{1} FILL{.}
        TEXT{Signal2}
      }
      HELP{\IM('MQOPT.RESERVED')}
    }
    CHAR{ FNAME{QNAME}  POS{+1,25,48}
      DLOC{GPMOQNME}
      XNAME{Queue Name}
      FDESC{ COL{1} FILL{.}
        TEXT{Resolved Queue Name}
      }
      HELP{
This field is set by the queue manager to the local name of the queue
from which the message was retrieved, as defined to the local queue
manager.
      }
    }
; ------------------------------------
; FOLLOWING FIELDS ADDED BY CHANGE @02
; ------------------------------------
    IF { COND{VALVER2}
    THEN {
      HEX{ FNAME{MATCHOPT}  POS{+2,25,8}
        DLOC{GPMOOPTM}
        XNAME{Matchopt}
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT} CMD{CPR MQM2 MAT @FF004}
                DESC{Display match options} }
        FDESC{ COL{1} FILL{.}
          TEXT{Match Options}
        }
        HELP{
These match options control selection criteria
to be used for the MQGET call. Each bit represents
a different setting which can be specified by the
application programmer.\P\P
For further information place the cursor on this field
and press <enter>.  The match options screen will be
displayed showing a breakdown of all the options.\P\P
This field is only shown if the GMO version is at least 2.
        }
      }
      LITERAL { FNAME{GRPSTAT} POS{+1,25,03}
       TEXT{N/A}
        XNAME{Grpstat}
        FDESC{ COL{1} FILL{.}
          TEXT{Group Status}
        }
        HELP{\IM('MQOPT.RESERVED')}
      }
      LITERAL { FNAME{SEGSTAT} POS{+1,25,03}
       TEXT{N/A}
        XNAME{Segstat}
        FDESC{ COL{1} FILL{.}
          TEXT{Segment Status}
        }
        HELP{\IM('MQOPT.RESERVED')}
      }
      LITERAL { FNAME{SEGMENT} POS{+1,25,03}
       TEXT{N/A}
        XNAME{Segment}
        FDESC{ COL{1} FILL{.}
          TEXT{Segmentation}
        }
        HELP{\IM('MQOPT.RESERVED')}
      }
    }}
; ------------------------------------
; FOLLOWING FIELDS ADDED BY CHANGE @02
; ------------------------------------
    IF { COND{VALVER3}
    THEN {
      LITERAL { FNAME{RESERVE1} POS{+2,25,03}
       TEXT{N/A}
        XNAME{Reserve1}
        FDESC{ COL{1} FILL{.}
          TEXT{Reserved1}
        }
        HELP{\IM('MQOPT.RESERVED')}
      }
      CHAR{ FNAME{MSGTOKEN}  POS{+1,25,16}
        DLOC{GPMOTOKN}
        XNAME{Msgtoken}
        ATTR{ TABS }
        FDESC{ COL{1} FILL{.}
          TEXT{Message Token}
        }
        HELP{
This field is used in association with the MQMO_MATCH_MSG_TOKEN
option.  If that option is specified
then the message to be retrieved
must have a mesage token that matches the value of the
MsgToken field in the MQGMO structure of the MQGET call.
        }
      }
      LITERAL { FNAME{RETLENG} POS{+1,25,03}
       TEXT{N/A}
        XNAME{Retleng}
        FDESC{ COL{1} FILL{.}
          TEXT{Returned Length}
        }
        HELP{\IM('MQOPT.RESERVED')}
      }
    }}
  }   /* end-of-fixed  */
  HELP{
This screen displays information interpreted from the WebSphere MQ
Get-Message Options (GMO) structure.
  }
} /* end-of-screen */
:END                                                          /* @03 */ 03180000

*                                                               @03
*   --------------------------------------------------------    @03
*   FOLLOWING STREAMS ADDED FOR ABEND-AID E-BUSINESS            @03
*   EDITION RELEASE 2.0. FOR SCREEN MQOPTGET.                   @03
*   --------------------------------------------------------    @03

:STREAM{ NAME{MQOPTGET.GMO} TEXT{
\EM(ON)GMO Options\EM(OFF)\P\P
The value of the Get Message Options.\P\P  Each bit represents
a different setting which can be specified by the application
programmer.  The settings are broken down and shown on the
following lines on the terminal.
}}
:END

:STREAM{ NAME{MQOPTGET.WAIT} TEXT{
\EM(ON)MQGMO_WAIT\EM(OFF)\P\P
If this option is set then
the application is to wait until a suitable message arrives.\P\P
The maximum wait interval may be shown on the GMO Detail screen.
}}
:END

:STREAM{ NAME{MQOPTGET.NOWAIT} TEXT{
\EM(ON)MQGMO_NO_WAIT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will return immediately to the application if    /* @06 */
there is no suitable message. \P\P                            /* @05 */
This is the opposite of the
\EM(on)MQGMO_WAIT\EM(off) option.\P\P
There is no bit setting defined for this option because
it is only defined to aid program documentation.  Therefore
Abend-AID for WebSphere MQ cannot determine if this
option was specified.  Instead Abend-AID for
WebSphere MQ examines the opposite setting
\EM(on)MQGMO_WAIT.\EM(off)\P\P
If \EM(ON)MQGMO_WAIT\EM(OFF) was
specified then \EM(ON)NO\EM(OFF) will be displayed
for \EM(on)MQGMO_NO_WAIT,\EM(off) otherwise
\EM(ON)YES\EM(OFF) will be shown.
}}
:END

:STREAM{ NAME{MQOPTGET.SYNC} TEXT{
\EM(ON)MQGMO_SYNCPOINT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will get the message with syncpoint control.\P\P /* @06 */
This means the message will be marked unavailable to other
applications, but will not be deleted until the unit of
work is committed.  If the unit of work is backed out the
message will be made available to other applications.\P\P
This option is the opposite of
\EM(on)MQGMO_NO_SYNCPOINT.\EM(off)\P\P
If neither \EM(on)MQGMO_SYNCPOINT\EM(off)
nor \EM(on)MQGMO_NO_SYNCPOINT\EM(off)
is specified the default depends on
the environment.\P\P  On OS/390 the default is
\EM(on)MQGMO_SYNCPOINT,\EM(off) but on most other environments
it is \EM(on)MQGMO_NO_SYNCPOINT.\EM(off)
}}
:END

:STREAM{ NAME{MQOPTGET.SYNC2} TEXT{
\EM(ON)MQGMO_SYNCPOINT_IF_PERSISTENT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will use syncpoint or no_syncpoint depending on  /* @06 */
whether or not the message is persistent.\P\P
Persistent messages
will be handled as if \EM(on)MQGMO_SYNCPOINT\EM(off) had
been specified, and
not persistent messages will be handled as if
\EM(on)MQGMO_NO_SYNCPOINT\EM(off) had been specified.
}}
:END

:STREAM{ NAME{MQOPTGET.SYNC3} TEXT{
\EM(ON)MQGMO_NO_SYNCPOINT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will get the message without                     /* @06 */
syncpoint control.\P\P                                        /* @05 */
This means the message, except for browse requests, will be
immediately deleted from the queue.\P\P
This option is the opposite of
\EM(on)MQGMO_SYNCPOINT.\EM(off)\P\P
If neither \EM(on)MQGMO_SYNCPOINT\EM(off) nor
\EM(on)MQGMO_NO_SYNCPOINT\EM(off)
is specified the default depends on
the environment.\P\P  On OS/390 the default is
\EM(on)MQGMO_SYNCPOINT,\EM(off) but on most other environments
it is \EM(on)MQGMO_NO_SYNCPOINT.\EM(off)
}}
:END

:STREAM{ NAME{MQOPTGET.SKIP} TEXT{
\EM(ON)MQGMO_MARK_SKIP_BACKOUT\EM(OFF)\P\P
If this option is set then
if the unit is work is backed out the message will
\EM(on)not\EM(off) be returned to the queue.\P\P
This allows a unit of work which determines it cannot
complete successfully to roll back all other updates
without returning the message to the queue.  The application
can then perform error processing.  If the message were
returned to the queue, the error situation could occur again
next time the message is retrieved.\P\P
If \EM(ON)MQGMO_MARK_SKIP_BACKOUT\EM(OFF) is used
then \EM(ON)MQGMO_SYNCPOINT\EM(OFF) is also required.
}}
:END

:STREAM{ NAME{MQOPTGET.BROWSEF} TEXT{
\EM(ON)MQGMO_BROWSE_FIRST\EM(OFF)\P\P
If this option is set then
the queue will be browsed from the start of the queue. \P\P
The message returned to the application will remain on the queue.
}}
:END

:STREAM{ NAME{MQOPTGET.BROWSEN} TEXT{
\EM(ON)MQGMO_BROWSE_NEXT\EM(OFF)\P\P
If this option is set then
the next message on the queue will be retrieved. \P\P
The message returned to the application will remain on the queue.
}}
:END

:STREAM{ NAME{MQOPTGET.CURSOR} TEXT{
\EM(ON)MQGMO_MSG_UNDER_CURSOR\EM(OFF)\P\P
If this option is set then
the message most recently retrieved from that queue using
\EM(on)MQGMO_BROWSE_FIRST\EM(off)
or \EM(on)MQGMO_BROWSE_NEXT\EM(off)
will be retrieved and removed from the queue.\P\P
The get may fail if the most recently browsed message is
no longer available because it has been retrieved by this
or another application.
}}
:END

:STREAM{ NAME{MQOPTGET.TRUNC} TEXT{
\EM(ON)MQGMO_ACCEPT_TRUNCATED_MSG\EM(OFF)\P\P
If this option is set then
even if the message buffer is too small to hold the complete
message, processing will still complete successfully.\P\P
The message will be truncated to fit the buffer, the message
may be removed from the queue, and the return code
\EM(on)MQRC_TRUNCATED_MSG_ACCEPTED\EM(off) will be issued.
}}
:END

:STREAM{ NAME{MQOPTGET.SIGNAL} TEXT{
\EM(ON)MQGMO_SET_SIGNAL\EM(OFF)\P\P
If this option is set then
if there is no message to be retrieved WebSphere MQ can       /* @06 */
send a signal to the application later when a message         /* @05 */
is available.\P\P                                             /* @05 */
This allows an application to wait for messages on more than
one queue, or to perform other processing until a message
arrives.
}}
:END

:STREAM{ NAME{MQOPTGET.QUIESCE} TEXT{
\EM(ON)MQGMO_FAIL_IF_QUIESCING\EM(OFF)\P\P
If this option is set then
the MQGET request will fail if the queue manager or the
CICS connection is quiescing.
}}
:END

:STREAM{ NAME{MQOPTGET.CONVERT} TEXT{
\EM(ON)MQGMO_CONVERT\EM(OFF)\P\P
If this option is set then
the retrieved message is to be converted into the format
required by the application.\P\P
Conversion between standard
formats can be performed by WebSphere MQ code, or a user      /* @06 */
exit can be invoked to perform the conversion.                /* @05 */
}}
:END

:STREAM{ NAME{MQOPTGET.LOCK} TEXT{                            /* @07 */
\EM(ON)MQGMO_LOCK\EM(OFF)                                     /* @07 */
\P\P                                                          /* @07 */
If this option is specified, WebSphere MQ locks a browsed     /* @07 */
message, so that it is hidden to any other handle open for    /* @07 */
the same queue.                                               /* @07 */
\P\P                                                          /* @07 */
Only one message can be locked for a queue, which can be      /* @07 */
either a physical message or a logical message. If the        /* @07 */
\EM(on)MQGMO_COMPLETE_MSG\EM(off) option is specified, all    /* @07 */
message segments that make up the logical message are also    /* @07 */
locked. Otherwise, only a single message segment is locked.   /* @07 */
\P\P                                                          /* @07 */
}}                                                            /* @07 */
:END                                                          /* @07 */

:STREAM{ NAME{MQOPTGET.UNLOCK} TEXT{                          /* @07 */
\EM(ON)MQGMO_UNLOCK\EM(OFF)                                   /* @07 */
\P\P                                                          /* @07 */
If this option is specified, WebSphere MQ unlocks a           /* @07 */
previously-locked message.                                    /* @07 */
\P\P                                                          /* @07 */
}}                                                            /* @07 */
:END                                                          /* @07 */

:STREAM{ NAME{MQOPTGET.BROWSEU} TEXT{                         /* @07 */
\EM(ON)MQGMO_BROWSE_MSG_UNDER_CURSOR\EM(OFF)                  /* @07 */
\P\P                                                          /* @07 */
If this option is specified, WebSphere MQ gets a copy of      /* @07 */
the message that was last retrieved by a MQGET browse         /* @07 */
request, specifically the message that is currently pointed   /* @07 */
to by the browse cursor.  The current position of the         /* @07 */
browse cursor is unchanged by this call.                      /* @07 */
\P\P                                                          /* @07 */
The call will fail if the message is no longer available on   /* @07 */
the queue or if a MQGET browse request has not been issued    /* @07 */
since the queue was opened.  The MatchOptions field is        /* @07 */
ignored when this MQGET option is used.                       /* @07 */
\P\P                                                          /* @07 */
}}                                                            /* @07 */
:END                                                          /* @07 */

:STREAM{ NAME{MQOPTGET.LOGICAL} TEXT{                         /* @07 */
\EM(ON)MQGMO_LOGICAL_ORDER\EM(OFF)                            /* @07 */
\P\P                                                          /* @07 */
If this option is specified, WebSphere MQ retrieves browsed   /* @07 */
messages from the queue in their logical order. Grouped       /* @07 */
messages are retrieved in the order of their message          /* @07 */
sequence numbers and segmented messages are retrieved in      /* @07 */
the order of their segment offsets.                           /* @07 */
\P\P                                                          /* @07 */
This option must be specified on each subsequent MQGET call   /* @07 */
to continue to browse messages in logical order. Otherwise,   /* @07 */
messages are browsed in the order they occur in the queue,    /* @07 */
or their physical order.                                      /* @07 */
\P\P                                                          /* @07 */
}}                                                            /* @07 */
:END                                                          /* @07 */

:STREAM{ NAME{MQOPTGET.COMPLET} TEXT{                         /* @07 */
\EM(ON)MQGMO_COMPLETE_MSG\EM(OFF)                             /* @07 */
\P\P                                                          /* @07 */
If this option is specified, WebSphere MQ will only return    /* @07 */
a complete logical message.  All message segments are         /* @07 */
merged together by the queue manager prior to returning       /* @07 */
them to the application.                                      /* @07 */
\P\P                                                          /* @07 */
}}                                                            /* @07 */
:END                                                          /* @07 */

:STREAM{ NAME{MQOPTGET.ALLMSGS} TEXT{                         /* @07 */
\EM(ON)MQGMO_ALL_MSGS_AVAILABLE\EM(OFF)                       /* @07 */
\P\P                                                          /* @07 */
If this option is specified, WebSphere MQ prohibits the       /* @07 */
retrieval of any messages in a message group unless all       /* @07 */
messages belonging to the group are available. For example,   /* @07 */
some messages in the group may not be available because       /* @07 */
they have been delayed within the network.                    /* @07 */
\P\P                                                          /* @07 */
Grouped messages are retrieved only when all messages in      /* @07 */
the group are available for retrieval.  WebSphere MQ waits    /* @07 */
the specified wait interval (if any) and returns the          /* @07 */
\EM(on)MQRC_NO_MSG_AVAILABLE\EM(off) reason code if no        /* @07 */
messages are returned.                                        /* @07 */
\P\P                                                          /* @07 */
}}                                                            /* @07 */
:END                                                          /* @07 */

:STREAM{ NAME{MQOPTGET.ALLSEGS} TEXT{                         /* @07 */
\EM(ON)MQGMO_ALL_SEGMENTS_AVAILABLE\EM(OFF)                   /* @07 */
\P\P                                                          /* @07 */
If this option is specified, WebSphere MQ prohibits the       /* @07 */
retrieval of an incomplete set of message segments            /* @07 */
belonging to a single logical message.  For example, some     /* @07 */
message segments may not be available in the queue because    /* @07 */
they have been delayed within the network.                    /* @07 */
\P\P                                                          /* @07 */
Message segments are retrieved only when all segments in      /* @07 */
the logical message are available for retrieval.  WebSphere   /* @07 */
MQ waits the specified wait interval (if any) and returns     /* @07 */
the \EM(on)MQRC_NO_MSG_AVAILABLE\EM(off) reason code if no    /* @07 */
messages are returned.                                        /* @07 */
\P\P                                                          /* @07 */
}}                                                            /* @07 */
:END                                                          /* @07 */

:STREAM{ NAME{MQOPTGET.YESMQ} TEXT{
\EM(ON)YES\EM(OFF)\P\P
This indicates that the specified option was used by the queue
manager.  This may differ from what was specified in the program, as
for example, a default option may be used even when not coded in the
program.
}}
:END

:STREAM{ NAME{MQOPTGET.YESPROG} TEXT{
\EM(ON)YES\EM(OFF)\P\P
This indicates that the specified option was coded on the MQGET
call in the program.
}}
:END

:STREAM{ NAME{MQOPTGET.NOMQ} TEXT{
\EM(ON)NO\EM(OFF)\P\P
This indicates that the specified option was not used by the queue
manager.  This may differ from what was specified in the program, as
for example, a default option may be used even when not coded in the
program.
}}

:STREAM{ NAME{MQOPTGET.NOPROG} TEXT{
\EM(ON)NO\EM(OFF)\P\P
This indicates that the specified option was not coded on the MQGET
call in the program.
}}
:END

*   --------------------------------------------------------    @01
*   FOLLOWING SCREEN MQOPTGET ADDED FOR ABEND-AID E-BUSINESS    @01
*   EDITION RELEASE 2.0.                                        @01
*   --------------------------------------------------------    @01

:SCREEN{ NAME{MQOPTGET} TITLE{GMO Options}
 TEMPLATE{KAZHDTMP.MQOPTGET}                                  /* @08 */
  ORG{KAZ#MQOQ}                                               /* @03 */
  FIXED{
;       * ----------------------------------------------- *
;       * TEST ALL BITS IN PROGRAM SUPPLIED OPTION BYTE 4 *
;       * ----------------------------------------------- *
  COND{ FNAME{OP2B4X00} DLOC{OP2BYTE4}
       COMPOP{TM,X'FF',Z} }
  COND{ FNAME{OP2B4X01} DLOC{OP2BYTE4}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{OP2B4X02} DLOC{OP2BYTE4}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{OP2B4X04} DLOC{OP2BYTE4}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{OP2B4X08} DLOC{OP2BYTE4}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{OP2B4X10} DLOC{OP2BYTE4}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{OP2B4X20} DLOC{OP2BYTE4}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{OP2B4X40} DLOC{OP2BYTE4}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{OP2B4X80} DLOC{OP2BYTE4}
       COMPOP{TM,X'80',O} }
;       * ----------------------------------------------- *
;       * TEST ALL BITS IN PROGRAM SUPPLIED OPTION BYTE 3 *
;       * ----------------------------------------------- *
  COND{ FNAME{OP2B3X01} DLOC{OP2BYTE3}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{OP2B3X02} DLOC{OP2BYTE3}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{OP2B3X04} DLOC{OP2BYTE3}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{OP2B3X08} DLOC{OP2BYTE3}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{OP2B3X10} DLOC{OP2BYTE3}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{OP2B3X20} DLOC{OP2BYTE3}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{OP2B3X40} DLOC{OP2BYTE3}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{OP2B3X80} DLOC{OP2BYTE3}
       COMPOP{TM,X'80',O} }
;       * ----------------------------------------------- *
;       * TEST ALL BITS IN PROGRAM SUPPLIED OPTION BYTE 2 *
;       * ----------------------------------------------- *
  COND{ FNAME{OP2B2X01} DLOC{OP2BYTE2}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{OP2B2X02} DLOC{OP2BYTE2}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{OP2B2X04} DLOC{OP2BYTE2}
       COMPOP{TM,X'04',O} }
;
; * ------------------------- *
; * DISPLAY THE 'GMO' OPTIONS *
; * ------------------------- *
  LITERAL { POS{+2,36}
    FNAME{GMOOPT}
    XNAME{GMO Option}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{GMO Options}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.GMO')}
  }
  HEX{ FNAME{GMO@} POS{+0,36,8}
    DLOC{OP2VALUE}
    XNAME{Get Msg Options}
    HELP{\IM('MQOPTGET.GMO')}
  }
;
; * -------------------------- *
; * DISPLAY THE 'WAIT' SETTING *
; * -------------------------- *
  LITERAL { POS{+2,36}
    FNAME{WAIT}
    XNAME{MQGMO_WAIT}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_WAIT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.WAIT')}
  }
  IF { COND{OP2B4X01}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_01A}
          XNAME{Wait_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.WAIT')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_01A}
          XNAME{Wait_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.WAIT')}
          }
  }}
; * ----------------------------- *
; * DISPLAY THE 'NO-WAIT' SETTING *
; * ----------------------------- *
  LITERAL { POS{+1,36}
    FNAME{NOWAIT}
    XNAME{MQGMO_No_Wait}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_NO_WAIT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.NOWAIT')}
  }
  IF { COND{OP2B4X01}
   THEN { LITERAL { POS{+0,36}
          FNAME{NOT_02A}
          XNAME{NoWait_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.NOWAIT')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{SET_02A}
          XNAME{NoWait_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.NOWAIT')}
          }
  }}
; * ------------------------------- *
; * DISPLAY THE 'SYNCPOINT' SETTING *
; * ------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{SYNC}
    XNAME{MQGMO_Syncpoint}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_SYNCPOINT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.SYNC')}
  }
  IF { COND{OP2B4X02}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_03A}
          XNAME{Sync_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.SYNC')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_03A}
          XNAME{Sync_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.SYNC')}
          }
  }}
; * --------------------------------------------- *
; * DISPLAY THE 'SYNCPOINT IF PERSISTENT' SETTING *
; * --------------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{SYNCPERS}
    XNAME{MQGMO_Sync_Pers}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_SYNCPOINT_IF_PERSISTENT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.SYNC2')}
  }
  IF { COND{OP2B3X10}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_04A}
          XNAME{Syncp_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.SYNC2')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_04A}
          XNAME{Syncp_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.SYNC2')}
          }
  }}
; * ---------------------------------- *
; * DISPLAY THE 'NO SYNCPOINT' SETTING *
; * ---------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{NOSYNC}
    XNAME{MQGMO_No_Sync}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_NO_SYNCPOINT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.SYNC3')}
  }
  IF { COND{OP2B4X04}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_05A}
          XNAME{NoSync_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.SYNC3')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_05A}
          XNAME{NoSync_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.SYNC3')}
          }
  }}
; * --------------------------------------- *
; * DISPLAY THE 'MARK SKIP BACKOUT' SETTING *
; * --------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{SKIPBACK}
    XNAME{MQGMO_Skip_Back}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_MARK_SKIP_BACKOUT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.SKIP')}
  }
  IF { COND{OP2B4X80}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_06A}
          XNAME{Backout_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.SKIP')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_06A}
          XNAME{Backout_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.SKIP')}
          }
  }}
; * ---------------------------------- *
; * DISPLAY THE 'BROWSE FIRST' SETTING *
; * ---------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{BROW1ST}
    XNAME{MQGMO_Browse_1ST}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_BROWSE_FIRST}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.BROWSEF')}
  }
  IF { COND{OP2B4X10}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_07A}
          XNAME{BrowseF_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.BROWSEF')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_07A}
          XNAME{BrowseF_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.BROWSEF')}
          }
  }}
; * --------------------------------- *
; * DISPLAY THE 'BROWSE NEXT' SETTING *
; * --------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{BROWNXT}
    XNAME{MQGMO_Browse_Nxt}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_BROWSE_NEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.BROWSEN')}
  }
  IF { COND{OP2B4X20}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_08A}
          XNAME{BrowseN_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.BROWSEN')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_08A}
          XNAME{BrowseN_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.BROWSEN')}
          }
  }}
; * ------------------------------------------ *
; * DISPLAY THE 'MESSAGE UNDER CURSOR' SETTING *
; * ------------------------------------------ *
  LITERAL { POS{+1,36}
    FNAME{MSGCURS}
    XNAME{MQGMO_Msg_Cursor}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_MSG_UNDER_CURSOR}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.CURSOR')}
  }
  IF { COND{OP2B3X01}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_09A}
          XNAME{Cursor_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.CURSOR')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_09A}
          XNAME{Cursor_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.CURSOR')}
          }
  }}
; * ---------------------------------------------- *
; * DISPLAY THE 'ACCEPT TRUNCATED MESSAGE' SETTING *
; * ---------------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{TRUNCATE}
    XNAME{MQGMO_Msg_Trunc}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_ACCEPT_TRUNCATED_MSG}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.TRUNC')}
  }
  IF { COND{OP2B4X40}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_10A}
          XNAME{Trunc_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.TRUNC')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_10A}
          XNAME{Trunc_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.TRUNC')}
          }
  }}
; * -------------------------------- *
; * DISPLAY THE 'SET SIGNAL' SETTING *
; * -------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{SIGNAL}
    XNAME{MQGMO_Set_Signal}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_SET_SIGNAL}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.SIGNAL')}
  }
  IF { COND{OP2B4X08}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_11A}
          XNAME{Signal_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.SIGNAL')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_11A}
          XNAME{Signal_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.SIGNAL')}
          }
  }}
; * --------------------------------------- *
; * DISPLAY THE 'FAIL IF QUIESCING' SETTING *
; * --------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{QUIESCE}
    XNAME{MQGMO_Quiescing}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_FAIL_IF_QUIESCING}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.QUIESCE')}
  }
  IF { COND{OP2B3X20}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_12A}
          XNAME{Quiesce_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.QUIESCE')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_12A}
          XNAME{Quiesce_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.QUIESCE')}
          }
  }}
; * ----------------------------- *
; * DISPLAY THE 'CONVERT' SETTING *
; * ----------------------------- *
  LITERAL { POS{+1,36}
    FNAME{CONVERT}
    XNAME{MQGMO_Convert}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQGMO_CONVERT}
      FILL{.}
    }
    HELP{\IM('MQOPTGET.CONVERT')}
  }
  IF { COND{OP2B3X40}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_14A}
          XNAME{Convert_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTGET.YESPROG')
               \P\P
               \IM('MQOPTGET.CONVERT')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_14A}
          XNAME{Convert_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTGET.NOPROG')
               \P\P
               \IM('MQOPTGET.CONVERT')}
          }
  }}
; * -------------------------------------------- *            /* @07 */
; * DISPLAY THE 'ALL MESSAGES AVAILABLE' SETTING *            /* @07 */
; * -------------------------------------------- *            /* @07 */
  LITERAL { POS{+1,36}                                        /* @07 */
    FNAME{ALLMSGS}                                            /* @07 */
    XNAME{MQGMO_AllMsgs}                                      /* @07 */
    TEXT{ }                                                   /* @07 */
    FDESC{ COL{1}                                             /* @07 */
      TEXT{MQGMO_ALL_MSGS_AVAILABLE}                          /* @07 */
      FILL{.}                                                 /* @07 */
    }                                                         /* @07 */
    HELP{\IM('MQOPTGET.ALLMSGS')}                             /* @07 */
  }                                                           /* @07 */
  IF { COND{OP2B2X02}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{SET_15A}                                      /* @07 */
          XNAME{AllMsgs_Prog_Set}                             /* @07 */
          TEXT{YES}                                           /* @07 */
          HELP{\IM('MQOPTGET.YESPROG')                        /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.ALLMSGS')}                       /* @07 */
          }                                                   /* @07 */
   }                                                          /* @07 */
   ELSE { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{NOT_15A}                                      /* @07 */
          XNAME{AllMsgs_Prog_Off}                             /* @07 */
          TEXT{NO}                                            /* @07 */
          HELP{\IM('MQOPTGET.NOPROG')                         /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.ALLMSGS')}                       /* @07 */
          }                                                   /* @07 */
  }}                                                          /* @07 */
; * -------------------------------------------- *            /* @07 */
; * DISPLAY THE 'ALL SEGMENTS AVAILABLE' SETTING *            /* @07 */
; * -------------------------------------------- *            /* @07 */
  LITERAL { POS{+1,36}                                        /* @07 */
    FNAME{ALLSEGS}                                            /* @07 */
    XNAME{MQGMO_AllSegs}                                      /* @07 */
    TEXT{ }                                                   /* @07 */
    FDESC{ COL{1}                                             /* @07 */
      TEXT{MQGMO_ALL_SEGMENTS_AVAILABLE}                      /* @07 */
      FILL{.}                                                 /* @07 */
    }                                                         /* @07 */
    HELP{\IM('MQOPTGET.ALLSEGS')}                             /* @07 */
  }                                                           /* @07 */
  IF { COND{OP2B2X04}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{SET_16A}                                      /* @07 */
          XNAME{AllSegs_Prog_Set}                             /* @07 */
          TEXT{YES}                                           /* @07 */
          HELP{\IM('MQOPTGET.YESPROG')                        /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.ALLSEGS')}                       /* @07 */
          }                                                   /* @07 */
   }                                                          /* @07 */
   ELSE { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{NOT_16A}                                      /* @07 */
          XNAME{AllSegs_Prog_Off}                             /* @07 */
          TEXT{NO}                                            /* @07 */
          HELP{\IM('MQOPTGET.NOPROG')                         /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.ALLSEGS')}                       /* @07 */
          }                                                   /* @07 */
  }}                                                          /* @07 */
; * --------------------------------------------- *           /* @07 */
; * DISPLAY THE 'BROWSE MSG UNDER CURSOR' SETTING *           /* @07 */
; * --------------------------------------------- *           /* @07 */
  LITERAL { POS{+1,36}                                        /* @07 */
    FNAME{BROWCSR}                                            /* @07 */
    XNAME{MQGMO_BrwsUnder}                                    /* @07 */
    TEXT{ }                                                   /* @07 */
    FDESC{ COL{1}                                             /* @07 */
      TEXT{MQGMO_BROWSE_MSG_UNDER_CURSOR}                     /* @07 */
      FILL{.}                                                 /* @07 */
    }                                                         /* @07 */
    HELP{\IM('MQOPTGET.BROWSEU')}                             /* @07 */
  }                                                           /* @07 */
  IF { COND{OP2B3X08}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{SET_17A}                                      /* @07 */
          XNAME{BrwsCsr_Prog_Set}                             /* @07 */
          TEXT{YES}                                           /* @07 */
          HELP{\IM('MQOPTGET.YESPROG')                        /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.BROWSEU')}                       /* @07 */
          }                                                   /* @07 */
   }                                                          /* @07 */
   ELSE { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{NOT_17A}                                      /* @07 */
          XNAME{BrwsCsr_Prog_Off}                             /* @07 */
          TEXT{NO}                                            /* @07 */
          HELP{\IM('MQOPTGET.NOPROG')                         /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.BROWSEU')}                       /* @07 */
          }                                                   /* @07 */
  }}                                                          /* @07 */
; * ---------------------------------- *                      /* @07 */
; * DISPLAY THE 'COMPLETE MSG' SETTING *                      /* @07 */
; * ---------------------------------- *                      /* @07 */
  LITERAL { POS{+1,36}                                        /* @07 */
    FNAME{COMPLET}                                            /* @07 */
    XNAME{MQGMO_Complet}                                      /* @07 */
    TEXT{ }                                                   /* @07 */
    FDESC{ COL{1}                                             /* @07 */
      TEXT{MQGMO_COMPLETE_MSG}                                /* @07 */
      FILL{.}                                                 /* @07 */
    }                                                         /* @07 */
    HELP{\IM('MQOPTGET.COMPLET')}                             /* @07 */
  }                                                           /* @07 */
  IF { COND{OP2B2X01}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{SET_18A}                                      /* @07 */
          XNAME{Complet_Prog_Set}                             /* @07 */
          TEXT{YES}                                           /* @07 */
          HELP{\IM('MQOPTGET.YESPROG')                        /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.COMPLET')}                       /* @07 */
          }                                                   /* @07 */
   }                                                          /* @07 */
   ELSE { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{NOT_18A}                                      /* @07 */
          XNAME{Complet_Prog_Off}                             /* @07 */
          TEXT{NO}                                            /* @07 */
          HELP{\IM('MQOPTGET.NOPROG')                         /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.COMPLET')}                       /* @07 */
          }                                                   /* @07 */
  }}                                                          /* @07 */
; * ---------------------------------- *                      /* @07 */
; * DISPLAY THE 'LOCK' SETTING *                              /* @07 */
; * ---------------------------------- *                      /* @07 */
  LITERAL { POS{+1,36}                                        /* @07 */
    FNAME{LOCK}                                               /* @07 */
    XNAME{MQGMO_Lock}                                         /* @07 */
    TEXT{ }                                                   /* @07 */
    FDESC{ COL{1}                                             /* @07 */
      TEXT{MQGMO_LOCK}                                        /* @07 */
      FILL{.}                                                 /* @07 */
    }                                                         /* @07 */
    HELP{\IM('MQOPTGET.LOCK')}                                /* @07 */
  }                                                           /* @07 */
  IF { COND{OP2B3X02}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{SET_19A}                                      /* @07 */
          XNAME{Lock_Prog_Set}                                /* @07 */
          TEXT{YES}                                           /* @07 */
          HELP{\IM('MQOPTGET.YESPROG')                        /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.LOCK')}                          /* @07 */
          }                                                   /* @07 */
   }                                                          /* @07 */
   ELSE { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{NOT_19A}                                      /* @07 */
          XNAME{Lock_Prog_Off}                                /* @07 */
          TEXT{NO}                                            /* @07 */
          HELP{\IM('MQOPTGET.NOPROG')                         /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.LOCK')}                          /* @07 */
          }                                                   /* @07 */
  }}                                                          /* @07 */
; * ----------------------------------- *                     /* @07 */
; * DISPLAY THE 'LOGICAL ORDER' SETTING *                     /* @07 */
; * ----------------------------------- *                     /* @07 */
  LITERAL { POS{+1,36}                                        /* @07 */
    FNAME{LOGICAL}                                            /* @07 */
    XNAME{MQGMO_Logical}                                      /* @07 */
    TEXT{ }                                                   /* @07 */
    FDESC{ COL{1}                                             /* @07 */
      TEXT{MQGMO_LOGICAL_ORDER}                               /* @07 */
      FILL{.}                                                 /* @07 */
    }                                                         /* @07 */
    HELP{\IM('MQOPTGET.LOGICAL')}                             /* @07 */
  }                                                           /* @07 */
  IF { COND{OP2B3X80}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{SET_20A}                                      /* @07 */
          XNAME{Logical_Prog_Set}                             /* @07 */
          TEXT{YES}                                           /* @07 */
          HELP{\IM('MQOPTGET.YESPROG')                        /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.LOGICAL')}                       /* @07 */
          }                                                   /* @07 */
   }                                                          /* @07 */
   ELSE { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{NOT_20A}                                      /* @07 */
          XNAME{Logical_Prog_Off}                             /* @07 */
          TEXT{NO}                                            /* @07 */
          HELP{\IM('MQOPTGET.NOPROG')                         /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.LOGICAL')}                       /* @07 */
          }                                                   /* @07 */
  }}                                                          /* @07 */
; * ----------------------------- *                           /* @07 */
; * DISPLAY THE 'UNLOCK' SETTING  *                           /* @07 */
; * ----------------------------- *                           /* @07 */
  LITERAL { POS{+1,36}                                        /* @07 */
    FNAME{UNLOCK}                                             /* @07 */
    XNAME{MQGMO_Unlock}                                       /* @07 */
    TEXT{ }                                                   /* @07 */
    FDESC{ COL{1}                                             /* @07 */
      TEXT{MQGMO_UNLOCK}                                      /* @07 */
      FILL{.}                                                 /* @07 */
    }                                                         /* @07 */
    HELP{\IM('MQOPTGET.UNLOCK')}                              /* @07 */
  }                                                           /* @07 */
  IF { COND{OP2B3X04}                                         /* @07 */
   THEN { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{SET_21A}                                      /* @07 */
          XNAME{Unlock_Prog_Set}                              /* @07 */
          TEXT{YES}                                           /* @07 */
          HELP{\IM('MQOPTGET.YESPROG')                        /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.UNLOCK')}                        /* @07 */
          }                                                   /* @07 */
   }                                                          /* @07 */
   ELSE { LITERAL { POS{+0,36}                                /* @07 */
          FNAME{NOT_21A}                                      /* @07 */
          XNAME{Unlock_Prog_Off}                              /* @07 */
          TEXT{NO}                                            /* @07 */
          HELP{\IM('MQOPTGET.NOPROG')                         /* @07 */
               \P\P                                           /* @07 */
               \IM('MQOPTGET.UNLOCK')}                        /* @07 */
          }                                                   /* @07 */
  }}                                                          /* @07 */
 }                                           /* END OF FIXED  */
  HELP{
This screen displays information interpreted from the MQGMO_OPTIONS
field. These options control the action of MQGET.\P\P
Each option which is supported on OS/390 for MQGET is shown, together
with its setting.  Help information is available for every option.  To
get the help information move the cursor to the option on the screen
and press <PF-1>.
  }
}                                            /* END OF SCREEN */
:END

:STREAM{ NAME{MQOPTPUT.PMO} TEXT{
\EM(ON)PMO Options\EM(OFF)\P\P
The value of the Put Message Options.\P\P  Each bit represents
a different setting which can be specified by the application
programmer.  The settings are broken down and shown on the
following lines on the terminal.
}}
:END

:STREAM{ NAME{MQOPTPUT.SYNC} TEXT{
\EM(ON)MQPMO_SYNCPOINT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will put the message with syncpoint control.\P\P /* @06 */
This means the message will be unavailable to other
applications until the unit of
work is committed.  If the unit of work is backed out the
message will be deleted.\P\P
This option is the opposite of
\EM(on)MQPMO_NO_SYNCPOINT.\EM(off)\P\P
If neither \EM(on)MQPMO_SYNCPOINT\EM(off)
nor \EM(on)MQPMO_NO_SYNCPOINT\EM(off)
is specified the default depends on
the environment.\P\P  On OS/390 the default is
\EM(on)MQPMO_SYNCPOINT,\EM(off) but on most other environments
it is \EM(on)MQPMO_NO_SYNCPOINT.\EM(off)
}}
:END

:STREAM{ NAME{MQOPTPUT.SYNC3} TEXT{
\EM(ON)MQPMO_NO_SYNCPOINT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will put the message                             /* @06 */
without syncpoint control.\P\P                                /* @05 */
This means the message, will be
immediately available to other applications.  The message
will not be deleted if the unit of work fails or is
backed out.\P\P
This option is the opposite of
\EM(on)MQPMO_SYNCPOINT.\EM(off)\P\P
If neither \EM(on)MQPMO_SYNCPOINT\EM(off) nor
\EM(on)MQPMO_NO_SYNCPOINT\EM(off)
is specified the default depends on
the environment.\P\P  On OS/390 the default is
\EM(on)MQPMO_SYNCPOINT,\EM(off) but on most other environments
it is \EM(on)MQPMO_NO_SYNCPOINT.\EM(off)
}}
:END

:STREAM{ NAME{MQOPTPUT.CONTEXT} TEXT{
\EM(ON)MQPMO_NO_CONTEXT\EM(OFF)\P\P
If this option is set then
no context is to be associated with the message.\P\P

Both identity and origin context are set to indicate no
context.  The context fields in
the message descriptor will be set as follows:\P\P
\T(%,08,30)
 %Field type         %Value used  \P
 %----------------   %------------\P
 %Character fields   %Blanks      \P
 %                   %            \P
 %Byte fields        %Nulls       \P
 %                   %            \P
 %Numeric fields     %Zeroes      \P
}}
:END

:STREAM{ NAME{MQOPTPUT.DEFCTEXT} TEXT{
\EM(ON)MQPMO_DEFAULT_CONTEXT\EM(OFF)\P\P
If this option is set then
 the message is to have default context information associated
 with it, for both identity and origin.  The queue manager
 sets the context fields in the message descriptor as follows:
\P\P
\T(%,04,22)
 %                   %                            \P
 %Field in message   %Value used                  \P
 %descriptor         %                            \P
 %-------------------%--------------------------  \P
 %UserIdentifier     %If possible it will be      \P
 %                   %determined from the         \P
 %                   %environment, otherwise it   \P
 %                   %will be set to blanks.      \P
 %                   %                            \P
 %AccountingToken    %If possible it will be      \P
 %                   %determined from the         \P
 %                   %environment, otherwise it   \P
 %                   %will be set to MQACT_NONE.  \P
 %                   %                            \P
 %ApplIdentityData   %It will be set to blanks.   \P
 %                   %                            \P
 %PutApplType        %It will be determined       \P
 %                   %from the environment.       \P
 %                   %                            \P
 %PutApplName        %If possible it will be      \P
 %                   %determined from the         \P
 %                   %environment, otherwise it   \P
 %                   %will be set to blanks.      \P
 %                   %                            \P
 %PutDate            %It will be set to the date  \P
 %                   %when the message is put.    \P
 %                   %                            \P
 %PutTime            %It will be set to the time  \P
 %                   %when the message is put.    \P
 %                   %                            \P
 %ApplOriginData     %It will be set to blanks.   \P
 %                   %                            \P
}}
:END

:STREAM{ NAME{MQOPTPUT.PASSID} TEXT{
\EM(ON)MQPMO_PASS_IDENTITY_CONTEXT\EM(OFF)\P\P
If this option is set then
the message is to have context information associated with
it.\P\P
Identity context is taken from the queue handle
specified in the Context field.\P\P
Origin context information
is generated by the queue manager in the same way that it is
for MQPMO_DEFAULT_CONTEXT.
}}
:END

:STREAM{ NAME{MQOPTPUT.PASS_ALL} TEXT{
\EM(ON)MQPMO_PASS_ALL_CONTEXT\EM(OFF)\P\P
If this option is set then
the message is to have context information associated with
it.\P\P
Identity context is taken from the queue handle
specified in the Context field.\P\P
Origin context is also taken from the queue handle
specified in the Context field.\P\P
}}
:END

:STREAM{ NAME{MQOPTPUT.SET_ID} TEXT{
\EM(ON)MQPMO_SET_IDENTITY_CONTEXT\EM(OFF)\P\P
If this option is set then
the message is to have context information associated with
it.\P\P
Identity context is specified by the application in
the Message Descriptor structure.\P\P
Origin context information
is generated by the queue manager in the same way that it is
for MQPMO_DEFAULT_CONTEXT.
}}
:END

:STREAM{ NAME{MQOPTPUT.SET_ALL} TEXT{
\EM(ON)MQPMO_SET_ALL_CONTEXT\EM(OFF)\P\P
If this option is set then
the message is to have context information associated with
it.\P\P
Identity context is specified by the application in
the Message Descriptor structure.\P\P
Origin context is also specified by the application in
the Message Descriptor structure.\P\P
}}
:END

:STREAM{ NAME{MQOPTPUT.ALT_USER} TEXT{
\EM(ON)MQPMO_ALTERNATE_USER_AUTHORITY\EM(OFF)\P\P
If this option is set then
validatation will be performed with the specified user identifier.\P\P
This indicates that the AlternateUserId field in the ObjDesc
parameter of the MQPUT1 call contains a user identifier that
is to be used to validate authority to put messages on the
queue. \P\P
The call can succeed only if this AlternateUserId is
authorized to open the queue with the specified options,
regardless of whether the user identifier under which the
application is running is authorized to do so.  (This does
not apply to the context options specified, however, which
are always checked against the user identifier under which
the application is running.)
}}
:END

:STREAM{ NAME{MQOPTPUT.QUIESCE} TEXT{
\EM(ON)MQPMO_FAIL_IF_QUIESCING\EM(OFF)\P\P
If this option is set then
the MQPUT or MQPUT1 request will fail if the queue manager
or the CICS connection is quiescing.
}}
:END

:STREAM{ NAME{MQOPTPUT.YESMQ} TEXT{
\EM(ON)YES\EM(OFF)\P\P
This indicates that the specified option was used by the queue
manager.  This may differ from what was specified in the program, as
for example, a default option may be used even when not coded in the
program.
}}
:END

:STREAM{ NAME{MQOPTPUT.YESPROG} TEXT{
\EM(ON)YES\EM(OFF)\P\P
This indicates that the specified option was coded on the MQPUT
call in the program.
}}
:END

:STREAM{ NAME{MQOPTPUT.NOMQ} TEXT{
\EM(ON)NO\EM(OFF)\P\P
This indicates that the specified option was not used by the queue
manager.  This may differ from what was specified in the program, as
for example, a default option may be used even when not coded in the
program.
}}

:STREAM{ NAME{MQOPTPUT.NOPROG} TEXT{
\EM(ON)NO\EM(OFF)\P\P
This indicates that the specified option was not coded on the MQPUT
call in the program.
}}
:END

*   --------------------------------------------------------    @01
*   FOLLOWING SCREEN MQOPTPUT ADDED FOR ABEND-AID E-BUSINESS    @01
*   EDITION RELEASE 2.0.                                        @01
*   --------------------------------------------------------    @01

:SCREEN{ NAME{MQOPTPUT} TITLE{PMO Options}
 TEMPLATE{KAZHDTMP.MQOPTPUT}                                  /* @08 */
  ORG{KAZ#MQOQ}                                               /* @03 */
  FIXED{
;       * ----------------------------------- *
;       * TEST ALL BITS IN QMGR OPTION BYTE 4 *
;       * ----------------------------------- *
  COND{ FNAME{BYTE4X00} DLOC{OPTBYTE4}
       COMPOP{TM,X'FF',Z} }
  COND{ FNAME{BYTE4X01} DLOC{OPTBYTE4}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{BYTE4X02} DLOC{OPTBYTE4}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{BYTE4X04} DLOC{OPTBYTE4}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{BYTE4X08} DLOC{OPTBYTE4}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{BYTE4X10} DLOC{OPTBYTE4}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{BYTE4X20} DLOC{OPTBYTE4}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{BYTE4X40} DLOC{OPTBYTE4}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{BYTE4X80} DLOC{OPTBYTE4}
       COMPOP{TM,X'80',O} }
;       * ----------------------------------- *
;       * TEST ALL BITS IN QMGR OPTION BYTE 3 *
;       * ----------------------------------- *
  COND{ FNAME{BYTE3X01} DLOC{OPTBYTE3}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{BYTE3X02} DLOC{OPTBYTE3}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{BYTE3X04} DLOC{OPTBYTE3}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{BYTE3X08} DLOC{OPTBYTE3}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{BYTE3X10} DLOC{OPTBYTE3}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{BYTE3X20} DLOC{OPTBYTE3}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{BYTE3X40} DLOC{OPTBYTE3}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{BYTE3X80} DLOC{OPTBYTE3}
       COMPOP{TM,X'80',O} }
;       * ----------------------------------------------- *
;       * TEST FOR PRESENCE OF PROGRAMMER SUPPLIED OPTION *
;       * ----------------------------------------------- *
  COND{ FNAME{FLAGPROG} DLOC{OPTFLAG}
       COMPOP{TM,XISTPGM,O} }
;
;       * ------------------------------------- *
;       * TEST FOR PRESENCE OF QMGR USED OPTION *
;       * ------------------------------------- *
  COND{ FNAME{FLAGQMGR} DLOC{OPTFLAG}
       COMPOP{TM,XISTQMGR,O} }
;
;       * ---------------------------------- *
;       * TEST FOR ''ONLY'' QMGR USED OPTION *
;       * ---------------------------------- *
  COND{ FNAME{ONLYQMGR} DLOC{OPTFLAG}
       COMPOP{CLI,XISTQMGR,E} }
;
;       * --------------------------------- *
;       * TEST FOR PRESENCE OF BOTH OPTIONS *
;       * --------------------------------- *
  COND{ FNAME{FLAGBOTH} DLOC{OPTFLAG}
       COMPOP{TM,XISTBOTH,O} }
;
;       * ----------------------------------------------- *
;       * TEST ALL BITS IN PROGRAM SUPPLIED OPTION BYTE 4 *
;       * ----------------------------------------------- *
  COND{ FNAME{OP2B4X00} DLOC{OP2BYTE4}
       COMPOP{TM,X'FF',Z} }
  COND{ FNAME{OP2B4X01} DLOC{OP2BYTE4}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{OP2B4X02} DLOC{OP2BYTE4}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{OP2B4X04} DLOC{OP2BYTE4}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{OP2B4X08} DLOC{OP2BYTE4}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{OP2B4X10} DLOC{OP2BYTE4}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{OP2B4X20} DLOC{OP2BYTE4}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{OP2B4X40} DLOC{OP2BYTE4}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{OP2B4X80} DLOC{OP2BYTE4}
       COMPOP{TM,X'80',O} }
;       * ----------------------------------------------- *
;       * TEST ALL BITS IN PROGRAM SUPPLIED OPTION BYTE 3 *
;       * ----------------------------------------------- *
  COND{ FNAME{OP2B3X01} DLOC{OP2BYTE3}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{OP2B3X02} DLOC{OP2BYTE3}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{OP2B3X04} DLOC{OP2BYTE3}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{OP2B3X08} DLOC{OP2BYTE3}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{OP2B3X10} DLOC{OP2BYTE3}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{OP2B3X20} DLOC{OP2BYTE3}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{OP2B3X40} DLOC{OP2BYTE3}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{OP2B3X80} DLOC{OP2BYTE3}
       COMPOP{TM,X'80',O} }
;
; * ------------------------------------------ *
; * DISPLAY THE FOLLOWING LITERALS AS REQUIRED *
; *  - "SPECIFIED IN PROGRAM"                  *
; *  - "USED BY MQGR"                          *
; * ------------------------------------------ *
;  IF { COND{FLAGPROG}
;   THEN {
;      LITERAL { POS{+1,46}
;        FNAME{SPEC1}
;        XNAME{Column1}
;        TEXT{ }
;        FDESC{ COL{36}
;          TEXT{SPECIFIED}
;        }
;        HELP{\IM('MQOPTPUT.YESPROG')
;             \P \P
;             \IM('MQOPTPUT.NOPROG')}
;      }
;   }
;   ELSE {
;      LITERAL { POS{+1,46}
;        FNAME{QMGR1}
;        XNAME{Column2}
;        TEXT{ }
;        FDESC{ COL{36}
;          TEXT{USED BY}
;        }
;        HELP{\IM('MQOPTPUT.YESMQ')
;             \P \P
;             \IM('MQOPTPUT.NOMQ')}
;      }
;  }}
;  IF { COND{FLAGBOTH}
;   THEN {
;      LITERAL { POS{+0,58}
;        FNAME{QMGR1}
;        XNAME{Column2}
;        TEXT{ }
;        FDESC{ COL{48}
;          TEXT{USED BY}
;        }
;        HELP{\IM('MQOPTPUT.YESMQ')
;             \P \P
;             \IM('MQOPTPUT.NOMQ')}
;      }
;  }}
;
;
;  IF { COND{FLAGPROG}
;   THEN {
;      LITERAL { POS{+1,47}
;        FNAME{SPEC2}
;        XNAME{Column1}
;        TEXT{ }
;        FDESC{ COL{36}
;          TEXT{IN PROGRAM}
;        }
;        HELP{\IM('MQOPTPUT.YESPROG')
;             \P \P
;             \IM('MQOPTPUT.NOPROG')}
;      }
;   }
;   ELSE {
;      LITERAL { POS{+1,46}
;        FNAME{QMGR2}
;        XNAME{Column2}
;        TEXT{ }
;        FDESC{ COL{37}
;          TEXT{QMGR}
;        }
;        HELP{\IM('MQOPTPUT.YESMQ')
;             \P \P
;             \IM('MQOPTPUT.NOMQ')}
;      }
;   }
;  }
;  IF { COND{FLAGBOTH}
;   THEN {
;      LITERAL { POS{+0,58}
;        FNAME{QMGR2}
;        XNAME{Column2}
;        TEXT{ }
;        FDESC{ COL{49}
;          TEXT{QMGR}
;        }
;        HELP{\IM('MQOPTPUT.YESMQ')
;             \P \P
;             \IM('MQOPTPUT.NOMQ')}
;      }
;  }}
; * ------------------------- *
; * DISPLAY THE 'PMO' OPTIONS *
; * ------------------------- *
  LITERAL { POS{+2,36}
    FNAME{PMOOPT}
    XNAME{PMO_Option}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{PMO Options}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.PMO')}
  }
;
;    *** FIRST COLUMN OF APPROPRIATE OPTIONS ***
;
  IF { COND{FLAGPROG}
   THEN { HEX{ FNAME{PMO@} POS{+0,36,8}
            DLOC{OP2VALUE}
            XNAME{Put Msg Options}
            HELP{\IM('MQOPTPUT.PMO')}
          }
   }
   ELSE { HEX{ FNAME{PMO@} POS{+0,36,8}
            DLOC{OPTVALUE}
            XNAME{Put Msg Options}
            HELP{\IM('MQOPTPUT.PMO')}
          }
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN { HEX{ FNAME{PMO@} POS{+0,48,8}
            DLOC{OPTVALUE}
            XNAME{Put Msg Options}
            HELP{\IM('MQOPTPUT.PMO')}
          }
  }}
; * ------------------------------- *
; * DISPLAY THE 'SYNCPOINT' SETTING *
; * ------------------------------- *
  LITERAL { POS{+2,36}
    FNAME{SYNC}
    XNAME{MQPMO_Syncpoint}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_SYNCPOINT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.SYNC')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B4X02}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_01A}
              XNAME{Sync_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.SYNC')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_01A}
              XNAME{Sync_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.SYNC')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE4X02}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_01B}
              XNAME{Sync_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_01B}
              XNAME{Sync_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE4X02}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_01B}
              XNAME{Sync_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_01B}
              XNAME{Sync_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC')}
              }
      }}
  }}
; * ---------------------------------- *
; * DISPLAY THE 'NO SYNCPOINT' SETTING *
; * ---------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{NOSYNC}
    XNAME{MQPMO_No_Sync}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_NO_SYNCPOINT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.SYNC3')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B4X04}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_02A}
              XNAME{NoSync_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.SYNC3')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_02A}
              XNAME{NoSync_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.SYNC3')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE4X04}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_02B}
              XNAME{NoSync_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC3')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_02B}
              XNAME{NoSync_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC3')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE4X04}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_02B}
              XNAME{NoSync_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC3')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_02B}
              XNAME{NoSync_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SYNC3')}
              }
      }}
  }}
; * ---------------------------------- *
; * DISPLAY THE 'NO CONTEXT' SETTING *
; * ---------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{NOCTEXT}
    XNAME{MQPMO_No_Context}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_NO_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.CONTEXT')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B3X40}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_03A}
              XNAME{NoCtext_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.CONTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_03A}
              XNAME{NoCtext_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.CONTEXT')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE3X40}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_03B}
              XNAME{NoCtext_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.CONTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_03B}
              XNAME{NoCtext_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.CONTEXT')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE3X40}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_03B}
              XNAME{NoCtext_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.CONTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_03B}
              XNAME{NoCtext_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.CONTEXT')}
              }
      }}
  }}
; * ------------------------------------- *
; * DISPLAY THE 'DEFAULT CONTEXT' SETTING *
; * ------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{DEFCTEXT}
    XNAME{MQPMO_Defctxt_ID}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_DEFAULT_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.DEFCTEXT')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B4X20}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_04A}
              XNAME{DefCtxt_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_04A}
              XNAME{DefCtxt_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE4X20}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_04B}
              XNAME{DefCtxt_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_04B}
              XNAME{DefCtxt_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE4X20}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_04B}
              XNAME{DefCtxt_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_04B}
              XNAME{DefCtxt_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
; * ------------------------------------------- *
; * DISPLAY THE 'PASS IDENTITY CONTEXT' SETTING *
; * ------------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{PASSID}
    XNAME{MQPMO_Pass_ID}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_PASS_IDENTITY_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.PASSID')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B3X01}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_05A}
              XNAME{Pass_ID_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.PASSID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_05A}
              XNAME{Pass_ID_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.PASSID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE3X01}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_05B}
              XNAME{Pass_ID_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.PASSID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_05B}
              XNAME{Pass_ID_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.PASSID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE3X01}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_05B}
              XNAME{Pass_ID_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.PASSID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_05B}
              XNAME{Pass_ID_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.PASSID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
; * -------------------------------------- *
; * DISPLAY THE 'PASS ALL CONTEXT' SETTING *
; * -------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{PASS_ALL}
    XNAME{MQPMO_Pass_All}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_PASS_ALL_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.PASS_ALL')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B3X02}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_06A}
              XNAME{PassAll_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.PASS_ALL')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_06A}
              XNAME{PassAll_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.PASS_ALL')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE3X02}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_06B}
              XNAME{PassAll_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.PASS_ALL')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_06B}
              XNAME{PassAll_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.PASS_ALL')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE3X02}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_06B}
              XNAME{PassAll_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.PASS_ALL')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_06B}
              XNAME{PassAll_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.PASS_ALL')}
              }
      }}
  }}
; * ------------------------------------------ *
; * DISPLAY THE 'SET IDENTITY CONTEXT' SETTING *
; * ------------------------------------------ *
  LITERAL { POS{+1,36}
    FNAME{SET_ID}
    XNAME{MQPMO_Set_ID}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_SET_IDENTITY_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.SET_ID')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B3X04}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_07A}
              XNAME{Set_ID_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.SET_ID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_07A}
              XNAME{Set_ID_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.SET_ID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE3X04}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_07B}
              XNAME{Set_ID_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_07B}
              XNAME{Set_ID_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE3X04}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_07B}
              XNAME{Set_ID_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_07B}
              XNAME{Set_ID_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ID')
                   \P\P
                   \IM('MQOPTPUT.DEFCTEXT')}
              }
      }}
  }}
; * ------------------------------------- *
; * DISPLAY THE 'SET ALL CONTEXT' SETTING *
; * ------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{SET_ALL}
    XNAME{MQPMO_Set_All}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_SET_ALL_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.SET_ALL')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B3X08}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_08A}
              XNAME{Set_All_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.SET_ALL')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_08A}
              XNAME{Set_All_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.SET_ALL')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE3X08}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_08B}
              XNAME{Set_All_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ALL')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_08B}
              XNAME{Set_All_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ALL')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE3X08}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_08B}
              XNAME{Set_All_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ALL')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_08B}
              XNAME{Set_All_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.SET_ALL')}
              }
      }}
  }}
; * ---------------------------------------------- *
; * DISPLAY THE 'ALTERNATE USER AUTHORITY' SETTING *
; * ---------------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{ALT_USER}
    XNAME{MQPMO_Alt_User}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_ALTERNATE_USER_AUTHORITY}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.ALT_USER')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B3X10}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_09A}
              XNAME{AltUser_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.ALT_USER')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_09A}
              XNAME{AltUser_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.ALT_USER')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE3X10}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_09B}
              XNAME{AltUser_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.ALT_USER')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_09B}
              XNAME{AltUser_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.ALT_USER')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE3X10}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_09B}
              XNAME{AltUser_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.ALT_USER')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_09B}
              XNAME{AltUser_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.ALT_USER')}
              }
      }}
  }}
; * --------------------------------------- *
; * DISPLAY THE 'FAIL IF QUIESCING' SETTING *
; * --------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{QUIESCE}
    XNAME{MQPMO_Quiescing}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQPMO_FAIL_IF_QUIESCING}
      FILL{.}
    }
    HELP{\IM('MQOPTPUT.QUIESCE')}
  }
;
;    *** FIRST COLUMN PROGRAM OPTIONS IF NEEDED ***
;
  IF { COND{FLAGPROG}
   THEN {
      IF { COND{OP2B3X20}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_10A}
              XNAME{Quiesce_Prog_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESPROG')
                   \P\P
                   \IM('MQOPTPUT.QUIESCE')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_10A}
              XNAME{Quiesce_Prog_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOPROG')
                   \P\P
                   \IM('MQOPTPUT.QUIESCE')}
              }
      }}
  }}
;
;    *** SECOND COLUMN IF THERE ARE TWO COLUMNS REQUIRED ***
;
  IF { COND{FLAGBOTH}
   THEN {
      IF { COND{BYTE3X20}
       THEN { LITERAL { POS{+0,48}
              FNAME{SET_10B}
              XNAME{Quiesce_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.QUIESCE')}
              }
       }
       ELSE { LITERAL { POS{+0,48}
              FNAME{NOT_10B}
              XNAME{Quiesce_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.QUIESCE')}
              }
      }}
  }}
;
;    *** FIRST (AND ONLY) COLUMN QMGR OPTIONS IF NEEDED ***
;
  IF { COND{ONLYQMGR}
   THEN {
      IF { COND{BYTE3X20}
       THEN { LITERAL { POS{+0,36}
              FNAME{SET_10B}
              XNAME{Quiesce_Set}
              TEXT{YES}
              HELP{\IM('MQOPTPUT.YESMQ')
                   \P\P
                   \IM('MQOPTPUT.QUIESCE')}
              }
       }
       ELSE { LITERAL { POS{+0,36}
              FNAME{NOT_10B}
              XNAME{Quiesce_Off}
              TEXT{NO}
              HELP{\IM('MQOPTPUT.NOMQ')
                   \P\P
                   \IM('MQOPTPUT.QUIESCE')}
              }
      }}
  }}
 }                                           /* END OF FIXED  */
  HELP{
This screen displays information interpreted from the MQPMO_OPTIONS
field. These options control the action of MQPUT.\P\P
Each option which is supported on OS/390 for MQPUT is shown, together
with its setting.  Help information is available for every option.  To
get the help information move the cursor to the option on the screen
and press <PF-1>.
  }
}                                            /* END OF SCREEN */
:END
:STREAM{ NAME{MQOPTOPN.OPEN} TEXT{
\EM(ON)Open Options\EM(OFF)\P\P
The value of the Open Options.\P\P  Each bit represents
a different setting which can be specified by the application
programmer.  The settings are broken down and shown on the
following lines on the terminal.
}}
:END

:STREAM{ NAME{MQOPTOPN.INASQDEF} TEXT{
\EM(ON)MQOO_INPUT_AS_Q_DEF\EM(OFF)\P\P
If this option is set then
WebSphere MQ will open the                                    /* @06 */
queue to get messages using queue-defined defaults.  Messages
can be retrieved by using MQGET calls.
}}
:END

:STREAM{ NAME{MQOPTOPN.INSHARE} TEXT{
\EM(ON)MQOO_INPUT_SHARED\EM(OFF)\P\P
If this option is set then
WebSphere MQ will open the                                    /* @06 */
queue to get messages with shared access.\P\P
If the queue has already been opened by this or another
application for non shared access (using the
MQOO_INPUT_EXCLUSIVE parameter), the open will fail with
the MQRC_OBJECT_IN_USE return code.
}}
:END

:STREAM{ NAME{MQOPTOPN.INEXCL} TEXT{
\EM(ON)MQOO_INPUT_EXCLUSIVE\EM(OFF)\P\P
If this option is set then
WebSphere MQ will open the                                    /* @06 */
queue to get messages with exclusive access.\P\P
If the queue has already been opened for input by this or another
application, the open will fail with
the MQRC_OBJECT_IN_USE return code.
}}
:END

:STREAM{ NAME{MQOPTOPN.BROWSE} TEXT{
\EM(ON)MQOO_BROWSE\EM(OFF)\P\P
If this option is set then
WebSphere MQ will open the                                    /* @06 */
queue to browse messages.\P\P
A browse cursor will be established and positioned before the
first message on the queue.
}}
:END

:STREAM{ NAME{MQOPTOPN.OUTPUT} TEXT{
\EM(ON)MQOO_OUTPUT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will open the                                    /* @06 */
queue to put messages.\P\P
Messages can be retrieved by using MQGET calls.
}}
:END

:STREAM{ NAME{MQOPTOPN.INQUIRE} TEXT{
\EM(ON)MQOO_INQUIRE\EM(OFF)\P\P
If this option is set then
WebSphere MQ will open the                                    /* @06 */
object to inquire attributes.\P\P
The object can be a queue, namelist, process definition, or
queue manager.\P\P
Subsequent MQINQ calls be be used to obtain the object's attributes.
}}
:END

:STREAM{ NAME{MQOPTOPN.SET} TEXT{
\EM(ON)MQOO_SET\EM(OFF)\P\P
If this option is set then
WebSphere MQ will open the                                    /* @06 */
queue to set attributes.\P\P
Subsequent MQSET calls be be used to set the queue's attributes.
}}
:END

:STREAM{ NAME{MQOPTOPN.BINDOPEN} TEXT{
\EM(ON)MQOO_BIND_OPEN\EM(OFF)\P\P
If this option is set then
WebSphere MQ will bind the handle to a specific destination   /* @06 */
when the queue is opened.\P\P
This option is only applicable for cluster queues, and is ignored
for other types of queues.\P\P
All messages put using this
handle will be sent to the same instance of the destination
queue, and by the same route.
}}
:END

:STREAM{ NAME{MQOPTOPN.BINDNFIX} TEXT{
\EM(ON)MQOO_BIND_NOT_FIXED\EM(OFF)\P\P
If this option is set then
WebSphere MQ will not bind the handle to a specific           /* @06 */
destination when the queue is opened.\P\P                     /* @05 */
This option is only applicable for cluster queues, and is ignored
for other types of queues.\P\P
Messages put using this
handle may be sent to different instances of the destination
queue, or by a different route.
}}
:END

:STREAM{ NAME{MQOPTOPN.BINDQDEF} TEXT{
\EM(ON)MQOO_BIND_AS_Q_DEF\EM(OFF)\P\P
This means
WebSphere MQ will use the default binding for the queue.\P\P  /* @06 */
This option is defined to aid in program documentation.  It is
only applicable for cluster queues, and applies if neither the
\EM(on)MQOO_BIND_ON_OPEN\EM(off) nor the
\EM(on)MQOO_BIND_NOT_FIXED\EM(off) options are specified.
}}
:END

:STREAM{ NAME{MQOPTOPN.SYNC3} TEXT{
\EM(ON)MQOO_NO_SYNCPOINT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will put the message without                     /* @06 */
syncpoint control.\P\P                                        /* @05 */
This means the message, will be
immediately available to other applications.  The message
will not be deleted if the unit of work fails or is
backed out.\P\P
This option is the opposite of
\EM(on)MQOO_SYNCPOINT.\EM(off)\P\P
If neither \EM(on)MQOO_SYNCPOINT\EM(off) nor
\EM(on)MQOO_NO_SYNCPOINT\EM(off)
is specified the default depends on
the environment.\P\P  On OS/390 the default is
\EM(on)MQOO_SYNCPOINT,\EM(off) but on most other environments
it is \EM(on)MQOO_NO_SYNCPOINT.\EM(off)
}}
:END

:STREAM{ NAME{MQOPTOPN.SAVEALLC} TEXT{
\EM(ON)MQOO_SAVE_ALL_CONTEXT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will save all context information when a message /* @06 */
is retrieved.  This option is only applicable for queues
opened for input.\P\P
When a message is later put to a queue, the previously saved
context information can be passed to that message.
}}
:END

:STREAM{ NAME{MQOPTOPN.PASSID} TEXT{
\EM(ON)MQOO_PASS_IDENTITY_CONTEXT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will allow the                                   /* @06 */
\EM(on)MQPMO_PASS_INDENTITY_CONTEXT\EM(off)                   /* @05 */
parameter to be specified when a message is put to a
queue.  This option is only applicable for queues
opened for output.\P\P
This allows a message to be given the identity context
information from a previously opened input queue.\P\P
\IM('MQOPTPUT.PASSID')\P\P
\IM('MQOPTPUT.DEFCTEXT')
}}
:END

:STREAM{ NAME{MQOPTOPN.PASS_ALL} TEXT{
\EM(ON)MQOO_PASS_ALL_CONTEXT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will allow the                                   /* @06 */
\EM(on)MQPMO_PASS_ALL_CONTEXT\EM(off)                         /* @05 */
parameter to be specified when a message is put to a
queue.  This option is only applicable for queues
opened for output.\P\P
This allows a message to be given the identity
and origin context information
from a previously opened input queue.\P\P
\IM('MQOPTPUT.PASSID')\P\P
\IM('MQOPTPUT.DEFCTEXT')
}}
:END

:STREAM{ NAME{MQOPTOPN.SET_ID} TEXT{
\EM(ON)MQOO_SET_IDENTITY_CONTEXT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will allow the                                   /* @06 */
\EM(on)MQPMO_SET_IDENTITY_CONTEXT\EM(off)                     /* @05 */
parameter to be specified when a message is put to a
queue.  This option is only applicable for queues
opened for output.\P\P
This allows the program to set the identity context
information in the Message Descriptor structure
for the message when it is put.\P\P
\IM('MQOPTPUT.DEFCTEXT')
}}
:END

:STREAM{ NAME{MQOPTOPN.SET_ALL} TEXT{
\EM(ON)MQOO_SET_ALL_CONTEXT\EM(OFF)\P\P
If this option is set then
WebSphere MQ will allow the                                   /* @06 */
\EM(on)MQPMO_SET_ALL_CONTEXT\EM(off)                          /* @05 */
parameter to be specified when a message is put to a
queue.  This option is only applicable for queues
opened for output.\P\P
This allows the program to set the identity and origin context
information in the Message Descriptor structure
for the message when it is put.\P\P
\IM('MQOPTPUT.DEFCTEXT')
}}
:END

:STREAM{ NAME{MQOPTOPN.ALT_USER} TEXT{
\EM(ON)MQOO_ALTERNATE_USER_AUTHORITY\EM(OFF)\P\P
If this option is set then
validatation will be performed with the specified user identifier.\P\P
This indicates that the AlternateUserId field in the ObjDesc
parameter of the MQOPEN call contains a user identifier that
is to be used to validate authority to put messages on the
queue. \P\P
The call can succeed only if this AlternateUserId is
authorized to open the queue with the specified options,
regardless of whether the user identifier under which the
application is running is authorized to do so.  (This does
not apply to the context options specified, however, which
are always checked against the user identifier under which
the application is running.)
}}
:END

:STREAM{ NAME{MQOPTOPN.QUIESCE} TEXT{
\EM(ON)MQOO_FAIL_IF_QUIESCING\EM(OFF)\P\P
If this option is set then
the MQOPEN request will fail if the queue manager
or the CICS connection is quiescing.
}}
:END

:STREAM{ NAME{MQOPTOPN.YESOPT} TEXT{
\EM(ON)YES\EM(OFF)\P\P
This indicates that the specified option was coded on the MQPUT
call in the program.
}}
:END

:STREAM{ NAME{MQOPTOPN.NOOPT} TEXT{
\EM(ON)NO\EM(OFF)\P\P
This indicates that the specified option was not coded on the MQPUT
call in the program.
}}
:END

*   --------------------------------------------------------    @01
*   FOLLOWING SCREEN MQOPTOPN ADDED FOR ABEND-AID E-BUSINESS    @01
*   EDITION RELEASE 2.0.                                        @01
*   --------------------------------------------------------    @01

:SCREEN{ NAME{MQOPTOPN} TITLE{Open Options}
 TEMPLATE{KAZHDTMP.MQOPTOPN}                                  /* @08 */
  ORG{KAZ#MQOQ}                                               /* @03 */
  FIXED{
;       * ----------------------------------- *
;       * TEST ALL BITS IN QMGR OPTION BYTE 4 *
;       * ----------------------------------- *
  COND{ FNAME{BYTE4X00} DLOC{OPTBYTE4}
       COMPOP{TM,X'FF',Z} }
  COND{ FNAME{BYTE4X01} DLOC{OPTBYTE4}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{BYTE4X02} DLOC{OPTBYTE4}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{BYTE4X04} DLOC{OPTBYTE4}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{BYTE4X08} DLOC{OPTBYTE4}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{BYTE4X10} DLOC{OPTBYTE4}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{BYTE4X20} DLOC{OPTBYTE4}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{BYTE4X40} DLOC{OPTBYTE4}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{BYTE4X80} DLOC{OPTBYTE4}
       COMPOP{TM,X'80',O} }
;       * ----------------------------------- *
;       * TEST ALL BITS IN QMGR OPTION BYTE 3 *
;       * ----------------------------------- *
  COND{ FNAME{BYTE3X01} DLOC{OPTBYTE3}
       COMPOP{TM,X'01',O} }
  COND{ FNAME{BYTE3X02} DLOC{OPTBYTE3}
       COMPOP{TM,X'02',O} }
  COND{ FNAME{BYTE3X04} DLOC{OPTBYTE3}
       COMPOP{TM,X'04',O} }
  COND{ FNAME{BYTE3X08} DLOC{OPTBYTE3}
       COMPOP{TM,X'08',O} }
  COND{ FNAME{BYTE3X10} DLOC{OPTBYTE3}
       COMPOP{TM,X'10',O} }
  COND{ FNAME{BYTE3X20} DLOC{OPTBYTE3}
       COMPOP{TM,X'20',O} }
  COND{ FNAME{BYTE3X40} DLOC{OPTBYTE3}
       COMPOP{TM,X'40',O} }
  COND{ FNAME{BYTE3X80} DLOC{OPTBYTE3}
       COMPOP{TM,X'80',O} }
;
  COND{ FNAME{NOTB3XC0} DLOC{OPTBYTE3}
       COMPOP{TM,X'C0',Z} }
; * -------------------------- *
; * DISPLAY THE 'OPEN' OPTIONS *
; * -------------------------- *
  HEX{ FNAME{OPN@} POS{+2,36,8}
    DLOC{OPTVALUE}
    XNAME{Open Options}
    FDESC{ COL{1}
      TEXT{Open Options}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.OPEN')}
  }
; * ------------------------------------ *
; * DISPLAY THE 'INPUT_AS_Q_DEF' SETTING *
; * ------------------------------------ *
  LITERAL { POS{+2,36}
    FNAME{INASQ}
    XNAME{IN_As_Q_Def}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_INPUT_AS_Q_DEF}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.INASQDEF')}
  }
  IF { COND{BYTE4X01}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_01A}
          XNAME{IN_As_Q_Def_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.INASQDEF')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_01A}
          XNAME{IN_As_Q_Def_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.INASQDEF')}
          }
  }}
; * ---------------------------------- *
; * DISPLAY THE 'INPUT_SHARED' SETTING *
; * ---------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{INSHARE}
    XNAME{In_Shared}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_INPUT_SHARED}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.INSHARE')}
  }
  IF { COND{BYTE4X02}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_02A}
          XNAME{In_Shared_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.INSHARE')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_02A}
          XNAME{In_Shared_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.INSHARE')}
          }
  }}
; * ------------------------------------- *
; * DISPLAY THE 'INPUT_EXCLUSIVE' SETTING *
; * ------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{INEXCL}
    XNAME{In_Exclsive}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_INPUT_EXCLUSIVE}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.INEXCL')}
  }
  IF { COND{BYTE4X04}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_03A}
          XNAME{In_Excl_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.INEXCL')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_03A}
          XNAME{In_Excl_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.INEXCL')}
          }
  }}
; * ---------------------------- *
; * DISPLAY THE 'BROWSE' SETTING *
; * ---------------------------- *
  LITERAL { POS{+1,36}
    FNAME{BROWSE}
    XNAME{Browse}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_BROWSE}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.BROWSE')}
  }
  IF { COND{BYTE4X08}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_04A}
          XNAME{In_Browse_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.BROWSE')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_04A}
          XNAME{In_Browse_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.BROWSE')}
          }
  }}
; * ---------------------------- *
; * DISPLAY THE 'OUTPUT' SETTING *
; * ---------------------------- *
  LITERAL { POS{+1,36}
    FNAME{OUTPUT}
    XNAME{Output}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_OUTPUT}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.OUTPUT')}
  }
  IF { COND{BYTE4X10}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_05A}
          XNAME{In_Output_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.OUTPUT')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_05A}
          XNAME{In_Output_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.OUTPUT')}
          }
  }}
; * ----------------------------- *
; * DISPLAY THE 'INQUIRE' SETTING *
; * ----------------------------- *
  LITERAL { POS{+1,36}
    FNAME{INQUIRE}
    XNAME{Inquire}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_INQUIRE}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.INQUIRE')}
  }
  IF { COND{BYTE4X20}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_06A}
          XNAME{In_Inquire_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.INQUIRE')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_06A}
          XNAME{In_Inquire_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.INQUIRE')}
          }
  }}
; * ------------------------- *
; * DISPLAY THE 'SET' SETTING *
; * ------------------------- *
  LITERAL { POS{+1,36}
    FNAME{MQOO_SET}
    XNAME{MQOO_Set}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_SET}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.SET')}
  }
  IF { COND{BYTE4X40}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_07A}
          XNAME{MQOO_Set_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.SET')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_07A}
          XNAME{MQOO_Set_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.SET')}
          }
  }}
; * ---------------------------------- *
; * DISPLAY THE 'BIND_ON_OPEN' SETTING *
; * ---------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{BINDOPEN}
    XNAME{Bind_On_Open}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_BIND_ON_OPEN}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.BINDOPEN')}
  }
  IF { COND{BYTE3X40}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_08A}
          XNAME{Bind_On_Open_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.BINDOPEN')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_08A}
          XNAME{Bind_On_Open_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.BINDOPEN')}
          }
  }}
; * ------------------------------------ *
; * DISPLAY THE 'BIND_NOT_FIXED' SETTING *
; * ------------------------------------ *
  LITERAL { POS{+1,36}
    FNAME{BINDNFIX}
    XNAME{Bind_Not_Fixed}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_BIND_NOT_FIXED}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.BINDNFIX')}
  }
  IF { COND{BYTE3X80}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_09A}
          XNAME{Bind_Not_Fix_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.BINDNFIX')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_09A}
          XNAME{Bind_Not_Fix_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.BINDNFIX')}
          }
  }}
; * ----------------------------------- *
; * DISPLAY THE 'BIND_AS_Q_DEF' SETTING *
; * ----------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{BINDQDEF}
    XNAME{Bind_As_Q_Def}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_BIND_AS_Q_DEF}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.BINDQDEF')}
  }
  IF { COND{NOTB3XC0}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_10A}
          XNAME{Bind_Q_Def_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.BINDQDEF')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_10A}
          XNAME{Bind_Q_Def_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.BINDQDEF')}
          }
  }}
; * -------------------------------------- *
; * DISPLAY THE 'SAVE_ALL_CONTEXT' SETTING *
; * -------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{SAVEALLC}
    XNAME{Save_All_Ctxt}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_SAVE_ALL_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.SAVEALLC')}
  }
  IF { COND{BYTE4X80}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_11A}
          XNAME{Save_Allc_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.SAVEALLC')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_11A}
          XNAME{Save_Allc_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.SAVEALLC')}
          }
  }}
; * ------------------------------------------- *
; * DISPLAY THE 'PASS IDENTITY CONTEXT' SETTING *
; * ------------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{PASSID}
    XNAME{MQOO_Pass_ID}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_PASS_IDENTITY_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.PASSID')}
  }
  IF { COND{BYTE3X01}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_12A}
          XNAME{Pass_ID_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.PASSID')
               \P\P
               \IM('MQOPTOPN.DEFCTEXT')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_12A}
          XNAME{Pass_ID_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.PASSID')
               \P\P
               \IM('MQOPTOPN.DEFCTEXT')}
          }
  }}
; * -------------------------------------- *
; * DISPLAY THE 'PASS ALL CONTEXT' SETTING *
; * -------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{PASS_ALL}
    XNAME{MQOO_Pass_All}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_PASS_ALL_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.PASS_ALL')}
  }
  IF { COND{BYTE3X02}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_14A}
          XNAME{PassAll_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.PASS_ALL')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_14A}
          XNAME{PassAll_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.PASS_ALL')}
          }
  }}
; * ------------------------------------------ *
; * DISPLAY THE 'SET IDENTITY CONTEXT' SETTING *
; * ------------------------------------------ *
  LITERAL { POS{+1,36}
    FNAME{SET_ID}
    XNAME{MQOO_Set_ID}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_SET_IDENTITY_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.SET_ID')}
  }
  IF { COND{BYTE3X04}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_15A}
          XNAME{Set_ID_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.SET_ID')
               \P\P
               \IM('MQOPTOPN.DEFCTEXT')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_15A}
          XNAME{Set_ID_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.SET_ID')
               \P\P
               \IM('MQOPTOPN.DEFCTEXT')}
          }
  }}
; * ------------------------------------- *
; * DISPLAY THE 'SET ALL CONTEXT' SETTING *
; * ------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{SET_ALL}
    XNAME{MQOO_Set_All}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_SET_ALL_CONTEXT}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.SET_ALL')}
  }
  IF { COND{BYTE3X08}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_16A}
          XNAME{Set_All_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.SET_ALL')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_16A}
          XNAME{Set_All_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.SET_ALL')}
          }
  }}
; * ---------------------------------------------- *
; * DISPLAY THE 'ALTERNATE USER AUTHORITY' SETTING *
; * ---------------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{ALT_USER}
    XNAME{MQOO_Alt_User}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_ALTERNATE_USER_AUTHORITY}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.ALT_USER')}
  }
  IF { COND{BYTE3X10}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_17A}
          XNAME{AltUser_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.ALT_USER')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_17A}
          XNAME{AltUser_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.ALT_USER')}
          }
  }}
; * --------------------------------------- *
; * DISPLAY THE 'FAIL IF QUIESCING' SETTING *
; * --------------------------------------- *
  LITERAL { POS{+1,36}
    FNAME{QUIESCE}
    XNAME{MQOO_Quiescing}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQOO_FAIL_IF_QUIESCING}
      FILL{.}
    }
    HELP{\IM('MQOPTOPN.QUIESCE')}
  }
  IF { COND{BYTE3X20}
   THEN { LITERAL { POS{+0,36}
          FNAME{SET_18A}
          XNAME{Quiesce_Prog_Set}
          TEXT{YES}
          HELP{\IM('MQOPTOPN.YESOPT')
               \P\P
               \IM('MQOPTOPN.QUIESCE')}
          }
   }
   ELSE { LITERAL { POS{+0,36}
          FNAME{NOT_18A}
          XNAME{Quiesce_Prog_Off}
          TEXT{NO}
          HELP{\IM('MQOPTOPN.NOOPT')
               \P\P
               \IM('MQOPTOPN.QUIESCE')}
          }
  }}
 }                                           /* END OF FIXED  */
  HELP{
This screen displays information interpreted from the MQOO_OPTIONS
field. These options control the action of MQOPEN.\P\P
Each option which is supported on OS/390 for MQOPEN is shown, together
with its setting.  Help information is available for every option.  To
get the help information move the cursor to the option on the screen
and press <PF-1>.
  }
}                                            /* END OF SCREEN */
:END
*
*   --------------------------------------------------------    @01
*   FOLLOWING STREAMS ADDED FOR ABEND-AID E-BUSINESS            @01
*   EDITION RELEASE 2.0. FOR SCREEN MQOPTREP.                   @01
*   --------------------------------------------------------    @01

:STREAM{ NAME{MQOPTREP.REPORT} TEXT{
\EM(ON)Report Options\EM(OFF)\P\P
The value of the Report Options.\P\P  Each bit represents
a different setting which can be specified by the application
programmer.  The settings are broken down and shown on the
following lines on the terminal.
}}
:END

:STREAM{ NAME{MQOPTREP.EXCP} TEXT{
\EM(ON)MQRO_EXCEPTION\EM(OFF)\P\P
If this option is set then
exception reports are required.\P\P
Exception reports will not be generated if the application
can be notified synchronously by means of the return code
and reason code that delivery of the message failed.\P\P
}}
:END

:STREAM{ NAME{MQOPTREP.EXCPDATA} TEXT{
\EM(ON)MQRO_EXCEPTION_WITH_DATA\EM(OFF)\P\P
If this option is set then
exception reports are required.  In addition, the first
100 bytes of the message will be included in the report message.\P\P
Exception reports will not be generated if the application
can be notified synchronously by means of the return code
and reason code that delivery of the message failed.\P\P
}}
:END

:STREAM{ NAME{MQOPTREP.NOT_OS390} TEXT{
\P\P
This option is not supported for OS/390, but can be
specified on OS/390 if the message is destined for a different
platform which does support the option.  In this case
warning return and reason codes may be returned to the application
program.\P\P
The option may also appear to be set on OS/390 for a message
received on OS/390 from a non-OS/390 platform.  In this case the
option will be ignored on OS/390.
}}
:END

:STREAM{ NAME{MQOPTREP.EXCPFULL} TEXT{
\EM(ON)MQRO_EXCEPTION_WITH_FULL_DATA\EM(OFF)\P\P
If this option is set then
exception reports are required.  In addition, the entire
message data will be included in the report message.\P\P
Exception reports will not be generated if the application
can be notified synchronously by means of the return code
and reason code that delivery of the message failed.
\IM('MQOPTREP.NOT_OS390')
}}
:END

:STREAM{ NAME{MQOPTREP.XPIR} TEXT{
\EM(ON)MQRO_EXPIRATION\EM(OFF)\P\P
If this option is set then
expiration reports are required.\P\P
Expiration reports are generated when a message is discarded
prior to delivery to an application because its expiry time
has passed.
}}
:END

:STREAM{ NAME{MQOPTREP.XPIRDATA} TEXT{
\EM(ON)MQRO_EXPIRATION_WITH_DATA\EM(OFF)\P\P
If this option is set then
expiration reports are required.  In addition, the first
100 bytes of the message will be included in the report message.\P\P
Expiration reports are generated when a message is discarded
prior to delivery to an application because its expiry time
has passed.
}}
:END

:STREAM{ NAME{MQOPTREP.XPIRFULL} TEXT{
\EM(ON)MQRO_EXPIRATION_WITH_FULL_DATA\EM(OFF)\P\P
If this option is set then
expiration reports are required.  In addition, the entire
message data will be included in the report message.\P\P
Expiration reports are generated when a message is discarded
prior to delivery to an application because its expiry time
has passed.
\IM('MQOPTREP.NOT_OS390')
}}
:END

:STREAM{ NAME{MQOPTREP.COA} TEXT{
\EM(ON)MQRO_COA\EM(OFF)\P\P
If this option is set then
confirmation on arrival reports are required.\P\P
When the message is placed on the destination queue the confirmation
on arrival report is generated by the queue manager which owns
the destination queue.  Reports are not generated for messages
when they are placed on the transmission queue, nor for
undeliverable messages which are then placed on the dead-letter
queue.
}}
:END

:STREAM{ NAME{MQOPTREP.COADATA} TEXT{
\EM(ON)MQRO_COA_WITH_DATA\EM(OFF)\P\P
If this option is set then
confirmation on arrival reports are required.  In addition, the first
100 bytes of the message will be included in the report message.\P\P
When the message is placed on the destination queue the confirmation
on arrival report is generated by the queue manager which owns
the destination queue.  Reports are not generated for messages
when they are placed on the transmission queue, nor for
undeliverable messages which are then placed on the dead-letter
queue.
}}
:END

:STREAM{ NAME{MQOPTREP.COAFULL} TEXT{
\EM(ON)MQRO_COA_WITH_FULL_DATA\EM(OFF)\P\P
If this option is set then
confirmation on arrival reports are required.  In addition, the entire
message data will be included in the report message.\P\P
When the message is placed on the destination queue the confirmation
on arrival report is generated by the queue manager which owns
the destination queue.  Reports are not generated for messages
when they are placed on the transmission queue, nor for
undeliverable messages which are then placed on the dead-letter
queue.
\IM('MQOPTREP.NOT_OS390')
}}
:END

:STREAM{ NAME{MQOPTREP.COD} TEXT{
\EM(ON)MQRO_COD\EM(OFF)\P\P
If this option is set then
confirmation on delivery reports are required.\P\P
When the message is placed on the destination queue the confirmation
on arrival report is generated by the queue manager which owns
the destination queue.  Reports are not generated for
undeliverable messages which were placed on the dead-letter
queue.
}}
:END

:STREAM{ NAME{MQOPTREP.CODDATA} TEXT{
\EM(ON)MQRO_COD_WITH_DATA\EM(OFF)\P\P
If this option is set then
confirmation on delivery reports are required.  In addition, the first
100 bytes of the message will be included in the report message.\P\P
When the message is placed on the destination queue the confirmation
on arrival report is generated by the queue manager which owns
the destination queue.  Reports are not generated for
undeliverable messages which were placed on the dead-letter
queue.
}}
:END

:STREAM{ NAME{MQOPTREP.CODFULL} TEXT{
\EM(ON)MQRO_COD_WITH_FULL_DATA\EM(OFF)\P\P
If this option is set then
confirmation on delivery reports are required.  In addition, the
entire message data will be included in the report message.\P\P
When the message is placed on the destination queue the confirmation
on arrival report is generated by the queue manager which owns
the destination queue.  Reports are not generated for
undeliverable messages which were placed on the dead-letter
queue.
\IM('MQOPTREP.NOT_OS390')
}}
:END

:STREAM{ NAME{MQOPTREP.PAN} TEXT{
\EM(ON)MQRO_PAN\EM(OFF)\P\P
If this option is set then
positive action notification reports are required.\P\P
The queue manager conveys this request to the application
retrieving the message.  It is the responsibility of the retrieving
application to determine if this report is applicable, and to
generate this report.\P\P
The positive action
notification report indicates that the requested action was
performed successfully.
}}
:END

:STREAM{ NAME{MQOPTREP.NAN} TEXT{
\EM(ON)MQRO_NAN\EM(OFF)\P\P
If this option is set then
negative action notification reports are required.\P\P
The queue manager conveys this request to the application
retrieving the message.  It is the responsibility of the retrieving
application to determine if this report is applicable, and to
generate this report.\P\P
The negative action
notification report indicates that the requested action was
\EM(on)not\EM(off) performed successfully.
}}
:END

:STREAM{ NAME{MQOPTREP.NEWMSGID} TEXT{
\EM(ON)MQRO_NEW_MSG_ID\EM(OFF)\P\P
If this option is set then
a new MsgId is to be generated for any report or
reply generated as a result of this message.\P\P
There is no bit setting for this value.  This value
is used if the opposite option
\EM(on)MQRO_PASS_MSG_ID\EM(off) is not set.
}}
:END

:STREAM{ NAME{MQOPTREP.PASS_MSG} TEXT{
\EM(ON)MQRO_PASS_MSG_ID\EM(OFF)\P\P
If this option is set then
the MsgId of this message is to be copied to the
MsgId of any report or
reply generated as a result of this message.
}}
:END

:STREAM{ NAME{MQOPTREP.COPY_MSG} TEXT{
\EM(ON)MQRO_COPY_MSG_ID_TO_CORREL_ID\EM(OFF)\P\P
If this option is set then
the MsgId of this message is to be copied to the
CorrelId of any report or
reply generated as a result of this message.\P\P
There is no bit setting for this value.  This value
is used if the opposite option
\EM(on)MQRO_PASS_CORREL_ID\EM(off) is not set.
}}
:END

:STREAM{ NAME{MQOPTREP.CORREL_ID} TEXT{
\EM(ON)MQRO_PASS_CORREL_ID\EM(OFF)\P\P
If this option is set then
the CorrelId of this message is to be copied to the
CorrelId of any report or
reply generated as a result of this message.
}}
:END

:STREAM{ NAME{MQOPTREP.DEAD_LETTER_Q} TEXT{
\EM(ON)MQRO_DEAD_LETTER_Q\EM(OFF)\P\P
If this option is set then
if the message cannot be delivered to the destination queue
it should be placed on the dead-letter queue.\P\P
There is no bit setting for this value.  This value
is used if the opposite option
\EM(on)MQRO_DISCARD_MSG\EM(off) is not set.\P\P
On OS/390 this is the only supported option.
}}
:END

:STREAM{ NAME{MQOPTREP.DISCARD_MSG} TEXT{
\EM(ON)MQRO_DISCARD_MSG\EM(OFF)\P\P
If this option is set then
if the message cannot be delivered to the destination queue
it should be discarded.\P\P
On OS/390 this option is not supported and the message will
be placed on the dead-letter queue if it cannot be
delivered.  The value is shown because the destination queue
may be on a non-OS/390 platform which does support this option.
}}
:END

:STREAM{ NAME{MQOPTREP.YESOPT} TEXT{
\EM(ON)YES\EM(OFF)\P\P
This indicates that the specified option is set in the Report
Options field being used by WebSphere MQ.                     /* @06 */
}}
:END

:STREAM{ NAME{MQOPTREP.NOOPT} TEXT{
\EM(ON)NO\EM(OFF)\P\P
This indicates that the specified option is not set in the Report
Options field being used by WebSphere MQ.                     /* @06 */
}}
:END

:SCREEN{ NAME{MQOPTREP} TITLE{Report Options}
 TEMPLATE{KAZHDTMP.MQOPTREP}                                  /* @08 */
  ORG{KAZ#MQOQ}    /* REPX                                       @03 */
  FIXED{
;       * ----------------------------------- *
;       * FIRST BYTE
;       * ----------------------------------- *
  COND{ FNAME{EXCP1} DLOC{OPTBYTE1}     /* EXCEPTION             */
       COMPOP{CLI,X'01',E} }
  COND{ FNAME{EXCPWD} DLOC{OPTBYTE1}    /* EXCEPTION_WITH_DATA   */
       COMPOP{CLI,X'03',E} }
  COND{ FNAME{EXCPWFD} DLOC{OPTBYTE1}   /* EXCEPTION_WITH_FULL   */
       COMPOP{CLI,X'07',E} }
  COND{ FNAME{DISCMSG} DLOC{OPTBYTE1}   /* DISCARD_MSG           */
       COMPOP{CLI,X'08',E} }
;       * ----------------------------------- *
;       * SECOND BYTE
;       * ----------------------------------- *
  COND{ FNAME{EXPIR1} DLOC{OPTBYTE2}     /* EXPIRATION            */
       COMPOP{CLI,X'20',E} }
  COND{ FNAME{EXPIRWD} DLOC{OPTBYTE2}   /* EXPIRATION_WITH_DATA  */
       COMPOP{CLI,X'60',E} }
  COND{ FNAME{EXPIRWFD} DLOC{OPTBYTE2}  /* EXPIRATION_WITH_FULL  */
       COMPOP{CLI,X'E0',E} }
;       * ----------------------------------- *
;       * THIRD BYTE
;       * ----------------------------------- *
  COND{ FNAME{COA1} DLOC{OPTBYTE3}      /* COA                   */
       COMPOP{CLI,X'01',E} }
  COND{ FNAME{COAWD} DLOC{OPTBYTE3}     /* COA_WITH_DATA         */
       COMPOP{CLI,X'03',E} }
  COND{ FNAME{COAWFD} DLOC{OPTBYTE3}    /* COA_WITH_FULL         */
       COMPOP{CLI,X'07',E} }
  COND{ FNAME{COD1} DLOC{OPTBYTE3}      /* COD                   */
       COMPOP{CLI,X'08',E} }
  COND{ FNAME{CODWD} DLOC{OPTBYTE3}     /* COD_WITH_DATA         */
       COMPOP{CLI,X'18',E} }
  COND{ FNAME{CODWFD} DLOC{OPTBYTE3}    /* COD_WITH_FULL         */
       COMPOP{CLI,X'38',E} }
;       * ----------------------------------- *
;       * FOURTH BYTE
;       * ----------------------------------- *
  COND{ FNAME{DEFTS} DLOC{OPTBYTE4}     /* DEFAULTS              */
       COMPOP{CLI,X'00',E} }
  COND{ FNAME{PAN1} DLOC{OPTBYTE4}      /* PAN                   */
       COMPOP{CLI,X'01',E} }
  COND{ FNAME{NAN1} DLOC{OPTBYTE4}      /* NAN                   */
       COMPOP{CLI,X'02',E} }
  COND{ FNAME{PASSCORR} DLOC{OPTBYTE4}  /* PASS_CORREL_ID        */
       COMPOP{CLI,X'40',E} }
  COND{ FNAME{PASSMSG} DLOC{OPTBYTE4}   /* PASS_MSG_ID           */
       COMPOP{CLI,X'80',E} }
;
; * ---------------------------- *
; * DISPLAY THE 'REPORT' OPTIONS *
; * ---------------------------- *
;
  HEX{ FNAME{OPN@} POS{+1,34,8}
    DLOC{OPTVALUE}
    XNAME{Report Options}
    FDESC{ COL{1}
      TEXT{Report Options}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.REPORT')}
  }
; * -------------------------------------- *
; * DISPLAY THE 'EXCEPTION_REPORT' SETTING *
; * -------------------------------------- *
  LITERAL { POS{+2,34}
    FNAME{EXCP}
    XNAME{Exception}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_EXCEPTION}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.EXCP')}
  }
  IF { COND{EXCP1}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_01A}
          XNAME{Exception}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.EXCP')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_01A}
          XNAME{Exception}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.EXCP')}
          }
  }}
; * ------------------------------- *
; * DISPLAY A LITERAL ON THE SCREEN *
; * ------------------------------- *
  LITERAL { POS{+0,40,35}
    FNAME{LITERAL1}
    XNAME{Literal1}
    ATTR{ EMPH }
    TEXT{Message and Correlation ID Options:}
  }
; * ------------------------------------------------ *
; * DISPLAY THE 'EXCEPTION_REPORT_WITH_DATA' SETTING *
; * ------------------------------------------------ *
  LITERAL { POS{+1,34}
    FNAME{EXCPDATA}
    XNAME{Exception_Data}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_EXCEPTION_WITH_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.EXCPDATA')}
  }
  IF { COND{EXCPWD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_02A}
          XNAME{Exception_Data}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.EXCPDATA')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_02A}
          XNAME{Exception_Data}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.EXCPDATA')}
          }
  }}
; * -------------------------------- *
; * DISPLAY THE 'NEW_MSG_ID' SETTING *
; * -------------------------------- *
  LITERAL { POS{+0,72}
    FNAME{NEWMSGID}
    XNAME{NewMsgID}
    TEXT{ }
    FDESC{ COL{40}
      TEXT{MQRO_NEW_MSG_ID}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.NEWMSGID')}
  }
  IF { COND{DEFTS}
   THEN { LITERAL { POS{+0,72}
          FNAME{SET_51A}
          XNAME{NewMsgID}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.NEWMSGID')}
          }
   }
   ELSE { LITERAL { POS{+0,72}
          FNAME{NOT_51A}
          XNAME{NewMsgID}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.NEWMSGID')}
          }
  }}
; * ----------------------------------------------------- *
; * DISPLAY THE 'EXCEPTION_REPORT_WITH_FULL_DATA' SETTING *
; * ----------------------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{EXCPFULL}
    XNAME{Exception_FULL}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_EXCEPTION_WITH_FULL_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.EXCPFULL')}
  }
  IF { COND{EXCPWFD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_03A}
          XNAME{Exception_FULL}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.EXCPFULL')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_03A}
          XNAME{Exception_FULL}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.EXCPFULL')}
          }
  }}
; * --------------------------------- *
; * DISPLAY THE 'PASS_MSG_ID' SETTING *
; * --------------------------------- *
  LITERAL { POS{+0,72}
    FNAME{PASS_MSG}
    XNAME{Pass_Msg}
    TEXT{ }
    FDESC{ COL{40}
      TEXT{MQRO_PASS_MSG_ID}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.PASS_MSG')}
  }
  IF { COND{PASSMSG}
   THEN { LITERAL { POS{+0,72}
          FNAME{SET_52A}
          XNAME{Pass_Msg}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.PASS_MSG')}
          }
   }
   ELSE { LITERAL { POS{+0,72}
          FNAME{NOT_17A}
          XNAME{Pass_Msg}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.PASS_MSG')}
          }
  }}
; * --------------------------------------- *
; * DISPLAY THE 'EXPIRATION_REPORT' SETTING *
; * --------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{XPIR}
    XNAME{Expiration}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_EXPIRATION}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.XPIR')}
  }
  IF { COND{EXPIR1}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_04A}
          XNAME{Expiration}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.XPIR')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_04A}
          XNAME{Expiration}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.XPIR')}
          }
  }}
; * ---------------------------------------------- *
; * DISPLAY THE 'COPY_MSG_ID_TO_CORREL_ID' SETTING *
; * ---------------------------------------------- *
  LITERAL { POS{+0,72}
    FNAME{COPY_MSG}
    XNAME{Copy_Msg}
    TEXT{ }
    FDESC{ COL{40}
      TEXT{MQRO_COPY_MSG_ID_TO_CORREL_ID}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.COPY_MSG')}
  }
  IF { COND{DEFTS}
   THEN { LITERAL { POS{+0,72}
          FNAME{SET_53A}
          XNAME{Copy_Msg}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.COPY_MSG')}
          }
   }
   ELSE { LITERAL { POS{+0,72}
          FNAME{NOT_53A}
          XNAME{Copy_Msg}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.COPY_MSG')}
          }
  }}
; * ------------------------------------------------- *
; * DISPLAY THE 'EXPIRATION_REPORT_WITH_DATA' SETTING *
; * ------------------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{XPIRDATA}
    XNAME{ExpirationData}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_EXPIRATION_WITH_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.XPIRDATA')}
  }
  IF { COND{EXPIRWD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_05A}
          XNAME{ExpirationData}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.XPIRDATA')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_05A}
          XNAME{ExpirationData}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.XPIRDATA')}
          }
  }}
; * ------------------------------------ *
; * DISPLAY THE 'PASS_CORREL_ID' SETTING *
; * ------------------------------------ *
  LITERAL { POS{+0,72}
    FNAME{CORRELID}
    XNAME{Correl_ID}
    TEXT{ }
    FDESC{ COL{40}
      TEXT{MQRO_PASS_CORREL_ID}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.CORREL_ID')}
  }
  IF { COND{PASSCORR}
   THEN { LITERAL { POS{+0,72}
          FNAME{SET_54A}
          XNAME{Correl_ID}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.CORREL_ID')}
          }
   }
   ELSE { LITERAL { POS{+0,72}
          FNAME{NOT_54A}
          XNAME{Correl_ID}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.CORREL_ID')}
          }
  }}
; * ------------------------------------------------------ *
; * DISPLAY THE 'EXPIRATION_REPORT_WITH_FULL_DATA' SETTING *
; * ------------------------------------------------------ *
  LITERAL { POS{+1,34}
    FNAME{XPIRFULL}
    XNAME{ExpirationFull}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_EXPIRATION_WITH_FULL_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.XPIRFULL')}
  }
  IF { COND{EXPIRWFD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_06A}
          XNAME{ExpirationFull}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.XPIRFULL')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_06A}
          XNAME{ExpirationFull}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.XPIRFULL')}
          }
  }}
; * ---------------------------------------- *
; * DISPLAY THE 'CONFIRM_ON_ARRIVAL' SETTING *
; * ---------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{CON_OA}
    XNAME{CON_OA}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_COA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.COA')}
  }
  IF { COND{COA1}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_07A}
          XNAME{CON_OA}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.COA')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_07A}
          XNAME{CON_OA}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.COA')}
          }
  }}
; * ------------------------------- *
; * DISPLAY A LITERAL ON THE SCREEN *
; * ------------------------------- *
  LITERAL { POS{+0,40,31}
    FNAME{LITERAL2}
    XNAME{Literal2}
    ATTR{ EMPH }
    TEXT{Disposition Options:}
  }
; * -------------------------------------------------- *
; * DISPLAY THE 'CONFIRM_ON_ARRIVAL_WITH_DATA' SETTING *
; * -------------------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{COADATA}
    XNAME{CoaData}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_COA_WITH_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.COADATA')}
  }
  IF { COND{COAWD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_08A}
          XNAME{CoaData}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.COADATA')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_08A}
          XNAME{CoaData}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.COADATA')}
          }
  }}
; * --------------------------------------- *
; * DISPLAY THE 'DEAD_LETTER_QUEUE' SETTING *
; * --------------------------------------- *
  LITERAL { POS{+0,72}
    FNAME{DEAD_Q}
    XNAME{Dead_Letter_Q}
    TEXT{ }
    FDESC{ COL{40}
      TEXT{MQRO_DEAD_LETTER_Q}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.DEAD_LETTER_Q')}
  }
  IF { COND{DEFTS}
   THEN { LITERAL { POS{+0,72}
          FNAME{SET_55A}
          XNAME{Dead_Letter_Q}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.DEAD_LETTER_Q')}
          }
   }
   ELSE { LITERAL { POS{+0,72}
          FNAME{NOT_55A}
          XNAME{Dead_Letter_Q}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.DEAD_LETTER_Q')}
          }
  }}
; * ------------------------------------------------------- *
; * DISPLAY THE 'CONFIRM_ON_ARRIVAL_WITH_FULL_DATA' SETTING *
; * ------------------------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{COAFULL}
    XNAME{CoaFull}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_COA_WITH_FULL_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.COAFULL')}
  }
  IF { COND{COAWFD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_09A}
          XNAME{CoaFull}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.COAFULL')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_09A}
          XNAME{CoaFull}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.COAFULL')}
          }
  }}
; * ------------------------------------- *
; * DISPLAY THE 'DISCARD_MESSAGE' SETTING *
; * ------------------------------------- *
  LITERAL { POS{+0,72}
    FNAME{DISCARD}
    XNAME{Discard_Msg}
    TEXT{ }
    FDESC{ COL{40}
      TEXT{MQRO_DISCARD_MSG}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.DISCARD_MSG')}
  }
  IF { COND{DISCMSG}
   THEN { LITERAL { POS{+0,72}
          FNAME{SET_56A}
          XNAME{Discard_Msg}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.DISCARD_MSG')}
          }
   }
   ELSE { LITERAL { POS{+0,72}
          FNAME{NOT_56A}
          XNAME{Discard_Msg}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.DISCARD_MSG')}
          }
  }}
; * ----------------------------------------- *
; * DISPLAY THE 'CONFIRM_ON_DELIVERY' SETTING *
; * ----------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{COD_OA}
    XNAME{COD_OA}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_COD}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.COD')}
  }
  IF { COND{COD1}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_10A}
          XNAME{COD_OA}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.COD')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_10A}
          XNAME{COD_OA}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.COD')}
          }
  }}
; * --------------------------------------------------- *
; * DISPLAY THE 'CONFIRM_ON_DELIVERY_WITH_DATA' SETTING *
; * --------------------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{CODDATA}
    XNAME{CodData}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_COD_WITH_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.CODDATA')}
  }
  IF { COND{CODWD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_11A}
          XNAME{CodData}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.CODDATA')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_11A}
          XNAME{CodData}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.CODDATA')}
          }
  }}
; * -------------------------------------------------------- *
; * DISPLAY THE 'CONFIRM_ON_DELIVERY_WITH_FULL_DATA' SETTING *
; * -------------------------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{CODFULL}
    XNAME{CodFull}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_COD_WITH_FULL_DATA}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.CODFULL')}
  }
  IF { COND{CODWFD}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_12A}
          XNAME{CodFull}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.CODFULL')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_12A}
          XNAME{CodFull}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.CODFULL')}
          }
  }}
; * ------------------------------------- *
; * DISPLAY THE 'POSITIVE_ACTION' SETTING *
; * ------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{POS_ACT}
    XNAME{Pos_Act}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_PAN}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.PAN')}
  }
  IF { COND{PAN1}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_14A}
          XNAME{Pos_Act}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.PAN')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_14A}
          XNAME{Pos_Act}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.PAN')}
          }
  }}
; * ------------------------------------- *
; * DISPLAY THE 'NEGATIVE_ACTION' SETTING *
; * ------------------------------------- *
  LITERAL { POS{+1,34}
    FNAME{NEG_ACT}
    XNAME{Neg_Act}
    TEXT{ }
    FDESC{ COL{1}
      TEXT{MQRO_NAN}
      FILL{.}
    }
    HELP{\IM('MQOPTREP.NAN')}
  }
  IF { COND{NAN1}
   THEN { LITERAL { POS{+0,34}
          FNAME{SET_15A}
          XNAME{Neg_Act}
          TEXT{YES}
          HELP{\IM('MQOPTREP.YESOPT')
               \P\P
               \IM('MQOPTREP.NAN')}
          }
   }
   ELSE { LITERAL { POS{+0,34}
          FNAME{NOT_15A}
          XNAME{Neg_Act}
          TEXT{NO}
          HELP{\IM('MQOPTREP.NOOPT')
               \P\P
               \IM('MQOPTREP.NAN')}
          }
  }}
 }                                           /* END OF FIXED  */
  HELP{
This screen displays information interpreted from the MQRO_OPTIONS
in the message descriptors.  These control the generation of
reports.\P\P
Each option which is supported on OS/390 is shown, together
with its setting.  Help information is available for every option.  To
get the help information move the cursor to the option on the screen
and press <PF-1>.
  }
}                                            /* END OF SCREEN */
:END

*                                                               /*@04*/
*   --------------------------------------------------------    /*@04*/
*   FOLLOWING STREAMS ADDED FOR SCREEN MQOPTMGF.                /*@04*/
*   --------------------------------------------------------    /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.MSGFLGS} TEXT{                           /*@04*/
\EM(ON)Report Options\EM(OFF)\P\P                               /*@04*/
The value of the MQMD Message Flags.\P\P  Each bit represents   /*@04*/
a different setting which can be specified by the application   /*@04*/
programmer.  The settings are broken down and shown on the      /*@04*/
following lines on the terminal.                                /*@04*/
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.SEGINH} TEXT{                            /*@04*/
\EM(ON)MQMF_SEGMENTATION_INHIBITED\EM(OFF)\P\P                  /*@04*/
If this option is set then                                      /*@04*/
MQ Message Segmentation is inhibited.\P\P                       /*@04*/
The queue manager is prevented from breaking the message into   /*@04*/
segments or message segments into smaller segments. \P\P        /*@04*/
Default value of this flag is binary zero. \P\P                 /*@04*/
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.SEGALL} TEXT{                            /*@04*/
\EM(ON)MQMF_SEGMENTATION_ALLOWED\EM(OFF)\P\P                    /*@04*/
If this option is set then                                      /*@04*/
MQ Messageg Segmentation is allowed.  The queue manager         /*@04*/
can break messages into segments.  Also, message segments can   /*@04*/
be broken into smaller segments. \P\P                           /*@04*/
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.SEGMNT} TEXT{                            /*@04*/
\P\P                                                            /*@04*/
This option indicates a message is a segment of a logical       /*@04*/
message.  \P\P                                                  /*@04*/
Note:  If MQMF_SEGMENT is specified without MQMF_LAST_SEGMENT   /*@04*/
also being specified then the application message data length   /*@04*/
(minus the engths of MQ header structures) must be at least     /*@04*/
one. \P\P                                                       /*@04*/
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.MSGNGP} TEXT{                            /*@04*/
\EM(ON)MQMF_MSG_IN_GROUP\EM(OFF)\P\P                            /*@04*/
If this option is set then the message is a member of a         /*@04*/
group. \P\P                                                     /*@04*/
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.LSTNGP} TEXT{                            /*@04*/
\EM(ON)MQMF_LAST_MSG_IN_GROUP\EM(OFF)\P\P                       /*@04*/
If this option is set then the queue manager turns on           /*@04*/
MQMF_MSG_IN_GROUP in the copt of MQMD that is sent with         /*@04*/
the message, but no updates are made to the flags providedq     /*@04*/
by the application on the MQPUT or MQPUT1 call.                 /*@04*/
A group can consist of one logical message.  In that instance,  /*@04*/
the MsgSeqNumber field has a value of one and                   /*@04*/
MQMF_LAST_MSG_IN_GROUP is set.  \P\P                            /*@04*/
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.LSTSEG} TEXT{                            /*@04*/
\EM(ON)MQMF_LAST_SEGMENT\EM(OFF)\P\P                            /*@04*/
If this option is set then the message is the                   /*@04*/
last logical message in a group.\P\P                            /*@04*/
When specified, the the queue manger sets MQMF_SEGEMENT         /*@04*/
in the MQMD that is sent with the message, but not the MQMD     /*@04*/
specified by the application for the MQPUT or MQPUT1 call. /P/P /*@04*/
A logical message can consist of only one segment.  In that     /*@04*/
instance the Offset field is zero but MQMF_LAST_SEGMENT is      /*@04*/
set. /P/P                                                       /*@04*/
It is possible for the application message data length to be    /*@04*/
zero (minus any header structure lengths) when MQMF_LAST_SEGMENT/*@04*/
has been set. /P/P                                              /*@04*/
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.YESOPT} TEXT{                            /*@04*/
\EM(ON)YES\EM(OFF)\P\P                                          /*@04*/
This indicates that the specified bit flag is set in the MQMD   /*@04*/
Message Flags being used by WebSphere MQ. \P\P                /* @06 */
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:STREAM{ NAME{MQOPTMGF.NOOPT} TEXT{                             /*@04*/
\EM(ON)NO\EM(OFF)\P\P                                           /*@04*/
This indicates that the specified bit flag is not set in the    /*@04*/
MQMD Message Flags field being used by WebSphere MQ. \P\P     /* @06 */
}}                                                              /*@04*/
:END                                                            /*@04*/
*                                                               /*@04*/
:SCREEN{ NAME{MQOPTMGF} TITLE{MQMD Message Flags}               /*@04*/
 TEMPLATE{KAZHDTMP.MQOPTMGF}                                  /* @08 */
  ORG{KAZ#MQOQ}                                                 /*@04*/
  FIXED{                                                        /*@04*/
;       * ----------------------------------- *                 /*@04*/
;       * FIRST BYTE                                            /*@04*/
;       * ----------------------------------- *                 /*@04*/
;       * ----------------------------------- *                 /*@04*/
;       * SECOND BYTE                                           /*@04*/
;       * ----------------------------------- *                 /*@04*/
;       * ----------------------------------- *                 /*@04*/
;       * THIRD BYTE                                            /*@04*/
;       * ----------------------------------- *                 /*@04*/
;       * ----------------------------------- *                 /*@04*/
;       * FOURTH BYTE                                           /*@04*/
;       * ----------------------------------- *                 /*@04*/
  COND{ FNAME{SEGINH} DLOC{OPTBYTE4}    /* SEGMENTATION INHIBITED @04*/
       COMPOP{TM,X'00',O} }                                     /*@04*/
  COND{ FNAME{SEGALL} DLOC{OPTBYTE4}    /* SEGMENTATION ALLOWED   @04*/
       COMPOP{TM,X'01',O} }                                     /*@04*/
  COND{ FNAME{SEGMNT} DLOC{OPTBYTE4}    /* SEGMENT                @04*/
       COMPOP{TM,X'02',O} }                                     /*@04*/
  COND{ FNAME{LSTNGP} DLOC{OPTBYTE4}    /* LAST IN GROUP          @04*/
       COMPOP{TM,X'10',O} }                                     /*@04*/
  COND{ FNAME{LSTSEG} DLOC{OPTBYTE4}    /* LAST SEGMENT           @04*/
       COMPOP{TM,X'04',O} }                                     /*@04*/
  COND{ FNAME{MSGNGP} DLOC{OPTBYTE4}    /* MESSAGE IN GROUP       @04*/
       COMPOP{TM,X'08',O} }                                     /*@04*/
/*                                                              /*@04*/
/*-------------------------------------------*                    @04*/
/*  DISPLAY THE 'MQMD MESSAGE FLAGS' OPTIONS *                    @04*/
/*-------------------------------------------*                    @04*/
/*                                                                @04*/
  HEX{ FNAME{MSGF} POS{+1,34,8}                                 /*@04*/
    DLOC{OPTVALUE}                                              /*@04*/
    XNAME{Message Flags}                                        /*@04*/
    FDESC{ COL{1}                                               /*@04*/
      TEXT{Message Flags}                                       /*@04*/
      FILL{.}                                                   /*@04*/
    }                                                           /*@04*/
    HELP{\IM('MQOPTMGF.MSGFLGS')}                               /*@04*/
  }                                                             /*@04*/
; * -------------------------------------------- *              /*@04*/
; * DISPLAY THE 'SEGMENTATION_INHIBITED' SETTING *              /*@04*/
; * -------------------------------------------- *              /*@04*/
  LITERAL { POS{+2,34}                                          /*@04*/
    FNAME{SEGINH}                                               /*@04*/
    XNAME{Seg. Inhibited}                                       /*@04*/
    TEXT{ }                                                     /*@04*/
    FDESC{ COL{1}                                               /*@04*/
      TEXT{MQMF_SEGMENTATION_INHIBITED}                         /*@04*/
      FILL{.}                                                   /*@04*/
    }                                                           /*@04*/
    HELP{\IM('MQOPTMGF.SEGINH')}                                /*@04*/
  }                                                             /*@04*/
  IF { COND{SEGINH}                                             /*@04*/
   THEN { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{SET_01A}                                        /*@04*/
          XNAME{Segmenation Inh}                                /*@04*/
          TEXT{YES}                                             /*@04*/
          HELP{\IM('MQOPTMGF.YESOPT')                           /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.SEGINH')}                          /*@04*/
          }                                                     /*@04*/
   }                                                            /*@04*/
   ELSE { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{NOT_01A}                                        /*@04*/
          XNAME{Seg. Inhibited}                                 /*@04*/
          TEXT{NO}                                              /*@04*/
          HELP{\IM('MQOPTMGF.NOOPT')                            /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.SEGINH')}                          /*@04*/
          }                                                     /*@04*/
  }}                                                            /*@04*/
; * ------------------------------------------ *                /*@04*/
; * DISPLAY THE 'SEGMENTATION ALLOWED' SETTING *                /*@04*/
; * ------------------------------------------ *                /*@04*/
  LITERAL { POS{+1,34}                                          /*@04*/
    FNAME{SEGALL}                                               /*@04*/
    XNAME{Seg. Allowed}                                         /*@04*/
    TEXT{ }                                                     /*@04*/
    FDESC{ COL{1}                                               /*@04*/
      TEXT{MQMF_SEGMENTATION_ALLOWED}                           /*@04*/
      FILL{.}                                                   /*@04*/
    }                                                           /*@04*/
    HELP{\IM('MQOPTMGF.SEGALL')}                                /*@04*/
  }                                                             /*@04*/
  IF { COND{SEGALL}                                             /*@04*/
   THEN { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{SET_02A}                                        /*@04*/
          XNAME{Seg. Allowed}                                   /*@04*/
          TEXT{YES}                                             /*@04*/
          HELP{\IM('MQOPTMGF.YESOPT')                           /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.SEGALL')}                          /*@04*/
          }                                                     /*@04*/
   }                                                            /*@04*/
   ELSE { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{NOT_02A}                                        /*@04*/
          XNAME{Seg. Allowed}                                   /*@04*/
          TEXT{NO}                                              /*@04*/
          HELP{\IM('MQOPTMGF.NOOPT')                            /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.SEGALL')}                          /*@04*/
          }                                                     /*@04*/
  }}                                                            /*@04*/
; * ----------------------------- *                             /*@04*/
; * DISPLAY THE 'SEGMENT' SETTING *                             /*@04*/
; * ----------------------------- *                             /*@04*/
  LITERAL { POS{+1,34}                                          /*@04*/
    FNAME{SEGMNT}                                               /*@04*/
    XNAME{Segment}                                              /*@04*/
    TEXT{ }                                                     /*@04*/
    FDESC{ COL{1}                                               /*@04*/
      TEXT{MQMF_SEGMENT}                                        /*@04*/
      FILL{.}                                                   /*@04*/
    }                                                           /*@04*/
    HELP{\IM('MQOPTMGF.SEGMNT')}                                /*@04*/
  }                                                             /*@04*/
  IF { COND{SEGMNT}                                             /*@04*/
   THEN { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{SET_51A}                                        /*@04*/
          XNAME{Segment}                                        /*@04*/
          TEXT{YES}                                             /*@04*/
          HELP{\IM('MQOPTMGF.YESOPT')                           /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.SEGMNT')}                          /*@04*/
          }                                                     /*@04*/
   }                                                            /*@04*/
   ELSE { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{NOT_51A}                                        /*@04*/
          XNAME{Segment}                                        /*@04*/
          TEXT{NO}                                              /*@04*/
          HELP{\IM('MQOPTMGF.NOOPT')                            /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.SEGMNT')}                          /*@04*/
          }                                                     /*@04*/
  }}                                                            /*@04*/
; * ----------------------------------------------------- *     /*@04*/
; * DISPLAY THE 'LAST IN GROUP' SETTING *                       /*@04*/
; * ----------------------------------------------------- *     /*@04*/
  LITERAL { POS{+1,34}                                          /*@04*/
    FNAME{LSTNGP}                                               /*@04*/
    XNAME{Last_IN_GROUP}                                        /*@04*/
    TEXT{ }                                                     /*@04*/
    FDESC{ COL{1}                                               /*@04*/
      TEXT{MQMF_LAST_MSG_IN_GROUP}                              /*@04*/
      FILL{.}                                                   /*@04*/
    }                                                           /*@04*/
    HELP{\IM('MQOPTMGF.LSTNGP')}                                /*@04*/
  }                                                             /*@04*/
  IF { COND{LSTNGP}                                             /*@04*/
   THEN { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{SET_03A}                                        /*@04*/
          XNAME{Last_In_Group}                                  /*@04*/
          TEXT{YES}                                             /*@04*/
          HELP{\IM('MQOPTMGF.YESOPT')                           /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.LSTNGP')}                          /*@04*/
          }                                                     /*@04*/
   }                                                            /*@04*/
   ELSE { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{NOT_03A}                                        /*@04*/
          XNAME{Last_In_Group}                                  /*@04*/
          TEXT{NO}                                              /*@04*/
          HELP{\IM('MQOPTMGF.NOOPT')                            /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.LSTNGP')}                          /*@04*/
          }                                                     /*@04*/
  }}                                                            /*@04*/
; * ---------------------------------- *                        /*@04*/
; * DISPLAY THE 'LAST SEGMENT' SETTING *                        /*@04*/
; * ---------------------------------- *                        /*@04*/
  LITERAL { POS{+1,34}                                          /*@04*/
    FNAME{LSTSEG}                                               /*@04*/
    XNAME{Last_Segment}                                         /*@04*/
    TEXT{ }                                                     /*@04*/
    FDESC{ COL{1}                                               /*@04*/
      TEXT{MQMF_LAST_SEGMENT}                                   /*@04*/
      FILL{.}                                                   /*@04*/
    }                                                           /*@04*/
    HELP{\IM('MQOPTMGF.LSTSEG')}                                /*@04*/
  }                                                             /*@04*/
  IF { COND{LSTSEG}                                             /*@04*/
   THEN { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{SET_52A}                                        /*@04*/
          XNAME{Last_Segment}                                   /*@04*/
          TEXT{YES}                                             /*@04*/
          HELP{\IM('MQOPTMGF.YESOPT')                           /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.LSTSEG')}                          /*@04*/
          }                                                     /*@04*/
   }                                                            /*@04*/
   ELSE { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{NOT_17A}                                        /*@04*/
          XNAME{Last_Segment}                                   /*@04*/
          TEXT{NO}                                              /*@04*/
          HELP{\IM('MQOPTMGF.NOOPT')                            /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.LSTSEG')}                          /*@04*/
          }                                                     /*@04*/
  }}                                                            /*@04*/
; * -------------------------------------- *                    /*@04*/
; * DISPLAY THE 'MESSAGE IN GROUP' SETTING *                    /*@04*/
; * -------------------------------------- *                    /*@04*/
  LITERAL { POS{+1,34}                                          /*@04*/
    FNAME{MSGNGRP}                                              /*@04*/
    XNAME{Message_In_Group}                                     /*@04*/
    TEXT{ }                                                     /*@04*/
    FDESC{ COL{1}                                               /*@04*/
      TEXT{MQMF_MSG_IN_GROUP}                                   /*@04*/
      FILL{.}                                                   /*@04*/
    }                                                           /*@04*/
    HELP{\IM('MQOPTMGF.MSGNGP')}                                /*@04*/
  }                                                             /*@04*/
  IF { COND{MSGNGP}                                             /*@04*/
   THEN { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{SET_04A}                                        /*@04*/
          XNAME{Message_In_Group}                               /*@04*/
          TEXT{YES}                                             /*@04*/
          HELP{\IM('MQOPTMGF.YESOPT')                           /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.MSGNGP')}                          /*@04*/
          }                                                     /*@04*/
   }                                                            /*@04*/
   ELSE { LITERAL { POS{+0,34}                                  /*@04*/
          FNAME{NOT_04A}                                        /*@04*/
          XNAME{Message_In_Group}                               /*@04*/
          TEXT{NO}                                              /*@04*/
          HELP{\IM('MQOPTMGF.NOOPT')                            /*@04*/
               \P\P                                             /*@04*/
               \IM('MQOPTMGF.MSGNGP')}                          /*@04*/
          }                                                     /*@04*/
  }}                                                            /*@04*/
 }                                           /* END OF FIXED      @04*/
  HELP{                                                         /*@04*/
This screen displays information interpreted from the           /*@04*/
MQMD_MSGFLAGS in the message descriptors. These flags indicate  /*@04*/
the message statues.  \P\P                                      /*@04*/
Help information is available for every option.  To get the     /*@04*/
help information move the cursor to the screen and press        /*@04*/
<PF-1>.                                                         /*@04*/
  }                                                             /*@04*/
}                                            /* END OF SCREEN     @04*/
:END                                                            /*@04*/
:SCREEN{ NAME{MQOPTMAT} TITLE{Match Options}                  /* @06 */
 TEMPLATE{KAZHDTMP.MQOPTMAT}                                  /* @08 */
  ORG{KAZ#MQOQ}                                               /* @06 */
  FIXED{                                                      /* @06 */
;       * ----------------------------------- *               /* @06 */
;       * TEST ALL BITS IN QMGR OPTION BYTE 4 *               /* @06 */
;       * ----------------------------------- *               /* @06 */
  COND{ FNAME{BYTE4X00} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'FF',Z} }                                   /* @06 */
  COND{ FNAME{BYTE4X01} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'01',O} }                                   /* @06 */
  COND{ FNAME{BYTE4X02} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'02',O} }                                   /* @06 */
  COND{ FNAME{BYTE4X04} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'04',O} }                                   /* @06 */
  COND{ FNAME{BYTE4X08} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'08',O} }                                   /* @06 */
  COND{ FNAME{BYTE4X10} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'10',O} }                                   /* @06 */
  COND{ FNAME{BYTE4X20} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'20',O} }                                   /* @06 */
  COND{ FNAME{BYTE4X40} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'40',O} }                                   /* @06 */
  COND{ FNAME{BYTE4X80} DLOC{OPTBYTE4}                        /* @06 */
       COMPOP{TM,X'80',O} }                                   /* @06 */
; * --------------------------- *                             /* @06 */
; * DISPLAY THE 'MATCH' OPTIONS *                             /* @06 */
; * --------------------------- *                             /* @06 */
  HEX{ FNAME{OPN@} POS{+1,36,8}                               /* @06 */
    DLOC{OPTVALUE}                                            /* @06 */
    XNAME{Match Options}                                      /* @06 */
    FDESC{ COL{1}                                             /* @06 */
      TEXT{Match Options}                                     /* @06 */
      FILL{.}                                                 /* @06 */
    }                                                         /* @06 */
    HELP{\IM('MQOPTMAT.MATCH')}                               /* @06 */
  }                                                           /* @06 */
; * ---------------------------------- *                      /* @06 */
; * DISPLAY THE 'MATCH_MSG_ID' SETTING *                      /* @06 */
; * ---------------------------------- *                      /* @06 */
  LITERAL { POS{+2,36}                                        /* @06 */
    FNAME{MSG_ID}                                             /* @06 */
    XNAME{Match_Msg_ID}                                       /* @06 */
    TEXT{ }                                                   /* @06 */
    FDESC{ COL{1}                                             /* @06 */
      TEXT{MQMO_MATCH_MSG_ID}                                 /* @06 */
      FILL{.}                                                 /* @06 */
    }                                                         /* @06 */
    HELP{\IM('MQOPTMAT.MSG_ID')}                              /* @06 */
  }                                                           /* @06 */
  IF { COND{BYTE4X01}                                         /* @06 */
   THEN { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{SET_01A}                                      /* @06 */
          XNAME{Match_Msg_ID_Set}                             /* @06 */
          TEXT{YES}                                           /* @06 */
          HELP{\IM('MQOPTMAT.YESOPT')                         /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.MSG_ID')}                        /* @06 */
          }                                                   /* @06 */
   }                                                          /* @06 */
   ELSE { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{NOT_01A}                                      /* @06 */
          XNAME{Match_Msg_ID_Off}                             /* @06 */
          TEXT{NO}                                            /* @06 */
          HELP{\IM('MQOPTMAT.NOOPT')                          /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.MSG_ID')}                        /* @06 */
          }                                                   /* @06 */
  }}                                                          /* @06 */
; * ------------------------------------- *                   /* @06 */
; * DISPLAY THE 'MATCH_CORREL_ID' SETTING *                   /* @06 */
; * ------------------------------------- *                   /* @06 */
  LITERAL { POS{+1,36}                                        /* @06 */
    FNAME{CORREL}                                             /* @06 */
    XNAME{Match_Correl_ID}                                    /* @06 */
    TEXT{ }                                                   /* @06 */
    FDESC{ COL{1}                                             /* @06 */
      TEXT{MQMO_MATCH_CORREL_ID}                              /* @06 */
      FILL{.}                                                 /* @06 */
    }                                                         /* @06 */
    HELP{\IM('MQOPTMAT.CORREL_ID')}                           /* @06 */
  }                                                           /* @06 */
  IF { COND{BYTE4X02}                                         /* @06 */
   THEN { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{SET_02A}                                      /* @06 */
          XNAME{Correl_ID_Set}                                /* @06 */
          TEXT{YES}                                           /* @06 */
          HELP{\IM('MQOPTMAT.YESOPT')                         /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.CORREL_ID')}                     /* @06 */
          }                                                   /* @06 */
   }                                                          /* @06 */
   ELSE { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{NOT_02A}                                      /* @06 */
          XNAME{Correl_ID_Off}                                /* @06 */
          TEXT{NO}                                            /* @06 */
          HELP{\IM('MQOPTMAT.NOOPT')                          /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.CORREL_ID')}                     /* @06 */
          }                                                   /* @06 */
  }}                                                          /* @06 */
; * ------------------------------------- *                   /* @06 */
; * DISPLAY THE 'MATCH_MSG_TOKEN' SETTING *                   /* @06 */
; * ------------------------------------- *                   /* @06 */
  LITERAL { POS{+1,36}                                        /* @06 */
    FNAME{TOKEN}                                              /* @06 */
    XNAME{Match_Msg_Token}                                    /* @06 */
    TEXT{ }                                                   /* @06 */
    FDESC{ COL{1}                                             /* @06 */
      TEXT{MQMO_MATCH_MSG_TOKEN}                              /* @06 */
      FILL{.}                                                 /* @06 */
    }                                                         /* @06 */
    HELP{\IM('MQOPTMAT.MSG_TOKEN')}                           /* @06 */
  }                                                           /* @06 */
  IF { COND{BYTE4X20}                                         /* @06 */
   THEN { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{SET_03A}                                      /* @06 */
          XNAME{Msg_Token_Set}                                /* @06 */
          TEXT{YES}                                           /* @06 */
          HELP{\IM('MQOPTMAT.YESOPT')                         /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.MSG_TOKEN')}                     /* @06 */
          }                                                   /* @06 */
   }                                                          /* @06 */
   ELSE { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{NOT_03A}                                      /* @06 */
          XNAME{Msg_Token_Off}                                /* @06 */
          TEXT{NO}                                            /* @06 */
          HELP{\IM('MQOPTMAT.NOOPT')                          /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.MSG_TOKEN')}                     /* @06 */
          }                                                   /* @06 */
  }}                                                          /* @06 */
                                                              /* @06 */
; * ------------------------------------- *                   /* @06 */
; * DISPLAY THE 'MATCH_GROUP_ID' SETTING  *                   /* @06 */
; * ------------------------------------- *                   /* @06 */
  LITERAL { POS{+1,36}                                        /* @06 */
    FNAME{GROUP_ID}                                           /* @06 */
    XNAME{Match_Group_Id}                                     /* @06 */
    TEXT{ }                                                   /* @06 */
    FDESC{ COL{1}                                             /* @06 */
      TEXT{MQMO_MATCH_GROUP_ID}                               /* @06 */
      FILL{.}                                                 /* @06 */
    }                                                         /* @06 */
    HELP{\IM('MQOPTMAT.MSG_TOKEN')}                           /* @06 */
  }                                                           /* @06 */
  IF { COND{BYTE4X04}                                         /* @06 */
   THEN { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{SET_04A}                                      /* @06 */
          XNAME{Msg_Group_ID_Set}                             /* @06 */
          TEXT{YES}                                           /* @06 */
          HELP{\IM('MQOPTMAT.YESOPT')                         /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.MSG_GROUP_ID')}                  /* @06 */
          }                                                   /* @06 */
   }                                                          /* @06 */
   ELSE { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{NOT_04A}                                      /* @06 */
          XNAME{Group_Id_Off}                                 /* @06 */
          TEXT{NO}                                            /* @06 */
          HELP{\IM('MQOPTMAT.NOOPT')                          /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.GROUP_ID')}                      /* @06 */
          }                                                   /* @06 */
  }}                                                          /* @06 */
; * ------------------------------------------- *             /* @06 */
; * DISPLAY THE 'MATCH_MSG_SEQ_NUMBER' SETTING  *             /* @06 */
; * ------------------------------------------- *             /* @06 */
  LITERAL { POS{+1,36}                                        /* @06 */
    FNAME{SEQNUM}                                             /* @06 */
    XNAME{SEQ_NUMBER}                                         /* @06 */
    TEXT{ }                                                   /* @06 */
    FDESC{ COL{1}                                             /* @06 */
      TEXT{MQMO_MATCH_MSG_SEQ_NUMBER}                         /* @06 */
      FILL{.}                                                 /* @06 */
    }                                                         /* @06 */
    HELP{\IM('MQOPTMAT.MSG_SEQ_NUMBER')}                      /* @06 */
  }                                                           /* @06 */
  IF { COND{BYTE4X08}                                         /* @06 */
   THEN { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{SET_05A}                                      /* @06 */
          XNAME{Seq_Number_Set}                               /* @06 */
          TEXT{YES}                                           /* @06 */
          HELP{\IM('MQOPTMAT.YESOPT')                         /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.MSG_SEQ_NUMBER')}                /* @06 */
          }                                                   /* @06 */
   }                                                          /* @06 */
   ELSE { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{NOT_05A}                                      /* @06 */
          XNAME{Seq_Number_Off}                               /* @06 */
          TEXT{NO}                                            /* @06 */
          HELP{\IM('MQOPTMAT.NOOPT')                          /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.MSG_SEQ_NUMBER')}                /* @06 */
          }                                                   /* @06 */
  }}                                                          /* @06 */
; * ------------------------------------------- *             /* @06 */
; * DISPLAY THE 'MATCH_OFFSET' SETTING  *                     /* @06 */
; * ------------------------------------------- *             /* @06 */
  LITERAL { POS{+1,36}                                        /* @06 */
    FNAME{OFFSET}                                             /* @06 */
    XNAME{Match_OFFSET}                                       /* @06 */
    TEXT{ }                                                   /* @06 */
    FDESC{ COL{1}                                             /* @06 */
      TEXT{MQMO_MATCH_OFFSET}                                 /* @06 */
      FILL{.}                                                 /* @06 */
    }                                                         /* @06 */
    HELP{\IM('MQOPTMAT.OFFSET')}                              /* @06 */
  }                                                           /* @06 */
  IF { COND{BYTE4X10}                                         /* @06 */
   THEN { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{SET_06A}                                      /* @06 */
          XNAME{Offset_Set}                                   /* @06 */
          TEXT{YES}                                           /* @06 */
          HELP{\IM('MQOPTMAT.YESOPT')                         /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.OFFSET')}                        /* @06 */
          }                                                   /* @06 */
   }                                                          /* @06 */
   ELSE { LITERAL { POS{+0,36}                                /* @06 */
          FNAME{NOT_06A}                                      /* @06 */
          XNAME{Offset_Off}                                   /* @06 */
          TEXT{NO}                                            /* @06 */
          HELP{\IM('MQOPTMAT.NOOPT')                          /* @06 */
               \P\P                                           /* @06 */
               \IM('MQOPTMAT.OFFSET')}                        /* @06 */
          }                                                   /* @06 */
  }}                                                          /* @06 */
 }                                                            /* @06 */
  HELP{This screen displays information interpreted from the  /* @06 */
       MQMO_OPTIONS field.  These options further control the /* @06 */
       action of MQGET.\P\P Each option which is supported on /* @06 */
       OS/390 is shown, together with its setting.  Help      /* @06 */
       information is available for every option.  To get the /* @06 */
       help information move the cursor to the option on the  /* @06 */
       screen and press <PF-1>.                               /* @06 */
  }                                                           /* @06 */
}                                                             /* @06 */
:END                                                          /* @06 */
*                                                             /* @06 */
:SCREEN{ NAME{MQOPMO} TITLE{PMO Detail}                       /* @06 */
 TEMPLATE{KAZHDTMP.MQOPMO}                                    /* @08 */
  ORG{KAZ#MQOQ}                                               /* @06 */
  FIXED{                                                      /* @06 */
    DP{ FNAME{F001}  DLOC{GPMOPMO@} }                         /* @06 */
    DP{ FNAME{F002}  DLOC{GPMOOPTN} }                         /* @06 */
                                                              /* @06 */
    COND{ FNAME{VALSTRUC} DLOC{GPMOFLAG}                      /* @06 */
         COMPOP{TM,SW_IDOK,O} }                               /* @06 */
    COND{ FNAME{VALVER} DLOC{GPMOFLAG}                        /* @06 */
         COMPOP{TM,SW_VEROK,O} }                              /* @06 */
                                                              /* @06 */
    HEX{ FNAME{PMO@}  POS{+2,25,8}                            /* @06 */
      DLOC{GPMOPMO@}                                          /* @06 */
      XNAME{PMO Address}                                      /* @06 */
      ATTR{ TABS }                                            /* @06 */
      HEXD{A,'PMO'}                                           /* @06 */
      FDESC{ COL{1} FILL{.}                                   /* @06 */
        TEXT{PMO Address}                                     /* @06 */
      }                                                       /* @06 */
      HELP{The address of the Put Message Options storage     /* @06 */
           block.                                             /* @06 */
      }                                                       /* @06 */
    }                                                         /* @06 */
    IF { COND{VALSTRUC}                                       /* @06 */
    THEN {                                                    /* @06 */
       CHAR { FNAME{STRUCTID} POS{+2,25,04}                   /* @06 */
         DLOC{GPMOID}                                         /* @06 */
         XNAME{Structure ID}                                  /* @06 */
         FDESC{ COL{1} FILL{.}                                /* @06 */
           TEXT{Structure ID}                                 /* @06 */
         }                                                    /* @06 */
         HELP{\IM('MQOPT.STRUCT')}                            /* @06 */
       }                                                      /* @06 */
    }                                                         /* @06 */
    ELSE {                                                    /* @06 */
       HEX { FNAME{STRUCTID} POS{+2,25,08}                    /* @06 */
         DLOC{GPMOID}                                         /* @06 */
         XNAME{Structure ID}                                  /* @06 */
         FDESC{ COL{1} FILL{.}                                /* @06 */
           TEXT{Structure ID}                                 /* @06 */
         }                                                    /* @06 */
         HELP{\IM('MQOPT.STRUCT')}                            /* @06 */
       }                                                      /* @06 */
       LITERAL { FNAME{STRUCT#} POS{+0,34,01}                 /* @06 */
         TEXT{#}                                              /* @06 */
         XNAME{Structure #}                                   /* @06 */
         HELP{\IM('MQOPT.STRUCT2')}                           /* @06 */
       }                                                      /* @06 */
    }}                                                        /* @06 */
    HEX { FNAME{VERSION} POS{+1,25,08}                        /* @06 */
      DLOC{GPMOVER}                                           /* @06 */
      XNAME{Version NUMBER}                                   /* @06 */
      FDESC{ COL{1} FILL{.}                                   /* @06 */
        TEXT{Version}                                         /* @06 */
      }                                                       /* @06 */
      HELP{\IM('MQOPT.VER')}                                  /* @06 */
    }                                                         /* @06 */
    IF { COND{NOT.VALVER}                                     /* @06 */
    THEN {                                                    /* @06 */
       LITERAL { FNAME{VERSION#} POS{+0,34,01}                /* @06 */
         TEXT{#}                                              /* @06 */
         XNAME{Version #}                                     /* @06 */
         HELP{\IM('MQOPT.VER2')}                              /* @06 */
       }                                                      /* @06 */
    }}                                                        /* @06 */
    HEX{ FNAME{PMOOPT}  POS{+1,25,8}                          /* @06 */
      DLOC{GPMOOPTN}                                          /* @06 */
      XNAME{PMOopt}                                           /* @06 */
      ATTR{ TABS }                                            /* @06 */
      COMMAND{ NAME{.DFLT} CMD{CPR MQM2 PUT @FF002}           /* @06 */
              DESC{Display PMO options} }                     /* @06 */
      FDESC{ COL{1} FILL{.}                                   /* @06 */
        TEXT{Options}                                         /* @06 */
      }                                                       /* @06 */
      HELP{These PMO options control processing to be used    /* @06 */
           for the MQPUT call.  Each bit represents a         /* @06 */
           different setting which can be specified by the    /* @06 */
           application programmer.  \P \P For further         /* @06 */
           information place the cursor on this field and     /* @06 */
           press <enter>.  The PMO options screen will be     /* @06 */
           displayed showing a breakdown of all the options.  /* @06 */
      }                                                       /* @06 */
    }                                                         /* @06 */
    LITERAL { FNAME{TIMEOUT} POS{+1,25,03}                    /* @06 */
      TEXT{N/A}                                               /* @06 */
      XNAME{Timeout}                                          /* @06 */
      FDESC{ COL{1} FILL{.}                                   /* @06 */
        TEXT{Timeout}                                         /* @06 */
      }                                                       /* @06 */
      HELP{\IM('MQOPT.RESERVED')}                             /* @06 */
    }                                                         /* @06 */
    HEX{ FNAME{CONTEXT}  POS{+1,25,8}                         /* @06 */
      DLOC{GPMOCTXT}                                          /* @06 */
      XNAME{Context}                                          /* @06 */
      FDESC{ COL{1} FILL{.}                                   /* @06 */
        TEXT{Context}                                         /* @06 */
      }                                                       /* @06 */
      HELP{If PASS_IDENTITY_CONTEXT or PASS_ALL_CONTEXT is    /* @06 */
           specified, this field must contain the input queue /* @06 */
           handle from which context information to be        /* @06 */
           associated with the message being put is taken.    /* @06 */
           \P \P If neither PASS_IDENTITY_CONTEXT nor         /* @06 */
           PASS_ALL_CONTEXT is specified, this field is       /* @06 */
           ignored.  \P                                       /* @06 */
      }                                                       /* @06 */
    }                                                         /* @06 */
    CHAR{ FNAME{QNAME}  POS{+1,25,48}                         /* @06 */
      DLOC{GPMOQNME}                                          /* @06 */
      XNAME{Queue Name}                                       /* @06 */
      FDESC{ COL{1} FILL{.}                                   /* @06 */
        TEXT{Resolved Queue Name}                             /* @06 */
      }                                                       /* @06 */
      HELP{This field is set by the queue manager to the name /* @06 */
           of the queue (after alias resolution) on which the /* @06 */
           message will be placed.  \P                        /* @06 */
      }                                                       /* @06 */
    }                                                         /* @06 */
    CHAR{ FNAME{QMGR}  POS{+1,25,48}                          /* @06 */
      DLOC{GPMOQMGR}                                          /* @06 */
      XNAME{Queue Manager}                                    /* @06 */
      FDESC{ COL{1} FILL{.}                                   /* @06 */
        TEXT{Resolved QMGR Name}                              /* @06 */
      }                                                       /* @06 */
      HELP{This is the name of the queue manager (after alias /* @06 */
           resolution) that owns the queue specified by       /* @06 */
           Resolved Queue Name.                               /* @06 */
      }                                                       /* @06 */
    }                                                         /* @06 */
  }                                                           /* @06 */
  HELP{This screen displays information interpreted from the  /* @06 */
       WebSphere MQ Put-Message Options (PMO) structure.      /* @06 */
  }                                                           /* @06 */
}                                                             /* @06 */
:END                                                          /* @06 */