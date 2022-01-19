#pragma once
#include <list>
#include <iostream>
#include "pawn.h"
#include "defines.h"
#include "move.h"
#include "checker.h"

class Game
{
public:
	Pawn* cur_pawn = nullptr;
	enum game_state_t { STATE_RED, STATE_BLUE, STATE_MOVER,STATE_MOVEB,STATE_ATTACKR,STATE_ATTACKB,STATE_CHOOSE_ATTACKMOVER, STATE_CHOOSE_ATTACKMOVEB
	};//RED TURN, BLUE TURN, RED CHOOSE MOVE,BLUE CHOOSE MOVE, RED MUST ATTACK, BLUE MUST ATTACK,RED CHOOSE ATTACK MOVE.BLUE ATTACK MOVE
	float matrx[8] { CANVAS_WIDTH / 16.0f,CANVAS_WIDTH / 5.28f,CANVAS_WIDTH / 3.21f,CANVAS_WIDTH / 2.28f,CANVAS_WIDTH / 1.78f,CANVAS_WIDTH / 1.46f,CANVAS_WIDTH / 1.235f,CANVAS_WIDTH / 1.07f };
	float matry[8] { CANVAS_HEIGHT / 1.07f,CANVAS_HEIGHT / 1.235f,CANVAS_HEIGHT / 1.46f,CANVAS_HEIGHT / 1.78f,CANVAS_HEIGHT / 2.28f,CANVAS_HEIGHT / 3.21f,CANVAS_HEIGHT / 5.28f,CANVAS_HEIGHT / 16.0f };
	// original: // float matry[8] { CANVAS_HEIGHT / 1.07f,CANVAS_HEIGHT / 1.235f,CANVAS_HEIGHT / 1.46f,CANVAS_HEIGHT / 1.78f,CANVAS_HEIGHT / 2.28f,CANVAS_HEIGHT / 3.21f,CANVAS_HEIGHT / 5.28f,CANVAS_HEIGHT / 16.0f };
	Pawn*  matpawn[8][8];
protected:
	enum m_state;
	static Game* m_instance;
	std::list<Pawn*> m_pawns;
	std::list<Pawn*> m_att_pawns;
	std::list<Move*> m_moves;
	std::list<Pawn*>::iterator it;
	Pawn* m_active_pawn = nullptr;
	game_state_t m_state;

	// gia checker
	std::list<Checker*> m_checkers;
	
public:
	
	void draw();
	void update();
	void init();
	Game();
	~Game();
	static void releaseInstance();
	static Game* getInstance();
	float getMatx(int x);//give matrix coordinates and get coordinates on canvas
	float getMaty(int y);//give matrix coordinates and get coordinates on canvas
	int getMatx(float x);//give canvas coordinates and get matrix coordinates
	int getMaty(float y);//give canvas coordinates and get matrix coordinates
	bool isRightSide(int x);//pawn is on left side
	bool isLeftSide(int x);//pawn is on right side
	bool can_attack(Pawn* p);//pawn can attack 
};
