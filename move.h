#pragma once

class Move {
	float pos[2];
	float MOVE_SIZE = 0.4f;
	bool m_highlight = false;
	bool m_active = false;
	int matx;
	int maty;
public:
	void draw();
	Move(float x, float y, int matx, int maty);
	bool contains(float x,float y);
	void sethighlight(bool h);
	void setactive(bool h);
	void update();
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void setMatx(int x);
	void setMaty(int y);
	int getmatx() { return this->matx; };
	int getmaty() { return this->maty; };

};
