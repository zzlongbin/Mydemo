// ConsoleApplication1.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include "ATLProject2_i.c"
#include "ATLProject2_i.h"
#include <windows.h>
#include <comsvcs.h>

#include "comutil.h"'
#pragma  comment(lib,  "comsuppw.lib")

int main()
{
    IATLSimpleObject* testAdd;
    if (CoInitialize(NULL) != S_OK)
    {
        std::cout << "��ʼ��COMʧ��" << std::endl;
        return -1;
    }


    HRESULT hResult = CoCreateInstance(CLSID_ATLSimpleObject, NULL, CLSCTX_INPROC_SERVER, IID_IATLSimpleObject, (void**)&testAdd);
    if (hResult != S_OK)
    {
        std::cout << "ʵ����C0Mʧ��" << std::endl;
        return -2;
    }
    long result;
    const wchar_t* str = L"COM7";
    const wchar_t* write = L"2131231";
    const wchar_t* read;
    BSTR bstr = SysAllocString(str);

    BSTR bstr1 = SysAllocString(write);
    BSTR bstr2;
    // ���BSTR�Ƿ�ɹ�����
    //if (bstr != NULL) {
    //    // �ڴ˴�ʹ��BSTR�����紫�ݸ�COM�ӿڻ�Win32 API����
    //    printf("create bstr failed");
    //    // �ͷ�BSTR
    //    SysFreeString(bstr);
    //}
    testAdd->OpenSerial(&bstr);
    //WriteSerial(BSTR* WriteData, LONG len);
    testAdd->WriteSerial(&bstr1, 14);
    testAdd->ReadSerial(&bstr2);
    char *data = _com_util::ConvertBSTRToString(bstr2);

    for (int i = 0; i < 7; i++)
    {
        printf("data %02x", data[i]);
    }
   
    Sleep(5000);
}

