#pragma once

#include<Windows.h>
#include<tchar.h>
#include<stdio.h>
#include<mmsystem.h> //mciSendString的头文件
//#include"resource.h" 

#pragma comment(lib,"winmm.lib") 
BOOL FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter);
BOOL FolderExists(char* Path);
void GetDir(char *DIRFile);
void IsYouComeBack();
void SetSchtasks();
