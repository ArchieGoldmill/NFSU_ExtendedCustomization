#pragma once
#include "includes/injector/injector.hpp"

struct ListItem
{
	ListItem* Next;
	ListItem* Prev;
	int Value;
};

struct List
{
	ListItem* Head;
	ListItem* Tail;
};