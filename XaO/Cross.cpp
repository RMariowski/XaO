#include "Main.h"
#include "Cross.h"

void Cross::draw(int fieldX, int fieldY)
{
    int displayW = game.getDisplayWidth();
    int displayH = game.getDisplayHeight();
	int fieldCenterX = displayW / 3 / 2;
	int fieldCenterY = displayH / 3 / 2;

    // Top-left to bottom-right
    SDL_RenderDrawLine(game.getRenderer(), 2 * (fieldX * fieldCenterX),
						2 * (fieldY * fieldCenterY),
						fieldX * displayW / 3 + displayW / 3,
						fieldY * displayH / 3 + displayH / 3);

    // Bottom-left to top-right
    SDL_RenderDrawLine(game.getRenderer(), fieldX * displayW / 3 + displayW / 3,
						2 * (fieldY * fieldCenterY),
						2 * (fieldX * fieldCenterX),
						fieldY * displayH / 3 + displayH / 3);
}
