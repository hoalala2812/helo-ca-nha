#include <iostream>
#include "Variables.h"

using namespace std;

extern SDL_Window* gWindow = NULL;
extern SDL_Renderer* gRenderer = NULL;
extern TTF_Font* gFont = NULL;

extern SDL_Color textColor = {0,0,255};

extern int BOARD_SIZE_X = 0;
extern int BOARD_SIZE_Y = 0;
extern int sumOfMines = 1;
extern int numOfMines = 0;
extern int numOfTiles = 1;

//toa do board
extern const int board_x = 21;
extern const int board_y = 72;

//toa do digit & face
extern int digit_x = 0;
extern int face_x = 0;
extern int digit_y = 50;

extern bool quit = false;
extern bool isRunning = false;
extern bool issGuessing = true;
extern bool isChoosingMode = true;

extern bool easy = false;
extern bool medium = false;
extern bool hard = false;

extern bool playAgain = false;
extern bool newGame = true;

extern bool winGame = false;
extern bool loseGame = false;

extern int mlose = -1;
extern int nlose = -1;

//Mouse button sprites
extern SDL_Rect gSpriteClips[12] = {};
LTexture gTilesSpriteSheetTexture = LTexture();

//mouse digit sprites
extern SDL_Rect gSpriteClipsForDigit[10] = {};
extern LTexture gDigitSpriteSheetTexture = LTexture();

//Texture load from text
extern LTexture menu = LTexture();
extern LTexture menu1 = LTexture();
extern LTexture menuColor = LTexture();
extern LTexture menu1Color = LTexture();
extern LTexture easyChoice = LTexture();
extern LTexture mediumChoice = LTexture();
extern LTexture hardChoice = LTexture();
extern LTexture easyChoiceColor = LTexture();
extern LTexture mediumChoiceColor = LTexture();
extern LTexture hardChoiceColor = LTexture();

extern LTexture easyBackGround = LTexture();
extern LTexture mediumBackGround = LTexture();
extern LTexture hardBackGround = LTexture();
extern LTexture goBackT = LTexture();
extern LTexture muteSoundT = LTexture();
extern LTexture unMuteSoundT = LTexture();

//3 cai mat
extern LTexture winFace = LTexture();
extern LTexture loseFace = LTexture();
extern LTexture playingFace = LTexture();

extern LTexture redMine = LTexture();

// audio
extern bool mute = false;
extern Mix_Chunk* click = NULL;
extern Mix_Music* loseMusic = NULL;
extern Mix_Music* winMusic = NULL;

extern vector<vector<int>> boardForShow(3, vector<int>(2,0));
extern vector<vector<int>> board(3, vector<int>(2, 0));
