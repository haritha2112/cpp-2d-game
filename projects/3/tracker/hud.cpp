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

Hud::~Hud() {}

Hud::Hud(Player* player):
    player(player),
    heartImage(RenderContext::getInstance()->getImage("hudHeart")),
    eggImage(RenderContext::getInstance()->getImage("hudEgg")),
    deadGreenEnemy(RenderContext::getInstance()->getImages("hudDeadGreenEnemy")),
    deadRedEnemy(RenderContext::getInstance()->getImages("hudDeadRedEnemy")),
    width(Gamedata::getInstance().getXmlInt("hud/width")),
    height(Gamedata::getInstance().getXmlInt("hud/height")),
    hudx(Gamedata::getInstance().getXmlInt("hud/start/x")),
    hudy(Gamedata::getInstance().getXmlInt("hud/start/y")),
    hudRect({hudx,hudy,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    io( IOmod::getInstance() ),
    textFontColor({255,255,255,255})
{}

int Hud::fontSize() const {
	float fontWidthsize = width * 0.1;
	float fontHeightsize = height * 0.1;
	if(fontWidthsize < fontHeightsize) {
		return (int)fontWidthsize;
	}
	return (int)fontHeightsize;
}

void Hud::drawHealthBar(int x, int y, int w, int h, float percent) const {
   SDL_Color FGColor({0, 255, 0, 200});
   SDL_Color BGColor({255, 0, 0, 255});
   SDL_Rect bgrect = { x, y, w, h };
   SDL_SetRenderDrawColor(renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
   SDL_RenderFillRect(renderer, &bgrect);
   SDL_SetRenderDrawColor(renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
   int pw =  (int)((float)w * (percent/100));
   SDL_Rect fgrect = { x, y, pw, h };
   SDL_RenderFillRect(renderer, &fgrect);
}


void Hud::draw(const Vector2f& position) const {
    std::stringstream strm;
    int fSize = fontSize();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 100, 100, 100, 200 );
    SDL_RenderFillRect( renderer, &hudRect );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect );

    heartImage->draw(position[0]+hudx+20, position[1]+hudy+10, 0.25);
    strm << player->getRemainingLives();
    IOmod::getInstance().writeText(strm.str(), hudx+60, hudy+15, textFontColor, 20);

    drawHealthBar(hudx+80, hudy+20, 150, 15, player->getCurrentHealth()*100/player->getTotalHealth());

    eggImage->draw(position[0]+hudx+310, position[1]+hudy+10, 1);
    strm.clear();
    strm.str("");
    strm << player->getNumEggsCollected();
    IOmod::getInstance().writeText(strm.str(), hudx+350, hudy+15, textFontColor, 20);
    //
    deadGreenEnemy[0]->draw(position[0]+hudx+470, position[1]+hudy+10, 0.8);
    deadRedEnemy[0]->draw(position[0]+hudx+520, position[1]+hudy+5, 0.8);
    strm.clear();
    strm.str("");
    strm << player->getNumEnemiesDestroyed();
    IOmod::getInstance().writeText(strm.str(), hudx+570, hudy+15, textFontColor, 20);

    IOmod::getInstance().writeText("Haritha Rathinakumar", hudx+650, hudy+15, textFontColor, 18);
}
