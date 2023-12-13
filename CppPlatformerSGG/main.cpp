#include "graphics.h"
#include "GameState.h"

// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float dt)
{
	GameState::getInstance()->update(dt);
}

// The window content drawing function.
void draw()
{
	GameState::getInstance()->draw();
}

bool init() {
	return GameState::getInstance()->init();
}

int main()
{
	graphics::createWindow(1200, 600, "Hello World");

	init();

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();

	return 0;
}