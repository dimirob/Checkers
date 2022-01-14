#include "game.h"
#include "defines.h"
#include <sgg/graphics.h>
#include "util.h"

#include <iostream>

Game::Game()
{
}

void Game::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (m_state == STATE_INIT)
	{
		graphics::setFont(std::string(ASSET_PATH) + "Partikular.ttf");
		graphics::drawText(CANVAS_WIDTH/4, CANVAS_HEIGHT/2, 1.5f, "Loading assets...", br);
		m_state = STATE_LOADING;
		return;
	}

	if (m_state == STATE_START_SCREEN)
	{
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "start.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		return;
	}

	if (m_state == STATE_LAST_SCREEN)
	{
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "last.png";
		br.outline_opacity = 0.0f;
		
		SETCOLOR(br.fill_color, 0.7f, 0.7f, 0.7f);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		return;
	}

	
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("Board.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	for (auto pawn : m_pawns) {
		pawn->draw();
	}
	for (auto move : m_moves) {
		move->draw();
	}
}

Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();
	return m_instance;
}

float Game::getMatx(int x)
{
	return matrx[x];
}

float Game::getMaty(int y)
{
	return matry[y];
}

bool Game::isRightSide(int x)
{
	return x==7;
}

bool Game::isLeftSide(int x)
{
	return x==0;
}


void Game::update()
{
	if (m_state == STATE_INIT)
	{
		return;
	}

	if (m_state == STATE_LOADING)
	{
		init();
		m_state = STATE_START_SCREEN;
		return;
	}

	if (m_state == STATE_START_SCREEN)
	{
		drawText();
		if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		{
			m_state = STATE_RED;
		}
		return;
	}

	if (m_state == STATE_LAST_SCREEN)
	{
		if (graphics::getKeyState(graphics::SCANCODE_R))
		{
			m_pawns.clear();
			init();
			m_state = STATE_START_SCREEN;
		}
		return;
	}

	// del:
	/*if (graphics::getGlobalTime() > 6000)
		if (graphics::getGlobalTime() < 12000)
			m_state = STATE_LAST_SCREEN;*/
	// _______________________________

	for (auto pawn : m_pawns) {
		pawn->update();
	}
	for (auto moves : m_moves) {
		moves->update();
	}

	// del:
	for (auto pawn : m_pawns) 
	{
		float y = pawn->getMatposY();
		if (y < CANVAS_HEIGHT / 1.235f - 4.0f && m_state == STATE_BLUE)
		{
			m_state = STATE_LAST_SCREEN;
		}
	}
	// _______________________________

	
	for (auto pawn : m_pawns)
	{
		bool canattack = pawn->hasAttackingPawn(matpawn);
		if (canattack && pawn->getTeam()==0&&m_state==STATE_RED) {//red pawn can attack and it is its turn
			m_state = STATE_ATTACKR;

		}
		else if (canattack && pawn->getTeam() == 1&&m_state==STATE_BLUE) {//blue pawn can attack and it is its turn
			m_state = STATE_ATTACKB;
		}
		
	}
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	if (m_state == STATE_RED){// highlight pawn if not in attack mode
		for (auto p : m_pawns)
		{
			if (p->contains(mx, my)&&p->getTeam()==0 && p->canMove(matpawn))
			{
				p->setHighlight(true);
				cur_pawn = p;
			}
			else
				p->setHighlight(false);
		}

		// ativate pawn
		if (ms.button_left_pressed && cur_pawn)
		{
			m_active_pawn = cur_pawn;
			m_active_pawn->setActive(true);
			for (auto p : m_pawns)
			{
				if (p != m_active_pawn)
					p->setActive(false);
			}
			float act_x = cur_pawn->getPosX();//x of active pawn 
			float act_y = cur_pawn->getPosY();//y of active pawn
			int act_posx = cur_pawn-> getMatposX();//matx of active pawn
			int act_posy = cur_pawn-> getMatposY();//maty of active pawn
			bool rightSide = this->isRightSide(act_posx);//is pawn in the right side
			bool leftSide = this->isLeftSide(act_posx);//is pawn in the left side 
			if (rightSide) {
				Move* move = new Move(getMatx(cur_pawn->getmoveLx()), getMaty(cur_pawn->getmoveLy()), cur_pawn->getmoveLx(), cur_pawn->getmoveLy());
				move->draw();
				m_moves.push_back(move);
			}
			else if (leftSide) {
				Move* move = new Move(getMatx(cur_pawn->getmoveRx()), getMaty(cur_pawn->getmoveRy()), cur_pawn->getmoveRx(), cur_pawn->getmoveRy());
				move->draw();
				m_moves.push_back(move);
			}
			else {
				Move* move;
				if (matpawn[cur_pawn->getmoveLx()][cur_pawn->getmoveLy()] == nullptr) {
					move = new Move(getMatx(cur_pawn->getmoveLx()), getMaty(cur_pawn->getmoveLy()), cur_pawn->getmoveLx(), cur_pawn->getmoveLy());
					m_moves.push_back(move);
					move->draw();
				}
				if (matpawn[cur_pawn->getmoveRx()][cur_pawn->getmoveRy()] == nullptr) {
					move = new Move(getMatx(cur_pawn->getmoveRx()), getMaty(cur_pawn->getmoveRy()), cur_pawn->getmoveRx(), cur_pawn->getmoveRy());
					move->draw();
					m_moves.push_back(move);
				}
			}
			m_state = STATE_MOVER;//change gamestate to move
		}
	}
	else if (m_state == STATE_BLUE) {//highlight pawn if not in attack mode
		for (auto p : m_pawns)
		{
			if (p->contains(mx, my) && p->getTeam() == 1&&p->canMove(matpawn))
			{
				p->setHighlight(true);
				cur_pawn = p;
			}
			else
				p->setHighlight(false);
		}

		// ativate pawn
		if (ms.button_left_pressed && cur_pawn)
		{
			m_active_pawn = cur_pawn;
			m_active_pawn->setActive(true);
			for (auto p : m_pawns)
			{
				if (p != m_active_pawn)
					p->setActive(false);
			}
			float act_x = cur_pawn->getPosX();//x of active pawn 
			float act_y = cur_pawn->getPosY();//y of active pawn
			int act_posx =cur_pawn->getMatposX();//matx of active pawn
			int act_posy = cur_pawn->getMatposY();//maty of active pawn
			bool rightSide = this->isRightSide(act_posx);//is pawn in the right side
			bool leftSide = this->isLeftSide(act_posx);//is pawn in the left side 
			if (rightSide) {
				Move* move = new Move(getMatx(cur_pawn->getmoveLx()), getMaty(cur_pawn->getmoveLy()), cur_pawn->getmoveLx(), cur_pawn->getmoveLy());
				move->draw();
				m_moves.push_back(move);
			}
			else if (leftSide) {
				Move* move = new Move(getMatx(cur_pawn->getmoveRx()), getMaty(cur_pawn->getmoveRy()), cur_pawn->getmoveRx(), cur_pawn->getmoveRy());
				move->draw();
				m_moves.push_back(move);
			}
			else {
				Move* move;
				if (matpawn[cur_pawn->getmoveLx()][cur_pawn->getmoveLy()] == nullptr) {
					move = new Move(getMatx(cur_pawn->getmoveLx()), getMaty(cur_pawn->getmoveLy()), cur_pawn->getmoveLx(), cur_pawn->getmoveLy());
					m_moves.push_back(move);
					move->draw();
				}
				if (matpawn[cur_pawn->getmoveRx()][cur_pawn->getmoveRy()] == nullptr) {
					move = new Move(getMatx(cur_pawn->getmoveRx()), getMaty(cur_pawn->getmoveRy()), cur_pawn->getmoveRx(), cur_pawn->getmoveRy());
					move->draw();
					m_moves.push_back(move);
				}
			}
			m_state = STATE_MOVEB;//change state to move
		}
		
	}
	else if (m_state == STATE_MOVER) {//state where we have selected pawn and we must choose where to move it
		Move* curr_move = nullptr; 
		for (auto m : m_moves) {
			if (m->contains(mx, my)) {
				m->sethighlight(true);
				curr_move = m;
			}
			else
				m->sethighlight(false);
		}
		if (ms.button_left_pressed && curr_move) {
			m_state = STATE_BLUE;
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = nullptr;
			cur_pawn->setPosX(curr_move->getX());
			cur_pawn->setPosY(curr_move->getY());
			cur_pawn->setMatposx(curr_move->getmatx());
			cur_pawn->setMatposy(curr_move->getmaty());
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = cur_pawn;
			m_moves.clear();
			cur_pawn->setActive(false);
			cur_pawn->setHighlight(false);
		}
		else if (ms.button_left_pressed) {//deselect the pawn
			cur_pawn->setActive(false);
			cur_pawn->setHighlight(false);
			m_moves.clear();
			m_state = STATE_RED;
		}

	}
	else if (m_state == STATE_MOVEB) {//state where we have selected pawn and we must choose where to move it
		Move* curr_move = nullptr;
		for (auto m : m_moves) {
			if (m->contains(mx, my)) {
				m->sethighlight(true);
				curr_move = m;
			}
			else
				m->sethighlight(false);
		}
		if (ms.button_left_pressed && curr_move) {
			m_state = STATE_RED;
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = nullptr;
			cur_pawn->setPosX(curr_move->getX());
			cur_pawn->setPosY(curr_move->getY());
			cur_pawn->setMatposx(curr_move->getmatx());
			cur_pawn->setMatposy(curr_move->getmaty());
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = cur_pawn;
			m_moves.clear();
			cur_pawn->setActive(false);
			cur_pawn->setHighlight(false);
		}
		else if (ms.button_left_pressed) {//deselect the pawn
			cur_pawn->setActive(false);
			cur_pawn->setHighlight(false);
			m_moves.clear();
			m_state = STATE_BLUE;
		}
		m_att_pawns.clear();
	}
	else if (m_state == STATE_ATTACKR) {//red must attack 
		Pawn* curr_att_pawn = nullptr;
		for (auto pawn : m_pawns) {
			if (pawn->hasAttackingPawn(matpawn)&&pawn->getTeam()==0) {//place all red pawns that can attack in a list
				m_att_pawns.push_back(pawn);
			}
		}
		for (auto p : m_att_pawns) {
			if (p->contains(mx, my)) {
				p->setHighlight(true);
				curr_att_pawn = p;
			}
			else
				p->setHighlight(false);
		}
		if (ms.button_left_pressed && curr_att_pawn) {
			if (isLeftSide(curr_att_pawn->getMatposX())) {//pawn is in left side
				Move* att_move=curr_att_pawn->getAttMoveR();//checks are already made in getAttMoveR
				att_move->setX(getMatx(att_move->getmatx()));
				att_move->setY(getMaty(att_move->getmaty()));
				m_moves.push_back(att_move);
			}
			else if (isRightSide(curr_att_pawn->getMatposX())) {//pawn is in right side
				Move* att_move = curr_att_pawn->getAttMoveL();//checks are already made in getAttMoveL
				att_move->setX(getMatx(att_move->getmatx()));
				att_move->setY(getMaty(att_move->getmaty()));
				m_moves.push_back(att_move);
			}
			else {//pawn is in the middle
				Move* att_move = curr_att_pawn->getAttMoveR();
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr) {//check where the pawn can attack
					att_move->setX(getMatx(att_move->getmatx()));
					att_move->setY(getMaty(att_move->getmaty()));
					m_moves.push_back(att_move);
				}
				att_move = curr_att_pawn->getAttMoveL();
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr) {
					att_move->setX(getMatx(att_move->getmatx()));
					att_move->setY(getMaty(att_move->getmaty()));
					m_moves.push_back(att_move);
				}
			}
			m_state = STATE_MOVER;
		}
		m_att_pawns.clear();
	}
	else if (m_state==STATE_ATTACKB) {//blue must attack
		Pawn* curr_att_pawn=nullptr;
		for (auto pawn : m_pawns) {
			if (pawn->hasAttackingPawn(matpawn) && pawn->getTeam() == 1) {//place all blue pawns that can attack in a list
				m_att_pawns.push_back(pawn);
			}
		}
		for (auto p : m_att_pawns) {
			if (p->contains(mx, my)) {
				p->setHighlight(true);
				curr_att_pawn = p;
			}
			else
				p->setHighlight(false);
		}
		if (ms.button_left_pressed && curr_att_pawn) {
			if (isLeftSide(curr_att_pawn->getMatposX())) {//pawn is in left side
				Move* att_move = curr_att_pawn->getAttMoveR();
				att_move->setX(getMatx(att_move->getmatx()));
				att_move->setY(getMaty(att_move->getmaty()));
				m_moves.push_back(att_move);
			}
			else if (isRightSide(curr_att_pawn->getMatposX())) {//pawn is in right side
				Move* att_move = curr_att_pawn->getAttMoveL();
				att_move->setX(getMatx(att_move->getmatx()));
				att_move->setY(getMaty(att_move->getmaty()));
				m_moves.push_back(att_move);
			}
			else {//pawn is in the middle
				Move* att_move = curr_att_pawn->getAttMoveR();
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr) {//check if the pawn can attack right side
					att_move->setX(getMatx(att_move->getmatx()));
					att_move->setY(getMaty(att_move->getmaty()));
					m_moves.push_back(att_move);
				}
				att_move = curr_att_pawn->getAttMoveL();
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr) {//check if the pawn can attack left side
					att_move->setX(getMatx(att_move->getmatx()));
					att_move->setY(getMaty(att_move->getmaty()));
					m_moves.push_back(att_move);
				}
			}
			m_state = STATE_MOVEB;
		}
	}
	
}

void Game::init()
{
	// m_state = STATE_BLUE; // del
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			matpawn[i][j] = nullptr;
		}
	}
		
	for (int i = 0; i < 8; i=i+2) {
		for (int j = 0; j < 3; j=j+2) {
			Pawn* p = new Pawn(0,i,j);
			m_pawns.push_front(p);
			p->setPosX(matrx[i]);
			p->setPosY(matry[j]);
			matpawn[i][j] = p;//update pawn matrix
		}
	}

	for (int i = 1; i <= 8; i = i + 2) {
		Pawn* p = new Pawn(0,i,1);
		m_pawns.push_front(p);
		p->setPosX(matrx[i]);
		p->setPosY(matry[1]);
		matpawn[i][1] = p;//update pawn matrix
	}
	for (int i = 1; i < 8; i = i + 2) {
		for (int j = 7; j >4; j = j - 2) {
			Pawn* p = new Pawn(1, i, j);
			m_pawns.push_front(p);
			p->setPosX(matrx[i]);
			p->setPosY(matry[j]);
			}
	}
	for (int i = 0; i < 8; i = i + 2) {
		Pawn* p = new Pawn(1,i,6);
		m_pawns.push_front(p);
		p->setPosX(matrx[i]);
		p->setPosY(matry[6]);
		matpawn[i][6] = p;//update pawn matrix
	}

	graphics::preloadBitmaps(ASSET_PATH);

	// sleep(2000);

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
