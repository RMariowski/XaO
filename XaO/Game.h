#pragma once

#include "Board.h"

class Game
{
public:
    enum State
    {
        STATE_PLAY,
        STATE_WIN,
        STATE_LOSE,
        STATE_DRAW,
        STATE_QUIT,
        STATE_COUNT
    };

public:
    Game();

    bool init();

    void randomTurn();

    void mainLoop();

    int getDisplayWidth() const {
		return _display.w;
	}

    int getDisplayHeight() const {
		return _display.h;
	}

    SDL_Renderer* getRenderer() const {
		return _renderer;
	}

public:
    State state;
    bool myTurn;
    unsigned int moves;

    SDL_Event event;

private:
    SDL_DisplayMode _display;
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    Board _board;
};