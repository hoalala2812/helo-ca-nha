#ifndef _BUTTON_H//_INCLUDED
#define _BUTTON_H//_INCLUDED

#include <SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

using namespace std;

class LButton{
public:
    //Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	void handleEvent(SDL_Event* e, int &mlose, int &nlose);
	//void handleBack(SDL_Event* e);
	void handleMute(SDL_Event* e);
	void handlePlayAgain(SDL_Event* e);

	//Shows button sprite
	void render(int i, int j);
	void renderWhenLose(int i, int j);

private:
	//Top left position
	SDL_Point mPosition;
};

#endif // BUTTON_H_INCLUDED
