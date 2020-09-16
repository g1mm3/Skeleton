#define _CRT_SECURE_NO_WARNINGS
#include "main.h"

typedef HRESULT(__stdcall* tPresent)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
tPresent gOriginalPresent = nullptr;

D3D9Hook* d3d3hk = nullptr;
bool Draw = false;


HRESULT __stdcall hkdPresent(IDirect3DDevice9* d3dDev, CONST RECT* srcRect, CONST RECT* destRect, HWND destWindow, CONST RGNDATA* dirtyRegion)
{
    if (Draw && !IsGTAMenuActive())
    {
        DWORD pedPoolUsageInfo = *(DWORD*)0xB74490;
        DWORD pedPoolBegining = *(DWORD*)pedPoolUsageInfo;
        DWORD byteMapAddr = *(DWORD*)(pedPoolUsageInfo + 4);

        for (BYTE i = 1; i < 140; i++) // 0 - our ped
        {
            BYTE activityStatus = *(BYTE*)(byteMapAddr + i);
            if (activityStatus > 0 && activityStatus < 128)
            {
                actor_info actor = *(actor_info*)(pedPoolBegining + i * 1988);
                if (IsOnScreen(&actor))
                {
                    D3DXVECTOR3 worldPos1 = { 0, 0, 0 };
                    D3DXVECTOR3 worldPos2 = { 0, 0, 0 };
                    D3DXVECTOR2 screenPos1 = { 0, 0 };
                    D3DXVECTOR2 screenPos2 = { 0, 0 };

                    int t[14] = { 3, 4, 5, 51, 52, 41, 42, 31, 32, 33, 21, 22, 23, 2 };
                    for (int i = 0; i < 14; i++)
                    {
                        GetBonePosition(&actor, worldPos1, t[i]);
                        GetBonePosition(&actor, worldPos2, t[i] + 1);
                        screenPos1 = ConvertGlobalXYZToWindowScreenXY(worldPos1);
                        screenPos2 = ConvertGlobalXYZToWindowScreenXY(worldPos2);

                        DrawLine(d3dDev, screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y, D3DCOLOR_ARGB(255, 255, 255, 255));

                    }
                    for (int i = 4; i < 6; i++)
                    {
                        GetBonePosition(&actor, worldPos2, i * 10 + 1);
                        screenPos2 = ConvertGlobalXYZToWindowScreenXY(worldPos2);

                        DrawLine(d3dDev, screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y, D3DCOLOR_ARGB(255, 255, 255, 255));
                    }
                }
            }
        }
    }

    return gOriginalPresent(d3dDev, srcRect, destRect, destWindow, dirtyRegion);
}

void InitHook()
{
    d3d3hk = new D3D9Hook(*reinterpret_cast<IDirect3DDevice9**>(0xC97C28));
    d3d3hk->SetHook(&hkdPresent, iPresent);
    gOriginalPresent = (tPresent)d3d3hk->GetOriginalFunc(iPresent);
}

int __stdcall MainThread()
{
    while (*reinterpret_cast<IDirect3DDevice9**>(0xC97C28) != nullptr)
        Sleep(350);

    InitHook();
    
    while (true)
    {
        if (State_Key(VK_NUMPAD0, 1000))
            Draw = !Draw;

        Sleep(0);
    }

    delete d3d3hk;

    return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID lpReserved)
{
    if (reason == DLL_PROCESS_ATTACH)
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);

	return TRUE;
}