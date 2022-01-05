#pragma once
#include <list>
#include "pawn.h"
class Game
{
	static Game* m_instance;
	std::list<Pawn*> m_pawns;
	
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
