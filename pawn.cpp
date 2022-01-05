#include "pawn.h"
#include <sgg/graphics.h>
#include "defines.h"
#include <string>

void Pawn::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("Pawn.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);

}

void Pawn::update()
{
}
