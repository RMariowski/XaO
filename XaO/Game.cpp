#include "Main.h"
#include "Game.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

Game game;

Game::Game()
    : state(STATE_PLAY), myTurn(false), moves(0), _window(0), _renderer(0)
{ }

bool Game::init()
{
	srand(time(0));

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		SDL_Log(SDL_GetError());
        return false;
    }

	SDL_GetDisplayMode(0, 0, &_display);
#if !defined(__ANDROID__) && !defined(TARGET_OS_IPHONE)
	_display.w = DEFAULT_WIDTH;
	_display.h = DEFAULT_HEIGHT;
#endif

	_window = SDL_CreateWindow("Kolko i Krzyzyk", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, _display.w, _display.h, SDL_WINDOW_SHOWN);
    if (_window == 0)
	{
		SDL_Log(SDL_GetError());
        return false;
    }

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == 0)
	{
        SDL_Log(SDL_GetError());
        return false;
    }

	_board.clearFields();
	randomTurn();
	return true;
}

void Game::randomTurn()
{
	(random(0, 1) == 1) ? myTurn = true : myTurn = false;
}

void Game::mainLoop()
{
    while (state != STATE_QUIT)
	{
        while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				case SDL_APP_TERMINATING:
					state = STATE_QUIT;
					break;
			}
        }

		_board.update();
		_board.draw();
		_board.checkWinConditions();
	}

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
