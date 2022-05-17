#include <iostream>
#include "main.h"
#include "Button.h"
#include "ThapCam.h"

using namespace std;

LButton::LButton(){
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int x, int y){
	mPosition.x = x;
	mPosition.y = y;
}

//faceBt.hand
void LButton::handlePlayAgain(SDL_Event* e){
	if (e->type == SDL_MOUSEBUTTONDOWN){
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		//Mouse is out of the button
		if (x < mPosition.x || x > mPosition.x+faceButton_size){
			inside = false;
		} else if (y < mPosition.y || y > mPosition.y+faceButton_size){
			inside = false;
		}

		if (inside && e->button.button == SDL_BUTTON_LEFT){
            playAgain = true;
		}
	}
}

//muteBt.hand
void LButton::handleMute(SDL_Event* e){
	if (e->type == SDL_MOUSEBUTTONDOWN){
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		//Mouse is out of the button
		if (x < mPosition.x || x > mPosition.x + muteButton_size){
			inside = false;
		} else if (y < mPosition.y || y > mPosition.y + muteButton_size){
			inside = false;
		}

		if (inside && e->button.button == SDL_BUTTON_LEFT){
		    if(mute == true) mute = false;
            else mute = true;
		}
	}
}

void LButton::handleEvent(SDL_Event* e, int &mlose, int &nlose){
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		int i = (x - board_x)/TILE_SIZE;
		int j = (y - board_y)/TILE_SIZE;

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x || x > mPosition.x + TILE_SIZE){
			inside = false;
		} else if (y < mPosition.y || y > mPosition.y + TILE_SIZE){
			inside = false;
		}

		//Mouse is inside button
		if (inside){
			if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT){
                loang1(i, j);
                loang2(i, j);
                numOfTiles = 0;
                for (int i = 0; i < BOARD_SIZE_X; i++){
                    for (int j = 0; j < BOARD_SIZE_Y; j++){
                        if(boardForShow[i][j] == 10) numOfTiles++;
                        if(boardForShow[i][j] == 9){
                            loseGame = true;
                            mlose = i; nlose = j;
                        }
                    }
                }
                // win
                if (numOfTiles == numOfMines){
                    winGame = true;
                    for(int i=0;i<BOARD_SIZE_X-1;i++) {
                        for(int j=0;j<BOARD_SIZE_Y-1;j++) {
                            if(boardForShow[i][j]==11 && board[i][j]!=9) {
                                winGame = false;
                            }
                        }
                    }
                    if(winGame) Mix_PlayMusic(winMusic, 1);
                }
                // lose
                if (board[i][j] == 9){
                    loseGame = true;
                    Mix_PlayMusic(loseMusic, 1);
                    mlose = i; nlose = j;
                }
                // just click
                else{
                    Mix_PlayChannel(-1, click, 0);
                }
			} else if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_RIGHT){
			    Mix_PlayChannel(-1, click, 0);
                if(boardForShow[i][j] == 10){
                    boardForShow[i][j] = 11;
                    numOfMines--;
                } else if(boardForShow[i][j] == 11){
                    boardForShow[i][j] = 10;
                    numOfMines++;
                }
			}
		}
	}
}

void LButton::render(int i, int j){
	//Show current button sprite
	gTilesSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[boardForShow[i][j]]);
}

void LButton::renderWhenLose(int i, int j){
	//Show all button sprite
	gTilesSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[board[i][j]]);
	if(boardForShow[i][j]==11 && board[i][j]==9) gTilesSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[boardForShow[i][j]]);
}
