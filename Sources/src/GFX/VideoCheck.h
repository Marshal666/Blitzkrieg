#ifndef __VIDEOCHECK_H__
#define __VIDEOCHECK_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma ONCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NVideoCheck
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SVideoMemory
{
	struct SMemory
	{
		DWORD dwTotal;
		DWORD dwFree;
	};
	//
	SMemory local;
	SMemory nonlocal;
	SMemory texture;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// get API name (DirectX)
const wchar_t* STDCALL GetAPIName();
// get API version (0x00000800)
DWORD STDCALL GetAPIVersion();
// get video memory amount
bool STDCALL GetVideoMemory( SVideoMemory *pMemory );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __VIDEOCHECK_H__
