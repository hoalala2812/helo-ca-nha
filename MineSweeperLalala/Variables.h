#pragma once

#ifndef _VARIABLES_H//_INCLUDED
#define _VARIABLES_H//_INCLUDED

#include <vector>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Button.h"

using namespace std;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

extern int BOARD_SIZE_X;
extern int BOARD_SIZE_Y;
extern int sumOfMines;
extern int numOfMines;
extern int numOfTiles;

//toa do board
extern const int board_x;
extern const int board_y;

//toa do digit & face
extern int digit_x;
extern int face_x;
extern int digit_y;

extern bool quit;
extern bool isRunning;
extern bool issGuessing;
extern bool isChoosingMode;

extern bool easy;
extern bool medium;
extern bool hard;

extern bool playAgain;
extern bool newGame;

extern bool winGame;
extern bool loseGame;

extern int mlose;
extern int nlose;

//Mouse button sprites
extern LTexture gTilesSpriteSheetTexture;
extern SDL_Rect gSpriteClips[12];

//mouse digit sprites
extern SDL_Rect gSpriteClipsForDigit[10];
extern LTexture gDigitSpriteSheetTexture;

//Texture load from text
extern LTexture menu;
extern LTexture menu1;
extern LTexture menuColor;
extern LTexture menu1Color;
extern LTexture easyChoice;
extern LTexture mediumChoice;
extern LTexture hardChoice;
extern LTexture easyChoiceColor;
extern LTexture mediumChoiceColor;
extern LTexture hardChoiceColor;

extern LTexture easyBackGround;
extern LTexture mediumBackGround;
extern LTexture hardBackGround;

extern LTexture goBackT;
extern LTexture muteSoundT;
extern LTexture unMuteSoundT;

//3 cai mat
extern LTexture winFace;
extern LTexture loseFace;
extern LTexture playingFace;

extern LTexture redMine;

// audio
extern bool mute;
extern Mix_Chunk* click;
extern Mix_Music* loseMusic;
extern Mix_Music* winMusic;

//flag board
extern vector<vector<int>> boardForShow;
//mine board
extern vector<vector<int>> board;

#endif // VARIABLES_H_INCLUDED
