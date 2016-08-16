#include "Main.h"
#include "Board.h"
#include "AI.h"
#include "Cross.h"
#include "Circle.h"

void Board::clearFields()
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
			_fields[x][y] = FIELD_EMPTY;
	}
}

void Board::update()
{
    static AI ai;

    int displayW = game.getDisplayWidth();
    int displayH = game.getDisplayHeight();

	if (game.state == Game::STATE_PLAY)
	{
		if (!game.myTurn)
		{
			ai.update(this);
			game.moves++;
			game.myTurn = true;

			// Delay between AI and player move.
			SDL_Delay(100);
		}
		else /* !MyTurn */
		{
			if (game.event.type == SDL_MOUSEBUTTONDOWN &&
                game.event.button.state == SDL_PRESSED &&
				game.event.button.button == SDL_BUTTON_LEFT)
			{
				int x = game.event.button.x / (displayW / 3.0f);
				int y = game.event.button.y / (displayH / 3.0f);
				playerMove(x, y);
			}
			else if (game.event.type == SDL_FINGERDOWN)
			{
				int x = static_cast<int>(game.event.tfinger.x *
                             displayW / (displayW / 3.0f));
				int y = static_cast<int>(game.event.tfinger.y *
                             displayH / (displayH / 3.0f));
				playerMove(x, y);
			}
		}
	}
	else
	{
		if ((game.event.type == SDL_MOUSEBUTTONDOWN &&
            game.event.button.state == SDL_PRESSED &&
			game.event.button.button == SDL_BUTTON_LEFT) ||
            game.event.type == SDL_FINGERDOWN)
		{
			game.moves = 0;
			game.state = Game::STATE_PLAY;
			clearFields();

			// Delay to prevent immediately starting new game.
			SDL_Delay(100);
		}
	}
}

void Board::draw()
{
    SDL_Renderer* renderer = game.getRenderer();
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	drawLines();
    drawMarks();
}

void Board::checkWinConditions()
{
    SDL_Renderer* renderer = game.getRenderer();
    int displayW = game.getDisplayWidth();
    int displayH = game.getDisplayHeight();

	// Horizontal win
    for (int y = 0; y < 3; y++)
	{
		// AI
		if (isFieldCircle(0, y) && isFieldCircle(1, y) && isFieldCircle(2, y))
		{
			SDL_RenderDrawLine(renderer, 0, 2 * (y * (displayH / 3 / 2)) + (displayH / 3 / 2),
				displayW, 2 * (y * (displayH / 3 / 2)) + (displayH / 3 / 2));
			if (game.state == Game::STATE_PLAY)
                game.state = Game::STATE_LOSE;
		}

		// Player
		if (isFieldCross(0, y) && isFieldCross(1, y) && isFieldCross(2, y))
		{
			SDL_RenderDrawLine(renderer, 0, 2 * (y * (displayH / 3 / 2)) + (displayH / 3 / 2),
				displayW, 2 * (y * (displayH / 3 / 2)) + (displayH / 3 / 2));
			if (game.state == Game::STATE_PLAY)
                game.state = Game::STATE_WIN;
        }
	}

	// Vertical Win
    for (int x = 0; x < 3; x++)
	{
		// AI
		if (isFieldCircle(x, 0) && isFieldCircle(x, 1) && isFieldCircle(x, 2))
		{
			SDL_RenderDrawLine(renderer, 2 * (x * (displayW / 3 / 2)) + (displayW / 3 / 2), 0,
				2 * (x * (displayW / 3 / 2)) + (displayW / 3 / 2), displayW);
			if (game.state == Game::STATE_PLAY)
                game.state = Game::STATE_LOSE;
		}

		// Player
		if (isFieldCross(x, 0) && isFieldCross(x, 1) && isFieldCross(x, 2))
		{
			SDL_RenderDrawLine(renderer, 2 * (x * (displayW / 3 / 2)) + (displayW / 3 / 2), 0,
				2 * (x * (displayW / 3 / 2)) + (displayW / 3 / 2), displayW);
			if (game.state == Game::STATE_PLAY)
                game.state = Game::STATE_WIN;
        }
	}


	// AI - diagonal win
    if (isFieldCircle(0, 0) && isFieldCircle(1, 1) && isFieldCircle(2, 2))
	{
		SDL_RenderDrawLine(renderer, 0, 0, displayW, displayH);
		if (game.state == Game::STATE_PLAY)
            game.state = Game::STATE_LOSE;
	}
    else if (isFieldCircle(2, 0) && isFieldCircle(1, 1) && isFieldCircle(0, 2))
	{
		SDL_RenderDrawLine(renderer, displayW, 0, 0, displayH);
		if (game.state == Game::STATE_PLAY)
            game.state = Game::STATE_LOSE;
	}
	// Player - diagonal win
	else if (isFieldCross(0, 0) && isFieldCross(1, 1) && isFieldCross(2, 2))
	{
		SDL_RenderDrawLine(renderer, 0, 0, displayW, displayH);
		if (game.state == Game::STATE_PLAY)
            game.state = Game::STATE_WIN;
	}
	else if (isFieldCross(2, 0) && isFieldCross(1, 1) && isFieldCross(0, 2))
	{
		SDL_RenderDrawLine(renderer, displayW, 0, 0, displayH);
		if (game.state == Game::STATE_PLAY)
            game.state = Game::STATE_WIN;
	}

	// Draw
	if (game.moves >= 9 && game.state == Game::STATE_PLAY)
        game.state = Game::STATE_DRAW;

	SDL_RenderPresent(renderer);
}

bool Board::isFieldEmpty(int x, int y) const
{
    return (_fields[x][y] == FIELD_EMPTY);
}

bool Board::isFieldCross(int x, int y) const
{
    return (_fields[x][y] == FIELD_CROSS);
}

bool Board::isFieldCircle(int x, int y) const
{
    return (_fields[x][y] == FIELD_CIRCLE);
}

void Board::setFieldToCross(int x, int y)
{
    _fields[x][y] = FIELD_CROSS;
}

void Board::setFieldToCircle(int x, int y)
{
    _fields[x][y] = FIELD_CIRCLE;
}

void Board::playerMove(int x, int y)
{
    if (x > 3) x = 2;
    if (y > 3) y = 2;

    if (isFieldEmpty(x, y))
    {
        setFieldToCross(x, y);
        game.moves++;
        game.myTurn = false;

        // Delay between player and AI move.
        SDL_Delay(100);
    }
}

void Board::drawLines()
{
    SDL_Renderer* renderer = game.getRenderer();
    int displayW = game.getDisplayWidth();
    int displayH = game.getDisplayHeight();

	SDL_RenderDrawLine(renderer, 0, displayH / 3, displayW, displayH / 3);
	SDL_RenderDrawLine(renderer, 0, displayH - displayH / 3, displayW, displayH - displayH / 3);
	SDL_RenderDrawLine(renderer, displayW / 3, 0, displayW / 3, displayH);
	SDL_RenderDrawLine(renderer, displayW - displayW / 3, 0,  displayW - displayW / 3, displayH);
}

void Board::drawMarks()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			switch (_fields[x][y])
			{
				case FIELD_CROSS:
					Cross::draw(x, y);
                    break;

				case FIELD_CIRCLE:
                    Circle::draw(x, y);
					break;
			}
		}
	}
}
