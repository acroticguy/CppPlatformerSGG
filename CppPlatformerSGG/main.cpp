#include "graphics.h"
#include "GameState.h"

// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float dt)
{
	GameState::getInstance()->update(dt);
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	if (mouse.button_left_released)
	{
		graphics::playSound("assets\\door2.wav", 1.0f, false);
	}
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