#pragma once
class Pawn {
	float m_pos[2];
	float m_color[3];
	int team;
	bool m_highlighted = false;
	bool m_active = false;

public:
	void draw();
	void update();
	Pawn(int i);
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }

	bool contains(float x, float y);
};
