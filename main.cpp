#include "spaceinvaders.h"
#include <QScreen>
#include <QApplication>

CSpaceInvaders* pGame;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CSpaceInvaders* pGame = new CSpaceInvaders(qApp->screens()[0]->size());
    pGame->showFullScreen();
    pGame->Menu();

    return a.exec();
}
