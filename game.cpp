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
	
			Pawn* p = new Pawn();
			m_pawns.push_front(p);
			p->setPosX(CANVAS_WIDTH / 15.0f);
			p->setPosY(CANVAS_HEIGHT / 1.07f);
			Pawn* p2 = new Pawn();
			m_pawns.push_front(p2);
			p2->setPosX(CANVAS_WIDTH / 3.2f);
			p2->setPosY(CANVAS_HEIGHT / 1.07f);
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
