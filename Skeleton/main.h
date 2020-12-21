#pragma once
#include <Windows.h>

#include "D3D9Hook/D3D9Hook.hpp"
#include "GTAFuncs.h"

// from AntTweakBar
void DrawLine(LPDIRECT3DDEVICE9 m_pDevice, int x1, int y1, int x2, int y2, DWORD Color, bool _AntiAliased = false)
{
	struct CVtx
	{
		float m_Pos[4];
		DWORD m_Color;
	};
	CVtx p[2];

	p[0].m_Pos[0] = (float)x1;
	p[0].m_Pos[1] = (float)y1;
	p[0].m_Pos[2] = 0;
	p[0].m_Pos[3] = 0;
	p[0].m_Color = Color;

	p[1].m_Pos[0] = (float)x2;
	p[1].m_Pos[1] = (float)y2;
	p[1].m_Pos[2] = 0;
	p[1].m_Pos[3] = 0;
	p[1].m_Color = Color;

	//if( m_State->m_Caps.LineCaps & D3DLINECAPS_ANTIALIAS )
	m_pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, (_AntiAliased ? TRUE : FALSE));
	m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, p, sizeof(CVtx));
	//if( m_State->m_Caps.LineCaps & D3DLINECAPS_ANTIALIAS )
	m_pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);
}

static struct _Keys
{
    bool        bPressed;
    DWORD       dwStartTime;
} kPressingKeys[256];

BOOL State_Key(int Key, DWORD dwTimeOut)
{
    if (HIWORD(GetKeyState(Key)))
    {
        if (!kPressingKeys[Key].bPressed || (kPressingKeys[Key].dwStartTime && (kPressingKeys[Key].dwStartTime + dwTimeOut) <= GetTickCount()))
        {
            kPressingKeys[Key].bPressed = TRUE;
            if (dwTimeOut > NULL)
                kPressingKeys[Key].dwStartTime = GetTickCount();
            return TRUE;
        }
    }
    else
        kPressingKeys[Key].bPressed = FALSE;
    return FALSE;
}