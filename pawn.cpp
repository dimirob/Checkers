#include "pawn.h"
#include <sgg/graphics.h>
#include "defines.h"
#include <string>

void Pawn::draw()
{
	graphics::Brush br;
	float h = 1.0f * m_highlighted;

	SETCOLOR(br.fill_color, h, h, h);
	br.outline_opacity = 1.0f * m_active;
	graphics::drawDisk(m_pos[0], m_pos[1], PL_DISK_SIZE, br);
	
	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("Pawn.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);

}

void Pawn::update()
{
	this->setHighlight(false);
	this->setActive(false);
	if (team == 0) {//red team, update possible moves
		movelx = getMatposX() - 1;
		movely = getMatposY() + 1;
		moverx = getMatposX() + 1;
		movery = getMatposY() + 1;
	}
	else {//blue team, update possible moves
		movelx = getMatposX() - 1;
		movely = getMatposY() - 1;
		moverx = getMatposX() + 1;
		movery = getMatposY() - 1;
	}
}

Pawn::Pawn(int team,int x,int y)
{
	moved = false;
	this->team = team;
	this->setMatposx(x);
	this->setMatposy(y);
	if (team == 0) {//red team, set color and possible moves
		SETCOLOR(m_color, 1.0f, 0, 0);
		movelx = getMatposX() - 1;
		movely = getMatposY() + 1;
		moverx = getMatposX() + 1;
		movery = getMatposY() + 1;
	}
	else { //blue team, set color and possible moves 
		SETCOLOR(m_color, 0, 0, 1.0f); 
		movelx = getMatposX() - 1;
		movely = getMatposY() - 1;
		moverx = getMatposX() + 1;
		movery = getMatposY() - 1;
	}
}
bool Pawn::contains(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < PL_DISK_SIZE; 
}

int Pawn::getTeam()
{
	return team;
}

void Pawn::gotMoved()
{
	this->moved = true;
}

bool Pawn::hasAttackingPawn(Pawn* p_matrix[8][8])
{
	if (this->getTeam() == 0)//pawn is red
	{
		if (this->getMatposX() == 0)//pawn is left
		{
			int posx = getMatposX() + 1;
			int posy = getMatposY() + 1;
			if (p_matrix[posx][posy] != nullptr && p_matrix[posx][posy]->getTeam() != getTeam()) {//has enemy pawn in diagonal 
				if (p_matrix[posx + 1][posy + 1] == nullptr) {//has attacking place in board
					return true;
				}
			}
		}
		else if (this->getMatposX()==7)//pawn is right
		{
			int posx = getMatposX() - 1;
			int posy = getMatposY() + 1;
			if (p_matrix[posx][posy] != nullptr && p_matrix[posx][posy]->getTeam() != getTeam()) {//has enemy pawn in diagonal
				if (p_matrix[posx - 1][posy + 1] == nullptr) {//has attacking place in board
					return true;
				}
			}
		}
		else//pawn is middle sections
		{
			int posx = getMatposX() + 1;
			int posy = getMatposY() + 1;
			int posx2 = getMatposX() - 1;
			int posy2 = getMatposY() + 1;
			bool right = p_matrix[posx][posy] != nullptr && p_matrix[posx][posy]->getTeam() != getTeam();//attacking pawn in left diagonal
			if (posx == 7) { right = false; }//attacking pawn is at the right side of the board
			bool left = p_matrix[posx2][posy2] != nullptr && p_matrix[posx2][posy2]->getTeam() != getTeam();//atttacking pawn in right diagonal
			if (posx2 == 0) { left = false; }//attacking pawn is at the left side of the board
			if (left || right) {//has enemy pawn in diagonal
				if (p_matrix[posx + 1][posy + 1] == nullptr&&right) {//has attacking place in board
					return true;
				}
				if (p_matrix[posx2 - 1][posy2 + 1] == nullptr&&left) {//has attacking place in board
					return true;
				}
			}
		}
	}
	else//pawn is blue
	{
		if (this->getMatposX() == 0)//pawn is left
		{
			int posx = getMatposX() + 1;
			int posy = getMatposY() - 1;
			if (p_matrix[posx][posy] != nullptr && p_matrix[posx][posy]->getTeam() != getTeam()) {//has enemy pawn in diagonal 
				if (p_matrix[posx + 1][posy - 1] == nullptr) {//has attacking place in board
					return true;
				}
			}
		}
		else if (this->getMatposX() == 7)//pawn is right
		{
			int posx = getMatposX() - 1;
			int posy = getMatposY() - 1;
			if (p_matrix[posx][posy] != nullptr && p_matrix[posx][posy]->getTeam() != getTeam()) { //has enemy pawn in diagonal
				if (p_matrix[posx - 1][posy - 1] == nullptr) {//has attacking place in board
					return true;
				}
			}
		}
		else//pawn is middle sections
		{
			int posx = getMatposX() + 1;
			int posy = getMatposY() - 1;
			int posx2 = getMatposX() - 1;
			int posy2 = getMatposY() - 1;
			bool right= p_matrix[posx][posy] != nullptr && p_matrix[posx][posy]->getTeam() != getTeam();//attacking move is in left
			if (posx == 7) { right = false; }//attacking pawn is at the right side of the board
			bool left= p_matrix[posx2][posy2] != nullptr && p_matrix[posx2][posy2]->getTeam() != getTeam();//attacking move is on right
			if (posx2 == 0) { left = false; }//attacking pawn is at the left side of the board
			if (left || right) { //has enemy pawn in diagonal
				if ((p_matrix[posx + 1][posy - 1] == nullptr)&&right) {//has attacking place in board
					return true;
				}
				if (p_matrix[posx2 - 1][posy2 - 1] == nullptr&&left) {//has attacking place in board
					return true;
				}
			}
		}
	}
	return false;
}

bool Pawn::canMove(Pawn* p_matrix[8][8])
{
	if (this->getTeam() == 0) {//red pawn
		if (this->getMatposX() == 0) {//pawn is in left side
			if (p_matrix[this->getMatposX() + 1][this->getMatposY() + 1] == nullptr) { return true; }
		}
		if (this->getMatposX() == 7) {//pawn is in right side
			if (p_matrix[this->getMatposX() - 1][this->getMatposY() + 1] == nullptr) { return true; }
		}
		else {//pawn is in the middle
			if (p_matrix[this->getMatposX() + 1][this->getMatposY() + 1] == nullptr || p_matrix[this->getMatposX() - 1][this->getMatposY() + 1] == nullptr) { return true; }
		}
	}
	else {//blue pawn
		if (this->getMatposX() == 0) {//pawn is in left side
			if (p_matrix[this->getMatposX() + 1][this->getMatposY() - 1] == nullptr) { return true; }
		}
		if (this->getMatposX() == 7) {//pawn is in right side
			if (p_matrix[this->getMatposX() - 1][this->getMatposY() - 1] == nullptr) { return true; }
		}
		else {//pawn is in the middle
			if (p_matrix[this->getMatposX() + 1][this->getMatposY() - 1] == nullptr || p_matrix[this->getMatposX() - 1][this->getMatposY() - 1] == nullptr) { return true; }
		}
	}
	return false;
}

Move* Pawn::getAttMoveR()
{
	Move* move = new Move(0.0f,0.0f,0,0);
	if (getTeam() == 0) {//team is red
		move->setMatx(this->getMatposX() + 2);
		move->setMaty(this->getMatposY() + 2);
	}
	else {//team is blue
		move->setMatx(this->getMatposX() + 2);
		move->setMaty(this->getMatposY() - 2);
	}
	return move;
}

Move* Pawn::getAttMoveL()
{
	Move* move = new Move(0.0f, 0.0f, 0, 0);
	if (getTeam() == 0) {//team is red
		move->setMatx(this->getMatposX() - 2);
		move->setMaty(this->getMatposY() + 2);
	}
	else {//team is blue
		move->setMatx(this->getMatposX() - 2);
		move->setMaty(this->getMatposY() - 2);
	}
	return move;
}
