#pragma once
#include <list>
#include "pawn.h"
class Game
{
public:
	enum game_state_t { STATE_INIT, SATTE_LOADING, STATE_IDLE, STATE_MOVING, STATE_ATTACKING };
protected:
	static Game* m_instance;
	std::list<Pawn*> m_pawns;
	Pawn* m_active_pawn = nullptr;

	
public:
	const static float BX[1][1];
	void draw();
	void update();
	void init();
	Game();
	~Game();
	static void releaseInstance();
	static Game* getInstance();
	static float getXy(int i, int j) { return  BX[i][j]; }
};
