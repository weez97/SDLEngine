#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include "Sprite.h"
#include "HLSLProgram.h"
#include "Window.h"

enum class GameState {
	PLAY,EXIT
};

class MainGame
{
private:
	int max_sprites;
	int width;
	int height;
	float time;
	Window window;
	HLSLProgram program;
	Sprite** sprites;
	void init();
	void processInput();
	void initShaders();

public:
	MainGame(int spriteNum);
	~MainGame();
	GameState gameState;
	
	void run();
	void draw();
	void update();
};

