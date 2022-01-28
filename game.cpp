#include "game.h"
#include "defines.h"
#include <sgg/graphics.h>
#include "util.h"

#include <iostream> // del

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
		graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2, 1.5f, "Loading assets...", br);
		m_state = STATE_LOADING;
		return;
	}

	if (m_state == STATE_START_SCREEN)
	{
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "start.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

		drawText();
		return;
	}

	if (m_state == STATE_LAST_SCREEN)
	{
		br.texture = std::string(ASSET_PATH) + "last.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		
		
		graphics::setFont(std::string(ASSET_PATH) + "Partikular.ttf");
		
		if (redPawns0 == 0) {
			SETCOLOR(br.fill_color, 0.0f, 0.0f, 1.0f); // rgb
			graphics::drawText(CANVAS_WIDTH / 11, CANVAS_HEIGHT / 9, 1.2f, "BLUE TEAM WON THE GAME", br);
		}
		if (bluePawns1 == 0) {
			SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f); // rgb
			graphics::drawText(CANVAS_WIDTH / 11, CANVAS_HEIGHT / 9, 1.2f, "RED TEAM WON THE GAME", br);
		}
		
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		
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
	// del
	std::cout << "red: " << redPawns0 << "\nblue: " << bluePawns1 << std::endl;
	// _____del

	if (m_state == STATE_INIT)
	{
		return;
	}

	if (m_state == STATE_LOADING)
	{
		// init();
		m_state = STATE_START_SCREEN;
		return;
	}

	if (m_state == STATE_START_SCREEN)
	{
		if (graphics::getKeyState(graphics::SCANCODE_SPACE))
		{
			init();
			m_state = STATE_BLUE;
		}
		return;
	}

	if (m_state == STATE_LAST_SCREEN)
	{
		if (graphics::getKeyState(graphics::SCANCODE_R))
		{
			m_state = STATE_START_SCREEN;
			m_pawns.clear();
		}
		return;
	}

	// check for winner
	if (redPawns0 == 0 || bluePawns1 == 0)
	{
		m_state = STATE_LAST_SCREEN;
		return;
	}


	for (auto pawn : m_pawns) {
		pawn->update();
	}
	for (auto moves : m_moves) {
		moves->update();
	}
	for (auto pawn : m_pawns) {
		bool canattack = pawn->hasAttackingPawn(matpawn);
		if((canattack && pawn->getTeam()==0&&m_state==STATE_RED)) {//red pawn can attack and it is its turn
			m_state = STATE_ATTACKR;

		}
		else if ((canattack && pawn->getTeam() == 1&&m_state==STATE_BLUE)) {//blue pawn can attack and it is its turn
			m_state = STATE_ATTACKB;
		}
		
	}
	it = m_pawns.begin();
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
					m_moves.push_back(move);
					move->draw();
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
			if (pawn->hasAttacked() == true) { m_att_pawns.clear(); m_att_pawns.push_back(pawn); break; }//multiple move
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
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr&&matpawn[att_move->getmatx()-1][att_move->getmaty()-1]!=nullptr) {//check where the pawn can attack
					if (matpawn[att_move->getmatx() - 1][att_move->getmaty() - 1]->getTeam() != curr_att_pawn->getTeam()) {//last check
						att_move->setX(getMatx(att_move->getmatx()));
						att_move->setY(getMaty(att_move->getmaty()));
						m_moves.push_back(att_move);
					}
				}
				att_move = curr_att_pawn->getAttMoveL();
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr&& matpawn[att_move->getmatx() + 1][att_move->getmaty() - 1]!=nullptr) {//check where the pawn can attack
					if (matpawn[att_move->getmatx() + 1][att_move->getmaty() - 1]->getTeam() != curr_att_pawn->getTeam()) {//last check
						att_move->setX(getMatx(att_move->getmatx()));
						att_move->setY(getMaty(att_move->getmaty()));
						m_moves.push_back(att_move);
					}
				}
			}
			m_state=STATE_CHOOSE_ATTACKMOVER;
			cur_pawn = curr_att_pawn;
		}
		m_att_pawns.clear();
	}
	else if (m_state==STATE_ATTACKB) {//blue must attack
		Pawn* curr_att_pawn=nullptr;
		for (auto pawn : m_pawns) {
			if (pawn->hasAttackingPawn(matpawn) && pawn->getTeam() == 1) {//place all blue pawns that can attack in a list
				m_att_pawns.push_back(pawn);
			}
			if (pawn->hasAttacked() == true) { m_att_pawns.clear(); m_att_pawns.push_back(pawn); break; }
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
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr && matpawn[att_move->getmatx() - 1][att_move->getmaty() + 1] != nullptr) {//check where the pawn can attack
					if (matpawn[att_move->getmatx() - 1][att_move->getmaty() + 1]->getTeam() != curr_att_pawn->getTeam()) {//last check
						att_move->setX(getMatx(att_move->getmatx()));
						att_move->setY(getMaty(att_move->getmaty()));
						m_moves.push_back(att_move);
					}
				}
				att_move = curr_att_pawn->getAttMoveL();
				if (matpawn[att_move->getmatx()][att_move->getmaty()] == nullptr && matpawn[att_move->getmatx() + 1][att_move->getmaty() + 1] != nullptr) {//check where the pawn can attack
					if (matpawn[att_move->getmatx() + 1][att_move->getmaty() + 1]->getTeam() != curr_att_pawn->getTeam()) {//last check
						att_move->setX(getMatx(att_move->getmatx()));
						att_move->setY(getMaty(att_move->getmaty()));
						m_moves.push_back(att_move);
					}
				}
			}
			m_state = STATE_CHOOSE_ATTACKMOVEB;
			cur_pawn = curr_att_pawn;
		}
		m_att_pawns.clear();
	}
	else if (m_state == STATE_CHOOSE_ATTACKMOVER) {//red chooses move to attack
		Move* curr_move = nullptr;
		for (auto m : m_moves) {
			if (m->contains(mx, my)) {
				m->sethighlight(true);
				curr_move = m;
			}
			else {
				m->sethighlight(false);
			}
		}
		if (ms.button_left_pressed && curr_move) {
			bool left, right = false;//attacked left or right?
			int attmove = cur_pawn->getMatposX();//save previous move to see where we attacked 
			m_state = STATE_BLUE;
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = nullptr;
			cur_pawn->setPosX(curr_move->getX());
			cur_pawn->setPosY(curr_move->getY());
			cur_pawn->setMatposx(curr_move->getmatx());
			cur_pawn->setMatposy(curr_move->getmaty());
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = cur_pawn;
			m_moves.clear();
			cur_pawn->setActive(false);
			cur_pawn->setHighlight(false);// pawn moved
			cur_pawn->Attacked(true);//the pawn has attacked, it may have multiple moves
			if (cur_pawn->getMatposX() > attmove) { right = true; }//attacked right
			else { left = true; }//attacked left
			if (right) {
				while (it != m_pawns.end()) {
					if (*it == matpawn[cur_pawn->getMatposX() - 1][cur_pawn->getMatposY() - 1]) {
						m_pawns.erase(it); //erase enemy pawn
						bluePawns1--;
						matpawn[cur_pawn->getMatposX() - 1][cur_pawn->getMatposY() - 1] = nullptr;
						break;
					}
					++it;
				}
			}
			else {
				while (it != m_pawns.end()) {
					if (*it == matpawn[cur_pawn->getMatposX() + 1][cur_pawn->getMatposY() - 1]) {
						m_pawns.erase(it);  //erase enemy pawn
						bluePawns1--;
						matpawn[cur_pawn->getMatposX() + 1][cur_pawn->getMatposY() - 1] = nullptr;
						break;
					}
					++it;
				}
			}
			if (cur_pawn->hasAttackingPawn(matpawn)) { m_state = STATE_ATTACKR; }
			else { cur_pawn->Attacked(false); m_state = STATE_BLUE; }
		}
	}
	else if (m_state == STATE_CHOOSE_ATTACKMOVEB) {//blue chooses move to attack
		Move* curr_move = nullptr;
		for (auto m : m_moves) {
			if (m->contains(mx, my)) {
				m->sethighlight(true);
				curr_move = m;
			}
			else {
				m->sethighlight(false);
			}
		}
		if (ms.button_left_pressed && curr_move) {
			bool left, right = false;//attacked left or right?
			int attmove = cur_pawn->getMatposX();//save previous move to see where we attacked 
			m_state = STATE_RED;
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = nullptr;
			cur_pawn->setPosX(curr_move->getX());
			cur_pawn->setPosY(curr_move->getY());
			cur_pawn->setMatposx(curr_move->getmatx());
			cur_pawn->setMatposy(curr_move->getmaty());
			matpawn[cur_pawn->getMatposX()][cur_pawn->getMatposY()] = cur_pawn;
			m_moves.clear();
			cur_pawn->setActive(false);
			cur_pawn->setHighlight(false);//pawn moved
			cur_pawn->Attacked(true);//pawn has attacked, may have multiple moves
			if (cur_pawn->getMatposX() > attmove) { right = true; }//attacked right
			else { left = true; }//attacked left
			if (right) {
				while (it != m_pawns.end()) {
					if (*it == matpawn[cur_pawn->getMatposX() - 1][cur_pawn->getMatposY() + 1]) {
						m_pawns.erase(it); //erase enemy pawn
						redPawns0--;
						matpawn[cur_pawn->getMatposX() - 1][cur_pawn->getMatposY() + 1] = nullptr;
						break;
					}
					++it;
				}
			}
			else {
				while (it != m_pawns.end()) {
					if (*it == matpawn[cur_pawn->getMatposX() + 1][cur_pawn->getMatposY() + 1]) {
						m_pawns.erase(it); //erase enemy pawn
						redPawns0--;
						matpawn[cur_pawn->getMatposX() + 1][cur_pawn->getMatposY() + 1] = nullptr;
						break;
					}
					++it;
				}
			}
			if (cur_pawn->hasAttackingPawn(matpawn)) { m_state = STATE_ATTACKB; }
			else { cur_pawn->Attacked(false); m_state = STATE_RED; }
		}
	}
}

void Game::init()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			matpawn[i][j] = nullptr;
		}
	}
		for (int i = 0; i < 8; i=i+2) {
			for (int j = 0; j < 3; j=j+2) {
				Pawn* p = new Pawn(0,i,j);
				m_pawns.push_front(p);
				redPawns0++;
				p->setPosX(matrx[i]);
				p->setPosY(matry[j]);
				matpawn[i][j] = p;//update pawn matrix
			}
		}
		for (int i = 1; i <= 8; i = i + 2) {
			Pawn* p = new Pawn(0,i,1);
			m_pawns.push_front(p);
			redPawns0++;
			p->setPosX(matrx[i]);
			p->setPosY(matry[1]);
			matpawn[i][1] = p;//update pawn matrix
		}
		for (int i = 1; i < 8; i = i + 2) {
			for (int j = 7; j >4; j = j - 2) {
				Pawn* p = new Pawn(1, i, j);
				m_pawns.push_front(p);
				bluePawns1++;
				p->setPosX(matrx[i]);
				p->setPosY(matry[j]);
				matpawn[i][j] = p;//update pawn matrix
			}
		}
		for (int i = 0; i < 8; i = i + 2) {
			Pawn* p = new Pawn(1,i,6);
			m_pawns.push_front(p);
			bluePawns1++;
			p->setPosX(matrx[i]);
			p->setPosY(matry[6]);
			matpawn[i][6] = p;//update pawn matrix
		}

		graphics::preloadBitmaps(ASSET_PATH);
		sleep(2000);
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
