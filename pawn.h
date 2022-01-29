#pragma once
#include "move.h"
class Pawn {
	float m_pos[2];
	int m_matpos[2];
	float m_color[3];
	int team;
	bool m_highlighted = false;
	bool m_active = false;
	bool attacked=false;//pawn has been moved
	int movelx;
	int movely;
	int moverx;
	int movery;

public:
	void draw();
	void update();
	Pawn(int team,int x,int y);
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	int getMatposX() { return m_matpos[0]; }
	int getMatposY() { return m_matpos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	void setMatposx(int x) { m_matpos[0] = x; }
	void setMatposy(int y) { m_matpos[1] = y; }
	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }
	bool contains(float x, float y);
	int getTeam();
	void Attacked(bool n);//pawn has been attacked
	bool hasAttacked() {return this->attacked; }
	int getmoveRx() { return moverx; };//get right move x
	int getmoveRy() { return movery; };//get right move y
	int getmoveLx() { return movelx; };//get left move x
	int getmoveLy() { return movely; };//get left move y
	bool hasAttackingPawn(Pawn* p_matrix[8][8]);//checks if it has a pawn that it can attack
	bool canMove(Pawn* p_matrix[8][8]);
	Move* getAttMoveR();//gives attacking move from right
	Move* getAttMoveL();//gives attacking move from left
	bool isQueen() { return false; }
	bool operator ==(Pawn* p) { return this->getPosX() == p->getPosX() && this->getPosY() == p->getPosY(); }
	bool operator !=(Pawn* p) { return this->getPosX() != p->getPosX() || this->getPosY() != p->getPosY(); }
	
};
