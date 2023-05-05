#include "MainGame.h"
#include <iostream>
#include "Error.h"
#include <ctime>
#include <cstdlib>
using namespace std;

MainGame::MainGame(int spriteNum) {
	max_sprites = spriteNum;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	ingame_time = 0;
}

MainGame::~MainGame() {

}
void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//cout << event.motion.x << " , " << event.motion.y << endl;
				break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window.create("Hola", width, height,0);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Glew not initialized");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();
}

void MainGame::draw() {
	ingame_time += 0.02;
	if (sprites.size() == 0) return;
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, ingame_time);
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	for (int i = 0; i < sprites.size(); i++)
		sprites[i]->draw();
	program.unuse();
	window.swapWindow();
}

void MainGame::run() {
	srand(unsigned int(time(NULL)));
	init();
	update();
}

void MainGame::spriteGeneration() 
{
	if (sprites.size() == max_sprites || ingame_time - last_time < 5.0) return;

	float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.8 - 1.9;
	float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.8 - 1.9;

	Sprite* sprite = new Sprite();
	sprite->init(x, y, 1, 1, "Textures/imagen.png");
	sprites.push_back(sprite);
	last_time = ingame_time;

}

void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		spriteGeneration();
		processInput();
	}
}