#pragma once
#include "move.h"

class Pawn {
protected:
	float m_pos[2]; // thesis ston kamva(float)
	int m_matpos[2]; // thesis ston kamva(int)
	float m_color[3];
	int team; // omada 0 = red, 1 = mple
	bool m_highlighted = false;
	bool m_active = false;
	bool moved=false;//pawn has been moved
	int movelx; // aristera x
	int movely; // aristera y 
	int moverx; // deksia x
	int movery; // deksia y

public:
	void draw();
	void update();
	Pawn(int team,int x,int y);
	float getm_color(int i) { return m_color[i]; }
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	int getMatposX() { return m_matpos[0]; }
	int getMatposY() { return m_matpos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	void setMatposx(int x) { m_matpos[0] = x; }
	void setMatposy(int y) { m_matpos[1] = y; }
	bool getHighlighted() { return m_highlighted; }
	void setHighlight(bool h) { m_highlighted = h; }
	bool getM_active() { return m_active; }
	void setActive(bool a) { m_active = a; }
	bool contains(float x, float y);
	int getTeam();
	void gotMoved();//pawn has been moved
	int getmoveRx() { return moverx; };//get right move x
	int getmoveRy() { return movery; };//get right move y
	int getmoveLx() { return movelx; };//get left move x
	int getmoveLy() { return movely; };//get left move y
	bool hasAttackingPawn(Pawn* p_matrix[8][8]);//checks if it has a pawn that it can attack
	bool canMove(Pawn* p_matrix[8][8]);
	Move* getAttMoveR();//gives attacking move from right
	Move* getAttMoveL();//gives attacking move from left
	bool operator ==(Pawn* p) { return this->getPosX() == p->getPosX() && this->getPosY() == p->getPosY(); }
	bool operator !=(Pawn* p) { return this->getPosX() != p->getPosX() || this->getPosY() != p->getPosY(); }
	
};
