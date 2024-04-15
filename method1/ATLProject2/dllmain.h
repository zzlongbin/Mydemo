// dllmain.h: 模块类的声明。

class CATLProject2Module : public ATL::CAtlDllModuleT< CATLProject2Module >
{
public :
	DECLARE_LIBID(LIBID_ATLProject2Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROJECT2, "{4310cc46-00df-46b1-a392-0478ff9a4ef0}")
};

extern class CATLProject2Module _AtlModule;
