# Microsoft Developer Studio Project File - Name="bsatestfile" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=bsatestfile - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bsatestfile.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bsatestfile.mak" CFG="bsatestfile - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bsatestfile - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "bsatestfile - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bsatestfile - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "../" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "bsatestfile - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
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

# Name "bsatestfile - Win32 Release"
# Name "bsatestfile - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\csvfile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\filebuffer.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obcallback.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obconfigentry.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obconfigfile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\oberror.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\oberrorhandler.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obfile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\oblogfile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obmemfile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obptrarray.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obtime.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\obutils.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\sstring.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\textutils.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\common\zlib\zdll.lib
# End Source File
# End Group
# Begin Group "BsaFile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bsafile\obbsafile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\bsafile\obbsafilerecord.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\bsafile\obbsafolder.cpp
# SUBTRACT CPP /YX
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bsafile\obresourcefile.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcefolder.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcehandler.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourceinstance.cpp
# SUBTRACT CPP /YX
# End Source File
# End Group
# Begin Source File

SOURCE=.\bsatestfile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Common."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\csvfile.h
# End Source File
# Begin Source File

SOURCE=..\common\dl_map.h
# End Source File
# Begin Source File

SOURCE=..\common\filebuffer.h
# End Source File
# Begin Source File

SOURCE=..\common\obarray.h
# End Source File
# Begin Source File

SOURCE=..\common\obblockallocator.h
# End Source File
# Begin Source File

SOURCE=..\common\obcallback.h
# End Source File
# Begin Source File

SOURCE=..\common\obconfigentry.h
# End Source File
# Begin Source File

SOURCE=..\common\obconfigfile.h
# End Source File
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

SOURCE=..\common\obsimplemap.h
# End Source File
# Begin Source File

SOURCE=..\common\obtime.h
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
# Begin Group "BsaFile."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bsafile\obbsafile.h
# End Source File
# Begin Source File

SOURCE=..\bsafile\obbsafilerecord.h
# End Source File
# Begin Source File

SOURCE=..\bsafile\obbsafolder.h
# End Source File
# End Group
# Begin Group "Resources."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bsafile\obresourcebase.h
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcefile.h
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcefolder.h
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcehandler.h
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourceinstance.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\bsatestfile.log
# End Source File
# End Target
# End Project
