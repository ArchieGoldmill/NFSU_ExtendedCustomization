#pragma once
#include "includes/injector/injector.hpp"

struct Node
{
	Node* Next;
	Node* Prev;
	int Value;
};

struct List
{
	Node* Head;
	Node* Tail;
};