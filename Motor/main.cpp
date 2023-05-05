#include <SDL/SDL.h>
#include "MainGame.h"

int main(int argc,char** argv) {
	MainGame mainGame(2);
	mainGame.run();
	system("PAUSE");
	return 0;
}