/*===========================================================================
 *
 * File:	Obscriptfunction.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 17, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obscriptfunction.h"


/*===========================================================================
 *
 * Class CObScriptFunction Constructor
 *
 *=========================================================================*/
CObScriptFunction::CObScriptFunction() {
  m_Index         = -1;
  m_Flags         = 0;
  m_CustomFlags   = 0;
  m_NumParameters = 0;
  m_OpCode        = 0;

}
/*===========================================================================
 *		End of Class CObScriptFunction Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunction Method - void Destroy (void);
 *
 *=========================================================================*/
void CObScriptFunction::Destroy (void) {
  m_Name.Empty();
  m_ShortName.Empty();
  m_HelpText.Empty();

  m_Index         = -1;
  m_Flags         = 0;
  m_CustomFlags   = 0;
  m_NumParameters = 0;
  m_OpCode        = 0;
}
/*===========================================================================
 *		End of Class Method CObScriptFunction::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunction Method - bool ParseParameter (Buffer);
 *
 *=========================================================================*/
bool CObScriptFunction::ParseParameter (CSString& Buffer) {
  CSString Type;
  CSString Flags;

  if (m_NumParameters >= OB_FUNCTION_MAXPARAMS) {
    AddObGeneralError("Exceeded the maximum number of function parameters (%u)!", OB_FUNCTION_MAXPARAMS); 
    return (false);
  }

  Buffer.SeperateVarValueNQ(Type, Flags, ',', 0);

  ObFieldConvertShort(Type, m_Parameters[m_NumParameters].Type);

  if (Flags.CompareNoCase("Optional") == 0) {
    m_Parameters[m_NumParameters].Flags |= OB_FUNCPARAMFLAG_OPTIONAL;
  }

  ++m_NumParameters;
  return (true);
}
/*===========================================================================
 *		End of Class Method CObScriptFunction::ParseParameter()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunction Method - bool Read (File);
 *
 * Read a function definition from the given file.
 *
 *=========================================================================*/
bool CObScriptFunction::Read (CObFile& File) {
  CSString Buffer;
  CSString Variable;
  CSString Value;
  bool     Result;
  bool	   FlagResult;

  while (!File.IsEOF()) {
    Result = File.ReadLine(Buffer);
    if (!Result) return (false);

    Buffer.SeperateVarValueNQ(Variable, Value, '=', 0);

    if (Variable.CompareNoCase("name") == 0) {
      m_Name = Value;
    }
    else if (Variable.CompareNoCase("shortname") == 0) {
      m_ShortName = Value;
    }
    else if (Variable.CompareNoCase("helptext") == 0) {
      m_HelpText = Value;
    }
    else if (Variable.CompareNoCase("opcode") == 0) {
      ObFieldConvertWord(Value, m_OpCode);
    }
    else if (Variable.CompareNoCase("index") == 0) {
      ObFieldConvertInt(Value, m_Index);
    }
    else if (Variable.CompareNoCase("usesreference") == 0) {
      Result = ObFieldConvertBoolean(Value, FlagResult);
      if (Result && FlagResult) m_CustomFlags |= OB_FUNCFLAG_USESREF;
    }
    else if (Variable.CompareNoCase("flags") == 0) {
      ObFieldConvertDword(Value, m_Flags);
    }
    else if (Variable.CompareNoCase("numparams") == 0) {
	/* set from number of parameters read */
    }
    else if (strnicmp(Variable, "param", 5) == 0) {
      ParseParameter(Value);
    }
    else if (Variable.CompareNoCase("end") == 0) {
      return (true);
    }

  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObScriptFunction::Read()
 *=========================================================================*/

