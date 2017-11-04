//#include <iostream>
//#include <Windows.h>
//#include <fstream>
//
////_CRT_SECURE_NO_WARNINGS
//using namespace std;
//
//char* volName = "e:\\";			// 驱动盘名称
//HANDLE hVol;					// 用于储存驱动盘句柄
//USN_JOURNAL_DATA UsnInfo;		// 用于储存USN日志的基本信息
//#define BUF_LEN 4096
//ofstream fout("i:\\log.txt");	// 用来将数据记录到文本，方便查看
//long counter = 0;
//
//int main()
//{
//	bool status;
//	bool isNTFS = false;
//	bool getHandleSuccess = false;
//	bool initUsnJournalSuccess = false;
//	char sysNameBuf[MAX_PATH] = { 0 };
//
//	status = GetVolumeInformationA(volName,	NULL,0,NULL,NULL,NULL,sysNameBuf,MAX_PATH);
//	if (0 != status)
//	{
//		printf("文件系统名: %s\n", sysNameBuf);
//		if (0 == strcmp(sysNameBuf, "NTFS"))
//		{
//			isNTFS = true;
//		}
//		else
//		{
//			printf("该驱动盘非NTFS格式\n");
//		}
//	}
//
//	if (isNTFS) 
//	{
//		char fileName[MAX_PATH];
//		fileName[0] = '\0';
//		strcpy(fileName, "\\\\.\\");				// 传入的文件名必须为\\.\C:的形式
//		strcat(fileName, volName);
//		string fileNameStr = (string)fileName;
//		fileNameStr.erase(fileNameStr.find_last_of(":") + 1);
//		printf("驱动盘地址: %s\n", fileNameStr.data());
//		/*2.可以为0*//*3.必须包含有FILE_SHARE_WRITE*/	/*4.这里不需要*//*5.必须包含OPEN_EXISTING, CREATE_ALWAYS可能会导致错误*//*6.FILE_ATTRIBUTE_NORMAL可能会导致错误*/
//		hVol = CreateFileA(fileNameStr.data(),GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,	FILE_ATTRIBUTE_READONLY,NULL);		
//		if (INVALID_HANDLE_VALUE != hVol)
//		{
//			getHandleSuccess = true;
//		}
//		else 
//		{
//			printf("获取驱动盘句柄失败 —— handle:%x error:%d\n", hVol, GetLastError());
//		}
//	}
//
//	if (getHandleSuccess)
//	{
//		DWORD br;
//		CREATE_USN_JOURNAL_DATA cujd;
//		cujd.MaximumSize = 0;
//		cujd.AllocationDelta = 0;
//		status = DeviceIoControl(hVol,FSCTL_CREATE_USN_JOURNAL,	&cujd,sizeof(cujd),	NULL,0,	&br,NULL);
//		if (0 != status)
//		{
//			initUsnJournalSuccess = true;
//		}
//		else
//		{
//			printf("初始化USN日志文件失败 —— status:%x error:%d\n", status, GetLastError());
//		}
//
//	}
//
//	if (initUsnJournalSuccess) 
//	{
//		bool getBasicInfoSuccess = false;
//		DWORD br;
//		status = DeviceIoControl(hVol,FSCTL_QUERY_USN_JOURNAL,NULL,	0,&UsnInfo,sizeof(USN_JOURNAL_DATA),&br,NULL);
//		if (0 != status)
//		{
//			getBasicInfoSuccess = true;
//		}
//		else 
//		{
//			printf("获取USN日志基本信息失败 —— status:%x error:%d\n", status, GetLastError());
//		}
//
//		if (getBasicInfoSuccess) 
//		{
//			printf("UsnJournalID: %xI64\n", UsnInfo.UsnJournalID);
//			printf("lowUsn: %xI64\n", UsnInfo.FirstUsn);
//			printf("highUsn: %xI64\n", UsnInfo.NextUsn);
//
//			READ_USN_JOURNAL_DATA usnReadData;
//			usnReadData.UsnJournalID = UsnInfo.UsnJournalID;
//			//MFT_ENUM_DATA med;
//			//med.StartFileReferenceNumber = 0;
//			//med.LowUsn = 0;								//UsnInfo.FirstUsn; 这里经测试发现，如果用FirstUsn有时候不正确，导致获取到不完整的数据，还是直接写0好.
//			//med.HighUsn = UsnInfo.NextUsn;
//
//			CHAR buffer[BUF_LEN];						// 用于储存记录的缓冲,尽量足够地大
//			memset(buffer, 0, BUF_LEN);
//			DWORD usnDataSize;
//			PUSN_RECORD UsnRecord;
//
//			//while (0 != DeviceIoControl(hVol, /*IOCTL_DISK_GET_DRIVE_GEOMETRY*//*FSCTL_ENUM_USN_DATA*/FSCTL_READ_USN_JOURNAL, &med, sizeof(med), buffer, BUF_LEN, &usnDataSize, NULL))
//			while (0 != DeviceIoControl(hVol, /*IOCTL_DISK_GET_DRIVE_GEOMETRY*//*FSCTL_ENUM_USN_DATA*/FSCTL_READ_USN_JOURNAL, &usnReadData, sizeof(usnReadData), &buffer, BUF_LEN, &usnDataSize, NULL))
//			{
//				DWORD dwRetBytes = usnDataSize - sizeof(USN);
//				UsnRecord = (PUSN_RECORD)(((PCHAR)buffer) + sizeof(USN));		// 找到第一个USN记录
//				while (dwRetBytes>0) 
//				{
//					const int strLen = UsnRecord->FileNameLength;				// 打印获取到的信息
//					char fileName[MAX_PATH] = { 0 };
//					WideCharToMultiByte(CP_OEMCP, NULL, UsnRecord->FileName, strLen / 2, fileName, strLen, NULL, FALSE);
//					printf("FileName: %s\n", fileName);
//					printf("FileReferenceNumber: %xI64\n", UsnRecord->FileReferenceNumber);		// 下面两个file reference number可以用来获取文件的路径信息
//					printf("ParentFileReferenceNumber: %xI64\n", UsnRecord->ParentFileReferenceNumber);
//					printf("\n");
//					fout << "FileName:" << fileName << endl;
//					fout << "frn:" << UsnRecord->FileReferenceNumber << endl;
//					fout << "pfrn:" << UsnRecord->ParentFileReferenceNumber << endl;
//					fout << endl;
//					counter++;
//					DWORD recordLen = UsnRecord->RecordLength;
//					dwRetBytes -= recordLen;
//					UsnRecord = (PUSN_RECORD)(((PCHAR)UsnRecord) + recordLen);
//				}
//				//med.StartFileReferenceNumber = *(USN *)&buffer;		//获取下一页数据，MTF大概是分多页来储存的吧？
//				// Update starting USN for next call
//				usnReadData.StartUsn = *(USN *)&buffer;
//			}
//
//			printf("共%d个文件\n", counter);
//			fout << "共" << counter << "个文件" << endl;
//			fout << flush;
//			fout.close();
//		}
//
//		DELETE_USN_JOURNAL_DATA dujd;
//		dujd.UsnJournalID = UsnInfo.UsnJournalID;
//		dujd.DeleteFlags = USN_DELETE_FLAG_DELETE;
//
		//status = DeviceIoControl(hVol,	FSCTL_DELETE_USN_JOURNAL, &dujd, sizeof(dujd), NULL, 0, &br, NULL);
		//if (0 != status)
		//	printf("成功删除USN日志文件!\n");
		//else
		//	printf("删除USN日志文件失败 —— status:%x error:%d\n", status, GetLastError());
//	}
//
//	if (getHandleSuccess)
//		CloseHandle(hVol);
//	system("pause");
//	return 0;
//}