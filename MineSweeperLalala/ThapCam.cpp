#include<iostream>
#include "ThapCam.h"

using namespace std;

vector<vector<LButton>> Buttons;
LButton faceBt;
LButton backBt;
LButton muteBt;

bool init() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize! SDL Error: %s\n", SDL_GetError();
		return false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning: Linear texture filtering not enabled!";
		}
		//Create window
		gWindow = SDL_CreateWindow("WELCOME TO HOALALA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			cout << "Window could not be created! SDL Error: %s\n", SDL_GetError();
			return false;
		} else {
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				cout << "Renderer could not be created! SDL Error: %s\n", SDL_GetError();
				return false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					cout << "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError();
					return false;
                }
				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					cout << "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError();
					return false;
                }
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
					cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError();
					return false;
				}
			}
		}
	}
	return true;
}

bool loadmedia(){
	//Open image of tiles
	if (!gTilesSpriteSheetTexture.loadFromFile("Tiles.png")){
		cout << "Chiu khong load duoc dau";
		return false;
	} else {
		//Set sprites
		for (int i=0;i<12;i++) {
			gSpriteClips[i].x = i*TILE_SIZE;
			gSpriteClips[i].y = 0;
			gSpriteClips[i].w = TILE_SIZE;
			gSpriteClips[i].h = TILE_SIZE;

		}
	}
	//load digits
	if (!gDigitSpriteSheetTexture.loadFromFile("numbers.png")){
		cout << "Fail numbers";
		return false;
	} else {
		//Set sprites
		for (int i = 0;i < 10;i++)
		{
			gSpriteClipsForDigit[i].x = i * 28;
			gSpriteClipsForDigit[i].y = 0;
            gSpriteClipsForDigit[i].w = 28;
			gSpriteClipsForDigit[i].h = 46;
		}
	}
	//load easy table
	if (!easyBackGround.loadFromFile("easybgr.png")){
		cout << "Fail easybg";
		return false;
	}
	//load medium table
	if (!mediumBackGround.loadFromFile("mediumbgr.png")){
		cout << "Fail mediumbg";
		return false;
	}
	//load hard table
	if (!hardBackGround.loadFromFile("hardbgr.png")){
		cout << " hardbg";
		return false;
	}
	//load face
	if (!winFace.loadFromFile("winface.png")){
		cout << "Fail winface";
		return false;
	}
	if (!loseFace.loadFromFile("loseface.png")){
		cout << "Fail loseface";
		return false;
	}
	if (!playingFace.loadFromFile("playingface.png")){
		cout << "Fail face";
		return false;
	}
	if (!goBackT.loadFromFile("backtomode.png")){
	    cout << "fail backicon";
		return false;
	}
	if (!muteSoundT.loadFromFile("muted.png")){
	    cout << "fail mute png";
		return false;
	}
	if (!unMuteSoundT.loadFromFile("unmuted.png")){
	    cout << "fail unmute png";
		return false;
	}
	if(!redMine.loadFromFile("redmine.jpg")){
        cout << "fail redmine png";
        return false;
	}
	//Open the font
	gFont = TTF_OpenFont("VHCENTB.TTF", 30);
	if (gFont == NULL){
		cout << "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError();
		return false;
	}

	//Load music
	loseMusic = Mix_LoadMUS("BomNo.wav");
	if (loseMusic == NULL){
		cout << "Failed to load lose music! SDL_mixer Error: %s\n", Mix_GetError();
		return false;
	}

	//Load sound effects
	winMusic = Mix_LoadMUS("victory bond.wav");
	if (winMusic == NULL){
		cout << "Failed to load win sound effect! SDL_mixer Error: %s\n", Mix_GetError();
		return false;
	}

	click = Mix_LoadWAV("click.wav");
	if (click == NULL){
		cout << "Failed to load click sound effect! SDL_mixer Error: %s\n", Mix_GetError();
		return false;
	}

	SDL_Color textColor = { 255,255,255 };//trang
	if (!easyChoice.loadFromRenderedText("EASY MODE", textColor)){
		cout << "Fail easy text";
		return false;
	}
	if (!mediumChoice.loadFromRenderedText("MEDIUM MODE", textColor)){
		cout << "Fail med text";
		return false;
	}
	if (!hardChoice.loadFromRenderedText("HARD MODE", textColor)){
		cout << "Fail hard text";
		return false;
	}
	SDL_Color textcolor = { 255,255,0 };//vang
	if (!easyChoiceColor.loadFromRenderedText("EASY MODE", textcolor)){
		cout << "Fail easy text cl";
		return false;
	}
	if (!mediumChoiceColor.loadFromRenderedText("MEDIUM MODE", textcolor)){
		cout << "Fail med text cl";
		return false;
	}
	if (!hardChoiceColor.loadFromRenderedText("HARD MODE", textcolor)){
		cout << "Fail hard text cl";
		return false;
	}

	return true;
}

void CreateBoard(){
	srand(time(NULL));
	int numOfMines = 0;
	//Initialization
	for (int i=0;i<BOARD_SIZE_X;i++){
		for (int j=0;j<BOARD_SIZE_Y;j++){
			boardForShow[i][j] = 10;
			board[i][j] = 0;
			/*
            9 = mine;
            10 = start;
            11 = flag;
            */
		}
	}

	//Random mines in board
	while (numOfMines<sumOfMines){
		int i = rand()%BOARD_SIZE_X;
		int j = rand()%BOARD_SIZE_Y;
		if(board[i][j]==9) continue;
		board[i][j] = 9;
		numOfMines++;
	}

	//Calculate the number of mines around each cell
	for(int i=0;i<BOARD_SIZE_X;i++){
		for(int j=0;j<BOARD_SIZE_Y;j++){
			if (board[i][j] == 9) continue;
			for(int x=-1;x<=1;x++){
				for(int y=-1;y<=1;y++){
					if(x+i<0 || y+j<0) continue;
					if(x+i>BOARD_SIZE_X-1 || y+j>BOARD_SIZE_Y-1) continue;
					if(board[x+i][y+j] == 9) board[i][j]++;
				}
			}
		}
	}
}

void setButtonPosition(){
	faceBt.setPosition(21+BOARD_SIZE_X*TILE_SIZE/2-faceButton_size/2, digit_y);
	muteBt.setPosition(BOARD_SIZE_X*TILE_SIZE + 42  - 56, 0);
	for(int i = 0;i < BOARD_SIZE_X;i++){
		for(int j = 0;j < BOARD_SIZE_Y;j++){
			Buttons[i][j].setPosition(i*TILE_SIZE + board_x, j*TILE_SIZE + board_y);
		}
	}
}

void createMenu(){
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);//black
	SDL_RenderClear(gRenderer);
	easyChoice.render((SCREEN_WIDTH-easyChoice.getWidth())/2, 150);
	mediumChoice.render((SCREEN_WIDTH-mediumChoice.getWidth())/2, 200);
	hardChoice.render((SCREEN_WIDTH-hardChoice.getWidth())/2, 250);
}

void handleMenu(){
	bool easyInside = false;
	bool mediumInside = false;
	bool hardInside = false;
	SDL_Event event;
	createMenu();
	while (isChoosingMode){
		while (SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT){
				quit = true;
				isChoosingMode = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION){
				int x, y;
				SDL_GetMouseState(&x, &y);
                if ((x > (SCREEN_WIDTH-easyChoice.getWidth())/2) && (x < (SCREEN_WIDTH-easyChoice.getWidth())/2 + easyChoice.getWidth()) && y > 150 && y < 150 + easyChoice.getHeight()) easyInside = true;
				else easyInside = false;
				if (x > (SCREEN_WIDTH-mediumChoice.getWidth())/2 && x < (SCREEN_WIDTH-mediumChoice.getWidth())/2 + mediumChoice.getWidth() && y > 200 && y < 200 + mediumChoice.getHeight()) mediumInside = true;
				else mediumInside = false;
				if (x > (SCREEN_WIDTH-hardChoice.getWidth())/2 && x < (SCREEN_WIDTH-hardChoice.getWidth())/2+ hardChoice.getWidth() && y > 250 && y < 250 + hardChoice.getHeight()) hardInside = true;
				else hardInside = false;

				if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
                    if (easyInside){
                        isRunning = true;
                        isChoosingMode = false;
                        easy = true;
                        medium = false;
                        hard = false;
                        SDL_SetWindowSize(gWindow, 294, 344);
                        setGameMode(9, 9, 10, 2, 2, 28*9+42-56, BOARD_SIZE_X, BOARD_SIZE_Y, sumOfMines, numOfMines, numOfTiles, digit_x, digit_y, face_x);
                        CreateBoard();
                    } else if(mediumInside){
                        isRunning = true;
                        isChoosingMode = false;
                        easy = false;
                        medium = true;
                        hard = false;
                        SDL_SetWindowSize(gWindow, 488, 540);
                        setGameMode(16, 16, 40, 2, 2, 28*16+42-56, BOARD_SIZE_X, BOARD_SIZE_Y, sumOfMines, numOfMines, numOfTiles, digit_x, digit_y, face_x);
                        CreateBoard();
                    } else if(hardInside){
                        isRunning = true;
                        isChoosingMode = false;
                        easy = false;
                        medium = false;
                        hard = true;
                        SDL_SetWindowSize(gWindow, 880, 540);
                        setGameMode(30, 16, 99, 2, 2, 28*30+42-56, BOARD_SIZE_X, BOARD_SIZE_Y, sumOfMines, numOfMines, numOfTiles, digit_x, digit_y, face_x);
                        CreateBoard();
                    }
				}

				if (event.type == SDL_MOUSEMOTION){
					if (easyInside == true) easyChoiceColor.render((SCREEN_WIDTH-easyChoice.getWidth())/2, 150);
					else easyChoice.render((SCREEN_WIDTH-easyChoice.getWidth())/2, 150);

					if (mediumInside == true) mediumChoiceColor.render((SCREEN_WIDTH-mediumChoice.getWidth())/2, 200);
					else mediumChoice.render((SCREEN_WIDTH-mediumChoice.getWidth())/2, 200);

					if (hardInside == true) hardChoiceColor.render((SCREEN_WIDTH-hardChoice.getWidth())/2, 250);
					else hardChoice.render((SCREEN_WIDTH-hardChoice.getWidth())/2, 250);
				}
			}
			SDL_RenderPresent(gRenderer);
		}
	}
}

void handleEventInGame(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if (e.type == SDL_QUIT){
            isRunning = false;
            quit = true;
        }
        faceBt.handlePlayAgain(&e);
        muteBt.handleMute(&e);
        for (int i = 0; i < BOARD_SIZE_X; i++){
            for (int j = 0; j < BOARD_SIZE_Y; j++){
                Buttons[i][j].handleEvent(&e, mlose, nlose);
            }
        }
    }
}

void loang1(int i, int j){
	if(boardForShow[i][j] == 10){
		boardForShow[i][j] = board[i][j];
		//if(boardForShow[i][j] != 9) numOfTiles--;
		if(boardForShow[i][j] == 0){
			for(int i1 = -1; i1 < 2; i1++){
                for(int j1 = -1; j1 < 2; j1++){
					if(i+i1 < 0 || i+i1 > BOARD_SIZE_X-1) continue;
					if(j+j1 < 0 || j+j1 > BOARD_SIZE_Y-1) continue;
					loang1(i+i1, j+j1);
				}
			}
		}
	}
}

void loang2(int i, int j){
	if(boardForShow[i][j]>0 && boardForShow[i][j]<9) {
        int count = 0;
        for(int i1 = -1; i1 < 2; i1++){
            for(int j1 = -1; j1 < 2; j1++){
                if(i+i1 < 0 || i+i1 > BOARD_SIZE_X-1) continue;
                if(j+j1 < 0 || j+j1 > BOARD_SIZE_Y-1) continue;
                if(i1 == 0 && j1 == 0) continue;
                if(boardForShow[i+i1][j+j1] == 11) count++;
            }
        }
        if(count == board[i][j]) {
            numOfTiles -= count;
            for(int i1 = -1; i1 < 2; i1++){
                for(int j1 = -1; j1 < 2; j1++){
                    if(i+i1 < 0 || i+i1 > BOARD_SIZE_X-1) continue;
                    if(j+j1 < 0 || j+j1 > BOARD_SIZE_Y-1) continue;
                    if(boardForShow[i+i1][j+j1] == 11) continue;
                    boardForShow[i+i1][j+j1] = board[i+i1][j+j1];
                    if(board[i+i1][j+j1]==0) {
                        boardForShow[i+i1][j+j1]=10;
                        loang1(i+i1, j+j1);
                    }
                }
            }
        }
	}
}

void GameManager(){
	if(playAgain) {
        newGame = true;
        CreateBoard();
        Mix_HaltMusic();
        numOfMines=sumOfMines;
        numOfTiles = BOARD_SIZE_X * BOARD_SIZE_Y;
        winGame = false;
        loseGame = false;
        playAgain = false;
	}

	if(loseGame){
		loseFace.render(21+BOARD_SIZE_X*TILE_SIZE/2-faceButton_size/2, digit_y);
		for(int i = 0; i < BOARD_SIZE_X; i++){
			for(int j = 0; j < BOARD_SIZE_Y; j++){
				Buttons[i][j].renderWhenLose(i, j);
			}
		}
		redMine.render(mlose*TILE_SIZE+board_x, nlose*TILE_SIZE+board_y);
	} else if(winGame){
		winFace.render(21+BOARD_SIZE_X*TILE_SIZE/2-faceButton_size/2, digit_y);
	}
}

void showingMineLeft(){
	if(numOfMines < 10){
		gDigitSpriteSheetTexture.render(digit_x, digit_y, &gSpriteClipsForDigit[0]);
		for(int i = 0;i <= 9;i++){
			if(i == numOfMines) gDigitSpriteSheetTexture.render(digit_x + 28, digit_y, &gSpriteClipsForDigit[i]);
		}
	} else {
	    int n = numOfMines;
		int i = 0;
		while (n > 0){
			int a = n % 10;
			gDigitSpriteSheetTexture.render(digit_x + (1 - i) * 28, digit_y, &gSpriteClipsForDigit[a]);
			n /= 10;
			i++;
		}
	}
}

void setGameMode(int boardsizex, int boardsizey, int mine, int dx, int dy, int fx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& sumOfMines, int& numOfMines, int& numOfTiles, int& digit_x, int& digit_y, int& face_x){
	BOARD_SIZE_X = boardsizex;
	BOARD_SIZE_Y = boardsizey;
	sumOfMines = mine;
	numOfMines = mine;
	numOfTiles = boardsizex*boardsizey;
	digit_x = dx;
	digit_y = dy;
	face_x = fx;

	Buttons.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++){
		Buttons[i].resize(BOARD_SIZE_Y);
	}

	board.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++){
		board[i].resize(BOARD_SIZE_Y);
	}

	boardForShow.resize(BOARD_SIZE_X);
	for (int i = 0; i < BOARD_SIZE_X; i++){
		boardForShow[i].resize(BOARD_SIZE_Y);
	}
}

void renderGame(){
	if (!mute){
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		unMuteSoundT.render(face_x, 0);
		loseMusic = Mix_LoadMUS("BomNo.wav");
		winMusic = Mix_LoadMUS("victory bond.wav");
		click = Mix_LoadWAV("click.wav");
	} else {
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gRenderer);
		muteSoundT.render(face_x, 0);
		click = NULL;
		winMusic = NULL;
		loseMusic = NULL;
	}

    if (easy){
        easyBackGround.render(0, 50);
    } else if(medium){
        mediumBackGround.render(0, 50);
    } else if(hard){
        hardBackGround.render(0, 50);
    }

	playingFace.render(21+BOARD_SIZE_X*TILE_SIZE/2-faceButton_size/2, digit_y);

	//renderButton();
	for(int i = 0; i < BOARD_SIZE_X; i++){
		for(int j = 0;j < BOARD_SIZE_Y;j++){
			Buttons[i][j].render(i, j);
		}
	}
	goBackT.render(0, 0);
	showingMineLeft();
	GameManager();
	SDL_RenderPresent(gRenderer);
}

void close(){
	//Free loaded images
	gTilesSpriteSheetTexture.free();
	gDigitSpriteSheetTexture.free();
	menu.free();
    menu1.free();
    menuColor.free();
    menu1Color.free();
    easyChoice.free();
    mediumChoice.free();
    hardChoice.free();
    easyChoiceColor.free();
    mediumChoiceColor.free();
    hardChoiceColor.free();
    easyBackGround.free();
    mediumBackGround.free();
    hardBackGround.free();
    goBackT.free();
    muteSoundT.free();
    unMuteSoundT.free();
    winFace.free();
    loseFace.free();
    playingFace.free();
    redMine.free();


	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}




