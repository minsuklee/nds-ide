//---------------------------------------------------------------------------*
//                                                                           *
//                            File 'xml_os.cpp'                              *
//                 Generated by version GALGAS_BETA_VERSION                  *
//                      june 12th, 2009, at 14h44'48"                        *
//                                                                           *
//---------------------------------------------------------------------------*

//--- START OF USER ZONE 1


//--- END OF USER ZONE 1

//---------------------------------------------------------------------------*

#include "version_libpm.h"
#if LIBPM_VERSION != 502
  #error "This file has been compiled with a version of GALGAS different than the version of libpm"
#endif

//---------------------------------------------------------------------------*

#include <typeinfo>
#include "utilities/MF_MemoryControl.h"
#include "files/C_TextFileWrite.h"
#include "xml_os.h"

//---------------------------------------------------------------------------*

#ifndef DO_NOT_GENERATE_CHECKINGS
  #define SOURCE_FILE_AT_LINE(line) "xml_os.ggs", line
  #define COMMA_SOURCE_FILE_AT_LINE(line) , SOURCE_FILE_AT_LINE(line)
#else
  #define SOURCE_FILE_AT_LINE(line) 
  #define COMMA_SOURCE_FILE_AT_LINE(line) 
#endif


//--- START OF USER ZONE 2


//--- END OF USER ZONE 2

//---------------------------------------------------------------------------*
//                                                                           *
//                Implementation of routine "parse_oshooks"                  *
//                                                                           *
//---------------------------------------------------------------------------*

void routine_parse_oshooks (C_Compiler & inLexique,
                                const GGS_xmlNodeList   var_cas_hooks,
                                GGS_root_obj  & var_cas_cpu COMMA_UNUSED_LOCATION_ARGS) {
  #ifdef DEBUG_TRACE_ENABLED
    printf ("ENTER routine_parse_oshooks at %s:%d\n", __FILE__, __LINE__) ;
  #endif
  {
    GGS_xmlNodeList::cEnumerator enumerator_661 (var_cas_hooks, true) ;
    const GGS_xmlNodeList::cElement * operand_661 = NULL ;
    while (((operand_661 = enumerator_661.nextObject ()))) {
      macroValidPointer (operand_661) ;
      if ((function_is_elem (inLexique, operand_661->node, GGS_string ("PARAMETER-VALUES") COMMA_SOURCE_FILE_AT_LINE (36))).isBuiltAndTrue ()) {
        GGS_xmlNodeList  var_cas_params ;
        var_cas_params = operand_661->node.reader_nodeList (inLexique COMMA_SOURCE_FILE_AT_LINE (37)) ;
        GGS_os_obj  var_cas_os ;
        var_cas_os = var_cas_cpu.reader_os (inLexique COMMA_SOURCE_FILE_AT_LINE (38)) ;
        {
          GGS_xmlNodeList::cEnumerator enumerator_807 (var_cas_params, true) ;
          const GGS_xmlNodeList::cElement * operand_807 = NULL ;
          while (((operand_807 = enumerator_807.nextObject ()))) {
            macroValidPointer (operand_807) ;
            if ((function_is_param (inLexique, operand_807->node, GGS_string ("OsErrorHook") COMMA_SOURCE_FILE_AT_LINE (40))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setErrorhook (inLexique, function_bool_class_param (inLexique, operand_807->node COMMA_SOURCE_FILE_AT_LINE (41)) COMMA_SOURCE_FILE_AT_LINE (41)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_errorhook (inLexique COMMA_SOURCE_FILE_AT_LINE (42)) COMMA_SOURCE_FILE_AT_LINE (42)) ;
            }else if ((function_is_param (inLexique, operand_807->node, GGS_string ("OsPostTaskHook") COMMA_SOURCE_FILE_AT_LINE (43))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setPosttaskhook (inLexique, function_bool_class_param (inLexique, operand_807->node COMMA_SOURCE_FILE_AT_LINE (44)) COMMA_SOURCE_FILE_AT_LINE (44)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_posttaskhook (inLexique COMMA_SOURCE_FILE_AT_LINE (45)) COMMA_SOURCE_FILE_AT_LINE (45)) ;
            }else if ((function_is_param (inLexique, operand_807->node, GGS_string ("OsPreTaskHook") COMMA_SOURCE_FILE_AT_LINE (46))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setPretaskhook (inLexique, function_bool_class_param (inLexique, operand_807->node COMMA_SOURCE_FILE_AT_LINE (47)) COMMA_SOURCE_FILE_AT_LINE (47)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_pretaskhook (inLexique COMMA_SOURCE_FILE_AT_LINE (48)) COMMA_SOURCE_FILE_AT_LINE (48)) ;
            }else if ((function_is_param (inLexique, operand_807->node, GGS_string ("OsProtectionHook") COMMA_SOURCE_FILE_AT_LINE (49))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setProtectionhook (inLexique, function_bool_class_param (inLexique, operand_807->node COMMA_SOURCE_FILE_AT_LINE (50)) COMMA_SOURCE_FILE_AT_LINE (50)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_protectionhook (inLexique COMMA_SOURCE_FILE_AT_LINE (51)) COMMA_SOURCE_FILE_AT_LINE (51)) ;
            }else if ((function_is_param (inLexique, operand_807->node, GGS_string ("OsShutdownHook") COMMA_SOURCE_FILE_AT_LINE (52))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setShutdownhook (inLexique, function_bool_class_param (inLexique, operand_807->node COMMA_SOURCE_FILE_AT_LINE (53)) COMMA_SOURCE_FILE_AT_LINE (53)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_shutdownhook (inLexique COMMA_SOURCE_FILE_AT_LINE (54)) COMMA_SOURCE_FILE_AT_LINE (54)) ;
            }else if ((function_is_param (inLexique, operand_807->node, GGS_string ("OsStartupHook") COMMA_SOURCE_FILE_AT_LINE (55))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setStartuphook (inLexique, function_bool_class_param (inLexique, operand_807->node COMMA_SOURCE_FILE_AT_LINE (56)) COMMA_SOURCE_FILE_AT_LINE (56)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_startuphook (inLexique COMMA_SOURCE_FILE_AT_LINE (57)) COMMA_SOURCE_FILE_AT_LINE (57)) ;
            }
          }
        }
        var_cas_cpu.modifier_setOs (inLexique, var_cas_os COMMA_SOURCE_FILE_AT_LINE (60)) ;
      }
    }
  }
  #ifdef DEBUG_TRACE_ENABLED
    printf ("LEAVE routine_parse_oshooks\n") ;
  #endif
}

//---------------------------------------------------------------------------*
//                                                                           *
//            Implementation of routine "parse_os_subcontainer"              *
//                                                                           *
//---------------------------------------------------------------------------*

void routine_parse_os_subcontainer (C_Compiler & inLexique,
                                const GGS_xmlNodeList   var_cas_cont_elems,
                                GGS_root_obj  & var_cas_cpu COMMA_UNUSED_LOCATION_ARGS) {
  #ifdef DEBUG_TRACE_ENABLED
    printf ("ENTER routine_parse_os_subcontainer at %s:%d\n", __FILE__, __LINE__) ;
  #endif
  {
    GGS_xmlNodeList::cEnumerator enumerator_1880 (var_cas_cont_elems, true) ;
    const GGS_xmlNodeList::cElement * operand_1880 = NULL ;
    while (((operand_1880 = enumerator_1880.nextObject ()))) {
      macroValidPointer (operand_1880) ;
      GGS_lstring  var_cas_elem_name ;
      var_cas_elem_name = function_long_name (inLexique, operand_1880->node COMMA_SOURCE_FILE_AT_LINE (70)) ;
      if (((var_cas_elem_name.reader_string (inLexique COMMA_SOURCE_FILE_AT_LINE (71))).operator_isEqual (GGS_string ("OsHooks"))).isBuiltAndTrue ()) {
        inLexique.printMessage (GGS_string ("OsHooks trouve\n") COMMA_SOURCE_FILE_AT_LINE (72)) ;
        ::routine_parse_oshooks (inLexique,  var_cas_cont_elems,  var_cas_cpu COMMA_SOURCE_FILE_AT_LINE (73)) ;
      }
    }
  }
  #ifdef DEBUG_TRACE_ENABLED
    printf ("LEAVE routine_parse_os_subcontainer\n") ;
  #endif
}

//---------------------------------------------------------------------------*
//                                                                           *
//                  Implementation of routine "parse_osos"                   *
//                                                                           *
//---------------------------------------------------------------------------*

void routine_parse_osos (C_Compiler & inLexique,
                                const GGS_xmlNodeList   var_cas_osos,
                                GGS_root_obj  & var_cas_cpu COMMA_UNUSED_LOCATION_ARGS) {
  #ifdef DEBUG_TRACE_ENABLED
    printf ("ENTER routine_parse_osos at %s:%d\n", __FILE__, __LINE__) ;
  #endif
  {
    GGS_xmlNodeList::cEnumerator enumerator_2161 (var_cas_osos, true) ;
    const GGS_xmlNodeList::cElement * operand_2161 = NULL ;
    while (((operand_2161 = enumerator_2161.nextObject ()))) {
      macroValidPointer (operand_2161) ;
      if ((function_is_elem (inLexique, operand_2161->node, GGS_string ("PARAMETER-VALUES") COMMA_SOURCE_FILE_AT_LINE (83))).isBuiltAndTrue ()) {
        inLexique.printMessage (GGS_string ("*** PARAMETER-VALUES trouve\n") COMMA_SOURCE_FILE_AT_LINE (84)) ;
        GGS_xmlNodeList  var_cas_params ;
        var_cas_params = operand_2161->node.reader_nodeList (inLexique COMMA_SOURCE_FILE_AT_LINE (85)) ;
        GGS_os_obj  var_cas_os ;
        var_cas_os = var_cas_cpu.reader_os (inLexique COMMA_SOURCE_FILE_AT_LINE (86)) ;
        {
          GGS_xmlNodeList::cEnumerator enumerator_2354 (var_cas_params, true) ;
          const GGS_xmlNodeList::cElement * operand_2354 = NULL ;
          while (((operand_2354 = enumerator_2354.nextObject ()))) {
            macroValidPointer (operand_2354) ;
            if ((function_is_param (inLexique, operand_2354->node, GGS_string ("OsScalabilityClass") COMMA_SOURCE_FILE_AT_LINE (88))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setScalabilityclass (inLexique, function_lstring_param (inLexique, operand_2354->node COMMA_SOURCE_FILE_AT_LINE (89)) COMMA_SOURCE_FILE_AT_LINE (89)) ;
              inLexique.printMessage ((var_cas_os.reader_scalabilityclass (inLexique COMMA_SOURCE_FILE_AT_LINE (90)).reader_string (inLexique COMMA_SOURCE_FILE_AT_LINE (90))).operator_concat (GGS_string ("\n")) COMMA_SOURCE_FILE_AT_LINE (90)) ;
            }else if ((function_is_param (inLexique, operand_2354->node, GGS_string ("OsStatus") COMMA_SOURCE_FILE_AT_LINE (91))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setStatus (inLexique, function_lstring_param (inLexique, operand_2354->node COMMA_SOURCE_FILE_AT_LINE (92)) COMMA_SOURCE_FILE_AT_LINE (92)) ;
              inLexique.printMessage ((var_cas_os.reader_status (inLexique COMMA_SOURCE_FILE_AT_LINE (93)).reader_string (inLexique COMMA_SOURCE_FILE_AT_LINE (93))).operator_concat (GGS_string ("\n")) COMMA_SOURCE_FILE_AT_LINE (93)) ;
            }else if ((function_is_param (inLexique, operand_2354->node, GGS_string ("OsStackMonitoring") COMMA_SOURCE_FILE_AT_LINE (94))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setStackmonitoring (inLexique, function_bool_class_param (inLexique, operand_2354->node COMMA_SOURCE_FILE_AT_LINE (95)) COMMA_SOURCE_FILE_AT_LINE (95)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_stackmonitoring (inLexique COMMA_SOURCE_FILE_AT_LINE (96)) COMMA_SOURCE_FILE_AT_LINE (96)) ;
            }else if ((function_is_param (inLexique, operand_2354->node, GGS_string ("OsUseGetServiceId") COMMA_SOURCE_FILE_AT_LINE (97))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setUsegetserviceid (inLexique, function_bool_class_param (inLexique, operand_2354->node COMMA_SOURCE_FILE_AT_LINE (98)) COMMA_SOURCE_FILE_AT_LINE (98)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_usegetserviceid (inLexique COMMA_SOURCE_FILE_AT_LINE (99)) COMMA_SOURCE_FILE_AT_LINE (99)) ;
            }else if ((function_is_param (inLexique, operand_2354->node, GGS_string ("OsUseParameterAccess") COMMA_SOURCE_FILE_AT_LINE (100))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setUseparameteraccess (inLexique, function_bool_class_param (inLexique, operand_2354->node COMMA_SOURCE_FILE_AT_LINE (101)) COMMA_SOURCE_FILE_AT_LINE (101)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_useparameteraccess (inLexique COMMA_SOURCE_FILE_AT_LINE (102)) COMMA_SOURCE_FILE_AT_LINE (102)) ;
            }else if ((function_is_param (inLexique, operand_2354->node, GGS_string ("OsUseResScheduler") COMMA_SOURCE_FILE_AT_LINE (103))).isBuiltAndTrue ()) {
              var_cas_os.modifier_setUseresscheduler (inLexique, function_bool_class_param (inLexique, operand_2354->node COMMA_SOURCE_FILE_AT_LINE (104)) COMMA_SOURCE_FILE_AT_LINE (104)) ;
              ::routine_p_bt (inLexique,  var_cas_os.reader_useresscheduler (inLexique COMMA_SOURCE_FILE_AT_LINE (105)) COMMA_SOURCE_FILE_AT_LINE (105)) ;
            }
          }
        }
        var_cas_cpu.modifier_setOs (inLexique, var_cas_os COMMA_SOURCE_FILE_AT_LINE (108)) ;
      }else if ((function_is_elem (inLexique, operand_2161->node, GGS_string ("SUB-CONTAINERS") COMMA_SOURCE_FILE_AT_LINE (109))).isBuiltAndTrue ()) {
        GGS_xmlNodeList  var_cas_nl ;
        var_cas_nl = operand_2161->node.reader_nodeList (inLexique COMMA_SOURCE_FILE_AT_LINE (110)) ;
        {
          GGS_xmlNodeList::cEnumerator enumerator_3465 (var_cas_nl, true) ;
          const GGS_xmlNodeList::cElement * operand_3465 = NULL ;
          while (((operand_3465 = enumerator_3465.nextObject ()))) {
            macroValidPointer (operand_3465) ;
            ::routine_parse_os_subcontainer (inLexique,  operand_3465->node.reader_nodeList (inLexique COMMA_SOURCE_FILE_AT_LINE (112)),  var_cas_cpu COMMA_SOURCE_FILE_AT_LINE (112)) ;
          }
        }
      }
    }
  }
  #ifdef DEBUG_TRACE_ENABLED
    printf ("LEAVE routine_parse_osos\n") ;
  #endif
}

//---------------------------------------------------------------------------*

