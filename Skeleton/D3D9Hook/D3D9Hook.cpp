#include "D3D9Hook.hpp"



D3D9Hook::D3D9Hook(IDirect3DDevice9* IDirectDevice)
{
	if (IDirectDevice != 0)
		VTable = *reinterpret_cast<void***>(IDirectDevice);
	else VTable = *reinterpret_cast<void***>(FindDevice(0x128000));
	for (BYTE i = 0; i <= 133; i++)
		m_VTable[i] = 0;
}

void D3D9Hook::SetHook(void* func, D3DVTABLE_INDEX index)
{
	unsigned long oldProtect;
	VirtualProtect(&VTable[index], sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);
	m_VTable[index] = VTable[index];
	VTable[index] = func;
	VirtualProtect(&VTable[index], sizeof(void*), oldProtect, NULL);
}

void* D3D9Hook::GetOriginalFunc(D3DVTABLE_INDEX index)
{
	if (m_VTable[index] == 0) return NULL;
	return  m_VTable[index];
}
#ifndef _M_X64
void* D3D9Hook::FindDevice(unsigned long dwLen)
{
	DWORD dwObjBase = (DWORD)LoadLibraryA("d3d9.dll");

	if (dwObjBase == 0x0)
		return 0x0;

	while (dwObjBase++ < dwObjBase + dwLen)
	{
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7 && (*(WORD*)(dwObjBase + 0x06)) == 0x8689 && (*(WORD*)(dwObjBase + 0x0C)) == 0x8689)
		{
			dwObjBase += 2;
			break;
		}
	}

	return reinterpret_cast<void*>(dwObjBase);
};
#else
void* D3D9Hook::FindDevice(unsigned long long dwLen)
{
	unsigned long long dwObjBase = (unsigned long long)LoadLibraryA("d3d9.dll");

	if (dwObjBase == 0x0)
		return 0x0;

	while (dwObjBase++ < dwObjBase + dwLen)
	{
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7 && (*(WORD*)(dwObjBase + 0x06)) == 0x8689 && (*(WORD*)(dwObjBase + 0x0C)) == 0x8689)
		{
			dwObjBase += 2;
			break;
		}
	}

	return reinterpret_cast<void*>(dwObjBase);
};
#endif // !_M_X64


D3D9Hook::~D3D9Hook()
{
	for (unsigned char i = 0; i <= 133; i++)
	{
		if (m_VTable[i] == 0) continue;
		unsigned long oldProtect;
		VirtualProtect(&VTable[i], sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect);
		VTable[i] = m_VTable[i];
		VirtualProtect(&VTable[i], sizeof(void*), oldProtect, NULL);
	}
}