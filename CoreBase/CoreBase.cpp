// CoreBase.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Controller.h"
#include <ctime>

int main(int argc, char* argv[])
{
	Controller* controller = new Controller();
	controller->PrepareProcess(&argc, &argv);
	controller->StartProcess();
	controller->CloseProcess();

	return 0;
}