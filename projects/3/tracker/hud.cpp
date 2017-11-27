#include "hud.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>

Hud& Hud::getInstance(Player* player){
    static Hud instance(player);
    return instance;
}

Hud::~Hud()
{}

Hud::Hud(Player* player):
    player(player),
    width(Gamedata::getInstance().getXmlInt("hud/width")),
    height(Gamedata::getInstance().getXmlInt("hud/height")),
    hudx(Gamedata::getInstance().getXmlInt("hud/start/x")),
    hudy(Gamedata::getInstance().getXmlInt("hud/start/y")),
    hudRect({hudx,hudy,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    io( IOmod::getInstance() ),
    textFontColor({0, 0, 0, 0})
{}

int Hud::fontSize()const{
	float fontWidthsize = width * 0.1;
	float fontHeightsize = height * 0.1;
	if(fontWidthsize < fontHeightsize) {
		return (int)fontWidthsize;
	}
	return (int)fontHeightsize;
}


void Hud::displayHud() const {
    int fSize = fontSize();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect );
    IOmod::getInstance().writeText("Press: ", hudx+15, hudy+20,textFontColor, fSize);
    IOmod::getInstance().writeText("F1: Toggle this menu", hudx+15, hudy+50,textFontColor, fSize);
    IOmod::getInstance().writeText("WASD: Movement ", hudx+15, hudy+80,textFontColor, fSize);
    IOmod::getInstance().writeText("-----------------------", hudx+15, hudy+110,textFontColor, fSize);
    std::stringstream strm;
    strm << "Bullets in use: " << player->bulletCount();
    IOmod::getInstance().writeText(strm.str(), hudx+15, hudy+140,textFontColor, fSize);
    strm.clear();
    strm.str("");
    strm << "Bullets in pool: " << player->freeCount();
    IOmod::getInstance().writeText(strm.str(), hudx+15, hudy+170, textFontColor, fSize);
}
