#include "game.h"
#include "defines.h"
#include <sgg/graphics.h>

void Game::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("Board.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	for (auto pawn : m_pawns) {
		pawn->draw();
	}
}

Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();
	return m_instance;
}

void Game::update()
{
	for (auto pawn : m_pawns) {
		pawn->update();
	}
}

void Game::init()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			Pawn* p = new Pawn();
			m_pawns.push_front(p);
			p->setPosX(CANVAS_WIDTH * i / 4.0f);
			p->setPosY(CANVAS_HEIGHT * j / 2.0f);
		}
	}
}

Game::~Game()
{
	for (auto p : m_pawns)
	{
		delete p;
	}
	m_pawns.clear();
}

void Game::releaseInstance()
{
	if (m_instance) delete m_instance;
}

Game* Game::m_instance = nullptr;
