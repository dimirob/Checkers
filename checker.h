#pragma once
#include "move.h"
#include "pawn.h"

class Checker : public Pawn
{
	int movelxB; // aristera x N, N einai tou checker afou phgainei k piso
	int movelyB; // aristera y 
	int moverxB; // deksia x
	int moveryB; // deksia y
public:
	Checker(int team, int x, int y);
	void draw();
	void update();
	Checker();
};