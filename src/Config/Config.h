﻿/******************************************************************************
*                                                                             *
*                                                                             *
* Notepad3                                                                    *
*                                                                             *
* Config.h                                                                    *
*   Methods to read and write configuration                                   *
*                                                                             *
*                                                  (c) Rizonesoft 2008-2019   *
*                                                    https://rizonesoft.com   *
*                                                                             *
*                                                                             *
*******************************************************************************/
#pragma once
#ifndef _NP3_CONFIG_H_
#define _NP3_CONFIG_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "TypeDefs.h"
#include "Helpers.h"

//==== Ini-File Handling =============================================

bool FindIniFile();
int  TestIniFile();
bool CreateIniFile();
bool CreateIniFileEx(LPCWSTR lpszIniFile);

void LoadSettings();
void LoadFlags();

bool OpenSettingsFile();
bool SaveSettings(bool);
bool CloseSettingsFile();

// ----------------------------------------------------------------------------

bool LoadIniFile(LPCWSTR lpIniFilePath);
bool SaveIniFile(LPCWSTR lpIniFilePath);
void ReleaseIniFile();

size_t IniSectionGetString(LPCWSTR lpSectionName, LPCWSTR lpKeyName, LPCWSTR lpDefault, 
                           LPWSTR lpReturnedString, size_t cchReturnedString);
int IniSectionGetInt(LPCWSTR lpSectionName, LPCWSTR lpKeyName, int iDefault);
double IniSectionGetDouble(LPCWSTR lpSectionName, LPCWSTR lpKeyName, double dDefault);
bool IniSectionGetBool(LPCWSTR lpSectionName, LPCWSTR lpKeyName, bool bDefault);

inline DocPos IniSectionGetPos(LPCWSTR lpSectionName, LPCWSTR lpKeyName, DocPos posDefault) {
  return (DocPos)IniSectionGetInt(lpSectionName, lpKeyName, (MBWC_DocPos_Cast)posDefault);
}

// ----------------------------------------------------------------------------

bool IniSectionSetString(LPCWSTR lpSectionName, LPCWSTR lpKeyName, LPCWSTR lpString);
bool IniSectionSetInt(LPCWSTR lpSectionName, LPCWSTR lpKeyName, int iValue);
bool IniSectionSetHex(LPCWSTR lpSectionName, LPCWSTR lpKeyName, int iValue);
bool IniSectionSetDouble(LPCWSTR lpSectionName, LPCWSTR lpKeyName, double dValue);
bool IniSectionSetBool(LPCWSTR lpSectionName, LPCWSTR lpName, bool bValue);

inline bool IniSectionSetPos(LPCWSTR lpSectionName, LPCWSTR lpKeyName, DocPos posValue) {
  return IniSectionSetInt(lpSectionName, lpKeyName, (MBWC_DocPos_Cast)posValue);
}

// ----------------------------------------------------------------------------

//  IniSectionDeleteValue():
//
//  lpSectionName   Section to delete key from, or if
//                  a_pKey is NULL, the section to remove.
//  lpKeyName       Key to remove from the section.Set to
//                  NULL to remove the entire section.
//  bRemoveEmpty    If the section is empty after this key has
//                  been deleted, should the empty section be removed ?
//
bool IniSectionDelete(LPCWSTR lpSectionName, LPCWSTR lpKeyName, bool bRemoveEmpty);
bool IniSectionClear(LPCWSTR lpSectionName, bool bRemoveEmpty);
bool IniClearAllSections(LPCWSTR lpPrefix, bool bRemoveEmpty);

// ----------------------------------------------------------------------------

// ==========================================
// open file , get/set value, save(set) file 
// ==========================================

size_t IniFileGetString(LPCWSTR lpFilePath, LPCWSTR lpSectionName, LPCWSTR lpKeyName, LPCWSTR lpDefault,
                        LPWSTR lpReturnedString, size_t cchReturnedString);
bool  IniFileSetString(LPCWSTR lpFilePath, LPCWSTR lpSectionName, LPCWSTR lpKeyName, LPCWSTR lpString);

int  IniFileGetInt(LPCWSTR lpFilePath, LPCWSTR lpSectionName, LPCWSTR lpKeyName, int iDefault);
bool IniFileSetInt(LPCWSTR lpFilePath, LPCWSTR lpSectionName, LPCWSTR lpKeyName, int iValue);

bool IniFileGetBool(LPCWSTR lpFilePath, LPCWSTR lpSectionName, LPCWSTR lpKeyName, bool bDefault);
bool IniFileSetBool(LPCWSTR lpFilePath, LPCWSTR lpSectionName, LPCWSTR lpKeyName, bool bValue);

//  IniFileDeleteValue():
//
//  lpSectionName   Section to delete key from, or if
//                  a_pKey is NULL, the section to remove.
//  lpKeyName       Key to remove from the section.Set to
//                  NULL to remove the entire section.
//  bRemoveEmpty    If the section is empty after this key has
//                  been deleted, should the empty section be removed ?
//
bool IniFileDelete(LPCWSTR lpFilePath, LPCWSTR lpSectionName, LPCWSTR lpKeyName, bool bRemoveEmpty);

//  IniFileIterateSection():
//
typedef void (CALLBACK* IterSectionFunc_t)(LPCWSTR key, LPCWSTR value);
bool IniFileIterateSection(LPCWSTR lpFilePath, LPCWSTR lpSectionName, IterSectionFunc_t callBack);

//==== MRU Functions ==========================================================

LPMRULIST MRU_Create(LPCWSTR pszRegKey, int iFlags, int iSize);
bool      MRU_Destroy(LPMRULIST pmru);
bool      MRU_Add(LPMRULIST pmru, LPCWSTR pszNew, cpi_enc_t iEnc, DocPos iPos, LPCWSTR pszBookMarks);
bool      MRU_FindFile(LPMRULIST pmru, LPCWSTR pszFile, int* iIndex);
bool      MRU_AddFile(LPMRULIST pmru, LPCWSTR pszFile, bool, bool, cpi_enc_t iEnc, DocPos iPos, LPCWSTR pszBookMarks);
bool      MRU_Delete(LPMRULIST pmru, int iIndex);
bool      MRU_Empty(LPMRULIST pmru);
int       MRU_Enum(LPMRULIST pmru, int iIndex, LPWSTR pszItem, int cchItem);
bool      MRU_Load(LPMRULIST pmru);
bool      MRU_Save(LPMRULIST pmru);
bool      MRU_MergeSave(LPMRULIST pmru, bool, bool, bool);
#define   MRU_Count(pmru) MRU_Enum((pmru), 0, NULL, 0)

// ----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif


#endif //_NP3_CONFIG_H_
