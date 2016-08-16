#pragma once

class Board;

class AI
{
public:
    void update(Board* board);

private:
    bool horizontalCheck(Board* board);

    bool verticalCheck(Board* board);

    bool diagonalCheck(Board* board);

    bool horizontalBlock(Board* board);

    bool verticalBlock(Board* board);

    bool diagonalBlock(Board* board);

    void randomMove(Board* board);
};
