#pragma once

#include <d3d9.h>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
#ifndef _M_X64
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86\\d3d9.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86\\d3dx9.lib")
#else
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64\\d3d9.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64\\d3dx9.lib")
#endif // !_M_X64


enum D3DVTABLE_INDEX {
	iQueryInterface,
	iAddRef,
	iRelease,
	iTestCooperativeLevel,
	iGetAvailableTextureMem,
	iEvictManagedResources,
	iGetDirect3D,
	iGetDeviceCaps,
	iGetDisplayMode,
	iGetCreationParameters,
	iSetCursorProperties,
	iSetCursorPosition,
	iShowCursor,
	iCreateAdditionalSwapChain,
	iGetSwapChain,
	iGetNumberOfSwapChains,
	iReset,
	iPresent,
	iGetBackBuffer,
	iGetRasterStatus,
	iSetDialogBoxMode,
	iSetGammaRamp,
	iGetGammaRamp,
	iCreateTexture,
	iCreateVolumeTexture,
	iCreateCubeTexture,
	iCreateVertexBuffer,
	iCreateIndexBuffer,
	iCreateRenderTarget,
	iCreateDepthStencilSurface,
	iUpdateSurface,
	iUpdateTexture,
	iGetRenderTargetData,
	iGetFrontBufferData,
	iStretchRect,
	iColorFill,
	iCreateOffscreenPlainSurface,
	iSetRenderTarget,
	iGetRenderTarget,
	iSetDepthStencilSurface,
	iGetDepthStencilSurface,
	iBeginScene,
	iEndScene,
	iClear,
	iSetTransform,
	iGetTransform,
	iMultiplyTransform,
	iSetViewport,
	iGetViewport,
	iSetMaterial,
	iGetMaterial,
	iSetLight,
	iGetLight,
	iLightEnable,
	iGetLightEnable,
	iSetClipPlane,
	iGetClipPlane,
	iSetRenderState,
	iGetRenderState,
	iCreateStateBlock,
	iBeginStateBlock,
	iEndStateBlock,
	iSetClipStatus,
	iGetClipStatus,
	iGetTexture,
	iSetTexture,
	iGetTextureStageState,
	iSetTextureStageState,
	iGetSamplerState,
	iSetSamplerState,
	iValidateDevice,
	iSetPaletteEntries,
	iGetPaletteEntries,
	iSetCurrentTexturePalette,
	iGetCurrentTexturePalette,
	iSetScissorRect,
	iGetScissorRect,
	iSetSoftwareVertexProcessing,
	iGetSoftwareVertexProcessing,
	iSetNPatchMode,
	iGetNPatchMode,
	iDrawPrimitive,
	iDrawIndexedPrimitive,
	iDrawPrimitiveUP,
	iDrawIndexedPrimitiveUP,
	iProcessVertices,
	iCreateVertexDeclaration,
	iSetVertexDeclaration,
	iGetVertexDeclaration,
	iSetFVF,
	iGetFVF,
	iCreateVertexShader,
	iSetVertexShader,
	iGetVertexShader,
	iSetVertexShaderConstantF,
	iGetVertexShaderConstantF,
	iSetVertexShaderConstantI,
	iGetVertexShaderConstantI,
	iSetVertexShaderConstantB,
	iGetVertexShaderConstantB,
	iSetStreamSource,
	iGetStreamSource,
	iSetStreamSourceFreq,
	iGetStreamSourceFreq,
	iSetIndices,
	iGetIndices,
	iCreatePixelShader,
	iSetPixelShader,
	iGetPixelShader,
	iSetPixelShaderConstantF,
	iGetPixelShaderConstantF,
	iSetPixelShaderConstantI,
	iGetPixelShaderConstantI,
	iSetPixelShaderConstantB,
	iGetPixelShaderConstantB,
	iDrawRectPatch,
	iDrawTriPatch,
	iDeletePatch,
	iCreateQuery,
	iSetConvolutionMonoKernel,
	iComposeRects,
	iPresentEx,
	iGetGPUThreadPriority,
	iSetGPUThreadPriority,
	iWaitForVBlank,
	iCheckResourceResidency,
	iSetMaximumFrameLatency,
	iGetMaximumFrameLatency,
	iCheckDeviceState,
	iCreateRenderTargetEx,
	iCreateOffscreenPlainSurfaceEx,
	iCreateDepthStencilSurfaceEx,
	iResetEx,
	iGetDisplayModeEx
};

class D3D9Hook
{
public:
	D3D9Hook(IDirect3DDevice9* IDirectDevice = 0);
	~D3D9Hook();
	void SetHook(void* func, D3DVTABLE_INDEX index);
	void* GetOriginalFunc(D3DVTABLE_INDEX index);
#ifndef _M_X64
	void* FindDevice(unsigned long dwLen);
#else
	void* FindDevice(unsigned long long dwLen);
#endif
private:
	void** VTable;
	void* m_VTable[133];
};

