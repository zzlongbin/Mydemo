// ATLSimpleObject.cpp: CATLSimpleObject 的实现

#include "pch.h"
#include "ATLSimpleObject.h"


#include <windows.h>
#include <stdlib.h>

#include "comutil.h"'
#pragma  comment(lib,  "comsuppw.lib")




STDMETHODIMP  CATLSimpleObject::OpenSerial(BSTR *COM )
{
	std::string ComStr = _com_util::ConvertBSTRToString(*COM);

	file = fopen("log.txt", "a");

	if (file == NULL) {
		
		char cmd[1024] = { '\0' };
		char buffer[1024] = { '\0' };

		snprintf(cmd, 1024, "Error opening log.txt file");
		snprintf(buffer, 1024, "echo  [%s] >> LogBack.txt", cmd);
		system(buffer);
	
		return S_FALSE;
	}


	fprintf(file, "串口: %s\n", ComStr.c_str());

	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };
	WCHAR iTempChar[255];
	int ret = 0;
	mbstowcs(iTempChar, ComStr.c_str(), 255); // 多字节转宽字节

	// 打开串口
	//hSerial = CreateFile(_T("COM1"), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	hSerial = CreateFile(iTempChar, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hSerial == INVALID_HANDLE_VALUE) {
		// 处理错误
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			// 串口不存在
			fprintf(file, "%s\n", "串口不存在");
		}
		else {
			// 其他错误
			fprintf(file, "%s\n", "其它错误");
		}
		return S_FALSE;
	}

	// 配置串口参数
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	ret = GetCommState(hSerial, &dcbSerialParams);

	dcbSerialParams.BaudRate = CBR_115200;      // 波特率
	dcbSerialParams.ByteSize = 8;              // 数据位
	dcbSerialParams.StopBits = ONE5STOPBITS;     // 停止位
	dcbSerialParams.Parity = NOPARITY;         // 校验位

	ret = SetCommState(hSerial, &dcbSerialParams);
	if (ret == 0)
	{
		fprintf(file, "%s\n", "SetCommState failed ");
	}
	
		// 设置读写超时时间
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	ret = SetCommTimeouts(hSerial, &timeouts);

	if (ret == 0)
	{
		fprintf(file, "%s\n", "SetCommTimeouts failed ");
	}


	fprintf(file, "%s\n", "打开串口成功");
	fflush(file);


	return S_OK;
}

STDMETHODIMP  CATLSimpleObject::CloseSerial()
{
	CloseHandle(hSerial);
	return S_OK;
}

STDMETHODIMP  CATLSimpleObject::WriteSerial(BSTR*  WriteData, LONG len)
{
	// 在这里可以进行读写串口的操作
	std::string ComStr = _com_util::ConvertBSTRToString(*WriteData);
	unsigned char * m_WriteData = (unsigned char*)ComStr.c_str();


	DWORD bytesSent;

	fprintf(file, "%s", "WriteData is");
	for (int i = 0; i < len; i++)
	{
		fprintf(file, "%02x", m_WriteData[i]);
	}
	fprintf(file, "\n");
	fflush(file);

	if (!WriteFile(hSerial, m_WriteData, len, &bytesSent, NULL)) {

		fprintf(file, "%s\n", "WriteFile failed");
		CloseHandle(hSerial);
		return 1;
	}


	fprintf(file, "%s\n", "WriteFile success");
	fflush(file);
	return 0;
}

STDMETHODIMP  CATLSimpleObject::ReadSerial(BSTR* ReadData )
{
	unsigned char buffer[256] = { '\0' };
	unsigned char m_ReadData[256] = { '\0' };
	DWORD bytesRead;
	if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
	{
		fprintf(file, "%s", "ReadFile error CloseHandle");
		CloseHandle(hSerial);
		return 1;
	}
	
	memcpy(m_ReadData, buffer, bytesRead);

	*ReadData = _com_util::ConvertStringToBSTR((char* )m_ReadData);

	fprintf(file, "%s", "ReadSerial Success  data is");
	for (int i = 0; i < bytesRead; i++)
	{
		fprintf(file, "%02x", m_ReadData[i]);
	}
	fprintf(file, "\n");
	fflush(file);

	return 0;
}



// CATLSimpleObject

