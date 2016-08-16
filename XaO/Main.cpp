#include "Main.h"
#include <cstdlib>

int random(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int main(int argc, char** argv)
{
	if (!game.init())
        return -1;

    game.mainLoop();

    return 0;
}
