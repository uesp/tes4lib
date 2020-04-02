# Microsoft Developer Studio Generated NMAKE File, Based on ObFileLib.dsp
!IF "$(CFG)" == ""
CFG=ObFileLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ObFileLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ObFileLib - Win32 Release" && "$(CFG)" != "ObFileLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ObFileLib.mak" CFG="ObFileLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ObFileLib - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ObFileLib - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ObFileLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ObFileLib.exe"


CLEAN :
	-@erase "$(INTDIR)\oberror.obj"
	-@erase "$(INTDIR)\oberrorhandler.obj"
	-@erase "$(INTDIR)\obfile.obj"
	-@erase "$(INTDIR)\obfiletest.obj"
	-@erase "$(INTDIR)\oblogfile.obj"
	-@erase "$(INTDIR)\sstring.obj"
	-@erase "$(INTDIR)\sstring_test.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ObFileLib.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ObFileLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObFileLib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\ObFileLib.pdb" /machine:I386 /out:"$(OUTDIR)\ObFileLib.exe" 
LINK32_OBJS= \
	"$(INTDIR)\oberror.obj" \
	"$(INTDIR)\oberrorhandler.obj" \
	"$(INTDIR)\obfile.obj" \
	"$(INTDIR)\obfiletest.obj" \
	"$(INTDIR)\sstring.obj" \
	"$(INTDIR)\oblogfile.obj" \
	"$(INTDIR)\sstring_test.obj"

"$(OUTDIR)\ObFileLib.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ObFileLib.exe" "$(OUTDIR)\ObFileLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\oberror.obj"
	-@erase "$(INTDIR)\oberror.sbr"
	-@erase "$(INTDIR)\oberrorhandler.obj"
	-@erase "$(INTDIR)\oberrorhandler.sbr"
	-@erase "$(INTDIR)\obfile.obj"
	-@erase "$(INTDIR)\obfile.sbr"
	-@erase "$(INTDIR)\obfiletest.obj"
	-@erase "$(INTDIR)\obfiletest.sbr"
	-@erase "$(INTDIR)\oblogfile.obj"
	-@erase "$(INTDIR)\oblogfile.sbr"
	-@erase "$(INTDIR)\sstring.obj"
	-@erase "$(INTDIR)\sstring.sbr"
	-@erase "$(INTDIR)\sstring_test.obj"
	-@erase "$(INTDIR)\sstring_test.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ObFileLib.bsc"
	-@erase "$(OUTDIR)\ObFileLib.exe"
	-@erase "$(OUTDIR)\ObFileLib.ilk"
	-@erase "$(OUTDIR)\ObFileLib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ObFileLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ObFileLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\oberror.sbr" \
	"$(INTDIR)\oberrorhandler.sbr" \
	"$(INTDIR)\obfile.sbr" \
	"$(INTDIR)\obfiletest.sbr" \
	"$(INTDIR)\sstring.sbr" \
	"$(INTDIR)\oblogfile.sbr" \
	"$(INTDIR)\sstring_test.sbr"

"$(OUTDIR)\ObFileLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\ObFileLib.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ObFileLib.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\oberror.obj" \
	"$(INTDIR)\oberrorhandler.obj" \
	"$(INTDIR)\obfile.obj" \
	"$(INTDIR)\obfiletest.obj" \
	"$(INTDIR)\sstring.obj" \
	"$(INTDIR)\oblogfile.obj" \
	"$(INTDIR)\sstring_test.obj"

"$(OUTDIR)\ObFileLib.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ObFileLib.dep")
!INCLUDE "ObFileLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "ObFileLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ObFileLib - Win32 Release" || "$(CFG)" == "ObFileLib - Win32 Debug"
SOURCE=.\common\oberror.cpp

!IF  "$(CFG)" == "ObFileLib - Win32 Release"


"$(INTDIR)\oberror.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"


"$(INTDIR)\oberror.obj"	"$(INTDIR)\oberror.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\common\oberrorhandler.cpp

!IF  "$(CFG)" == "ObFileLib - Win32 Release"


"$(INTDIR)\oberrorhandler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"


"$(INTDIR)\oberrorhandler.obj"	"$(INTDIR)\oberrorhandler.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\common\obfile.cpp

!IF  "$(CFG)" == "ObFileLib - Win32 Release"


"$(INTDIR)\obfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"


"$(INTDIR)\obfile.obj"	"$(INTDIR)\obfile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\obfiletest.cpp

!IF  "$(CFG)" == "ObFileLib - Win32 Release"


"$(INTDIR)\obfiletest.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"


"$(INTDIR)\obfiletest.obj"	"$(INTDIR)\obfiletest.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\common\oblogfile.cpp

!IF  "$(CFG)" == "ObFileLib - Win32 Release"


"$(INTDIR)\oblogfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"


"$(INTDIR)\oblogfile.obj"	"$(INTDIR)\oblogfile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\common\sstring.cpp

!IF  "$(CFG)" == "ObFileLib - Win32 Release"


"$(INTDIR)\sstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"


"$(INTDIR)\sstring.obj"	"$(INTDIR)\sstring.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\common\test\sstring_test.cpp

!IF  "$(CFG)" == "ObFileLib - Win32 Release"


"$(INTDIR)\sstring_test.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ObFileLib - Win32 Debug"


"$(INTDIR)\sstring_test.obj"	"$(INTDIR)\sstring_test.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

