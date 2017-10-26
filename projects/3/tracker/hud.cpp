#include "hud.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>

Hud::~Hud()
{}

Hud::Hud():
    width(Gamedata::getInstance().getXmlInt("hud/width")),
    height(Gamedata::getInstance().getXmlInt("hud/height")),
    hudx(Gamedata::getInstance().getXmlInt("hud/start/x")),
    hudy(Gamedata::getInstance().getXmlInt("hud/start/y")),
    hudRect({hudx,hudy,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    clock(Clock::getInstance()),
    io( IOmod::getInstance() ),
    textFontColor({0, 0, 0, 255})
{}

int Hud::fontSize()const{
	float fWsize = width * 0.09;
	float fHsize = height * 0.09;
	if(fWsize < fHsize)
	{
		return (int)fWsize;
	}
	
	return (int)fHsize;
}


void Hud::displayHud() const{
    int fSize = fontSize();
    std::stringstream fps;
    fps << "Fps: " << clock.getFps();
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect );
    IOmod::getInstance().writeText(fps.str(), hudx+15, hudy+15, textFontColor, fSize);
    IOmod::getInstance().writeText("Press: ", hudx+15, hudy+140,textFontColor, fSize);
    IOmod::getInstance().writeText("a: Move Left ", hudx+15, hudy+165,textFontColor, fSize);
    IOmod::getInstance().writeText("d: Move Right", hudx+15, hudy+190,textFontColor, fSize);
    IOmod::getInstance().writeText("w: Move up", hudx+15, hudy+215,textFontColor, fSize);
    IOmod::getInstance().writeText("s: Move down: ", hudx+15, hudy+240, textFontColor, fSize);
}



void Hud::displayLoose() const{
	SDL_Rect looseRect = {300,200,200,100};

    int fSize = fontSize();
    std::stringstream str1;
    str1 << "Game Over!! ";
    std::stringstream str2;
    str2 << "You Lose";
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &looseRect );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &looseRect );
    IOmod::getInstance().writeText(str1.str(), 320+15, 200+15, textFontColor, fSize);
    IOmod::getInstance().writeText(str2.str(), 320+15, 200+40, textFontColor, fSize);
}


void Hud::displayWin() const{
	SDL_Rect winRect = {300,200,300,100};

    int fSize = fontSize();
    std::stringstream str1;
    str1 << "Game Over!! ";
    std::stringstream str2;
    str2 << "You WIN";
    std::stringstream str3;
    str3 << "Destination Reached!! ";
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &winRect );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &winRect );
    IOmod::getInstance().writeText(str3.str(), 320+15, 200+15, textFontColor, fSize);
    IOmod::getInstance().writeText(str1.str(), 320+15, 200+45, textFontColor, fSize);
    IOmod::getInstance().writeText(str2.str(), 320+15, 200+75, textFontColor, fSize);	
}

