#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <winioctl.h>

using namespace std;

char* volName = "e:\\";		//	驱动盘名称
HANDLE hVol;				//	用于存储驱动盘句柄
USN_JOURNAL_DATA UsnInfo;	//	用于存储USN日志的基本信息
#define BUF_LEN 4096
