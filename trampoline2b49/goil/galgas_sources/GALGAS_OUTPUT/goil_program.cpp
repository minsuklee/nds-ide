//---------------------------------------------------------------------------*
//                                                                           *
//                         File 'goil_program.cpp'                           *
//                        Generated by version 2.0.0                         *
//                       july 7th, 2010, at 17h17'9"                         *
//                                                                           *
//---------------------------------------------------------------------------*

//--- START OF USER ZONE 1


//--- END OF USER ZONE 1

#include "version_libpm.h"
#if CURRENT_LIBPM_VERSION != 820
  #error "This file has been compiled with a version of GALGAS that uses libpm version 820, different than the current version (CURRENT_LIBPM_VERSION) of libpm"
#endif

//---------------------------------------------------------------------------*

#include "utilities/F_DisplayException.h"
#include "utilities/MF_MemoryControl.h"
#include "collections/TC_UniqueArray.h"
#include "command_line_interface/F_Analyze_CLI_Options.h"
#include "command_line_interface/mainForLIBPM.h"
#include "utilities/MF_MemoryControl.h"
#include "command_line_interface/C_StringCommandLineOption.h"
#include "utilities/cpp-allocation.h"
#include "utilities/basic-allocation.h"

#ifdef TARGET_API_MAC_CARBON
  #include <SIOUX.H>
#endif

#ifdef COMPILE_FOR_WIN32
  #ifdef __MWERKS__
    #include <WINSIOUX.H>
  #endif
#endif

#include <typeinfo>

//---------------------------------------------------------------------------*

#include "goil_grammar.h"
#include "goil_program.h"

//---------------------------------------------------------------------------*

#ifndef DO_NOT_GENERATE_CHECKINGS
  #define SOURCE_FILE_AT_LINE(line) "goil_program.gProgram", line
  #define COMMA_SOURCE_FILE_AT_LINE(line) , SOURCE_FILE_AT_LINE(line)
#else
  #define SOURCE_FILE_AT_LINE(line) 
  #define COMMA_SOURCE_FILE_AT_LINE(line) 
#endif

//---------------------------------------------------------------------------*
//                                                                           *
//                     P R O G R A M    P R O L O G U E                      *
//                                                                           *
//---------------------------------------------------------------------------*

static void
goil_program_prologue (C_Compiler & /* inLexique */,
                     const TC_UniqueArray <C_String> & /* inSourceFilesArray */) {
}

//---------------------------------------------------------------------------*
//                                                                           *
//                     P R O G R A M    E P I L O G U E                      *
//                                                                           *
//---------------------------------------------------------------------------*

static void
goil_program_epilogue (C_Compiler & /* inLexique */,
                     const TC_UniqueArray <C_String> & /* inSourceFilesArray */) {
}

//---------------------------------------------------------------------------*
//                                                                           *
//                      M A I N    F O R    L I B P M                        *
//                                                                           *
//---------------------------------------------------------------------------*

int mainForLIBPM  (const int argc, const char * argv []) {
  bool verboseOptionOn = true ;
  PMSInt16 returnCode = 0 ; // No error
//--- Fix parameters for BDD package
  C_BDD::setHashMapSize (19) ;
  C_BDD::setITEcacheSize (17) ;
  C_BDD::setANDcacheSize (1) ;
  C_BDD::forAllOnBitsGreaterCacheSize (18) ;
  C_PrologueEpilogue::runPrologueActions () ;
  {
  //--- Input/output parameters
    const char * extensions [] = {"oil", "OIL", NULL} ;
    const char * helpMessages [] = {"an '.oil' source file", "an '.OIL' source file", NULL} ;
    TC_UniqueArray <C_String> sourceFilesArray ;
  //--- Analyze Command Line Options
    F_Analyze_CLI_Options (argc, argv,
                                 #ifndef DO_NOT_GENERATE_CHECKINGS
        "version 2.0b48" " [debug]",
      #else
        "version 2.0b48",
      #endif
                           sourceFilesArray,
                           extensions,
                           helpMessages) ;
  //--- Build galgas io object
    C_galgas_io * galgasIOptr = NULL ;
    macroMyNew (galgasIOptr, C_galgas_io (HERE)) ;
    C_Object::retain (galgasIOptr COMMA_HERE) ;
  //--- Common lexique object
    C_Compiler * commonLexique = NULL ;
    macroMyNew (commonLexique, C_Compiler (NULL, "", "", galgasIOptr COMMA_HERE)) ;
    C_Object::retain (commonLexique COMMA_HERE) ;
  //--- Ask Save On Close ? (Carbon and Windows SIOUX Only)
    #ifdef SIOUX_IS_IMPLEMENTED
      SIOUXSettings.asktosaveonclose = gOption_generic_5F_cli_5F_options_options_asktosaveonclose.mValue ;
    #endif
  //--- Enable 64 bit alloc debug ? Only if compiled in 64 bit and in debug mode
    #ifndef DO_NOT_GENERATE_CHECKINGS
      #ifdef __LP64__
        if (gOption_generic_5F_cli_5F_options_enable_5F_allocation_5F_debugging.mValue) {
          enableAllocDebugFor64BitTool () ;
        }
      #endif
    #endif
    try{
      verboseOptionOn = gOption_galgas_5F_cli_5F_options_verbose_5F_output.mValue ;
      goil_program_prologue (* commonLexique, sourceFilesArray) ;
      for (PMSInt32 i=0 ; i<sourceFilesArray.count () ; i++) {
        const C_String fileExtension = sourceFilesArray (i COMMA_HERE).pathExtension () ;
        PMSInt16 r = 0 ;
          if (fileExtension.compare ("oil") == 0) {
          C_Compiler & inLexique = * commonLexique ;
          const GGS_string source (true, sourceFilesArray (i COMMA_HERE)) ;
          const GGS_location _here (inLexique) ;
          const GGS_lstring var_cas_inSourceFile (GGS_lstring::constructor_new (inLexique, source, _here COMMA_HERE)) ;
            const GGS_string _depExtension = GGS_string ("") ;
            const GGS_string _depPath = GGS_string ("") ;
            if (_depExtension.isBuilt () && _depPath.isBuilt ()) {
              C_Grammar_goil_5F_grammar::_performSourceFileParsing_ (inLexique,
                                            _depExtension.string (),
                                            _depPath.string (),
                                            NULL,
                                            var_cas_inSourceFile
                                            COMMA_SOURCE_FILE_AT_LINE (14)) ;
            }
          if (verboseOptionOn) {
            co << "Analysis of '" << sourceFilesArray (i COMMA_HERE).lastPathComponent () << "' completed. " ;
            switch (commonLexique->totalErrorCount ()) {
            case 0 :
              co << "No error, " ;
              break ;
            case 1 :
              co << "1 error, " ;
              returnCode = 1 ; // Error code
              break ;
            default :
              co << cStringWithSigned (commonLexique->totalErrorCount ()) << " errors, " ;
              returnCode = 1 ; // Error code
              break ;
            }
            switch (commonLexique->totalWarningCount ()) {
            case 0 :
              co << "no warning" ;
              break ;
            case 1 :
              co << "1 warning" ;
              break ;
            default :
              co << cStringWithSigned (commonLexique->totalWarningCount ()) << " warnings" ;
              break ;
            }
            if (verboseOptionOn || ((commonLexique->totalErrorCount () + commonLexique->totalWarningCount ()) > 0)) {
              co << ".\n" ;
            }
          }
          }else if (fileExtension.compare ("OIL") == 0) {
          C_Compiler & inLexique = * commonLexique ;
          const GGS_string source (true, sourceFilesArray (i COMMA_HERE)) ;
          const GGS_location _here (inLexique) ;
          const GGS_lstring var_cas_inSourceFile (GGS_lstring::constructor_new (inLexique, source, _here COMMA_HERE)) ;
            const GGS_string _depExtension = GGS_string ("") ;
            const GGS_string _depPath = GGS_string ("") ;
            if (_depExtension.isBuilt () && _depPath.isBuilt ()) {
              C_Grammar_goil_5F_grammar::_performSourceFileParsing_ (inLexique,
                                            _depExtension.string (),
                                            _depPath.string (),
                                            NULL,
                                            var_cas_inSourceFile
                                            COMMA_SOURCE_FILE_AT_LINE (18)) ;
            }
          if (verboseOptionOn) {
            co << "Analysis of '" << sourceFilesArray (i COMMA_HERE).lastPathComponent () << "' completed. " ;
            switch (commonLexique->totalErrorCount ()) {
            case 0 :
              co << "No error, " ;
              break ;
            case 1 :
              co << "1 error, " ;
              returnCode = 1 ; // Error code
              break ;
            default :
              co << cStringWithSigned (commonLexique->totalErrorCount ()) << " errors, " ;
              returnCode = 1 ; // Error code
              break ;
            }
            switch (commonLexique->totalWarningCount ()) {
            case 0 :
              co << "no warning" ;
              break ;
            case 1 :
              co << "1 warning" ;
              break ;
            default :
              co << cStringWithSigned (commonLexique->totalWarningCount ()) << " warnings" ;
              break ;
            }
            if (verboseOptionOn || ((commonLexique->totalErrorCount () + commonLexique->totalWarningCount ()) > 0)) {
              co << ".\n" ;
            }
          }
        }else{
          printf ("*** Error: unhandled extension for file '%s' ***\n", sourceFilesArray (i COMMA_HERE).cString (HERE)) ;
          r = 1 ;
        }
        if (r != 0) {
          returnCode = r ;
        }
      }
    //--- Error or warnings ?
      if (commonLexique->totalErrorCount () > 0) {
        returnCode = 1 ; // Error code
      }else if (commonLexique->totalWarningCount () > 0) {
        if (gOption_galgas_5F_cli_5F_options_treat_5F_warnings_5F_as_5F_error.mValue) {
          returnCode = 1 ; // Error code
          if (verboseOptionOn) {
            printf ("** Note: warnings are treated as errors. **\n") ;
          }
        }
      }
    //--- Epilogue
      goil_program_epilogue (* commonLexique, sourceFilesArray) ;
    }catch (const M_STD_NAMESPACE exception & e) {
      F_default_display_exception (e) ;
      returnCode = 1 ; // Error code
    }catch (...) {
      throw ;
    }
    macroReleaseObject (galgasIOptr) ;
    macroReleaseObject (commonLexique) ;
  }
  C_PrologueEpilogue::runEpilogueActions () ;
  #ifndef DO_NOT_GENERATE_CHECKINGS
    C_Object::checkAllObjectsHaveBeenReleased () ;
  #endif
  displayAllocationStats () ;
  displayAllocatedBlockSizeStats () ;
  displayAllocatedBlocksInfo () ;
  return returnCode ;
}

//--- START OF USER ZONE 2


//--- END OF USER ZONE 2


