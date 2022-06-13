#include "Rims.h"
#include "Common.h"

int RimsBackup = 0;
void __stdcall RestoreImg()
{
	injector::WriteMemory(0x004F87DB, 0x5E5F0C478B344589, true);
	injector::WriteMemory(0x004F87B7, 0x282444D8, true);
}

void __stdcall CheckImgBackup(int hash)
{
	if (hash == RimsBackup)
	{
		injector::WriteMemory(0x004F87DB, 0x5E5F900C4789C031, true);
		injector::MakeNOP(0x004F87B7, 4, true);
	}

	RimsBackup = hash;
}

void __declspec(naked) RimsCave()
{
	static constexpr auto cExit = 0x0050DDC0;
	static constexpr auto ThumbnailScroller_AddNode = 0x004F8730;
	__asm
	{
		pushad;
		push ebp;
		call CheckImgBackup;
		popad;

		call ThumbnailScroller_AddNode;

		pushad;
		call RestoreImg;
		popad;

		jmp cExit;
	}
}

void InitRims()
{
	injector::MakeNOP(0x0050D977, 6, true);
	injector::MakeNOP(0x0050DA17, 2, true);
	injector::MakeNOP(0x0050D89B, 2, true);
	injector::MakeNOP(0x0050D7E1, 6, true);
	injector::MakeNOP(0x0050D8C8, 6, true);
	injector::WriteMemory<char>(0x0050DA3C, 0xEB, true);
	injector::MakeJMP(0x0050DDBB, RimsCave, true);
	injector::WriteMemory(0x004F87B4, 0x8D282444D81C45D9, true);
}