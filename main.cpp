#include "gamewindow.h"

int main(int argc, char *argv[])
{

    gamewindow *game= new gamewindow();

    game->game_play();

    delete game;
    return 0;
}
