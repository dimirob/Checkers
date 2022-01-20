#pragma once
#include "move.h"
#include "pawn.h"
#include "defines.h"
#include <sgg/graphics.h>
#include<iostream>

class Checker : public Pawn
{
	int movelxB; // aristera x N, N einai tou checker afou phgainei k piso
	int movelyB; // aristera y 
	int moverxB; // deksia x
	int moveryB; // deksia y
public:
	Checker(int team, int x, int y);
	void draw()
	{
		graphics::Brush br;
		float h = 1.0f * getHighlighted();

		SETCOLOR(br.fill_color, h, h, h);
		br.outline_opacity = 1.0f * getM_active();
		graphics::drawDisk(getPosX(), getPosY(), PL_DISK_SIZE, br);

		// SETCOLOR(br.fill_color, getm_color(0), getm_color(1), getm_color(2));
		SETCOLOR(br.fill_color, 0.5, 0.5, 0.5);
		br.outline_opacity = 0.0f;
		br.texture = ASSET_PATH + std::string("Pawn.png");
		graphics::drawRect(getPosX(), getPosY(), PLAYER_SIZE, PLAYER_SIZE, br);
		std::cout << "draw from Checker" << std::endl;
		std::cout << getPosX() << "  " << getPosY() << std::endl;

	}
	void update();
	Checker();
};