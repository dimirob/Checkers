#include "move.h"
#include "sgg/graphics.h"
#include "defines.h"

void Move::draw()
{
	graphics::Brush br;
	float h = 1.0f * m_highlight;
	
	SETCOLOR(br.fill_color, h, h, h);
	br.outline_opacity = 1.0f * m_active;
	graphics::drawDisk(pos[0], pos[1], MOVE_SIZE+0.05f, br);
	
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 0.0f);
	graphics::drawDisk(pos[0], pos[1], MOVE_SIZE, br);
}

Move::Move(float x, float y, int matx, int maty)
{
	pos[0] = x;
	pos[1] = y;
	this->matx = matx;
	this->maty = maty;
}

bool Move::contains(float x, float y)
{
	return distance(x, y, pos[0], pos[1]) < MOVE_SIZE;
}

void Move::sethighlight(bool h)
{
	m_highlight = h;
}

void Move::setactive(bool h)
{
	m_active = h;
}

void Move::update()
{
}

void Move::setX(float x)
{
	this->pos[0] = x;
}

void Move::setY(float y)
{
	this->pos[1] = y;
}

float Move::getX()
{
	return pos[0];
}

float Move::getY()
{
	return pos[1];
}

void Move::setMatx(int x)
{
	this->matx = x;
}

void Move::setMaty(int y)
{
	this->maty = y;
}
