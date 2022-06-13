#include "Engine.h"
#include "Common.h"

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

void InitEngine()
{
	injector::MakeJMP(0x00504822, InstallEngineCave, true);
	injector::MakeNOP(0x005817DE, 2, true);
	injector::MakeNOP(0x0050A9D8, 5, true);
	injector::MakeNOP(0x0042245F, 6, true);
}