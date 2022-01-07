#pragma once
#include <list>
#include "pawn.h"
#include "defines.h"
class Game
{
public:
	enum game_state_t { STATE_INIT, SATTE_LOADING, STATE_IDLE, STATE_MOVING, STATE_ATTACKING };
	float matrx[8]  { CANVAS_WIDTH / 16.0f,CANVAS_WIDTH / 5.28f,CANVAS_WIDTH / 3.21f,CANVAS_WIDTH / 2.28f,CANVAS_WIDTH / 1.78f,CANVAS_WIDTH / 1.46f,CANVAS_WIDTH / 1.235f,CANVAS_WIDTH / 1.07f };
	float matry[8] { CANVAS_HEIGHT / 1.07f,CANVAS_HEIGHT / 1.235f,CANVAS_HEIGHT / 1.46f,CANVAS_HEIGHT / 1.78f,CANVAS_HEIGHT / 2.28f,CANVAS_HEIGHT / 3.21f,CANVAS_HEIGHT / 5.28f,CANVAS_HEIGHT / 16.0f };
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
