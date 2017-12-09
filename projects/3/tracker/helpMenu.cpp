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

int HelpMenu::fontSize()const{
	float fontWidthsize = width * 0.1;
	float fontHeightsize = height * 0.1;
	if(fontWidthsize < fontHeightsize) {
		return (int)fontWidthsize;
	}
	return (int)fontHeightsize;
}


void HelpMenu::draw() const {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 100, 100, 100, 170 );
    SDL_RenderFillRect( renderer, &rect );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &rect );
    IOmod::getInstance().writeText("CONTROLS", x+250, y+5, textFontColor, 18);
    IOmod::getInstance().writeText("F1 ........ Toggle this menu   |", x+15, y+30,textFontColor, 16);
    IOmod::getInstance().writeText("R ......... Restart Game       |   WASD ......... Movement", x+15, y+50,textFontColor, 16);
    IOmod::getInstance().writeText("P ......... Pause Game         |   Space Bar .... Shoot", x+15, y+70,textFontColor, 16);
    IOmod::getInstance().writeText("ESC or Q .. Quit Game          |", x+15, y+90,textFontColor, 16);
}
