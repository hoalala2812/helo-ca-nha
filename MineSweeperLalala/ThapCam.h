#ifndef _THAPCAM_H//_INCLUDED
#define _THAPCAM_H//_INCLUDED

#include<iostream>
#include<ctime>
#include<stdio.h>
#include "main.h"
#include "ThapCam.h"
#include "Variables.h"

using namespace std;

bool init();

bool loadmedia();

void CreateBoard();

void setButtonPosition();

void createMenu();

void handleMenu();

void handleEventInGame();

void loang1(int i, int j);
void loang2(int i, int j);

void GameManager();

void showingMineLeft();

void setGameMode(int boardsizex, int boardsizey, int mine, int dx, int dy, int fx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& sumOfMines, int& numOfMines, int& numOfTiles, int& digit_x, int& digit_y, int& face_x);

void renderGame();

//close SDL
void close();

#endif // THAPCAM_H_INCLUDED
