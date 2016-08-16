#include "Main.h"
#include "Circle.h"
#include <cmath>

void Circle::draw(int fieldX, int fieldY)
{
	int displayH = game.getDisplayHeight();
	int fieldCenterX = game.getDisplayWidth() / 3 / 2;
	int fieldCenterY = displayH / 3 / 2;
	int centerX = 2 * (fieldX * fieldCenterX) + fieldCenterX;
	int centerY = 2 * (fieldY * fieldCenterY) + fieldCenterY;
	int r = static_cast<int>(displayH / 7);

	double sides = 2 * M_PI * r / 2.0;
	double d_a = 2.0 * M_PI / sides,
	angle = d_a;

	int endX = r + centerX;
	int endY = centerY;
	for (int i = 0; i <= sides; i++)
	{
		int startX = endX;
		int startY = endY;
		endX = cos(angle) * r + centerX;
		endY = sin(angle) * r + centerY;
		angle += d_a;
		SDL_RenderDrawLine(game.getRenderer(), startX, startY, endX, endY);
	}
}
