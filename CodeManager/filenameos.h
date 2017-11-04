#pragma once
#include <vector>
#include <iostream>
#include <string.h>

using namespace std;

typedef struct _VOLUME_INFO
{
	TCHAR    chFlag;
	DWORD    dwDiskNumber;
}VOLUME_INFO, *PVOLUME_INFO;

//获取硬盘信息
BOOL GetVolumeInfo(IN TCHAR chFlag, OUT PVOLUME_INFO pVolumeInfo);

string Trim(const string &str, const char* szBlank = NULL);

//去除指定字符串
char* _cdecl GetPointStr(const char* str, int pos, char* step);

//便利指定文件夹文件
void TraversalFile(std::string strFilePath, std::vector<CString>& arrFilePath);

//获取文件文件夹
//template<class TypeName>
//TypeName GetFileDirectory(TypeName strFilePath);

std::string GetFileDirectory(std::string strFilePath);

//切割字符串
void strSplit(const string & strInput, vector<std::string> & arrStr, char chSep = ',', bool bRemovePair = false);