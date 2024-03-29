KAZJ2MQL @GENMOD                                                        00031000
*                                                                       00040000
         TITLE '- LAST WebSphere MQ CALL INFORMATION'                   00050000
*--------------------------------------------------------------------*  00060000
*                    COMPUWARE CONFIDENTIAL                          *  00080000
*--------------------------------------------------------------------*  00100000
*                       MAINTENANCE LOG                              *  00120000
*--------------------------------------------------------------------*  00140000
*               DESCRIPTION                  |   DATE   | WHO | CHG  *  00150000
*--------------------------------------------------------------------*  00160000
* AA.V11R2.5.B - WEBSPHERE MQ 2033  - #181582| 12/19/08 | DFS |      *
*--------------------------------------------------------------------*  00160000
* TRANID MQM4 NOT FOUND             - #188520| 03/26/09 | DFS | @01  *
*--------------------------------------------------------------------*  00160000
* CORRECTIONS TO MQ SCREEN DISPLAY.   #190517| 09/15/09 | BJS | @02  *
*--------------------------------------------------------------------*  00160000
* ADDED TEMPLATE DEFINITIONS AFTER    #092616| 06/06/14 | SDK | @03  *
* SCREEN DEFINITIONS. MFD-10545              |          |     |      *
* ALSO ADDED FNAMES TO LITERALS THAT WERE    |          |     |      *
* MISSING THEM                               |          |     |      *
*--------------------------------------------------------------------*  00160000
*                                            |          |     |      *  00201000
*--------------------------------------------------------------------*  00210000
         EJECT                                                          00220000
*--------------------------------------------------------------------*  00230000
*                    COMPUWARE CONFIDENTIAL                          *  00250000
*--------------------------------------------------------------------*  00270000
*                        PROGRAM PROLOG                              *  00290000
*--------------------------------------------------------------------*  00310000
*                                                                    *  00320000
*      PROGRAM NAME: KAZJ2MQL                                        *  00330000
*                                                                    *  00340000
*    DISTRIBUTED BY: COMPUWARE CORPORATION                           *  00370000
*                                                                    *  00380000
*          FUNCTION: DEFINES THE SCREEN DEFINITIONS FOR THE          *  00390000
*                    LAST WEBSPHERE MQ CALL INFORMATION SCREENS.     *  00410000
*                                                                    *  00410000
*--------------------------------------------------------------------*  00530000
*
         EJECT                                                          00540000
*
         COPY  KAZ#MQLC                                                 00560000
*
KAZJ2MQL FDB$CSCT                                                       00580000
*
*
:SCREEN{ NAME{MQLOPEN} TITLE{Last WebSphere MQ Call Info}               00600000
 TEMPLATE{KAZHDTMP.MQLOPEN}                     /* @03 */
  ORG{KAZ#MQLC}                                                         00610000
  FIXED{                                                                00620000
;
    DP{ FNAME{F001}     DLOC{MQLCBFR@} }       /* MSGBFR ADDRESS  */
    DP{ FNAME{F002}     DLOC{MQLCBFRL} }       /* MSGBFR LENGTH   */
    DP{ FNAME{F003}     DLOC{MQLCQTYP} }       /* QUEUE TYPE      */
    DP{ FNAME{F004}     DLOC{MQLCHOBJ} }       /* HANDLE NUMBER   */
    DP{ FNAME{F005}     DLOC{MQLCRC} }         /* REASON CODE     */
    DP{ FNAME{F006}     DLOC{MQLCOPEN} }       /* MQ OPEN OPTION  */
    DP{ FNAME{F007}     DLOC{MQLCOPTN} }       /* PGM OPEN OPTION */
    DP{ FNAME{F009}     DLOC{MQLCQREL} }       /* MQ RELEASE  @02 */
;
   COND{ FNAME{CHKCODE} DLOC{MQLCRC}
         COMPOP{CLC,'2085',NL} }
   COND{ FNAME{GOTMHND} DLOC{MQLCMHND}
         COMPOP{CLC,'Y',E} }
   COND{ FNAME{GOODCC} DLOC{MQLCMQCC}
         COMPOP{CB,X'00000002',L} }
   COND{FNAME{OLDFMT} DLOC{MQLC@FMT}
         COMPOP{CLC,'1',E} }
;
    LITERAL{ FNAME{CALMOPEN} POS{1,1,40} /*->fixedPro<-*/ /* @03 */
        TEXT {CALL 'MQOPEN' USING}  }
    GROUP{ POS{2,1,79}
        DATACOL{25}
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HCONN}  POS{1,,8}
        XNAME{HCONN}
        DLOC{MQLCHCON}
        FDESC{ COL{7} FILL{.}
          TEXT{Hconn} }
        HELP{Connection Handle:  Input parameter \P\P
             This parameter represents the connection to the queue
             manager. The value was return on a previous MQCONN call.
             \P\P
             On OS/390 for CICS applications, the MQCONN call can be
             omitted and the value of MQHC_DEF_HCONN can be specified
             for this parameter. \P
        }
      } } }
      HEX{ FNAME{OBJDESC}  POS{2,,8}
        XNAME{OBJ DESCPRIPTOR}
        DLOC{MQLCOD@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Object Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQOD}
           DESC{Display Object Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{ObjDesc} }
        HELP{Object Descriptor:  Input/Output parameter \P\P
             This is the address of the object descriptor.\P\P
             The object descriptor is a structure that identifies the
             object to be opened. \P
        }
      }
      HEX{ FNAME{OPNOPTNS}  POS{3,,8}
        XNAME{OPEN OPTIONS}
        DLOC{MQLCOPTN}
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQM2 OPN @FF007}
           DESC{Display OPEN Options } }
        FDESC{ COL{7} FILL{.}
          TEXT{Options} }
        HELP{Options:  Input parameter \P\P
             Options that control the action of MQOPEN. \P\P
             At least one of the following options must be specified.
             \P\P
             MQOO_BROWSE                        \P
             MQOO_INPUT_* (only one of these)   \P
             MQOO_INQUIRE                       \P
             MQOO_OUTPUT                        \P
             MQOO_SET                           \P
        }
      }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HOBJECT}  POS{4,,8}
        XNAME{HOBJECT}
        DLOC{MQLCHOBJ}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQHI @FF004 C @FF009}                   /* @02 */
              DESC{Display Handle Information} }
        }}
        FDESC{ COL{7} FILL{.}
          TEXT{Hobj} }
        HELP{Object Handle:  Output parameter \P\P
             The object handle represents the access that has been
             established to an object. It must be specified on
             subsequent message queuing calls that operate on this
             object. \P
             It ceases to be valid when the MQCLOSE call is
             issued, or when the unit of processing that defines
             the scope of the handle terminates.
        }
      } } }
      BIN{ FNAME{COMPCODE} POS{5,,8}
        XNAME{COMP CODE}
        DLOC{MQLCMQCC}
        FDESC{ COL{7} FILL{.}
          TEXT{CompCode} }
        HELP{Completion Code:  Output parameter \P\P
             This is the completion code for the MQ API call. \P
        }
      }
      CHOICE{ FNAME{MQCCEQU} POS{5,40,20}
      XNAME{MQCCEQU}
      DLOC{MQLCMQCC}
       LISTV{
            VALUE{X'00','MQCC_OK'}
            VALUE{X'01','MQCC_WARNING'}
            VALUE{X'02','MQCC_FAILED'}
       }
      }
      CHAR{ FNAME{REASCODE} POS{6,,4}
        XNAME{REASON CODE}
        DLOC{MQLCRC}
        FDESC{ COL{7} FILL{.}
          TEXT{Reason} }
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQDI @FF005}
           DESC{Display Reason Code}
           }
        HELP{Reason Code:  Output parameter \P\P
             This is the reason code that qualifies the
             completion code for the MQ API call.
        }
      }
     CHOICE{ FNAME{RCEQU1} POS{6,40,30}
     XNAME{REASON EQU}
     DLOC{MQLCRC}
      LISTV{
           VALUE{'0000','MQRC_NONE'}
           VALUE{'2001','MQRC_ALIAS_BASE_Q_TYPE_ERROR'}
           VALUE{'2002','MQRC_ALREADY_CONNECTED'}
           VALUE{'2003','MQRC_BACKED_OUT'}
           VALUE{'2004','MQRC_BUFFER_ERROR'}
           VALUE{'2005','MQRC_BUFFER_LENGTH_ERROR'}
           VALUE{'2006','MQRC_CHAR_ATTR_LENGTH_ERROR'}
           VALUE{'2007','MQRC_CHAR_ATTRS_ERROR'}
           VALUE{'2008','MQRC_CHAR_ATTRS_TOO_SHORT'}
           VALUE{'2009','MQRC_CONNECTION_BROKEN'}
           VALUE{'2010','MQRC_DATA_LENGTH_ERROR'}
           VALUE{'2011','MQRC_DYNAMIC_Q_NAME_ERROR'}
           VALUE{'2012','MQRC_ENVIRONMENT_ERROR'}
           VALUE{'2013','MQRC_EXPIRY_ERROR'}
           VALUE{'2014','MQRC_FEEDBACK_ERROR'}
           VALUE{'2016','MQRC_GET_INHIBITED'}
           VALUE{'2017','MQRC_HANDLE_NOT_AVAILABLE'}
           VALUE{'2018','MQRC_HCONN_ERROR'}
           VALUE{'2019','MQRC_HOBJ_ERROR'}
           VALUE{'2020','MQRC_INHIBIT_VALUE_ERROR'}
           VALUE{'2021','MQRC_INT_ATTR_COUNT_ERROR'}
           VALUE{'2022','MQRC_INT_ATTR_COUNT_TOO_SMALL'}
           VALUE{'2023','MQRC_INT_ATTRS_ARRAY_ERROR'}
           VALUE{'2024','MQRC_SYNCPOINT_LIMIT_REACHED'}
           VALUE{'2025','MQRC_MAX_CONNS_LIMIT_REACHED'}
           VALUE{'2026','MQRC_MD_ERROR'}
           VALUE{'2027','MQRC_MISSING_REPLY_TO_Q'}
           VALUE{'2029','MQRC_MSG_TYPE_ERROR'}
           VALUE{'2030','MQRC_MSG_TOO_BIG_FOR_Q'}
           VALUE{'2031','MQRC_MSG_TOO_BIG_FOR_Q_MGR'}
           VALUE{'2033','MQRC_NO_MSG_AVAILABLE'}
           VALUE{'2034','MQRC_NO_MSG_UNDER_CURSOR'}
           VALUE{'2035','MQRC_NOT_AUTHORIZED'}
           VALUE{'2036','MQRC_NOT_OPEN_FOR_BROWSE'}
           VALUE{'2037','MQRC_NOT_OPEN_FOR_INPUT'}
           VALUE{'2038','MQRC_NOT_OPEN_FOR_INQUIRE'}
           VALUE{'2039','MQRC_NOT_OPEN_FOR_OUTPUT'}
           VALUE{'2040','MQRC_NOT_OPEN_FOR_SET'}
           VALUE{'2041','MQRC_OBJECT_CHANGED'}
           VALUE{'2042','MQRC_OBJECT_IN_USE'}
           VALUE{'2043','MQRC_OBJECT_TYPE_ERROR'}
           VALUE{'2044','MQRC_OD_ERROR'}
           VALUE{'2045','MQRC_OPTION_NOT_VALID_FOR_TYPE'}
           VALUE{'2046','MQRC_OPTIONS_ERROR'}
           VALUE{'2047','MQRC_PERSISTENCE_ERROR'}
           VALUE{'2048','MQRC_PERSISTENT_NOT_ALLOWED'}
           VALUE{'2049','MQRC_PRIORITY_EXCEEDS_MAXIMUM'}
           VALUE{'2050','MQRC_PRIORITY_ERROR'}
           VALUE{'2051','MQRC_PUT_INHIBITED'}
           VALUE{'2052','MQRC_Q_DELETED'}
           VALUE{'2053','MQRC_Q_FULL'}
           VALUE{'2055','MQRC_Q_NOT_EMPTY'}
           VALUE{'2056','MQRC_Q_SPACE_NOT_AVAILABLE'}
           VALUE{'2057','MQRC_Q_TYPE_ERROR'}
           VALUE{'2058','MQRC_Q_MGR_NAME_ERROR'}
           VALUE{'2059','MQRC_Q_MGR_NOT_AVAILABLE'}
           VALUE{'2061','MQRC_REPORT_OPTIONS_ERROR'}
           VALUE{'2062','MQRC_SECOND_MARK_NOT_ALLOWED'}
           VALUE{'2063','MQRC_SECURITY_ERROR'}
           VALUE{'2065','MQRC_SELECTOR_COUNT_ERROR'}
           VALUE{'2066','MQRC_SELECTOR_LIMIT_EXCEEDED'}
           VALUE{'2067','MQRC_SELECTOR_ERROR'}
           VALUE{'2068','MQRC_SELECTOR_NOT_FOR_TYPE'}
           VALUE{'2069','MQRC_SIGNAL_OUTSTANDING'}
           VALUE{'2070','MQRC_SIGNAL_REQUEST_ACCEPTED'}
           VALUE{'2071','MQRC_STORAGE_NOT_AVAILABLE'}
           VALUE{'2072','MQRC_SYNCPOINT_NOT_AVAILABLE'}
           VALUE{'2075','MQRC_TRIGGER_CONTROL_ERROR'}
           VALUE{'2076','MQRC_TRIGGER_DEPTH_ERROR'}
           VALUE{'2077','MQRC_TRIGGER_MSG_PRIORITY_ERR'}
           VALUE{'2078','MQRC_TRIGGER_TYPE_ERROR'}
           VALUE{'2079','MQRC_TRUNCATED_MSG_ACCEPTED'}
           VALUE{'2080','MQRC_TRUNCATED_MSG_FAILED'}
           VALUE{'2082','MQRC_UNKNOWN_ALIAS_BASE_Q'}
      }
      }
    IF { COND{CHKCODE} THEN {
       CHOICE{ FNAME{RCEQU2}  POS{6,40,30}
       XNAME{REASON EQU}
       DLOC{MQLCRC}
         LISTV{
           VALUE{'2085','MQRC_UNKNOWN_OBJECT_NAME'}
           VALUE{'2086','MQRC_UNKNOWN_OBJECT_Q_MGR'}
           VALUE{'2087','MQRC_UNKNOWN_REMOTE_Q_MGR'}
           VALUE{'2090','MQRC_WAIT_INTERVAL_ERROR'}
           VALUE{'2091','MQRC_XMIT_Q_TYPE_ERROR'}
           VALUE{'2092','MQRC_XMIT_Q_USAGE_ERROR'}
           VALUE{'2093','MQRC_NOT_OPEN_FOR_PASS_ALL'}
           VALUE{'2094','MQRC_NOT_OPEN_FOR_PASS_IDENT'}
           VALUE{'2095','MQRC_NOT_OPEN_FOR_SET_ALL'}
           VALUE{'2096','MQRC_NOT_OPEN_FOR_SET_IDENT'}
           VALUE{'2097','MQRC_CONTEXT_HANDLE_ERROR'}
           VALUE{'2098','MQRC_CONTEXT_NOT_AVAILABLE'}
           VALUE{'2099','MQRC_SIGNAL1_ERROR'}
           VALUE{'2100','MQRC_OBJECT_ALREADY_EXISTS'}
           VALUE{'2101','MQRC_OBJECT_DAMAGED'}
           VALUE{'2102','MQRC_RESOURCE_PROBLEM'}
           VALUE{'2103','MQRC_ANOTHER_Q_MGR_CONNECTED'}
           VALUE{'2104','MQRC_UNKNOWN_REPORT_OPTION'}
           VALUE{'2105','MQRC_STORAGE_CLASS_ERROR'}
           VALUE{'2106','MQRC_COD_NOT_VALID_FOR_XCF_Q'}
           VALUE{'2107','MQRC_XWAIT_CANCELED'}
           VALUE{'2108','MQRC_XWAIT_ERROR'}
           VALUE{'2109','MQRC_SUPPRESSED_BY_EXIT'}
           VALUE{'2110','MQRC_FORMAT_ERROR'}
           VALUE{'2111','MQRC_SOURCE_CCSID_ERROR'}
           VALUE{'2112','MQRC_SOURCE_INTEGER_ENC_ERROR'}
           VALUE{'2113','MQRC_SOURCE_DECIMAL_ENC_ERROR'}
           VALUE{'2114','MQRC_SOURCE_FLOAT_ENC_ERROR'}
           VALUE{'2115','MQRC_TARGET_CCSID_ERROR'}
           VALUE{'2116','MQRC_TARGET_INTEGER_ENC_ERROR'}
           VALUE{'2117','MQRC_TARGET_DECIMAL_ENC_ERROR'}
           VALUE{'2118','MQRC_TARGET_FLOAT_ENC_ERROR'}
           VALUE{'2119','MQRC_NOT_CONVERTED'}
           VALUE{'2120','MQRC_CONVERTED_MSG_TOO_BIG'}
           VALUE{'2120','MQRC_TRUNCATED'}
           VALUE{'2121','MQRC_NO_EXTERNAL_PARTICIPANTS'}
           VALUE{'2122','MQRC_PARTICIPANT_NOT_AVAILABLE'}
           VALUE{'2123','MQRC_OUTCOME_MIXED'}
           VALUE{'2124','MQRC_OUTCOME_PENDING'}
           VALUE{'2125','MQRC_BRIDGE_STARTED'}
           VALUE{'2126','MQRC_BRIDGE_STOPPED'}
           VALUE{'2127','MQRC_ADAPTER_STORAGE_SHORTAGE'}
           VALUE{'2128','MQRC_UOW_IN_PROGRESS'}
           VALUE{'2129','MQRC_ADAPTER_CONN_LOAD_ERROR'}
           VALUE{'2130','MQRC_ADAPTER_SERV_LOAD_ERROR'}
           VALUE{'2131','MQRC_ADAPTER_DEFS_ERROR'}
           VALUE{'2132','MQRC_ADAPTER_DEFS_LOAD_ERROR'}
           VALUE{'2133','MQRC_ADAPTER_CONV_LOAD_ERROR'}
           VALUE{'2134','MQRC_BO_ERROR'}
           VALUE{'2135','MQRC_DH_ERROR'}
           VALUE{'2136','MQRC_MULTIPLE_REASONS'}
           VALUE{'2137','MQRC_OPEN_FAILED'}
           VALUE{'2138','MQRC_ADAPTER_DISC_LOAD_ERROR'}
           VALUE{'2139','MQRC_CNO_ERROR'}
           VALUE{'2140','MQRC_CICS_WAIT_FAILED'}
           VALUE{'2141','MQRC_DLH_ERROR'}
           VALUE{'2142','MQRC_HEADER_ERROR'}
           VALUE{'2143','MQRC_SOURCE_LENGTH_ERROR'}
           VALUE{'2144','MQRC_TARGET_LENGTH_ERROR'}
           VALUE{'2145','MQRC_SOURCE_BUFFER_ERROR'}
           VALUE{'2146','MQRC_TARGET_BUFFER_ERROR'}
           VALUE{'2148','MQRC_IIH_ERROR'}
           VALUE{'2149','MQRC_PCF_ERROR'}
           VALUE{'2150','MQRC_DBCS_ERROR'}
           VALUE{'2152','MQRC_OBJECT_NAME_ERROR'}
           VALUE{'2153','MQRC_OBJECT_Q_MGR_NAME_ERROR'}
           VALUE{'2154','MQRC_RECS_PRESENT_ERROR'}
           VALUE{'2155','MQRC_OBJECT_RECORDS_ERROR'}
           VALUE{'2156','MQRC_RESPONSE_RECORDS_ERROR'}
           VALUE{'2157','MQRC_ASID_MISMATCH'}
           VALUE{'2158','MQRC_PMO_RECORD_FLAGS_ERROR'}
           VALUE{'2159','MQRC_PUT_MSG_RECORDS_ERROR'}
           VALUE{'2160','MQRC_CONN_ID_IN_USE'}
           VALUE{'2161','MQRC_Q_MGR_QUIESCING'}
           VALUE{'2162','MQRC_Q_MGR_STOPPING'}
           VALUE{'2163','MQRC_DUPLICATE_RECOV_COORD'}
           VALUE{'2173','MQRC_PMO_ERROR'}
           VALUE{'2182','MQRC_API_EXIT_NOT_FOUND'}
           VALUE{'2183','MQRC_API_EXIT_LOAD_ERROR'}
           VALUE{'2184','MQRC_REMOTE_Q_NAME_ERROR'}
           VALUE{'2185','MQRC_INCONSISTENT_PERSISTENCE'}
           VALUE{'2186','MQRC_GMO_ERROR'}
           VALUE{'2187','MQRC_CICS_BRIDGE_RESTRICTION'}
           VALUE{'2188','MQRC_STOPPED_BY_CLUSTER_EXIT'}
           VALUE{'2189','MQRC_CLUSTER_RESOLUTION_ERROR'}
           VALUE{'2190','MQRC_CONVERTED_STRING_TOO_BIG'}
           VALUE{'2191','MQRC_TMC_ERROR'}
           VALUE{'2192','MQRC_PAGESET_FULL'}
           VALUE{'2193','MQRC_PAGESET_ERROR'}
           VALUE{'2194','MQRC_NAME_NOT_VALID_FOR_TYPE'}
           VALUE{'2195','MQRC_UNEXPECTED_ERROR'}
           VALUE{'2196','MQRC_UNKNOWN_XMIT_Q'}
           VALUE{'2197','MQRC_UNKNOWN_DEF_XMIT_Q'}
           VALUE{'2198','MQRC_DEF_XMIT_Q_TYPE_ERROR'}
           VALUE{'2199','MQRC_DEF_XMIT_Q_USAGE_ERROR'}
           VALUE{'2201','MQRC_NAME_IN_USE'}
           VALUE{'2202','MQRC_CONNECTION_QUIESCING'}
           VALUE{'2203','MQRC_CONNECTION_STOPPING'}
           VALUE{'2204','MQRC_ADAPTER_NOT_AVAILABLE'}
           VALUE{'2206','MQRC_MSG_ID_ERROR'}
           VALUE{'2207','MQRC_CORREL_ID_ERROR'}
           VALUE{'2208','MQRC_FILE_SYSTEM_ERROR'}
           VALUE{'2209','MQRC_NO_MSG_LOCKED'}
           VALUE{'2216','MQRC_FILE_NOT_AUDITED'}
           VALUE{'2217','MQRC_CONNECTION_NOT_AUTHORIZED'}
           VALUE{'2218','MQRC_MSG_TOO_BIG_FOR_CHANNEL'}
           VALUE{'2219','MQRC_CALL_IN_PROGRESS'}
           VALUE{'2220','MQRC_RMH_ERROR'}
           VALUE{'2222','MQRC_Q_MGR_ACTIVE'}
           VALUE{'2223','MQRC_Q_MGR_NOT_ACTIVE'}
           VALUE{'2224','MQRC_Q_DEPTH_HIGH'}
           VALUE{'2225','MQRC_Q_DEPTH_LOW'}
           VALUE{'2226','MQRC_Q_SERVICE_INTERVAL_HIGH'}
           VALUE{'2227','MQRC_Q_SERVICE_INTERVAL_OK'}
           VALUE{'2232','MQRC_UNIT_OF_WORK_NOT_STARTED'}
           VALUE{'2233','MQRC_CHANNEL_AUTO_DEF_OK'}
           VALUE{'2234','MQRC_CHANNEL_AUTO_DEF_ERROR'}
           VALUE{'2235','MQRC_CFH_ERROR'}
           VALUE{'2236','MQRC_CFIL_ERROR'}
           VALUE{'2237','MQRC_CFIN_ERROR'}
           VALUE{'2238','MQRC_CFSL_ERROR'}
           VALUE{'2239','MQRC_CFST_ERROR'}
           VALUE{'2241','MQRC_INCOMPLETE_GROUP'}
           VALUE{'2242','MQRC_INCOMPLETE_MSG'}
           VALUE{'2243','MQRC_INCONSISTENT_CCSIDS'}
           VALUE{'2244','MQRC_INCONSISTENT_ENCODINGS'}
           VALUE{'2245','MQRC_INCONSISTENT_UOW'}
           VALUE{'2246','MQRC_INVALID_MSG_UNDER_CURSOR'}
           VALUE{'2247','MQRC_MATCH_OPTIONS_ERROR'}
           VALUE{'2248','MQRC_MDE_ERROR'}
           VALUE{'2249','MQRC_MSG_FLAGS_ERROR'}
           VALUE{'2250','MQRC_MSG_SEQ_NUMBER_ERROR'}
           VALUE{'2251','MQRC_OFFSET_ERROR'}
           VALUE{'2252','MQRC_ORIGINAL_LENGTH_ERROR'}
           VALUE{'2253','MQRC_SEGMENT_LENGTH_ZERO'}
           VALUE{'2255','MQRC_UOW_NOT_AVAILABLE'}
           VALUE{'2256','MQRC_WRONG_GMO_VERSION'}
           VALUE{'2257','MQRC_WRONG_MD_VERSION'}
           VALUE{'2258','MQRC_GROUP_ID_ERROR'}
           VALUE{'2259','MQRC_INCONSISTENT_BROWSE'}
           VALUE{'2260','MQRC_XQH_ERROR'}
           VALUE{'2261','MQRC_SRC_ENV_ERROR'}
           VALUE{'2262','MQRC_SRC_NAME_ERROR'}
           VALUE{'2263','MQRC_DEST_ENV_ERROR'}
           VALUE{'2264','MQRC_DEST_NAME_ERROR'}
           VALUE{'2265','MQRC_TM_ERROR'}
           VALUE{'2266','MQRC_CLUSTER_EXIT_ERROR'}
           VALUE{'2267','MQRC_CLUSTER_EXIT_LOAD_ERROR'}
           VALUE{'2268','MQRC_CLUSTER_PUT_INHIBITED'}
           VALUE{'2269','MQRC_CLUSTER_RESOURCE_ERROR'}
           VALUE{'2270','MQRC_NO_DESTINATIONS_AVAILABLE'}
           VALUE{'2273','MQRC_CONNECTION_ERROR'}
           VALUE{'2274','MQRC_OPTION_ENVIRONMENT_ERROR'}
           VALUE{'2277','MQRC_CD_ERROR'}
           VALUE{'2278','MQRC_CLIENT_CONN_ERROR'}
           VALUE{'2279','MQRC_CHANNEL_STOPPED_BY_USER'}
           VALUE{'2280','MQRC_HCONFIG_ERROR'}
           VALUE{'2281','MQRC_FUNCTION_ERROR'}
           VALUE{'2282','MQRC_CHANNEL_STARTED'}
           VALUE{'2283','MQRC_CHANNEL_STOPPED'}
           VALUE{'2284','MQRC_CHANNEL_CONV_ERROR'}
           VALUE{'2285','MQRC_SERVICE_NOT_AVAILABLE'}
           VALUE{'2286','MQRC_INITIALIZATION_FAILED'}
           VALUE{'2287','MQRC_TERMINATION_FAILED'}
           VALUE{'2288','MQRC_UNKNOWN_Q_NAME'}
           VALUE{'2289','MQRC_SERVICE_ERROR'}
           VALUE{'2290','MQRC_Q_ALREADY_EXISTS'}
           VALUE{'2291','MQRC_USER_ID_NOT_AVAILABLE'}
           VALUE{'2292','MQRC_UNKNOWN_ENTITY'}
           VALUE{'2293','MQRC_UNKNOWN_AUTH_ENTITY'}
           VALUE{'2294','MQRC_UNKNOWN_REF_OBJECT'}
           VALUE{'2295','MQRC_CHANNEL_ACTIVATED'}
           VALUE{'2296','MQRC_CHANNEL_NOT_ACTIVATED'}
           VALUE{'2297','MQRC_UOW_CANCELED'}
           VALUE{'2299','MQRC_SELECTOR_TYPE_ERROR'}
           VALUE{'2300','MQRC_COMMAND_TYPE_ERROR'}
           VALUE{'2301','MQRC_MULTIPLE_INSTANCE_ERROR'}
           VALUE{'2302','MQRC_SYSTEM_ITEM_NOT_ALTERABLE'}
           VALUE{'2303','MQRC_BAG_CONVERSION_ERROR'}
           VALUE{'2304','MQRC_SELECTOR_OUT_OF_RANGE'}
           VALUE{'2305','MQRC_SELECTOR_NOT_UNIQUE'}
           VALUE{'2306','MQRC_INDEX_NOT_PRESENT'}
           VALUE{'2307','MQRC_STRING_ERROR'}
           VALUE{'2308','MQRC_ENCODING_NOT_SUPPORTED'}
           VALUE{'2309','MQRC_SELECTOR_NOT_PRESENT'}
           VALUE{'2310','MQRC_OUT_SELECTOR_ERROR'}
           VALUE{'2311','MQRC_STRING_TRUNCATED'}
           VALUE{'2312','MQRC_SELECTOR_WRONG_TYPE'}
           VALUE{'2313','MQRC_INCONSISTENT_ITEM_TYPE'}
           VALUE{'2314','MQRC_INDEX_ERROR'}
           VALUE{'2315','MQRC_SYSTEM_BAG_NOT_ALTERABLE'}
           VALUE{'2316','MQRC_ITEM_COUNT_ERROR'}
           VALUE{'2317','MQRC_FORMAT_NOT_SUPPORTED'}
           VALUE{'2318','MQRC_SELECTOR_NOT_SUPPORTED'}
           VALUE{'2319','MQRC_ITEM_VALUE_ERROR'}
           VALUE{'2320','MQRC_HBAG_ERROR'}
           VALUE{'2321','MQRC_PARAMETER_MISSING'}
           VALUE{'2322','MQRC_CMD_SERVER_NOT_AVAILABLE'}
           VALUE{'2323','MQRC_STRING_LENGTH_ERROR'}
           VALUE{'2324','MQRC_INQUIRY_COMMAND_ERROR'}
           VALUE{'2325','MQRC_NESTED_BAG_NOT_SUPPORTED'}
           VALUE{'2326','MQRC_BAG_WRONG_TYPE'}
           VALUE{'2327','MQRC_ITEM_TYPE_ERROR'}
           VALUE{'2328','MQRC_SYSTEM_BAG_NOT_DELETABLE'}
           VALUE{'2329','MQRC_SYSTEM_ITEM_NOT_DELETABLE'}
           VALUE{'2330','MQRC_CODED_CHAR_SET_ID_ERROR'}
           VALUE{'2331','MQRC_MSG_TOKEN_ERROR'}
           VALUE{'2332','MQRC_MISSING_WIH'}
           VALUE{'2333','MQRC_WIH_ERROR'}
        }
       }
       }}
    }    /* end-group */
;
    GROUP{ POS{13,1,79}
      HDR{YES} FNAME{EXCALINF}
        TEXT{                        Expanded Call Information }
    }
;
    GROUP{ POS{15,1,79}
        DATACOL{25}
      CHAR{ FNAME{QMGRNAME} POS{1,,4}
        XNAME{QMGR NAME}
        DLOC{MQLCQMGR}
        FDESC{ COL{1} FILL{.}
          TEXT{QMgr Name} }
        HELP{This is the name of the queue manager that CICS was
             connected to at the time of the dump. \P
        }
      }
      CHAR{ FNAME{QNAME} POS{2,,48}
        XNAME{QUEUE NAME}
        DLOC{MQLCQNME}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQCB @FF003 @FF004 }
              DESC{Displays the queue defintions.  } }
        }}
        FDESC{ COL{1} FILL{.}
          TEXT{Queue Used in Call} }
        HELP{This is the name of the queue that was used for the
             MQOPEN call. \P
        }
      }
    IF {COND{OLDFMT} THEN { } ELSE {
      IF { COND{GOTMHND} THEN {
         HEX{ FNAME{OPENOPT}  POS{3,,8}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
              ATTR{ TABS }
              COMMAND{ NAME{.DFLT}
                 CMD{CPR MQM2 OPN @FF006 }
                 DESC{Displays the OPEN options} }
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
      }} } }
   }  /* end-group */
;
  }                                              /* end-fixed */        03130000
  HELP{The MQOPEN call is used to establish access to an object. \P\P
       This screen displays the parameters that were used in the        03140000
       MQOPEN call. \P
  }                                                                     03160000
}                                                /* end-screen */       03170000
:END                                                                    03180000
*
*
:SCREEN{ NAME{MQLGET} TITLE{Last WebSphere MQ Call Info}                00600000
 TEMPLATE{KAZHDTMP.MQLGET}                     /* @03 */
  ORG{KAZ#MQLC}                                                         00610000
  FIXED{                                                                00620000
;
    DP{ FNAME{F001}     DLOC{MQLCBFR@} }
    DP{ FNAME{F002}     DLOC{MQLCBFRL} }
    DP{ FNAME{F003}     DLOC{MQLCQTYP} }
    DP{ FNAME{F004}     DLOC{MQLCHOBJ} }
    DP{ FNAME{F005}     DLOC{MQLCRC} }
    DP{ FNAME{F006}     DLOC{MQLCOPEN} }      /* PROG OPEN OPTIONS */
    DP{ FNAME{F007}     DLOC{MQLCMQGO} }      /* MQ GET OPTIONS    */
    DP{ FNAME{F008}     DLOC{MQLCGET} }       /* PROG GET OPTIONS  */
    DP{ FNAME{F009}     DLOC{MQLCQREL} }      /* MQ RELEASE    @02 */
;
   COND{ FNAME{CHKCODE} DLOC{MQLCRC}
         COMPOP{CLC,'2085',NL} }
   COND{ FNAME{GOTMHND} DLOC{MQLCMHND}
         COMPOP{CLC,'Y',E} }
   COND{ FNAME{GOODCC} DLOC{MQLCMQCC}
         COMPOP{CB,X'00000002',L} }
   COND{FNAME{OLDFMT} DLOC{MQLC@FMT}
         COMPOP{CLC,'1',E} }
;
    LITERAL{ FNAME{CALMQGET} POS{1,1,40} /*->fixedPro<-*/ /* @03 */
        TEXT {CALL 'MQGET' USING}  }
    GROUP{ POS{2,1,79}
        DATACOL{25}
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HCONN}  POS{1,,8}
        XNAME{HCONN}
        DLOC{MQLCHCON}
        FDESC{ COL{7} FILL{.}
          TEXT{Hconn} }
        HELP{Connection Handle:  Input parameter \P\P
             This parameter represents the connection to the queue
             manager. The value was return on a previous MQCONN call.
             \P\P
             On OS/390 for CICS applications, the MQCONN call can be
             omitted and the value of MQHC_DEF_HCONN can be specified
             for this parameter. \P
        }
      } } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HOBJECT}  POS{2,,8}
        XNAME{HOBJECT}
        DLOC{MQLCHOBJ}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQHI @FF004 C @FF009}                   /* @02 */
              DESC{Display Handle Information} }
        }}
        FDESC{ COL{7} FILL{.}
          TEXT{Hobj} }
        HELP{Object Handle:  Input parameter \P\P
             This handle represents the queue from which a message
             is to be retrieved. \P\P
             The value of Hobj was returned by a previous MQOPEN call.
        }
      } } }
     IF {COND{OLDFMT} THEN {
      CHAR{ FNAME{MQMD@}  POS{3,,8}
        XNAME{MQMD ADDRESS}
        DLOC{MQLCDTL}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Message Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQMD }
           DESC{Display Message Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{MsgDesc} }
        HELP{Message Descriptor:  Input/Output parameter \P\P
             This is the address of the message descriptor.\P\P
             The message descriptor describes the attributes
             of the message required,
             and the attributes of the message retrieved. \P
        }
      }
      }ELSE {
      HEX{ FNAME{MQMD@}  POS{3,,8}
        XNAME{MQMD ADDRESS}
        DLOC{MQLCMD@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Message Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQMD }
           DESC{Display Message Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{MsgDesc} }
        HELP{Message Descriptor:  Input/Output parameter \P\P
             This is the address of the message descriptor.\P\P
             The message descriptor describes the attributes
             of the message required,
             and the attributes of the message retrieved. \P
        }
      }
     } }
     IF {COND{OLDFMT} THEN {
      CHAR{ FNAME{MQGMO@}  POS{4,,8}
        XNAME{GMO ADDRESS}
        DLOC{MQLCDTL}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ MQGMO Detail'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQGM}
           DESC{Display MQGMO Detail}
           }
        FDESC{ COL{7} FILL{.}
          TEXT{GetMsgOpts} }
        HELP{Get Message Options:  Input/Output parameter \P\P
             This is the address of the MQGMO structure. \P
        }
      }
      } ELSE {
      HEX{ FNAME{MQGMO@}  POS{4,,8}
        XNAME{GMO ADDRESS}
        DLOC{MQLCGMO@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ MQGMO Detail'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQGM}
           DESC{Display MQGMO Detail}
           }
        FDESC{ COL{7} FILL{.}
          TEXT{GetMsgOpts} }
        HELP{Get Message Options:  Input/Output parameter \P\P
             This is the address of the MQGMO structure. \P
        }
      } } }
      HEX{ FNAME{BFRLGTH}  POS{5,,8}
        XNAME{BUFFER LENGTH}
        DLOC{MQLCBFRL}
        FDESC{ COL{7} FILL{.}
          TEXT{BufferLength} }
        HELP{Buffer Length:  Input parameter \P\P
             Length in bytes of the Buffer area.
        }
      }
      BIN{ FNAME{BFRLGTH2}  POS{5,51,8} /*->3ColWithFDesc<-*/
        XNAME{BUFFER LENGTH}
        DLOC{MQLCBFRL}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{BUFFR@}  POS{6,,8}
        XNAME{BUFFER ADDRESS}
        DLOC{MQLCBFR@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Buffer'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQINVBFR @FF001 @FF002 }
           DESC{Displays the message bufer area }
        }
        FDESC{ COL{7} FILL{.}
          TEXT{Buffer} }
        HELP{Buffer:  Output parameter \P\P
             This is the address of the area to contain the message
             data. \P
        }
      }
      HEX{ FNAME{DATALGTH} POS{7,,8}
        XNAME{DATA LENGTH}
        DLOC{MQLCDTAL}
        FDESC{ COL{7} FILL{.}
          TEXT{DataLength} }
        HELP{Data Length:  Output parameter \P\P
             This is the length in bytes of the application data
             in the message. If this is greater than BufferLength,
             only BufferLength bytes are returned in the Buffer
             parameter (that is, the message is truncated). If the
             value is zero, it means that the message contains
             no application data.
        }
      }
      BIN{ FNAME{DATLGTH2}  POS{7,51,8} /*->3ColWithFDesc<-*/
        XNAME{DATA LENGTH}
        DLOC{MQLCDTAL}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      BIN{ FNAME{COMPCODE} POS{8,,8}
        XNAME{COMP CODE}
        DLOC{MQLCMQCC}
        FDESC{ COL{7} FILL{.}
          TEXT{CompCode} }
        HELP{Completion Code:  Output parameter \P\P
             This is the completion code for the MQ API call. \P
        }
      }
      CHOICE{ FNAME{MQCCEQU} POS{8,40,20}
      XNAME{MQCCEQU}
      DLOC{MQLCMQCC}
       LISTV{
            VALUE{X'00','MQCC_OK'}
            VALUE{X'01','MQCC_WARNING'}
            VALUE{X'02','MQCC_FAILED'}
       }
      }
      CHAR{ FNAME{REASCODE} POS{9,,4}
        XNAME{REASON CODE}
        DLOC{MQLCRC}
        FDESC{ COL{7} FILL{.}
          TEXT{Reason} }
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQDI @FF005}
           DESC{Display Reason Code}
           }
        HELP{Reason Code:  Output parameter \P\P
             This is the reason code that qualifies the
             completion code for the MQ API call.
        }
      }
     CHOICE{ FNAME{RCEQU1} POS{9,40,30}
     XNAME{REASON EQU}
     DLOC{MQLCRC}
      LISTV{
           VALUE{'0000','MQRC_NONE'}
           VALUE{'2001','MQRC_ALIAS_BASE_Q_TYPE_ERROR'}
           VALUE{'2002','MQRC_ALREADY_CONNECTED'}
           VALUE{'2003','MQRC_BACKED_OUT'}
           VALUE{'2004','MQRC_BUFFER_ERROR'}
           VALUE{'2005','MQRC_BUFFER_LENGTH_ERROR'}
           VALUE{'2006','MQRC_CHAR_ATTR_LENGTH_ERROR'}
           VALUE{'2007','MQRC_CHAR_ATTRS_ERROR'}
           VALUE{'2008','MQRC_CHAR_ATTRS_TOO_SHORT'}
           VALUE{'2009','MQRC_CONNECTION_BROKEN'}
           VALUE{'2010','MQRC_DATA_LENGTH_ERROR'}
           VALUE{'2011','MQRC_DYNAMIC_Q_NAME_ERROR'}
           VALUE{'2012','MQRC_ENVIRONMENT_ERROR'}
           VALUE{'2013','MQRC_EXPIRY_ERROR'}
           VALUE{'2014','MQRC_FEEDBACK_ERROR'}
           VALUE{'2016','MQRC_GET_INHIBITED'}
           VALUE{'2017','MQRC_HANDLE_NOT_AVAILABLE'}
           VALUE{'2018','MQRC_HCONN_ERROR'}
           VALUE{'2019','MQRC_HOBJ_ERROR'}
           VALUE{'2020','MQRC_INHIBIT_VALUE_ERROR'}
           VALUE{'2021','MQRC_INT_ATTR_COUNT_ERROR'}
           VALUE{'2022','MQRC_INT_ATTR_COUNT_TOO_SMALL'}
           VALUE{'2023','MQRC_INT_ATTRS_ARRAY_ERROR'}
           VALUE{'2024','MQRC_SYNCPOINT_LIMIT_REACHED'}
           VALUE{'2025','MQRC_MAX_CONNS_LIMIT_REACHED'}
           VALUE{'2026','MQRC_MD_ERROR'}
           VALUE{'2027','MQRC_MISSING_REPLY_TO_Q'}
           VALUE{'2029','MQRC_MSG_TYPE_ERROR'}
           VALUE{'2030','MQRC_MSG_TOO_BIG_FOR_Q'}
           VALUE{'2031','MQRC_MSG_TOO_BIG_FOR_Q_MGR'}
           VALUE{'2033','MQRC_NO_MSG_AVAILABLE'}
           VALUE{'2034','MQRC_NO_MSG_UNDER_CURSOR'}
           VALUE{'2035','MQRC_NOT_AUTHORIZED'}
           VALUE{'2036','MQRC_NOT_OPEN_FOR_BROWSE'}
           VALUE{'2037','MQRC_NOT_OPEN_FOR_INPUT'}
           VALUE{'2038','MQRC_NOT_OPEN_FOR_INQUIRE'}
           VALUE{'2039','MQRC_NOT_OPEN_FOR_OUTPUT'}
           VALUE{'2040','MQRC_NOT_OPEN_FOR_SET'}
           VALUE{'2041','MQRC_OBJECT_CHANGED'}
           VALUE{'2042','MQRC_OBJECT_IN_USE'}
           VALUE{'2043','MQRC_OBJECT_TYPE_ERROR'}
           VALUE{'2044','MQRC_OD_ERROR'}
           VALUE{'2045','MQRC_OPTION_NOT_VALID_FOR_TYPE'}
           VALUE{'2046','MQRC_OPTIONS_ERROR'}
           VALUE{'2047','MQRC_PERSISTENCE_ERROR'}
           VALUE{'2048','MQRC_PERSISTENT_NOT_ALLOWED'}
           VALUE{'2049','MQRC_PRIORITY_EXCEEDS_MAXIMUM'}
           VALUE{'2050','MQRC_PRIORITY_ERROR'}
           VALUE{'2051','MQRC_PUT_INHIBITED'}
           VALUE{'2052','MQRC_Q_DELETED'}
           VALUE{'2053','MQRC_Q_FULL'}
           VALUE{'2055','MQRC_Q_NOT_EMPTY'}
           VALUE{'2056','MQRC_Q_SPACE_NOT_AVAILABLE'}
           VALUE{'2057','MQRC_Q_TYPE_ERROR'}
           VALUE{'2058','MQRC_Q_MGR_NAME_ERROR'}
           VALUE{'2059','MQRC_Q_MGR_NOT_AVAILABLE'}
           VALUE{'2061','MQRC_REPORT_OPTIONS_ERROR'}
           VALUE{'2062','MQRC_SECOND_MARK_NOT_ALLOWED'}
           VALUE{'2063','MQRC_SECURITY_ERROR'}
           VALUE{'2065','MQRC_SELECTOR_COUNT_ERROR'}
           VALUE{'2066','MQRC_SELECTOR_LIMIT_EXCEEDED'}
           VALUE{'2067','MQRC_SELECTOR_ERROR'}
           VALUE{'2068','MQRC_SELECTOR_NOT_FOR_TYPE'}
           VALUE{'2069','MQRC_SIGNAL_OUTSTANDING'}
           VALUE{'2070','MQRC_SIGNAL_REQUEST_ACCEPTED'}
           VALUE{'2071','MQRC_STORAGE_NOT_AVAILABLE'}
           VALUE{'2072','MQRC_SYNCPOINT_NOT_AVAILABLE'}
           VALUE{'2075','MQRC_TRIGGER_CONTROL_ERROR'}
           VALUE{'2076','MQRC_TRIGGER_DEPTH_ERROR'}
           VALUE{'2077','MQRC_TRIGGER_MSG_PRIORITY_ERR'}
           VALUE{'2078','MQRC_TRIGGER_TYPE_ERROR'}
           VALUE{'2079','MQRC_TRUNCATED_MSG_ACCEPTED'}
           VALUE{'2080','MQRC_TRUNCATED_MSG_FAILED'}
           VALUE{'2082','MQRC_UNKNOWN_ALIAS_BASE_Q'}
      }
      }
    IF { COND{CHKCODE} THEN {
       CHOICE{ FNAME{RCEQU2}  POS{9,40,30}
       XNAME{REASON EQU}
       DLOC{MQLCRC}
         LISTV{
           VALUE{'2085','MQRC_UNKNOWN_OBJECT_NAME'}
           VALUE{'2086','MQRC_UNKNOWN_OBJECT_Q_MGR'}
           VALUE{'2087','MQRC_UNKNOWN_REMOTE_Q_MGR'}
           VALUE{'2090','MQRC_WAIT_INTERVAL_ERROR'}
           VALUE{'2091','MQRC_XMIT_Q_TYPE_ERROR'}
           VALUE{'2092','MQRC_XMIT_Q_USAGE_ERROR'}
           VALUE{'2093','MQRC_NOT_OPEN_FOR_PASS_ALL'}
           VALUE{'2094','MQRC_NOT_OPEN_FOR_PASS_IDENT'}
           VALUE{'2095','MQRC_NOT_OPEN_FOR_SET_ALL'}
           VALUE{'2096','MQRC_NOT_OPEN_FOR_SET_IDENT'}
           VALUE{'2097','MQRC_CONTEXT_HANDLE_ERROR'}
           VALUE{'2098','MQRC_CONTEXT_NOT_AVAILABLE'}
           VALUE{'2099','MQRC_SIGNAL1_ERROR'}
           VALUE{'2100','MQRC_OBJECT_ALREADY_EXISTS'}
           VALUE{'2101','MQRC_OBJECT_DAMAGED'}
           VALUE{'2102','MQRC_RESOURCE_PROBLEM'}
           VALUE{'2103','MQRC_ANOTHER_Q_MGR_CONNECTED'}
           VALUE{'2104','MQRC_UNKNOWN_REPORT_OPTION'}
           VALUE{'2105','MQRC_STORAGE_CLASS_ERROR'}
           VALUE{'2106','MQRC_COD_NOT_VALID_FOR_XCF_Q'}
           VALUE{'2107','MQRC_XWAIT_CANCELED'}
           VALUE{'2108','MQRC_XWAIT_ERROR'}
           VALUE{'2109','MQRC_SUPPRESSED_BY_EXIT'}
           VALUE{'2110','MQRC_FORMAT_ERROR'}
           VALUE{'2111','MQRC_SOURCE_CCSID_ERROR'}
           VALUE{'2112','MQRC_SOURCE_INTEGER_ENC_ERROR'}
           VALUE{'2113','MQRC_SOURCE_DECIMAL_ENC_ERROR'}
           VALUE{'2114','MQRC_SOURCE_FLOAT_ENC_ERROR'}
           VALUE{'2115','MQRC_TARGET_CCSID_ERROR'}
           VALUE{'2116','MQRC_TARGET_INTEGER_ENC_ERROR'}
           VALUE{'2117','MQRC_TARGET_DECIMAL_ENC_ERROR'}
           VALUE{'2118','MQRC_TARGET_FLOAT_ENC_ERROR'}
           VALUE{'2119','MQRC_NOT_CONVERTED'}
           VALUE{'2120','MQRC_CONVERTED_MSG_TOO_BIG'}
           VALUE{'2120','MQRC_TRUNCATED'}
           VALUE{'2121','MQRC_NO_EXTERNAL_PARTICIPANTS'}
           VALUE{'2122','MQRC_PARTICIPANT_NOT_AVAILABLE'}
           VALUE{'2123','MQRC_OUTCOME_MIXED'}
           VALUE{'2124','MQRC_OUTCOME_PENDING'}
           VALUE{'2125','MQRC_BRIDGE_STARTED'}
           VALUE{'2126','MQRC_BRIDGE_STOPPED'}
           VALUE{'2127','MQRC_ADAPTER_STORAGE_SHORTAGE'}
           VALUE{'2128','MQRC_UOW_IN_PROGRESS'}
           VALUE{'2129','MQRC_ADAPTER_CONN_LOAD_ERROR'}
           VALUE{'2130','MQRC_ADAPTER_SERV_LOAD_ERROR'}
           VALUE{'2131','MQRC_ADAPTER_DEFS_ERROR'}
           VALUE{'2132','MQRC_ADAPTER_DEFS_LOAD_ERROR'}
           VALUE{'2133','MQRC_ADAPTER_CONV_LOAD_ERROR'}
           VALUE{'2134','MQRC_BO_ERROR'}
           VALUE{'2135','MQRC_DH_ERROR'}
           VALUE{'2136','MQRC_MULTIPLE_REASONS'}
           VALUE{'2137','MQRC_OPEN_FAILED'}
           VALUE{'2138','MQRC_ADAPTER_DISC_LOAD_ERROR'}
           VALUE{'2139','MQRC_CNO_ERROR'}
           VALUE{'2140','MQRC_CICS_WAIT_FAILED'}
           VALUE{'2141','MQRC_DLH_ERROR'}
           VALUE{'2142','MQRC_HEADER_ERROR'}
           VALUE{'2143','MQRC_SOURCE_LENGTH_ERROR'}
           VALUE{'2144','MQRC_TARGET_LENGTH_ERROR'}
           VALUE{'2145','MQRC_SOURCE_BUFFER_ERROR'}
           VALUE{'2146','MQRC_TARGET_BUFFER_ERROR'}
           VALUE{'2148','MQRC_IIH_ERROR'}
           VALUE{'2149','MQRC_PCF_ERROR'}
           VALUE{'2150','MQRC_DBCS_ERROR'}
           VALUE{'2152','MQRC_OBJECT_NAME_ERROR'}
           VALUE{'2153','MQRC_OBJECT_Q_MGR_NAME_ERROR'}
           VALUE{'2154','MQRC_RECS_PRESENT_ERROR'}
           VALUE{'2155','MQRC_OBJECT_RECORDS_ERROR'}
           VALUE{'2156','MQRC_RESPONSE_RECORDS_ERROR'}
           VALUE{'2157','MQRC_ASID_MISMATCH'}
           VALUE{'2158','MQRC_PMO_RECORD_FLAGS_ERROR'}
           VALUE{'2159','MQRC_PUT_MSG_RECORDS_ERROR'}
           VALUE{'2160','MQRC_CONN_ID_IN_USE'}
           VALUE{'2161','MQRC_Q_MGR_QUIESCING'}
           VALUE{'2162','MQRC_Q_MGR_STOPPING'}
           VALUE{'2163','MQRC_DUPLICATE_RECOV_COORD'}
           VALUE{'2173','MQRC_PMO_ERROR'}
           VALUE{'2182','MQRC_API_EXIT_NOT_FOUND'}
           VALUE{'2183','MQRC_API_EXIT_LOAD_ERROR'}
           VALUE{'2184','MQRC_REMOTE_Q_NAME_ERROR'}
           VALUE{'2185','MQRC_INCONSISTENT_PERSISTENCE'}
           VALUE{'2186','MQRC_GMO_ERROR'}
           VALUE{'2187','MQRC_CICS_BRIDGE_RESTRICTION'}
           VALUE{'2188','MQRC_STOPPED_BY_CLUSTER_EXIT'}
           VALUE{'2189','MQRC_CLUSTER_RESOLUTION_ERROR'}
           VALUE{'2190','MQRC_CONVERTED_STRING_TOO_BIG'}
           VALUE{'2191','MQRC_TMC_ERROR'}
           VALUE{'2192','MQRC_PAGESET_FULL'}
           VALUE{'2193','MQRC_PAGESET_ERROR'}
           VALUE{'2194','MQRC_NAME_NOT_VALID_FOR_TYPE'}
           VALUE{'2195','MQRC_UNEXPECTED_ERROR'}
           VALUE{'2196','MQRC_UNKNOWN_XMIT_Q'}
           VALUE{'2197','MQRC_UNKNOWN_DEF_XMIT_Q'}
           VALUE{'2198','MQRC_DEF_XMIT_Q_TYPE_ERROR'}
           VALUE{'2199','MQRC_DEF_XMIT_Q_USAGE_ERROR'}
           VALUE{'2201','MQRC_NAME_IN_USE'}
           VALUE{'2202','MQRC_CONNECTION_QUIESCING'}
           VALUE{'2203','MQRC_CONNECTION_STOPPING'}
           VALUE{'2204','MQRC_ADAPTER_NOT_AVAILABLE'}
           VALUE{'2206','MQRC_MSG_ID_ERROR'}
           VALUE{'2207','MQRC_CORREL_ID_ERROR'}
           VALUE{'2208','MQRC_FILE_SYSTEM_ERROR'}
           VALUE{'2209','MQRC_NO_MSG_LOCKED'}
           VALUE{'2216','MQRC_FILE_NOT_AUDITED'}
           VALUE{'2217','MQRC_CONNECTION_NOT_AUTHORIZED'}
           VALUE{'2218','MQRC_MSG_TOO_BIG_FOR_CHANNEL'}
           VALUE{'2219','MQRC_CALL_IN_PROGRESS'}
           VALUE{'2220','MQRC_RMH_ERROR'}
           VALUE{'2222','MQRC_Q_MGR_ACTIVE'}
           VALUE{'2223','MQRC_Q_MGR_NOT_ACTIVE'}
           VALUE{'2224','MQRC_Q_DEPTH_HIGH'}
           VALUE{'2225','MQRC_Q_DEPTH_LOW'}
           VALUE{'2226','MQRC_Q_SERVICE_INTERVAL_HIGH'}
           VALUE{'2227','MQRC_Q_SERVICE_INTERVAL_OK'}
           VALUE{'2232','MQRC_UNIT_OF_WORK_NOT_STARTED'}
           VALUE{'2233','MQRC_CHANNEL_AUTO_DEF_OK'}
           VALUE{'2234','MQRC_CHANNEL_AUTO_DEF_ERROR'}
           VALUE{'2235','MQRC_CFH_ERROR'}
           VALUE{'2236','MQRC_CFIL_ERROR'}
           VALUE{'2237','MQRC_CFIN_ERROR'}
           VALUE{'2238','MQRC_CFSL_ERROR'}
           VALUE{'2239','MQRC_CFST_ERROR'}
           VALUE{'2241','MQRC_INCOMPLETE_GROUP'}
           VALUE{'2242','MQRC_INCOMPLETE_MSG'}
           VALUE{'2243','MQRC_INCONSISTENT_CCSIDS'}
           VALUE{'2244','MQRC_INCONSISTENT_ENCODINGS'}
           VALUE{'2245','MQRC_INCONSISTENT_UOW'}
           VALUE{'2246','MQRC_INVALID_MSG_UNDER_CURSOR'}
           VALUE{'2247','MQRC_MATCH_OPTIONS_ERROR'}
           VALUE{'2248','MQRC_MDE_ERROR'}
           VALUE{'2249','MQRC_MSG_FLAGS_ERROR'}
           VALUE{'2250','MQRC_MSG_SEQ_NUMBER_ERROR'}
           VALUE{'2251','MQRC_OFFSET_ERROR'}
           VALUE{'2252','MQRC_ORIGINAL_LENGTH_ERROR'}
           VALUE{'2253','MQRC_SEGMENT_LENGTH_ZERO'}
           VALUE{'2255','MQRC_UOW_NOT_AVAILABLE'}
           VALUE{'2256','MQRC_WRONG_GMO_VERSION'}
           VALUE{'2257','MQRC_WRONG_MD_VERSION'}
           VALUE{'2258','MQRC_GROUP_ID_ERROR'}
           VALUE{'2259','MQRC_INCONSISTENT_BROWSE'}
           VALUE{'2260','MQRC_XQH_ERROR'}
           VALUE{'2261','MQRC_SRC_ENV_ERROR'}
           VALUE{'2262','MQRC_SRC_NAME_ERROR'}
           VALUE{'2263','MQRC_DEST_ENV_ERROR'}
           VALUE{'2264','MQRC_DEST_NAME_ERROR'}
           VALUE{'2265','MQRC_TM_ERROR'}
           VALUE{'2266','MQRC_CLUSTER_EXIT_ERROR'}
           VALUE{'2267','MQRC_CLUSTER_EXIT_LOAD_ERROR'}
           VALUE{'2268','MQRC_CLUSTER_PUT_INHIBITED'}
           VALUE{'2269','MQRC_CLUSTER_RESOURCE_ERROR'}
           VALUE{'2270','MQRC_NO_DESTINATIONS_AVAILABLE'}
           VALUE{'2273','MQRC_CONNECTION_ERROR'}
           VALUE{'2274','MQRC_OPTION_ENVIRONMENT_ERROR'}
           VALUE{'2277','MQRC_CD_ERROR'}
           VALUE{'2278','MQRC_CLIENT_CONN_ERROR'}
           VALUE{'2279','MQRC_CHANNEL_STOPPED_BY_USER'}
           VALUE{'2280','MQRC_HCONFIG_ERROR'}
           VALUE{'2281','MQRC_FUNCTION_ERROR'}
           VALUE{'2282','MQRC_CHANNEL_STARTED'}
           VALUE{'2283','MQRC_CHANNEL_STOPPED'}
           VALUE{'2284','MQRC_CHANNEL_CONV_ERROR'}
           VALUE{'2285','MQRC_SERVICE_NOT_AVAILABLE'}
           VALUE{'2286','MQRC_INITIALIZATION_FAILED'}
           VALUE{'2287','MQRC_TERMINATION_FAILED'}
           VALUE{'2288','MQRC_UNKNOWN_Q_NAME'}
           VALUE{'2289','MQRC_SERVICE_ERROR'}
           VALUE{'2290','MQRC_Q_ALREADY_EXISTS'}
           VALUE{'2291','MQRC_USER_ID_NOT_AVAILABLE'}
           VALUE{'2292','MQRC_UNKNOWN_ENTITY'}
           VALUE{'2293','MQRC_UNKNOWN_AUTH_ENTITY'}
           VALUE{'2294','MQRC_UNKNOWN_REF_OBJECT'}
           VALUE{'2295','MQRC_CHANNEL_ACTIVATED'}
           VALUE{'2296','MQRC_CHANNEL_NOT_ACTIVATED'}
           VALUE{'2297','MQRC_UOW_CANCELED'}
           VALUE{'2299','MQRC_SELECTOR_TYPE_ERROR'}
           VALUE{'2300','MQRC_COMMAND_TYPE_ERROR'}
           VALUE{'2301','MQRC_MULTIPLE_INSTANCE_ERROR'}
           VALUE{'2302','MQRC_SYSTEM_ITEM_NOT_ALTERABLE'}
           VALUE{'2303','MQRC_BAG_CONVERSION_ERROR'}
           VALUE{'2304','MQRC_SELECTOR_OUT_OF_RANGE'}
           VALUE{'2305','MQRC_SELECTOR_NOT_UNIQUE'}
           VALUE{'2306','MQRC_INDEX_NOT_PRESENT'}
           VALUE{'2307','MQRC_STRING_ERROR'}
           VALUE{'2308','MQRC_ENCODING_NOT_SUPPORTED'}
           VALUE{'2309','MQRC_SELECTOR_NOT_PRESENT'}
           VALUE{'2310','MQRC_OUT_SELECTOR_ERROR'}
           VALUE{'2311','MQRC_STRING_TRUNCATED'}
           VALUE{'2312','MQRC_SELECTOR_WRONG_TYPE'}
           VALUE{'2313','MQRC_INCONSISTENT_ITEM_TYPE'}
           VALUE{'2314','MQRC_INDEX_ERROR'}
           VALUE{'2315','MQRC_SYSTEM_BAG_NOT_ALTERABLE'}
           VALUE{'2316','MQRC_ITEM_COUNT_ERROR'}
           VALUE{'2317','MQRC_FORMAT_NOT_SUPPORTED'}
           VALUE{'2318','MQRC_SELECTOR_NOT_SUPPORTED'}
           VALUE{'2319','MQRC_ITEM_VALUE_ERROR'}
           VALUE{'2320','MQRC_HBAG_ERROR'}
           VALUE{'2321','MQRC_PARAMETER_MISSING'}
           VALUE{'2322','MQRC_CMD_SERVER_NOT_AVAILABLE'}
           VALUE{'2323','MQRC_STRING_LENGTH_ERROR'}
           VALUE{'2324','MQRC_INQUIRY_COMMAND_ERROR'}
           VALUE{'2325','MQRC_NESTED_BAG_NOT_SUPPORTED'}
           VALUE{'2326','MQRC_BAG_WRONG_TYPE'}
           VALUE{'2327','MQRC_ITEM_TYPE_ERROR'}
           VALUE{'2328','MQRC_SYSTEM_BAG_NOT_DELETABLE'}
           VALUE{'2329','MQRC_SYSTEM_ITEM_NOT_DELETABLE'}
           VALUE{'2330','MQRC_CODED_CHAR_SET_ID_ERROR'}
           VALUE{'2331','MQRC_MSG_TOKEN_ERROR'}
           VALUE{'2332','MQRC_MISSING_WIH'}
           VALUE{'2333','MQRC_WIH_ERROR'}
        }
       }
       }}
    }    /* end-group */
;
    GROUP{ POS{13,1,79}
      HDR{YES} FNAME{EXCALINF}
        TEXT{                        Expanded Call Information }
    }
;
    GROUP{ POS{15,1,79}
        DATACOL{25}
      CHAR{ FNAME{QMGRNAME} POS{1,,4}
        XNAME{QMGR NAME}
        DLOC{MQLCQMGR}
        FDESC{ COL{1} FILL{.}
          TEXT{QMgr Name} }
        HELP{This is the name of the queue manager that CICS was
             connected to at the time of the dump. \P
        }
      }
      CHAR{ FNAME{QNAME} POS{2,,48}
        XNAME{QUEUE NAME}
        DLOC{MQLCQNME}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQCB @FF003 @FF004 }
              DESC{Displays the queue defintions.  } }
        }}
        FDESC{ COL{1} FILL{.}
          TEXT{Queue Used in Call} }
        HELP{This is the name of the queue that was used for the
             MQGET call. \P
        }
      }
    IF {COND{OLDFMT} THEN { } ELSE {
      IF { COND{GOTMHND} THEN {
         HEX{ FNAME{OPENOPT}  POS{3,,8}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQM2 OPN @FF006 }
              DESC{Displays the OPEN options} }
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
      } ELSE  {
         CHAR{ FNAME{OPENOPT}  POS{3,,4}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
        }
      } } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{GETOPT}  POS{4,,8}
        XNAME{GET OPTIONS}
        DLOC{MQLCGET}
        ATTR{ TABS }
        IF { COND{GOODCC}
          THEN {
             COMMAND{ NAME{.DFLT}
                 CMD{CPR MQM2 GET @FF007 @FF008 }             /* @01 */
                  DESC{Displays the GET options} }
          }
          ELSE {
              COMMAND{ NAME{.DFLT}
               CMD{CPR MQM2 GET @FF008 }
                 DESC{Displays the GET options} }
          }
        }
        FDESC{ COL{1} FILL{.}
          TEXT{Get Options} }
        HELP{These are the MQGMO options that were specified by the
             program for the MQGET call.
        }
      } } }
   }  /* end-group */
;
  }                                              /* end-fixed */        03130000
  HELP{The MQGET call retrieves a message from a local queue that
       has been opened using the MQOPEN call. \P\P
       This screen displays the parameters that were used in the        03140000
       MQGET call. \P\P

  }                                                                     03160000
}                                                /* end-screen */       03170000
:END                                                                    03180000
*
*
:SCREEN{ NAME{MQLPUT} TITLE{Last WebSphere MQ Call Info}                00600000
 TEMPLATE{KAZHDTMP.MQLPUT}                     /* @03 */
  ORG{KAZ#MQLC}                                                         00610000
  FIXED{                                                                00620000
;
    DP{ FNAME{F001}     DLOC{MQLCBFR@} }
    DP{ FNAME{F002}     DLOC{MQLCBFRL} }
    DP{ FNAME{F003}     DLOC{MQLCQTYP} }
    DP{ FNAME{F004}     DLOC{MQLCHOBJ} }
    DP{ FNAME{F005}     DLOC{MQLCRC} }
    DP{ FNAME{F006}     DLOC{MQLCOPEN} }      /* PROG OPEN OPTIONS */
    DP{ FNAME{F007}     DLOC{MQLCMQPO} }      /* MQ PUT OPTIONS    */
    DP{ FNAME{F008}     DLOC{MQLCPUT} }       /* PROG PUT OPTIONS  */
    DP{ FNAME{F009}     DLOC{MQLCQREL} }      /* MQ RELEASE    @02 */
;
   COND{ FNAME{CHKCODE} DLOC{MQLCRC}
         COMPOP{CLC,'2085',NL} }
   COND{ FNAME{GOTMHND} DLOC{MQLCMHND}
         COMPOP{CLC,'Y',E} }
   COND{ FNAME{GOODCC} DLOC{MQLCMQCC}
         COMPOP{CB,X'00000002',L} }
   COND{FNAME{OLDFMT} DLOC{MQLC@FMT}
         COMPOP{CLC,'1',E} }
;
    LITERAL{ FNAME{CALMQPUT} POS{1,1,40} /*->fixedPro<-*/ /* @03 */
        TEXT {CALL 'MQPUT' USING}  }
    GROUP{ POS{2,1,79}
        DATACOL{25}
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HCONN}  POS{1,,8}
        XNAME{HCONN}
        DLOC{MQLCHCON}
        FDESC{ COL{7} FILL{.}
          TEXT{Hconn} }
        HELP{Connection Handle:  Input parameter \P\P
             This parameter represents the connection to the queue
             manager. The value was return on a previous MQCONN call.
             \P\P
             On OS/390 for CICS applications, the MQCONN call can be
             omitted and the value of MQHC_DEF_HCONN can be specified
             for this parameter. \P
        }
      } } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HOBJECT}  POS{2,,8}
        XNAME{HOBJECT}
        DLOC{MQLCHOBJ}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQHI @FF004 C @FF009}                   /* @02 */
              DESC{Display Handle Information} }
        }}
        FDESC{ COL{7} FILL{.}
          TEXT{Hobj} }
        HELP{Object Handle:  Input parameter \P\P
             This handle represents the queue to which a message
             is to be added. \P\P
             The value of Hobj was returned by a previous MQOPEN call
             that specified the MQOO_OUTPUT option.
        }
      } } }
     IF {COND{OLDFMT} THEN {
      CHAR{ FNAME{MQMD@}  POS{3,,8}
        XNAME{MQMD ADDRESS}
        DLOC{MQLCDTL}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Message Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQMD }
           DESC{Display Message Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{MsgDesc} }
        HELP{Message Descriptor:  Input/Output parameter \P\P
             This is the address of the message descriptor.\P\P
             The message descriptor describes the attributes
             of the message required,
             and the attributes of the message retrieved. \P
        }
      }
      }ELSE {
      HEX{ FNAME{MQMD@}  POS{3,,8}
        XNAME{MQMD ADDRESS}
        DLOC{MQLCMD@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Message Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQMD }                                /* @02 */
           DESC{Display Message Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{MsgDesc} }
        HELP{Message Descriptor:  Input/Output parameter \P\P
             This is the address of the message descriptor.\P\P
             The message descriptor describes the attributes of the
             message being sent, and receives information about the
             message after the put request is complete.
        }
      } } }
      IF {COND{OLDFMT} THEN {
      CHAR{ FNAME{MQPMO@}  POS{4,,8}
        XNAME{PMO ADDRESS}
        DLOC{MQLCDTL}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ MQPMO Detail'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQPM  }
           DESC{Display MQPMO Detail}
           }
        FDESC{ COL{7} FILL{.}
          TEXT{PutMsgOpts} }
        HELP{Put Message Options:  Input/Output parameter \P\P
             This is the address of the MQPMO structure. \P
        }
      }
      } ELSE {
      HEX{ FNAME{MQPMO@}  POS{4,,8}
        XNAME{PMO ADDRESS}
        DLOC{MQLCPMO@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ MQPMO Detail'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQPM }                                /* @02 */
           DESC{Display MQPMO Detail}
           }
        FDESC{ COL{7} FILL{.}
          TEXT{PutMsgOpts} }
        HELP{Put Message Options:  Input/Output parameter \P\P
             This is the address of the MQPMO structure. \P
        }
      }
      } }
      HEX{ FNAME{BFRLGTH}  POS{5,,8}
        XNAME{BUFFER LENGTH}
        DLOC{MQLCBFRL}
        FDESC{ COL{7} FILL{.}
          TEXT{BufferLength} }
        HELP{Buffer Length:  Input parameter \P\P
             This is the length of the message in Buffer.
        }
      }
      BIN{ FNAME{BFRLGTH2}  POS{5,51,8} /*->3ColWithFDesc<-*/
        XNAME{BUFFER LENGTH}
        DLOC{MQLCBFRL}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{BUFFR@}  POS{6,,8}
        XNAME{BUFFER ADDRESS}
        DLOC{MQLCBFR@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Buffer'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQINVBFR @FF001 @FF002 }
           DESC{Displays the message bufer area }
        }
        FDESC{ COL{7} FILL{.}
          TEXT{Buffer} }
        HELP{Buffer:  Input parameter \P\P
             This is the address of the buffer area containing the
             application data to be sent. \P
        }
      }
      BIN{ FNAME{COMPCODE} POS{7,,8}
        XNAME{COMP CODE}
        DLOC{MQLCMQCC}
        FDESC{ COL{7} FILL{.}
          TEXT{CompCode} }
        HELP{Completion Code:  Output parameter \P\P
             This is the completion code for the MQ API call. \P
        }
      }
      CHOICE{ FNAME{MQCCEQU} POS{7,40,20}
      XNAME{MQCCEQU}
      DLOC{MQLCMQCC}
       LISTV{
            VALUE{X'00','MQCC_OK'}
            VALUE{X'01','MQCC_WARNING'}
            VALUE{X'02','MQCC_FAILED'}
       }
      }
      CHAR{ FNAME{REASCODE} POS{8,,4}
        XNAME{REASON CODE}
        DLOC{MQLCRC}
        FDESC{ COL{7} FILL{.}
          TEXT{Reason} }
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQDI @FF005}
           DESC{Display Reason Code}
           }
        HELP{Reason Code:  Output parameter \P\P
             This is the reason code that qualifies the
             completion code for the MQ API call.
        }
      }
     CHOICE{ FNAME{RCEQU1} POS{8,40,30}
     XNAME{REASON EQU}
     DLOC{MQLCRC}
      LISTV{
           VALUE{'0000','MQRC_NONE'}
           VALUE{'2001','MQRC_ALIAS_BASE_Q_TYPE_ERROR'}
           VALUE{'2002','MQRC_ALREADY_CONNECTED'}
           VALUE{'2003','MQRC_BACKED_OUT'}
           VALUE{'2004','MQRC_BUFFER_ERROR'}
           VALUE{'2005','MQRC_BUFFER_LENGTH_ERROR'}
           VALUE{'2006','MQRC_CHAR_ATTR_LENGTH_ERROR'}
           VALUE{'2007','MQRC_CHAR_ATTRS_ERROR'}
           VALUE{'2008','MQRC_CHAR_ATTRS_TOO_SHORT'}
           VALUE{'2009','MQRC_CONNECTION_BROKEN'}
           VALUE{'2010','MQRC_DATA_LENGTH_ERROR'}
           VALUE{'2011','MQRC_DYNAMIC_Q_NAME_ERROR'}
           VALUE{'2012','MQRC_ENVIRONMENT_ERROR'}
           VALUE{'2013','MQRC_EXPIRY_ERROR'}
           VALUE{'2014','MQRC_FEEDBACK_ERROR'}
           VALUE{'2016','MQRC_GET_INHIBITED'}
           VALUE{'2017','MQRC_HANDLE_NOT_AVAILABLE'}
           VALUE{'2018','MQRC_HCONN_ERROR'}
           VALUE{'2019','MQRC_HOBJ_ERROR'}
           VALUE{'2020','MQRC_INHIBIT_VALUE_ERROR'}
           VALUE{'2021','MQRC_INT_ATTR_COUNT_ERROR'}
           VALUE{'2022','MQRC_INT_ATTR_COUNT_TOO_SMALL'}
           VALUE{'2023','MQRC_INT_ATTRS_ARRAY_ERROR'}
           VALUE{'2024','MQRC_SYNCPOINT_LIMIT_REACHED'}
           VALUE{'2025','MQRC_MAX_CONNS_LIMIT_REACHED'}
           VALUE{'2026','MQRC_MD_ERROR'}
           VALUE{'2027','MQRC_MISSING_REPLY_TO_Q'}
           VALUE{'2029','MQRC_MSG_TYPE_ERROR'}
           VALUE{'2030','MQRC_MSG_TOO_BIG_FOR_Q'}
           VALUE{'2031','MQRC_MSG_TOO_BIG_FOR_Q_MGR'}
           VALUE{'2033','MQRC_NO_MSG_AVAILABLE'}
           VALUE{'2034','MQRC_NO_MSG_UNDER_CURSOR'}
           VALUE{'2035','MQRC_NOT_AUTHORIZED'}
           VALUE{'2036','MQRC_NOT_OPEN_FOR_BROWSE'}
           VALUE{'2037','MQRC_NOT_OPEN_FOR_INPUT'}
           VALUE{'2038','MQRC_NOT_OPEN_FOR_INQUIRE'}
           VALUE{'2039','MQRC_NOT_OPEN_FOR_OUTPUT'}
           VALUE{'2040','MQRC_NOT_OPEN_FOR_SET'}
           VALUE{'2041','MQRC_OBJECT_CHANGED'}
           VALUE{'2042','MQRC_OBJECT_IN_USE'}
           VALUE{'2043','MQRC_OBJECT_TYPE_ERROR'}
           VALUE{'2044','MQRC_OD_ERROR'}
           VALUE{'2045','MQRC_OPTION_NOT_VALID_FOR_TYPE'}
           VALUE{'2046','MQRC_OPTIONS_ERROR'}
           VALUE{'2047','MQRC_PERSISTENCE_ERROR'}
           VALUE{'2048','MQRC_PERSISTENT_NOT_ALLOWED'}
           VALUE{'2049','MQRC_PRIORITY_EXCEEDS_MAXIMUM'}
           VALUE{'2050','MQRC_PRIORITY_ERROR'}
           VALUE{'2051','MQRC_PUT_INHIBITED'}
           VALUE{'2052','MQRC_Q_DELETED'}
           VALUE{'2053','MQRC_Q_FULL'}
           VALUE{'2055','MQRC_Q_NOT_EMPTY'}
           VALUE{'2056','MQRC_Q_SPACE_NOT_AVAILABLE'}
           VALUE{'2057','MQRC_Q_TYPE_ERROR'}
           VALUE{'2058','MQRC_Q_MGR_NAME_ERROR'}
           VALUE{'2059','MQRC_Q_MGR_NOT_AVAILABLE'}
           VALUE{'2061','MQRC_REPORT_OPTIONS_ERROR'}
           VALUE{'2062','MQRC_SECOND_MARK_NOT_ALLOWED'}
           VALUE{'2063','MQRC_SECURITY_ERROR'}
           VALUE{'2065','MQRC_SELECTOR_COUNT_ERROR'}
           VALUE{'2066','MQRC_SELECTOR_LIMIT_EXCEEDED'}
           VALUE{'2067','MQRC_SELECTOR_ERROR'}
           VALUE{'2068','MQRC_SELECTOR_NOT_FOR_TYPE'}
           VALUE{'2069','MQRC_SIGNAL_OUTSTANDING'}
           VALUE{'2070','MQRC_SIGNAL_REQUEST_ACCEPTED'}
           VALUE{'2071','MQRC_STORAGE_NOT_AVAILABLE'}
           VALUE{'2072','MQRC_SYNCPOINT_NOT_AVAILABLE'}
           VALUE{'2075','MQRC_TRIGGER_CONTROL_ERROR'}
           VALUE{'2076','MQRC_TRIGGER_DEPTH_ERROR'}
           VALUE{'2077','MQRC_TRIGGER_MSG_PRIORITY_ERR'}
           VALUE{'2078','MQRC_TRIGGER_TYPE_ERROR'}
           VALUE{'2079','MQRC_TRUNCATED_MSG_ACCEPTED'}
           VALUE{'2080','MQRC_TRUNCATED_MSG_FAILED'}
           VALUE{'2082','MQRC_UNKNOWN_ALIAS_BASE_Q'}
      }
      }
    IF { COND{CHKCODE} THEN {
       CHOICE{ FNAME{RCEQU2}  POS{8,40,30}
       XNAME{REASON EQU}
       DLOC{MQLCRC}
         LISTV{
           VALUE{'2085','MQRC_UNKNOWN_OBJECT_NAME'}
           VALUE{'2086','MQRC_UNKNOWN_OBJECT_Q_MGR'}
           VALUE{'2087','MQRC_UNKNOWN_REMOTE_Q_MGR'}
           VALUE{'2090','MQRC_WAIT_INTERVAL_ERROR'}
           VALUE{'2091','MQRC_XMIT_Q_TYPE_ERROR'}
           VALUE{'2092','MQRC_XMIT_Q_USAGE_ERROR'}
           VALUE{'2093','MQRC_NOT_OPEN_FOR_PASS_ALL'}
           VALUE{'2094','MQRC_NOT_OPEN_FOR_PASS_IDENT'}
           VALUE{'2095','MQRC_NOT_OPEN_FOR_SET_ALL'}
           VALUE{'2096','MQRC_NOT_OPEN_FOR_SET_IDENT'}
           VALUE{'2097','MQRC_CONTEXT_HANDLE_ERROR'}
           VALUE{'2098','MQRC_CONTEXT_NOT_AVAILABLE'}
           VALUE{'2099','MQRC_SIGNAL1_ERROR'}
           VALUE{'2100','MQRC_OBJECT_ALREADY_EXISTS'}
           VALUE{'2101','MQRC_OBJECT_DAMAGED'}
           VALUE{'2102','MQRC_RESOURCE_PROBLEM'}
           VALUE{'2103','MQRC_ANOTHER_Q_MGR_CONNECTED'}
           VALUE{'2104','MQRC_UNKNOWN_REPORT_OPTION'}
           VALUE{'2105','MQRC_STORAGE_CLASS_ERROR'}
           VALUE{'2106','MQRC_COD_NOT_VALID_FOR_XCF_Q'}
           VALUE{'2107','MQRC_XWAIT_CANCELED'}
           VALUE{'2108','MQRC_XWAIT_ERROR'}
           VALUE{'2109','MQRC_SUPPRESSED_BY_EXIT'}
           VALUE{'2110','MQRC_FORMAT_ERROR'}
           VALUE{'2111','MQRC_SOURCE_CCSID_ERROR'}
           VALUE{'2112','MQRC_SOURCE_INTEGER_ENC_ERROR'}
           VALUE{'2113','MQRC_SOURCE_DECIMAL_ENC_ERROR'}
           VALUE{'2114','MQRC_SOURCE_FLOAT_ENC_ERROR'}
           VALUE{'2115','MQRC_TARGET_CCSID_ERROR'}
           VALUE{'2116','MQRC_TARGET_INTEGER_ENC_ERROR'}
           VALUE{'2117','MQRC_TARGET_DECIMAL_ENC_ERROR'}
           VALUE{'2118','MQRC_TARGET_FLOAT_ENC_ERROR'}
           VALUE{'2119','MQRC_NOT_CONVERTED'}
           VALUE{'2120','MQRC_CONVERTED_MSG_TOO_BIG'}
           VALUE{'2120','MQRC_TRUNCATED'}
           VALUE{'2121','MQRC_NO_EXTERNAL_PARTICIPANTS'}
           VALUE{'2122','MQRC_PARTICIPANT_NOT_AVAILABLE'}
           VALUE{'2123','MQRC_OUTCOME_MIXED'}
           VALUE{'2124','MQRC_OUTCOME_PENDING'}
           VALUE{'2125','MQRC_BRIDGE_STARTED'}
           VALUE{'2126','MQRC_BRIDGE_STOPPED'}
           VALUE{'2127','MQRC_ADAPTER_STORAGE_SHORTAGE'}
           VALUE{'2128','MQRC_UOW_IN_PROGRESS'}
           VALUE{'2129','MQRC_ADAPTER_CONN_LOAD_ERROR'}
           VALUE{'2130','MQRC_ADAPTER_SERV_LOAD_ERROR'}
           VALUE{'2131','MQRC_ADAPTER_DEFS_ERROR'}
           VALUE{'2132','MQRC_ADAPTER_DEFS_LOAD_ERROR'}
           VALUE{'2133','MQRC_ADAPTER_CONV_LOAD_ERROR'}
           VALUE{'2134','MQRC_BO_ERROR'}
           VALUE{'2135','MQRC_DH_ERROR'}
           VALUE{'2136','MQRC_MULTIPLE_REASONS'}
           VALUE{'2137','MQRC_OPEN_FAILED'}
           VALUE{'2138','MQRC_ADAPTER_DISC_LOAD_ERROR'}
           VALUE{'2139','MQRC_CNO_ERROR'}
           VALUE{'2140','MQRC_CICS_WAIT_FAILED'}
           VALUE{'2141','MQRC_DLH_ERROR'}
           VALUE{'2142','MQRC_HEADER_ERROR'}
           VALUE{'2143','MQRC_SOURCE_LENGTH_ERROR'}
           VALUE{'2144','MQRC_TARGET_LENGTH_ERROR'}
           VALUE{'2145','MQRC_SOURCE_BUFFER_ERROR'}
           VALUE{'2146','MQRC_TARGET_BUFFER_ERROR'}
           VALUE{'2148','MQRC_IIH_ERROR'}
           VALUE{'2149','MQRC_PCF_ERROR'}
           VALUE{'2150','MQRC_DBCS_ERROR'}
           VALUE{'2152','MQRC_OBJECT_NAME_ERROR'}
           VALUE{'2153','MQRC_OBJECT_Q_MGR_NAME_ERROR'}
           VALUE{'2154','MQRC_RECS_PRESENT_ERROR'}
           VALUE{'2155','MQRC_OBJECT_RECORDS_ERROR'}
           VALUE{'2156','MQRC_RESPONSE_RECORDS_ERROR'}
           VALUE{'2157','MQRC_ASID_MISMATCH'}
           VALUE{'2158','MQRC_PMO_RECORD_FLAGS_ERROR'}
           VALUE{'2159','MQRC_PUT_MSG_RECORDS_ERROR'}
           VALUE{'2160','MQRC_CONN_ID_IN_USE'}
           VALUE{'2161','MQRC_Q_MGR_QUIESCING'}
           VALUE{'2162','MQRC_Q_MGR_STOPPING'}
           VALUE{'2163','MQRC_DUPLICATE_RECOV_COORD'}
           VALUE{'2173','MQRC_PMO_ERROR'}
           VALUE{'2182','MQRC_API_EXIT_NOT_FOUND'}
           VALUE{'2183','MQRC_API_EXIT_LOAD_ERROR'}
           VALUE{'2184','MQRC_REMOTE_Q_NAME_ERROR'}
           VALUE{'2185','MQRC_INCONSISTENT_PERSISTENCE'}
           VALUE{'2186','MQRC_GMO_ERROR'}
           VALUE{'2187','MQRC_CICS_BRIDGE_RESTRICTION'}
           VALUE{'2188','MQRC_STOPPED_BY_CLUSTER_EXIT'}
           VALUE{'2189','MQRC_CLUSTER_RESOLUTION_ERROR'}
           VALUE{'2190','MQRC_CONVERTED_STRING_TOO_BIG'}
           VALUE{'2191','MQRC_TMC_ERROR'}
           VALUE{'2192','MQRC_PAGESET_FULL'}
           VALUE{'2193','MQRC_PAGESET_ERROR'}
           VALUE{'2194','MQRC_NAME_NOT_VALID_FOR_TYPE'}
           VALUE{'2195','MQRC_UNEXPECTED_ERROR'}
           VALUE{'2196','MQRC_UNKNOWN_XMIT_Q'}
           VALUE{'2197','MQRC_UNKNOWN_DEF_XMIT_Q'}
           VALUE{'2198','MQRC_DEF_XMIT_Q_TYPE_ERROR'}
           VALUE{'2199','MQRC_DEF_XMIT_Q_USAGE_ERROR'}
           VALUE{'2201','MQRC_NAME_IN_USE'}
           VALUE{'2202','MQRC_CONNECTION_QUIESCING'}
           VALUE{'2203','MQRC_CONNECTION_STOPPING'}
           VALUE{'2204','MQRC_ADAPTER_NOT_AVAILABLE'}
           VALUE{'2206','MQRC_MSG_ID_ERROR'}
           VALUE{'2207','MQRC_CORREL_ID_ERROR'}
           VALUE{'2208','MQRC_FILE_SYSTEM_ERROR'}
           VALUE{'2209','MQRC_NO_MSG_LOCKED'}
           VALUE{'2216','MQRC_FILE_NOT_AUDITED'}
           VALUE{'2217','MQRC_CONNECTION_NOT_AUTHORIZED'}
           VALUE{'2218','MQRC_MSG_TOO_BIG_FOR_CHANNEL'}
           VALUE{'2219','MQRC_CALL_IN_PROGRESS'}
           VALUE{'2220','MQRC_RMH_ERROR'}
           VALUE{'2222','MQRC_Q_MGR_ACTIVE'}
           VALUE{'2223','MQRC_Q_MGR_NOT_ACTIVE'}
           VALUE{'2224','MQRC_Q_DEPTH_HIGH'}
           VALUE{'2225','MQRC_Q_DEPTH_LOW'}
           VALUE{'2226','MQRC_Q_SERVICE_INTERVAL_HIGH'}
           VALUE{'2227','MQRC_Q_SERVICE_INTERVAL_OK'}
           VALUE{'2232','MQRC_UNIT_OF_WORK_NOT_STARTED'}
           VALUE{'2233','MQRC_CHANNEL_AUTO_DEF_OK'}
           VALUE{'2234','MQRC_CHANNEL_AUTO_DEF_ERROR'}
           VALUE{'2235','MQRC_CFH_ERROR'}
           VALUE{'2236','MQRC_CFIL_ERROR'}
           VALUE{'2237','MQRC_CFIN_ERROR'}
           VALUE{'2238','MQRC_CFSL_ERROR'}
           VALUE{'2239','MQRC_CFST_ERROR'}
           VALUE{'2241','MQRC_INCOMPLETE_GROUP'}
           VALUE{'2242','MQRC_INCOMPLETE_MSG'}
           VALUE{'2243','MQRC_INCONSISTENT_CCSIDS'}
           VALUE{'2244','MQRC_INCONSISTENT_ENCODINGS'}
           VALUE{'2245','MQRC_INCONSISTENT_UOW'}
           VALUE{'2246','MQRC_INVALID_MSG_UNDER_CURSOR'}
           VALUE{'2247','MQRC_MATCH_OPTIONS_ERROR'}
           VALUE{'2248','MQRC_MDE_ERROR'}
           VALUE{'2249','MQRC_MSG_FLAGS_ERROR'}
           VALUE{'2250','MQRC_MSG_SEQ_NUMBER_ERROR'}
           VALUE{'2251','MQRC_OFFSET_ERROR'}
           VALUE{'2252','MQRC_ORIGINAL_LENGTH_ERROR'}
           VALUE{'2253','MQRC_SEGMENT_LENGTH_ZERO'}
           VALUE{'2255','MQRC_UOW_NOT_AVAILABLE'}
           VALUE{'2256','MQRC_WRONG_GMO_VERSION'}
           VALUE{'2257','MQRC_WRONG_MD_VERSION'}
           VALUE{'2258','MQRC_GROUP_ID_ERROR'}
           VALUE{'2259','MQRC_INCONSISTENT_BROWSE'}
           VALUE{'2260','MQRC_XQH_ERROR'}
           VALUE{'2261','MQRC_SRC_ENV_ERROR'}
           VALUE{'2262','MQRC_SRC_NAME_ERROR'}
           VALUE{'2263','MQRC_DEST_ENV_ERROR'}
           VALUE{'2264','MQRC_DEST_NAME_ERROR'}
           VALUE{'2265','MQRC_TM_ERROR'}
           VALUE{'2266','MQRC_CLUSTER_EXIT_ERROR'}
           VALUE{'2267','MQRC_CLUSTER_EXIT_LOAD_ERROR'}
           VALUE{'2268','MQRC_CLUSTER_PUT_INHIBITED'}
           VALUE{'2269','MQRC_CLUSTER_RESOURCE_ERROR'}
           VALUE{'2270','MQRC_NO_DESTINATIONS_AVAILABLE'}
           VALUE{'2273','MQRC_CONNECTION_ERROR'}
           VALUE{'2274','MQRC_OPTION_ENVIRONMENT_ERROR'}
           VALUE{'2277','MQRC_CD_ERROR'}
           VALUE{'2278','MQRC_CLIENT_CONN_ERROR'}
           VALUE{'2279','MQRC_CHANNEL_STOPPED_BY_USER'}
           VALUE{'2280','MQRC_HCONFIG_ERROR'}
           VALUE{'2281','MQRC_FUNCTION_ERROR'}
           VALUE{'2282','MQRC_CHANNEL_STARTED'}
           VALUE{'2283','MQRC_CHANNEL_STOPPED'}
           VALUE{'2284','MQRC_CHANNEL_CONV_ERROR'}
           VALUE{'2285','MQRC_SERVICE_NOT_AVAILABLE'}
           VALUE{'2286','MQRC_INITIALIZATION_FAILED'}
           VALUE{'2287','MQRC_TERMINATION_FAILED'}
           VALUE{'2288','MQRC_UNKNOWN_Q_NAME'}
           VALUE{'2289','MQRC_SERVICE_ERROR'}
           VALUE{'2290','MQRC_Q_ALREADY_EXISTS'}
           VALUE{'2291','MQRC_USER_ID_NOT_AVAILABLE'}
           VALUE{'2292','MQRC_UNKNOWN_ENTITY'}
           VALUE{'2293','MQRC_UNKNOWN_AUTH_ENTITY'}
           VALUE{'2294','MQRC_UNKNOWN_REF_OBJECT'}
           VALUE{'2295','MQRC_CHANNEL_ACTIVATED'}
           VALUE{'2296','MQRC_CHANNEL_NOT_ACTIVATED'}
           VALUE{'2297','MQRC_UOW_CANCELED'}
           VALUE{'2299','MQRC_SELECTOR_TYPE_ERROR'}
           VALUE{'2300','MQRC_COMMAND_TYPE_ERROR'}
           VALUE{'2301','MQRC_MULTIPLE_INSTANCE_ERROR'}
           VALUE{'2302','MQRC_SYSTEM_ITEM_NOT_ALTERABLE'}
           VALUE{'2303','MQRC_BAG_CONVERSION_ERROR'}
           VALUE{'2304','MQRC_SELECTOR_OUT_OF_RANGE'}
           VALUE{'2305','MQRC_SELECTOR_NOT_UNIQUE'}
           VALUE{'2306','MQRC_INDEX_NOT_PRESENT'}
           VALUE{'2307','MQRC_STRING_ERROR'}
           VALUE{'2308','MQRC_ENCODING_NOT_SUPPORTED'}
           VALUE{'2309','MQRC_SELECTOR_NOT_PRESENT'}
           VALUE{'2310','MQRC_OUT_SELECTOR_ERROR'}
           VALUE{'2311','MQRC_STRING_TRUNCATED'}
           VALUE{'2312','MQRC_SELECTOR_WRONG_TYPE'}
           VALUE{'2313','MQRC_INCONSISTENT_ITEM_TYPE'}
           VALUE{'2314','MQRC_INDEX_ERROR'}
           VALUE{'2315','MQRC_SYSTEM_BAG_NOT_ALTERABLE'}
           VALUE{'2316','MQRC_ITEM_COUNT_ERROR'}
           VALUE{'2317','MQRC_FORMAT_NOT_SUPPORTED'}
           VALUE{'2318','MQRC_SELECTOR_NOT_SUPPORTED'}
           VALUE{'2319','MQRC_ITEM_VALUE_ERROR'}
           VALUE{'2320','MQRC_HBAG_ERROR'}
           VALUE{'2321','MQRC_PARAMETER_MISSING'}
           VALUE{'2322','MQRC_CMD_SERVER_NOT_AVAILABLE'}
           VALUE{'2323','MQRC_STRING_LENGTH_ERROR'}
           VALUE{'2324','MQRC_INQUIRY_COMMAND_ERROR'}
           VALUE{'2325','MQRC_NESTED_BAG_NOT_SUPPORTED'}
           VALUE{'2326','MQRC_BAG_WRONG_TYPE'}
           VALUE{'2327','MQRC_ITEM_TYPE_ERROR'}
           VALUE{'2328','MQRC_SYSTEM_BAG_NOT_DELETABLE'}
           VALUE{'2329','MQRC_SYSTEM_ITEM_NOT_DELETABLE'}
           VALUE{'2330','MQRC_CODED_CHAR_SET_ID_ERROR'}
           VALUE{'2331','MQRC_MSG_TOKEN_ERROR'}
           VALUE{'2332','MQRC_MISSING_WIH'}
           VALUE{'2333','MQRC_WIH_ERROR'}
        }
       }
       }}
    }    /* end-group */
;
    GROUP{ POS{13,1,79}
      HDR{YES} FNAME{EXCALINF}
        TEXT{                        Expanded Call Information }
    }
;
    GROUP{ POS{15,1,79}
        DATACOL{25}
      CHAR{ FNAME{QMGRNAME} POS{1,,4}
        XNAME{QMGR NAME}
        DLOC{MQLCQMGR}
        FDESC{ COL{1} FILL{.}
          TEXT{QMgr Name} }
        HELP{This is the name of the queue manager that CICS was
             connected to at the time of the dump. \P
        }
      }
      CHAR{ FNAME{QNAME} POS{2,,48}
        XNAME{QUEUE NAME}
        DLOC{MQLCQNME}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQCB @FF003 @FF004 }
              DESC{Displays the queue defintions.  } }
        }}
        FDESC{ COL{1} FILL{.}
          TEXT{Queue Used in Call} }
        HELP{This is the name of the queue that was used for the
             MQPUT call. \P
        }
      }
    IF {COND{OLDFMT} THEN { } ELSE {
      IF { COND{GOTMHND} THEN {
         HEX{ FNAME{OPENOPT}  POS{3,,8}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQM2 OPN @FF006 }
              DESC{Displays the OPEN options} }
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
      } ELSE {
         CHAR{ FNAME{OPENOPT}  POS{3,,4}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
        }
      } } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{PUTOPT}  POS{4,,8}
        XNAME{PUT OPTIONS}
        DLOC{MQLCPUT}
        ATTR{ TABS }
        IF { COND{GOODCC}
          THEN {
              COMMAND{ NAME{.DFLT}
                CMD{CPR MQM2 PUT @FF007 @FF008}               /* @01 */
                DESC{Displays the PUT options} }
          }
          ELSE {
             COMMAND{ NAME{.DFLT}
                CMD{CPR MQM2 PUT @FF008}
                DESC{Displays the PUT options} }
          }
        }
        FDESC{ COL{1} FILL{.}
          TEXT{Put Options} }
        HELP{These are the MQPMO options that were specified by the
             program for the MQPUT call.
        }
      } } }
   }  /* end-group */
;
  }                                              /* end-fixed */        03130000
  HELP{The MQPUT call puts a message on a queue. \P\P
       This screen displays the parameters that were used in the        03140000
       MQPUT call. \P\P

  }                                                                     03160000
}                                                /* end-screen */       03170000
:END                                                                    03180000
*
*
:SCREEN{ NAME{MQLPUT1} TITLE{Last WebSphere MQ Call Info}               00600000
 TEMPLATE{KAZHDTMP.MQLPUT1}                     /* @03 */
  ORG{KAZ#MQLC}                                                         00610000
  FIXED{                                                                00620000
;
    DP{ FNAME{F001}     DLOC{MQLCBFR@} }
    DP{ FNAME{F002}     DLOC{MQLCBFRL} }
    DP{ FNAME{F003}     DLOC{MQLCQTYP} }
    DP{ FNAME{F004}     DLOC{MQLCHOBJ} }
    DP{ FNAME{F005}     DLOC{MQLCRC} }
    DP{ FNAME{F006}     DLOC{MQLCOPEN} }      /* PROG OPEN OPTIONS */
    DP{ FNAME{F007}     DLOC{MQLCMQPO} }      /* MQ PUT OPTIONS    */
    DP{ FNAME{F008}     DLOC{MQLCPUT} }       /* PROG PUT OPTIONS  */
;
   COND{ FNAME{CHKCODE} DLOC{MQLCRC}
         COMPOP{CLC,'2085',NL} }
   COND{ FNAME{GOTMHND} DLOC{MQLCMHND}
         COMPOP{CLC,'Y',E} }
   COND{ FNAME{GOODCC} DLOC{MQLCMQCC}
         COMPOP{CB,X'00000002',L} }
   COND{FNAME{OLDFMT} DLOC{MQLC@FMT}
         COMPOP{CLC,'1',E} }
;
    LITERAL{ FNAME{CALMPT1} POS{1,1,40} /*->fixedPro<-*/ /* @03 */
        TEXT {CALL 'MQPUT1' USING}  }
    GROUP{ POS{2,1,79}
        DATACOL{25}
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HCONN}  POS{1,,8}
        XNAME{HCONN}
        DLOC{MQLCHCON}
        FDESC{ COL{7} FILL{.}
          TEXT{Hconn} }
        HELP{Connection Handle:  Input parameter \P\P
             This parameter represents the connection to the queue
             manager. The value was return on a previous MQCONN call.
             \P\P
             On OS/390 for CICS applications, the MQCONN call can be
             omitted and the value of MQHC_DEF_HCONN can be specified
             for this parameter. \P
        }
      } } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{OBJDESC}  POS{2,,8}
        XNAME{OBJ DESCPRIPTOR}
        DLOC{MQLCOD@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Object Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQOD}
           DESC{Display Object Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{ObjDesc} }
        HELP{Object Descriptor:  Input/Output parameter \P\P
             This is the address of the object descriptor.\P\P
             The object descriptor is a structure that identifies the
             queue to which the message is added. \P
        }
      } } }
     IF {COND{OLDFMT} THEN {
      CHAR{ FNAME{MQMD@}  POS{3,,8}
        XNAME{MQMD ADDRESS}
        DLOC{MQLCDTL}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Message Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQMD }
           DESC{Display Message Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{MsgDesc} }
        HELP{Message Descriptor:  Input/Output parameter \P\P
             This is the address of the message descriptor.\P\P
             The message descriptor describes the attributes
             of the message required,
             and the attributes of the message retrieved. \P
        }
      }
      }ELSE {
      HEX{ FNAME{MQMD@}  POS{3,,8}
        XNAME{MQMD ADDRESS}
        DLOC{MQLCMD@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Message Descriptor'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQMD }                                /* @02 */
           DESC{Display Message Descriptor Detail}
        }
        FDESC{ COL{7} FILL{.}
          TEXT{MsgDesc} }
        HELP{Message Descriptor:  Input/Output parameter \P\P
             This is the address of the message descriptor.\P\P
             The message descriptor describes the attributes of the
             message being sent, and receives information about the
             message after the put request is complete.
        }
      } } }
      HEX{ FNAME{MQPMO@}  POS{4,,8}
        XNAME{PMO ADDRESS}
        DLOC{MQLCPMO@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ MQPMO Detail'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQCB MQPM }                                /* @02 */
           DESC{Display MQPMO Detail}
           }
        FDESC{ COL{7} FILL{.}
          TEXT{PutMsgOpts} }
        HELP{Put Message Options:  Input/Output parameter \P\P
             This is the address of the MQPMO structure. \P
        }
      }
      HEX{ FNAME{BFRLGTH}  POS{5,,8}
        XNAME{BUFFER LENGTH}
        DLOC{MQLCBFRL}
        FDESC{ COL{7} FILL{.}
          TEXT{BufferLength} }
        HELP{Buffer Length:  Input parameter \P\P
             This is the length of the message in Buffer.
        }
      }
      BIN{ FNAME{BFRLGTH2}  POS{5,51,8} /*->3ColWithFDesc<-*/
        XNAME{BUFFER LENGTH}
        DLOC{MQLCBFRL}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{BUFFR@}  POS{6,,8}
        XNAME{BUFFER ADDRESS}
        DLOC{MQLCBFR@}
        ATTR{ TABS }
        HEXD{A,'WebSphere MQ Buffer'}
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQINVBFR @FF001 @FF002 }
           DESC{Displays the message bufer area }
        }
        FDESC{ COL{7} FILL{.}
          TEXT{Buffer} }
        HELP{Buffer:  Input parameter \P\P
             This is the address of the buffer area containing the
             application data to be sent. \P
        }
      }
      BIN{ FNAME{COMPCODE} POS{7,,8}
        XNAME{COMP CODE}
        DLOC{MQLCMQCC}
        FDESC{ COL{7} FILL{.}
          TEXT{CompCode} }
        HELP{Completion Code:  Output parameter \P\P
             This is the completion code for the MQ API call. \P
        }
      }
      CHOICE{ FNAME{MQCCEQU} POS{7,40,20}
      XNAME{MQCCEQU}
      DLOC{MQLCMQCC}
       LISTV{
            VALUE{X'00','MQCC_OK'}
            VALUE{X'01','MQCC_WARNING'}
            VALUE{X'02','MQCC_FAILED'}
       }
      }
      CHAR{ FNAME{REASCODE} POS{8,,4}
        XNAME{REASON CODE}
        DLOC{MQLCRC}
        FDESC{ COL{7} FILL{.}
          TEXT{Reason} }
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQDI @FF005}
           DESC{Display Reason Code}
           }
        HELP{Reason Code:  Output parameter \P\P
             This is the reason code that qualifies the
             completion code for the MQ API call.
        }
      }
     CHOICE{ FNAME{RCEQU1} POS{8,40,30}
     XNAME{REASON EQU}
     DLOC{MQLCRC}
      LISTV{
           VALUE{'0000','MQRC_NONE'}
           VALUE{'2001','MQRC_ALIAS_BASE_Q_TYPE_ERROR'}
           VALUE{'2002','MQRC_ALREADY_CONNECTED'}
           VALUE{'2003','MQRC_BACKED_OUT'}
           VALUE{'2004','MQRC_BUFFER_ERROR'}
           VALUE{'2005','MQRC_BUFFER_LENGTH_ERROR'}
           VALUE{'2006','MQRC_CHAR_ATTR_LENGTH_ERROR'}
           VALUE{'2007','MQRC_CHAR_ATTRS_ERROR'}
           VALUE{'2008','MQRC_CHAR_ATTRS_TOO_SHORT'}
           VALUE{'2009','MQRC_CONNECTION_BROKEN'}
           VALUE{'2010','MQRC_DATA_LENGTH_ERROR'}
           VALUE{'2011','MQRC_DYNAMIC_Q_NAME_ERROR'}
           VALUE{'2012','MQRC_ENVIRONMENT_ERROR'}
           VALUE{'2013','MQRC_EXPIRY_ERROR'}
           VALUE{'2014','MQRC_FEEDBACK_ERROR'}
           VALUE{'2016','MQRC_GET_INHIBITED'}
           VALUE{'2017','MQRC_HANDLE_NOT_AVAILABLE'}
           VALUE{'2018','MQRC_HCONN_ERROR'}
           VALUE{'2019','MQRC_HOBJ_ERROR'}
           VALUE{'2020','MQRC_INHIBIT_VALUE_ERROR'}
           VALUE{'2021','MQRC_INT_ATTR_COUNT_ERROR'}
           VALUE{'2022','MQRC_INT_ATTR_COUNT_TOO_SMALL'}
           VALUE{'2023','MQRC_INT_ATTRS_ARRAY_ERROR'}
           VALUE{'2024','MQRC_SYNCPOINT_LIMIT_REACHED'}
           VALUE{'2025','MQRC_MAX_CONNS_LIMIT_REACHED'}
           VALUE{'2026','MQRC_MD_ERROR'}
           VALUE{'2027','MQRC_MISSING_REPLY_TO_Q'}
           VALUE{'2029','MQRC_MSG_TYPE_ERROR'}
           VALUE{'2030','MQRC_MSG_TOO_BIG_FOR_Q'}
           VALUE{'2031','MQRC_MSG_TOO_BIG_FOR_Q_MGR'}
           VALUE{'2033','MQRC_NO_MSG_AVAILABLE'}
           VALUE{'2034','MQRC_NO_MSG_UNDER_CURSOR'}
           VALUE{'2035','MQRC_NOT_AUTHORIZED'}
           VALUE{'2036','MQRC_NOT_OPEN_FOR_BROWSE'}
           VALUE{'2037','MQRC_NOT_OPEN_FOR_INPUT'}
           VALUE{'2038','MQRC_NOT_OPEN_FOR_INQUIRE'}
           VALUE{'2039','MQRC_NOT_OPEN_FOR_OUTPUT'}
           VALUE{'2040','MQRC_NOT_OPEN_FOR_SET'}
           VALUE{'2041','MQRC_OBJECT_CHANGED'}
           VALUE{'2042','MQRC_OBJECT_IN_USE'}
           VALUE{'2043','MQRC_OBJECT_TYPE_ERROR'}
           VALUE{'2044','MQRC_OD_ERROR'}
           VALUE{'2045','MQRC_OPTION_NOT_VALID_FOR_TYPE'}
           VALUE{'2046','MQRC_OPTIONS_ERROR'}
           VALUE{'2047','MQRC_PERSISTENCE_ERROR'}
           VALUE{'2048','MQRC_PERSISTENT_NOT_ALLOWED'}
           VALUE{'2049','MQRC_PRIORITY_EXCEEDS_MAXIMUM'}
           VALUE{'2050','MQRC_PRIORITY_ERROR'}
           VALUE{'2051','MQRC_PUT_INHIBITED'}
           VALUE{'2052','MQRC_Q_DELETED'}
           VALUE{'2053','MQRC_Q_FULL'}
           VALUE{'2055','MQRC_Q_NOT_EMPTY'}
           VALUE{'2056','MQRC_Q_SPACE_NOT_AVAILABLE'}
           VALUE{'2057','MQRC_Q_TYPE_ERROR'}
           VALUE{'2058','MQRC_Q_MGR_NAME_ERROR'}
           VALUE{'2059','MQRC_Q_MGR_NOT_AVAILABLE'}
           VALUE{'2061','MQRC_REPORT_OPTIONS_ERROR'}
           VALUE{'2062','MQRC_SECOND_MARK_NOT_ALLOWED'}
           VALUE{'2063','MQRC_SECURITY_ERROR'}
           VALUE{'2065','MQRC_SELECTOR_COUNT_ERROR'}
           VALUE{'2066','MQRC_SELECTOR_LIMIT_EXCEEDED'}
           VALUE{'2067','MQRC_SELECTOR_ERROR'}
           VALUE{'2068','MQRC_SELECTOR_NOT_FOR_TYPE'}
           VALUE{'2069','MQRC_SIGNAL_OUTSTANDING'}
           VALUE{'2070','MQRC_SIGNAL_REQUEST_ACCEPTED'}
           VALUE{'2071','MQRC_STORAGE_NOT_AVAILABLE'}
           VALUE{'2072','MQRC_SYNCPOINT_NOT_AVAILABLE'}
           VALUE{'2075','MQRC_TRIGGER_CONTROL_ERROR'}
           VALUE{'2076','MQRC_TRIGGER_DEPTH_ERROR'}
           VALUE{'2077','MQRC_TRIGGER_MSG_PRIORITY_ERR'}
           VALUE{'2078','MQRC_TRIGGER_TYPE_ERROR'}
           VALUE{'2079','MQRC_TRUNCATED_MSG_ACCEPTED'}
           VALUE{'2080','MQRC_TRUNCATED_MSG_FAILED'}
           VALUE{'2082','MQRC_UNKNOWN_ALIAS_BASE_Q'}
      }
      }
    IF { COND{CHKCODE} THEN {
       CHOICE{ FNAME{RCEQU2}  POS{8,40,30}
       XNAME{REASON EQU}
       DLOC{MQLCRC}
         LISTV{
           VALUE{'2085','MQRC_UNKNOWN_OBJECT_NAME'}
           VALUE{'2086','MQRC_UNKNOWN_OBJECT_Q_MGR'}
           VALUE{'2087','MQRC_UNKNOWN_REMOTE_Q_MGR'}
           VALUE{'2090','MQRC_WAIT_INTERVAL_ERROR'}
           VALUE{'2091','MQRC_XMIT_Q_TYPE_ERROR'}
           VALUE{'2092','MQRC_XMIT_Q_USAGE_ERROR'}
           VALUE{'2093','MQRC_NOT_OPEN_FOR_PASS_ALL'}
           VALUE{'2094','MQRC_NOT_OPEN_FOR_PASS_IDENT'}
           VALUE{'2095','MQRC_NOT_OPEN_FOR_SET_ALL'}
           VALUE{'2096','MQRC_NOT_OPEN_FOR_SET_IDENT'}
           VALUE{'2097','MQRC_CONTEXT_HANDLE_ERROR'}
           VALUE{'2098','MQRC_CONTEXT_NOT_AVAILABLE'}
           VALUE{'2099','MQRC_SIGNAL1_ERROR'}
           VALUE{'2100','MQRC_OBJECT_ALREADY_EXISTS'}
           VALUE{'2101','MQRC_OBJECT_DAMAGED'}
           VALUE{'2102','MQRC_RESOURCE_PROBLEM'}
           VALUE{'2103','MQRC_ANOTHER_Q_MGR_CONNECTED'}
           VALUE{'2104','MQRC_UNKNOWN_REPORT_OPTION'}
           VALUE{'2105','MQRC_STORAGE_CLASS_ERROR'}
           VALUE{'2106','MQRC_COD_NOT_VALID_FOR_XCF_Q'}
           VALUE{'2107','MQRC_XWAIT_CANCELED'}
           VALUE{'2108','MQRC_XWAIT_ERROR'}
           VALUE{'2109','MQRC_SUPPRESSED_BY_EXIT'}
           VALUE{'2110','MQRC_FORMAT_ERROR'}
           VALUE{'2111','MQRC_SOURCE_CCSID_ERROR'}
           VALUE{'2112','MQRC_SOURCE_INTEGER_ENC_ERROR'}
           VALUE{'2113','MQRC_SOURCE_DECIMAL_ENC_ERROR'}
           VALUE{'2114','MQRC_SOURCE_FLOAT_ENC_ERROR'}
           VALUE{'2115','MQRC_TARGET_CCSID_ERROR'}
           VALUE{'2116','MQRC_TARGET_INTEGER_ENC_ERROR'}
           VALUE{'2117','MQRC_TARGET_DECIMAL_ENC_ERROR'}
           VALUE{'2118','MQRC_TARGET_FLOAT_ENC_ERROR'}
           VALUE{'2119','MQRC_NOT_CONVERTED'}
           VALUE{'2120','MQRC_CONVERTED_MSG_TOO_BIG'}
           VALUE{'2120','MQRC_TRUNCATED'}
           VALUE{'2121','MQRC_NO_EXTERNAL_PARTICIPANTS'}
           VALUE{'2122','MQRC_PARTICIPANT_NOT_AVAILABLE'}
           VALUE{'2123','MQRC_OUTCOME_MIXED'}
           VALUE{'2124','MQRC_OUTCOME_PENDING'}
           VALUE{'2125','MQRC_BRIDGE_STARTED'}
           VALUE{'2126','MQRC_BRIDGE_STOPPED'}
           VALUE{'2127','MQRC_ADAPTER_STORAGE_SHORTAGE'}
           VALUE{'2128','MQRC_UOW_IN_PROGRESS'}
           VALUE{'2129','MQRC_ADAPTER_CONN_LOAD_ERROR'}
           VALUE{'2130','MQRC_ADAPTER_SERV_LOAD_ERROR'}
           VALUE{'2131','MQRC_ADAPTER_DEFS_ERROR'}
           VALUE{'2132','MQRC_ADAPTER_DEFS_LOAD_ERROR'}
           VALUE{'2133','MQRC_ADAPTER_CONV_LOAD_ERROR'}
           VALUE{'2134','MQRC_BO_ERROR'}
           VALUE{'2135','MQRC_DH_ERROR'}
           VALUE{'2136','MQRC_MULTIPLE_REASONS'}
           VALUE{'2137','MQRC_OPEN_FAILED'}
           VALUE{'2138','MQRC_ADAPTER_DISC_LOAD_ERROR'}
           VALUE{'2139','MQRC_CNO_ERROR'}
           VALUE{'2140','MQRC_CICS_WAIT_FAILED'}
           VALUE{'2141','MQRC_DLH_ERROR'}
           VALUE{'2142','MQRC_HEADER_ERROR'}
           VALUE{'2143','MQRC_SOURCE_LENGTH_ERROR'}
           VALUE{'2144','MQRC_TARGET_LENGTH_ERROR'}
           VALUE{'2145','MQRC_SOURCE_BUFFER_ERROR'}
           VALUE{'2146','MQRC_TARGET_BUFFER_ERROR'}
           VALUE{'2148','MQRC_IIH_ERROR'}
           VALUE{'2149','MQRC_PCF_ERROR'}
           VALUE{'2150','MQRC_DBCS_ERROR'}
           VALUE{'2152','MQRC_OBJECT_NAME_ERROR'}
           VALUE{'2153','MQRC_OBJECT_Q_MGR_NAME_ERROR'}
           VALUE{'2154','MQRC_RECS_PRESENT_ERROR'}
           VALUE{'2155','MQRC_OBJECT_RECORDS_ERROR'}
           VALUE{'2156','MQRC_RESPONSE_RECORDS_ERROR'}
           VALUE{'2157','MQRC_ASID_MISMATCH'}
           VALUE{'2158','MQRC_PMO_RECORD_FLAGS_ERROR'}
           VALUE{'2159','MQRC_PUT_MSG_RECORDS_ERROR'}
           VALUE{'2160','MQRC_CONN_ID_IN_USE'}
           VALUE{'2161','MQRC_Q_MGR_QUIESCING'}
           VALUE{'2162','MQRC_Q_MGR_STOPPING'}
           VALUE{'2163','MQRC_DUPLICATE_RECOV_COORD'}
           VALUE{'2173','MQRC_PMO_ERROR'}
           VALUE{'2182','MQRC_API_EXIT_NOT_FOUND'}
           VALUE{'2183','MQRC_API_EXIT_LOAD_ERROR'}
           VALUE{'2184','MQRC_REMOTE_Q_NAME_ERROR'}
           VALUE{'2185','MQRC_INCONSISTENT_PERSISTENCE'}
           VALUE{'2186','MQRC_GMO_ERROR'}
           VALUE{'2187','MQRC_CICS_BRIDGE_RESTRICTION'}
           VALUE{'2188','MQRC_STOPPED_BY_CLUSTER_EXIT'}
           VALUE{'2189','MQRC_CLUSTER_RESOLUTION_ERROR'}
           VALUE{'2190','MQRC_CONVERTED_STRING_TOO_BIG'}
           VALUE{'2191','MQRC_TMC_ERROR'}
           VALUE{'2192','MQRC_PAGESET_FULL'}
           VALUE{'2193','MQRC_PAGESET_ERROR'}
           VALUE{'2194','MQRC_NAME_NOT_VALID_FOR_TYPE'}
           VALUE{'2195','MQRC_UNEXPECTED_ERROR'}
           VALUE{'2196','MQRC_UNKNOWN_XMIT_Q'}
           VALUE{'2197','MQRC_UNKNOWN_DEF_XMIT_Q'}
           VALUE{'2198','MQRC_DEF_XMIT_Q_TYPE_ERROR'}
           VALUE{'2199','MQRC_DEF_XMIT_Q_USAGE_ERROR'}
           VALUE{'2201','MQRC_NAME_IN_USE'}
           VALUE{'2202','MQRC_CONNECTION_QUIESCING'}
           VALUE{'2203','MQRC_CONNECTION_STOPPING'}
           VALUE{'2204','MQRC_ADAPTER_NOT_AVAILABLE'}
           VALUE{'2206','MQRC_MSG_ID_ERROR'}
           VALUE{'2207','MQRC_CORREL_ID_ERROR'}
           VALUE{'2208','MQRC_FILE_SYSTEM_ERROR'}
           VALUE{'2209','MQRC_NO_MSG_LOCKED'}
           VALUE{'2216','MQRC_FILE_NOT_AUDITED'}
           VALUE{'2217','MQRC_CONNECTION_NOT_AUTHORIZED'}
           VALUE{'2218','MQRC_MSG_TOO_BIG_FOR_CHANNEL'}
           VALUE{'2219','MQRC_CALL_IN_PROGRESS'}
           VALUE{'2220','MQRC_RMH_ERROR'}
           VALUE{'2222','MQRC_Q_MGR_ACTIVE'}
           VALUE{'2223','MQRC_Q_MGR_NOT_ACTIVE'}
           VALUE{'2224','MQRC_Q_DEPTH_HIGH'}
           VALUE{'2225','MQRC_Q_DEPTH_LOW'}
           VALUE{'2226','MQRC_Q_SERVICE_INTERVAL_HIGH'}
           VALUE{'2227','MQRC_Q_SERVICE_INTERVAL_OK'}
           VALUE{'2232','MQRC_UNIT_OF_WORK_NOT_STARTED'}
           VALUE{'2233','MQRC_CHANNEL_AUTO_DEF_OK'}
           VALUE{'2234','MQRC_CHANNEL_AUTO_DEF_ERROR'}
           VALUE{'2235','MQRC_CFH_ERROR'}
           VALUE{'2236','MQRC_CFIL_ERROR'}
           VALUE{'2237','MQRC_CFIN_ERROR'}
           VALUE{'2238','MQRC_CFSL_ERROR'}
           VALUE{'2239','MQRC_CFST_ERROR'}
           VALUE{'2241','MQRC_INCOMPLETE_GROUP'}
           VALUE{'2242','MQRC_INCOMPLETE_MSG'}
           VALUE{'2243','MQRC_INCONSISTENT_CCSIDS'}
           VALUE{'2244','MQRC_INCONSISTENT_ENCODINGS'}
           VALUE{'2245','MQRC_INCONSISTENT_UOW'}
           VALUE{'2246','MQRC_INVALID_MSG_UNDER_CURSOR'}
           VALUE{'2247','MQRC_MATCH_OPTIONS_ERROR'}
           VALUE{'2248','MQRC_MDE_ERROR'}
           VALUE{'2249','MQRC_MSG_FLAGS_ERROR'}
           VALUE{'2250','MQRC_MSG_SEQ_NUMBER_ERROR'}
           VALUE{'2251','MQRC_OFFSET_ERROR'}
           VALUE{'2252','MQRC_ORIGINAL_LENGTH_ERROR'}
           VALUE{'2253','MQRC_SEGMENT_LENGTH_ZERO'}
           VALUE{'2255','MQRC_UOW_NOT_AVAILABLE'}
           VALUE{'2256','MQRC_WRONG_GMO_VERSION'}
           VALUE{'2257','MQRC_WRONG_MD_VERSION'}
           VALUE{'2258','MQRC_GROUP_ID_ERROR'}
           VALUE{'2259','MQRC_INCONSISTENT_BROWSE'}
           VALUE{'2260','MQRC_XQH_ERROR'}
           VALUE{'2261','MQRC_SRC_ENV_ERROR'}
           VALUE{'2262','MQRC_SRC_NAME_ERROR'}
           VALUE{'2263','MQRC_DEST_ENV_ERROR'}
           VALUE{'2264','MQRC_DEST_NAME_ERROR'}
           VALUE{'2265','MQRC_TM_ERROR'}
           VALUE{'2266','MQRC_CLUSTER_EXIT_ERROR'}
           VALUE{'2267','MQRC_CLUSTER_EXIT_LOAD_ERROR'}
           VALUE{'2268','MQRC_CLUSTER_PUT_INHIBITED'}
           VALUE{'2269','MQRC_CLUSTER_RESOURCE_ERROR'}
           VALUE{'2270','MQRC_NO_DESTINATIONS_AVAILABLE'}
           VALUE{'2273','MQRC_CONNECTION_ERROR'}
           VALUE{'2274','MQRC_OPTION_ENVIRONMENT_ERROR'}
           VALUE{'2277','MQRC_CD_ERROR'}
           VALUE{'2278','MQRC_CLIENT_CONN_ERROR'}
           VALUE{'2279','MQRC_CHANNEL_STOPPED_BY_USER'}
           VALUE{'2280','MQRC_HCONFIG_ERROR'}
           VALUE{'2281','MQRC_FUNCTION_ERROR'}
           VALUE{'2282','MQRC_CHANNEL_STARTED'}
           VALUE{'2283','MQRC_CHANNEL_STOPPED'}
           VALUE{'2284','MQRC_CHANNEL_CONV_ERROR'}
           VALUE{'2285','MQRC_SERVICE_NOT_AVAILABLE'}
           VALUE{'2286','MQRC_INITIALIZATION_FAILED'}
           VALUE{'2287','MQRC_TERMINATION_FAILED'}
           VALUE{'2288','MQRC_UNKNOWN_Q_NAME'}
           VALUE{'2289','MQRC_SERVICE_ERROR'}
           VALUE{'2290','MQRC_Q_ALREADY_EXISTS'}
           VALUE{'2291','MQRC_USER_ID_NOT_AVAILABLE'}
           VALUE{'2292','MQRC_UNKNOWN_ENTITY'}
           VALUE{'2293','MQRC_UNKNOWN_AUTH_ENTITY'}
           VALUE{'2294','MQRC_UNKNOWN_REF_OBJECT'}
           VALUE{'2295','MQRC_CHANNEL_ACTIVATED'}
           VALUE{'2296','MQRC_CHANNEL_NOT_ACTIVATED'}
           VALUE{'2297','MQRC_UOW_CANCELED'}
           VALUE{'2299','MQRC_SELECTOR_TYPE_ERROR'}
           VALUE{'2300','MQRC_COMMAND_TYPE_ERROR'}
           VALUE{'2301','MQRC_MULTIPLE_INSTANCE_ERROR'}
           VALUE{'2302','MQRC_SYSTEM_ITEM_NOT_ALTERABLE'}
           VALUE{'2303','MQRC_BAG_CONVERSION_ERROR'}
           VALUE{'2304','MQRC_SELECTOR_OUT_OF_RANGE'}
           VALUE{'2305','MQRC_SELECTOR_NOT_UNIQUE'}
           VALUE{'2306','MQRC_INDEX_NOT_PRESENT'}
           VALUE{'2307','MQRC_STRING_ERROR'}
           VALUE{'2308','MQRC_ENCODING_NOT_SUPPORTED'}
           VALUE{'2309','MQRC_SELECTOR_NOT_PRESENT'}
           VALUE{'2310','MQRC_OUT_SELECTOR_ERROR'}
           VALUE{'2311','MQRC_STRING_TRUNCATED'}
           VALUE{'2312','MQRC_SELECTOR_WRONG_TYPE'}
           VALUE{'2313','MQRC_INCONSISTENT_ITEM_TYPE'}
           VALUE{'2314','MQRC_INDEX_ERROR'}
           VALUE{'2315','MQRC_SYSTEM_BAG_NOT_ALTERABLE'}
           VALUE{'2316','MQRC_ITEM_COUNT_ERROR'}
           VALUE{'2317','MQRC_FORMAT_NOT_SUPPORTED'}
           VALUE{'2318','MQRC_SELECTOR_NOT_SUPPORTED'}
           VALUE{'2319','MQRC_ITEM_VALUE_ERROR'}
           VALUE{'2320','MQRC_HBAG_ERROR'}
           VALUE{'2321','MQRC_PARAMETER_MISSING'}
           VALUE{'2322','MQRC_CMD_SERVER_NOT_AVAILABLE'}
           VALUE{'2323','MQRC_STRING_LENGTH_ERROR'}
           VALUE{'2324','MQRC_INQUIRY_COMMAND_ERROR'}
           VALUE{'2325','MQRC_NESTED_BAG_NOT_SUPPORTED'}
           VALUE{'2326','MQRC_BAG_WRONG_TYPE'}
           VALUE{'2327','MQRC_ITEM_TYPE_ERROR'}
           VALUE{'2328','MQRC_SYSTEM_BAG_NOT_DELETABLE'}
           VALUE{'2329','MQRC_SYSTEM_ITEM_NOT_DELETABLE'}
           VALUE{'2330','MQRC_CODED_CHAR_SET_ID_ERROR'}
           VALUE{'2331','MQRC_MSG_TOKEN_ERROR'}
           VALUE{'2332','MQRC_MISSING_WIH'}
           VALUE{'2333','MQRC_WIH_ERROR'}
        }
       }
       }}
    }    /* end-group */
;
    GROUP{ POS{13,1,79}
      HDR{YES} FNAME{EXCALINF}
        TEXT{                        Expanded Call Information }
    }
;
    GROUP{ POS{15,1,79}
        DATACOL{25}
      CHAR{ FNAME{QMGRNAME} POS{1,,4}
        XNAME{QMGR NAME}
        DLOC{MQLCQMGR}
        FDESC{ COL{1} FILL{.}
          TEXT{QMgr Name} }
        HELP{This is the name of the queue manager that CICS was
             connected to at the time of the dump. \P
        }
      }
      CHAR{ FNAME{QNAME} POS{2,,48}
        XNAME{QUEUE NAME}
        DLOC{MQLCQNME}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQCB @FF003 @FF004 }
              DESC{Displays the queue defintions.  } }
        }}
        FDESC{ COL{1} FILL{.}
          TEXT{Queue Used in Call} }
        HELP{This is the name of the queue that was used for the
             MQPUT1 call. \P
        }
      }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{PUTOPT}  POS{3,,8}
        XNAME{PUT OPTIONS}
        DLOC{MQLCPUT}
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQM2 PUT @FF008}
           DESC{Displays the PUT options} }
        FDESC{ COL{1} FILL{.}
          TEXT{Put Options} }
        HELP{These are the MQPMO options that were specified by the
             program for the MQPUT1 call.
        }
      } } }
   }  /* end-group */
;
  }                                              /* end-fixed */        03130000
  HELP{The MQPUT1 call puts a message on a queue. The queue need
       not be opened. \P\P
       This screen displays the parameters that were used in the
       MQPUT1 call. \P\P

  }
}                                                /* end-screen */       03170000
:END                                                                    03180000
*
*
:SCREEN{ NAME{MQLINQ} TITLE{Last WebSphere MQ Call Info}                00600000
 TEMPLATE{KAZHDTMP.MQLINQ}                     /* @03 */
  ORG{KAZ#MQLC}                                                         00610000
  FIXED{                                                                00620000
;
    DP{ FNAME{F001}     DLOC{MQLCBFR@} }
    DP{ FNAME{F002}     DLOC{MQLCBFRL} }
    DP{ FNAME{F003}     DLOC{MQLCQTYP} }
    DP{ FNAME{F004}     DLOC{MQLCHOBJ} }
    DP{ FNAME{F005}     DLOC{MQLCRC} }
    DP{ FNAME{F006}     DLOC{MQLCOPEN} }      /* PROG OPEN OPTIONS */
    DP{ FNAME{F009}     DLOC{MQLCQREL} }      /* MQ RELEASE    @02 */
;
   COND{ FNAME{CHKCODE} DLOC{MQLCRC}
         COMPOP{CLC,'2085',NL} }
   COND{ FNAME{GOTMHND} DLOC{MQLCMHND}
         COMPOP{CLC,'Y',E} }
   COND{ FNAME{GOODCC} DLOC{MQLCMQCC}
         COMPOP{CB,X'00000002',L} }
   COND{FNAME{OLDFMT} DLOC{MQLC@FMT}
         COMPOP{CLC,'1',E} }
;
    LITERAL{ FNAME{CALMQNQ} POS{1,1,40} /*->fixedPro<-*/ /* @03 */
        TEXT {CALL 'MQINQ' USING}  }
    GROUP{ POS{2,1,79}
        DATACOL{25}
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HCONN}  POS{1,,8}
        XNAME{HCONN}
        DLOC{MQLCHCON}
        FDESC{ COL{7} FILL{.}
          TEXT{Hconn} }
        HELP{Connection Handle:  Input parameter \P\P
             This parameter represents the connection to the queue
             manager. The value was return on a previous MQCONN call.
             \P\P
             On OS/390 for CICS applications, the MQCONN call can be
             omitted and the value of MQHC_DEF_HCONN can be specified
             for this parameter. \P
        }
      }  } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HOBJECT}  POS{2,,8}
        XNAME{HOBJECT}
        DLOC{MQLCHOBJ}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQHI @FF004 C @FF009}                   /* @02 */
              DESC{Display Handle Information} }
        }}
        FDESC{ COL{7} FILL{.}
          TEXT{Hobj} }
        HELP{Object Handle:  Input parameter \P\P
             This handle represents the object (of any type) whose
             attributes are required. \P
             The handle must have been returned by a previous MQOPEN
             call that specified the MQOO_INQUIRE option. \P
        }
      } } }
      HEX{ FNAME{SELCNT}  POS{3,,8}
        XNAME{SELECTOR COUNT}
        DLOC{MQLCSEL#}
        FDESC{ COL{7} FILL{.}
          TEXT{SelectorCount} }
        HELP{Selector Count:  Input parameter \P\P
             This is the count of selectors that are supplied in the
             Selectors array. It is the number of attributes
             that are to be returned. Zero is a valid value. The
             maximum number allowed is 256.
        }
      }
      BIN{ FNAME{SELCNT2}  POS{3,51,8} /*->3ColWithFDesc<-*/
        XNAME{SELECTOR COUNT}
        DLOC{MQLCSEL#}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{SELECTOR}  POS{4,,8}
        XNAME{SELECTORS ARRAY}
        DLOC{MQLCSEL@}
        ATTR{ TABS }
        HEXD{A,'Selector Array'}
        FDESC{ COL{7} FILL{.}
          TEXT{Selectors} }
        HELP{Selectors:  Input parameter   \P\P
             This is the address of the array of SelectorCount
             attribute selectors;
             each selector identifies an attribute (integer or
             character) whose value is required. \P
        }
      }
      HEX{ FNAME{INTCNT}  POS{5,,8}
        XNAME{INTEGER COUNT}
        DLOC{MQLCINT#}
        FDESC{ COL{7} FILL{.}
          TEXT{IntAttrCount} }
        HELP{Interger Attributes Count:  Input parameter \P\P
             This is the number of elements in the IntAttrs array.
             Zero is a valid value. \P
        }
      }
      BIN{ FNAME{INTCNT2}  POS{5,51,8} /*->3ColWithFDesc<-*/
        XNAME{INTEGER COUNT}
        DLOC{MQLCINT#}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{INTATTR}  POS{6,,8}
        XNAME{INTEGER ARRAY}
        DLOC{MQLCINT@}
        ATTR{ TABS }
        HEXD{A,'Integer Attr. Array'}
        FDESC{ COL{7} FILL{.}
          TEXT{IntAttrs} }
        HELP{Integer Attributes Array:  Output parameter \P\P
             This is the address of the array of IntAttrCount
             integer attribute values.
        }
      }
      HEX{ FNAME{CHARLGTH}  POS{7,,8}
        XNAME{CHAR ATTR LENGTH}
        DLOC{MQLCCHRL}
        FDESC{ COL{7} FILL{.}
          TEXT{CharAttrLength} }
        HELP{Character Attributes Length:  Input parameter \P\P
             This is the length in bytes of the CharAttrs parameter.
        }
      }
      BIN{ FNAME{CHRLGTH2}  POS{7,51,8} /*->3ColWithFDesc<-*/ 
        XNAME{CHAR ATTR LENGTH}
        DLOC{MQLCCHRL}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{CHARATTR}  POS{8,,8}
        XNAME{CHAR ATTR ARRAY}
        DLOC{MQLCCHR@}
        ATTR{ TABS }
        HEXD{A,'Char Attr. Array'}
        FDESC{ COL{7} FILL{.}
          TEXT{CharAttrs} }
        HELP{Character Attributes Array:  Output parameter \P\P
             This is the adddress of the buffer in which the
             character attributes are returned, concatenated
             together. The length of the buffer is given by the
             CharAttrLength parameter.
        }
      }
      BIN{ FNAME{COMPCODE} POS{9,,8}
        XNAME{COMP CODE}
        DLOC{MQLCMQCC}
        FDESC{ COL{7} FILL{.}
          TEXT{CompCode} }
        HELP{Completion Code:  Output parameter \P\P
             This is the completion code for the MQ API call. \P
        }
      }
      CHOICE{ FNAME{MQCCEQU} POS{9,40,20}
      XNAME{MQCCEQU}
      DLOC{MQLCMQCC}
       LISTV{
            VALUE{X'00','MQCC_OK'}
            VALUE{X'01','MQCC_WARNING'}
            VALUE{X'02','MQCC_FAILED'}
       }
      }
      CHAR{ FNAME{REASCODE} POS{10,,4}
        XNAME{REASON CODE}
        DLOC{MQLCRC}
        FDESC{ COL{7} FILL{.}
          TEXT{Reason} }
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQDI @FF005}
           DESC{Display Reason Code}
           }
        HELP{Reason Code:  Output parameter \P\P
             This is the reason code that qualifies the
             completion code for the MQ API call.
        }
      }
     CHOICE{ FNAME{RCEQU1} POS{10,40,30}
     XNAME{REASON EQU}
     DLOC{MQLCRC}
      LISTV{
           VALUE{'0000','MQRC_NONE'}
           VALUE{'2001','MQRC_ALIAS_BASE_Q_TYPE_ERROR'}
           VALUE{'2002','MQRC_ALREADY_CONNECTED'}
           VALUE{'2003','MQRC_BACKED_OUT'}
           VALUE{'2004','MQRC_BUFFER_ERROR'}
           VALUE{'2005','MQRC_BUFFER_LENGTH_ERROR'}
           VALUE{'2006','MQRC_CHAR_ATTR_LENGTH_ERROR'}
           VALUE{'2007','MQRC_CHAR_ATTRS_ERROR'}
           VALUE{'2008','MQRC_CHAR_ATTRS_TOO_SHORT'}
           VALUE{'2009','MQRC_CONNECTION_BROKEN'}
           VALUE{'2010','MQRC_DATA_LENGTH_ERROR'}
           VALUE{'2011','MQRC_DYNAMIC_Q_NAME_ERROR'}
           VALUE{'2012','MQRC_ENVIRONMENT_ERROR'}
           VALUE{'2013','MQRC_EXPIRY_ERROR'}
           VALUE{'2014','MQRC_FEEDBACK_ERROR'}
           VALUE{'2016','MQRC_GET_INHIBITED'}
           VALUE{'2017','MQRC_HANDLE_NOT_AVAILABLE'}
           VALUE{'2018','MQRC_HCONN_ERROR'}
           VALUE{'2019','MQRC_HOBJ_ERROR'}
           VALUE{'2020','MQRC_INHIBIT_VALUE_ERROR'}
           VALUE{'2021','MQRC_INT_ATTR_COUNT_ERROR'}
           VALUE{'2022','MQRC_INT_ATTR_COUNT_TOO_SMALL'}
           VALUE{'2023','MQRC_INT_ATTRS_ARRAY_ERROR'}
           VALUE{'2024','MQRC_SYNCPOINT_LIMIT_REACHED'}
           VALUE{'2025','MQRC_MAX_CONNS_LIMIT_REACHED'}
           VALUE{'2026','MQRC_MD_ERROR'}
           VALUE{'2027','MQRC_MISSING_REPLY_TO_Q'}
           VALUE{'2029','MQRC_MSG_TYPE_ERROR'}
           VALUE{'2030','MQRC_MSG_TOO_BIG_FOR_Q'}
           VALUE{'2031','MQRC_MSG_TOO_BIG_FOR_Q_MGR'}
           VALUE{'2033','MQRC_NO_MSG_AVAILABLE'}
           VALUE{'2034','MQRC_NO_MSG_UNDER_CURSOR'}
           VALUE{'2035','MQRC_NOT_AUTHORIZED'}
           VALUE{'2036','MQRC_NOT_OPEN_FOR_BROWSE'}
           VALUE{'2037','MQRC_NOT_OPEN_FOR_INPUT'}
           VALUE{'2038','MQRC_NOT_OPEN_FOR_INQUIRE'}
           VALUE{'2039','MQRC_NOT_OPEN_FOR_OUTPUT'}
           VALUE{'2040','MQRC_NOT_OPEN_FOR_SET'}
           VALUE{'2041','MQRC_OBJECT_CHANGED'}
           VALUE{'2042','MQRC_OBJECT_IN_USE'}
           VALUE{'2043','MQRC_OBJECT_TYPE_ERROR'}
           VALUE{'2044','MQRC_OD_ERROR'}
           VALUE{'2045','MQRC_OPTION_NOT_VALID_FOR_TYPE'}
           VALUE{'2046','MQRC_OPTIONS_ERROR'}
           VALUE{'2047','MQRC_PERSISTENCE_ERROR'}
           VALUE{'2048','MQRC_PERSISTENT_NOT_ALLOWED'}
           VALUE{'2049','MQRC_PRIORITY_EXCEEDS_MAXIMUM'}
           VALUE{'2050','MQRC_PRIORITY_ERROR'}
           VALUE{'2051','MQRC_PUT_INHIBITED'}
           VALUE{'2052','MQRC_Q_DELETED'}
           VALUE{'2053','MQRC_Q_FULL'}
           VALUE{'2055','MQRC_Q_NOT_EMPTY'}
           VALUE{'2056','MQRC_Q_SPACE_NOT_AVAILABLE'}
           VALUE{'2057','MQRC_Q_TYPE_ERROR'}
           VALUE{'2058','MQRC_Q_MGR_NAME_ERROR'}
           VALUE{'2059','MQRC_Q_MGR_NOT_AVAILABLE'}
           VALUE{'2061','MQRC_REPORT_OPTIONS_ERROR'}
           VALUE{'2062','MQRC_SECOND_MARK_NOT_ALLOWED'}
           VALUE{'2063','MQRC_SECURITY_ERROR'}
           VALUE{'2065','MQRC_SELECTOR_COUNT_ERROR'}
           VALUE{'2066','MQRC_SELECTOR_LIMIT_EXCEEDED'}
           VALUE{'2067','MQRC_SELECTOR_ERROR'}
           VALUE{'2068','MQRC_SELECTOR_NOT_FOR_TYPE'}
           VALUE{'2069','MQRC_SIGNAL_OUTSTANDING'}
           VALUE{'2070','MQRC_SIGNAL_REQUEST_ACCEPTED'}
           VALUE{'2071','MQRC_STORAGE_NOT_AVAILABLE'}
           VALUE{'2072','MQRC_SYNCPOINT_NOT_AVAILABLE'}
           VALUE{'2075','MQRC_TRIGGER_CONTROL_ERROR'}
           VALUE{'2076','MQRC_TRIGGER_DEPTH_ERROR'}
           VALUE{'2077','MQRC_TRIGGER_MSG_PRIORITY_ERR'}
           VALUE{'2078','MQRC_TRIGGER_TYPE_ERROR'}
           VALUE{'2079','MQRC_TRUNCATED_MSG_ACCEPTED'}
           VALUE{'2080','MQRC_TRUNCATED_MSG_FAILED'}
           VALUE{'2082','MQRC_UNKNOWN_ALIAS_BASE_Q'}
      }
      }
    IF { COND{CHKCODE} THEN {
       CHOICE{ FNAME{RCEQU2}  POS{10,40,30}
       XNAME{REASON EQU}
       DLOC{MQLCRC}
         LISTV{
           VALUE{'2085','MQRC_UNKNOWN_OBJECT_NAME'}
           VALUE{'2086','MQRC_UNKNOWN_OBJECT_Q_MGR'}
           VALUE{'2087','MQRC_UNKNOWN_REMOTE_Q_MGR'}
           VALUE{'2090','MQRC_WAIT_INTERVAL_ERROR'}
           VALUE{'2091','MQRC_XMIT_Q_TYPE_ERROR'}
           VALUE{'2092','MQRC_XMIT_Q_USAGE_ERROR'}
           VALUE{'2093','MQRC_NOT_OPEN_FOR_PASS_ALL'}
           VALUE{'2094','MQRC_NOT_OPEN_FOR_PASS_IDENT'}
           VALUE{'2095','MQRC_NOT_OPEN_FOR_SET_ALL'}
           VALUE{'2096','MQRC_NOT_OPEN_FOR_SET_IDENT'}
           VALUE{'2097','MQRC_CONTEXT_HANDLE_ERROR'}
           VALUE{'2098','MQRC_CONTEXT_NOT_AVAILABLE'}
           VALUE{'2099','MQRC_SIGNAL1_ERROR'}
           VALUE{'2100','MQRC_OBJECT_ALREADY_EXISTS'}
           VALUE{'2101','MQRC_OBJECT_DAMAGED'}
           VALUE{'2102','MQRC_RESOURCE_PROBLEM'}
           VALUE{'2103','MQRC_ANOTHER_Q_MGR_CONNECTED'}
           VALUE{'2104','MQRC_UNKNOWN_REPORT_OPTION'}
           VALUE{'2105','MQRC_STORAGE_CLASS_ERROR'}
           VALUE{'2106','MQRC_COD_NOT_VALID_FOR_XCF_Q'}
           VALUE{'2107','MQRC_XWAIT_CANCELED'}
           VALUE{'2108','MQRC_XWAIT_ERROR'}
           VALUE{'2109','MQRC_SUPPRESSED_BY_EXIT'}
           VALUE{'2110','MQRC_FORMAT_ERROR'}
           VALUE{'2111','MQRC_SOURCE_CCSID_ERROR'}
           VALUE{'2112','MQRC_SOURCE_INTEGER_ENC_ERROR'}
           VALUE{'2113','MQRC_SOURCE_DECIMAL_ENC_ERROR'}
           VALUE{'2114','MQRC_SOURCE_FLOAT_ENC_ERROR'}
           VALUE{'2115','MQRC_TARGET_CCSID_ERROR'}
           VALUE{'2116','MQRC_TARGET_INTEGER_ENC_ERROR'}
           VALUE{'2117','MQRC_TARGET_DECIMAL_ENC_ERROR'}
           VALUE{'2118','MQRC_TARGET_FLOAT_ENC_ERROR'}
           VALUE{'2119','MQRC_NOT_CONVERTED'}
           VALUE{'2120','MQRC_CONVERTED_MSG_TOO_BIG'}
           VALUE{'2120','MQRC_TRUNCATED'}
           VALUE{'2121','MQRC_NO_EXTERNAL_PARTICIPANTS'}
           VALUE{'2122','MQRC_PARTICIPANT_NOT_AVAILABLE'}
           VALUE{'2123','MQRC_OUTCOME_MIXED'}
           VALUE{'2124','MQRC_OUTCOME_PENDING'}
           VALUE{'2125','MQRC_BRIDGE_STARTED'}
           VALUE{'2126','MQRC_BRIDGE_STOPPED'}
           VALUE{'2127','MQRC_ADAPTER_STORAGE_SHORTAGE'}
           VALUE{'2128','MQRC_UOW_IN_PROGRESS'}
           VALUE{'2129','MQRC_ADAPTER_CONN_LOAD_ERROR'}
           VALUE{'2130','MQRC_ADAPTER_SERV_LOAD_ERROR'}
           VALUE{'2131','MQRC_ADAPTER_DEFS_ERROR'}
           VALUE{'2132','MQRC_ADAPTER_DEFS_LOAD_ERROR'}
           VALUE{'2133','MQRC_ADAPTER_CONV_LOAD_ERROR'}
           VALUE{'2134','MQRC_BO_ERROR'}
           VALUE{'2135','MQRC_DH_ERROR'}
           VALUE{'2136','MQRC_MULTIPLE_REASONS'}
           VALUE{'2137','MQRC_OPEN_FAILED'}
           VALUE{'2138','MQRC_ADAPTER_DISC_LOAD_ERROR'}
           VALUE{'2139','MQRC_CNO_ERROR'}
           VALUE{'2140','MQRC_CICS_WAIT_FAILED'}
           VALUE{'2141','MQRC_DLH_ERROR'}
           VALUE{'2142','MQRC_HEADER_ERROR'}
           VALUE{'2143','MQRC_SOURCE_LENGTH_ERROR'}
           VALUE{'2144','MQRC_TARGET_LENGTH_ERROR'}
           VALUE{'2145','MQRC_SOURCE_BUFFER_ERROR'}
           VALUE{'2146','MQRC_TARGET_BUFFER_ERROR'}
           VALUE{'2148','MQRC_IIH_ERROR'}
           VALUE{'2149','MQRC_PCF_ERROR'}
           VALUE{'2150','MQRC_DBCS_ERROR'}
           VALUE{'2152','MQRC_OBJECT_NAME_ERROR'}
           VALUE{'2153','MQRC_OBJECT_Q_MGR_NAME_ERROR'}
           VALUE{'2154','MQRC_RECS_PRESENT_ERROR'}
           VALUE{'2155','MQRC_OBJECT_RECORDS_ERROR'}
           VALUE{'2156','MQRC_RESPONSE_RECORDS_ERROR'}
           VALUE{'2157','MQRC_ASID_MISMATCH'}
           VALUE{'2158','MQRC_PMO_RECORD_FLAGS_ERROR'}
           VALUE{'2159','MQRC_PUT_MSG_RECORDS_ERROR'}
           VALUE{'2160','MQRC_CONN_ID_IN_USE'}
           VALUE{'2161','MQRC_Q_MGR_QUIESCING'}
           VALUE{'2162','MQRC_Q_MGR_STOPPING'}
           VALUE{'2163','MQRC_DUPLICATE_RECOV_COORD'}
           VALUE{'2173','MQRC_PMO_ERROR'}
           VALUE{'2182','MQRC_API_EXIT_NOT_FOUND'}
           VALUE{'2183','MQRC_API_EXIT_LOAD_ERROR'}
           VALUE{'2184','MQRC_REMOTE_Q_NAME_ERROR'}
           VALUE{'2185','MQRC_INCONSISTENT_PERSISTENCE'}
           VALUE{'2186','MQRC_GMO_ERROR'}
           VALUE{'2187','MQRC_CICS_BRIDGE_RESTRICTION'}
           VALUE{'2188','MQRC_STOPPED_BY_CLUSTER_EXIT'}
           VALUE{'2189','MQRC_CLUSTER_RESOLUTION_ERROR'}
           VALUE{'2190','MQRC_CONVERTED_STRING_TOO_BIG'}
           VALUE{'2191','MQRC_TMC_ERROR'}
           VALUE{'2192','MQRC_PAGESET_FULL'}
           VALUE{'2193','MQRC_PAGESET_ERROR'}
           VALUE{'2194','MQRC_NAME_NOT_VALID_FOR_TYPE'}
           VALUE{'2195','MQRC_UNEXPECTED_ERROR'}
           VALUE{'2196','MQRC_UNKNOWN_XMIT_Q'}
           VALUE{'2197','MQRC_UNKNOWN_DEF_XMIT_Q'}
           VALUE{'2198','MQRC_DEF_XMIT_Q_TYPE_ERROR'}
           VALUE{'2199','MQRC_DEF_XMIT_Q_USAGE_ERROR'}
           VALUE{'2201','MQRC_NAME_IN_USE'}
           VALUE{'2202','MQRC_CONNECTION_QUIESCING'}
           VALUE{'2203','MQRC_CONNECTION_STOPPING'}
           VALUE{'2204','MQRC_ADAPTER_NOT_AVAILABLE'}
           VALUE{'2206','MQRC_MSG_ID_ERROR'}
           VALUE{'2207','MQRC_CORREL_ID_ERROR'}
           VALUE{'2208','MQRC_FILE_SYSTEM_ERROR'}
           VALUE{'2209','MQRC_NO_MSG_LOCKED'}
           VALUE{'2216','MQRC_FILE_NOT_AUDITED'}
           VALUE{'2217','MQRC_CONNECTION_NOT_AUTHORIZED'}
           VALUE{'2218','MQRC_MSG_TOO_BIG_FOR_CHANNEL'}
           VALUE{'2219','MQRC_CALL_IN_PROGRESS'}
           VALUE{'2220','MQRC_RMH_ERROR'}
           VALUE{'2222','MQRC_Q_MGR_ACTIVE'}
           VALUE{'2223','MQRC_Q_MGR_NOT_ACTIVE'}
           VALUE{'2224','MQRC_Q_DEPTH_HIGH'}
           VALUE{'2225','MQRC_Q_DEPTH_LOW'}
           VALUE{'2226','MQRC_Q_SERVICE_INTERVAL_HIGH'}
           VALUE{'2227','MQRC_Q_SERVICE_INTERVAL_OK'}
           VALUE{'2232','MQRC_UNIT_OF_WORK_NOT_STARTED'}
           VALUE{'2233','MQRC_CHANNEL_AUTO_DEF_OK'}
           VALUE{'2234','MQRC_CHANNEL_AUTO_DEF_ERROR'}
           VALUE{'2235','MQRC_CFH_ERROR'}
           VALUE{'2236','MQRC_CFIL_ERROR'}
           VALUE{'2237','MQRC_CFIN_ERROR'}
           VALUE{'2238','MQRC_CFSL_ERROR'}
           VALUE{'2239','MQRC_CFST_ERROR'}
           VALUE{'2241','MQRC_INCOMPLETE_GROUP'}
           VALUE{'2242','MQRC_INCOMPLETE_MSG'}
           VALUE{'2243','MQRC_INCONSISTENT_CCSIDS'}
           VALUE{'2244','MQRC_INCONSISTENT_ENCODINGS'}
           VALUE{'2245','MQRC_INCONSISTENT_UOW'}
           VALUE{'2246','MQRC_INVALID_MSG_UNDER_CURSOR'}
           VALUE{'2247','MQRC_MATCH_OPTIONS_ERROR'}
           VALUE{'2248','MQRC_MDE_ERROR'}
           VALUE{'2249','MQRC_MSG_FLAGS_ERROR'}
           VALUE{'2250','MQRC_MSG_SEQ_NUMBER_ERROR'}
           VALUE{'2251','MQRC_OFFSET_ERROR'}
           VALUE{'2252','MQRC_ORIGINAL_LENGTH_ERROR'}
           VALUE{'2253','MQRC_SEGMENT_LENGTH_ZERO'}
           VALUE{'2255','MQRC_UOW_NOT_AVAILABLE'}
           VALUE{'2256','MQRC_WRONG_GMO_VERSION'}
           VALUE{'2257','MQRC_WRONG_MD_VERSION'}
           VALUE{'2258','MQRC_GROUP_ID_ERROR'}
           VALUE{'2259','MQRC_INCONSISTENT_BROWSE'}
           VALUE{'2260','MQRC_XQH_ERROR'}
           VALUE{'2261','MQRC_SRC_ENV_ERROR'}
           VALUE{'2262','MQRC_SRC_NAME_ERROR'}
           VALUE{'2263','MQRC_DEST_ENV_ERROR'}
           VALUE{'2264','MQRC_DEST_NAME_ERROR'}
           VALUE{'2265','MQRC_TM_ERROR'}
           VALUE{'2266','MQRC_CLUSTER_EXIT_ERROR'}
           VALUE{'2267','MQRC_CLUSTER_EXIT_LOAD_ERROR'}
           VALUE{'2268','MQRC_CLUSTER_PUT_INHIBITED'}
           VALUE{'2269','MQRC_CLUSTER_RESOURCE_ERROR'}
           VALUE{'2270','MQRC_NO_DESTINATIONS_AVAILABLE'}
           VALUE{'2273','MQRC_CONNECTION_ERROR'}
           VALUE{'2274','MQRC_OPTION_ENVIRONMENT_ERROR'}
           VALUE{'2277','MQRC_CD_ERROR'}
           VALUE{'2278','MQRC_CLIENT_CONN_ERROR'}
           VALUE{'2279','MQRC_CHANNEL_STOPPED_BY_USER'}
           VALUE{'2280','MQRC_HCONFIG_ERROR'}
           VALUE{'2281','MQRC_FUNCTION_ERROR'}
           VALUE{'2282','MQRC_CHANNEL_STARTED'}
           VALUE{'2283','MQRC_CHANNEL_STOPPED'}
           VALUE{'2284','MQRC_CHANNEL_CONV_ERROR'}
           VALUE{'2285','MQRC_SERVICE_NOT_AVAILABLE'}
           VALUE{'2286','MQRC_INITIALIZATION_FAILED'}
           VALUE{'2287','MQRC_TERMINATION_FAILED'}
           VALUE{'2288','MQRC_UNKNOWN_Q_NAME'}
           VALUE{'2289','MQRC_SERVICE_ERROR'}
           VALUE{'2290','MQRC_Q_ALREADY_EXISTS'}
           VALUE{'2291','MQRC_USER_ID_NOT_AVAILABLE'}
           VALUE{'2292','MQRC_UNKNOWN_ENTITY'}
           VALUE{'2293','MQRC_UNKNOWN_AUTH_ENTITY'}
           VALUE{'2294','MQRC_UNKNOWN_REF_OBJECT'}
           VALUE{'2295','MQRC_CHANNEL_ACTIVATED'}
           VALUE{'2296','MQRC_CHANNEL_NOT_ACTIVATED'}
           VALUE{'2297','MQRC_UOW_CANCELED'}
           VALUE{'2299','MQRC_SELECTOR_TYPE_ERROR'}
           VALUE{'2300','MQRC_COMMAND_TYPE_ERROR'}
           VALUE{'2301','MQRC_MULTIPLE_INSTANCE_ERROR'}
           VALUE{'2302','MQRC_SYSTEM_ITEM_NOT_ALTERABLE'}
           VALUE{'2303','MQRC_BAG_CONVERSION_ERROR'}
           VALUE{'2304','MQRC_SELECTOR_OUT_OF_RANGE'}
           VALUE{'2305','MQRC_SELECTOR_NOT_UNIQUE'}
           VALUE{'2306','MQRC_INDEX_NOT_PRESENT'}
           VALUE{'2307','MQRC_STRING_ERROR'}
           VALUE{'2308','MQRC_ENCODING_NOT_SUPPORTED'}
           VALUE{'2309','MQRC_SELECTOR_NOT_PRESENT'}
           VALUE{'2310','MQRC_OUT_SELECTOR_ERROR'}
           VALUE{'2311','MQRC_STRING_TRUNCATED'}
           VALUE{'2312','MQRC_SELECTOR_WRONG_TYPE'}
           VALUE{'2313','MQRC_INCONSISTENT_ITEM_TYPE'}
           VALUE{'2314','MQRC_INDEX_ERROR'}
           VALUE{'2315','MQRC_SYSTEM_BAG_NOT_ALTERABLE'}
           VALUE{'2316','MQRC_ITEM_COUNT_ERROR'}
           VALUE{'2317','MQRC_FORMAT_NOT_SUPPORTED'}
           VALUE{'2318','MQRC_SELECTOR_NOT_SUPPORTED'}
           VALUE{'2319','MQRC_ITEM_VALUE_ERROR'}
           VALUE{'2320','MQRC_HBAG_ERROR'}
           VALUE{'2321','MQRC_PARAMETER_MISSING'}
           VALUE{'2322','MQRC_CMD_SERVER_NOT_AVAILABLE'}
           VALUE{'2323','MQRC_STRING_LENGTH_ERROR'}
           VALUE{'2324','MQRC_INQUIRY_COMMAND_ERROR'}
           VALUE{'2325','MQRC_NESTED_BAG_NOT_SUPPORTED'}
           VALUE{'2326','MQRC_BAG_WRONG_TYPE'}
           VALUE{'2327','MQRC_ITEM_TYPE_ERROR'}
           VALUE{'2328','MQRC_SYSTEM_BAG_NOT_DELETABLE'}
           VALUE{'2329','MQRC_SYSTEM_ITEM_NOT_DELETABLE'}
           VALUE{'2330','MQRC_CODED_CHAR_SET_ID_ERROR'}
           VALUE{'2331','MQRC_MSG_TOKEN_ERROR'}
           VALUE{'2332','MQRC_MISSING_WIH'}
           VALUE{'2333','MQRC_WIH_ERROR'}
        }
       }
       }}
    }    /* end-group */
;
    GROUP{ POS{13,1,79}
      HDR{YES} FNAME{EXCALINF}
        TEXT{                        Expanded Call Information }
    }
;
    GROUP{ POS{15,1,79}
        DATACOL{25}
      CHAR{ FNAME{QMGRNAME} POS{1,,4}
        XNAME{QMGR NAME}
        DLOC{MQLCQMGR}
        FDESC{ COL{1} FILL{.}
          TEXT{QMgr Name} }
        HELP{This is the name of the queue manager that CICS was
             connected to at the time of the dump. \P
        }
      }
      CHAR{ FNAME{QNAME} POS{2,,48}
        XNAME{QUEUE NAME}
        DLOC{MQLCQNME}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQCB @FF003 @FF004 }
              DESC{Displays the queue defintions.  } }
        }}
        FDESC{ COL{1} FILL{.}
          TEXT{Queue Used in Call} }
        HELP{This is the name of the object that was used for the
             MQINQ call. \P
        }
      }
    IF {COND{OLDFMT} THEN { } ELSE {
      IF { COND{GOTMHND} THEN {
         HEX{ FNAME{OPENOPT}  POS{3,,8}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           ATTR{TABS}
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQM2 OPN @FF006 }
              DESC{Displays the OPEN options} }
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
      } ELSE {
         CHAR{ FNAME{OPENOPT}  POS{3,,4}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the object. \P
           }
         }
        }
      } } }
   }  /* end-group */
;
  }                                              /* end-fixed */        03130000
  HELP{The MQINQ call returns an array of integers and a set of         03140000
       character strings containing the attributes of an object. \P\P
       This screen displays the parameters that were used in the
       MQINQ call. \P\P
  }                                                                     03160000
}                                                /* end-screen */       03170000
:END                                                                    03180000
*
*
:SCREEN{ NAME{MQLSET} TITLE{Last WebSphere MQ Call Info}                00600000
 TEMPLATE{KAZHDTMP.MQLSET}                     /* @03 */
  ORG{KAZ#MQLC}                                                         00610000
  FIXED{                                                                00620000
;
    DP{ FNAME{F003}     DLOC{MQLCQTYP} }
    DP{ FNAME{F004}     DLOC{MQLCHOBJ} }
    DP{ FNAME{F005}     DLOC{MQLCRC} }
    DP{ FNAME{F006}     DLOC{MQLCOPEN} }      /* PROG OPEN OPTIONS */
    DP{ FNAME{F009}     DLOC{MQLCQREL} }      /* MQ RELEASE    @02 */
;
   COND{ FNAME{CHKCODE} DLOC{MQLCRC}
         COMPOP{CLC,'2085',NL} }
   COND{ FNAME{GOTMHND} DLOC{MQLCMHND}
         COMPOP{CLC,'Y',E} }
   COND{ FNAME{GOODCC} DLOC{MQLCMQCC}
         COMPOP{CB,X'00000002',L} }
   COND{FNAME{OLDFMT} DLOC{MQLC@FMT}
         COMPOP{CLC,'1',E} }
;
    LITERAL{ FNAME{CALMQSET} POS{1,1,40} /*->fixedPro<-*/ /* @03 */
        TEXT {CALL 'MQSET' USING}  }
    GROUP{ POS{2,1,79}
        DATACOL{25}
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HCONN}  POS{1,,8}
        XNAME{HCONN}
        DLOC{MQLCHCON}
        FDESC{ COL{7} FILL{.}
          TEXT{Hconn} }
        HELP{Connection Handle:  Input parameter \P\P
             This parameter represents the connection to the queue
             manager. The value was return on a previous MQCONN call.
             \P\P
             On OS/390 for CICS applications, the MQCONN call can be
             omitted and the value of MQHC_DEF_HCONN can be specified
             for this parameter. \P
        }
      } } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HOBJECT}  POS{2,,8}
        XNAME{HOBJECT}
        DLOC{MQLCHOBJ}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQHI @FF004 C @FF009}                   /* @02 */
              DESC{Display Handle Information} }
        }}
        FDESC{ COL{7} FILL{.}
          TEXT{Hobj} }
        HELP{Object Handle:  Input parameter \P\P
             This handle represents the queue whose attributes
             are to be set. \P
             The handle must have been returned by a previous MQOPEN
             call that specified the MQOO_SET option. \P
        }
      } } }
      HEX{ FNAME{SELCNT}  POS{3,,8}
        XNAME{SELECTOR COUNT}
        DLOC{MQLCSEL#}
        FDESC{ COL{7} FILL{.}
          TEXT{SelectorCount} }
        HELP{Selector Count:  Input parameter \P\P
             This is the count of selectors that are supplied in the
             Selectors array. It is the number of attributes
             that are to be set. Zero is a valid value. The
             maximum number allowed is 256.
        }
      }
      BIN{ FNAME{SELCNT2}  POS{3,51,8} /*->3ColWithFDesc<-*/
        XNAME{SELECTOR COUNT}
        DLOC{MQLCSEL#}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{SELECTOR}  POS{4,,8}
        XNAME{SELECTORS ARRAY}
        DLOC{MQLCSEL@}
        ATTR{ TABS }
        HEXD{A,'Selector Array'}
        FDESC{ COL{7} FILL{.}
          TEXT{Selectors} }
        HELP{Selectors:  Input parameter   \P\P
             This is the address of the array of SelectorCount
             attribute selectors;
             each selector identifies an attribute (integer or
             character) whose value is to be set. \P
        }
      }
      HEX{ FNAME{INTCNT}  POS{5,,8}
        XNAME{INTEGER COUNT}
        DLOC{MQLCINT#}
        FDESC{ COL{7} FILL{.}
          TEXT{IntAttrCount} }
        HELP{Interger Attributes Count:  Input parameter \P\P
             This is the number of elements in the IntAttrs array,
             and must be at least the number of MQIA_* selectors in
             the Selectors parameter. Zero is a valid value
             if there are none.
        }
      }
      BIN{ FNAME{INTCNT2}  POS{5,51,8} /*->3ColWithFDesc<-*/
        XNAME{INTEGER COUNT}
        DLOC{MQLCINT#}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{INTATTR}  POS{6,,8}
        XNAME{INTEGER ARRAY}
        DLOC{MQLCINT@}
        ATTR{ TABS }
        HEXD{A,'Integer Attr. Array'}
        FDESC{ COL{7} FILL{.}
          TEXT{IntAttrs} }
        HELP{Integer Attributes Array:  Input parameter \P\P
             This is the address of the array of IntAttrCount
             integer attribute values.
        }
      }
      HEX{ FNAME{CHARLGTH}  POS{7,,8}
        XNAME{CHAR ATTR LENGTH}
        DLOC{MQLCCHRL}
        FDESC{ COL{7} FILL{.}
          TEXT{CharAttrLength} }
        HELP{Character Attributes Length:  Input parameter \P\P
             This is the length in bytes of the CharAttrs parameter.
        }
      }
      BIN{ FNAME{CHRLGTH2}  POS{7,51,8} /*->3ColWithFDesc<-*/
        XNAME{CHAR ATTR LENGTH}
        DLOC{MQLCCHRL}
        FDESC{ COL{40} FILL{.}
          TEXT{Decimal} }
      }
      HEX{ FNAME{CHARATTR}  POS{8,,8}
        XNAME{CHAR ATTR ARRAY}
        DLOC{MQLCCHR@}
        ATTR{ TABS }
        HEXD{A,'Char Attr. Array'}
        FDESC{ COL{7} FILL{.}
          TEXT{CharAttrs} }
        HELP{Character Attributes Array:  Input parameter \P\P
             This is the adddress of the buffer containing the
             character attribute values, concatenated
             together. The length of the buffer is given by the
             CharAttrLength parameter.
        }
      }
      BIN{ FNAME{COMPCODE} POS{9,,8}
        XNAME{COMP CODE}
        DLOC{MQLCMQCC}
        FDESC{ COL{7} FILL{.}
          TEXT{CompCode} }
        HELP{Completion Code:  Output parameter \P\P
             This is the completion code for the MQ API call. \P
        }
      }
      CHOICE{ FNAME{MQCCEQU} POS{9,40,20}
      XNAME{MQCCEQU}
      DLOC{MQLCMQCC}
       LISTV{
            VALUE{X'00','MQCC_OK'}
            VALUE{X'01','MQCC_WARNING'}
            VALUE{X'02','MQCC_FAILED'}
       }
      }
      CHAR{ FNAME{REASCODE} POS{10,,4}
        XNAME{REASON CODE}
        DLOC{MQLCRC}
        FDESC{ COL{7} FILL{.}
          TEXT{Reason} }
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQDI @FF005}
           DESC{Display Reason Code}
           }
        HELP{Reason Code:  Output parameter \P\P
             This is the reason code that qualifies the
             completion code for the MQ API call.
        }
      }
     CHOICE{ FNAME{RCEQU1} POS{10,40,30}
     XNAME{REASON EQU}
     DLOC{MQLCRC}
      LISTV{
           VALUE{'0000','MQRC_NONE'}
           VALUE{'2001','MQRC_ALIAS_BASE_Q_TYPE_ERROR'}
           VALUE{'2002','MQRC_ALREADY_CONNECTED'}
           VALUE{'2003','MQRC_BACKED_OUT'}
           VALUE{'2004','MQRC_BUFFER_ERROR'}
           VALUE{'2005','MQRC_BUFFER_LENGTH_ERROR'}
           VALUE{'2006','MQRC_CHAR_ATTR_LENGTH_ERROR'}
           VALUE{'2007','MQRC_CHAR_ATTRS_ERROR'}
           VALUE{'2008','MQRC_CHAR_ATTRS_TOO_SHORT'}
           VALUE{'2009','MQRC_CONNECTION_BROKEN'}
           VALUE{'2010','MQRC_DATA_LENGTH_ERROR'}
           VALUE{'2011','MQRC_DYNAMIC_Q_NAME_ERROR'}
           VALUE{'2012','MQRC_ENVIRONMENT_ERROR'}
           VALUE{'2013','MQRC_EXPIRY_ERROR'}
           VALUE{'2014','MQRC_FEEDBACK_ERROR'}
           VALUE{'2016','MQRC_GET_INHIBITED'}
           VALUE{'2017','MQRC_HANDLE_NOT_AVAILABLE'}
           VALUE{'2018','MQRC_HCONN_ERROR'}
           VALUE{'2019','MQRC_HOBJ_ERROR'}
           VALUE{'2020','MQRC_INHIBIT_VALUE_ERROR'}
           VALUE{'2021','MQRC_INT_ATTR_COUNT_ERROR'}
           VALUE{'2022','MQRC_INT_ATTR_COUNT_TOO_SMALL'}
           VALUE{'2023','MQRC_INT_ATTRS_ARRAY_ERROR'}
           VALUE{'2024','MQRC_SYNCPOINT_LIMIT_REACHED'}
           VALUE{'2025','MQRC_MAX_CONNS_LIMIT_REACHED'}
           VALUE{'2026','MQRC_MD_ERROR'}
           VALUE{'2027','MQRC_MISSING_REPLY_TO_Q'}
           VALUE{'2029','MQRC_MSG_TYPE_ERROR'}
           VALUE{'2030','MQRC_MSG_TOO_BIG_FOR_Q'}
           VALUE{'2031','MQRC_MSG_TOO_BIG_FOR_Q_MGR'}
           VALUE{'2033','MQRC_NO_MSG_AVAILABLE'}
           VALUE{'2034','MQRC_NO_MSG_UNDER_CURSOR'}
           VALUE{'2035','MQRC_NOT_AUTHORIZED'}
           VALUE{'2036','MQRC_NOT_OPEN_FOR_BROWSE'}
           VALUE{'2037','MQRC_NOT_OPEN_FOR_INPUT'}
           VALUE{'2038','MQRC_NOT_OPEN_FOR_INQUIRE'}
           VALUE{'2039','MQRC_NOT_OPEN_FOR_OUTPUT'}
           VALUE{'2040','MQRC_NOT_OPEN_FOR_SET'}
           VALUE{'2041','MQRC_OBJECT_CHANGED'}
           VALUE{'2042','MQRC_OBJECT_IN_USE'}
           VALUE{'2043','MQRC_OBJECT_TYPE_ERROR'}
           VALUE{'2044','MQRC_OD_ERROR'}
           VALUE{'2045','MQRC_OPTION_NOT_VALID_FOR_TYPE'}
           VALUE{'2046','MQRC_OPTIONS_ERROR'}
           VALUE{'2047','MQRC_PERSISTENCE_ERROR'}
           VALUE{'2048','MQRC_PERSISTENT_NOT_ALLOWED'}
           VALUE{'2049','MQRC_PRIORITY_EXCEEDS_MAXIMUM'}
           VALUE{'2050','MQRC_PRIORITY_ERROR'}
           VALUE{'2051','MQRC_PUT_INHIBITED'}
           VALUE{'2052','MQRC_Q_DELETED'}
           VALUE{'2053','MQRC_Q_FULL'}
           VALUE{'2055','MQRC_Q_NOT_EMPTY'}
           VALUE{'2056','MQRC_Q_SPACE_NOT_AVAILABLE'}
           VALUE{'2057','MQRC_Q_TYPE_ERROR'}
           VALUE{'2058','MQRC_Q_MGR_NAME_ERROR'}
           VALUE{'2059','MQRC_Q_MGR_NOT_AVAILABLE'}
           VALUE{'2061','MQRC_REPORT_OPTIONS_ERROR'}
           VALUE{'2062','MQRC_SECOND_MARK_NOT_ALLOWED'}
           VALUE{'2063','MQRC_SECURITY_ERROR'}
           VALUE{'2065','MQRC_SELECTOR_COUNT_ERROR'}
           VALUE{'2066','MQRC_SELECTOR_LIMIT_EXCEEDED'}
           VALUE{'2067','MQRC_SELECTOR_ERROR'}
           VALUE{'2068','MQRC_SELECTOR_NOT_FOR_TYPE'}
           VALUE{'2069','MQRC_SIGNAL_OUTSTANDING'}
           VALUE{'2070','MQRC_SIGNAL_REQUEST_ACCEPTED'}
           VALUE{'2071','MQRC_STORAGE_NOT_AVAILABLE'}
           VALUE{'2072','MQRC_SYNCPOINT_NOT_AVAILABLE'}
           VALUE{'2075','MQRC_TRIGGER_CONTROL_ERROR'}
           VALUE{'2076','MQRC_TRIGGER_DEPTH_ERROR'}
           VALUE{'2077','MQRC_TRIGGER_MSG_PRIORITY_ERR'}
           VALUE{'2078','MQRC_TRIGGER_TYPE_ERROR'}
           VALUE{'2079','MQRC_TRUNCATED_MSG_ACCEPTED'}
           VALUE{'2080','MQRC_TRUNCATED_MSG_FAILED'}
           VALUE{'2082','MQRC_UNKNOWN_ALIAS_BASE_Q'}
      }
      }
    IF { COND{CHKCODE} THEN {
       CHOICE{ FNAME{RCEQU2}  POS{10,40,30}
       XNAME{REASON EQU}
       DLOC{MQLCRC}
         LISTV{
           VALUE{'2085','MQRC_UNKNOWN_OBJECT_NAME'}
           VALUE{'2086','MQRC_UNKNOWN_OBJECT_Q_MGR'}
           VALUE{'2087','MQRC_UNKNOWN_REMOTE_Q_MGR'}
           VALUE{'2090','MQRC_WAIT_INTERVAL_ERROR'}
           VALUE{'2091','MQRC_XMIT_Q_TYPE_ERROR'}
           VALUE{'2092','MQRC_XMIT_Q_USAGE_ERROR'}
           VALUE{'2093','MQRC_NOT_OPEN_FOR_PASS_ALL'}
           VALUE{'2094','MQRC_NOT_OPEN_FOR_PASS_IDENT'}
           VALUE{'2095','MQRC_NOT_OPEN_FOR_SET_ALL'}
           VALUE{'2096','MQRC_NOT_OPEN_FOR_SET_IDENT'}
           VALUE{'2097','MQRC_CONTEXT_HANDLE_ERROR'}
           VALUE{'2098','MQRC_CONTEXT_NOT_AVAILABLE'}
           VALUE{'2099','MQRC_SIGNAL1_ERROR'}
           VALUE{'2100','MQRC_OBJECT_ALREADY_EXISTS'}
           VALUE{'2101','MQRC_OBJECT_DAMAGED'}
           VALUE{'2102','MQRC_RESOURCE_PROBLEM'}
           VALUE{'2103','MQRC_ANOTHER_Q_MGR_CONNECTED'}
           VALUE{'2104','MQRC_UNKNOWN_REPORT_OPTION'}
           VALUE{'2105','MQRC_STORAGE_CLASS_ERROR'}
           VALUE{'2106','MQRC_COD_NOT_VALID_FOR_XCF_Q'}
           VALUE{'2107','MQRC_XWAIT_CANCELED'}
           VALUE{'2108','MQRC_XWAIT_ERROR'}
           VALUE{'2109','MQRC_SUPPRESSED_BY_EXIT'}
           VALUE{'2110','MQRC_FORMAT_ERROR'}
           VALUE{'2111','MQRC_SOURCE_CCSID_ERROR'}
           VALUE{'2112','MQRC_SOURCE_INTEGER_ENC_ERROR'}
           VALUE{'2113','MQRC_SOURCE_DECIMAL_ENC_ERROR'}
           VALUE{'2114','MQRC_SOURCE_FLOAT_ENC_ERROR'}
           VALUE{'2115','MQRC_TARGET_CCSID_ERROR'}
           VALUE{'2116','MQRC_TARGET_INTEGER_ENC_ERROR'}
           VALUE{'2117','MQRC_TARGET_DECIMAL_ENC_ERROR'}
           VALUE{'2118','MQRC_TARGET_FLOAT_ENC_ERROR'}
           VALUE{'2119','MQRC_NOT_CONVERTED'}
           VALUE{'2120','MQRC_CONVERTED_MSG_TOO_BIG'}
           VALUE{'2120','MQRC_TRUNCATED'}
           VALUE{'2121','MQRC_NO_EXTERNAL_PARTICIPANTS'}
           VALUE{'2122','MQRC_PARTICIPANT_NOT_AVAILABLE'}
           VALUE{'2123','MQRC_OUTCOME_MIXED'}
           VALUE{'2124','MQRC_OUTCOME_PENDING'}
           VALUE{'2125','MQRC_BRIDGE_STARTED'}
           VALUE{'2126','MQRC_BRIDGE_STOPPED'}
           VALUE{'2127','MQRC_ADAPTER_STORAGE_SHORTAGE'}
           VALUE{'2128','MQRC_UOW_IN_PROGRESS'}
           VALUE{'2129','MQRC_ADAPTER_CONN_LOAD_ERROR'}
           VALUE{'2130','MQRC_ADAPTER_SERV_LOAD_ERROR'}
           VALUE{'2131','MQRC_ADAPTER_DEFS_ERROR'}
           VALUE{'2132','MQRC_ADAPTER_DEFS_LOAD_ERROR'}
           VALUE{'2133','MQRC_ADAPTER_CONV_LOAD_ERROR'}
           VALUE{'2134','MQRC_BO_ERROR'}
           VALUE{'2135','MQRC_DH_ERROR'}
           VALUE{'2136','MQRC_MULTIPLE_REASONS'}
           VALUE{'2137','MQRC_OPEN_FAILED'}
           VALUE{'2138','MQRC_ADAPTER_DISC_LOAD_ERROR'}
           VALUE{'2139','MQRC_CNO_ERROR'}
           VALUE{'2140','MQRC_CICS_WAIT_FAILED'}
           VALUE{'2141','MQRC_DLH_ERROR'}
           VALUE{'2142','MQRC_HEADER_ERROR'}
           VALUE{'2143','MQRC_SOURCE_LENGTH_ERROR'}
           VALUE{'2144','MQRC_TARGET_LENGTH_ERROR'}
           VALUE{'2145','MQRC_SOURCE_BUFFER_ERROR'}
           VALUE{'2146','MQRC_TARGET_BUFFER_ERROR'}
           VALUE{'2148','MQRC_IIH_ERROR'}
           VALUE{'2149','MQRC_PCF_ERROR'}
           VALUE{'2150','MQRC_DBCS_ERROR'}
           VALUE{'2152','MQRC_OBJECT_NAME_ERROR'}
           VALUE{'2153','MQRC_OBJECT_Q_MGR_NAME_ERROR'}
           VALUE{'2154','MQRC_RECS_PRESENT_ERROR'}
           VALUE{'2155','MQRC_OBJECT_RECORDS_ERROR'}
           VALUE{'2156','MQRC_RESPONSE_RECORDS_ERROR'}
           VALUE{'2157','MQRC_ASID_MISMATCH'}
           VALUE{'2158','MQRC_PMO_RECORD_FLAGS_ERROR'}
           VALUE{'2159','MQRC_PUT_MSG_RECORDS_ERROR'}
           VALUE{'2160','MQRC_CONN_ID_IN_USE'}
           VALUE{'2161','MQRC_Q_MGR_QUIESCING'}
           VALUE{'2162','MQRC_Q_MGR_STOPPING'}
           VALUE{'2163','MQRC_DUPLICATE_RECOV_COORD'}
           VALUE{'2173','MQRC_PMO_ERROR'}
           VALUE{'2182','MQRC_API_EXIT_NOT_FOUND'}
           VALUE{'2183','MQRC_API_EXIT_LOAD_ERROR'}
           VALUE{'2184','MQRC_REMOTE_Q_NAME_ERROR'}
           VALUE{'2185','MQRC_INCONSISTENT_PERSISTENCE'}
           VALUE{'2186','MQRC_GMO_ERROR'}
           VALUE{'2187','MQRC_CICS_BRIDGE_RESTRICTION'}
           VALUE{'2188','MQRC_STOPPED_BY_CLUSTER_EXIT'}
           VALUE{'2189','MQRC_CLUSTER_RESOLUTION_ERROR'}
           VALUE{'2190','MQRC_CONVERTED_STRING_TOO_BIG'}
           VALUE{'2191','MQRC_TMC_ERROR'}
           VALUE{'2192','MQRC_PAGESET_FULL'}
           VALUE{'2193','MQRC_PAGESET_ERROR'}
           VALUE{'2194','MQRC_NAME_NOT_VALID_FOR_TYPE'}
           VALUE{'2195','MQRC_UNEXPECTED_ERROR'}
           VALUE{'2196','MQRC_UNKNOWN_XMIT_Q'}
           VALUE{'2197','MQRC_UNKNOWN_DEF_XMIT_Q'}
           VALUE{'2198','MQRC_DEF_XMIT_Q_TYPE_ERROR'}
           VALUE{'2199','MQRC_DEF_XMIT_Q_USAGE_ERROR'}
           VALUE{'2201','MQRC_NAME_IN_USE'}
           VALUE{'2202','MQRC_CONNECTION_QUIESCING'}
           VALUE{'2203','MQRC_CONNECTION_STOPPING'}
           VALUE{'2204','MQRC_ADAPTER_NOT_AVAILABLE'}
           VALUE{'2206','MQRC_MSG_ID_ERROR'}
           VALUE{'2207','MQRC_CORREL_ID_ERROR'}
           VALUE{'2208','MQRC_FILE_SYSTEM_ERROR'}
           VALUE{'2209','MQRC_NO_MSG_LOCKED'}
           VALUE{'2216','MQRC_FILE_NOT_AUDITED'}
           VALUE{'2217','MQRC_CONNECTION_NOT_AUTHORIZED'}
           VALUE{'2218','MQRC_MSG_TOO_BIG_FOR_CHANNEL'}
           VALUE{'2219','MQRC_CALL_IN_PROGRESS'}
           VALUE{'2220','MQRC_RMH_ERROR'}
           VALUE{'2222','MQRC_Q_MGR_ACTIVE'}
           VALUE{'2223','MQRC_Q_MGR_NOT_ACTIVE'}
           VALUE{'2224','MQRC_Q_DEPTH_HIGH'}
           VALUE{'2225','MQRC_Q_DEPTH_LOW'}
           VALUE{'2226','MQRC_Q_SERVICE_INTERVAL_HIGH'}
           VALUE{'2227','MQRC_Q_SERVICE_INTERVAL_OK'}
           VALUE{'2232','MQRC_UNIT_OF_WORK_NOT_STARTED'}
           VALUE{'2233','MQRC_CHANNEL_AUTO_DEF_OK'}
           VALUE{'2234','MQRC_CHANNEL_AUTO_DEF_ERROR'}
           VALUE{'2235','MQRC_CFH_ERROR'}
           VALUE{'2236','MQRC_CFIL_ERROR'}
           VALUE{'2237','MQRC_CFIN_ERROR'}
           VALUE{'2238','MQRC_CFSL_ERROR'}
           VALUE{'2239','MQRC_CFST_ERROR'}
           VALUE{'2241','MQRC_INCOMPLETE_GROUP'}
           VALUE{'2242','MQRC_INCOMPLETE_MSG'}
           VALUE{'2243','MQRC_INCONSISTENT_CCSIDS'}
           VALUE{'2244','MQRC_INCONSISTENT_ENCODINGS'}
           VALUE{'2245','MQRC_INCONSISTENT_UOW'}
           VALUE{'2246','MQRC_INVALID_MSG_UNDER_CURSOR'}
           VALUE{'2247','MQRC_MATCH_OPTIONS_ERROR'}
           VALUE{'2248','MQRC_MDE_ERROR'}
           VALUE{'2249','MQRC_MSG_FLAGS_ERROR'}
           VALUE{'2250','MQRC_MSG_SEQ_NUMBER_ERROR'}
           VALUE{'2251','MQRC_OFFSET_ERROR'}
           VALUE{'2252','MQRC_ORIGINAL_LENGTH_ERROR'}
           VALUE{'2253','MQRC_SEGMENT_LENGTH_ZERO'}
           VALUE{'2255','MQRC_UOW_NOT_AVAILABLE'}
           VALUE{'2256','MQRC_WRONG_GMO_VERSION'}
           VALUE{'2257','MQRC_WRONG_MD_VERSION'}
           VALUE{'2258','MQRC_GROUP_ID_ERROR'}
           VALUE{'2259','MQRC_INCONSISTENT_BROWSE'}
           VALUE{'2260','MQRC_XQH_ERROR'}
           VALUE{'2261','MQRC_SRC_ENV_ERROR'}
           VALUE{'2262','MQRC_SRC_NAME_ERROR'}
           VALUE{'2263','MQRC_DEST_ENV_ERROR'}
           VALUE{'2264','MQRC_DEST_NAME_ERROR'}
           VALUE{'2265','MQRC_TM_ERROR'}
           VALUE{'2266','MQRC_CLUSTER_EXIT_ERROR'}
           VALUE{'2267','MQRC_CLUSTER_EXIT_LOAD_ERROR'}
           VALUE{'2268','MQRC_CLUSTER_PUT_INHIBITED'}
           VALUE{'2269','MQRC_CLUSTER_RESOURCE_ERROR'}
           VALUE{'2270','MQRC_NO_DESTINATIONS_AVAILABLE'}
           VALUE{'2273','MQRC_CONNECTION_ERROR'}
           VALUE{'2274','MQRC_OPTION_ENVIRONMENT_ERROR'}
           VALUE{'2277','MQRC_CD_ERROR'}
           VALUE{'2278','MQRC_CLIENT_CONN_ERROR'}
           VALUE{'2279','MQRC_CHANNEL_STOPPED_BY_USER'}
           VALUE{'2280','MQRC_HCONFIG_ERROR'}
           VALUE{'2281','MQRC_FUNCTION_ERROR'}
           VALUE{'2282','MQRC_CHANNEL_STARTED'}
           VALUE{'2283','MQRC_CHANNEL_STOPPED'}
           VALUE{'2284','MQRC_CHANNEL_CONV_ERROR'}
           VALUE{'2285','MQRC_SERVICE_NOT_AVAILABLE'}
           VALUE{'2286','MQRC_INITIALIZATION_FAILED'}
           VALUE{'2287','MQRC_TERMINATION_FAILED'}
           VALUE{'2288','MQRC_UNKNOWN_Q_NAME'}
           VALUE{'2289','MQRC_SERVICE_ERROR'}
           VALUE{'2290','MQRC_Q_ALREADY_EXISTS'}
           VALUE{'2291','MQRC_USER_ID_NOT_AVAILABLE'}
           VALUE{'2292','MQRC_UNKNOWN_ENTITY'}
           VALUE{'2293','MQRC_UNKNOWN_AUTH_ENTITY'}
           VALUE{'2294','MQRC_UNKNOWN_REF_OBJECT'}
           VALUE{'2295','MQRC_CHANNEL_ACTIVATED'}
           VALUE{'2296','MQRC_CHANNEL_NOT_ACTIVATED'}
           VALUE{'2297','MQRC_UOW_CANCELED'}
           VALUE{'2299','MQRC_SELECTOR_TYPE_ERROR'}
           VALUE{'2300','MQRC_COMMAND_TYPE_ERROR'}
           VALUE{'2301','MQRC_MULTIPLE_INSTANCE_ERROR'}
           VALUE{'2302','MQRC_SYSTEM_ITEM_NOT_ALTERABLE'}
           VALUE{'2303','MQRC_BAG_CONVERSION_ERROR'}
           VALUE{'2304','MQRC_SELECTOR_OUT_OF_RANGE'}
           VALUE{'2305','MQRC_SELECTOR_NOT_UNIQUE'}
           VALUE{'2306','MQRC_INDEX_NOT_PRESENT'}
           VALUE{'2307','MQRC_STRING_ERROR'}
           VALUE{'2308','MQRC_ENCODING_NOT_SUPPORTED'}
           VALUE{'2309','MQRC_SELECTOR_NOT_PRESENT'}
           VALUE{'2310','MQRC_OUT_SELECTOR_ERROR'}
           VALUE{'2311','MQRC_STRING_TRUNCATED'}
           VALUE{'2312','MQRC_SELECTOR_WRONG_TYPE'}
           VALUE{'2313','MQRC_INCONSISTENT_ITEM_TYPE'}
           VALUE{'2314','MQRC_INDEX_ERROR'}
           VALUE{'2315','MQRC_SYSTEM_BAG_NOT_ALTERABLE'}
           VALUE{'2316','MQRC_ITEM_COUNT_ERROR'}
           VALUE{'2317','MQRC_FORMAT_NOT_SUPPORTED'}
           VALUE{'2318','MQRC_SELECTOR_NOT_SUPPORTED'}
           VALUE{'2319','MQRC_ITEM_VALUE_ERROR'}
           VALUE{'2320','MQRC_HBAG_ERROR'}
           VALUE{'2321','MQRC_PARAMETER_MISSING'}
           VALUE{'2322','MQRC_CMD_SERVER_NOT_AVAILABLE'}
           VALUE{'2323','MQRC_STRING_LENGTH_ERROR'}
           VALUE{'2324','MQRC_INQUIRY_COMMAND_ERROR'}
           VALUE{'2325','MQRC_NESTED_BAG_NOT_SUPPORTED'}
           VALUE{'2326','MQRC_BAG_WRONG_TYPE'}
           VALUE{'2327','MQRC_ITEM_TYPE_ERROR'}
           VALUE{'2328','MQRC_SYSTEM_BAG_NOT_DELETABLE'}
           VALUE{'2329','MQRC_SYSTEM_ITEM_NOT_DELETABLE'}
           VALUE{'2330','MQRC_CODED_CHAR_SET_ID_ERROR'}
           VALUE{'2331','MQRC_MSG_TOKEN_ERROR'}
           VALUE{'2332','MQRC_MISSING_WIH'}
           VALUE{'2333','MQRC_WIH_ERROR'}
        }
       }
       }}
    }    /* end-group */
;
    GROUP{ POS{13,1,79}
      HDR{YES} FNAME{EXCALINF}
        TEXT{                        Expanded Call Information }
    }
;
    GROUP{ POS{15,1,79}
        DATACOL{25}
      CHAR{ FNAME{QMGRNAME} POS{1,,4}
        XNAME{QMGR NAME}
        DLOC{MQLCQMGR}
        FDESC{ COL{1} FILL{.}
          TEXT{QMgr Name} }
        HELP{This is the name of the queue manager that CICS was
             connected to at the time of the dump. \P
        }
      }
      CHAR{ FNAME{QNAME} POS{2,,48}
        XNAME{QUEUE NAME}
        DLOC{MQLCQNME}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQCB @FF003 @FF004 }
              DESC{Displays the queue defintions.  } }
        }}
        FDESC{ COL{1} FILL{.}
          TEXT{Queue Used in Call} }
        HELP{This is the name of the queue that was used for the
             MQSET call. \P
        }
      }
    IF {COND{OLDFMT} THEN { } ELSE {
      IF { COND{GOTMHND} THEN {
         HEX{ FNAME{OPENOPT}  POS{3,,8}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQM2 OPN @FF006 }
              DESC{Displays the OPEN options} }
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
      } ELSE {
         CHAR{ FNAME{OPENOPT}  POS{3,,4}
           XNAME{OPEN OPTIONS}
           DLOC{MQLCOPEN}
           FDESC{ COL{1} FILL{.}
             TEXT{Open Options} }
           HELP{These are the options that the queue manager used to
                open the queue. \P
           }
         }
        }
      } } }
   }  /* end-group */
;
  }                                              /* end-fixed */        03130000
  HELP{The MQSET call is used to change the attributes of an object     03140000
       represented by a handle. The object must be a queue. \P\P
       This screen displays the parameters that were used in the
       MQSET call. \P\P
  }                                                                     03160000
}                                                /* end-screen */       03170000
:END                                                                    03180000
*
*
*
:SCREEN{ NAME{MQLCLOSE} TITLE{Last WebSphere MQ Call Info}              00600000
 TEMPLATE{KAZHDTMP.MQLCLOSE}                     /* @03 */
  ORG{KAZ#MQLC}                                                         00610000
  FIXED{                                                                00620000
;
    DP{ FNAME{F003}     DLOC{MQLCQTYP} }
    DP{ FNAME{F004}     DLOC{MQLCHOBJ} }
    DP{ FNAME{F005}     DLOC{MQLCRC} }
    DP{ FNAME{F009}     DLOC{MQLCQREL} }       /* MQ RELEASE  @02 */
;
   COND{ FNAME{CHKCODE} DLOC{MQLCRC}
         COMPOP{CLC,'2085',NL} }
   COND{ FNAME{GOTMHND} DLOC{MQLCMHND}
         COMPOP{CLC,'Y',E} }
   COND{ FNAME{GOODCC} DLOC{MQLCMQCC}
         COMPOP{CB,X'00000002',L} }
   COND{FNAME{OLDFMT} DLOC{MQLC@FMT}
         COMPOP{CLC,'1',E} }
;
    LITERAL{ FNAME{CALMQCLS} POS{1,1,40} /*->fixedPro<-*/ /* @03 */
        TEXT {CALL 'MQCLOSE' USING}  }
    GROUP{ POS{2,1,79}
        DATACOL{25}
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HCONN}  POS{1,,8}
        XNAME{HCONN}
        DLOC{MQLCHCON}
        FDESC{ COL{7} FILL{.}
          TEXT{Hconn} }
        HELP{Connection Handle:  Input parameter \P\P
             This parameter represents the connection to the queue
             manager. The value was return on a previous MQCONN call.
             \P\P
             On OS/390 for CICS applications, the MQCONN call can be
             omitted and the value of MQHC_DEF_HCONN can be specified
             for this parameter. \P
        }
      } } }
    IF {COND{OLDFMT} THEN { } ELSE {
      HEX{ FNAME{HOBJECT}  POS{2,,8}
        XNAME{HOBJECT}
        DLOC{MQLCHOBJ}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQHI @FF004 C @FF009}                   /* @02 */
              DESC{Display Handle Information} }
        }}
        FDESC{ COL{7} FILL{.}
          TEXT{Hobj} }
        HELP{Object Handle:  Input/Output parameter \P\P
             This handle represents the object that is being closed.
             The object can be of any type. The value of Hobj was
             returned by a previous MQOPEN call. \P
             On successful completion of the call, the queue manager
             sets this parameter to a value that is not a valid
             handle for the environment. \P
             On OS/390, Hobj is set to a value that is undefined.
        }
      } } }
      HEX{ FNAME{CLOSOPTN}  POS{3,,8}
        XNAME{CLOSE OPTIONS}
        DLOC{MQLCOPTN}
        FDESC{ COL{7} FILL{.}
          TEXT{Options} }
        HELP{Close Options:  Input parameter \P\P
             The Options parameter controls how the object is closed.
             \P\P
             Only permanent dynamic queues can be closed in more
             than one way, being either retained or deleted.
        }
      }
      CHOICE{ FNAME{MQCOEQU} POS{3,40,20}
      XNAME{MQCOEQU}
      DLOC{MQLCOPTN}
       LISTV{
            VALUE{X'00','MQCO_NONE'}
            VALUE{X'01','MQCO_DELETE'}
            VALUE{X'02','MQCO_DELETE_PURGE'}
       }
       NOMATCH{*** INVALID ***}
      }
      BIN{ FNAME{COMPCODE} POS{4,,8}
        XNAME{COMP CODE}
        DLOC{MQLCMQCC}
        FDESC{ COL{7} FILL{.}
          TEXT{CompCode} }
        HELP{Completion Code:  Output parameter \P\P
             This is the completion code for the MQ API call. \P
        }
      }
      CHOICE{ FNAME{MQCCEQU} POS{4,40,20}
      XNAME{MQCCEQU}
      DLOC{MQLCMQCC}
       LISTV{
            VALUE{X'00','MQCC_OK'}
            VALUE{X'01','MQCC_WARNING'}
            VALUE{X'02','MQCC_FAILED'}
       }
      }
      CHAR{ FNAME{REASCODE} POS{5,,4}
        XNAME{REASON CODE}
        DLOC{MQLCRC}
        FDESC{ COL{7} FILL{.}
          TEXT{Reason} }
        ATTR{ TABS }
        COMMAND{ NAME{.DFLT}
           CMD{CPR MQDI @FF005}
           DESC{Display Reason Code}
           }
        HELP{Reason Code:  Output parameter \P\P
             This is the reason code that qualifies the
             completion code for the MQ API call.
        }
      }
     CHOICE{ FNAME{RCEQU1} POS{5,40,30}
     XNAME{REASON EQU}
     DLOC{MQLCRC}
      LISTV{
           VALUE{'0000','MQRC_NONE'}
           VALUE{'2001','MQRC_ALIAS_BASE_Q_TYPE_ERROR'}
           VALUE{'2002','MQRC_ALREADY_CONNECTED'}
           VALUE{'2003','MQRC_BACKED_OUT'}
           VALUE{'2004','MQRC_BUFFER_ERROR'}
           VALUE{'2005','MQRC_BUFFER_LENGTH_ERROR'}
           VALUE{'2006','MQRC_CHAR_ATTR_LENGTH_ERROR'}
           VALUE{'2007','MQRC_CHAR_ATTRS_ERROR'}
           VALUE{'2008','MQRC_CHAR_ATTRS_TOO_SHORT'}
           VALUE{'2009','MQRC_CONNECTION_BROKEN'}
           VALUE{'2010','MQRC_DATA_LENGTH_ERROR'}
           VALUE{'2011','MQRC_DYNAMIC_Q_NAME_ERROR'}
           VALUE{'2012','MQRC_ENVIRONMENT_ERROR'}
           VALUE{'2013','MQRC_EXPIRY_ERROR'}
           VALUE{'2014','MQRC_FEEDBACK_ERROR'}
           VALUE{'2016','MQRC_GET_INHIBITED'}
           VALUE{'2017','MQRC_HANDLE_NOT_AVAILABLE'}
           VALUE{'2018','MQRC_HCONN_ERROR'}
           VALUE{'2019','MQRC_HOBJ_ERROR'}
           VALUE{'2020','MQRC_INHIBIT_VALUE_ERROR'}
           VALUE{'2021','MQRC_INT_ATTR_COUNT_ERROR'}
           VALUE{'2022','MQRC_INT_ATTR_COUNT_TOO_SMALL'}
           VALUE{'2023','MQRC_INT_ATTRS_ARRAY_ERROR'}
           VALUE{'2024','MQRC_SYNCPOINT_LIMIT_REACHED'}
           VALUE{'2025','MQRC_MAX_CONNS_LIMIT_REACHED'}
           VALUE{'2026','MQRC_MD_ERROR'}
           VALUE{'2027','MQRC_MISSING_REPLY_TO_Q'}
           VALUE{'2029','MQRC_MSG_TYPE_ERROR'}
           VALUE{'2030','MQRC_MSG_TOO_BIG_FOR_Q'}
           VALUE{'2031','MQRC_MSG_TOO_BIG_FOR_Q_MGR'}
           VALUE{'2033','MQRC_NO_MSG_AVAILABLE'}
           VALUE{'2034','MQRC_NO_MSG_UNDER_CURSOR'}
           VALUE{'2035','MQRC_NOT_AUTHORIZED'}
           VALUE{'2036','MQRC_NOT_OPEN_FOR_BROWSE'}
           VALUE{'2037','MQRC_NOT_OPEN_FOR_INPUT'}
           VALUE{'2038','MQRC_NOT_OPEN_FOR_INQUIRE'}
           VALUE{'2039','MQRC_NOT_OPEN_FOR_OUTPUT'}
           VALUE{'2040','MQRC_NOT_OPEN_FOR_SET'}
           VALUE{'2041','MQRC_OBJECT_CHANGED'}
           VALUE{'2042','MQRC_OBJECT_IN_USE'}
           VALUE{'2043','MQRC_OBJECT_TYPE_ERROR'}
           VALUE{'2044','MQRC_OD_ERROR'}
           VALUE{'2045','MQRC_OPTION_NOT_VALID_FOR_TYPE'}
           VALUE{'2046','MQRC_OPTIONS_ERROR'}
           VALUE{'2047','MQRC_PERSISTENCE_ERROR'}
           VALUE{'2048','MQRC_PERSISTENT_NOT_ALLOWED'}
           VALUE{'2049','MQRC_PRIORITY_EXCEEDS_MAXIMUM'}
           VALUE{'2050','MQRC_PRIORITY_ERROR'}
           VALUE{'2051','MQRC_PUT_INHIBITED'}
           VALUE{'2052','MQRC_Q_DELETED'}
           VALUE{'2053','MQRC_Q_FULL'}
           VALUE{'2055','MQRC_Q_NOT_EMPTY'}
           VALUE{'2056','MQRC_Q_SPACE_NOT_AVAILABLE'}
           VALUE{'2057','MQRC_Q_TYPE_ERROR'}
           VALUE{'2058','MQRC_Q_MGR_NAME_ERROR'}
           VALUE{'2059','MQRC_Q_MGR_NOT_AVAILABLE'}
           VALUE{'2061','MQRC_REPORT_OPTIONS_ERROR'}
           VALUE{'2062','MQRC_SECOND_MARK_NOT_ALLOWED'}
           VALUE{'2063','MQRC_SECURITY_ERROR'}
           VALUE{'2065','MQRC_SELECTOR_COUNT_ERROR'}
           VALUE{'2066','MQRC_SELECTOR_LIMIT_EXCEEDED'}
           VALUE{'2067','MQRC_SELECTOR_ERROR'}
           VALUE{'2068','MQRC_SELECTOR_NOT_FOR_TYPE'}
           VALUE{'2069','MQRC_SIGNAL_OUTSTANDING'}
           VALUE{'2070','MQRC_SIGNAL_REQUEST_ACCEPTED'}
           VALUE{'2071','MQRC_STORAGE_NOT_AVAILABLE'}
           VALUE{'2072','MQRC_SYNCPOINT_NOT_AVAILABLE'}
           VALUE{'2075','MQRC_TRIGGER_CONTROL_ERROR'}
           VALUE{'2076','MQRC_TRIGGER_DEPTH_ERROR'}
           VALUE{'2077','MQRC_TRIGGER_MSG_PRIORITY_ERR'}
           VALUE{'2078','MQRC_TRIGGER_TYPE_ERROR'}
           VALUE{'2079','MQRC_TRUNCATED_MSG_ACCEPTED'}
           VALUE{'2080','MQRC_TRUNCATED_MSG_FAILED'}
           VALUE{'2082','MQRC_UNKNOWN_ALIAS_BASE_Q'}
      }
      }
    IF { COND{CHKCODE} THEN {
       CHOICE{ FNAME{RCEQU2}  POS{5,40,30}
       XNAME{REASON EQU}
       DLOC{MQLCRC}
         LISTV{
           VALUE{'2085','MQRC_UNKNOWN_OBJECT_NAME'}
           VALUE{'2086','MQRC_UNKNOWN_OBJECT_Q_MGR'}
           VALUE{'2087','MQRC_UNKNOWN_REMOTE_Q_MGR'}
           VALUE{'2090','MQRC_WAIT_INTERVAL_ERROR'}
           VALUE{'2091','MQRC_XMIT_Q_TYPE_ERROR'}
           VALUE{'2092','MQRC_XMIT_Q_USAGE_ERROR'}
           VALUE{'2093','MQRC_NOT_OPEN_FOR_PASS_ALL'}
           VALUE{'2094','MQRC_NOT_OPEN_FOR_PASS_IDENT'}
           VALUE{'2095','MQRC_NOT_OPEN_FOR_SET_ALL'}
           VALUE{'2096','MQRC_NOT_OPEN_FOR_SET_IDENT'}
           VALUE{'2097','MQRC_CONTEXT_HANDLE_ERROR'}
           VALUE{'2098','MQRC_CONTEXT_NOT_AVAILABLE'}
           VALUE{'2099','MQRC_SIGNAL1_ERROR'}
           VALUE{'2100','MQRC_OBJECT_ALREADY_EXISTS'}
           VALUE{'2101','MQRC_OBJECT_DAMAGED'}
           VALUE{'2102','MQRC_RESOURCE_PROBLEM'}
           VALUE{'2103','MQRC_ANOTHER_Q_MGR_CONNECTED'}
           VALUE{'2104','MQRC_UNKNOWN_REPORT_OPTION'}
           VALUE{'2105','MQRC_STORAGE_CLASS_ERROR'}
           VALUE{'2106','MQRC_COD_NOT_VALID_FOR_XCF_Q'}
           VALUE{'2107','MQRC_XWAIT_CANCELED'}
           VALUE{'2108','MQRC_XWAIT_ERROR'}
           VALUE{'2109','MQRC_SUPPRESSED_BY_EXIT'}
           VALUE{'2110','MQRC_FORMAT_ERROR'}
           VALUE{'2111','MQRC_SOURCE_CCSID_ERROR'}
           VALUE{'2112','MQRC_SOURCE_INTEGER_ENC_ERROR'}
           VALUE{'2113','MQRC_SOURCE_DECIMAL_ENC_ERROR'}
           VALUE{'2114','MQRC_SOURCE_FLOAT_ENC_ERROR'}
           VALUE{'2115','MQRC_TARGET_CCSID_ERROR'}
           VALUE{'2116','MQRC_TARGET_INTEGER_ENC_ERROR'}
           VALUE{'2117','MQRC_TARGET_DECIMAL_ENC_ERROR'}
           VALUE{'2118','MQRC_TARGET_FLOAT_ENC_ERROR'}
           VALUE{'2119','MQRC_NOT_CONVERTED'}
           VALUE{'2120','MQRC_CONVERTED_MSG_TOO_BIG'}
           VALUE{'2120','MQRC_TRUNCATED'}
           VALUE{'2121','MQRC_NO_EXTERNAL_PARTICIPANTS'}
           VALUE{'2122','MQRC_PARTICIPANT_NOT_AVAILABLE'}
           VALUE{'2123','MQRC_OUTCOME_MIXED'}
           VALUE{'2124','MQRC_OUTCOME_PENDING'}
           VALUE{'2125','MQRC_BRIDGE_STARTED'}
           VALUE{'2126','MQRC_BRIDGE_STOPPED'}
           VALUE{'2127','MQRC_ADAPTER_STORAGE_SHORTAGE'}
           VALUE{'2128','MQRC_UOW_IN_PROGRESS'}
           VALUE{'2129','MQRC_ADAPTER_CONN_LOAD_ERROR'}
           VALUE{'2130','MQRC_ADAPTER_SERV_LOAD_ERROR'}
           VALUE{'2131','MQRC_ADAPTER_DEFS_ERROR'}
           VALUE{'2132','MQRC_ADAPTER_DEFS_LOAD_ERROR'}
           VALUE{'2133','MQRC_ADAPTER_CONV_LOAD_ERROR'}
           VALUE{'2134','MQRC_BO_ERROR'}
           VALUE{'2135','MQRC_DH_ERROR'}
           VALUE{'2136','MQRC_MULTIPLE_REASONS'}
           VALUE{'2137','MQRC_OPEN_FAILED'}
           VALUE{'2138','MQRC_ADAPTER_DISC_LOAD_ERROR'}
           VALUE{'2139','MQRC_CNO_ERROR'}
           VALUE{'2140','MQRC_CICS_WAIT_FAILED'}
           VALUE{'2141','MQRC_DLH_ERROR'}
           VALUE{'2142','MQRC_HEADER_ERROR'}
           VALUE{'2143','MQRC_SOURCE_LENGTH_ERROR'}
           VALUE{'2144','MQRC_TARGET_LENGTH_ERROR'}
           VALUE{'2145','MQRC_SOURCE_BUFFER_ERROR'}
           VALUE{'2146','MQRC_TARGET_BUFFER_ERROR'}
           VALUE{'2148','MQRC_IIH_ERROR'}
           VALUE{'2149','MQRC_PCF_ERROR'}
           VALUE{'2150','MQRC_DBCS_ERROR'}
           VALUE{'2152','MQRC_OBJECT_NAME_ERROR'}
           VALUE{'2153','MQRC_OBJECT_Q_MGR_NAME_ERROR'}
           VALUE{'2154','MQRC_RECS_PRESENT_ERROR'}
           VALUE{'2155','MQRC_OBJECT_RECORDS_ERROR'}
           VALUE{'2156','MQRC_RESPONSE_RECORDS_ERROR'}
           VALUE{'2157','MQRC_ASID_MISMATCH'}
           VALUE{'2158','MQRC_PMO_RECORD_FLAGS_ERROR'}
           VALUE{'2159','MQRC_PUT_MSG_RECORDS_ERROR'}
           VALUE{'2160','MQRC_CONN_ID_IN_USE'}
           VALUE{'2161','MQRC_Q_MGR_QUIESCING'}
           VALUE{'2162','MQRC_Q_MGR_STOPPING'}
           VALUE{'2163','MQRC_DUPLICATE_RECOV_COORD'}
           VALUE{'2173','MQRC_PMO_ERROR'}
           VALUE{'2182','MQRC_API_EXIT_NOT_FOUND'}
           VALUE{'2183','MQRC_API_EXIT_LOAD_ERROR'}
           VALUE{'2184','MQRC_REMOTE_Q_NAME_ERROR'}
           VALUE{'2185','MQRC_INCONSISTENT_PERSISTENCE'}
           VALUE{'2186','MQRC_GMO_ERROR'}
           VALUE{'2187','MQRC_CICS_BRIDGE_RESTRICTION'}
           VALUE{'2188','MQRC_STOPPED_BY_CLUSTER_EXIT'}
           VALUE{'2189','MQRC_CLUSTER_RESOLUTION_ERROR'}
           VALUE{'2190','MQRC_CONVERTED_STRING_TOO_BIG'}
           VALUE{'2191','MQRC_TMC_ERROR'}
           VALUE{'2192','MQRC_PAGESET_FULL'}
           VALUE{'2193','MQRC_PAGESET_ERROR'}
           VALUE{'2194','MQRC_NAME_NOT_VALID_FOR_TYPE'}
           VALUE{'2195','MQRC_UNEXPECTED_ERROR'}
           VALUE{'2196','MQRC_UNKNOWN_XMIT_Q'}
           VALUE{'2197','MQRC_UNKNOWN_DEF_XMIT_Q'}
           VALUE{'2198','MQRC_DEF_XMIT_Q_TYPE_ERROR'}
           VALUE{'2199','MQRC_DEF_XMIT_Q_USAGE_ERROR'}
           VALUE{'2201','MQRC_NAME_IN_USE'}
           VALUE{'2202','MQRC_CONNECTION_QUIESCING'}
           VALUE{'2203','MQRC_CONNECTION_STOPPING'}
           VALUE{'2204','MQRC_ADAPTER_NOT_AVAILABLE'}
           VALUE{'2206','MQRC_MSG_ID_ERROR'}
           VALUE{'2207','MQRC_CORREL_ID_ERROR'}
           VALUE{'2208','MQRC_FILE_SYSTEM_ERROR'}
           VALUE{'2209','MQRC_NO_MSG_LOCKED'}
           VALUE{'2216','MQRC_FILE_NOT_AUDITED'}
           VALUE{'2217','MQRC_CONNECTION_NOT_AUTHORIZED'}
           VALUE{'2218','MQRC_MSG_TOO_BIG_FOR_CHANNEL'}
           VALUE{'2219','MQRC_CALL_IN_PROGRESS'}
           VALUE{'2220','MQRC_RMH_ERROR'}
           VALUE{'2222','MQRC_Q_MGR_ACTIVE'}
           VALUE{'2223','MQRC_Q_MGR_NOT_ACTIVE'}
           VALUE{'2224','MQRC_Q_DEPTH_HIGH'}
           VALUE{'2225','MQRC_Q_DEPTH_LOW'}
           VALUE{'2226','MQRC_Q_SERVICE_INTERVAL_HIGH'}
           VALUE{'2227','MQRC_Q_SERVICE_INTERVAL_OK'}
           VALUE{'2232','MQRC_UNIT_OF_WORK_NOT_STARTED'}
           VALUE{'2233','MQRC_CHANNEL_AUTO_DEF_OK'}
           VALUE{'2234','MQRC_CHANNEL_AUTO_DEF_ERROR'}
           VALUE{'2235','MQRC_CFH_ERROR'}
           VALUE{'2236','MQRC_CFIL_ERROR'}
           VALUE{'2237','MQRC_CFIN_ERROR'}
           VALUE{'2238','MQRC_CFSL_ERROR'}
           VALUE{'2239','MQRC_CFST_ERROR'}
           VALUE{'2241','MQRC_INCOMPLETE_GROUP'}
           VALUE{'2242','MQRC_INCOMPLETE_MSG'}
           VALUE{'2243','MQRC_INCONSISTENT_CCSIDS'}
           VALUE{'2244','MQRC_INCONSISTENT_ENCODINGS'}
           VALUE{'2245','MQRC_INCONSISTENT_UOW'}
           VALUE{'2246','MQRC_INVALID_MSG_UNDER_CURSOR'}
           VALUE{'2247','MQRC_MATCH_OPTIONS_ERROR'}
           VALUE{'2248','MQRC_MDE_ERROR'}
           VALUE{'2249','MQRC_MSG_FLAGS_ERROR'}
           VALUE{'2250','MQRC_MSG_SEQ_NUMBER_ERROR'}
           VALUE{'2251','MQRC_OFFSET_ERROR'}
           VALUE{'2252','MQRC_ORIGINAL_LENGTH_ERROR'}
           VALUE{'2253','MQRC_SEGMENT_LENGTH_ZERO'}
           VALUE{'2255','MQRC_UOW_NOT_AVAILABLE'}
           VALUE{'2256','MQRC_WRONG_GMO_VERSION'}
           VALUE{'2257','MQRC_WRONG_MD_VERSION'}
           VALUE{'2258','MQRC_GROUP_ID_ERROR'}
           VALUE{'2259','MQRC_INCONSISTENT_BROWSE'}
           VALUE{'2260','MQRC_XQH_ERROR'}
           VALUE{'2261','MQRC_SRC_ENV_ERROR'}
           VALUE{'2262','MQRC_SRC_NAME_ERROR'}
           VALUE{'2263','MQRC_DEST_ENV_ERROR'}
           VALUE{'2264','MQRC_DEST_NAME_ERROR'}
           VALUE{'2265','MQRC_TM_ERROR'}
           VALUE{'2266','MQRC_CLUSTER_EXIT_ERROR'}
           VALUE{'2267','MQRC_CLUSTER_EXIT_LOAD_ERROR'}
           VALUE{'2268','MQRC_CLUSTER_PUT_INHIBITED'}
           VALUE{'2269','MQRC_CLUSTER_RESOURCE_ERROR'}
           VALUE{'2270','MQRC_NO_DESTINATIONS_AVAILABLE'}
           VALUE{'2273','MQRC_CONNECTION_ERROR'}
           VALUE{'2274','MQRC_OPTION_ENVIRONMENT_ERROR'}
           VALUE{'2277','MQRC_CD_ERROR'}
           VALUE{'2278','MQRC_CLIENT_CONN_ERROR'}
           VALUE{'2279','MQRC_CHANNEL_STOPPED_BY_USER'}
           VALUE{'2280','MQRC_HCONFIG_ERROR'}
           VALUE{'2281','MQRC_FUNCTION_ERROR'}
           VALUE{'2282','MQRC_CHANNEL_STARTED'}
           VALUE{'2283','MQRC_CHANNEL_STOPPED'}
           VALUE{'2284','MQRC_CHANNEL_CONV_ERROR'}
           VALUE{'2285','MQRC_SERVICE_NOT_AVAILABLE'}
           VALUE{'2286','MQRC_INITIALIZATION_FAILED'}
           VALUE{'2287','MQRC_TERMINATION_FAILED'}
           VALUE{'2288','MQRC_UNKNOWN_Q_NAME'}
           VALUE{'2289','MQRC_SERVICE_ERROR'}
           VALUE{'2290','MQRC_Q_ALREADY_EXISTS'}
           VALUE{'2291','MQRC_USER_ID_NOT_AVAILABLE'}
           VALUE{'2292','MQRC_UNKNOWN_ENTITY'}
           VALUE{'2293','MQRC_UNKNOWN_AUTH_ENTITY'}
           VALUE{'2294','MQRC_UNKNOWN_REF_OBJECT'}
           VALUE{'2295','MQRC_CHANNEL_ACTIVATED'}
           VALUE{'2296','MQRC_CHANNEL_NOT_ACTIVATED'}
           VALUE{'2297','MQRC_UOW_CANCELED'}
           VALUE{'2299','MQRC_SELECTOR_TYPE_ERROR'}
           VALUE{'2300','MQRC_COMMAND_TYPE_ERROR'}
           VALUE{'2301','MQRC_MULTIPLE_INSTANCE_ERROR'}
           VALUE{'2302','MQRC_SYSTEM_ITEM_NOT_ALTERABLE'}
           VALUE{'2303','MQRC_BAG_CONVERSION_ERROR'}
           VALUE{'2304','MQRC_SELECTOR_OUT_OF_RANGE'}
           VALUE{'2305','MQRC_SELECTOR_NOT_UNIQUE'}
           VALUE{'2306','MQRC_INDEX_NOT_PRESENT'}
           VALUE{'2307','MQRC_STRING_ERROR'}
           VALUE{'2308','MQRC_ENCODING_NOT_SUPPORTED'}
           VALUE{'2309','MQRC_SELECTOR_NOT_PRESENT'}
           VALUE{'2310','MQRC_OUT_SELECTOR_ERROR'}
           VALUE{'2311','MQRC_STRING_TRUNCATED'}
           VALUE{'2312','MQRC_SELECTOR_WRONG_TYPE'}
           VALUE{'2313','MQRC_INCONSISTENT_ITEM_TYPE'}
           VALUE{'2314','MQRC_INDEX_ERROR'}
           VALUE{'2315','MQRC_SYSTEM_BAG_NOT_ALTERABLE'}
           VALUE{'2316','MQRC_ITEM_COUNT_ERROR'}
           VALUE{'2317','MQRC_FORMAT_NOT_SUPPORTED'}
           VALUE{'2318','MQRC_SELECTOR_NOT_SUPPORTED'}
           VALUE{'2319','MQRC_ITEM_VALUE_ERROR'}
           VALUE{'2320','MQRC_HBAG_ERROR'}
           VALUE{'2321','MQRC_PARAMETER_MISSING'}
           VALUE{'2322','MQRC_CMD_SERVER_NOT_AVAILABLE'}
           VALUE{'2323','MQRC_STRING_LENGTH_ERROR'}
           VALUE{'2324','MQRC_INQUIRY_COMMAND_ERROR'}
           VALUE{'2325','MQRC_NESTED_BAG_NOT_SUPPORTED'}
           VALUE{'2326','MQRC_BAG_WRONG_TYPE'}
           VALUE{'2327','MQRC_ITEM_TYPE_ERROR'}
           VALUE{'2328','MQRC_SYSTEM_BAG_NOT_DELETABLE'}
           VALUE{'2329','MQRC_SYSTEM_ITEM_NOT_DELETABLE'}
           VALUE{'2330','MQRC_CODED_CHAR_SET_ID_ERROR'}
           VALUE{'2331','MQRC_MSG_TOKEN_ERROR'}
           VALUE{'2332','MQRC_MISSING_WIH'}
           VALUE{'2333','MQRC_WIH_ERROR'}
        }
       }
       }}
    }    /* end-group */
;
    GROUP{ POS{13,1,79}
      HDR{YES} FNAME{EXCALINF}
        TEXT{                        Expanded Call Information }
    }
;
    GROUP{ POS{15,1,79}
        DATACOL{25}
      CHAR{ FNAME{QMGRNAME} POS{1,,4}
        XNAME{QMGR NAME}
        DLOC{MQLCQMGR}
        FDESC{ COL{1} FILL{.}
          TEXT{QMgr Name} }
        HELP{This is the name of the queue manager that CICS was
             connected to at the time of the dump. \P
        }
      }
      CHAR{ FNAME{QNAME} POS{2,,48}
        XNAME{QUEUE NAME}
        DLOC{MQLCQNME}
        IF { COND{GOTMHND} THEN {
           ATTR{ TABS }
           COMMAND{ NAME{.DFLT}
              CMD{CPR MQCB @FF003 @FF004 }
              DESC{Displays the queue defintions.  } }
        }}
        FDESC{ COL{1} FILL{.}
          TEXT{Queue Used in Call} }
        HELP{This is the name of the queue that was used for the
             MQCLOSE call. \P
        }
      }
   }  /* end-group */
;
  }                                              /* end-fixed */        03130000
  HELP{The MQCLOSE call relinquishes access to an object. \P\P          03140000
       This screen displays the parameters that were used in the
       MQCLOSE call.\P
  }                                                                     03160000
}                                                /* end-screen */       03170000
:END                                                                    03180000