#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include "Sprite.h"
#include "HLSLProgram.h"
#include "Window.h"
#include <vector>

enum class GameState {
	PLAY,EXIT
};

class MainGame
{
private:
	float last_time;
	int max_sprites;
	int width;
	int height;
	float ingame_time;
	Window window;
	HLSLProgram program;
	std::vector<Sprite*> sprites;
	void init();
	void processInput();
	void initShaders();
	void spriteGeneration();

public:
	MainGame(int spriteNum);
	~MainGame();
	GameState gameState;
	
	void run();
	void draw();
	void update();
};

