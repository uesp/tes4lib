# Microsoft Developer Studio Project File - Name="tes4lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=tes4lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tes4lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tes4lib.mak" CFG="tes4lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tes4lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "tes4lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tes4lib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "tes4lib - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "tes4lib - Win32 Release"
# Name "tes4lib - Win32 Debug"
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
# Begin Group "modfile"

# PROP Default_Filter ""
# Begin Group "subrecords"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\subrecords\obctdasubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obctdtsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obefitsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obenitsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obformidarraysubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obhedrsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obnamesubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obpgrlsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdgssubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdotsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdsdsubrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdwtsubrecord.cpp
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
# Begin Source File

SOURCE=..\modfile\subrecords\obwlstsubrecord.cpp
# End Source File
# End Group
# Begin Group "records"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\records\obachrrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obacrerecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obactirecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obalchrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obammorecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obaniorecord.cpp
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

SOURCE=..\modfile\records\obbsgnrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcellrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcheckrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obclmtrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obclotrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcontrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcrearecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obdialrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obdoorrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obeffitemrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obenchrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obfactrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obflorrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obidlerecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obidrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obinforecord.cpp
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

SOURCE=..\modfile\records\oblandrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblighrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblscrrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obltexrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvlcrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvlirecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvsprecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obmgefrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obmiscrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obnpcrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obpackrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obpgrdrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obqustrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obracerecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obreccont.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrefrrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obregnrecord.cpp
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

SOURCE=..\modfile\records\obwatrrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obweaprecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obwrldrecord.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obwthrrecord.cpp
# End Source File
# End Group
# Begin Group "groups"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\groups\obfilegroup.cpp
# End Source File
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
# Begin Group "handlers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\obmultirecordhandler.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\obsimplerecordhandler.cpp
# End Source File
# End Group
# Begin Group "compiler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\compiler\charclass.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\charclassarray.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\customcompiler.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\scansourcestring.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentable.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentablearray.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentableresult.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentablerow.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentype.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentypearray.cpp
# SUBTRACT CPP /YX
# End Source File
# End Group
# Begin Source File

SOURCE=..\modfile\obespfile.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\obexport.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\obfields.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\obmoddefs.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\obrecordcreate.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\obrectype.cpp
# End Source File
# Begin Source File

SOURCE=..\modfile\obundoitem.cpp
# End Source File
# End Group
# Begin Group "bsa"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bsafile\obbsafile.cpp
# End Source File
# Begin Source File

SOURCE=..\bsafile\obbsafilerecord.cpp
# End Source File
# Begin Source File

SOURCE=..\bsafile\obbsafolder.cpp
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcefile.cpp
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcefolder.cpp
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourcehandler.cpp
# End Source File
# Begin Source File

SOURCE=..\bsafile\obresourceinstance.cpp
# End Source File
# End Group
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
# Begin Group "modfile."

# PROP Default_Filter ""
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

SOURCE=..\modfile\subrecords\obatxtsubrecord.h
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

SOURCE=..\modfile\subrecords\obcntosubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obctdasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obctdtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obdnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obdwordsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obefitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obenamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obenit8subrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obenitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obfloatsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obformidarraysubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obformidsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obhedrsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obidledatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obingrenitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obint64subrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\oblighdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\oblnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\oblongsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\oblvlosubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obmgefdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obmiscdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obnamesubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obpgrlsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obpldtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obposanglesubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obpositionsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obptdtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obqstasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdgssubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdotsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdsdsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrdwtsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obrefrdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obschrsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obscitsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obscrosubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obsgstdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obsnamsubrecord.h
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

SOURCE=..\modfile\subrecords\obvnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obvtexsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obweapdatasubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obwlstsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obwordsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obwthrrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obxespsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obxlocsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obxnamsubrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\subrecords\obxtelsubrecord.h
# End Source File
# End Group
# Begin Group "records."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\records\obachrrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obacrerecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obactirecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obalchrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obammorecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obaniorecord.h
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

SOURCE=..\modfile\records\obbsgnrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcellrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcheckrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obclmtrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obclotrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcontrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obcrearecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obdialrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obdoorrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obeffitemrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obenchrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obfactrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obflorrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obidlerecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obidrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obinforecord.h
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

SOURCE=..\modfile\records\oblandrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblighrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblscrrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obltexrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvlcrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvlirecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\oblvsprecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obmgefrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obmiscrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obnpcrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obpackrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obpgrdrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obqustrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obracerecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obreccont.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrecordfield.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrecordmap.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obrefrrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obregnrecord.h
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

SOURCE=..\modfile\records\obwatrrecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obweaprecord.h
# End Source File
# Begin Source File

SOURCE=..\modfile\records\obwrldrecord.h
# End Source File
# End Group
# Begin Group "groups."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\groups\obblockgroup.h
# End Source File
# Begin Source File

SOURCE=..\modfile\groups\obfilegroup.h
# End Source File
# Begin Source File

SOURCE=..\modfile\groups\obformidgroup.h
# End Source File
# Begin Source File

SOURCE=..\modfile\groups\obgridgroup.h
# End Source File
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
# Begin Group "handlers."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\obmultirecordhandler.h
# End Source File
# Begin Source File

SOURCE=..\modfile\obrecordhandler.h
# End Source File
# Begin Source File

SOURCE=..\modfile\obsimplerecordhandler.h
# End Source File
# End Group
# Begin Group "compiler."

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modfile\compiler\charclass.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\charclassarray.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\customcompiler.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\scansource.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\scansourcestring.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentable.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentablearray.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentableresult.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentablerow.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentype.h
# End Source File
# Begin Source File

SOURCE=..\modfile\compiler\tokentypearray.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\modfile\obespfile.h
# End Source File
# Begin Source File

SOURCE=..\modfile\obexport.h
# End Source File
# Begin Source File

SOURCE=..\modfile\obfields.h
# End Source File
# Begin Source File

SOURCE=..\modfile\obmoddefs.h
# End Source File
# Begin Source File

SOURCE=..\modfile\obrectype.h
# End Source File
# Begin Source File

SOURCE=..\modfile\obundoitem.h
# End Source File
# End Group
# Begin Group "bsa."

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
# Begin Source File

SOURCE=.\tes4lib.h
# End Source File
# End Group
# End Target
# End Project
