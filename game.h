#pragma once
#include <list>
#include "pawn.h"
class Game
{
	static Game* m_instance;
	std::list<Pawn*> m_pawns;
	Game() {}
public:
	void draw();
	void update();
	void init();
	~Game();
	static void releaseInstance();
	static Game* getInstance();

};

