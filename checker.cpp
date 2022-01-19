#include "checker.h"
#include <sgg/graphics.h>
#include "defines.h"
#include <string>

#include<iostream>

Checker::Checker(int team, int x, int y)
	:Pawn(team, x, y){}

void Checker::draw()
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

void Checker::update()
{
	this->setHighlight(false);
	this->setActive(false);
	
	if (team == 0)	//red team, update possible moves
	{
		movelx = getMatposX() - 1;
		movely = getMatposY() + 1;
		moverx = getMatposX() + 1;
		movery = getMatposY() + 1;
	}
	else			//blue team, update possible moves
	{
		movelx = getMatposX() - 1;
		movely = getMatposY() - 1;
		moverx = getMatposX() + 1;
		movery = getMatposY() - 1;
	}
}