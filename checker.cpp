#include "checker.h"
#include <sgg/graphics.h>
#include "defines.h"
#include <string>

#include<iostream>

Checker::Checker(int team, int x, int y)
	:Pawn(team, x, y){}



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