#include "sgg\graphics.h"
#include "defines.h"
#include <string>
void draw() {
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("checkersboard.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

int main(int argc, char** argv)
{
	graphics::createWindow(1200, 800, "Checkers v0.1");
	graphics::setCanvasSize(28, 16);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::setDrawFunction(draw);
	graphics::startMessageLoop();
	return 0;
}