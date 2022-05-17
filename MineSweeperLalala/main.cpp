#include<iostream>
#include "ThapCam.h"

using namespace std;
#undef main

int main() {
	if (!init()){
		cout << "Failed init";
	} else {
		if(loadmedia()){
            while(!quit){
                if(isChoosingMode){
                    handleMenu();
                }
                while(newGame){
                    newGame = false;
                    while(isRunning){
                    handleEventInGame();
                    setButtonPosition();
                    renderGame();
                    }
                }
            }
        }
    }

	close();

    return 0;
}
