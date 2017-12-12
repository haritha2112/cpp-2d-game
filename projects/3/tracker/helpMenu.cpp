#include "helpMenu.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>

HelpMenu& HelpMenu::getInstance(){
    static HelpMenu instance;
    return instance;
}

HelpMenu::~HelpMenu() {}

HelpMenu::HelpMenu():
    width(Gamedata::getInstance().getXmlInt("helpMenu/width")),
    height(Gamedata::getInstance().getXmlInt("helpMenu/height")),
    x(Gamedata::getInstance().getXmlInt("helpMenu/start/x")),
    y(Gamedata::getInstance().getXmlInt("helpMenu/start/y")),
    rect({x,y,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    io( IOmod::getInstance() ),
    textFontColor({255, 255, 255, 255})
{}

void HelpMenu::draw() const {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 100, 100, 100, 170 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &rect );
    IOmod::getInstance().writeText("CONTROLS", x+255, y+5, textFontColor, 18);
    IOmod::getInstance().writeText(" Help Aqua go to her nest! Collect all the eggs and kill the enemies ", x+15, y+30,textFontColor, 16);
    IOmod::getInstance().writeText("F1 ........ Toggle this menu     |   WASD ......... Movement", x+15, y+50,textFontColor, 16);
    IOmod::getInstance().writeText("R ......... Restart Game         |   Space Bar .... Shoot", x+15, y+70,textFontColor, 16);
    IOmod::getInstance().writeText("P ......... Pause Game           |   G ............ God Mode", x+15, y+90,textFontColor, 16);
    IOmod::getInstance().writeText("E ......... Toggle Sound Effects |", x+15, y+110,textFontColor, 16);
    IOmod::getInstance().writeText("M ......... Toggle Music         |       Reach the tree", x+15, y+130,textFontColor, 16);
    IOmod::getInstance().writeText("ESC or Q .. Quit Game            |           to win", x+15, y+150,textFontColor, 16);
}
