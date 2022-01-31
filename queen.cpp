#include "queen.h"
#include <iostream>
#include "sgg/graphics.h"
#include "defines.h"

void Queen::draw()
{
	graphics::Brush br;
	float h = 1.0f * m_highlighted;

	SETCOLOR(br.fill_color, h, h, h);
	br.outline_opacity = 1.0f * m_active;
	graphics::drawDisk(m_pos[0], m_pos[1], QUEEN_DISK_SIZE, br);
	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string("Queen.png");
	graphics::drawRect(m_pos[0], m_pos[1], PLAYER_SIZE, PLAYER_SIZE, br);
}
void Queen::update()
{
	this->setHighlight(false);
	this->setActive(false);
	moveFLx = getMatposX() - 1;
	moveFLy = getMatposY() + 1;
	moveFRx = getMatposX() + 1;
	moveFRy = getMatposY() + 1;
	moveBLx = getMatposX() - 1;
	moveBLy = getMatposY() - 1;
	moveBRx = getMatposX() + 1;
	moveBRy = getMatposY() - 1;
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
void Queen::setQueen()
{
	this->isqueen = true;
}
bool Queen::hasAttackingPawn(Pawn* p_matrix[8][8])
{
	if (this->getMatposY() == 0) {//queen is on the bottom side
		int posx = this->getMatposX() + 1;
		int posy = this->getMatposY() + 1;
		int posx2 = this->getMatposX() - 1;
		int posy2 = this->getMatposY() + 1;
		bool right=false;
		if (posx >= 7) { right = false; }//attacking queen is at the right side of the board
		else {
			if (p_matrix[posx][posy] != nullptr) {
				right = p_matrix[posx][posy]->getTeam() != getTeam();//attacking pawn in right diagonal
			}
		}
		bool left=false;
		if (posx2 <= 0) { left = false; }//attacking queen is at the left side of the board
		else {
			if (p_matrix[posx2][posy2] != nullptr) {
				left = p_matrix[posx2][posy2]->getTeam() != getTeam();//atttacking pawn in left diagonal
			}
		}
		if (left || right) {//has enemy pawn in diagonal
			if (p_matrix[posx + 1][posy + 1] == nullptr && right) {//has attacking place in board
				
				return true;
				
			}
			if (p_matrix[posx2 - 1][posy2 + 1] == nullptr && left) {//has attacking place in board
				
				return true;
				
			}
		}
	}
	else if (this->getMatposY() == 7) {//queen is on the top side
		int posx = this->getMatposX() + 1;
		int posy = this->getMatposY() - 1;
		int posx2 = this->getMatposX() - 1;
		int posy2 = this->getMatposY() - 1;
		bool right = false;
		if (posx >= 7) { right = false; }
		else {
			if (p_matrix[posx][posy] != nullptr) {
				right = p_matrix[posx][posy]->getTeam() != getTeam();
			}
		}
		bool left = false;
		if (posx2 <= 0) {left = false;}
		else {
			if (p_matrix[posx2][posy2] != nullptr) {
				left = p_matrix[posx2][posy2]->getTeam() != getTeam();
			}
		}
		
		if (left || right) { //has enemy pawn in diagonal
			if ((p_matrix[posx + 1][posy - 1] == nullptr) && right) {//has attacking place in board
				
				return true;
				
			}
			if (p_matrix[posx2 - 1][posy2 - 1] == nullptr && left) {//has attacking place in board
				
				return true;
				
			}
		}
	}
	else {
		int upRx = this->getMatposX() + 1;
		int upRy = this->getMatposY() + 1;
		int upLx = this->getMatposX() - 1;
		int	upLy = this->getMatposY() + 1;
		int boRx = this->getMatposX() + 1;
		int boRy = this->getMatposY() - 1;
		int boLx = this->getMatposX() - 1;
		int boLy = this->getMatposY() - 1;
		bool upR = true;
		bool upL=true;
		bool botR=true;
		bool botL=true;
		
		if (this->getMatposX() <= 1) { upL = false; botL = false; }
		if (this->getMatposX() >= 6) { upR = false; botR = false; }
		if (upRy == 7&&(upR==true||upL==true)) { upR = false; upL = false; }
		else{
			if (p_matrix[upRx][upRy] != nullptr&&upR==true) {
				upR = p_matrix[upRx][upRy]->getTeam() != this->getTeam();
			}
			else upR = false;
			if (p_matrix[upLx][upLy] != nullptr&&upL==true) {
				upL = p_matrix[upLx][upLy]->getTeam() != this->getTeam();
			}
			else upL = false;
		}
		if (boRy == 0&&(botR==true||botL==true)) { botR = false; botL = false; }
		else {
			if (p_matrix[boRx][boRy] != nullptr&& botR==true)
			{
				bool botR = p_matrix[boRx][boRy]->getTeam() != this->getTeam();
			}
			else botR = false;
			if (p_matrix[boLx][boLy] != nullptr&&botL==true) {
				bool botL = p_matrix[boLx][boLy]->getTeam() != this->getTeam();
			}
			else botL = false;
		}
		
		if (upR || upL || botR || botL) {
			if (p_matrix[upRx + 1][upRy + 1] == nullptr && upR) { return true;  }
			if (p_matrix[upLx - 1][upLy + 1] == nullptr && upL) { return true; }
			if (p_matrix[boRx + 1][boRy - 1] == nullptr && botR) { return true; }
			if (p_matrix[boLx - 1][boLy - 1] == nullptr && botL) {return true; }
		}
	}
	return false;
}
bool Queen::canMove(Pawn* p_matrix[8][8])
{
	if (this->getMatposY() == 7) {//queen is on top side
		if (this->getMatposX() == 0) {//queen is on top left side
			if (p_matrix[this->getmoveBRx()][this->getmoveBRy()] == nullptr) return true;
		}
		else if (this->getMatposX() == 7) {//queen is on top right side
			if (p_matrix[this->getmoveBLx()][this->getmoveBLy()] == nullptr) return true;
		}
		else {
			if (p_matrix[this->getmoveBRx()][this->getmoveBRy()] == nullptr) return true;
			if (p_matrix[this->getmoveBLx()][this->getmoveBLy()] == nullptr) return true;
		}
	}
	else if (this->getMatposY() == 0) {//queen is on bottom side
		if (this->getMatposX() == 0) {//queen is on bottom left side
			if (p_matrix[this->getmoveFRx()][this->getmoveFRy()] == nullptr) return true;

		}
		else if (this->getMatposX() == 7) {//queen is on bottom right side
			if (p_matrix[this->getmoveFLx()][this->getmoveFLy()] == nullptr) return true;
		}
		else {
			if (p_matrix[this->getmoveFRx()][this->getmoveFRy()] == nullptr) return true;
			if (p_matrix[this->getmoveFLx()][this->getmoveFLy()] == nullptr) return true;
		}
	}
	else {//queen is middle section
		if (this->getMatposX() == 0) {//queen is on left side
			if (p_matrix[this->getmoveFRx()][this->getmoveFRy()] == nullptr) return true;
			if (p_matrix[this->getmoveBRx()][this->getmoveBRy()] == nullptr) return true;
		}
		else if(this->getMatposX()==7){//queen is on right side
			if (p_matrix[this->getmoveFLx()][this->getmoveFLy()] == nullptr) return true;
			if (p_matrix[this->getmoveBLx()][this->getmoveBLy()] == nullptr) return true;
		}
		else {
			if (p_matrix[this->getmoveFRx()][this->getmoveFRy()] == nullptr) return true;
			if (p_matrix[this->getmoveBRx()][this->getmoveBRy()] == nullptr) return true;
			if (p_matrix[this->getmoveFLx()][this->getmoveFLy()] == nullptr) return true;
			if (p_matrix[this->getmoveBLx()][this->getmoveBLy()] == nullptr) return true;
		}
	}
	return false;
}
bool Queen::contains(float x, float y) {
	return distance(x, y, m_pos[0], m_pos[1]) < QUEEN_DISK_SIZE;
}
