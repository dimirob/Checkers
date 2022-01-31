#include "sgg\graphics.h"
#include "defines.h"
#include <string>
#include "game.h"

void draw()
{
	Game* mygame=Game::getInstance();
	mygame->draw();
}

void update(float ms)
{
	Game* mygame = Game::getInstance();
	mygame->update();
}

int main(int argc, char** argv)
{
	graphics::createWindow(1200, 800, "Checkers v0.1");

	Game * game = Game::getInstance();
	game->init();
	graphics::setCanvasSize(CANVAS_HEIGHT, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::startMessageLoop();

	Game::releaseInstance();

	return 0;
}