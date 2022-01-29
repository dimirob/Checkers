#pragma once
#include "pawn.h"
class Queen :public Pawn {
public:
	using Pawn::Pawn;
	using Pawn::draw;
	using Pawn::update;
	bool isQueen() { return true; }
};