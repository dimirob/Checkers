#include "pawn.h"
#include <sgg/graphics.h>
#include "defines.h"
#include <string>

void Pawn::draw()
{
	graphics::Brush br;
	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("Pawn.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);

}

void Pawn::update()
{
}

Pawn::Pawn(int i)
{
	this->setPosX(0);
	this->setPosY(0);
	this->team = i;
	if (i == 0) {
		SETCOLOR(m_color, 1.0f, 0, 0);
	}
	else SETCOLOR(m_color, 0, 0, 1.0f);
}
