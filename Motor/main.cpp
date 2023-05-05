#include <SDL/SDL.h>
#include "MainGame.h"

int main(int argc,char** argv) {
	MainGame mainGame(15);
	mainGame.run();
	system("PAUSE");
	return 0;
}