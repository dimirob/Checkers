#pragma once
#define CANVAS_WIDTH 15.0f
#define CANVAS_HEIGHT 17.0f

constexpr auto ASSET_PATH = ".\\assets\\";

#define PLAYER_SIZE 1.5f
#define PL_DISK_SIZE 0.8f
#define BOARD_TABLEY {CANVAS_HEIGHT / 1.07f}
<<<<<<< Updated upstream
=======

#define SETCOLOR(c, r, g, b) {c[0] = r; c[1] = g; c[2] = b;}

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrt(dx * dx + dy * dy);
}
>>>>>>> Stashed changes
