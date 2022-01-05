#include "game.h"
#include "defines.h"
#include <sgg/graphics.h>
Game::Game()
{
}
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
	float matrx[8] = { CANVAS_WIDTH / 16.0f,CANVAS_WIDTH / 5.28f,CANVAS_WIDTH / 3.21f,CANVAS_WIDTH / 2.28f,CANVAS_WIDTH / 1.78f,CANVAS_WIDTH / 1.46f,CANVAS_WIDTH / 1.235f,CANVAS_WIDTH / 1.07f };
	float matry[8] = { CANVAS_HEIGHT / 1.07f,CANVAS_HEIGHT / 1.235f,CANVAS_HEIGHT / 1.46f,CANVAS_HEIGHT / 1.78f,CANVAS_HEIGHT / 2.28f,CANVAS_HEIGHT / 3.21f,CANVAS_HEIGHT / 5.28f,CANVAS_HEIGHT / 16.0f };
		for (int i = 0; i < 8; i=i+2) {
			for (int j = 0; j < 3; j=j+2) {
				Pawn* p = new Pawn();
				m_pawns.push_front(p);
				p->setPosX(matrx[i]);
				p->setPosY(matry[j]);
			}
		}
		for (int i = 1; i <= 8; i = i + 2) {
			Pawn* p = new Pawn();
			m_pawns.push_front(p);
			p->setPosX(matrx[i]);
			p->setPosY(matry[1]);
		}
		for (int i = 1; i < 8; i = i + 2) {
			for (int j = 7; j >4; j = j - 2) {
				Pawn* p = new Pawn();
				m_pawns.push_front(p);
				p->setPosX(matrx[i]);
				p->setPosY(matry[j]);
			}
		}
		for (int i = 0; i < 8; i = i + 2) {
			Pawn* p = new Pawn();
			m_pawns.push_front(p);
			p->setPosX(matrx[i]);
			p->setPosY(matry[6]);
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
