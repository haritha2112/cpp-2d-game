#include "hud.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>

Hud& Hud::getInstance(){
    static Hud instance;
    return instance;
}

Hud::~Hud()
{}

Hud::Hud():
    width(Gamedata::getInstance().getXmlInt("hud/width")),
    height(Gamedata::getInstance().getXmlInt("hud/height")),
    hudx(Gamedata::getInstance().getXmlInt("hud/start/x")),
    hudy(Gamedata::getInstance().getXmlInt("hud/start/y")),
    hudRect({hudx,hudy,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    io( IOmod::getInstance() ),
    textFontColor({0, 0, 0, 255})
{}

int Hud::fontSize()const{
	float fontWidthsize = width * 0.09;
	float fontHeightsize = height * 0.09;
	if(fontWidthsize < fontHeightsize)
	{
		return (int)fontWidthsize;
	}
	
	return (int)fontHeightsize;
}


void Hud::displayHud() const {
    int fSize = fontSize();
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect );
    IOmod::getInstance().writeText("Press: ", hudx+15, hudy+105,textFontColor, fSize);
    IOmod::getInstance().writeText("F1 to toggle Help", hudx+15, hudy+140,textFontColor, fSize);
    IOmod::getInstance().writeText("a: Move Left ", hudx+15, hudy+165,textFontColor, fSize);
    IOmod::getInstance().writeText("d: Move Right", hudx+15, hudy+190,textFontColor, fSize);
    IOmod::getInstance().writeText("w: Move up", hudx+15, hudy+215,textFontColor, fSize);
    IOmod::getInstance().writeText("s: Move down: ", hudx+15, hudy+240, textFontColor, fSize);
}

