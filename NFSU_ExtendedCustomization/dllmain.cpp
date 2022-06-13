#include <Windows.h>
#include "includes/injector/injector.hpp"
#include "includes//IniReader.h"

#include "ColorPicker.h"
#include "Engine.h"
#include "Rims.h"

void Init()
{
	CIniReader ini("NFSU_ExtendedCustomization.ini");

	// Engine
	if (ini.ReadInteger("GENERAL", "InstallEngine", 0) == 1)
	{
		InitEngine();
	}

	// Rims
	if (ini.ReadInteger("GENERAL", "AllRimSizes", 0) == 1)
	{
		InitRims();
	}

	if (ini.ReadInteger("GENERAL", "VinylsOnCustomHoods", 0) == 1)
	{
		// Disable modal on vinyl install
		injector::WriteMemory<char>(0x004E465B, 0xEB, true);
		// Disable modal on hood install
		char bytes[] = { 0xB8, 0x00, 0x00, 0x00, 0x00, 0x85, 0xC0, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x90, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x90, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x90 };
		injector::WriteMemoryRaw(0x00508AB8, bytes, sizeof(bytes), true);
	}

	if (ini.ReadInteger("GENERAL", "DecalsOnCustomHoods", 0) == 1)
	{
		// Disable EXCLUDEDECAL
		injector::WriteMemory(0x0057EAF2, 0, true);
		injector::WriteMemory(0x0057EB12, 0, true);
		injector::WriteMemory(0x0057EBA2, 0, true);
		// Disable modal on decal install
		injector::WriteMemory<short>(0x005104FC, 0xC039, true);
		// Disable modal on hood install
		injector::WriteMemory<char>(0x00508B86, 0xEB, true);
		// Disable clear hood decals
		injector::MakeNOP(0x00508F54, 5, true);
	}

	if (ini.ReadInteger("GENERAL", "ShowMoreColors", 0) == 1)
	{
		InitColorPicker();
	}

	// Lods
	int* CarLod = (int*)0x006F1B30;
	int* WheelLod = (int*)0x006F1B34;
	int lod = ini.ReadInteger("GENERAL", "ForceLod", -1);
	*CarLod = lod;
	*WheelLod = lod;
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