KAZJ2MQI @GENMOD
*--------------------------------------------------------------------*
*                                                                    *
*                       MAINTENANCE LOG                              *
*                                                                    *
*--------------------------------------------------------------------*
*               DESCRIPTION            |   DATE   | WHO | CHG | PT#  *
*--------------------------------------------------------------------*
* AAV11R1.28 INITIAL DEVELOPMENT       | 01/19/07 | PJR |     |171792*
* AA.V11R2.5.B - WEBSPHERE MQ 2033     | 12/19/08 | DFS | @01 |181582*
* CORRECTIONS TO MQ SCREEN DISPLAY.    | 09/09/09 | BJS | @02 |190517*
* MFD-10545, CCID 092616               | 06/  /14 | GAT | @03 |092616*
* UPDATE TO SUPPORT WEB TEMPLATES      |          |     |     |092616*
*--------------------------------------------------------------------*
         COPY  KAZ#MQIN
         COPY  KAZ#VBFR
*
KAZJ2MQI FDB$CSCT
*
:SCREEN{ NAME{MQINFO} TITLE{WebSphere MQ Information}         /* @02 */
 TEMPLATE{KAZHDTMP.MQINFO}                                    /* @03 */
     ORG{KAZ#MQIN}
  FIXED{
;
  DP{FNAME{F004}     DLOC{MQINREAS} }       /* REASON CODE      */
  DP{FNAME{F005}     DLOC{MQIN@QS} }        /* Q OPTIONS        */
  DP{FNAME{F006}     DLOC{MQINQREL} }       /* MQ RELEASE   @02 */
;
; DISPLAY FLAGS
;------------------------------------------------------
  COND{FNAME{OLDFMT} DLOC{MQIN@FMT}                           /* @01 */
        COMPOP{CLC,'1',E} }                                   /* @01 */
;
; START
;------------------------------------------------------
    CHAR{ FNAME{QMGRNAME} POS{1,17,4}                         /* @02 */
      XNAME{QMGR NAME}                                        /* @02 */
      DLOC{MQINQMGR}                                          /* @02 */
      FDESC{ COL{1} FILL{.}                                   /* @02 */
        TEXT{QMgr Name}                                       /* @02 */
      }                                                       /* @02 */
      HELP{This is the name of the queue manager that was     /* @02 */
           connected to at the time of the dump. \P           /* @02 */
      }                                                       /* @02 */
    }                                                         /* @02 */
    CHAR{ FNAME{AUTHID}                                       /* @02 */
      POS{1,69,8}                                             /* @02 */
      XNAME{AUTHID}                                           /* @02 */
      DLOC{MQINAUTH}
      FDESC{ COL{48} FILL{.}                                  /* @02 */
        TEXT{Authorization ID}                                /* @02 */
      }                                                       /* @02 */
      HELP{The authorization ID that was active for this      /* @01 */
           transaction. \P                                    /* @01 */
      }                                                       /* @01 */
    }                                                         /* @02 */
    CHAR{ FNAME{QREL}                                         /* @02 */
      POS{2,17,5}                                             /* @02 */
      XNAME{QUEUE MGR REL}                                    /* @02 */
      DLOC{MQINQREL}                                          /* @02 */
      FDESC{ COL{1} FILL{.}
        TEXT{QMgr Release}                                    /* @02 */
      }                                                       /* @02 */
      HELP{The release of the queue manager that              /* @02 */
           was connected to at the time of the dump.          /* @02 */
      }                                                       /* @02 */
    }                                                         /* @02 */
    CHAR{ FNAME{CONN}                                         /* @02 */
      POS{2,69,8}                                             /* @02 */
      XNAME{CONNECT TYPE}                                     /* @02 */
      DLOC{MQINCONN}
      FDESC{ COL{48} FILL{.}                                  /* @02 */
        TEXT{Connection Type}                                 /* @02 */
      }                                                       /* @02 */
      HELP{The type of connection to the queue manager.       /* @02 */
      }                                                       /* @02 */
    }
     MENUOPT{SEL{1}  POS{4,18,45}                             /* @01 */
             TEXT{WebSphere MQ Diagnostic Information }       /* @01 */
             PADCMD{MQDIAG}                                   /* @01 */
             CMD{CPR MQDI @FF004 }                            /* @01 */
     }                                                        /* @01 */
     MENUOPT{SEL{2}  POS{6,18,45}                             /* @01 */
             TEXT{Last WebSphere MQ Call Information }        /* @01 */
             PADCMD{MQCALL}                                   /* @01 */
             CMD{CPR MQLC @FF006 }                            /* @02 */
     }                                                        /* @01 */
     IF { COND{OLDFMT} THEN {                                 /* @01 */
     MENUOPT{SEL{3}  POS{8,18,45}                             /* @01 */
             TEXT{Task's Opened Queues at Dump Time}          /* @01 */
             PADCMD{MQQDEFS}                                  /* @01 */
             CMD{CPR MQINQDEF @FF005 }                        /* @01 */
     }                                                        /* @01 */
     } ELSE {                                                 /* @01 */
     MENUOPT{SEL{3}  POS{8,18,45}                             /* @01 */
             TEXT{Task's Opened Queues at Dump Time}          /* @01 */
             PADCMD{MQOPEN}                                   /* @01 */
             CMD{CPR MQOQ @FF006 }                            /* @02 */
     }                                                        /* @01 */
  }                                                           /* @01 */
      }
      }
  HELP{                                                       /* @01 */ 03140000
This is the main menu for the WebSphere MQ information. \P    /* @01 */ 03150000
  }                                                           /* @01 */ 03160000
 }                                                            /* @01 */
:END
*
:SCREEN{ NAME{MQINQDEF} TITLE{WebSphere MQ Queue Definitions} /* @01 */
 TEMPLATE{KAZHDTMP.MQINQDEF}                                  /* @03 */
     ORG{KAZ#MQIN}
  FIXED{
;
  COND{FNAME{LOCAL} DLOC{MQIN@QL}
        COMPOP{CLC,'Y',E} }
  COND{FNAME{ALIAS} DLOC{MQIN@QA}
        COMPOP{CLC,'Y',E} }
  COND{FNAME{REMOTE} DLOC{MQIN@QR}
        COMPOP{CLC,'Y',E} }
;
  MENUOPT{SEL{1}  POS{2,18,60}
          TEXT{Display Local Queue Definition}
          PADCMD{MQLO}
          IF { COND{NOT.LOCAL} THEN {
             REQ{AXX63,KA0070}
             }}
          CMD{CPR MQCB MQLO }
         }
;
  MENUOPT{SEL{2}  POS{4,18,60}
          TEXT{Display Alias Queue Definition}
          PADCMD{MQAO}
          IF { COND{NOT.ALIAS} THEN {
             REQ{AXX63,KA0070}
             }}
          CMD{CPR MQCB MQAO }
         }
;
  MENUOPT{SEL{3} POS{6,18,60}
          TEXT{Display Remote Queue Definition}
          PADCMD{MQRO}
          IF { COND{NOT.REMOTE} THEN {
             REQ{AXX63,KA0070}
             }}
          CMD{CPR MQCB MQRO }
         }
;
;
;
  }
  HELP{Main screen help....
  }
}
:END
*
:SCREEN{ NAME{MQINVBFR} TITLE{Message Buffer Area}
 TEMPLATE{KAZHDTMP.MQINVBFR}                                  /* @03 */
  ORG{BUFSTRT}
  FIXED{
    VHEX{ FNAME{VHEXDATA}
      POS{0}
      DLOC{VHEXDATA,2,V}
      XNAME{VHEX Field Data}
      CHARLOC{ABOVE}
      GRIDLOC{BELOW}
      ADDRESS{DATAADDR}
      HEXD{A,'FIELD DATA'}
      HELP{The record's key data displayed in vertical hex format.  The
           tab selectable data at the start of the field is the virtual
           storage address of the field.  The contents of the field are
           described by four rows.\P\P
           Row #1 is the character interpretation of the field.\P\P
           Row #2 is the zone nibble of the byte.\P\P
           Row #3 is the digit nibble of the byte.\P\P
           Row #4 is the byte number counter (relative to one).
      }
    }
    BIN{ FNAME{DATALGTH}
      POS{0,1,8}
      XNAME{DATA LENGTH}
      DLOC{DATALEN}
      FDESC{
        TEXT{Message Buffer Length}
      }
      HELP{The length of the message buffer area. \P
      }
    }
  }
 TEXTWIN{ SKIP{1}
  TEXT{\EM(ON)Message Buffer Length:\EM(OFF)\F(DATALGTH)\P\P\F(VHEXDATA)
  }
 }
  HELP{This screen displays the message buffer area
       in vertical hex format. \P
  }
}
:END