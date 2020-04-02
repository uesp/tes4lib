# Microsoft Developer Studio Project File - Name="oblibtest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=oblibtest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "oblibtest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oblibtest.mak" CFG="oblibtest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oblibtest - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "oblibtest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "oblibtest - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "../" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "oblibtest - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "../" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "oblibtest - Win32 Release"
# Name "oblibtest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\oberror.cpp
# End Source File
# Begin Source File

SOURCE=..\common\oberrorhandler.cpp
# End Source File
# Begin Source File

SOURCE=..\common\obfile.cpp
# End Source File
# Begin Source File

SOURCE=..\common\oblogfile.cpp
# End Source File
# Begin Source File

SOURCE=..\common\obmemfile.cpp
# End Source File
# Begin Source File

SOURCE=..\common\obptrarray.cpp
# End Source File
# Begin Source File

SOURCE=..\common\obutils.cpp
# End Source File
# Begin Source File

SOURCE=..\common\sstring.cpp
# End Source File
# Begin Source File

SOURCE=..\common\textutils.cpp
# End Source File
# End Group
# Begin Group "groups"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\groups\obgroup.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\groups\obgrupcont.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\groups\obtypegroup.cpp
# End Source File
# End Group
# Begin Group "records"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\records\obammorecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obapparecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obarmorecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obbasereccont.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obbaserecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obbookrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obclotrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obeffitemrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obenchrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obidrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obingrrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obitem1record.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obitem2record.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvlirecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obmiscrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obreccont.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obscptrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obsgstrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obspelrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obtes4record.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obweaprecord.cpp
# End Source File
# End Group
# Begin Group "subrecords"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\subrecords\obefitsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obenitsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obhedrsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obnamesubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrecname.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obscitsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obspitsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obstring1subrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obstringsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obsubreccont.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obsubrecord.cpp
# End Source File
# End Group
# Begin Group "test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\obtest.cpp
# End Source File
# Begin Source File

SOURCE=.\testammo.cpp
# End Source File
# Begin Source File

SOURCE=.\testappa.cpp
# End Source File
# Begin Source File

SOURCE=.\testarmo.cpp
# End Source File
# Begin Source File

SOURCE=.\testbook.cpp
# End Source File
# Begin Source File

SOURCE=.\testclot.cpp
# End Source File
# Begin Source File

SOURCE=.\testench.cpp
# End Source File
# Begin Source File

SOURCE=.\testlevi.cpp
# End Source File
# Begin Source File

SOURCE=.\testmisc.cpp
# End Source File
# Begin Source File

SOURCE=.\testrecord.cpp
# End Source File
# Begin Source File

SOURCE=.\testscpt.cpp
# End Source File
# Begin Source File

SOURCE=.\testsgst.cpp
# End Source File
# Begin Source File

SOURCE=.\testspel.cpp
# End Source File
# Begin Source File

SOURCE=.\testtes4.cpp
# End Source File
# Begin Source File

SOURCE=.\testweap.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\modfile\obespfile.cpp
# End Source File
# Begin Source File

SOURCE=.\oblibtest.cpp
# End Source File
# Begin Source File

SOURCE=..\common\zlib\zdll.exp
# End Source File
# Begin Source File

SOURCE=..\common\zlib\zdll.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "common."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\oberror.h
# End Source File
# Begin Source File

SOURCE=..\common\oberrorhandler.h
# End Source File
# Begin Source File

SOURCE=..\common\obfile.h
# End Source File
# Begin Source File

SOURCE=..\common\oblogfile.h
# End Source File
# Begin Source File

SOURCE=..\common\obmemfile.h
# End Source File
# Begin Source File

SOURCE=..\common\obplatform.h
# End Source File
# Begin Source File

SOURCE=..\common\obptrarray.h
# End Source File
# Begin Source File

SOURCE=..\common\obtypes.h
# End Source File
# Begin Source File

SOURCE=..\common\obutils.h
# End Source File
# Begin Source File

SOURCE=..\common\obversion.h
# End Source File
# Begin Source File

SOURCE=..\common\sstring.h
# End Source File
# Begin Source File

SOURCE=..\common\textutils.h
# End Source File
# Begin Source File

SOURCE=..\common\zlib\zconf.h
# End Source File
# Begin Source File

SOURCE=..\common\zlib\zlib.h
# End Source File
# End Group
# Begin Group "groups."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\groups\obgroup.h
# End Source File
# Begin Source File

SOURCE=..\modfile\groups\obgrupcont.h
# End Source File
# Begin Source File

SOURCE=..\modfile\groups\obtypegroup.h
# End Source File
# End Group
# Begin Group "records."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\records\obammorecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obapparecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obarmorecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obbasereccont.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obbaserecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obbookrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obclotrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obeffitemrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obenchrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obidrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obingrrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obitem1record.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obitem2record.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvlirecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obmiscrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obreccont.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obscptrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obsgstrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obspelrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obtes4record.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obweaprecord.h
# End Source File
# End Group
# Begin Group "subrecords."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\subrecords\obammodatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obappadatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obarmodatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obbookdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obbytesubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obclotdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obdwordsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obefitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obenitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obfloatsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obhedrsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obingrenitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obint64subrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\oblvlosubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obmiscdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obmoddefs.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obnamesubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrecname.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obschrsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obscitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obsgstdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obspitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obstring1subrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obstringsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obsubreccont.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obweapdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obwordsubrecord.h
# End Source File
# End Group
# Begin Group "test."

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\obtest.h
# End Source File
# Begin Source File

SOURCE=.\testammo.h
# End Source File
# Begin Source File

SOURCE=.\testappa.h
# End Source File
# Begin Source File

SOURCE=.\testarmo.h
# End Source File
# Begin Source File

SOURCE=.\testbook.h
# End Source File
# Begin Source File

SOURCE=.\testclot.h
# End Source File
# Begin Source File

SOURCE=.\testench.h
# End Source File
# Begin Source File

SOURCE=.\testlevi.h
# End Source File
# Begin Source File

SOURCE=.\testmisc.h
# End Source File
# Begin Source File

SOURCE=.\testrecord.h
# End Source File
# Begin Source File

SOURCE=.\testscpt.h
# End Source File
# Begin Source File

SOURCE=.\testsgst.h
# End Source File
# Begin Source File

SOURCE=.\testspel.h
# End Source File
# Begin Source File

SOURCE=.\testtes4.h
# End Source File
# Begin Source File

SOURCE=.\testweap.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\modfile\obespfile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\oblivtest.log
# End Source File
# End Target
# End Project
