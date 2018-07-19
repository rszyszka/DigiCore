#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Space.h"

class IOStreamer
{
public:
	__declspec(dllexport) static void SaveSpace(Space* space, string path);
	__declspec(dllexport) static void LoadSpace(Space* space, string path);
};