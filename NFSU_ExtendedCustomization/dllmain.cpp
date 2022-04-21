#include <Windows.h>
#include "includes/injector/injector.hpp"

void __declspec(naked) InstallEngineCave()
{
	static constexpr auto cExit = 0x00504828;
	static constexpr auto GarageManager_InstallPart = 0x005044B0;

	__asm
	{
		mov[ebx + 0x47C], eax;

		pushad;
		push 0;
		push eax;
		mov eax, esi;
		mov ebx, 12;
		call GarageManager_InstallPart;
		popad;

		jmp cExit;
	}
}

void Init()
{
	injector::MakeJMP(0x00504822, InstallEngineCave, true);
	injector::MakeNOP(0x005817DE, 2, true);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x670CB5) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
		{
			Init();
		}
		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.4 English speed.exe (3,03 MB (3.178.496 bytes)).", "NFSU - Extended Customization", MB_ICONERROR);
			return FALSE;
		}
	}
	break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}