/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "timer.h"
#include "easymesh.h"
using namespace std;

/*==========================================================================*/
int main(int argc, char *argv[])
{
	EasyMesh em;
	argc = 2;
	argv[1] = "example_1";
	em.algor(argc, argv);
	cin.get();
	return 1;
}
