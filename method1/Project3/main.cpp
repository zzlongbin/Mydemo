// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
        std::cout << "初始化COM失败" << std::endl;
        return -1;
    }


    HRESULT hResult = CoCreateInstance(CLSID_ATLSimpleObject, NULL, CLSCTX_INPROC_SERVER, IID_IATLSimpleObject, (void**)&testAdd);
    if (hResult != S_OK)
    {
        std::cout << "实例化C0M失败" << std::endl;
        return -2;
    }
    long result;
    const wchar_t* str = L"COM7";
    const wchar_t* write = L"2131231";
    const wchar_t* read;
    BSTR bstr = SysAllocString(str);

    BSTR bstr1 = SysAllocString(write);
    BSTR bstr2;
    // 检查BSTR是否成功创建
    //if (bstr != NULL) {
    //    // 在此处使用BSTR，例如传递给COM接口或Win32 API函数
    //    printf("create bstr failed");
    //    // 释放BSTR
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

