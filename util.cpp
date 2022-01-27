#include "util.h"
#include "sgg\graphics.h"
#include "defines.h"

void drawText()
{
	graphics::Brush br;
	br.texture = "";
	float salto = CANVAS_HEIGHT * sinf(graphics::getGlobalTime() / 500.0f) / 40;
	char message[40];

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 0.5f);
	graphics::setFont(std::string(ASSET_PATH) + "Partikular.ttf");
	graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 5, 1.0f, "Welcome to Checkers", br);

	SETCOLOR(br.fill_color, 0.5f, 1.0f, 1.0f);
	graphics::setFont(std::string(ASSET_PATH) + "Partikular.ttf");
	graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2 + salto, 1.0f, " Press 'SPACE' to START ", br);

	SETCOLOR(br.fill_color, 0.5f, 0.5f, 0.5f); // SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::setFont(std::string(ASSET_PATH) + "Partikular.ttf");
	graphics::drawText(.5, CANVAS_HEIGHT - .5, .5f, " Press 'ESC' to EXIT ", br);
}
