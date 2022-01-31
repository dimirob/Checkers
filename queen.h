#pragma once
#include "pawn.h"
class Queen :public Pawn {
private:
	int moveFRx;
	int moveFRy;
	int moveBRy;
	int moveBRx;
	int moveFLx;
	int moveFLy;
	int moveBLy;
	int moveBLx;
public:
	using Pawn::Pawn;
	virtual void draw();
	virtual void update();
	virtual bool contains(float x,float y);
	int getmoveFRx() { return moveFRx; };//get front right move x
	int getmoveFRy() { return moveFRy; };//get front right move y
	int getmoveFLx() { return moveFLx; };//get front left move x
	int getmoveFLy() { return moveFLy; };//get front left move y
	int getmoveBRx() { return moveBRx; };//get back right move x
	int getmoveBRy() { return moveBRy; };//get back right move y
	int getmoveBLx() { return moveBLx; };//get back left move x
	int getmoveBLy() { return moveBLy; };//get back left move y
	void setQueen();
	virtual bool hasAttackingPawn(Pawn* p_matrix[8][8]);
	virtual bool canMove(Pawn* p_matrix[8][8]);
};