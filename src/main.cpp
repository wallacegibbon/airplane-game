#include <QApplication>
#include "Game.h"

Game *game;

int main(int argc, const char *argv[])
{
    QApplication app(argc, const_cast<char **>(argv));

    game = new Game(800, 600);
    game->show();

    return app.exec();
}