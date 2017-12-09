#include "gameOverBox.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>

GameOverBox& GameOverBox::getInstance(Player* player){
    static GameOverBox instance(player);
    return instance;
}

GameOverBox::~GameOverBox() {}

GameOverBox::GameOverBox(Player* player):
    player(player),
    heartImage(RenderContext::getInstance()->getImage("hudHeart")),
    eggImage(RenderContext::getInstance()->getImage("hudEgg")),
    deadGreenEnemy(RenderContext::getInstance()->getImages("hudDeadGreenEnemy")),
    deadRedEnemy(RenderContext::getInstance()->getImages("hudDeadRedEnemy")),
    width(Gamedata::getInstance().getXmlInt("gameOverBox/width")),
    height(Gamedata::getInstance().getXmlInt("gameOverBox/height")),
    x(Gamedata::getInstance().getXmlInt("gameOverBox/start/x")),
    y(Gamedata::getInstance().getXmlInt("gameOverBox/start/y")),
    rect({x,y,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    io( IOmod::getInstance() ),
    textFontColor({255,255,255,255})
{}

void GameOverBox::draw(const Vector2f& position, const bool playerWon) const {
    std::ostringstream strm;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 100, 100, 100, 200 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &rect );

    IOmod::getInstance().writeText("GAME OVER", x+140, y+15, textFontColor, 28);
    if ( playerWon ) {
      IOmod::getInstance().writeText("YOU WON", x+170, y+50, textFontColor, 20);
    } else {
      IOmod::getInstance().writeText("YOU LOST", x+170, y+50, textFontColor, 20);
    }

    heartImage->draw(position[0]+x+50, position[1]+y+100, 0.25);
    strm << std::setw(2) << std::setfill(' ') << player->getRemainingLives();
    IOmod::getInstance().writeText(strm.str(), x+110, y+103, textFontColor, 20);
    IOmod::getInstance().writeText("  x  100   =   ", x+140, y+103, textFontColor, 20);
    int heartScore = player->getRemainingLives() * 100;
    strm.clear();
    strm.str("");
    strm << std::setw(3) << std::setfill(' ') << heartScore;
    IOmod::getInstance().writeText(strm.str(), x+300, y+103, textFontColor, 20);

    eggImage->draw(position[0]+x+50, position[1]+y+140, 1);
    strm.clear();
    strm.str("");
    strm << std::setw(2) << std::setfill(' ') << player->getNumEggsCollected();
    IOmod::getInstance().writeText(strm.str(), x+110, y+146, textFontColor, 20);
    IOmod::getInstance().writeText("  x   20   =   ", x+140, y+146, textFontColor, 20);
    int eggScore = player->getNumEggsCollected() * 20;
    strm.clear();
    strm.str("");
    strm << std::setw(3) << std::setfill(' ') << eggScore;
    IOmod::getInstance().writeText(strm.str(), x+300, y+146, textFontColor, 20);

    deadGreenEnemy[0]->draw(position[0]+x+10, position[1]+y+185, 0.8);
    deadRedEnemy[0]->draw(position[0]+x+50, position[1]+y+180, 0.8);
    strm.clear();
    strm.str("");
    strm << std::setw(2) << std::setfill(' ') << player->getNumEnemiesDestroyed();
    IOmod::getInstance().writeText(strm.str(), x+110, y+190, textFontColor, 20);
    IOmod::getInstance().writeText("  x    5   =   ", x+140, y+190, textFontColor, 20);
    int enemyScore = player->getNumEnemiesDestroyed() * 5;
    strm.clear();
    strm.str("");
    strm << std::setw(3) << std::setfill(' ') << enemyScore;
    IOmod::getInstance().writeText(strm.str(), x+300, y+190, textFontColor, 20);

    IOmod::getInstance().writeText("Total Score :  ", x+140, y+236, textFontColor, 20);
    strm.clear();
    strm.str("");
    strm << std::setw(3) << std::setfill(' ') << enemyScore + eggScore + heartScore;
    IOmod::getInstance().writeText(strm.str(), x+300, y+236, textFontColor, 20);

    IOmod::getInstance().writeText("(R) Restart   |   (Q) Quit", x+90, y+300, textFontColor, 16);
}
