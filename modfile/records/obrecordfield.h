/*===========================================================================
 *
 * File:	ObRecordfield.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 24, 2006
 *
 * Records will be considered to be composed of a number of fields 
 * for the purposes of representing them in the form of strings.
 *
 *=========================================================================*/
#ifndef __OBRECORDFIELD_H
#define __OBRECORDFIELD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/obtypes.h"
  #include "../obfields.h"
  #include "../../common/dl_map.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Record field flags */
  #define OB_RECFIELD_FLAG_LARGE	1	/* Possibly large amount of data in field */
  #define OB_RECFIELD_FLAG_INEXACT	2	/* Cannot be expressed exactly in string form */
  #define OB_RECFIELD_FLAG_NOLIST	4	/* Is not output in lists by default */
  #define OB_RECFIELD_FLAG_NOCSV	8	/* Is not input/output to CSV files by default */
  #define OB_RECFIELD_FLAG_ALNUM	16	/* Must be alpha-numeric */

	/* Shortcuts */
  #define OBRF_NOCSV OB_RECFIELD_FLAG_NOCSV
  #define OBRF_ALNUM OB_RECFIELD_FLAG_ALNUM

	/* Macros to define/declare a compare field method */
  #define DECLARE_OBCOMPFIELD(Name)  int Name (CObRecord* pRecord, long Reserved = 0);
  #define BEGIN_OBCOMPFIELD(Name)    int Name (CObRecord* pRecord, long Reserved) {
  #define END_OBCOMPFIELD()          return (0); }

  #define DEFINE_OBCOMPFIELDINT(Class, Name, Function) \
	int Class::Name (CObRecord* pRecord, long Reserved) { \
		if (pRecord == NULL) return (1); \
		Class* pRecord1 = ObCastClass(Class, pRecord); \
		if (pRecord1 == NULL) return (1); \
		return (int)this->Function() - (int) pRecord1->Function(); }

  #define DEFINE_OBCOMPFIELDDWORD(Class, Name, Function) \
	int Class::Name (CObRecord* pRecord, long Reserved) { \
		if (pRecord == NULL) return (1); \
		Class* pRecord1 = ObCastClass(Class, pRecord); \
		if (pRecord1 == NULL) return (1); \
		dword Value1 = (dword) this->Function(); \
		dword Value2 = (dword) pRecord1->Function(); \
		if (Value1 == Value2) return (0); \
		if (Value1 > Value2)  return (1); \
		return (-1); }

  #define DEFINE_OBCOMPFIELDFLOAT(Class, Name, Function, Digits) \
	int Class::Name (CObRecord* pRecord, long Reserved) { \
		if (pRecord == NULL) return (1); \
		Class* pRecord1 = ObCastClass(Class, pRecord); \
		if (pRecord1 == NULL) return (1); \
		return (int)( ( ((float)this->Function()) - ((float)pRecord1->Function()) )  * Digits); }

  #define DEFINE_OBCOMPFIELDSTRING(Class, Name, Function) \
	int Class::Name (CObRecord* pRecord, long Reserved) { \
		if (pRecord == NULL) return (1); \
		Class* pRecord1 = ObCastClass(Class, pRecord); \
		if (pRecord1 == NULL) return (1); \
		return SafeStringCompare((const char *)this->Function(), (const char *)pRecord1->Function(), true); }

  #define DEFINE_OBCOMPFIELDEDITORID(Class, Name, Function) \
	int Class::Name (CObRecord* pRecord, long Reserved) { \
		if (pRecord == NULL) return (1); \
		Class* pRecord1 = ObCastClass(Class, pRecord); \
		if (pRecord1 == NULL) return (1); \
		if (m_pParent != NULL && pRecord1 != NULL) { \
			return SafeStringCompare(m_pParent->GetEditorID(Function()), m_pParent->GetEditorID(pRecord1->Function()), true); } \
        return (1); } \

  #define DEFINE_OBCOMPFIELD(Name, Function)    int Name (CObRecord* pRecord, long Reserved) {\
							return (Function); }
  #define BEGIN_OBCOMPFIELD(Name)    int Name (CObRecord* pRecord, long Reserved) {
  #define END_OBCOMPFIELD()          return (0); }

	/* Macros to define/declare a get field method */
  #define DECLARE_OBGETFIELD(Name)  bool Name (CSString& String, long Reserved = 0);
  #define BEGIN_OBGETFIELD(Name)    bool Name (CSString& String, long Reserved) {
  #define END_OBGETFIELD()          return (true); }

  #define DEFINE_OBGETFIELD(Name, Function)    bool Name (CSString& String, long Reserved) {\
							Function; return (true); }

	/* Macros to define/declare a set field method */
  #define DECLARE_OBSETFIELD(Name)  bool Name (const SSCHAR* pString, long Reserved = 0);
  #define BEGIN_OBSETFIELD(Name)    bool Name (const SSCHAR* pString, long Reserved) {
  #define END_OBSETFIELD()          return (true); }

  #define DEFINE_OBSETFIELD(Name, Function)    bool Name (const SSCHAR* pString, long Reserved) {\
							Function; return (true); }

	/* Combination definitions */
  #define DECLARE_OBFIELD(Suffix) \
	bool Get##Suffix     (CSString& String, long Reserved = 0); \
	int  Compare##Suffix (CObRecord* pRecord, long Reserved = 0); \
	bool Set##Suffix     (const SSCHAR* pString, long Reserved = 0); 	 

	/* Define a static class array to hold the field data */
  #define DECLARE_OBFIELDMAP() public: \
	static  const obrecfieldmap_t  s_FieldMap; \
	static  const obrecfield_t     s_Fields[]; \
	virtual const obrecfieldmap_t* GetFieldMap (void) const { return (&s_FieldMap); } \
	virtual const obrecfield_t*    GetFields   (void) const { return (&s_Fields[0]); } \
	virtual const obrecfield_t*    FindField   (const obrecfieldid_t FieldID);

  #define BEGIN_OBFIELDBASEMAP(Class) \
        const obrecfield_t*   Class::FindField (const obrecfieldid_t FieldID) { \
		static CObRecFieldIDMap   s_FieldIDMap; \
		static bool s_Init = InitializeFieldMap(s_FieldIDMap); \
		return s_FieldIDMap.Lookup(FieldID); \
	} \
  	const obrecfieldmap_t Class::s_FieldMap = { NULL, Class::s_Fields }; \
	const obrecfield_t    Class::s_Fields[] = { 

  #define BEGIN_OBFIELDMAP(Class, BaseClass) \
          const obrecfield_t*   Class::FindField (const obrecfieldid_t FieldID) { \
		static CObRecFieldIDMap   s_FieldIDMap; \
		static bool s_Init = InitializeFieldMap(s_FieldIDMap); \
		return s_FieldIDMap.Lookup(FieldID); \
	} \
	const obrecfieldmap_t Class::s_FieldMap = { &BaseClass::s_FieldMap, Class::s_Fields }; \
	const obrecfield_t    Class::s_Fields[] = { 

  #define ADD_OBFIELDMAP(Name, ID, Flags, GetMethod, SetMethod, CompareMethod) { Name, ID, Flags, (FNOBGETRECORDFIELD) GetMethod, (FNOBSETRECORDFIELD) SetMethod,  (FNOBCOMPRECORDFIELD) CompareMethod},
  #define ADD_OBFIELDALL(Name, ID, Flags, Class, AllSuffix) { Name, ID, Flags, (FNOBGETRECORDFIELD) &Class::Get##AllSuffix, (FNOBSETRECORDFIELD) &Class::Set##AllSuffix,  (FNOBCOMPRECORDFIELD) &Class::Compare##AllSuffix },

  #define END_OBFIELDMAP() { NULL, OB_FIELD_NONE, 0, NULL, NULL } };

/*===========================================================================
 *		End of Definitions
 *========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definition */
  class CObRecord;
  
	/* Define the type of the field get/set methods */
  typedef bool (CObRecord::*FNOBGETRECORDFIELD)  (CSString&, long); 
  typedef bool (CObRecord::*FNOBSETRECORDFIELD)  (const SSCHAR* pString, long); 
  typedef int  (CObRecord::*FNOBCOMPRECORDFIELD) (CObRecord* pRecord, long); 

	/* Holds the information on a single field */
  struct obrecfield_t { 
	const char*		pName;		/* Short descriptive name */
	obrecfieldid_t		FieldID;	/* Unique field identifier */
	dword			Flags;		/* Field parameters */
	FNOBGETRECORDFIELD	GetMethod;
	FNOBSETRECORDFIELD	SetMethod;
	FNOBCOMPRECORDFIELD	CompareMethod;

	bool IsLarge   (void) const { return ((Flags & OB_RECFIELD_FLAG_LARGE)   != 0); }
	bool IsInexact (void) const { return ((Flags & OB_RECFIELD_FLAG_INEXACT) != 0); }
	bool IsNoList  (void) const { return ((Flags & OB_RECFIELD_FLAG_NOLIST)  != 0); }
	bool IsNoCSV   (void) const { return ((Flags & OB_RECFIELD_FLAG_NOCSV)   != 0); }
	bool IsAlNum   (void) const { return ((Flags & OB_RECFIELD_FLAG_ALNUM)   != 0); }
   };  

	/* Holds a reference to a field pointer to a class and its base class */
  struct obrecfieldmap_t {
  	const obrecfieldmap_t* pBaseFieldMap;
	const obrecfield_t*    pField;
   };

  typedef TGenRefPtrMap<CSString,       obrecfield_t, const SSCHAR*>  CObRecFieldNameMap;
  typedef TGenRefPtrMap<obrecfieldid_t, obrecfield_t, obrecfieldid_t> CObRecFieldIDMap;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRecordfield.H
 *=========================================================================*/
