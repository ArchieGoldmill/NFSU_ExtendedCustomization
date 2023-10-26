#include "ColorPicker.h"
#include "Common.h"

enum class PAINT_TYPE
{
	Gloss,
	Metalic,
	Pearl,
	Calipers,
	Engine,
	Rims,
	Exhaust,
	Vinyl
};

enum class PAINT_TARGET
{
	Base,
	Rims,
	Engine,
	Spoiler,
	Calipers,
	Exhaust,
	Vinyl
};

static auto malloc_0 = (void* (__cdecl*)(int))0x0067121A;
static auto free_0 = (void* (__cdecl*)(int))0x00671102;

int NumColors;
void AddListItem(List* list, PAINT_TYPE value)
{
	auto newItem = (Node*)malloc_0(sizeof(Node));
	newItem->Value = (int)value;

	auto last = list->Tail;
	newItem->Prev = last;
	newItem->Next = (Node*)list;
	last->Next = newItem;
	list->Tail = newItem;

	NumColors++;
}

void __stdcall CreateColorPicker(PAINT_TARGET target, List* list)
{
	NumColors = 0;

	switch (target)
	{
	case PAINT_TARGET::Base:
	case PAINT_TARGET::Spoiler:
	{
		AddListItem(list, PAINT_TYPE::Gloss);
		AddListItem(list, PAINT_TYPE::Metalic);
		AddListItem(list, PAINT_TYPE::Pearl);
		AddListItem(list, PAINT_TYPE::Engine);
		AddListItem(list, PAINT_TYPE::Rims);
		AddListItem(list, PAINT_TYPE::Vinyl);
		break;
	}
	case PAINT_TARGET::Rims:
	{
		AddListItem(list, PAINT_TYPE::Rims);
		AddListItem(list, PAINT_TYPE::Gloss);
		AddListItem(list, PAINT_TYPE::Metalic);
		AddListItem(list, PAINT_TYPE::Pearl);
		AddListItem(list, PAINT_TYPE::Engine);
		break;
	}
	case PAINT_TARGET::Engine:
	{
		AddListItem(list, PAINT_TYPE::Engine);
		break;
	}
	case PAINT_TARGET::Calipers:
	{
		AddListItem(list, PAINT_TYPE::Calipers);
		break;
	}
	case PAINT_TARGET::Exhaust:
	{
		AddListItem(list, PAINT_TYPE::Exhaust);
		break;
	}
	case PAINT_TARGET::Vinyl:
	{
		AddListItem(list, PAINT_TYPE::Vinyl);
		AddListItem(list, PAINT_TYPE::Gloss);
		AddListItem(list, PAINT_TYPE::Metalic);
		AddListItem(list, PAINT_TYPE::Pearl);
		AddListItem(list, PAINT_TYPE::Engine);
		AddListItem(list, PAINT_TYPE::Rims);
		break;
	}
	default:
	{
		AddListItem(list, PAINT_TYPE::Gloss);
		break;
	}
	}
}

void __declspec(naked) ColorPickerCave()
{
	__asm
	{
		pushad;
		push esi;
		push edi;
		call CreateColorPicker;
		popad;

		pop ecx;
		mov ecx, 0x01000000;
		mov edx, 0;
		mov eax, NumColors;

		ret 4;
	}
}

void InitColorPicker()
{
	injector::MakeJMP(0x004D7B90, ColorPickerCave, true);
}