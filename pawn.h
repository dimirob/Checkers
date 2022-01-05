#pragma once
class Pawn {
	float m_pos[2];
	float m_color[3];

public:
	void draw();
	void update();

	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

};
