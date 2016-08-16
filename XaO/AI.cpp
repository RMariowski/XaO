#include "Main.h"
#include "AI.h"
#include "Board.h"

void AI::update(Board* board)
{
    bool end = horizontalCheck(board);
    if (end) return;

    end = verticalCheck(board);
    if (end) return;

    end = diagonalCheck(board);
    if (end) return;

    end = verticalBlock(board);
    if (end) return;

    end = diagonalBlock(board);
    if (end) return;

	randomMove(board);
}

bool AI::horizontalCheck(Board* board)
{
    for (int y = 0; y < 3; y++)
	{
        if (board->isFieldCircle(0, y) && board->isFieldCircle(1, y) && 
			board->isFieldEmpty(2, y))
		{
			board->setFieldToCircle(2, y);
			return true;
        }
		else if (board->isFieldCircle(1, y) && board->isFieldCircle(2, y) && 
			board->isFieldEmpty(0, y))
		{
			board->setFieldToCircle(0, y);
			return true;
        }
		else if (board->isFieldCircle(0, y) && board->isFieldCircle(2, y) && 
			board->isFieldEmpty(1, y))
		{
			board->setFieldToCircle(1, y);
			return true;
        }
    }
    return false;
}

bool AI::verticalCheck(Board* board)
{
    for (int x = 0; x < 3; x++)
	{
        if (board->isFieldCircle(x, 0) && board->isFieldCircle(x, 1) && 
			board->isFieldEmpty(x, 2))
		{
			board->setFieldToCircle(x, 2);
			return true;
        }
		else if (board->isFieldCircle(x, 1) && board->isFieldCircle(x, 2) && 
			board->isFieldEmpty(x, 0))
		{
			board->setFieldToCircle(x, 0);
			return true;
        }
		else if (board->isFieldCircle(x, 0) && board->isFieldCircle(x, 2) && 
			board->isFieldEmpty(x, 1))
		{
			board->setFieldToCircle(x, 1);
			return true;
        }
	}
	return false;
}

bool AI::diagonalCheck(Board* board)
{
    if (board->isFieldCircle(0, 0) && board->isFieldCircle(1, 1) && board->isFieldEmpty(2, 2))
	{
		board->setFieldToCircle(2, 2);
		return true;
	}
    else if (board->isFieldCircle(1, 1) && board->isFieldCircle(2, 2) && 
		board->isFieldEmpty(0, 0))
	{
		board->setFieldToCircle(0, 0);
		return true;
	}
	else if (board->isFieldCircle(2, 0) && board->isFieldCircle(1, 1) && 
		board->isFieldEmpty(0, 2))
	{
		board->setFieldToCircle(0, 2);
		return true;
	}
    else if (board->isFieldCircle(0, 2) && board->isFieldCircle(1, 1) && 
		board->isFieldEmpty(2, 0))
	{
		board->setFieldToCircle(2, 0);
		return true;
	}
	return false;
}

bool AI::horizontalBlock(Board* board)
{
    for (int y = 0; y < 3; y++)
	{
        if (board->isFieldCross(0, y) && board->isFieldCross(1, y) && 
			board->isFieldEmpty(2, y))
		{
			board->setFieldToCircle(2, y);
			return true;
        }
        else if (board->isFieldCross(0, y) && board->isFieldCross(2, y) && 
			board->isFieldEmpty(1, y))
		{
			board->setFieldToCircle(1, y);
			return true;
		}
		else if (board->isFieldCross(1, y) && board->isFieldCross(2, y) && 
			board->isFieldEmpty(0, y))
		{
			board->setFieldToCircle(0, y);
			return true;
		}
    }
    return false;
}

bool AI::verticalBlock(Board* board)
{
    for (int x = 0; x < 3; x++)
	{
        if (board->isFieldCross(x, 0) && board->isFieldCross(x, 1) && 
			board->isFieldEmpty(x, 2))
		{
			board->setFieldToCircle(x, 2);
			return true;
        }
        else if (board->isFieldCross(x, 0) && board->isFieldCross(x, 2) && 
			board->isFieldEmpty(x, 1))
		{
			board->setFieldToCircle(x, 1);
			return true;
        }
		else if (board->isFieldCross(x, 1) && board->isFieldCross(x, 2) && 
			board->isFieldEmpty(x, 0))
		{
			board->setFieldToCircle(x, 0);
			return true;
        }
    }
    return false;
}

bool AI::diagonalBlock(Board* board)
{
    if (board->isFieldCross(0, 0) && board->isFieldCross(1, 1) && 
		board->isFieldEmpty(2, 2))
	{
		board->setFieldToCircle(2, 2);
		return true;
	}
    else if (board->isFieldCross(1, 1) && board->isFieldCross(2, 2) && 
		board->isFieldEmpty(0, 0))
	{
		board->setFieldToCircle(0, 0);
		return true;
	}
    else if (board->isFieldCross(0, 0) && board->isFieldCross(1, 1) && 
		board->isFieldEmpty(2, 2))
	{
        board->setFieldToCircle(2, 2);
        return true;
	}
	else if (board->isFieldCross(0, 2) && board->isFieldCross(1, 1) && 
		board->isFieldEmpty(2, 0))
	{
		board->setFieldToCircle(2, 0);
		return true;
	}
    else if (board->isFieldCross(2, 0) && board->isFieldCross(1, 1) && 
		board->isFieldEmpty(0, 2))
	{
		board->setFieldToCircle(0, 2);
		return true;
	}
    return false;
}

void AI::randomMove(Board* board)
{
	// Random move (just in case)
	int x;
	int y;
	do
	{
		x = random(0, 2);
		y = random(0, 2);
	} while (!board->isFieldEmpty(x, y));

	board->setFieldToCircle(x, y);
}
